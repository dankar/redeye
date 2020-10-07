#ifndef _REDEYE_H_
#define _REDEYE_H_

#define OVERFLOW_CHAR 0x100

void redeye_init();
uint8_t redeye_char_available();
uint16_t redeye_get_char();
uint8_t redeye_get_overflow();

#endif