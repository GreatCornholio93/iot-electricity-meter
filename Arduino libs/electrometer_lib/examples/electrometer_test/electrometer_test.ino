#include <electrometer.h>
#include <Sigfox.h>

#include <SoftwareSerial.h>
#include <stdlib.h>


void setup()
{

  Sigfox sgf(7,8,4800);
  Electrometer *elm = new Electrometer();
  
  sgf.getTemperature();
  sgf.sendString(String(sgf.getTemperature()));
  
  elm->sendHello();


}


void loop()
{

}
