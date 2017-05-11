#ifndef electrometer_h
#define electrometer_h

#include "Arduino.h"

#define TIMEOUT 5000

class Electrometer
{
	public:
	  Electrometer();
	  int readData();
	  int getE1();
	  int getE2();
	  int getE3();
 	  void sendHello();
	  void sendRequest();
	  void readHello();
	  int readResponse();
	  int tryParseResponse();
	  long parseFromResult(String s, String OBIS);

	private:
	  int e1, e2, e3;
	  long lastTime;
	  bool isDebug;
	 
	 
};

#endif