#ifndef electrometer_h
#define electrometer_h

#include "Arduino.h"

#define TIMEOUT 5000

class Electrometer
{
	public:
	  Electrometer();
	  Electrometer(int rx, int tx, int baud);
	  int readData();
	  int getE1();
	  int getE2();
	  int getE3();

	private:
	  int e1, e2, e3;
	  long lastTime;
	  bool isDebug;
	  void sendHello();
	  void sendRequest();
	  void readHello();
	  int readResponse();
	  int tryParseResponse();
	  String parseFromResult(String s, String OBIS);
};

#endif