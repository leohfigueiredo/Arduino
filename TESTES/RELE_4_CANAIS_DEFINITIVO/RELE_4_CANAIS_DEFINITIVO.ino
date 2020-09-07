/* ===============================================================
      Project: 4 Channel 5V Relay Module
       Author: Scott C
      Created: 7th Sept 2014
  Arduino IDE: 1.0.5
      Website: http://arduinobasics.blogspot.com.au
  Description: Explore the difference between NC and NO terminals.
================================================================== */

 /* 
  Connect 5V on Arduino to VCC on Relay Module
  Connect GND on Arduino to GND on Relay Module 
  Connect GND on Arduino to the Common Terminal (middle terminal) on Relay Module. */
 
 #define CH1 8   // Connect Digital Pin 8 on Arduino to CH1 on Relay Module
 #define CH2 9   // Connect Digital Pin 8 on Arduino to CH1 on Relay Module
 #define CH3 7   // Connect Digital Pin 7 on Arduino to CH3 on Relay Module
 #define CH4 6   // Connect Digital Pin 8 on Arduino to CH1 on Relay Module
 #define LED1 4 //Connect Digital Pin 4 on Arduino to Green LED (+ 330 ohm resistor) and then to "NO" terminal on relay module
 #define LED2 12 //Connect Digital Pin 12 on Arduino to Yellow LED (+ 330 ohm resistor) and then to "NC" terminal on relay module
 #define LED3 3 //Connect Digital Pin 4 on Arduino to Green LED (+ 330 ohm resistor) and then to "NO" terminal on relay module
 #define LED4 11 //Connect Digital Pin 12 on Arduino to Yellow LED (+ 330 ohm resistor) and then to "NC" terminal on relay module


 void setup(){
   //Setup all the Arduino Pins
   pinMode(CH1, OUTPUT);
   pinMode(CH2,OUTPUT);
   pinMode(CH3, OUTPUT);
   pinMode(CH4, OUTPUT);
   pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
   pinMode(LED3, OUTPUT);
   pinMode(LED4, OUTPUT);
   
   //Provide power to both LEDs
   digitalWrite(LED1, HIGH);
   digitalWrite(LED2, HIGH);
   digitalWrite(LED3, HIGH);
   digitalWrite(LED4, HIGH);
   
   //Turn OFF any power to the Relay channels
   digitalWrite(CH1,LOW);
   digitalWrite(CH2,LOW);
   digitalWrite(CH3,LOW);
   digitalWrite(CH4,LOW);
   
   delay(2000); //Wait 2 seconds before starting sequence
 }
 
 void loop(){



   digitalWrite(CH1, HIGH);  //Green LED on, Yellow LED off
   delay(1000);
   digitalWrite(CH1, LOW);   //Yellow LED on, Green LED off
   delay(1000);
   digitalWrite(CH3, HIGH);  //Relay 3 switches to NO
   delay(1000);
   digitalWrite(CH3,LOW);    //Relay 3 switches to NC
   delay(1000);
   digitalWrite(CH3,HIGH);    //Relay 3 switches to NC
   delay(1000);



 
   digitalWrite(CH2, HIGH);  //Relay 3 switches to NO
   delay(1000);
   digitalWrite(CH2,LOW);    //Relay 3 switches to NC
   delay(1000);
   digitalWrite(CH4, HIGH);  //Relay 3 switches to NO
   delay(1000);
   digitalWrite(CH4,LOW);    //Relay 3 switches to NC
   delay(1000);
}
   
