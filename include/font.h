#ifndef _FONT_H_
#define _FONT_H_

#include <Arduino.h>

#define FONT_OFFSET      32
#define FONT_WIDTH       5
#define FONT_HEIGHT      8
#define FONT_NUM_CHARS   223

#define BLOCK_CHAR       252

extern const unsigned char font[FONT_NUM_CHARS*FONT_WIDTH] PROGMEM;

#endif