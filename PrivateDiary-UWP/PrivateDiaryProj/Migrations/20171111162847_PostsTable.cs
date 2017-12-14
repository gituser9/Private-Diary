using System;
using Microsoft.EntityFrameworkCore.Migrations;

namespace PrivateDiary.Migrations
{
    public partial class PostsTable : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Posts",
                columns: table => new
                {
                    Id = table.Column<int>(nullable: false).Annotation("Sqlite:Autoincrement", true),
                    Body = table.Column<string>(nullable: true),
                    Date = table.Column<DateTime>(nullable: false),
                    Title = table.Column<string>(nullable: false),
                    UserId = table.Column<int>(nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Posts", x => x.Id);
                });
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Posts");
        }
    }
}
