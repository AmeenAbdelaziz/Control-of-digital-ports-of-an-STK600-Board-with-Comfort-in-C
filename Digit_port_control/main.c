

#include <avr/io.h>
#ifndef	 F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include "implementation.h"

#define OUTPUT	0b11111111
#define INPUT	0b00000000

int main(void)
{

	initialize(leds_h, PA, OUTPUT);
	initialize(sw_h, PK, INPUT);
	write(leds_h, 0b10101010);
	_delay_ms(1500);
	off(leds_h, 0x0F);
	_delay_ms(1500);
	on(leds_h, 0xF0);
	_delay_ms(1500);
	toggle(leds_h, 0x3C);
	_delay_ms(1500);
	toggle(leds_h, 0x3C);
	off(leds_h, 0xFF);
	
	
	write(leds_h, read_busy_wait(sw_h, 0xFF));
	_delay_ms(3000);

	
	while(1){
		write(leds_h, read_raw(sw_h, 0xFF));
	}
	
}

