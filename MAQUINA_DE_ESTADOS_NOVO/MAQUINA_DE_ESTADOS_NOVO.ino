//define state names and associated integer values
int start1 100;
int RED_LED_ON 101;
int BLUE_LED_ON 102;
//assign names to possible input conditions and give them unique values
int RED_PRESS 200;
int BLUE_PRESS 201;
int NO_PRESS 202;
//assign input pins
int RED_BTN 2;
int BLUE_BTN 3;
//assign output pin numbers
int RED_OUT 8;
int BLUE_OUT 9;
//create state variable and initialize it to START state
int state = START;
//create input variable and initialize
int input = NO_PRESS;
void setup(){
pinMode(RED_BTN, INPUT);
pinMode(BLUE_BTN, INPUT);
pinMode(RED_OUT, OUTPUT);
pinMode(BLUE_OUT, OUTPUT);
digitalWrite(RED_OUT, LOW); //turn red led off to start
digitalWrite(BLUE_OUT, LOW); //turn blue led off to start
}
//begin continuous loop
void loop(){
//read inputs
if(digitalRead(RED_BTN)){
input = RED_PRESS;
delay(100); //for debouncing
}
else if(digitalRead(BLUE_BTN)){
input = BLUE_PRESS;
delay(100); //for debouncing
}
else {
input = NO_PRESS;
}
//generate appropriate outputs and evaluate state transitions
switch(state){
case START:
digitalWrite(RED_OUT, LOW); // turn red LED off
digitalWrite(BLUE_OUT, LOW); // turn blue LED off
if (input==RED_PRESS) {
state = RED_LED_ON;
}
break;
case RED_LED_ON:
digitalWrite(RED_OUT, HIGH); // turn red LED on
digitalWrite(BLUE_OUT, LOW); // turn blue LED off
if (input==BLUE_PRESS) {
state = BLUE_LED_ON;
}
break;
case BLUE_LED_ON:
digitalWrite(RED_OUT, LOW); // turn red LED off
digitalWrite(BLUE_OUT, HIGH); // turn blue LED on
if (input==RED_PRESS) {
state = RED_LED_ON;
}
break;
}
}
