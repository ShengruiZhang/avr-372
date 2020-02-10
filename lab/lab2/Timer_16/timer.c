// This is to initialize the 16-bit timer 1

#include "global_macro.h"
#include "timer.h"
#include <avr/io.h>

void init_timer_8(enum MODE_TIMER timer_mode) {
	if (timer_mode == CTC)
	{
		TCCR0A |= 1 << COM0A0;	// Toggle output on compare match
		
		TCCR0A |= 1 << WGM01;	// Set to CTC mode
		
		TCCR0B |= (1 << CS02) | (1 << CS00);	// Prescaler as 1024
		
		OCR0A = 253;
	}
}
	
	
void init_timer_16(enum MODE_TIMER timer_mode) {
	if (timer_mode == CTC)
	{
		TCCR1A |= (1 << COM1A0) | (1 << COM1C0);	// Toggle OC1A on compare match
		
		TCCR1B |= 1 << WGM12;	// Set to CTC mode
		
		TCCR1B |= (1 << CS12) | (1 << CS10);	//Set prescaler to 1024
		
		OCR1A = 15624;	// Set compare value
	}
}