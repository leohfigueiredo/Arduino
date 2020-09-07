// Ponto 
int dp = 5;
 
// Segmentos
int a = 2;
int b = 4;
int c = 10;
int d = 9;
int e = 8;
int f = 3;
int g = 6;
 
// Digitos
int ls1 = 11;
int ls2 = 7;
int ls3 = 12;
int ls4 = 1;
 
int uno=0;
int t=0;
int dos=0;
int tres=0;
int cuatro=0;
int currentMillis = 0;
 
int buttonState = 0;
 
byte pin_order[7] = { a,b,c,d,e,f,g };
byte digit_order[4] = { ls1,ls2,ls3,ls4 };
byte digitos[4][4] = { { 0,0,0,1 },
                      { 0,0,1,0 },
                      { 0,1,0,0 },
                      { 1,0,0,0 }
                    };
 
//-----------------------------------------------------------------
// Formato do array é a ordem de segmentos:   a,b,c,d,e,f,g
//-----------------------------------------------------------------
byte seven_seg_digits[10][7] = { { 0,0,0,0,0,0,1 },  // = 0
                                 { 1,0,0,1,1,1,1 },  // = 1
                                 { 0,0,1,0,0,1,0 },  // = 2
                                 { 0,0,0,0,1,1,0 },  // = 3
                                 { 1,0,0,1,1,0,0 },  // = 4
                                 { 0,1,0,0,1,0,0 },  // = 5
                                 { 0,1,0,0,0,0,0 },  // = 6
                                 { 0,0,0,1,1,1,1 },  // = 7
                                 { 0,0,0,0,0,0,0 },  // = 8
                                 { 0,0,0,1,1,0,0 }   // = 9
                               };
 
//---------------------------------------------------------------------
// Escreve um determinado numero (number) no digito (digit) informado
// OBS: Se number = 200 então vai desligar completamente o digito
void digWrite(byte digit, byte number) {
  int pinseq = 0;
 
  pickDigit(digit);
 
  writeDot(1);
 
  if (number == 200)
  {
    for (byte segCount = 0; segCount < 7; ++segCount) 
    {
      digitalWrite(pin_order[pinseq], 0);
      ++pinseq;
    }
    return;
  }
 
  for (byte segCount = 0; segCount < 7; ++segCount) 
  {
    digitalWrite(pin_order[pinseq], seven_seg_digits[number][segCount]);
    ++pinseq;
  }
}
 
//---------------------------------------------------------------------
// Ativa um determinado digito do componente
void pickDigit(int x)
{
  digitalWrite(ls1, LOW);
  digitalWrite(ls2, LOW);
  digitalWrite(ls3, LOW);
  digitalWrite(ls4, LOW);
 
  switch(x)
  {
    case 1: 
      digitalWrite(ls1, HIGH); // colocando HIGH no pino, estamos habilitando o acendimento dos segmento
      break;
    case 2: 
      digitalWrite(ls2, HIGH); 
      break;
    case 3: 
      digitalWrite(ls3, HIGH); 
      break;
    default: 
      digitalWrite(ls4, HIGH); 
      break;
  }
}
 
void writeDot(byte dot) {
  digitalWrite(dp, dot);
}
 
void setup()
{
  int i;
 
  for(i=1; i <= 12;i++)     
     pinMode(i,OUTPUT);
 
  pinMode(A5, INPUT);
}
 
   int d1 = 0;
   int d2 = 0;
   int d3 = 0;
   int d4 = 0;
 
 void loop()
{
    buttonState = digitalRead(A5);
    if (buttonState == HIGH)
    {
       uno=0;
       dos=0;
       tres=0;
       cuatro=0;
   }
 
   if( currentMillis >= 10000)
   {
    currentMillis = 0;
    dos++;
        if(dos >= 6)
        {
            dos=0;
            tres++;
                if(tres >= 10)
                {
                    tres=0;
                    cuatro++;
                    if (cuatro >= 6)
                    {
                        uno=0;
                        dos=0;
                        tres=0;
                        cuatro=0;
                    }
                }
        }
 }
 
  uno=(currentMillis)/1000;
 
  digWrite(4, uno);
  delay(5); 
 
  digWrite(3, dos);
  delay(5); 
 
  digWrite(2, tres);
  delay(5); 
 
  digWrite(1, cuatro);
  delay(5);
 
  currentMillis = currentMillis + 20; // 20 = sum of each delay above
}
