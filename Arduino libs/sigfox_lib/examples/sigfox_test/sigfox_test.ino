#include <Sigfox.h>


/* 
 *  Constructor that creates object sgf using Sigfox library
 *  7 stands for rx pin
 *  8 stands for tx pin
 *  19200 is baudrate
 *  
 */
Sigfox sgf(7, 8, 19200);


void setup() {
  
  Serial.begin(19200);
}

void loop() {
  /*
  * 
  * Callings of methods from libraries
  * outputs are printed out to the serial inteface
  * 
  * 
  */
  
  Serial.print(String(sgf.getTemperature()));
  Serial.print("\n");
  delay(5000);
  Serial.print(String(sgf.getVoltage()));
  Serial.print("\n");
  delay(5000);
  Serial.print(String(sgf.getSignalRSSI()));
  Serial.print("\n");
  delay(5000);
  Serial.print(String(sgf.getTemperature()));
  Serial.print("\n");
  delay(5000);
  Serial.print(String(sgf.getVoltage()));
  Serial.print("\n");
  delay(5000);
  Serial.print(String(sgf.getSignalRSSI()));
  Serial.print("\n");
  delay(50000);
}
