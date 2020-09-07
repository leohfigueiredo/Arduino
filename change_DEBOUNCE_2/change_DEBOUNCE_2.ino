

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

#define BUTTON_PIN1 4
#define LED_PIN1 9

#define BUTTON_PIN2 5

int ledState = HIGH; // estado inicial das saídas
int ledState1 = HIGH;
int i;

byte letraE[8] = { 
0b00000, // vetor de bytes correspondentes
0b01110,  // ao desenho do E
0b01000,
0b01110,
0b01000,
0b01110,
0b00000,
0b00000
};
byte letraT[8] = { 
0b00000, // vetor de bytes correspondentes
0b11111,  // ao desenho do T
0b00100,
0b00100,
0b00100,
0b00100,
0b00000,
0b00000
};
byte letraO[8] = { 
0b00000, // vetor de bytes correspondentes
0b01110,  // ao desenho do O
0b01010,
0b01010,
0b01010,
0b01110,
0b00000,
0b00000
};


// Instantiate a Bounce object :
Bounce debouncer = Bounce();
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 


void setup() {

 Serial.begin(9600);    //inicialização da porta serial
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
   
lcd.createChar(1, letraE); // envia nosso character p/ o display
lcd.createChar(2, letraT); // envia nosso character p/ o display
lcd.createChar(3, letraO); // envia nosso character p/ o display

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

  lcd.clear();
lcd.setCursor(3,1);
lcd.write(1); // desenha o E
 // 
  lcd.clear();
lcd.setCursor(3,1);
lcd.write(2); // desenha o E
 // 
  lcd.clear();
lcd.setCursor(3,1);
lcd.write(3); // desenha o E
// 


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

}

void loop() {

  if(start == true){


    if(e_stop == false){
Serial.println("tudo ok");
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

void e_stop_ISR(void){
  detachInterrupt(0);
  e_stop = !e_stop;

}
