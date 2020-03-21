/*
	Author: Shengrui Zhang
	NetID: shengruizhang
	Date of publish: March 2019
	
		ECE 372 - Lab 3: Liquid Crystal Display
		
		Liquid Crystal implementations
		
*/
#define F_CPU 16000000UL

#include <avr/io.h>

// Use AVR delay for debug
#include <util/delay.h>

#include "LiquidCrystal.h"
#include "timer.h"

// LED initialization
void LCD_init() {
	LCD_init_Pins();
	LCD_init_Main();
}

void LCD_init_Main() {
	// Delay 50 ms
	TIMER1_delay_us(0xFFFF);
	
	// Set RS and EN low to begin commands
	LCD_RS_set_LOW;
	LCD_EN_set_LOW;
	
	_LCD_write_4bit(0x03);
	TIMER1_delay_us(4500);
	
	_LCD_write_4bit(0x03);
	TIMER1_delay_us(4500);
	
	_LCD_write_4bit(0x03);
	TIMER1_delay_us(150);
	
	_LCD_write_4bit(0x02);
	
	///////////////////////////////
	_LCD_write_8bit(0x28);
	TIMER1_delay_us(53);
	
	_LCD_write_8bit(0x08);
	TIMER1_delay_us(53);

	_LCD_write_8bit(0x01);
	TIMER1_delay_us(3000);

	_LCD_write_8bit(0x06);
	TIMER1_delay_us(3000);

	_LCD_write_8bit(0b00001101);
	TIMER1_delay_us(53);
}

void LCD_init_Pins() {
	
	// LCD: D4 ~ D7 -> PA0 ~ PA3 -> Arduino Pin 22 ~ 25
	DDRA |= _BV(PA0) | _BV(PA1) | _BV(PA2) | _BV(PA3);
	
	// LCD: RS -> PE4 -> 3
	// LCD: EN -> PE5 -> 2
	DDRB |= _BV(LCD_RS) | _BV(LCD_EN);
}



// High level commands
void LCD_moveCursor(uchar _dest_x, uchar _dest_y) {
	uchar mask = 0x80;
	mask |= ( (_dest_x << 6) & 0xF0) | (_dest_y & 0x0F);
	_LCD_write_8bit(mask);
	TIMER1_delay_us(53);
}

void LCD_writeCharacter(uchar _raw_char) {
	// Send upper 4 bits
	PORTA = _raw_char >> 4;
	// RS high, EN high
	LCD_RS_set_HIGH;
	LCD_EN_set_HIGH;
	// Delay 1 us
	TIMER1_delay_us(1);
	// EN low
	LCD_EN_set_LOW;
	TIMER1_delay_us(1);
	
	
	// Send lower 4 bits
	PORTA = _raw_char & 0x0F;
	// RS high, EN high
	LCD_RS_set_HIGH;
	LCD_EN_set_HIGH;
	// Delay 1 us
	TIMER1_delay_us(1);
	// EN low
	LCD_EN_set_LOW;
	TIMER1_delay_us(46);
}

void LCD_writeString(const char *_string) {
	while (*_string != '\0')
	{
		LCD_writeCharacter(*_string);
		++_string;
	}
}



// Low level commands
void _LCD_write_4bit(uchar _data_raw) {
	PORTA = _data_raw >> 4;
	_LCD_write_pulse();
}

void _LCD_write_8bit(uchar _data_raw) {
	// Send upper 4 bits first
	PORTA = _data_raw >> 4;
	LCD_RS_set_LOW;
	_LCD_write_pulse();
	
	// Send lower 4 bits
	PORTA = _data_raw & 0x0F;
	_LCD_write_pulse();
}

void _LCD_write_pulse() {
	// Pull EN low
	LCD_EN_set_LOW;
	
	// Delay 1 us
	TIMER1_delay_us(1);
	
	// Pull EN high
	LCD_EN_set_HIGH;
	
	// Delay at least 45 ns
	TIMER1_delay_us(1);
	
	// Pull EN low
	LCD_EN_set_LOW;
	
	// Delay at least 37 us
	TIMER1_delay_us(70);
}