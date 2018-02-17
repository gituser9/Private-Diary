using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using PrivateDiary.Model;

namespace PrivateDiary.Service
{
    public class PostService
    {
        //private readonly IDataContext _dataContext;

        public Post AddPost(string title, string body)
        {
            try
            {
                var post = new Post
                {
                    Title = Crypter.Encrypt(title),
                    Body = Crypter.Encrypt(body),
                    Date = GetTimestamp(),
                    UserId = Constant.User.Id
                };
                using (var db = new DataContext())
                {
                    db.Posts.AddAsync(post);
                    db.SaveChangesAsync();

                    post.Order = post.Id;
                    db.Entry(post).State = EntityState.Modified;
                    db.SaveChangesAsync();
                }
                post.Title = Crypter.Decrypt(post.Title);
                return post;
            }
            catch (Exception e)
            {
                return null;
            }
        }

        public async Task<IEnumerable<Post>> GetAll()
        {
            using (var db = new DataContext())
            {
                var encryptedPosts = await db.Posts.Where(post => post.UserId == Constant.User.Id).OrderBy(entity => entity.Order).ToArrayAsync();
                var decryptedPosts = new List<Post>(encryptedPosts.Length);

                foreach (Post encryptedPost in encryptedPosts)
                {
                    decryptedPosts.Add(new Post
                    {
                        Id = encryptedPost.Id,
                        UserId = encryptedPost.UserId,
                        Date = encryptedPost.Date,
                        Title = Crypter.Decrypt(encryptedPost.Title)
                    });
                }

                return decryptedPosts;
            }
        }

        public async Task<IEnumerable<Post>> Search(string searchString)
        {
            using (var db = new DataContext())
            {
                var encryptedPosts = await db.Posts.Where(post => post.UserId == Constant.User.Id).OrderBy(entity => entity.Order).ToArrayAsync();
                var decryptedPosts = new List<Post>(encryptedPosts.Length);
                var result = new List<Post>();

                foreach (Post encryptedPost in encryptedPosts)
                {
                    decryptedPosts.Add(new Post
                    {
                        Id = encryptedPost.Id,
                        UserId = encryptedPost.UserId,
                        Date = encryptedPost.Date,
                        Title = Crypter.Decrypt(encryptedPost.Title),
                        Body = Crypter.Decrypt(encryptedPost.Body)
                    });
                }
                foreach (Post post in decryptedPosts)
                {
                    if (post.Title.Contains(searchString) || post.Body.Contains(searchString))
                    {
                        result.Add(post);
                    }    
                }

                return result;
            }
        }

        public async Task<Post> Get(int id)
        {
            using (var db = new DataContext())
            {
                var encryptedPost = await db.Posts.FindAsync(id);
                return new Post
                {
                    Id = encryptedPost.Id,
                    UserId = encryptedPost.UserId,
                    Date = encryptedPost.Date,
                    Body = Crypter.Decrypt(encryptedPost.Body),
                    Title = Crypter.Decrypt(encryptedPost.Title)
                };
            }
        }

        public async Task Update(string body, string title, int postId)
        {
            using (var db = new DataContext())
            {
                var post = await db.Posts.FindAsync(postId);
                post.Body = Crypter.Encrypt(body);
                post.Title = Crypter.Encrypt(title);

                db.Entry(post).State = EntityState.Modified;
                await db.SaveChangesAsync();
            }
        }

        public async Task Delete(int postId)
        {
            using (var db = new DataContext())
            {
                var post = db.Posts.Find(postId);
                db.Remove(post);
                await db.SaveChangesAsync();
            }
        }

        public async Task UpdatePosition(int postId, int position)
        {
            using (var db = new DataContext())
            {
                var post = db.Posts.Find(postId);
                post.Order = position;

                db.Entry(post).State = EntityState.Modified;
                await db.SaveChangesAsync();
            }
        }


        private long GetTimestamp()
        {
            var timeSpan = DateTime.Now - new DateTime(1970, 1, 1, 0, 0, 0);
            return (long) timeSpan.TotalSeconds;
        }
    }
}
