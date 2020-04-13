package controller

import (
	"net/http"
	"server/model/dao"
	"strings"

	"github.com/dgrijalva/jwt-go"
)

const authHeader = "Authorization"
const bearer = "Bearer "

var config = dao.Config{}

func Setup(cfg dao.Config) {
	config = cfg
}

func getClaims(r *http.Request) dao.JwtClaims {
	claims := dao.JwtClaims{}
	tokenString := getJwtString(r)

	_, _ = jwt.ParseWithClaims(
		tokenString,
		&claims,
		func(token *jwt.Token) (interface{}, error) {
			return []byte(config.JwtSign), nil
		},
	)

	return claims
}

func getJwtString(r *http.Request) string {
	return strings.TrimSpace(strings.TrimPrefix(r.Header.Get(authHeader), bearer))
}

func getInclude(include string) []string {
	return strings.Split(include, ",")
}
