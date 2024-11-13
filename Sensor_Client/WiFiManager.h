#ifndef WIFICONTROLLER_H
#define WIFICONTROLLER_H

#include <WiFi.h>

class WiFiController {
  const char* SSID;
  const char* PASSWORD;

public:
  WiFiController(const char* WIFi_SSID, const char* WIFI_PASSWORD);
  void connect();
};

#endif 
