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
void init_timer_0(enum TimerMode _mode_Timer0) {
	
	switch(_mode_Timer0) {
		case _Timer_Mode_CTC:
			
			// Disconnect waveform gen.
			TCCR0A &= ~_BV(COM0A0);
			TCCR0A &= ~_BV(COM0A1);
			
			// CTC mode
			TCCR0A &= ~_BV(WGM00);
			TCCR0A |= _BV(WGM01);
			
			TCCR0B &= ~_BV(WGM02);
			
			// 16 counts -> 1 ms
			OCR0A = 250;
						
			break;
			
			
		case _Timer_Mode_FastPWM:
						
			break;
			
			
		default:
		break;
	}
	}
	
/*	This Function has been proved to be working */ 
void init_timer_1(enum TimerMode _mode_timer1) {
	
	switch(_mode_timer1) {
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
			ICR1 = Timer1_TOP;
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

/*	This Function has been proved to be working */ 
void init_timer_3(enum TimerMode _mode_timer3) {
	
	switch(_mode_timer3) {
		case _Timer_Mode_CTC:
		
		// Toggle OC3A and OC3B on compare match
		TCCR3A = ( _BV(COM3A0) ) | ( _BV(COM3B0) );
		
		// Timer operates in CTC mode
		TCCR3A &= ~( _BV(WGM30) );
		TCCR3A &= ~( _BV(WGM31) );
		TCCR3B = ( _BV(WGM32) );
		TCCR3B &= ~( _BV(WGM33) );
		
		// 1024 prescaler, timer starts
		TCCR3B |= _BV(CS30);
		TCCR3B &= ~( _BV(CS31) );
		TCCR3B |= _BV(CS32);

		// Set OCR3A, defines the length for OC3A/B
		OCR3A = 15525;
		
		break;
		
		
		case _Timer_Mode_FastPWM:
		
		TCCR3A = 0;
		TCCR3B = 0;
		
		// Fast PWM
		// Use ICR3 as Top, and use OCR3A to generate waveform
		TCCR3A &= ~( _BV(WGM30) );
		//TCCR3A |= _BV(WGM30);
		
		TCCR3A |= _BV(WGM31);
		//TCCR3A &= ~( _BV(WGM31) );
		
		TCCR3B |= _BV(WGM32);
		
		//TCCR3B &= ~( _BV(WGM33) );
		TCCR3B |= _BV(WGM33);
		
		// Non-inverting mode
		//TCCR3A = _BV(COM3A0);
		TCCR3A &= ~( _BV(COM3A0) );
		TCCR3A |= _BV(COM3A1);
		//TCCR3A &= ~( _BV(COM3A1) );
		TCCR3A |= _BV(COM3B1);
		
		// Define Top to MAX
		ICR3 = Timer3_TOP;;
		// 1FFF -> 8191
		
		OCR3A = 125;
		OCR3B = 125;
		
		// 1 prescaler
		TCCR3B |= _BV(CS30);
		//TCCR3B &= ~( _BV(CS30) );
		TCCR3B &= ~( _BV(CS31) );
		//TCCR3B |= _BV(CS32);
		TCCR3B &= ~( _BV(CS32) );
		
		break;
		
		
		default:
		break;
	}
}

/*	This Function has been proved to be working */
void Timer_0_delay(uint _Lenght_timer0) {
	
	// Clear match flag
	TIFR0 |= _BV(OCF0A);
	
	// Clear counter
	TCNT0 = 0;
	
	// Start Timer
	TCCR0B &= ~_BV(CS02);
	TCCR0B |= _BV(CS01);
	TCCR0B |= _BV(CS00);
	
	for(uint _aux = 1; _aux <= _Lenght_timer0; ++_aux) {
		// Wait for 1 match occur, 1 ms resolution
		while( !(TIFR0 & (1 << OCF0A)) );
		TIFR0 |= _BV(OCF0A);
	}
	
	// Stop Timer
	TCCR0B &= ~_BV(CS02);
	TCCR0B &= ~_BV(CS01);
	TCCR0B &= ~_BV(CS00);
}

/*	This Function has been proved to be working */ 
void Timer_1_SetWidth(uint _Width_timer1) {
	OCR1A = Timer1_TOP * ( (float)_Width_timer1 / 1024);
	OCR1B = Timer1_TOP * ( (float)_Width_timer1 / 1024);
}

/*	This Function has been proved to be working */ 
void Timer_3_SetWidth(uint _Width_timer3) {
	OCR3A = Timer3_TOP * ( (float)_Width_timer3 / 1024);
	OCR3B = Timer3_TOP * ( (float)_Width_timer3 / 1024);
}