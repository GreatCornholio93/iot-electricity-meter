#ifndef sigfox_h
#define sigfox_h

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <stdlib.h>

#define TIMEOUT 32000

class Sigfox
{
	public:
	  Sigfox();
	  Sigfox(int rx, int tx, int baud);
	  int getTemperature();
	  int getSignalRSSI();
	  int getSignalQuality();
	  void sendString(String string);
	  float getVoltage();
	  char intToString (int inputNumber);
	  void parse_int_to_12bytes(unsigned char *bytes, unsigned long a, unsigned long b, unsigned long c);
	  void sendBytes(unsigned char *bytes);

	private:
	SoftwareSerial *SIGFOX;
	int d;
  	int counter;
	  
};
#endif