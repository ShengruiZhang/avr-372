/*
 * Implementation - Button handling
 *
 * Created: 2020-04-08 03:55:37
 * Author: Shengrui Zhang
 */ 
#include <avr/io.h>

#include "button.h"

void init_button() {
	// Dedicated button indicator on Arduino Pin 18
	// PD3
	DDRD |= _BV(DDD3);
	//PORTD |= _BV(PD3);
	
	// Arduino Pin 19 as button input
	// PD2 / INT2
	DDRD &= ~_BV(DDD2);
	
	// Enable pull-up
	PORTD |= _BV(PD2);
	
	// TODO: Setup the INT2 interrupt
	// Any edge generates an interrupt
	EICRA &= ~_BV(ISC21);
	EICRA |= _BV(ISC20);
	
	// Enable INT2 interrupt
	EIMSK |= _BV(INT2);
}
