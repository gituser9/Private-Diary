package dao

type Post struct {
	Id       int64  `json:"id"`
	UserId   int64  `gorm:"column:userId" json:"userId"`
	Date     int64  `json:"date"`
	UserSign string `json:"user_sign"`
	Title    string `json:"title"`
	Body     string `json:"body"`
	Order    int    `gorm:"column:post_order" json:"order"`
}
