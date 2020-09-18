#include <Arduino.h>
#include <TimerOne.h>
#include "redeye.h"

void setup() {
	Serial.begin(115200);
	redeye_init();
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
	  Serial.write(redeye_get_char());
  }
}