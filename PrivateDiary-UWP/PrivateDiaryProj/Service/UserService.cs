using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using PrivateDiary.Model;

namespace PrivateDiary.Service
{
    public interface IUserService
    {
        Task<bool> Registration(string login, string password);
        Task<User> Auth(string login, string password);
        Task<User> Update(string login, string oldPassword, string newPassword, User userData);
    }


    public class UserService : IUserService
    {
        private readonly IDataContext _dataContext;

        public UserService(IDataContext dataContext)
        {
            _dataContext = dataContext;
        }

        public async Task<bool> Registration(string login, string password)
        {
            try
            {
                using (var db = new DataContext())
                {
                    bool isExist = await db.Users.AnyAsync(user => user.Login == login);

                    if (isExist)
                    {
                        return false;
                    }

                    db.Users.Add(new User
                    {
                        Login = login,
                        Password = HashPassword(password)
                    });
                    await db.SaveChangesAsync();
                }
                return true;
            }
            catch
            {
                return false;
            }
        }

        public async Task<User> Auth(string login, string password)
        {
            string passwordHash = HashPassword(password);

            
            return await _dataContext.Users.FirstOrDefaultAsync(user =>
                    user.Login == login
                    && user.Password == passwordHash
                );   
        }

        public async Task<User> Update(string login, string oldPassword, string newPassword, User userData)
        {
            string oldPasswordHash = HashPassword(oldPassword);
            User user = await _dataContext.Users.FirstOrDefaultAsync(entity =>
                entity.Login == userData.Login
                && entity.Password == oldPasswordHash
            );

            if (user == null)
            {
                return null;
            }

            user.Login = login;

            if (newPassword == oldPassword)
            {
                await _dataContext.SaveChangesAsync();
                return user;
            }

            user.Password = HashPassword(newPassword);
            IEnumerable<Post> posts = await _dataContext.Posts.ToArrayAsync();

            foreach (Post post in posts)
            {
                // decrypt all posts
                post.Title = Crypter.Decrypt(post.Title);
                post.Body = Crypter.Decrypt(post.Body);
            }
            Constant.Key = newPassword;
            Constant.User = user;
            foreach (Post post in posts)
            {
                // encrypt all posts
                post.Title = Crypter.Encrypt(post.Title);
                post.Body = Crypter.Encrypt(post.Body);
            }

            await _dataContext.SaveChangesAsync();

            return user;
        }



        private string HashPassword(string password)
        {
            byte[] bytes = new UTF8Encoding().GetBytes(password);
            byte[] hashBytes = System.Security.Cryptography.SHA256.Create().ComputeHash(bytes);

            return Convert.ToBase64String(hashBytes);
        }
    }
}
