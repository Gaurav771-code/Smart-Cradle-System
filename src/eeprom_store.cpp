#include "eeprom_store.h"
#include <EEPROM.h>

bool EEPROMStore::begin(size_t size) {
  return EEPROM.begin(size);
}

bool EEPROMStore::load(CradleConfig &cfg) {
  EEPROM.get(0, cfg);
  // if SSID looks empty, return false
  if (cfg.wifiSsid[0] == '\0') return false;
  return true;
}

bool EEPROMStore::save(const CradleConfig &cfg) {
  EEPROM.put(0, cfg);
  return EEPROM.commit();
}

void EEPROMStore::reset(CradleConfig &cfg) {
  memset(&cfg, 0, sizeof(cfg));
  EEPROM.put(0, cfg);
  EEPROM.commit();
}
