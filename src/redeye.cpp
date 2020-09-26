#include <Arduino.h>
#include <TimerOne.h>
#include "redeye.h"
#include "error_correction.h"

#define DEBUG_PIN_OUT       0

#define IR_PIN              3
#define DEBUG_PIN           4

#define BIT_PERIOD          854 // us
#define HALF_BIT_PERIOD     (BIT_PERIOD/2)
#define TOLERANCE           10 // Percent of a bit period
#define BIT_TOLERANCE       (BIT_PERIOD * TOLERANCE / 100)

#define WORD_LENGTH         12
#define START_BITS          3
#define STOP_BITS           3

#define BUFFER_SIZE         200

#define CHECK_START_BITS(x) ((((x) >> 0x1B) & 0b111) == 0b111)
#define CHECK_STOP_BITS(x)  (((x) & 0b111) == 0b000)
#define GET_DATA_BITS(x)    ((x) >> 0x3)

#define BIT_ONE             0b10
#define BIT_ZERO            0b01
#define BIT_MASK            0b11

volatile uint8_t redeye_data_buffer[BUFFER_SIZE];
volatile uint8_t redeye_data_buffer_head = 0;
volatile uint8_t redeye_data_buffer_tail = 0;

volatile uint8_t redeye_data_overflow_state = 0;
volatile uint8_t redeye_bit_period_counter = 0;
volatile uint32_t redeye_data = 0;

volatile uint8_t interrupt_enabled = 0;
volatile uint32_t last_pulse = 0;

TimerOne timer1;

uint8_t redeye_decode_char(uint32_t c)
{
	uint16_t result = 0;
	if(!CHECK_START_BITS(c) || !CHECK_STOP_BITS(c))
	{
		return 0;
	}

	c = GET_DATA_BITS(c);

	for(uint8_t i = 0; i < 12; i++)
	{
		result |= (((c >> i*2) & BIT_MASK) == BIT_ONE) << i;
	}

	return ERROR_CORRECT(result);
}

void redeye_put_char(uint8_t c)
{
	redeye_data_buffer[redeye_data_buffer_head++] = c;
	redeye_data_buffer_head = redeye_data_buffer_head % BUFFER_SIZE;
	redeye_data_overflow_state = redeye_data_buffer_head == redeye_data_buffer_tail;
}

uint8_t redeye_char_available()
{
	return redeye_data_buffer_head != redeye_data_buffer_tail;
}

uint8_t redeye_get_char()
{
	if(redeye_char_available())
	{
		char c = redeye_data_buffer[redeye_data_buffer_tail++];
		redeye_data_buffer_tail = redeye_data_buffer_tail % BUFFER_SIZE;
		return c;
	}
	else
	{
		return '\0';
	}
	
}

void redeye_isr();

void redeye_stop_isr()
{
	timer1.detachInterrupt();
	timer1.stop();
	interrupt_enabled = false;
}

void redeye_isr_bit_clock()
{
	uint8_t data = ((micros() - last_pulse) < 1200000/32768) ? 1 : 0;
	if(!data)
	{
		// If we are not getting pulses, check if we are continually high. This might
		// happen due to IR transistor saturation
		data = digitalRead(IR_PIN);
	}

	#if DEBUG_PIN_OUT == 1
	digitalWrite(DEBUG_PIN, HIGH);
	digitalWrite(DEBUG_PIN, LOW);
	#endif

	redeye_data = (redeye_data << 1) | data;

	if(++redeye_bit_period_counter == (START_BITS + (WORD_LENGTH*2) + STOP_BITS))
	{
		redeye_put_char(redeye_decode_char(redeye_data));
		redeye_stop_isr();
	}
	else if(redeye_bit_period_counter == START_BITS)
	{
		// Give up early if we haven't gotten the start bits
		if(redeye_data != 0b111)
		{
			redeye_stop_isr();
		}
	}
}

void redeye_isr()
{
	
	//redeye_bit_period_counter = 0;
	//

	//digitalWrite(4, HIGH);
	//delayMicroseconds(1);
	//digitalWrite(4, LOW);

	if(!interrupt_enabled)
	{
		redeye_bit_period_counter = 0;
		redeye_data = 0;
		delayMicroseconds(HALF_BIT_PERIOD/6);
		timer1.attachInterrupt(redeye_isr_bit_clock);
		timer1.setPeriod(HALF_BIT_PERIOD);
		timer1.start();
		interrupt_enabled = true;
	}

	last_pulse = micros();
}

void redeye_init()
{
#if DEBUG_PIN_OUT == 1
	pinMode(DEBUG_PIN, OUTPUT);
#endif
	pinMode(IR_PIN, INPUT);
	digitalWrite(IR_PIN, HIGH);
	timer1.initialize(HALF_BIT_PERIOD);
	timer1.attachInterrupt(redeye_isr_bit_clock);
	timer1.stop();
  	attachInterrupt(digitalPinToInterrupt(IR_PIN), redeye_isr, RISING);
	interrupt_enabled = 0;
}

uint8_t redeye_get_overflow()
{
	return redeye_data_overflow_state;
}