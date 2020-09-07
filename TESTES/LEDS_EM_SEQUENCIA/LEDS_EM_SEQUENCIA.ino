int led = 7;
int leda = 8;
int ledb = 9;
int ledc = 10;
int ledd = 13;

void setup() {

pinMode(led, OUTPUT);
pinMode(leda, OUTPUT);
pinMode(ledb, OUTPUT);
pinMode(ledc, OUTPUT); 
pinMode(ledd, OUTPUT);
}
void loop() {
// o led fica aceso durante o tempo de delay e apaga
digitalWrite(leda, HIGH);   
delay(1000);             
digitalWrite(leda, LOW);   
digitalWrite(ledb, HIGH);   
delay(1000);             
digitalWrite(ledb, LOW);   
digitalWrite(ledc, HIGH);   
delay(1000);             
digitalWrite(ledc, LOW);   
digitalWrite(ledd, HIGH);   
delay(1000);             
digitalWrite(ledd, LOW);   

delay(1000);              

}
