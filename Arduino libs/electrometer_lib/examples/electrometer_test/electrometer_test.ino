#include "electrometer.h"

Electrometer elm(7, 8, 9600);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
	elm.readData();

	delay(8000);
}