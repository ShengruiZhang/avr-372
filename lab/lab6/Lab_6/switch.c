 /*
 * Implementation - Button
 *
 * Created: 2020-05-06 17:45:38
 *
 * Author: Shengrui Zhang
			Zepeng Cai
 */
#include <avr/io.h>

#include "switch.h"

void init_button_PB4() {
	
	// PB7 as button indicator
	DDRB |= 1 << PB7;
	
	// PB4 as button input
	DDRB |= 1 << PB4;
	
	// Enable PB4 internal pull-up
	PORTB |= 1 << PB4;
	
	// Enable Pin Change INTerrupt [8:0]
	PCICR |= 1 << PCIE0;
	
	// Enable PCINT for PB4;
	PCMSK0 |= 1 << PCINT4;
}

void init_button_PD0() {
	 // PB7 as button indicator
	 DDRB |= 1 << DDB7;
	 
	 // PD0 (INT0) as button input
	 DDRD |= 1 << DDD0;
	 
	 // enable internal pull-up
	 PORTD |= 1 << PD0;
	 
	 // low level on the pin generates interrupt
	 EICRA = 0;
	 
	 // enable external interrupt (INT)
	 EIMSK |= 1 << INT0;
	 
	 // clear interrupt flag
	 EIFR |= 1 << INTF0;
}