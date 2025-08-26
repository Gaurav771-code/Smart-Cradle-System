#include <Arduino.h>
#include "config.h"
#include "types.h"
#include "sensors.h"
#include "servomotar.h"
#include "eeprom_store.h"
#include "wifi_manager.h"

Sensors sensors;
CradleServo cradle;
EEPROMStore store;
CradleConfig config;
WiFiManagerCustom wifiManager;

unsigned long lastRead = 0;
SensorData data;

void setup() {
  Serial.begin(115200);

  store.begin(EEPROM_SIZE);
  if (!store.load(config)) {
    store.reset(config); // start fresh if empty
  }

  wifiManager.begin();   // connect or start AP
  sensors.begin();
  cradle.begin(PIN_SERVO_LEFT, PIN_SERVO_RIGHT);
}

void loop() {
  wifiManager.handleClient();

  unsigned long now = millis();
  if (now - lastRead > LOOP_INTERVAL_MS) {
    lastRead = now;
    sensors.read(data);
    Serial.printf("Temp: %.2f C, Hum: %.2f %%, Rain: %d, Motion: %d\n",
                  data.temperatureC, data.humidity,
                  data.rainValue, data.motionDetected);
  }

  cradle.update(now, ROCK_PERIOD_MS, true);
}
