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
	_delay_ms(50);
	
	// Set RS and EN low to begin commands
	//LCD_RS_set_LOW;
	//LCD_EN_set_LOW;
	
	_LCD_write_4bit(0x03);
	_delay_us(4100);
	
	_LCD_write_4bit(0x03);
	_delay_us(100);
	
	_LCD_write_4bit(0x03);
	_delay_us(100);
	
	_LCD_write_4bit(0x02);
	_delay_us(100);


	///////////////////////////////
	_LCD_write_8bit(0x28);
	_delay_us(53);
	
	_LCD_write_8bit(0x08);
	_delay_us(53);

	_LCD_write_8bit(0x01);
	_delay_us(3000);

	_LCD_write_8bit(0x06);
	_delay_us(3000);

	_LCD_write_8bit(0b00001101);
	_delay_us(53);
}

void LCD_init_Pins() {
	
	// LCD: D4 ~ D7 -> PA0 ~ PA3 -> Arduino Pin 22 ~ 25
	DDRA |= _BV(PA0) | _BV(PA1) | _BV(PA2) | _BV(PA3);
	
	// LCD: RS -> PE4 -> 3
	// LCD: EN -> PE5 -> 2
	DDRE |= _BV(LCD_RS) | _BV(LCD_EN);
}


// High level commands
void LCD_moveCursor(uchar _dest_x, uchar _dest_y) {
	uchar mask = 0x80;
	mask |= ( (_dest_x << 6) & 0xF0) | (_dest_y & 0x0F);
	_LCD_write_8bit(mask);
	_delay_us(53);
}

void LCD_writeCharacter(uchar _raw_char) {
	// Send upper 4 bits
	PORTA = _raw_char >> 4;
	// RS high, EN high
	PORTE|=_BV(LCD_RS);
	PORTE|=_BV(LCD_EN);
	// Delay 1 us
	_delay_us(1);
	// EN low
	PORTE&=~(_BV(LCD_EN));
	_delay_us(1);
	
	
	// Send lower 4 bits
	PORTA = _raw_char & 0x0F;
	// RS high, EN high
	PORTE|=_BV(LCD_RS);
	PORTE|=_BV(LCD_EN);
	// Delay 1 us
	_delay_us(1);
	// EN low
	PORTE&=~(_BV(LCD_EN));
	_delay_us(46);
	
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
	// Only preserve the lower 4 bit of data
	PORTA = _data_raw & 0x0F;
	
	// Pull RS low
	PORTE&=~(_BV(LCD_RS));
	// EN high
	PORTE|=_BV(LCD_EN);
	_delay_us(1);
	// EN low
	PORTE&=~(_BV(LCD_EN));
}

void _LCD_write_8bit(uchar _data_raw) {
	// Send upper 4 bits first
	PORTA = _data_raw >> 4;
	
	// Pull RS to low
	PORTE&=~(_BV(LCD_RS));
	// Set EN to high
	PORTE|=_BV(LCD_EN);
	// Delay 1 ms, and pull EN low
	_delay_us(1);
	PORTE&=~(_BV(LCD_EN));
	_delay_us(1);
	
	// Send lower 4 bits
	PORTA = _data_raw & 0x0F;
	// Set EN to high
	PORTE|=_BV(LCD_EN);
	// Delay 1 ms
	_delay_us(1);
	// Pull EN low
	PORTE&=~(_BV(LCD_EN));
}

void _LCD_write_pulse() {
	// Pull EN low
	PORTE &= ~( _BV(LCD_EN) );
	
	// Delay 1 us
	_delay_us(1);
	
	// Pull EN back to high
	PORTE |= _BV(LCD_EN);
	
	// Delay at least 45 ns
	_delay_us(1);
	
	// Pull EN low again
	PORTE &= ~( _BV(LCD_EN) );
	
	// Delay at least  37 us
	_delay_us(100);
}

void LCD_sendCommand(uchar _command_raw) {
	LCD_send(_command_raw, 0);
}
