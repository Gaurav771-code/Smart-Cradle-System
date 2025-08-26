#include "wifi_manager.h"
#include "eeprom_store.h"
#include "config.h"
#include <WiFi.h>
#include <WebServer.h>

extern EEPROMStore store;
extern CradleConfig config;

static WebServer server(80);
static bool connected = false;

void handleRoot() {
  String html = "<html><body><h2>ESP32 WiFi Setup</h2>";
  html += "<form action='/save' method='POST'>";
  html += "SSID: <input name='ssid'><br>";
  html += "Password: <input name='pass' type='password'><br>";
  html += "<input type='submit' value='Save'>";
  html += "</form></body></html>";
  server.send(200, "text/html", html);
}

void handleSave() {
  if (server.hasArg("ssid") && server.hasArg("pass")) {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");

    ssid.toCharArray(config.wifiSsid, sizeof(config.wifiSsid));
    pass.toCharArray(config.wifiPass, sizeof(config.wifiPass));
    config.rainThreshold = 2000;

    store.save(config);

    server.send(200, "text/html",
      "<html><body><h3>Saved! Restart ESP32 to connect.</h3></body></html>");
  } else {
    server.send(400, "text/plain", "Missing SSID or password");
  }
}

bool WiFiManagerCustom::begin() {
  if (strlen(config.wifiSsid) > 0) {
    WiFi.begin(config.wifiSsid, config.wifiPass);
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
      delay(500);
      Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nConnected to WiFi!");
      Serial.println(WiFi.localIP());
      connected = true;
      return true;
    }
  }

  // fallback AP mode
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP32-Setup", "12345678");
  Serial.println("AP Mode started: SSID=ESP32-Setup, PASS=12345678");
  Serial.println("Open http://192.168.4.1/");

  server.on("/", handleRoot);
  server.on("/save", HTTP_POST, handleSave);
  server.begin();

  connected = false;
  return false;
}

void WiFiManagerCustom::handleClient() {
  if (!connected) {
    server.handleClient();
  }
}

bool WiFiManagerCustom::isConnected() {
  return connected;
}
