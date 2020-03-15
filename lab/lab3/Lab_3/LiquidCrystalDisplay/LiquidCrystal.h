/*
	Author: Shengrui Zhang
	NetID: shengruizhang
	Date of publish: March 2019
	
		ECE 372 - Lab 3: Liquid Crystal Display
		
		Header for Liquid Crystal
		
*/

#ifndef LIQUIDCRYSTAL_H_
#define LIQUIDCRYSTAL_H_

#define LCD_RS PE5
#define LCD_EN PE4

#define LCD_RS_set_LOW PORTE&=~(_BV(LCD_RS))
#define LCD_RS_set_HIGH PORTE|=_BV(LCD_RS)

#define LCD_EN_set_LOW PORTE&=~(_BV(LCD_EN))
#define LCD_EN_set_HIGH PORTE|=_BV(LCD_EN)

typedef unsigned int uint;
typedef unsigned char uchar;

// LCD_init is just a container for Pins and Main
void LCD_init();
void LCD_init_Pins();
void LCD_init_Main();

// Low level commands
void _LCD_write_4bit(uchar _data_raw);
void _LCD_write_8bit(uchar _data_raw);
void _LCD_write_pulse();

// Mid-level commands
void LCD_send();

// High level commands
void LCD_sendCommand(uchar _command_raw);
void LCD_writeString(const char *_string);
void LCD_writeCharacter(uchar _raw_char);
void LCD_moveCursor(uchar _dest_x, uchar _dest_y);

#endif