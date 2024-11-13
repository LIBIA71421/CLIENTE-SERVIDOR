#include "WiFiController.h"

WiFiController::WiFiController(const char* WIFi_SSID, const char* WIFI_PASSWORD)
  : SSID(WIFi_SSID), PASSWORD(WIFI_PASSWORD) {}

void WiFiController::connect() {
  Serial.print("Connecting to: ");
  Serial.print(SSID);
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());
}
