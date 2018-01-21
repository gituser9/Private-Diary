using System;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using PrivateDiary.Model;

namespace PrivateDiary.Service
{
    public interface IUserService
    {
        bool Registration(string login, string password);
        Task<User> Auth(string login, string password);
    }


    public class UserService : IUserService
    {
        private readonly IDataContext _dataContext;

        public UserService(IDataContext dataContext)
        {
            _dataContext = dataContext;
        }

        public bool Registration(string login, string password)
        {
            try
            {
                using (var db = new DataContext())
                {
                    bool isExist = db.Users.Any(user => user.Login == login);

                    if (isExist)
                    {
                        return false;
                    }

                    db.Users.Add(new User
                    {
                        Login = login,
                        Password = HashPassword(password)
                    });
                    db.SaveChanges();
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
            /*using (var db = new DataContext())
            {*/
                string passwordHash = HashPassword(password);

              //  return await db.Users.FirstOrDefaultAsync(user =>
                return await _dataContext.Users.FirstOrDefaultAsync(user =>
                        user.Login == login
                        && user.Password == passwordHash
                    );
            //}
        }



        private string HashPassword(string password)
        {
            byte[] bytes = new UTF8Encoding().GetBytes(password);
            byte[] hashBytes = System.Security.Cryptography.SHA256.Create().ComputeHash(bytes);

            return Convert.ToBase64String(hashBytes);
        }
    }
}
