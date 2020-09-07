#include <OledDisplay.h>
#include <RGB_LED.h>
#include <stddef.h>

int sensorPin = 4;
int inputValue = 0;
int lightLevel = 0;
RGB_LED led;


void setup() {
  Screen.init();

}

void loop() {
inputValue = analogRead(sensorPin);

Screen.print("Analog Value:", false);

char buf[10];
sprintf(buf, "%d", inputValue);
Screen.print(1, buf);

lightLevel = 255 * inputValue / 1024;

sprintf(buf, "%d / 255", lightLevel);
Screen.print(2, buf);

if (lightLevel > 255) {
    lightLevel = 255;
}

sprintf(buf, "%d / 255", lightLevel);
Screen.print(3, buf);

led.setColor(lightLevel, lightLevel, lightLevel);

}