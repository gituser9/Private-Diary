using System.Threading;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using PrivateDiary.Model;

namespace PrivateDiary.Service
{
    public interface IDataContext
    {
        DbSet<User> Users { get; set; }
        DbSet<Post> Posts { get; set; }

        int SaveChanges();
        Task<int> SaveChangesAsync(CancellationToken cancellationToken = default(CancellationToken));

    }


    public class DataContext : DbContext, IDataContext
    {
        public DbSet<User> Users { get; set; }
        public DbSet<Post> Posts { get; set; }


        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            base.OnConfiguring(optionsBuilder);

            

            optionsBuilder.UseSqlite("Filename=" + Constant.DbName);
        }
    }
}
