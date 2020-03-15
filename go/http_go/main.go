package main

import (
	"http_server_test/handlers"
	"github.com/gin-gonic/gin"
)

func main(){
	r:= gin.Default()
	r.GET("/ping", handlers.Ping)
	r.Run()
}
