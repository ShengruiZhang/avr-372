/*
 * Implementation - Serial using USART
 *
 * Created: 2020-04-25 04:10:50
 * Author:	Shengrui Zhang
			Zepeng Cai
 */ 

#include <avr/io.h>

#include "usart.h"

/* The initialization of USART0, it is used
	to transmit data to terminal */
void init_usart() {
	
	UBRR0H = BRC >> 8;       //set upper 3bit of UBRR0
	
	UBRR0L = BRC;             //set lower 8bit of UBRR0
	
	UCSR0B |= (1<<TXEN0) | (1<<TXCIE0);   // enable the transmitter and finish interrupt
	
	//  asynchronous mode
	UCSR0C &= ~(1<<UMSEL01);
	UCSR0C &= ~(1<<UMSEL00);
	
	// no parity
	UCSR0C &= ~(1<<UPM01);
	UCSR0C &= ~(1<<UPM00);
	
	// 1 Stop bit
	UCSR0C &= ~(1<<USBS0);
	
	// 8 data bits
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
}

//sending one byte/ one char to USART 
void usart_sendChar(char _c) {     
	while(!(UCSR0A&(1<<UDRE0)));       //until UDR0 is empty 
	UDR0 = _c;
}

//method #1 send string to USART 
void usart_sendStr(char _string[]) {
	unsigned char temp = 0;
	uint8_t char_index = 0;
	
	while ( (temp=_string[char_index])!=0 ){
		while(!(UCSR0A&(1<<UDRE0)));   // until UDR0 is empty
		UDR0 = temp;
		++char_index;	// move to next char
	}
}

// use pointer pass string and send string to USART
void usart_sendStr2(char *_string) {
	uint8_t char_index = 0;
	while ( _string[char_index] != 0 ){
		while(!(UCSR0A & _BV(UDRE0)));  // until UDR0 is empty 
		UDR0 = _string[char_index];
		++char_index;	// move to next char
	}
}