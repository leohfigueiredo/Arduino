
int S1=8;
int S0=9;


int estate=1;
int clk= 2;
int x=3;


void setup() {

  pinMode(S1, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(clk, INPUT);
  
  }

void loop() {

  if (digitalRead(clk)==HIGH){
      switch(estate){
        
  case 1:
  
        if(digitalRead(x)==HIGH){
          digitalWrite(S0,LOW);
          digitalWrite(S1,LOW);

          estate = 4;
          
        }else{
          digitalWrite(S0,HIGH);
          digitalWrite(S1,HIGH);

    estate=1;  
        }
        break;

   case 2:
        if (digitalRead(x)==HIGH){

         digitalWrite(S0,HIGH);
         digitalWrite(S1,LOW);
     estate = 2;
      }
      else{
          digitalWrite(S0,LOW);
          digitalWrite(S1,LOW);
     estate = 4;
        }
        break;

  case 3:
         if (digitalRead(x)==HIGH){

         digitalWrite(S0,LOW);
         digitalWrite(S1,HIGH);

          estate = 3;
      }
      else {
         digitalWrite(S0,LOW);
         digitalWrite(S1,LOW);

          estate = 4;
        }
        break;
  case 4:
         if (digitalRead(x)==HIGH){

         digitalWrite(S0,LOW);
         digitalWrite(S1,LOW);

          estate = 4;
      }
      else {
          
        digitalWrite(S0,HIGH);
        digitalWrite(S1,HIGH);


          estate = 1;
        }
        break;

  }
  delay(1000);
  }
 else if (digitalRead(x)==LOW){

         digitalWrite(S0,LOW);
         digitalWrite(S1,LOW);


 }
}
