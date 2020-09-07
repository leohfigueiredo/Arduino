const int porta_rele1 =7;
const int porta_rele2 =8;
const int porta_rele3 =9;
const int porta_rele4 =10;


void setup(){
pinMode(porta_rele1,OUTPUT);
pinMode(porta_rele2,OUTPUT);
pinMode(porta_rele3,OUTPUT);
pinMode(porta_rele4,OUTPUT);

}
void loop()
{
pisca(porta_rele1,1000,2000,0);
int porta_rele1 = LOW;
pisca(porta_rele2,1500,3000,0);
pisca(porta_rele3,3500,5000,0);
pisca(porta_rele4,5500,7000,0);


}
void pisca(int pin, int timeOn, int timeOff, int atraso){
int resto = (millis()-atraso)%(timeOn + timeOff);
digitalWrite(pin, resto<timeOn ? HIGH : LOW);
}
