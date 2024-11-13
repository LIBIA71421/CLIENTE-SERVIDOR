#include <WiFiController.h>
#include <LEDController.h>

const char* WIFI_SSID = "";
const char* WIFI_PASS = "";
const char* SERVER_ADDRESS = "0.0.0.0";
const int SERVER_PORT = 80;

const int LED_PINS[] = { 12, 14, 27, 26};
const int LED_COUNT = sizeof(LED_PINS) / sizeof(LED_PINS[0]);

WiFiController wifiController(WIFI_SSID, WIFI_PASS);
LEDController ledController(LED_PINS, LED_COUNT);

void setup() {
  Serial.begin(115200);
  wifiController.connect();
}

void loop() {
  delay(300);
  
  ledController.turnOffAll();

  WiFiClient client;
  Serial.print("Connecting to server: ");
  Serial.println(SERVER_ADDRESS);

  if (!client.connect(SERVER_ADDRESS, SERVER_PORT)) {
    Serial.println("Connection failed");
    return;
  }

  client.println("GET");

  unsigned long previousMillis = millis();
  while (!client.available() && millis() - previousMillis < 1000);

  if (client.available() > 0) {
    String line = client.readStringUntil('\n');
    int distance = line.toInt();
    Serial.println("Distance received from server: " + String(distance));

    ledController.setLEDsBasedOnDistance(distance);
  } else {
    Serial.println("Server timeout.");
  }

  Serial.println("Closing connection.");
  client.stop();
}
