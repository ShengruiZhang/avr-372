/*
 * Lab 4
 *
 * Main Function
 *
 * Created: 2020-04-01
 * Author: Shengrui Zhang
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"
#include "adc.h"

volatile uint ADC_raw = 0.0;

int main(void)
{
	DDRB |= _BV(DDB7);
	DDRF &= ~_BV(PF0);
	
	DDRB |= _BV(DDB5) | _BV(DDB6);
	
	sei();
	
	init_timer_16(_Timer_Mode_FastPWM);
	init_ADC_5();
	
	while (1) 
    {

    }
}

ISR(ADC_vect) {
	ADC_raw = ADC;
	// ADC output range 0 ~ 1024 (10-bit)
	OCR1A = 8190 * ((float)ADC_raw / 1024);
	ADC_Start();
}