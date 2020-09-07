/*
 * Integrando Arduino com Excel
 * 
 * arduinovacao.blogspot.com.br
 * By: Diego Santos
 * 
 * 05/08/2016
 */

int x = 0;
int linha = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("CLEARDATA");
    Serial.println("LABEL, Data, Hora, x, Sen(x), Cos(x)");
}

void loop() {
    Serial.print("DATA, DATE, TIME,");
    Serial.print(x);
    Serial.print(",");
    Serial.print(sin(x * PI / 180));
    Serial.print(x);
    Serial.print(",");
    Serial.println(cos(x * PI / 180));

    linha++;
    x++;  
    
    if (linha > 360) {
        linha = 0;
        Serial.println("ROW,SET,2");
    }
    delay(100);
}

