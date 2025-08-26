#ifndef TYPES_H
#define TYPES_H

struct SensorData {
  float temperatureC;
  float humidity;
  int rainValue;
  bool motionDetected;
  int soundLevel;   // <-- NEW: sound sensor reading
};

#endif
