boolean start = true;
volatile boolean e_stop = false;

void setup() {
Serial.begin(9600);
delay(100);


attachInterrupt(0,e_stop_ISR, RISING);

}

void loop() {
 if(start == true){


    if(e_stop == false){
Serial.println("tudo ok");
delay(300);
    }
    else{

Serial.println("EMERGENCIA!!!! RESETAR ARDUINO");
      
    }  
    }
}
void e_stop_ISR(void){
  detachInterrupt(0);
  e_stop = !e_stop;
}

