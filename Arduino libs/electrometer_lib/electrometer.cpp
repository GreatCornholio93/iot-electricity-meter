#include "electrometer.h"


Electrometer::Electrometer()
{
	e1 = 0;
	e2 = 0;
	e3 = 0;
	isDebug = true;
	Serial.begin(300,SERIAL_7E1);	
	
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
	// send hello message /?! RC LF
	Serial.print("/?!\r\n");
}

// read answer to the hello message - usually ID or ID and DATA
void Electrometer::readHello()
{
	long lastTime = millis();
	char c;
	String data = "";

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

	// send data request [ACK]000 CR LF
	byte message[] = {0x06, 0x30, 0x30, 0x30, 0x0d, 0x0a};
	Serial.write(message, sizeof(message));
}

long Electrometer::parseFromResult(String s, String OBIS)
{
   char *str = s.c_str();
   char *result = strstr(str, OBIS.c_str());
   int position = result - str;
   int substringLength = strlen(str) - position;
   //Serial.print(position);
   //Serial.print("\n");
   //Serial.print(substringLength);
   //String test;
   String stringValue = s.substring(position+4,position + 20);
 
   //get index of (
   char *tast = stringValue.c_str();
   char *result2 = strstr(tast, "(");
   int position2 = result2 - tast;
 
   //get index of )
   //char *stringValue = stringValue.c_str();
   
   char *result3 = strstr(tast, ")");
   int position3 = result3 - tast;
 
   String stringValue2 = stringValue.substring(position2+1,position3);
 
  //REMOVE KWH SUBSTRING
  stringValue2.replace("*kWh","");
  stringValue2.replace(",","");
  long longNumber = stringValue2.toInt();
   /*char * pch;*/
  return longNumber;
  // pch = strtok (string, "#CR#LF0.9.2");
 
   //return pch;
 
}  

// read data response from electrometer and try parse
// parsed values save to variable e1, e2, e3
// return: x if parse successful y if not
int Electrometer::readResponse()
{
	long lastTime = millis();
	char c;
	String data = "";

	
	while ((lastTime + TIMEOUT) > millis())
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
