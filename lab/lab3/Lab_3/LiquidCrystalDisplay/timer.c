/*
	Author: Shengrui Zhang
	NetID: shengruizhang
	Date of publish: March 2019
	
		ECE 372 - Lab 3: Liquid Crystal Display
		
		Timer1 implementations
		
*/


/*
	Timer1 is used to create microsecond-wise delay
	up to 2,000 us for LCD uses.
*/

#include <avr/io.h>
#include "timer.h"

void TIMER1_init() {
	
	// Waveform gen. Mode 4, CTC mode, OCR1A as top
	TCCR1B |= _BV(WGM12);
	
	// Value of 10 gives timer length of 5 us
	OCR1A = 10;
	
	/*	
		Prescaler of 8, which gives
		resolution of 0.5 us
	*/
	TCCR1B |= _BV(CS11);	// Timers starts here
}


void TIMER1_delay_us(uint _delay_length) {
	
	// Stop timer
	TCCR1B &= ~( _BV(CS12) | _BV(CS11) | _BV(CS10) );
	
	// Input check, as it can't be excess 65535
	if ( _delay_length > 32767 ) _delay_length = 0xFFFF;
	
	// Use user input as compare value
	// Multiple 2 because of 0.5 us resolution
	OCR1A = _delay_length * 2;
	
	// Clear output compare match flag
	TIFR1 |= _BV(OCF1A);
	
	// Clear counter
	TCNT1 = 0;
	
	// Start timer
	TCCR1B |= _BV(CS11);
	
	// Let counter run until flag shows up
	while (TCNT1 != 32767)
	{
		while(TIFR1 & (1 << OCF1A))
		{
			PORTB |= _BV(PB7);
		}
	}
	
	// Set OCR1A back to default 5 us
	OCR1A = 10;
}
