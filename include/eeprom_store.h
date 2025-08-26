#pragma once
#include <Arduino.h>

#define EEPROM_SIZE 512

struct CradleConfig {
  char wifiSsid[32];
  char wifiPass[64];
  uint16_t rainThreshold;
};

class EEPROMStore {
public:
  bool begin(size_t size);
  bool load(CradleConfig &cfg);
  bool save(const CradleConfig &cfg);
  void reset(CradleConfig &cfg);
};
