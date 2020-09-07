
struct BUTTONS {
  int button;
  int led1;
  int led2;
  int led3;
  int led4;
  int curstate;
  int btnstate;
  int btntimer;
  int lbtnstate;
  int btnreading; 
};
typedef struct BUTTONS Button;

Button b1 = {3, 3, 5, 6, 0, LOW, 0 ,0 ,HIGH ,0};
Button b2 = {4, 6, 0, 0, 0, LOW, 0 ,0 ,HIGH ,0};

unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
 
    pinMode(3, INPUT);
    pinMode(4, INPUT);
   
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
}

void loop() {
    b1.btnreading= digitalRead(b1.button);
    b2.btnreading= digitalRead(b2.button);
   
    if (b1.btnreading != b1.lbtnstate) {
      Serial.print("Change1 - 1");
      b1.btntimer = millis();
      if ((millis() - b1.btntimer) > debounceDelay) {
        Serial.print("Change1 - 2");
        if (b1.btnreading != b1.btnstate) {
          Serial.print("Change1 - 3");
          b1.btnstate = b1.btnreading;
          // only toggle the LED if the new button state is HIGH
          if (b1.btnstate == LOW) {
            b1.curstate = LOW;
            Serial.println(" Just pushed b1.");
          }
        }
      }
      digitalWrite(b1.led1, b1.curstate);
      digitalWrite(b1.led2, b1.curstate);
      digitalWrite(b1.led3, b1.curstate);
      digitalWrite(b1.led4, b1.curstate);
      b1.lbtnstate = b1.btnstate;
    }
   
    if (b2.btnreading != b2.lbtnstate) {
      Serial.print("Change2 - 1");
      b2.btntimer = millis();
      if ((millis() - b2.btntimer) > debounceDelay) {
        Serial.print("Change2 - 2");
        if (b2.btnreading != b2.btnstate) {
          Serial.print("Change2 - 3");
          b2.btnstate = b2.btnreading;
          // only toggle the LED if the new button state is HIGH
          if (b2.btnstate == LOW) {
            b2.curstate = !b2.curstate;
            Serial.print(b2.curstate);
            Serial.println(" Just pushed b2");
          }
        }
      }
      digitalWrite(b2.led1, b2.curstate);
      digitalWrite(b2.led2, b2.curstate);
      digitalWrite(b2.led3, b2.curstate);
      digitalWrite(b2.led4, b2.curstate);
      b2.lbtnstate = b2.btnstate;
    }
 }

