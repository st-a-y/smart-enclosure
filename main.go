package main

import (
	"github.com/gin-gonic/gin"
	"github.com/st-a-y/smart-enclosure/handlers"
)

func main() {
	router := gin.Default()
	router.GET("/temperature", handlers.GetTemperature)

	router.Run("localhost:8080")
}
