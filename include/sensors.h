#ifndef SENSORS_H
#define SENSORS_H

#include "types.h"

class Sensors {
public:
  static bool begin();
  static void read(SensorData &out);
};

#endif
