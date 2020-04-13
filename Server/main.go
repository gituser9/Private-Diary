package main

import (
	"log"
	"net/http"
	"os"

	"server/controller"
	"server/middleware"
	"server/model/dao"
	"server/model/service"

	"github.com/gorilla/mux"
	_ "github.com/joho/godotenv/autoload"
)

var config = dao.Config{}

func init() {
	config = dao.Config{
		Driver:           os.Getenv("DB_DRIVER"),
		ConnectionString: os.Getenv("DATABASE_URL"),
		Address:          os.Getenv("SERVER_ADDRESS"),
		JwtSign:          os.Getenv("JWT_SIGN"),
	}
}

func createRouter() http.Handler {
	router := mux.NewRouter()
	router.StrictSlash(true)

	// posts
	router.HandleFunc("/posts", controller.GetAll).Methods(http.MethodGet)
	router.HandleFunc("/posts", controller.Create).Methods(http.MethodPost)
	router.HandleFunc("/posts/{id}", controller.Get).Methods(http.MethodGet)
	router.HandleFunc("/posts/{id}", controller.UpdatePost).Methods(http.MethodPut)
	router.HandleFunc("/posts/{id}", controller.Delete).Methods(http.MethodDelete)

	// middleware
	amw := middleware.AuthenticationMiddleware{}
	amw.Setup(config)

	router.Use(amw.Middleware)

	return router
}

func main() {
	controller.Setup(config)
	service.Setup(config)
	defer service.Close()

	router := createRouter()
	log.Println("Server start on", config.Address)

	if err := http.ListenAndServe(config.Address, router); err != nil {
		panic("start server error: " + err.Error())
	}
}
