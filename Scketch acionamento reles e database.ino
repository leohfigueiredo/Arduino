
#include <TimeLib.h>

#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"


#include <Adafruit_Sensor.h>


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN            A5         // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT11 
DHT dht(DHTPIN, DHTTYPE);

// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11     // DHT 11 

#include <Time.h>
#include <DS1302RTC.h>

// Set pins:  CE, IO,CLK
DS1302RTC RTC(31, 33, 35); // no MEGA, no UNO, deve-se alterar

boolean start = true;             //variáveis de interrupção de emergência
volatile boolean e_stop = false;


int ledPin = 13; //led da musica
//led for visualization (use 13 for built-in led)

int speakerPin = 7; //speaker connected to one of the PWM ports

// the last 10 reads if power is lost but it uses less power and is much faster!
#define SYNC_INTERVAL 1500 // mills between calls to flush() - to write data to the card
uint32_t syncTime = 0; // time of last sync()

#define ECHO_TO_SERIAL 1 // echo data to serial port - DADOS PARA O SD CARD
#define WAIT_TO_START 0 // Wait for serial input in setup() - AGUARDANDO ENTRADA BOTAO PARA LOG

#define c 261       //declaração das frequencias das notas musicais
#define d 294
#define e 329
#define f 349
#define g 391
#define a 440
#define b 466


#define entradaChave1  3 // Set up chave SW
#define entradaChave2  5 // Set up chave SW
int entradaChave = 2; // Set up chave SW
int estadoChave = HIGH;
int estadoChave2 = HIGH;
int val = 0;
int val2 = 0;

int relay6M = 6; //Set up Pino Relay
int relay8M = 8; //Set up Pino Relay
 

int i; // contador para efeito do LCD 

const int chipSelect = 4; // chipselect do arduino MEGA, se for UNO, deve alterar ***** NAO USAR ESTE PINO PARA NADA
// the logging file
File logfile; // preparação para log de informações 

void error(char *str)
{
Serial.print("error: ");
Serial.println(str);
// red LED indicates error
while(1);
}

void setup(void)
{
Serial.begin(9600);
 lcd.begin (20,4);      //inicialização do display LCD 20 x 4



  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  lcd.setCursor(0,1);
  lcd.print("PROCESSO         ETO");
  lcd.setCursor(0,2);
  lcd.print("    INICIALIZADO    ");
  lcd.setCursor(0,3);
  lcd.print("--****************--");
   delay(500);

  //Faz o efeito de deslocamento para esquerda   
  for (i =0; i <20; i++){     
  lcd.scrollDisplayLeft();     
  delay(20);   }
  delay(1000); 
  //Faz o efeito de deslocamento para esquerda   
  for (i =0; i <20; i++){     
  lcd.scrollDisplayLeft();     
  delay(20);   }
  delay(1000); 
    //Faz o efeito de deslocamento para direita  
  for (i =0; i <20; i++){     
  lcd.scrollDisplayRight();     
  delay(20);   }
  delay(1000); 
      //Faz o efeito de deslocamento para direita   
  for (i =0; i <20; i++){     
  lcd.scrollDisplayRight();     
  delay(20);   }
  delay(1000); 

attachInterrupt(5,e_stop_ISR, RISING); //setando interrupção na subida da mudança de estado do botão interrupçao pino 18 - set 5 ***** NAO USAR ESTE PINO PARA NADA 

pinMode(entradaChave, INPUT);
pinMode(relay6M, OUTPUT);
pinMode(entradaChave2, INPUT);
pinMode(relay8M, OUTPUT);
pinMode(entradaChave1, INPUT);
pinMode(speakerPin, OUTPUT); 


musicaentrada();  // som de inicio - - puxar o void do beep para tocar a musica de inicio

    pinMode(10, OUTPUT); // para o mega funcionar com o Ethernet, necessario desligar o chip enable padrão, na porta 10
    digitalWrite(10, HIGH);  // desligando a porta 10, sem isto o shield ethernet nao funciona no arduino MEGA

    // use debugging LEDs
#if WAIT_TO_START
Serial.println("Type any character to start");
while (!Serial.available());
#endif //WAIT_TO_START

// initialize the SD card
Serial.print("Initializing SD card...");

// make sure that the default chip select pin is set to
// output, even if you don't use it:
pinMode(10, OUTPUT);

// see if the card is present and can be initialized:
if (!SD.begin(chipSelect)) {
error("La tarjeta de memoria falló o no está presente");
}
Serial.println("Tarjeta de memoria inicializada");
// create a new file
char filename[] = "LOGGER00.CSV";

for (uint8_t i = 0; i < 100; i++) {
  filename[6] = i/10 + '0';
  filename[7] = i%10 + '0';

if (! SD.exists(filename)) {
// only open a new file if it doesn't exist
logfile = SD.open(filename, FILE_WRITE);
break; // leave the loop!
}
}
if (! logfile) {
error("No podría crear el archivo");
}
Serial.print("Logging to: ");
Serial.println(filename);
// connect to RTC
Wire.begin();
if (!RTC.writeEN()) { //lê o estado do RTC - relógio
logfile.println("RTC failed");
#if ECHO_TO_SERIAL
Serial.println("RTC failed");
#endif //ECHO_TO_SERIAL
}
logfile.println("millis,stamp,data e hora,temperatura(Celsius),Humidad(%),status");
#if ECHO_TO_SERIAL
Serial.println("millis,stamp,data e hora,temperatura(Celsius),Humidad(%),status");
#endif //ECHO_TO_SERIAL



}

void loop() {
 
  //  /////////////////////////////////////////
  if(start == true){
    if(e_stop == false){

val = digitalRead(entradaChave1); // read input value
val2 = digitalRead(entradaChave2); // read input value


if (val == HIGH) { // check if the input is HIGH
digitalWrite(relay6M, HIGH); // turn Relay ON

delay(150);
if (estadoChave == LOW) {
// we have just turned on
logData();
Serial.print(", ");
Serial.println("MOTOR 3 EN MARCHA!");
logfile.print(", ");
logfile.println("MOTOR 3 EN MARCHA!");
logfile.flush();
 lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES"); 
  lcd.setCursor(6,1);
  lcd.print("MOTOR 3");
  lcd.setCursor(6,2);
  lcd.print("EN MARCHA");
  delay(500);

estadoChave = HIGH;
}
} 
else {
digitalWrite(relay6M, LOW); // turn Relay OFF
delay(150);
if (estadoChave == HIGH) {
  logData();
  Serial.print(", ");
Serial.println("MOTOR 3 PARADO!");
logfile.print(", ");
logfile.println("MOTOR 3 PARADO!");
logfile.flush();
 lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  lcd.setCursor(6,1);
  lcd.print("MOTOR 3");
  lcd.setCursor(6,2);
  lcd.print("PARADO");
   delay(500);

estadoChave = LOW;
}
}


if (val2 == HIGH) { // check if the input is HIGH
digitalWrite(relay8M, HIGH); // turn Relay ON
delay(150);
if (estadoChave2 == LOW) {
// we have just turned on
logData();
Serial.print(", ");
Serial.println("MOTOR 4 EN MARCHA!");
logfile.print(", ");
logfile.println("MOTOR 4 EN MARCHA!");
logfile.flush();
 lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");  
  lcd.setCursor(6,1);
  lcd.print("MOTOR 4");
  lcd.setCursor(6,2);
  lcd.print("EN MARCHA");
   delay(500);

estadoChave2 = HIGH;
}
} 
else {
digitalWrite(relay8M, LOW); // turn Relay OFF
delay(150);
if (estadoChave2 == HIGH) {
  logData();
  Serial.print(", ");
Serial.println("MOTOR 4 PARADO!");
logfile.print(", ");
logfile.println("MOTOR 4 PARADO!");
logfile.flush();
 lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  lcd.setCursor(6,1);
  lcd.print("MOTOR 4");
  lcd.setCursor(6,2);
  lcd.print("PARADO");
   delay(500);

estadoChave2 = LOW;
}
if (estadoChave2 == LOW && estadoChave == LOW){

lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  lcd.setCursor(3,1);
  lcd.print("MOTORES PARADOS");
  lcd.setCursor(3,2);
  lcd.print("AGUARDANDO LIGAR");
   delay(500);

}

}
    
}
    
    else{
  logData();
  Serial.print(", ");
Serial.println("MOTORES PARADOS");
  logfile.print(", ");
logfile.flush();
digitalWrite (relay6M, HIGH); // envia saida para nivel alto ----- desliga os relés
digitalWrite (relay8M, HIGH); // envia saida para nivel alto

alarme();
  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  lcd.setCursor(3,1);
  lcd.print("MOTORES 3 E 4 ");
  lcd.setCursor(6,2);
  lcd.print("PARADOS");
  lcd.setCursor(3,3);
  lcd.print("AGUARDANDO RESET");
  while(1);
  
    }
    }
}


    void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds)   //void para tocar a musica
{ 
    digitalWrite(ledPin, HIGH);   
    //use led to visualize the notes being played
    
    int x;   
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++)   
    {    
        digitalWrite(speakerPin,HIGH);
        delayMicroseconds(delayAmount);
        digitalWrite(speakerPin,LOW);
        delayMicroseconds(delayAmount);
    }    
    
    digitalWrite(ledPin, LOW);
    //set led back to low
    
    delay(20);
    //a little delay to make all notes sound separate
}    
     
void musicaentrada()  //void da musica de entrada do programa
{    
    beep(speakerPin, c, 700); 
    beep(speakerPin, c, 700);     
    beep(speakerPin, c, 700); 
    beep(speakerPin, f, 300); 
    beep(speakerPin, f, 300);
    
}

void alarme()   // void de som do alarme 
{    
    beep(speakerPin, a, 500); 
    beep(speakerPin, a, 500);     
    beep(speakerPin, a, 500); 
    beep(speakerPin, a, 500); 
    beep(speakerPin, a, 500);
    beep(speakerPin, a, 500);
    beep(speakerPin, a, 500);

}

void logData(){ // void para armazenamento da informaçao no cartao de memoria
  dht.begin();
  float h = dht.readHumidity();  // leitura da humidade, sendo h a variavel utilizada

  float t = dht.readTemperature();  // leitura da temperatura, sendo t a variavel
  
DateTime now;
// log milliseconds since starting
uint32_t m = millis();
logfile.print(m); // milliseconds since start
logfile.print(", ");

#if ECHO_TO_SERIAL
Serial.print(m); // milliseconds since start
Serial.print(", ");
#endif
now = RTC.get(); // o get é da biblioteca do RTC 1302, pega o horário atual
// log time
logfile.print(now.unixtime()); // seconds since 1/1/1970
logfile.print(", ");
logfile.print('"');
logfile.print(now.year(), DEC);
logfile.print("/");
logfile.print(now.month(), DEC);
logfile.print("/");
logfile.print(now.day(), DEC);
logfile.print(" ");
logfile.print(now.hour(), DEC);
logfile.print(":");
logfile.print(now.minute(), DEC);
logfile.print(":");
logfile.print(now.second(), DEC);
logfile.print('"');
logfile.print(", ");
logfile.print(t);
logfile.print(", ");
logfile.print(h);
logfile.flush();
#if ECHO_TO_SERIAL
Serial.print(now.unixtime()); // seconds since 1/1/1970
Serial.print(", ");
Serial.print('"');
Serial.print(now.year(), DEC);
Serial.print("/");
Serial.print(now.month(), DEC);
Serial.print("/");
Serial.print(now.day(), DEC);
Serial.print(" ");
Serial.print(now.hour(), DEC);
Serial.print(":");
Serial.print(now.minute(), DEC);
Serial.print(":");
Serial.print(now.second(), DEC);
Serial.print('"');
Serial.print(", ");
Serial.print(t);
Serial.print(", ");
Serial.print(h);
#endif //ECHO_TO_SERIAL
}


void e_stop_ISR(void){  // void da interrupcao
  detachInterrupt(5);  // 5 é a interrupcao no pino 18, para interrupcao em outro pino, deve verificar as interrupcoes no arduino MEGA
  e_stop = !e_stop;

}

