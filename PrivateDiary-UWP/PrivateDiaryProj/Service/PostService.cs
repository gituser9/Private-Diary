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
                    db.SaveChanges();
                }
                post.Title = Crypter.Decrypt(post.Title);
                return post;
            }
            catch (Exception e)
            {
                return null;
            }
        }

        public IEnumerable<Post> GetAll()
        {
            using (var db = new DataContext())
            {
                var encryptedPosts = db.Posts.Where(post => post.UserId == Constant.User.Id).ToArray();
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

        public void Update(string body, string title, int postId)
        {
            using (var db = new DataContext())
            {
                var post = db.Posts.Find(postId);
                post.Body = Crypter.Encrypt(body);
                post.Title = Crypter.Encrypt(title);

                db.Entry(post).State = EntityState.Modified;
                db.SaveChanges();
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


        private long GetTimestamp()
        {
            var timeSpan = DateTime.Now - new DateTime(1970, 1, 1, 0, 0, 0);
            return (long) timeSpan.TotalSeconds;
        }
    }
}
