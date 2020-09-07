#include <Arduino.h>
#line 1 "c:\\Users\\leona\\OneDrive\\Documentos\\Arduino\\generated_examples\\BareMinimum_2\\BareMinimum.ino"
#line 1 "c:\\Users\\leona\\OneDrive\\Documentos\\Arduino\\generated_examples\\BareMinimum_2\\BareMinimum.ino"
#include <OledDisplay.h>
#include <HTS221Sensor.h>
#include <stdarg.h> // sprintf

HTS221Sensor *sensor;
DevI2C *i2c;
float tempC;
float tempF;
float humidity;
// string message;
char buffer[99];

#line 13 "c:\\Users\\leona\\OneDrive\\Documentos\\Arduino\\generated_examples\\BareMinimum_2\\BareMinimum.ino"
void setup();
#line 22 "c:\\Users\\leona\\OneDrive\\Documentos\\Arduino\\generated_examples\\BareMinimum_2\\BareMinimum.ino"
void loop();
#line 13 "c:\\Users\\leona\\OneDrive\\Documentos\\Arduino\\generated_examples\\BareMinimum_2\\BareMinimum.ino"
void setup()
{
    // put your setup code here, to run once:
    Screen.init();
    i2c = new DevI2C(D14, D15);
    sensor = new HTS221Sensor(*i2c);
    sensor->init(NULL);
}

void loop()
{
    // put your main code here, to run repeatedly:
    Screen.print("Hello MXChip!!");
}

