// Libraries
#include <ESP8266WiFi.h>

// WiFi network
const char* ssid = "LudwigEFigueiredo";
const char* password = "41992549713";

// Host
const char* host = "dweet.io";

void setup() {
// Serial
Serial.begin(115200);

delay(3000);
// We start by connecting to a WiFi network
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(15000);
Serial.print(".");
}
}
void loop() {
delay(7000);
Serial.print("connecting to ");
Serial.println(host);

// Use WiFiClient class to create TCP connections
WiFiClient client;
const int httpPort = 80;
if (!client.connect(host, httpPort)) {
Serial.println("connection failed");
return;
}

// We now create a URI (Uniform Resource Identifier - is a string of characters used to identify a resource) for the request
String url = "www.google.com";

// Send request
Serial.print("Requesting URL: ");
Serial.println(url);
client.print(String("GET ") + url + " HTTP/1.1\r\n" +
"Host: " + host + "\r\n" +
"Connection: close\r\n\r\n");
unsigned long timeout = millis();
while (client.available() == 0) {
if (millis() - timeout > 5000) {
Serial.println(">>> Client Timeout !");
client.stop();
return;
}
}
// Read all the lines from the answer
while(client.available()){
String line = client.readStringUntil('\r');
Serial.print(line);
}
// Close connecting
Serial.println();
Serial.println("closing connection");
}
