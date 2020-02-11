#include <avr/io.h>
#include "timer.h"

void init_timer_8() {
	TCCR0A |= 1 << WGM01;	// Set to CTC mode
	
	OCR0A = 15;	// 1 ms on match 
	
	TIMSK0 |= 1 << OCIE0A;	// Enable compare A match interrupt
	
	TCCR0B |= (1 << CS02) | (1 << CS00);	// Start timer with 1024 prescaler
}

void init_timer_16() {
	TCCR1A |= (1 << COM1A0) | (1 << COM1C0);	// Toggle OC1A on compare match
	
	TCCR1B |= 1 << WGM12;	// Set to CTC mode
	
	TCCR1B |= (1 << CS12) | (1 << CS10);	//Set prescaler to 1024
	
	OCR1A = 7812;	// 15624 -> 0.5 Hz / 2 s period
}
