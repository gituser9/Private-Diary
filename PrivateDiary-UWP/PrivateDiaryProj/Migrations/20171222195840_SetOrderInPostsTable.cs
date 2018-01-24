using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Migrations;
using PrivateDiary.Service;

namespace PrivateDiary.Migrations
{
    public partial class SetOrderInPostsTable : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            using (var db = new DataContext())
            {
                var posts = db.Posts;

                foreach (var post in posts)
                {
                    post.Order = post.Id;

                    db.Entry(post).State = EntityState.Modified;
                }

                db.SaveChanges();
            }
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {

        }
    }
}
