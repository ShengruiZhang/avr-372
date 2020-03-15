/*
	Author: Shengrui Zhang
	NetID: shengruizhang
	Date of publish: March 2019
	
		ECE 372 - Lab 3: Liquid Crystal Display
		
		Main function
		
*/

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include "timer.h"
#include "LiquidCrystal.h"

typedef unsigned int uint;

int main(void)
{	
	DDRB |= _BV(DDB7);
	
	LCD_init();
	LCD_moveCursor(0, 4);
	LCD_writeString("COVID19");
	
    while (1) 
    {
		PORTB |= _BV(PB7);
		_delay_ms(500);
		PORTB &= ~(_BV(PB7));
		_delay_ms(500);
    }
}
