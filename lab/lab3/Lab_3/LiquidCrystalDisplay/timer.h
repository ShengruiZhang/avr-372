/*
	Author: Shengrui Zhang
	NetID: shengruizhang
	Date of publish: March 2019
	
		ECE 372 - Lab 3: Liquid Crystal Display
		
		Header for 16-bit Timer1
		
*/

#ifndef TIMER_H_
#define TIMER_H_

typedef unsigned int uint;

void TIMER1_init();
void TIMER1_delay_us(uint _delay_length);

#endif