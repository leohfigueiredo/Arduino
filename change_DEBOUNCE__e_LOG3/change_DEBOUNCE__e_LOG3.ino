#include <TimeLib.h>

#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"


#include <Adafruit_Sensor.h>

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

// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce-Arduino-Wiring

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);    //módulo I2C

boolean start = true;             //variáveis de interrupção de emergência
volatile boolean e_stop = false;

int ledPin = 13; //led da musica
//led for visualization (use 13 for built-in led)

int speakerPin = 12; //speaker connected to one of the PWM ports

// the last 10 reads if power is lost but it uses less power and is much faster!
#define SYNC_INTERVAL 1500 // mills between calls to flush() - to write data to the card
uint32_t syncTime = 0; // time of last sync()

#define ECHO_TO_SERIAL 1 // echo data to serial port - DADOS PARA O SD CARD
#define WAIT_TO_START 0 // Wait for serial input in setup() - AGUARDANDO ENTRADA BOTAO PARA LOG

#define c 261       //declaração das frequencias das notas musicais
#define c4 261.63
#define d 294
#define d4 293.66
#define d4S 311.13
#define e 329
#define e4 329.63
#define f 349
#define g 391
#define gS 415
#define a 440
#define a3 220
#define aS 455
#define b 466
#define b3 246.94
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880

#include <Bounce2.h>


#define BUTTON_PIN 3  //definição dos botoes e leds de saida de sinal
#define LED_PIN 8

#define BUTTON_PIN1 5
#define LED_PIN1 9

#define BUTTON_PIN2 6

int ledState = HIGH; // estado inicial das saídas DOS RELES
int ledState1 = HIGH; // estado inicial das saídas DOS RELES
int i;

int pirState = LOW; // we start, assuming NOTHING WITH BUTTONS
int val = 0; // variable for reading the pin status
int pirState1 = LOW; // we start, assuming NOTHING WITH BUTTONS
int val1 = 0; // variable for reading the pin status
const int chipSelect = 4; // chipselect do arduino MEGA, se for UNO, deve alterar
// the logging file
File logfile; // preparação para log de informações 

void error(char *str)
{
Serial.print("error: ");
Serial.println(str);
// red LED indicates error
while(1);
}


// Instantiate a Bounce object :
Bounce debouncer = Bounce();
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 

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

  pinMode(ledPin, OUTPUT);
  // sets the ledPin to be an output
  pinMode(speakerPin, OUTPUT);   
//sets the speakerPin to be an output

attachInterrupt(0,e_stop_ISR, RISING); //setando interrupção na subida da mudança de estado do botão


  // Setup the button with an internal pull-up :
  pinMode(BUTTON_PIN,INPUT);
  pinMode(BUTTON_PIN1,INPUT);
  pinMode(BUTTON_PIN2,INPUT);
  
  // After setting up the button, setup the Bounce instance :
  debouncer.attach(BUTTON_PIN);
  debouncer.interval(500);
  debouncer1.attach(BUTTON_PIN1);
  debouncer1.interval(500);

  debouncer2.attach(BUTTON_PIN2);
  debouncer2.interval(500);
  
  
  // Setup the LED :
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,ledState);
  pinMode(LED_PIN1,OUTPUT);
  digitalWrite(LED_PIN1,ledState1);
 
  beethoven();

  
    pinMode(10, OUTPUT); // para o mega funcionar com o Ethernet, desligar o chip enable padrão, na porta 10
    digitalWrite(10, HIGH);
    
Serial.begin(9600);
Serial.println();

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
error("Card failed, or not present");
}
Serial.println("card initialized.");
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
error("couldnt create file");
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
logfile.println("millis,stamp,datetime,temp(Celsius),Hum(%),status,");
#if ECHO_TO_SERIAL
Serial.println("millis,stamp,datetime,temp(Celsius),Hum(%),status,");
#endif //ECHO_TO_SERIAL






}
void loop(void)
{

//  /////////////////////////////////////////
  if(start == true){

    if(e_stop == false){
val = digitalRead(BUTTON_PIN); // read input value
if (val == HIGH) { // check if the input is HIGH
digitalWrite(ledPin, HIGH); // turn LED ON
if (pirState == LOW) {
// we have just turned on
logData();
Serial.print(", ");
Serial.println("MOTOR 3 EN MARCHA!");
logfile.print(", ");
logfile.println("MOTOR 3 PARADO!");
logfile.flush();
// We only want to print on the output change, not state
pirState = HIGH;
}
}
else {
digitalWrite(ledPin, LOW); // turn LED OFF
if (pirState == HIGH){
logData();
// we have just turned of
Serial.print(", ");
Serial.println("MOTOR 3 PARADO!");
logfile.print(", ");
logfile.println("MOTOR 3 PARADO!");
logfile.flush();
// We only want to print on the output change, not state
pirState = LOW;
}

val1 = digitalRead(BUTTON_PIN1); // read input value
if (val1 == HIGH) { // check if the input is HIGH
digitalWrite(ledPin, HIGH); // turn LED ON
if (pirState1 == LOW) {
// we have just turned on
logData();
Serial.print(", ");
Serial.println("MOTOR 4 EN MARCHA!");
logfile.print(", ");
logfile.println("MOTOR 4 PARADO!");
logfile.flush();
// We only want to print on the output change, not state
pirState1 = HIGH;
}
}
else {
digitalWrite(ledPin, LOW); // turn LED OFF
if (pirState1 == HIGH){
logData();
// we have just turned of
Serial.print(", ");
Serial.println("MOTOR 4 PARADO!");
logfile.print(", ");
logfile.println("MOTOR 4 PARADO!");
logfile.flush();
// We only want to print on the output change, not state
pirState1 = LOW;
}
}

    }
    }
    else{

Serial.println("EMERGENCIA!!!! RESETAR ARDUINO");
digitalWrite (LED_PIN1, HIGH); // envia saida para nivel alto
digitalWrite (LED_PIN,HIGH); // envia a saida para nivel baixo

alarme();
  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(3,0);
  lcd.print("EMERGENCIA!!!");
  lcd.setCursor(3,1);
  lcd.print("RESETAR ARDUINO");
  lcd.setCursor(5,2);
  lcd.print("!!!!!!!!!!!!!!!");
  
    }
    }


  // Update the Bounce instance :
   debouncer.update();
   debouncer1.update();
   debouncer2.update();
   
   // Call code if Bounce fell (transition from HIGH to LOW) :
   if ( debouncer.fell() ) {
   
     // Toggle LED state :
     ledState = !ledState;
     digitalWrite(LED_PIN,ledState);

  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  lcd.setCursor(6,1);
  lcd.print("MOTOR 3");
  lcd.setCursor(6,2);
  lcd.print("EN MARCHA");
   delay(500);

     
   }
   if ( debouncer1.fell() ) {
     ledState1 = !ledState1;
     digitalWrite(LED_PIN1,ledState1);

  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  lcd.setCursor(6,1);
  lcd.print("MOTOR 4");
  lcd.setCursor(6,2);
  lcd.print("EN MARCHA");
   delay(500);
   }
      if ( debouncer2.fell() ) {
     ledState = !ledState;
     digitalWrite(LED_PIN,ledState);
     ledState1 = !ledState1;
     digitalWrite(LED_PIN1,ledState1);
     
  lcd.clear();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("ETO ESTERILIZACIONES");
  lcd.setCursor(3,1);
  lcd.print("MOTORES 3 E 4");
  lcd.setCursor(6,2);
  lcd.print("EN MARCHA");
  delay(500);
     
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
     
void beethoven()
{    
    //for the sheet music see:
    //http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0016254
    //this is just a translation of said sheet music to frequencies / time in ms
    //used 500 ms for a quart note
    
    beep(speakerPin, e4, 300); 
    beep(speakerPin, d4S, 300);     
    beep(speakerPin, e4, 300); 
    beep(speakerPin, d4S, 300); 
    beep(speakerPin, e4, 300);
    
    beep(speakerPin, b3, 300);
    beep(speakerPin, d4, 300);
    beep(speakerPin, c4, 300);
    beep(speakerPin, a3, 1000);
//first bit
}
void alarme()
{    
    //for the sheet music see:
    //http://www.musicnotes.com/sheetmusic/mtd.asp?ppn=MN0016254
    //this is just a translation of said sheet music to frequencies / time in ms
    //used 500 ms for a quart note
    
    beep(speakerPin, a, 500); 
    beep(speakerPin, a, 500);     
    beep(speakerPin, a, 500); 
    beep(speakerPin, f, 350); 
    beep(speakerPin, cH, 150);
    
    beep(speakerPin, a, 500);
    beep(speakerPin, f, 350);
    beep(speakerPin, cH, 150);
    beep(speakerPin, a, 1000);

//first bit
}

void logData(){
  dht.begin();
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  
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


void e_stop_ISR(void){
  detachInterrupt(0);
  e_stop = !e_stop;

}

