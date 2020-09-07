#include <ESP8266WiFi.h>

const char* ssid = "LudwigEFigueiredo";
const char* pass = "41992549713";

void setup()
{
Serial.begin(9600);
WiFi.begin(ssid, pass);

uint8_t i = 0;
    while (WiFi.status() != WL_CONNECTED && i++ < 20)
    {
      Serial.print(".");
      delay(500);
    }

    if (i == 21) {
      Serial.print("\nCould not connect to"); Serial.println(ssid);
    }
    else
    {
      Serial.println("\nConnected!");
      Serial.print("Network IP address: "); Serial.println(WiFi.localIP());
    }

}
