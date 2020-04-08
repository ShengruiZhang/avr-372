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
#include "button.h"

volatile uint ADC_raw = 0;
volatile enum Button_State Button_PD2 = _State_Button_released;

int main(void)
{
	// On-board LED
	DDRB |= _BV(DDB7);
	
	// ADC input pin
	DDRF &= ~_BV(PF0);
	
	// Timer PWM waveform gen. pins
	DDRB |= _BV(DDB5) | _BV(DDB6);
	DDRE |= _BV(DDE3) | _BV(DDE4);
	
	init_ADC_0();
	init_button();
	sei();
	
	init_timer_0(_Timer_Mode_CTC);
	init_timer_1(_Timer_Mode_FastPWM);
	init_timer_3(_Timer_Mode_FastPWM);
	
	while (1) 
    {
		PORTB |= _BV(PB7);
		Timer_0_delay(1000);
		PORTB &= ~_BV(PB7);
		Timer_0_delay(1000);
    }
}

ISR(ADC_vect) {
	ADC_raw = ADC;
	
	// ADC output range 0 ~ 1024 (10-bit)
	Timer_1_SetWidth(ADC_raw);
	Timer_3_SetWidth(ADC_raw);
	ADC_Start();
}