package dao

import "github.com/dgrijalva/jwt-go"

type Config struct {
	Driver           string
	ConnectionString string
	Address          string
	JwtSign          string
}

type JwtClaims struct {
	*jwt.MapClaims
	Id   int64
	Exp  int64
	Sign string
}

func (JwtClaims) Valid() error {
	return nil
}
