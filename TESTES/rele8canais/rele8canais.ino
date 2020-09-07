#include "Wire.h"

#define I2C_ADDR  0x20  // 0x20 is the address with all jumpers removed

void setup()
{
  Serial.begin( 38400 );
  Serial.println("RELAY8 demonstration starting up");

  Wire.begin(); // Wake up I2C bus

  // Set I/O bank A to outputs
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x00); // IODIRA register
  Wire.write(0x00); // Set all of bank A to outputs
  Wire.endTransmission();
  
  Serial.println("Ready. Type 0 to turn off relays, 1 - 8 to activate a relay.");
}

void loop()
{
   int command = 0;
   if (Serial.available()) {
    command = Serial.read();
    if( command == '0' )
    {
      sendValueToLatch(0);
      Serial.println("Resetting all relays");
    }
    if( command == '1' )
    {
      sendValueToLatch(1);
      Serial.println("Activating relay 1");
    }
    if( command == '2' )
    {
      sendValueToLatch(2);
      Serial.println("Activating relay 2");
    }
    if( command == '3' )
    {
      sendValueToLatch(4);
      Serial.println("Activating relay 3");
    }
    if( command == '4' )
    {
      sendValueToLatch(8);
      Serial.println("Activating relay 4");
    }
    if( command == '5' )
    {
      sendValueToLatch(16);
      Serial.println("Activating relay 5");
    }
    if( command == '6' )
    {
      sendValueToLatch(32);
      Serial.println("Activating relay 6");
    }
    if( command == '7' )
    {
      sendValueToLatch(64);
      Serial.println("Activating relay 7");
    }
    if( command == '8' )
    {
      sendValueToLatch(128);
      Serial.println("Activating relay 8");
    }
  }
}

void sendValueToLatch(int latchValue)
{
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(0x12);        // Select GPIOA
  Wire.write(latchValue);  // Send value to bank A
  Wire.endTransmission();
}
