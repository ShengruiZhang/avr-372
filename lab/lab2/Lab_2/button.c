#include <avr/io.h>

#include "button.h"

void init_button_PA() {
	DDRB = 0;	// Port B as input
	DDRB |= 1 << PB7;	//  PB7 as button indicator
	
	PORTB |= 1 << PB3;	// Use PB# pull-up
	
	PCICR |= 1 << PCIE0;	// Enable PCINT 8:0
	
	PCMSK0 |= 1 << PCINT3;	// Enable PCINT3
}