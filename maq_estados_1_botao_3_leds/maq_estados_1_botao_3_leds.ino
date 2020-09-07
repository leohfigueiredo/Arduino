int S3=11;
int S2=10;
int S1=9;
int S0=8;


int estate=1;
int clk= 2;
int x=3;


void setup() {
  pinMode(S3, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(clk, INPUT);
  
  }

void loop() {

  if (digitalRead(clk)==HIGH){
      switch(estate){
        case 1:
        if(digitalRead(x)==HIGH){
          digitalWrite(S0,HIGH);
          digitalWrite(S1,LOW);
          digitalWrite(S2,LOW);

          estate = 2;
          
        }else{
          digitalWrite(S0,LOW);
          digitalWrite(S1,LOW);
          digitalWrite(S2,HIGH);
    estate=4;  
        }
        break;

        case 2:
        if (digitalRead(x)==HIGH){

         digitalWrite(S0,LOW);

          digitalWrite(S1,HIGH);
          digitalWrite(S2,LOW);

          estate = 3;
      }
      else{
                digitalWrite(S0,HIGH);

          digitalWrite(S1,LOW);
          digitalWrite(S2,LOW);

          estate = 1;
        }
        break;

        case 3:
                if (digitalRead(x)==HIGH){

         digitalWrite(S0,HIGH);

          digitalWrite(S1,HIGH);
          digitalWrite(S2,LOW);

          estate = 4;
      }
      else {
          

         digitalWrite(S0,LOW);

          digitalWrite(S1,HIGH);
          digitalWrite(S2,LOW);

          estate = 2;
        }
        break;
  case 4:
         if (digitalRead(x)==HIGH){

         digitalWrite(S0,LOW);

          digitalWrite(S1,LOW);
          digitalWrite(S2,HIGH);

          estate = 1;
      }
      else {
          

         digitalWrite(S0,HIGH);

          digitalWrite(S1,HIGH);
          digitalWrite(S2,LOW);

          estate = 3;
        }
        break;

  }
  delay(1000);
  }
 else if (digitalRead(x)==HIGH){

         digitalWrite(S0,LOW);

          digitalWrite(S1,LOW);
          digitalWrite(S2,LOW);

 }
}
