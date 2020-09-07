//mestre  
int num = 0;

void setup(){
 Serial.begin(9600);
}

void loop(){
  num = 0;
  Serial.write(num);
  delay(2000);
  
  num = 1;
  Serial.write(num);
  delay(2000);
}
