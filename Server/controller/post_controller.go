package controller

import (
	"encoding/json"
	"log"
	"net/http"
	"server/model/dao"
	"server/model/service"
	"strconv"

	"github.com/gorilla/mux"
)

const userSignHeader = "X-Auth-Id"

func GetAll(w http.ResponseWriter, r *http.Request) {
	claims := getClaims(r)
	posts := service.GetPostList(claims.Sign)

	if err := json.NewEncoder(w).Encode(posts); err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		return
	}
}

func Get(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	postId, err := strconv.ParseInt(vars["id"], 10, 64)

	if err != nil {
		w.WriteHeader(http.StatusBadRequest)
		return
	}

	claims := getClaims(r)
	post := service.GetPostById(postId, claims.Sign)

	if post.Id == 0 {
		w.WriteHeader(http.StatusNotFound)
		return
	}
	if err := json.NewEncoder(w).Encode(post); err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		return
	}
}

func Create(w http.ResponseWriter, r *http.Request) {
	post := dao.Post{}

	if err := json.NewDecoder(r.Body).Decode(&post); err != nil {
		log.Println("decode post error:", err)
		w.WriteHeader(http.StatusBadRequest)
		return
	}

	claims := getClaims(r)
	post.UserSign = claims.Sign
	post = service.CreatePost(post)

	if post.Id == 0 {
		w.WriteHeader(http.StatusInternalServerError)
		return
	}
	if err := json.NewEncoder(w).Encode(post); err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		return
	}
}

func UpdatePost(w http.ResponseWriter, r *http.Request) {
	claims := getClaims(r)
	post := dao.Post{}

	if err := json.NewDecoder(r.Body).Decode(&post); err != nil {
		w.WriteHeader(http.StatusBadRequest)
		return
	}
	if claims.Id != post.UserId {
		w.WriteHeader(http.StatusForbidden)
		return
	}

	post.UserSign = claims.Sign
	post = service.UpdatePost(post)

	if err := json.NewEncoder(w).Encode(post); err != nil {
		w.WriteHeader(http.StatusInternalServerError)
		return
	}
}

func Delete(w http.ResponseWriter, r *http.Request) {
	claims := getClaims(r)
	vars := mux.Vars(r)
	postId, err := strconv.ParseInt(vars["id"], 10, 64)

	if err != nil {
		w.WriteHeader(http.StatusBadRequest)
		return
	}

	service.Delete(postId, claims.Id, claims.Sign)
}
