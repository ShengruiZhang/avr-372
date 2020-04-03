/*
 * Implementation - Timers
 *
 * Created: 2020-04-01 18:57:44
 * Author: Shengrui Zhang
 */ 

/*
16 bit -> 65535

16 MHz -> 62.5 ns

prescaler 1 -> 65535 counts -> 4.1 ms
prescaler 1024 -> 65535 counts -> 4.2 s
*/
#include <avr/io.h>

#include "timer.h"

/*	This Function has been proved to be working */ 
void init_timer_16(enum TimerMode _mode) {
	
	switch(_mode) {
		case _Timer_Mode_CTC:
		
			// Toggle OC1A and OC1B on compare match
			TCCR1A = ( _BV(COM1A0) ) | ( _BV(COM1B0) );
			
			// Timer operates in CTC mode
			TCCR1A &= ~( _BV(WGM10) );
			TCCR1A &= ~( _BV(WGM11) );
			TCCR1B = ( _BV(WGM12) );
			TCCR1B &= ~( _BV(WGM13) );
			
			// 1024 prescaler, timer starts
			TCCR1B |= _BV(CS10);
			TCCR1B &= ~( _BV(CS11) );
			TCCR1B |= _BV(CS12);

			// Set OCR1A, defines the length for OC1A/B
			OCR1A = 15525;
			
			break;
			
		case _Timer_Mode_FastPWM:
			
			TCCR1A = 0;
			TCCR1B = 0;
						
			// Fast PWM
			// Use xx as Top, and use OCR1A to generate waveform
			TCCR1A &= ~( _BV(WGM10) );
			//TCCR1A |= _BV(WGM10);
			
			TCCR1A |= _BV(WGM11);
			//TCCR1A &= ~( _BV(WGM11) );
			
			TCCR1B |= _BV(WGM12);
			
			//TCCR1B &= ~( _BV(WGM13) );
			TCCR1B |= _BV(WGM13);
			
			// Non-inverting mode
			//TCCR1A = _BV(COM1A0);
			TCCR1A &= ~( _BV(COM1A0) );
			TCCR1A |= _BV(COM1A1);
			//TCCR1A &= ~( _BV(COM1A1) );
			TCCR1A |= _BV(COM1B1);
			
			// Define Top to MAX
			ICR1 = 0x1FFF;
			// 1FFF -> 8191
			
			OCR1A = 125;
			OCR1B = 125;
			
			// 1 prescaler
			TCCR1B |= _BV(CS10);
			//TCCR1B &= ~( _BV(CS10) );
			TCCR1B &= ~( _BV(CS11) );
			//TCCR1B |= _BV(CS12);
			TCCR1B &= ~( _BV(CS12) );
			
			break;
		
			
			default:
			break;
	}
}