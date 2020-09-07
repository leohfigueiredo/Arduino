#include <RGB_LED.h>

RGB_LED led;
int delayMs = 2000;
uint8_t colors[][3] = {
    {255, 0, 0},    // red
    {0, 255, 0},    // green
    {0, 0, 255},    // blue
};

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
// get the number of colors defined in the colors[] array
int lcv = sizeof(colors) / 3;

for (int i = 0; i < lcv; ++i)
{
    led.setColor(colors[i][0], colors[i][1], colors[i][2]);
    delay(delayMs);
    Serial.printf("Color values: %d, %d, %d\n", colors[i][0], colors[i][1], colors[i][2]);
}

}
