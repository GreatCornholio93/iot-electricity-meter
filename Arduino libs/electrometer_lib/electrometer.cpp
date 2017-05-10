#include "Arduino.h"
#include "electrometer.h"
#include <SoftwareSerial.h>

Electrometer::Electrometer()
{
	e1 = 0;
	e2 = 0;
	e3 = 0;
	isDebug = false;
	Serial.begin(300, SERIAL_7E1);
}

Electrometer::Electrometer(int rx, int tx, int baud)
{
	e1 = 0;
	e2 = 0;
	e3 = 0;
	isDebug = true;

	SoftwareSerial DEBUG(rx, tx);
	DEBUG.begin(baud);
	DEBUG.println("Starting debug serial interface");
	Serial.begin(300, SERIAL_7E1);
}

int Electrometer::readData()
{
	sendHello();
	readHello();

	sendRequest();
	return readResponse();
}

void Electrometer::sendHello()
{
	if (isDebug)
		DEBUG.println("Sending hello");
	// send hello message /?! RC LF
	Serial.print("/?!\r\n");
}

// read answer to the hello message - usually ID or ID and DATA
void Electrometer::readHello()
{
	lastTime = millis();
	char c;
	String data = "";

	if (isDebug)
		DEBUG.print(c);

	bool lfWaiting = false;

	while ((lastTime + TIMEOUT) > millis())
	{
		if (Serial.available() > 0)
		{
			c = Serial.read();
			data += c;

			if (c == 0x0D) // CR detection
			{
				lfWaiting = true;
			}
			if (c == 0x0A) // LF detection
			{
				// TODO pokud je elektrometr v rezimu A nebo B, tak vrati okamzite vsechny data, asi by bylo sluste to tady nejak osetrit
				// tryParseHello(); // for cases when electrometer is in A or B mode
				break;
			}
		}
	}
}

void Electrometer::sendRequest()
{  
	if (isDebug)
		DEBUG.println("Send data request");
	// send data request [ACK]000 CR LF
	byte message[] = {0x06, 0x30, 0x30, 0x30, 0x0d, 0x0a};
    Serial.write(message, sizeof(message));
}

String Electrometer::parseFromResult(String s, String OBIS)
{
   char *str = s.c_str();
   char *result = strstr(str, OBIS);
   int position = result - str;
   int substringLength = strlen(str) - position;
   String s = s.substring(position+4,position + 20);

   //get index of (
   char *tast = s.c_str();
   char *result2 = strstr(tast, "(");
   int position2 = result2 - tast;

   //get index of )
   char *result3 = strstr(tast, ")");
   int position3 = result3 - tast;

   String parsed = s.substring(position2+1,position3);
    
   return parsed;
}

// read data response from electrometer and try parse
// parsed values save to variable e1, e2, e3
// return: x if parse successful y if not
int Electrometer::readResponse()
{
	lastTime = millis();
	char c;
	String data = "";

	if (isDebug)
		DEBUG.print(c);
	
	while ((lasttime + TIMEOUT) > millis())
	{
		if (Serial.available() > 0)
		{
			c = Serial.read();
			data += c;
		}
	}

	// return tryParseResponse(data);
	return 0;
}

int Electrometer::getE1()
{
	return e1;
}

int Electrometer::getE2()
{
	return e2;
}

int Electrometer::getE3()
{
	return e3;
}
