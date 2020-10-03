#include <Arduino.h>
#include "printer.h"
#include "font.h"
#include "Adafruit_Thermal.h"

#define ESCAPE_CHAR         27
#define RESET               255
#define SELFTEST            254
#define DOUBLEWIDE          253
#define SINGLEWIDE          252
#define UNDERLINE           251
#define NO_UNDERLINE        250
#define LATIN1              249
#define ROMAN8              248

#define MAX_COLUMNS         166

#define LINE_FEED           10
#define SPECIAL_LINE_FEED   4

char printer_buffer[200];

uint8_t character_ptr = 0;

uint8_t x_position = 0;
uint32_t scroll_pos = 0;

uint8_t underline = 0;
uint8_t double_wide = 0;
uint8_t escape_mode = 0;
uint8_t graphic_chars_remaining = 0;

Adafruit_Thermal printer(&Serial);

void printer_reset_cursor()
{
	x_position = 0;
}

uint8_t graphics_buffer[200*4];

uint16_t double_bits(uint8_t x)
{
	uint16_t result = 0;
	for(int i = 0; i < 16; i++)
	{
		result |= ((x >> i/2) & 1) << i;
	}
	return result;
}

#define GET_BIT(arr, x, y) ((arr[x] >> (y)) & 1)

void printer_print_graphics()
{
	// Pad to a multiple of 8 pixels wide
	while(x_position % 8)
	{
		printer_buffer[x_position++] = '\0';
	}
	
	memset(graphics_buffer, 0, 200*4);

	for(int x = 0; x < x_position*2; x++)
	{
		for(int y = 0; y < 16; y++)
		{
			graphics_buffer[x/8 + y * (x_position*2)/8] |= GET_BIT(printer_buffer, x/2, y/2) << (7 - ((x) % 8));
		}
	}

	printer.printBitmap(x_position*2, 16, graphics_buffer, false);
	
	memset(printer_buffer, 0, 200);
}

void printer_print_text();
void printer_draw_character(uint8_t c)
{
	if(x_position != 0)
	{
		printer_buffer[x_position++] = '\0' | (underline ? 0x80 : 0x0);
	}

	for(int i = 0; i < FONT_WIDTH; i++)
	{
		printer_buffer[x_position++] = pgm_read_byte(&(font[(c-FONT_OFFSET)*FONT_WIDTH + i])) | (underline ? 0x80 : 0x0);
		if(double_wide)
		{
			printer_buffer[x_position++] = pgm_read_byte(&(font[(c-FONT_OFFSET)*FONT_WIDTH + i])) | (underline ? 0x80 : 0x0);
		}
	}
	printer_buffer[x_position++] = '\0' | (underline ? 0x80 : 0x0);
}

void printer_self_test()
{
	for(uint16_t i = 32; i < 255; i++)
	{
		if((i - 32) % 24 == 0 && (i-32))
		{
			printer_char('\n');
			delay(1000);
		}
		printer_char(i);
	}
	delay(1000);
	printer_char(' ');
	printer_char('D');
	printer_char('\n');
	delay(1000);
	printer_char('\n');
	delay(1000);
	printer_char('B');
	printer_char('A');
	printer_char('T');
	printer_char(':');
	printer_char(' ');
	printer_char('5');
	printer_char('\n');
	delay(500);
	printer_char('\n');
	delay(500);
}

void printer_char(uint8_t c);

void printer_init()
{
	printer.begin(255);
	printer.setLineHeight(8);
	printer_reset_cursor();
}

void printer_char(uint8_t c)
{
	if(!graphic_chars_remaining && c == ESCAPE_CHAR)
	{
		escape_mode = 1;
		return;
	}

	if(escape_mode)
	{
		switch(c)
		{
		case RESET:
			printer_reset_cursor();
			double_wide = 0;
			underline = 0;
			graphic_chars_remaining = 0;
			break;
		case SELFTEST:
			printer_self_test();
			break;
		case DOUBLEWIDE:
			double_wide = 1;
			break;
		case SINGLEWIDE:
			double_wide = 0;
			break;
		case UNDERLINE:
			underline = 1;
			break;
		case NO_UNDERLINE:
			underline = 0;
			break;
		case LATIN1:
			break;
		case ROMAN8:
			break;
		default:
			if(c > 0 && c <= 166)
			{
				graphic_chars_remaining = c;
			}
			else
			{
				printer_draw_character(BLOCK_CHAR);
			}
			
		}
		escape_mode = 0;
	}
	else if(graphic_chars_remaining)
	{
		printer_buffer[x_position++] = c;
		graphic_chars_remaining--;
	}
	else
	{
		if(c == 4 || c == 10)
		{
			if(!x_position)
			{
				printer.feedRows(16);
			}
			else
			{
				printer_print_graphics();
				printer_reset_cursor();
			}
		}
		else
		{
			if(c >= FONT_OFFSET)
			{
				printer_draw_character(c);
			}
			else
			{
				printer_draw_character(BLOCK_CHAR);
			}
		}
	}
}