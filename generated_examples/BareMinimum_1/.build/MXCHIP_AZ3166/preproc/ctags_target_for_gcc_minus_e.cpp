# 1 "c:\\Users\\leona\\OneDrive\\Documentos\\Arduino\\generated_examples\\BareMinimum_1\\BareMinimum.ino"
# 1 "c:\\Users\\leona\\OneDrive\\Documentos\\Arduino\\generated_examples\\BareMinimum_1\\BareMinimum.ino"
# 2 "c:\\Users\\leona\\OneDrive\\Documentos\\Arduino\\generated_examples\\BareMinimum_1\\BareMinimum.ino" 2
# 3 "c:\\Users\\leona\\OneDrive\\Documentos\\Arduino\\generated_examples\\BareMinimum_1\\BareMinimum.ino" 2
# 4 "c:\\Users\\leona\\OneDrive\\Documentos\\Arduino\\generated_examples\\BareMinimum_1\\BareMinimum.ino" 2


# 5 "c:\\Users\\leona\\OneDrive\\Documentos\\Arduino\\generated_examples\\BareMinimum_1\\BareMinimum.ino"
HTS221Sensor *sensor;
DevI2C *i2c;
float tempC;
float tempF;
float humidity;
// string message;
char buffer[99];

void setup()
{
    // put your setup code here, to run once:
    Screen.init();
    i2c = new DevI2C(D14, D15);
    sensor = new HTS221Sensor(*i2c);
    sensor->init(
# 19 "c:\\Users\\leona\\OneDrive\\Documentos\\Arduino\\generated_examples\\BareMinimum_1\\BareMinimum.ino" 3 4
                __null
# 19 "c:\\Users\\leona\\OneDrive\\Documentos\\Arduino\\generated_examples\\BareMinimum_1\\BareMinimum.ino"
                    );
}

void loop()
{
    // put your main code here, to run repeatedly:
    Screen.print("Hello MXChip!!");
}
