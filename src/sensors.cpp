#include "sensors.h"
#include "config.h"
#include <DHT.h>

static DHT dht(PIN_DHT, DHT_TYPE);

bool Sensors::begin() {
  dht.begin();
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_SOUND, INPUT);  // <-- NEW: Sound sensor pin
  return true;
}

void Sensors::read(SensorData &out) {
  out.temperatureC = dht.readTemperature();
  out.humidity = dht.readHumidity();
  out.rainValue = analogRead(PIN_RAIN);
  out.motionDetected = digitalRead(PIN_PIR);
  out.soundLevel = analogRead(PIN_SOUND);  // <-- NEW: Sound sensor value
}
