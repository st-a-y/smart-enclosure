package services

import "github.com/st-a-y/smart-enclosure/sensors"

type SensorService struct {
	tempSensor     sensors.TempSensor
	humiditySensor sensors.HumiditySensor
}

func NewSensorService(tempSensor sensors.TempSensor, humiditySensor sensors.HumiditySensor) *SensorService {
	return &SensorService{
		tempSensor:     tempSensor,
		humiditySensor: humiditySensor,
	}
}

func (s *SensorService) GetTemperature() float32 {
	return s.tempSensor.GetTemperature()
}

func (s *SensorService) GetHumidity() float32 {
	return s.humiditySensor.GetHumidity()
}
