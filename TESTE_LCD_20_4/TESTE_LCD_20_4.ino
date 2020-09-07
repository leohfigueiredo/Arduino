  

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x3F
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

void setup()
{
  // Define o LCD com 20 colunas e 4 linhas
  lcd.begin(20, 4);
  
  // Mostra informacoes no display


  lcd.setCursor(0,0);
  lcd.print("LEONARDO  FIGUEIREDO");
  lcd.setCursor(0,1);
  lcd.print("Electronic  Engineer");
    lcd.setCursor(0,2);
  lcd.print("* Looking for new  *");
  lcd.setCursor(0,3);
  lcd.print("*  Opportunities   *");
}

void loop()
{
  // Seu codigo aqui
}

