#include <Arduino.h>
#include "printer.h"
#include "font.h"

#define SCREEN_HEIGHT    320
#define SCREEN_WIDTH     240

#define TEXT_HEIGHT      8
#define MARGIN_LEFT      40

#define ESCAPE_CHAR      27
#define RESET            255
#define SELFTEST         254
#define DOUBLEWIDE       253
#define SINGLEWIDE       252
#define UNDERLINE        251
#define NO_UNDERLINE     250
#define LATIN1           249
#define ROMAN8           248

#define MAX_COLUMNS      166

char printer_buffer[200];

uint8_t character_buffer[50];
uint8_t character_ptr = 0;

uint8_t x_position = 0;
uint32_t scroll_pos = 0;

uint8_t underline = 0;
uint8_t double_wide = 0;
uint8_t escape_mode = 0;
uint8_t graphic_chars_remaining = 0;
uint8_t graphics_pointer = 0;

void printer_reset_cursor()
{
	x_position = 0;
}

#define RECEIVE_GRAPHICS 2
#define RECEIVE_CHARACTERS 3

void printer_print_graphics()
{
	while(x_position % 8)
	{
		printer_buffer[x_position++] = '\0';
	}

	
	uint8_t array[200];
	memset(array, 0, 200);

	for(int x = 0; x < x_position; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			array[x/8 + y * x_position/8] |= ((printer_buffer[x] >> (y)) & 1) << (7 - ((x) % 8));
		}
	}

	Serial.write(uint8_t(RECEIVE_GRAPHICS));
	Serial.write((uint8_t)x_position);

	
	for(int i = 0; i < x_position; i++)
	{
		Serial.write(array[i]);
	}
	
	memset(printer_buffer, 0, 200);
}

void printer_print_text();
void printer_draw_character(uint8_t c)
{
	character_buffer[character_ptr++] = c;
}

void printer_print_text()
{
	Serial.write(uint8_t(RECEIVE_CHARACTERS));
	Serial.write(uint8_t(character_ptr));

	for(int i = 0; i < character_ptr; i++)
	{
		Serial.write(character_buffer[i]);
	}

	character_ptr = 0;
}

#define UNDERLINE_ON 5
#define UNDERLINE_OFF 6
#define DOUBLEWIDTH_ON 7
#define DOUBLEWIDTH_OFF 8


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
	printer_char('4');
	printer_char('\n');
	delay(500);
	printer_char('\n');
	delay(500);
}

void printer_char(uint8_t c);
void printer_init()
{
	printer_reset_cursor();
	printer_self_test();
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
			printer_draw_character(DOUBLEWIDTH_ON);
			double_wide = 1;
			break;
		case SINGLEWIDE:
			printer_draw_character(DOUBLEWIDTH_OFF);
			double_wide = 0;
			break;
		case UNDERLINE:
			printer_draw_character(UNDERLINE_ON);
			underline = 1;
			break;
		case NO_UNDERLINE:
			printer_draw_character(UNDERLINE_OFF);
			underline = 0;
			break;
		case LATIN1:
			break;
		case ROMAN8:
			break;
		default:
			if(c > 0 && c <= 166)
			{
				graphics_pointer = 0;
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
		if(x_position > MAX_COLUMNS)
		{
			printer_reset_cursor();
		}
		graphic_chars_remaining--;

		if(!graphic_chars_remaining)
		{
			printer_print_graphics();
			graphics_pointer = 0;
		}
	}
	else
	{
		if(c == 4)
		{
			x_position = 0;
		}
		else if(c == 10)
		{
			printer_print_text();
			printer_reset_cursor();
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