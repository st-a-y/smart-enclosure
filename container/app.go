package container

import (
	"github.com/st-a-y/smart-enclosure/sensors"
	"github.com/st-a-y/smart-enclosure/services"
)

func GetSensorService() *services.SensorService {
	dummySensor := sensors.DummySensor{}
	return services.NewSensorService(&dummySensor, &dummySensor)
}
