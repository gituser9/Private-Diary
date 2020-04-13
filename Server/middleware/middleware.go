package middleware

import (
	"errors"
	"fmt"
	"log"
	"net/http"
	"strings"
	"time"

	"server/model/dao"

	"github.com/dgrijalva/jwt-go"
)

const authHeader = "Authorization"
const bearer = "Bearer "

var config = dao.Config{}

type AuthenticationMiddleware struct {
	config dao.Config
}

func (amw *AuthenticationMiddleware) Middleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		if err := amw.jwtValidate(r); err != nil {
			log.Println("jwt validation error:", err)
			w.WriteHeader(http.StatusForbidden)
			return
		}
		next.ServeHTTP(w, r)
	})
}

func (amw *AuthenticationMiddleware) jwtValidate(r *http.Request) error {
	tokenString := getJwtString(r)

	if tokenString == "" {
		return errors.New("token is empty")
	}

	claims := dao.JwtClaims{}
	_, err := jwt.ParseWithClaims(
		tokenString,
		&claims,
		func(token *jwt.Token) (interface{}, error) {
			return []byte(config.JwtSign), nil
		},
	)

	if err != nil {
		log.Println("JWT error:", err)
		return fmt.Errorf("parse JWT error: %s", err)
	}
	if claims.Exp == 0 || claims.Exp < time.Now().Unix() {
		return errors.New("JWT is expired")
	}
	if claims.Sign == "" {
		return errors.New("sign is required")
	}

	return nil
}

func (amw *AuthenticationMiddleware) Setup(cfg dao.Config) {
	config = cfg
}

func getJwtString(r *http.Request) string {
	return strings.TrimSpace(strings.TrimPrefix(r.Header.Get(authHeader), bearer))
}
