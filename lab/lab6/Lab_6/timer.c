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
#include "global_macro.h"

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
			
			// 64 prescaler, 1ms resolution
			OCR0A = 250;
						
			break;
			
			
		case _Timer_Mode_FastPWM:
						
			break;
			
			
		default:
		break;
	}
}

void init_timer_1(enum TimerMode _mode_timer1) {
	
	switch(_mode_timer1) {
		case _Timer_Mode_CTC:
		
		// Disconnect waveform gen.
		TCCR1A &= ~( _BV(COM1A1) ) | ( _BV(COM1A0) );
		
		// Timer operates in CTC mode
		TCCR1A &= ~( _BV(WGM10) );
		TCCR1A &= ~( _BV(WGM11) );
		TCCR1B = ( _BV(WGM12) );
		TCCR1B &= ~( _BV(WGM13) );

		/* 1 prescaler
			1 count -> 62.5 ns
			1 ms -> 16000 counts
			Resolution: 62.5 ns
		*/
		OCR1A = 16000;
		
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
		
		break;
		
		
		default:
		break;
	}
}

/*	This Function has been proved to be working */
void Timer_0_delay_ms(uint _Lenght_timer0) {
	
	// Clear match flag
	TIFR0 |= _BV(OCF0A);
	
	// Clear counter
	TCNT0 = 0;
	
	/* Start Timer
		64 prescaler */
	TCCR0B &= ~_BV(CS02);
	TCCR0B |= _BV(CS01);
	TCCR0B |= _BV(CS00);
	
	for (uint _aux = 1; _aux <= _Lenght_timer0; ++_aux) {
		// Wait for 1 match occur, 1 ms resolution
		while ( !(TIFR0 & (1 << OCF0A)) );
		TIFR0 |= _BV(OCF0A);
	}
	
	// Stop Timer
	TCCR0B &= ~_BV(CS02);
	TCCR0B &= ~_BV(CS01);
	TCCR0B &= ~_BV(CS00);
}

/*	This Function has been proved to be working */
void Timer_1_delay_ms(uint16_t _Lenght_timer1) {
	
	// Clear match flag
	TIFR1 |= _BV(OCF1A);
	
	OCR1A = 16000;
	
	// Clear counter
	TCNT1 = 0;
	
	// Start Timer, 1 prescaler
	TCCR1B &= ~_BV(CS12);
	TCCR1B &= ~_BV(CS11);
	TCCR1B |= _BV(CS10);
	
	for (uint16_t _aux = 1; _aux <= _Lenght_timer1; ++_aux) {
		// Wait for 1 match occur, Resolution: 1 ms
		while ( !(TIFR1 & (1 << OCF1A)) );
		TIFR1 |= _BV(OCF1A);
	}
	
	// Stop Timer
	TCCR1B &= ~_BV(CS12);
	TCCR1B &= ~_BV(CS11);
	TCCR1B &= ~_BV(CS10);
}

/*	This Function has been proved to be working */ 
void Timer_1_SetWidth(float _Width_timer1) {
	OCR1A = Timer1_TOP * _Width_timer1;
	OCR1B = Timer1_TOP * _Width_timer1;
}