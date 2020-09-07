#include <TimerOne.h>

int led1 = 7;
int led2 = 8;
int led3 = 9;
int led4 = 10;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  Timer1.initialize(500);
  Timer1.attachInterrupt(led4_cycle);
}

void led4_cycle() {
  digitalWrite(led4, HIGH);
  unsigned long inicio = millis();
  while (millis() < inicio + 45) {
    ;
  }
  digitalWrite(led4, LOW);
}

void loop() {
  digitalWrite(led1, HIGH);
  delay (15);
  digitalWrite(led1, LOW);
  delay(51);
  digitalWrite(led2, HIGH);
  delay (50);
  digitalWrite(led2, LOW);
  delay (100);
  digitalWrite(led3, HIGH);
  delay (30);
  digitalWrite(led3, LOW);
  delay(72);
}
