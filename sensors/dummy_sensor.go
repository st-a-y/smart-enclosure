package sensors

import "math/rand"

type DummySensor struct{}

func (s *DummySensor) GetHumidity() float32 {
	return rand.Float32()
}

func (s *DummySensor) GetTemperature() float32 {
	return rand.Float32()
}
