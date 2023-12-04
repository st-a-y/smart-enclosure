package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
	"github.com/st-a-y/smart-enclosure/handlers"
)

func main() {
	router := gin.Default()

	router.GET("/temperature", handlers.GetTemperature)
	router.GET("/humidity", func(c *gin.Context) {
		c.JSON(http.StatusOK, gin.H{
			"message": "pong",
		})
	})
	router.POST("/create-tag", func(c *gin.Context) {
		c.JSON(http.StatusOK, gin.H{
			"message": "pong",
		})
	})
	router.POST("/add-condition", func(c *gin.Context) {
		c.JSON(http.StatusOK, gin.H{
			"message": "pong",
		})
	})

	router.Run("localhost:8080")
}
