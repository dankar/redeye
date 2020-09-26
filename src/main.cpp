#include <Arduino.h>
#include "redeye.h"
#include "printer.h"

void setup() {
	Serial.begin(1000000);
	redeye_init();
	printer_init();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(redeye_get_overflow())
  {
	  Serial.println("OVERFLOW!");
	  for(;;);
  }

  if(redeye_char_available())
  {
	  printer_char(redeye_get_char());
  }
}