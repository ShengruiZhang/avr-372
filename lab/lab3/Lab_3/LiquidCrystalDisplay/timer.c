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
	// Set CTC mode
	TCCR1A &= ~(1 << WGM10);
	TCCR1A |= 1 << WGM11;
	TCCR1B &= ~(1<<WGM12);
	
	// Set prescaler 64
	TCCR1B |= (1<<CS10);
	
	OCR1A = 16;
}


void TIMER1_delay_us(uint _delay_length) {
	  uint extraCNT = 0;
	  
	  // Clear flag and counter
	  TIFR1 |= (1<<OCF1A);
	  TCNT1 = 0;
	  
	  while(extraCNT < _delay_length)
	  {
		  if(TIFR1 & (1 << OCF1A))
		  {
			  ++extraCNT;
			  TIFR1 |= (1 << OCF1A);
		  }
	  }
}