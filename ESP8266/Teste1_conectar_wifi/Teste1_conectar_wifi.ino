// Libraries
#include <ESP8266WiFi.h>

// WiFi network
const char* ssid = "LudwigEFigueiredo";
const char* password = "41992549713";
void setup() {
  
// Start serial
Serial.begin(115200);
delay(5000);

// Connecting to a WiFi network
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");

}

Serial.println("");
Serial.println("WiFi connected!!!");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());

}
void loop() {
}
