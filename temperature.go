package main

import (
	"net/http"
	"time"

	"github.com/gin-gonic/gin"
	"github.com/st-a-y/smart-enclosure/container"
)

type Temperature struct {
	Time  time.Time
	Value float32
}

func GetTemperature(c *gin.Context) {
	c.IndentedJSON(http.StatusOK, Temperature{
		Time:  time.Now(),
		Value: container.GetSensorService().GetTemperature(),
	})
}
