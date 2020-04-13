package service

import (
	"log"

	"server/model/dao"

	"github.com/jinzhu/gorm"
)

func GetPostList(userSign string) []dao.Post {
	posts := make([]dao.Post, 0)

	dbExec(func(db *gorm.DB) {
		if err := db.Where(dao.Post{UserSign: userSign}).Find(&posts).Error; err != nil {
			log.Println("get post list error:", err)
		}
	})

	return posts
}

func GetPostById(id int64, userSign string) dao.Post {
	post := dao.Post{}

	dbExec(func(db *gorm.DB) {
		if err := db.Where(dao.Post{Id: id, UserSign: userSign}).First(&post).Error; err != nil {
			log.Println("get post error:", err)
		}
	})

	return post
}

func CreatePost(post dao.Post) dao.Post {
	dbExec(func(db *gorm.DB) {
		if err := db.Save(&post).Error; err != nil {
			log.Println("create post error:", err)
		}
	})

	return post
}

func UpdatePost(post dao.Post) dao.Post {
	dbExec(func(db *gorm.DB) {
		fields := map[string]interface{}{
			"title": post.Title,
			"body":  post.Body,
		}
		err := db.Where("id = ? and user_sign = ?", post.Id, post.UserSign).
			Updates(fields).
			Error
		if err != nil {
			log.Println("update post error:", err)
		}
	})

	return post
}

func Delete(id int64, userId int64, sign string) {
	dbExec(func(db *gorm.DB) {
		if err := db.Where(dao.Post{Id: id, UserId: userId, UserSign: sign}).Delete(&dao.Post{}).Error; err != nil {
			log.Println("delete post error:", err)
		}
	})
}
