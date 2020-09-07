//escravo
int recByte;
int led = 13;

void setup(){
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}

void loop(){
 if(Serial.available() > 0){
  recByte = Serial.read();
 } 
 
 if(recByte == 0){
   digitalWrite(led,LOW);
 }else if(recByte == 1){
   digitalWrite(led,HIGH);
 }
}
