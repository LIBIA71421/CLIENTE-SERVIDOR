#include <WiFiController.h>
#include <UltrasonicSensor.h>

const char* WIFI_SSID = "";    
const char* WIFI_PASSWORD = "";      
const char* SERVER_ADDRESS = "0.0.0.0";   
const int SERVER_PORT = 80;                 

const int TRIGGER_PIN = 14;
const int ECHO_PIN = 12;

WiFiController wifiController(WIFI_SSID, WIFI_PASSWORD);
UltrasonicSensor ultrasonicSensor(TRIGGER_PIN, ECHO_PIN);

void setup() {
  Serial.begin(115200);   
  wifiController.connect();  
}

void loop() {
  long duration = ultrasonicSensor.readDistance();
  int distanceCm = 0.01723 * duration;   
  Serial.println(distanceCm);            
  delay(1000);                            

  Serial.print("Connecting to server: ");
  Serial.println(SERVER_ADDRESS);

  WiFiClient client;

  if (!client.connect(SERVER_ADDRESS, SERVER_PORT)) {
    Serial.println("Connection failed");
    return;
  }

  client.println("distance=" + String(distanceCm));

  String response = client.readStringUntil('\n');
  Serial.println(response);

  Serial.println("Closing connection.");
  client.stop();
}
