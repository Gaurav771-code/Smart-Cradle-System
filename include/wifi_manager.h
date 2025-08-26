#pragma once
#include <Arduino.h>

class WiFiManagerCustom {
public:
  bool begin();          // connect or start AP
  void handleClient();   // run in loop
  bool isConnected();    // check WiFi connection
};
