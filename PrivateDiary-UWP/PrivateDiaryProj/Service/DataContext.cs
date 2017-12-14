using Microsoft.EntityFrameworkCore;
using PrivateDiary.Model;

namespace PrivateDiary.Service
{
    public interface IDataContext
    {
        DbSet<User> Users { get; set; }
        DbSet<Post> Posts { get; set; }

        int SaveChanges();
    }


    public class DataContext : DbContext, IDataContext
    {
        public DbSet<User> Users { get; set; }
        public DbSet<Post> Posts { get; set; }


        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            base.OnConfiguring(optionsBuilder);

            

            optionsBuilder.UseSqlite("Filename=PrivateDiary.dbx");
        }
    }
}
