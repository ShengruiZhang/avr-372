/*
 * Implementation - Pulse Width Modulation
 *
 * Created: 2020-05-01 18:03:05
 *
 * Author: Shengrui Zhang
			Zepeng Cai
 */ 
#include <avr/io.h>
#include "global_macro.h"

#include "pwm.h"

/*	This Function has been proved to be working */
void init_timer_3(enum TimerMode _mode_timer3) {
	
	// Set OCR3A output
	DDRE |= _BV(DDE3);
	
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
		ICR3 = Timer3_TOP;
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

void Timer_3_SetWidth(float _Width_timer3) {
	OCR3A = Timer3_TOP * ( _Width_timer3 );
	OCR3B = Timer3_TOP * ( _Width_timer3 );
}