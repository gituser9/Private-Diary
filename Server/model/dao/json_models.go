package dao

type AuthData struct {
	Token        string `json:"token"`
	RefreshToken string `json:"refresh_token"`
}

type ApiError struct {
	Error string `json:"error,omitempty"`
}
