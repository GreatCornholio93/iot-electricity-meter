#include <SoftwareSerial.h>
#include <stdlib.h>

bool isDebug = true;
int e1, e2, e3;
long lastTime;
long TIMEOUT = 32000;
SoftwareSerial DEBUG(7, 8);  

int readData()
{
  sendHello();
  readHello();

  //sendRequest();
  return readResponse();
}

void sendHello()
{
  if (isDebug)
    DEBUG.println("Sending hello");
  // send hello message /?! RC LF
  Serial.print("/?!\r\n");
}

// read answer to the hello message - usually ID or ID and DATA
void readHello()
{
long  lastTime = millis();
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

void sendRequest()
{  
  if (isDebug)
    DEBUG.println("Send data request");
  // send data request [ACK]000 CR LF
  byte message[] = {0x06, 0x30, 0x30, 0x30, 0x0d, 0x0a};
    Serial.write(message, sizeof(message));
}

String parseFromResult(String s, String fuckingOBIS)
{
   /*char * string = s.c_str();
   char * fucking = fuckingOBIS.c_str();*/
   char *str = s.c_str();
   // na nasledujicim radku bude fucking OBIS
   char *result = strstr(str, fuckingOBIS.c_str());
   int position = result - str;
   int substringLength = strlen(str) - position;
   //Serial.print(position);
   //Serial.print("\n");
   //Serial.print(substringLength);
   //String test;
   String fuck = s.substring(position+4,position + 20);

   //get index of (
   char *tast = fuck.c_str();
   char *result2 = strstr(tast, "(");
   int position2 = result2 - tast;

   //get index of )
   //char *fuck = fuck.c_str();
   
   char *result3 = strstr(tast, ")");
   int position3 = result3 - tast;

    String tast666 = fuck.substring(position2+1,position3);
    
   
   /*char * pch;*/
  return tast666;
  // pch = strtok (string, "#CR#LF0.9.2");

   //return pch;
  
}  


// read data response from electrometer and try parse
// parsed values save to variable e1, e2, e3
// return: x if parse successful y if not
int readResponse()
{
  sendRequest();
  long lastTime = millis();
  char c;
  String data = "";

  if (isDebug)
    DEBUG.print(c);
  
  


  while ((lastTime + TIMEOUT) > millis())
  {
    if (Serial.available() > 0)
    {
      c = Serial.read();
      DEBUG.print(c);
      data += c;
    }
  // return tryParseResponse(data);

  }
  DEBUG.print("-----------------------------");
  DEBUG.print("DATA:");
  DEBUG.print(data);
  DEBUG.print("PARSED: ");
  DEBUG.print(parseFromResult(data,"C.7.1"));
  
  return 0;
  }

int getE1()
{
  return e1;
}

int getE2()
{
  return e2;
}

int getE3()
{
  return e3;
}

void setup()
{
  e1 = 0;
  e2 = 0;
  e3 = 0;
  Serial.begin(300, SERIAL_7E1);

  int rx = 7;
  int tx = 8;
  int baud = 9600;

  
  DEBUG.begin(baud);
  DEBUG.println("Starting debug serial interface");



}


void loop()
{
  readData();
  delay(60000);
}
