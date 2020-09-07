int btnPin = 2;
int led = 13;
int soundTime = 1200; // this the sound time each time button pressed 

int SPEAKER = 12;    // The speaker is on pin 12


unsigned long mainTimer = 0; // "ALWAYS use unsigned long..."
unsigned long ledTimer = 0;
boolean setMode = false;  

void setup() {
  pinMode(btnPin, INPUT); // d2 digital INPUT => BUTTON
  pinMode(led, OUTPUT); // d13 digital OUTPUT => LED
    pinMode(SPEAKER, OUTPUT);// d12 SPEAKER OUTPUT =>  sound  

}

void loop() {
  
  

  
  // check mainTimer and set setMode
  if ((millis() - mainTimer) >= 200UL) {
    if ((digitalRead(btnPin) == HIGH)) {
      if (setMode == false) {
        setMode = true;
              
              
              
              
              for (int i=0; i <= soundTime; i++){
          digitalWrite(SPEAKER, HIGH);

               } 
              
              

              
              

              
              
        ledTimer = millis();
      }
      else if (setMode == true) {
        setMode = false;

              
              for (int i=0; i <= soundTime; i++){
          digitalWrite(SPEAKER, HIGH);

               } 
              
              

      }
      mainTimer = millis();
    }
  }

  // LED on/off with ledTimer 
  if (setMode == true) {
      

      
    if ((millis() - ledTimer) <= (1024UL )) {
      digitalWrite(led, HIGH); 
          
                 
                digitalWrite(SPEAKER, LOW);



          
         
          
          
          
               }
      

    else if ((millis() - ledTimer) <= 2*(1024UL )) {
      digitalWrite(led, LOW);
          
          
                digitalWrite(SPEAKER, LOW);

           
           

    }
    else {
      ledTimer = millis();
    }
  }
  else {
    digitalWrite(led, LOW);
      
                digitalWrite(SPEAKER, LOW);

      
      
      


        

  }
}
