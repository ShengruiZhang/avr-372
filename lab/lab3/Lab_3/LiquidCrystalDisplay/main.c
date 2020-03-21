/*
	Author: Shengrui Zhang
	NetID: shengruizhang
	Date of publish: March 2019
	
		ECE 372 - Lab 3: Liquid Crystal Display
		
		Main function
		
*/

#define F_CPU 16000000UL

#include <avr/io.h>

#include "timer.h"
#include "LiquidCrystal.h"

typedef unsigned int uint;

int main(void)
{	
	DDRB |= _BV(DDB7);
	
	TIMER1_init();
	LCD_init();
	//LCD_moveCursor(0, 0);
	//LCD_writeString("Hello!");
	
	LCD_moveCursor(0, 0);
	LCD_writeString("My name is: ");
	LCD_moveCursor(1, 0);
	LCD_writeString("Shengrui Zhang");
	
    while (1) 
    {
		
    }
}
