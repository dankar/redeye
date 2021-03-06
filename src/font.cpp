#include <Arduino.h>
#include "font.h"

const unsigned char overflow_char[FONT_WIDTH] PROGMEM = {0x9f, 0xcf, 0xe7, 0xf3, 0xf9};

const unsigned char font[FONT_NUM_CHARS*FONT_WIDTH] PROGMEM = 
{ 
	0x0, 0x0, 0x0, 0x0, 0x0,
0x0, 0x0, 0x5f, 0x0, 0x0,
0x0, 0x7, 0x0, 0x7, 0x0,
0x14, 0x7f, 0x14, 0x7f, 0x14,
0x4, 0x2a, 0x7f, 0x2a, 0x10,
0x23, 0x13, 0x8, 0x64, 0x62,
0x36, 0x49, 0x56, 0x20, 0x50,
0x0, 0x0, 0x7, 0x0, 0x0,
0x0, 0x1c, 0x22, 0x41, 0x0,
0x0, 0x41, 0x22, 0x1c, 0x0,
0x8, 0x2a, 0x1c, 0x2a, 0x8,
0x8, 0x8, 0x3e, 0x8, 0x8,
0x0, 0xb0, 0x70, 0x0, 0x0,
0x8, 0x8, 0x8, 0x8, 0x8,
0x0, 0x60, 0x60, 0x0, 0x0,
0x20, 0x10, 0x8, 0x4, 0x2,
0x3c, 0x62, 0x52, 0x4a, 0x3c,
0x0, 0x44, 0x7e, 0x40, 0x0,
0x64, 0x52, 0x4a, 0x4a, 0x44,
0x24, 0x42, 0x4a, 0x4a, 0x34,
0x10, 0x18, 0x14, 0x7e, 0x10,
0x2e, 0x4a, 0x4a, 0x4a, 0x32,
0x38, 0x54, 0x52, 0x52, 0x20,
0x2, 0x62, 0x12, 0xa, 0x6,
0x34, 0x4a, 0x4a, 0x4a, 0x34,
0x4, 0x4a, 0x4a, 0x2a, 0x1c,
0x0, 0x36, 0x36, 0x0, 0x0,
0x0, 0xb6, 0x76, 0x0, 0x0,
0x8, 0x14, 0x22, 0x41, 0x0,
0x14, 0x14, 0x14, 0x14, 0x14,
0x0, 0x41, 0x22, 0x14, 0x8,
0x2, 0x1, 0x51, 0x9, 0x6,
0x3e, 0x41, 0x5d, 0x49, 0xe,
0x7c, 0x12, 0x12, 0x12, 0x7c,
0x7e, 0x4a, 0x4a, 0x4a, 0x34,
0x3c, 0x42, 0x42, 0x42, 0x24,
0x7e, 0x42, 0x42, 0x24, 0x18,
0x7e, 0x4a, 0x4a, 0x4a, 0x42,
0x7e, 0xa, 0xa, 0xa, 0x2,
0x3c, 0x42, 0x42, 0x52, 0x74,
0x7e, 0x8, 0x8, 0x8, 0x7e,
0x0, 0x42, 0x7e, 0x42, 0x0,
0x30, 0x40, 0x40, 0x40, 0x3e,
0x7e, 0x8, 0x14, 0x22, 0x40,
0x7e, 0x40, 0x40, 0x40, 0x40,
0x7e, 0x4, 0x18, 0x4, 0x7e,
0x7e, 0x4, 0x8, 0x10, 0x7e,
0x3c, 0x42, 0x42, 0x42, 0x3c,
0x7e, 0x12, 0x12, 0x12, 0xc,
0x3c, 0x42, 0x52, 0x22, 0x5c,
0x7e, 0x12, 0x12, 0x32, 0x4c,
0x24, 0x4a, 0x4a, 0x4a, 0x30,
0x2, 0x2, 0x7e, 0x2, 0x2,
0x3e, 0x40, 0x40, 0x40, 0x3e,
0xe, 0x30, 0x40, 0x30, 0xe,
0x7e, 0x20, 0x18, 0x20, 0x7e,
0x42, 0x24, 0x18, 0x24, 0x42,
0x6, 0x8, 0x70, 0x8, 0x6,
0x62, 0x52, 0x4a, 0x46, 0x42,
0x0, 0x7f, 0x41, 0x41, 0x0,
0x2, 0x4, 0x8, 0x10, 0x20,
0x0, 0x41, 0x41, 0x7f, 0x0,
0x4, 0x2, 0x1, 0x2, 0x4,
0x80, 0x80, 0x80, 0x80, 0x80,
0x0, 0x3, 0x4, 0x0, 0x0,
0x20, 0x54, 0x54, 0x54, 0x78,
0x7f, 0x44, 0x44, 0x44, 0x38,
0x38, 0x44, 0x44, 0x44, 0x44,
0x38, 0x44, 0x44, 0x44, 0x7f,
0x38, 0x54, 0x54, 0x54, 0x18,
0x8, 0x7e, 0x9, 0x2, 0x0,
0x18, 0xa4, 0xa4, 0xa4, 0x78,
0x7f, 0x4, 0x4, 0x4, 0x78,
0x0, 0x44, 0x7d, 0x40, 0x0,
0x40, 0x80, 0x84, 0x7d, 0x0,
0x7f, 0x10, 0x28, 0x44, 0x0,
0x0, 0x41, 0x7f, 0x40, 0x0,
0x7c, 0x4, 0x38, 0x4, 0x78,
0x7c, 0x4, 0x4, 0x4, 0x78,
0x38, 0x44, 0x44, 0x44, 0x38,
0xfc, 0x24, 0x24, 0x24, 0x18,
0x18, 0x24, 0x24, 0x24, 0xfc,
0x7c, 0x8, 0x4, 0x4, 0x4,
0x48, 0x54, 0x54, 0x54, 0x24,
0x4, 0x3f, 0x44, 0x20, 0x0,
0x3c, 0x40, 0x40, 0x40, 0x7c,
0x1c, 0x20, 0x40, 0x20, 0x1c,
0x3c, 0x40, 0x30, 0x40, 0x3c,
0x44, 0x28, 0x10, 0x28, 0x44,
0x1c, 0xa0, 0xa0, 0xa0, 0x7c,
0x44, 0x64, 0x54, 0x4c, 0x44,
0x8, 0x36, 0x41, 0x41, 0x0,
0x0, 0x0, 0x7f, 0x0, 0x0,
0x0, 0x41, 0x41, 0x36, 0x8,
0x8, 0x4, 0x8, 0x10, 0x8,
0x55, 0x2a, 0x55, 0x2a, 0x55,
0x0, 0x0, 0x0, 0x0, 0x0,
0x8, 0x8, 0x2a, 0x8, 0x8,
0x22, 0x14, 0x8, 0x14, 0x22,
0x10, 0x20, 0x7f, 0x1, 0x1,
0x20, 0x40, 0x3e, 0x1, 0x2,
0x41, 0x63, 0x55, 0x49, 0x63,
0x7f, 0x7f, 0x3e, 0x1c, 0x8,
0x4, 0x7c, 0x4, 0x7c, 0x4,
0x30, 0x49, 0x4a, 0x4c, 0x38,
0x50, 0x58, 0x54, 0x52, 0x51,
0x51, 0x52, 0x54, 0x58, 0x50,
0x14, 0x34, 0x1c, 0x16, 0x14,
0x30, 0x48, 0x48, 0x30, 0x48,
0x8, 0x8, 0x2a, 0x1c, 0x8,
0x8, 0x1c, 0x2a, 0x8, 0x8,
0x7c, 0x20, 0x20, 0x1c, 0x20,
0xf, 0x8, 0x0, 0x78, 0x28,
0x0, 0x7, 0x5, 0x7, 0x0,
0x8, 0x14, 0x2a, 0x14, 0x22,
0x22, 0x14, 0x2a, 0x14, 0x8,
0x7f, 0x8, 0x8, 0x8, 0x8,
0x0, 0x0, 0xf8, 0x0, 0x0,
0x0, 0xe8, 0xa8, 0xb8, 0x0,
0x0, 0x1d, 0x15, 0x17, 0x0,
0x0, 0x15, 0x15, 0x1f, 0x0,
0x0, 0x0, 0x68, 0x80, 0x0,
0x0, 0x40, 0x80, 0x74, 0x0,
0x60, 0x60, 0x0, 0x60, 0x60,
0x0, 0x0, 0xd, 0x10, 0x0,
0x0, 0x10, 0x10, 0xd, 0x0,
0x0, 0x1f, 0x4, 0xa, 0x10,
0x0, 0x1e, 0x2, 0x2, 0x1c,
0x30, 0x28, 0x34, 0x22, 0x21,
0x78, 0x15, 0x16, 0x14, 0x78,
0x78, 0x16, 0x15, 0x16, 0x78,
0x7c, 0x55, 0x56, 0x54, 0x44,
0x7c, 0x56, 0x55, 0x56, 0x44,
0x7c, 0x55, 0x54, 0x55, 0x44,
0x0, 0x46, 0x7d, 0x46, 0x0,
0x0, 0x45, 0x7c, 0x45, 0x0,
0x0, 0x0, 0x2, 0x1, 0x0,
0x0, 0x1, 0x2, 0x0, 0x0,
0x0, 0x2, 0x1, 0x2, 0x0,
0x0, 0x1, 0x0, 0x1, 0x0,
0x2, 0x1, 0x2, 0x4, 0x2,
0x3c, 0x41, 0x42, 0x40, 0x3c,
0x38, 0x42, 0x41, 0x42, 0x38,
0x58, 0x7e, 0x59, 0x41, 0x2,
0x1, 0x1, 0x1, 0x1, 0x1,
0x4, 0x8, 0x72, 0x9, 0x4,
0x18, 0xa0, 0xa2, 0xa1, 0x78,
0x0, 0x7, 0x5, 0x7, 0x0,
0x1e, 0x21, 0xa1, 0x61, 0x12,
0x18, 0x24, 0xa4, 0x64, 0x24,
0x7c, 0xa, 0x11, 0x22, 0x7d,
0x78, 0xa, 0x9, 0xa, 0x71,
0x0, 0x0, 0x7d, 0x0, 0x0,
0x30, 0x48, 0x45, 0x40, 0x20,
0x5d, 0x22, 0x22, 0x22, 0x5d,
0x48, 0x7e, 0x49, 0x41, 0x2,
0x2b, 0x2c, 0x78, 0x2c, 0x2b,
0x8, 0x56, 0x55, 0x35, 0x8,
0x40, 0x48, 0x3e, 0x9, 0x1,
0x18, 0x24, 0x7e, 0x24, 0x24,
0x20, 0x56, 0x55, 0x56, 0x38,
0x38, 0x56, 0x55, 0x56, 0x8,
0x30, 0x4a, 0x49, 0x4a, 0x30,
0x38, 0x42, 0x41, 0x42, 0x78,
0x20, 0x54, 0x56, 0x55, 0x78,
0x38, 0x54, 0x56, 0x55, 0x8,
0x30, 0x48, 0x4a, 0x49, 0x30,
0x38, 0x40, 0x42, 0x41, 0x78,
0x20, 0x55, 0x56, 0x54, 0x78,
0x38, 0x55, 0x56, 0x54, 0x8,
0x30, 0x49, 0x4a, 0x48, 0x30,
0x38, 0x41, 0x42, 0x40, 0x78,
0x20, 0x55, 0x54, 0x55, 0x78,
0x38, 0x55, 0x54, 0x55, 0x8,
0x30, 0x49, 0x48, 0x49, 0x30,
0x38, 0x41, 0x40, 0x41, 0x78,
0x78, 0x17, 0x15, 0x17, 0x78,
0x0, 0x4a, 0x79, 0x42, 0x0,
0x5c, 0x32, 0x2a, 0x26, 0x1d,
0x7e, 0x9, 0x7e, 0x49, 0x49,
0x20, 0x57, 0x55, 0x57, 0x78,
0x0, 0x48, 0x7a, 0x41, 0x0,
0x58, 0x24, 0x54, 0x48, 0x34,
0x74, 0x54, 0x78, 0x54, 0x5c,
0x78, 0x15, 0x14, 0x15, 0x78,
0x0, 0x49, 0x7a, 0x40, 0x0,
0x38, 0x45, 0x44, 0x45, 0x38,
0x3c, 0x41, 0x40, 0x41, 0x3c,
0x7c, 0x54, 0x56, 0x55, 0x44,
0x0, 0x49, 0x78, 0x41, 0x0,
0xfe, 0x25, 0x25, 0x25, 0x1a,
0x38, 0x46, 0x45, 0x46, 0x38,
0x78, 0x14, 0x16, 0x15, 0x78,
0x7a, 0x15, 0x16, 0x15, 0x78,
0x22, 0x55, 0x56, 0x55, 0x78,
0x8, 0x7f, 0x49, 0x22, 0x1c,
0x30, 0x48, 0x4a, 0x3f, 0x2,
0x0, 0x44, 0x7e, 0x45, 0x0,
0x0, 0x45, 0x7e, 0x44, 0x0,
0x38, 0x44, 0x46, 0x45, 0x38,
0x38, 0x45, 0x46, 0x44, 0x38,
0x3a, 0x45, 0x46, 0x45, 0x38,
0x32, 0x49, 0x4a, 0x49, 0x30,
0x48, 0x55, 0x56, 0x55, 0x24,
0x40, 0x51, 0x2a, 0x9, 0x0,
0x3c, 0x40, 0x42, 0x41, 0x3c,
0x4, 0x9, 0x70, 0x9, 0x4,
0x18, 0xa1, 0xa0, 0xa1, 0x78,
0x41, 0x7f, 0x55, 0x14, 0x8,
0xfe, 0x24, 0x24, 0x18, 0x0,
0x0, 0x18, 0x18, 0x0, 0x0,
0x7c, 0x20, 0x20, 0x1c, 0x20,
0x6, 0x4f, 0x7f, 0x1, 0x7f,
0x15, 0x1f, 0x30, 0x28, 0x74,
0x4, 0x4, 0x4, 0x4, 0x4,
0x27, 0x10, 0x68, 0x44, 0xe2,
0x27, 0x10, 0x8, 0xd4, 0xb2,
0x28, 0x35, 0x35, 0x3e, 0x0,
0x26, 0x29, 0x29, 0x29, 0x26,
0x8, 0x14, 0x2a, 0x14, 0x22,
0xff, 0xff, 0xff, 0xff, 0xff,
0x22, 0x14, 0x2a, 0x14, 0x8
};