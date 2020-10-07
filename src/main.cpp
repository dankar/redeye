#include <Arduino.h>
#include "redeye.h"
#include "printer.h"

void setup() {
	Serial.begin(19200);
	redeye_init();
	printer_init();
}

void loop() {
  if(redeye_char_available())
  {
	  printer_char(redeye_get_char());
  }
}