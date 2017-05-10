#include <SoftwareSerial.h>
 
SoftwareSerial DEBUG(7, 8);
 
char c, s;
void setup()
{
  Serial.begin(300, SERIAL_7E1);
  DEBUG.begin(19200);
  delay(500);
  Serial.print('/');
  Serial.print('?');
  Serial.print('!');
  Serial.print(0x0D); // CR
  Serial.print(0x0A); // LF
 

}

void loop()
{
  if (Serial.available() > 0)
  {
    c = Serial.read();
    DEBUG.print(c);
    //delay(0);

  }
  if (DEBUG.available() > 0)
  {
    s = DEBUG.read();
    //delay(0);
    Serial.print(s);
  }
}
