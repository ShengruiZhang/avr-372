/*
 * Header - USART
 *
 * Created: 2020-04-25 04:26:36
 * Author:	Shengrui Zhang
			Zepeng Cai
 */ 
#ifndef USART_H
#define	USART_H

#define F_CPU 16000000UL

#define BAUD 9600    //baud rate 

#define BRC ( (F_CPU/16/BAUD) - 1 )  //  value for UBRR0

void init_usart();   //initialize transmitter of USART    9600, 0, 1

void usart_sendChar(char _c);    //sending one byte/ one char to USART

void usart_sendStr(char _string[]);  //method #1 send string to USART 

void usart_sendStr2(char *_string);  //method #2 send string to USART

void usart_sendStrln(char *_string); //same as sendStr2, plus newline

#endif