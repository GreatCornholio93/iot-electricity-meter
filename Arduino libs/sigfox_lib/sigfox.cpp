// #include <SoftwareSerial.h>
// #include <stdlib.h>
// #include "Arduino.h"
#include "Sigfox.h"

Sigfox::Sigfox()
{
  
}

/* 
* definition of the constructor
* input parametrs are rx, tx and baund rate 
* value d stands for "data" and contains result of
* the following methods.
* value counter is indicating if RC chip is in
* configure mode or not if is greater than zero
* then RC chip is in configuration mode and can
* receive data (e.x.: temperature, signal strenght etc...)
*/
Sigfox::Sigfox(int rx, int tx, int baud)
{
  d = 0;
  
  counter = 0;

  // SoftwareSerial SIGFOX(5, 6);
  // SIGFOX.begin(9600);
  this->SIGFOX = new SoftwareSerial(rx, tx);
  this->SIGFOX->begin(baud);

}

/*
* Method that returns integer value containing
* temperature of the RC chip
* first of all checks if RC chip is in configuration
* mode if not is switched into it (sending 0x00)
* counter is incremented so its indicating now is RC
* chip in configuration state. Then instruction 0x55
* is sent into the RC chip. Then arduino receives
* result. The empty line firstly arrives to the buffer
* so it is stored into value emptyLine. To the value
* d is saved temperature that must me modified (d-128)
* according to the documentation of the RC chip
*/
int Sigfox::getTemperature()
{

  delay(1000);
  if (counter == 0)
  {
    byte message[] = {0x00};
    SIGFOX->write(message, sizeof(message));
    counter = counter + 1;
  }

  delay(300);
  byte message2[] = {0x55};

  SIGFOX->write(message2, sizeof(message2));
  int emptyLine = 0;
  
  if (SIGFOX->available() > 0)
  {
    emptyLine = SIGFOX->read();
    d = SIGFOX->read();
  }
  //counter = 0;
  return (d - 128);
}

/*
* Method that returns integer value containing
* RSSI of the RC chip
* first of all checks if RC chip is in configuration
* mode if not is switched into it (sending 0x00)
* counter is incremented so its indicating now is RC
* chip in configuration state. Then instruction 0x53
* is sent into the RC chip. Then arduino receives
* result. The empty line firstly arrives to the buffer
* so it is stored into variable signalstrength. To the value
* signalstrength2 is saved RSSI value that must me modified 
((-1*signalstrength2)/2) according to the documentation
* of the RC chip
*/
int Sigfox::getSignalRSSI()
{
  int signalstrength, signalstrength2;
  delay(1000);
  if (counter == 0)
  {
    byte message[] = {0x00};
    SIGFOX->write(message, sizeof(message));
    counter = counter + 1;
  }

  delay(300);
  byte message2[] = {0x53};

  SIGFOX->write(message2, sizeof(message2));

  delay (300);
   
  
   if (SIGFOX->available() > 0)
    {
       signalstrength = SIGFOX->read();
       signalstrength2 = SIGFOX->read();
    }
   
 // Serial.println(signalstrength);
  return ((-1*signalstrength2)/2);



}

/*
* Method that returns integer value containing
* signal quality of the RC chip
* first of all checks if RC chip is in configuration
* mode if not is switched into it (sending 0x00)
* counter is incremented so its indicating now is RC
* chip in configuration state. Then instruction 0x51
* is sent into the RC chip. Then arduino receives
* result. The empty line firstly arrives to the buffer
* so it is stored into variable signalstrength. To the value
* signalstrength2 is saved signal quality value
*/
int Sigfox::getSignalQuality()
{
  int signalstrength, signalstrength2;
  delay(1000);
  if (counter == 0)
  {
    byte message[] = {0x00};
    SIGFOX->write(message, sizeof(message));
    counter = counter + 1;
  }

  delay(300);
  byte message2[] = {0x51};

  SIGFOX->write(message2, sizeof(message2));

  delay (300);
   
  
   if (SIGFOX->available() > 0)
    {
       signalstrength = SIGFOX->read();
       signalstrength2 = SIGFOX->read();
    }
   
 // Serial.println(signalstrength);
  return signalstrength2;

}

/*
* Method that sends string in to the IoT network sigfox
* first of all character "X" is sent to the RC chip
* so if chip is in the configuration mode it quit that
* mode. Counter indicating state is set to zero. Then
* is is counted length of string and length is sent to
* the chip. Then is string sent byte by byte into the RC
* chip. There is no ACK or information if this code was
* successfull. String is coded into hexa so for example number 40
* is 3430 which hex to axcii converts to 40
*/
void Sigfox::sendString(String string)
{
  SIGFOX->print("X");

  counter = 0;

  delay(300);
  int ia;
  int sizeOfString = 0;
  int i = 0;
  char * string2 = string.c_str();
  size_t len = strlen(string2);

  //  String prefix = "0x0";
  // uncoment Serial.print((char)len);
  SIGFOX->print((char)len);
  for (int i = 0; i < len; i++)
  {

    SIGFOX->print((char)string2[i]);
  }
  
}

/*
* Method that returns float value containing
* voltage of the RC chip
* first of all checks if RC chip is in configuration
* mode if not is switched into it (sending 0x00)
* counter is incremented so its indicating now is RC
* chip in configuration state. Then instruction 0x56
* is sent into the RC chip. Then arduino receives
* result. The empty line firstly arrives to the buffer
* so it is stored into value emptyLine. To the value
* d is saved voltage that must me modified (d * 0.030)
* according to the documentation of the RC chip
*/
float Sigfox::getVoltage()
{
  float emptyLine;
  delay(1000);
  if (counter == 0)
  {
    byte message[] = {0x00};
    SIGFOX->write(message, sizeof(message));
    counter = counter + 1;
  }

  delay(300);
  byte message2[] = {0x56};

  SIGFOX->write(message2, sizeof(message2));

  if (SIGFOX->available() > 0)
  {
    emptyLine = SIGFOX->read();
    d = SIGFOX->read();
  }
  //counter = 0;
 return ((d * 0.030));

}

/*
* Simply converts int to the char
*/
char Sigfox::intToString (int inputNumber)
{
 
 char str = "0";
 return str+inputNumber;

}

/*
* Data are packed into char array of bytes
* convert 3 unsigned longs to 12B unsigned char array
* convert 3 longs to format {a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4} 
* where x1 is low significant byte and x4 is high significant byte
*/
void Sigfox::parse_int_to_12bytes(unsigned char *bytes, unsigned long a, unsigned long b, unsigned long c)
{
  bytes[0] = (char) (a);
  bytes[1] = (char) (a >> 8);
  bytes[2] = (char) (a >> 16);
  bytes[3] = (char) (a >> 24);
  bytes[4] = (char) (b);
  bytes[5] = (char) (b >> 8);
  bytes[6] = (char) (b >> 16);
  bytes[7] = (char) (b >> 24);
  bytes[8] = (char) (c);
  bytes[9] = (char) (c >> 8);
  bytes[10] = (char) (c >> 16);
  bytes[11] = (char) (c >> 24);
}


/*
* Method that sends char array of bytes in to the IoT network sigfox
* first of all character "X" is sent to the RC chip
* so if chip is in the configuration mode it quit that
* mode. Counter indicating state is set to zero. Then
* is is counted length of string and length is sent to
* the chip. Then is string sent byte by byte into the RC
* chip. There is no ACK or information if this code was
* successfull. Char array of bytes should be obtained
* by method parse_int_to_12bytes.
*/
void Sigfox::sendBytes(unsigned char *bytes)
{
  SIGFOX->print("X");
  delay(300);

  size_t len = 12;
  //Serial.print((char)len);
  SIGFOX->print((char)len);

  for (int i = 0; i < len; i++)
  {
    //Serial.println((char)bytes[i]);
    SIGFOX->print((char)bytes[i]);
  }
  counter = 0;
}