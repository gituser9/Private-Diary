using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using PrivateDiary.Service;

namespace PrivateDiary.Migrations
{
    [DbContext(typeof(DataContext))]
    [Migration("20171021184810_DbMigration")]
    partial class DbMigration
    {
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
            modelBuilder
                .HasAnnotation("ProductVersion", "1.1.1");

            modelBuilder.Entity("PrivateDiary.Main.Models.User", b =>
                {
                    b.Property<int>("Id")
                        .ValueGeneratedOnAdd();

                    b.Property<string>("Login");

                    b.Property<string>("Password");

                    b.HasKey("Id");

                    b.ToTable("Users");
                });
        }
    }
}
