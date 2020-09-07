#define led1 10
#define led2 9
#define led3 8
#define button 2

unsigned long StartTimePress = 0;
unsigned long LastTimePress = 0;
int ButonDown = 0;

void setup() {
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(led3, OUTPUT);
pinMode(button, INPUT);
digitalWrite(button, HIGH);
}
void loop()
{
if (digitalRead(button) == 0 && ButonDown == 0) {
StartTimePress = millis();
ButonDown = 1;
}
if (digitalRead(button) == 1 && ButonDown == 1) {
LastTimePress = millis() - StartTimePress;
if (LastTimePress < 3000 && LastTimePress > 100) {
digitalWrite(led1, 1);
} else if ( LastTimePress < 5000 && LastTimePress > 100) {
digitalWrite(led2, 1);
} else if ( LastTimePress > 100) {
digitalWrite(led3, 1);
}
ButonDown = 0;
}
}
