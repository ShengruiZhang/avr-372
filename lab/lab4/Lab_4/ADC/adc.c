/*
 * Implementation - ADC
 *
 * Created: 2020-04-02 03:14:49
 * Author: Shengrui Zhang
 */ 

#include <avr/io.h>

#include "adc.h"

void init_ADC_5() {
	
	// Set ADC reference voltage same as AVcc
	ADMUX |= _BV(REFS0);
	
	// Set ADC5 active -> 000101
	//ADMUX |= _BV(MUX2) | _BV(MUX0);
	
	// Set ADC0 active -> 000000
	ADMUX &= ~_BV(MUX0);
	ADMUX &= ~_BV(MUX1);
	ADMUX &= ~_BV(MUX2);
	ADMUX &= ~_BV(MUX3);
	ADMUX &= ~_BV(MUX4);
	ADCSRB &= ~_BV(MUX5);
	
	// Enable ADC
	ADCSRA |= _BV(ADEN);
	
	// Generate an interrupt when 1 conversion done
	ADCSRA |= _BV(ADIE);
	
	// 128 prescaler -> 8 us clock
	ADCSRA |= _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);
	
	// Disable digital buffer
	DIDR0 |= _BV(ADC0D);
	
	ADC_Start();
}

void ADC_Start() {
	ADCSRA |= _BV(ADSC);
}