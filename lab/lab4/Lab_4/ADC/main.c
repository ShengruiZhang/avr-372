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
#include <util/delay.h>

#include "timer.h"
#include "adc.h"
#include "button.h"

volatile uint ADC_raw = 0;
volatile uint Timer3_on = 0;
volatile enum Button_State Button_PD2 = _State_Button_released;

int main(void)
{
	// On-board LED
	DDRB |= _BV(DDB7);
		
	// Timer PWM waveform gen. pins
	DDRE |= _BV(DDE3) | _BV(DDE4);		// Timer3
	
	sei();
	
	init_ADC_0();
	init_button();	
	init_timer_0(_Timer_Mode_CTC);
	init_timer_3(_Timer_Mode_FastPWM);
	
	Button_PD2 = _State_Button_to_released;
	
	while (1) 
    {
		switch(Button_PD2) {
			case _State_Button_to_pressed:
			
				Timer_0_delay_ms(80);
				Button_PD2 = _State_Button_pressed;
			break;
			
			
			case _State_Button_pressed:
			
				// Button indicator on
				//PORTB |= 1 << PB7;
				PORTD |= _BV(PD3);
				break;
			
			
			case _State_Button_to_released:
			
				Timer_0_delay_ms(80);
				
				if (Timer3_on == 0)
				{
					Timer3_on = 1;
					Timer3_Toggle(1);
				}
				else if (Timer3_on == 1)
				{
					Timer3_on = 0;
					Timer3_Toggle(0);
				}
				
				Button_PD2 = _State_Button_released;
			break;
			
			
			case _State_Button_released:
			
				// Button indicator off
				PORTB &= ~(1 << PB7);
				PORTD &= ~_BV(PD3);
			break;
		}
    }
}

/*	ADC result handling */
ISR(ADC_vect) {
	ADC_raw = ADC;
	
	// ADC output range 0 ~ 1024 (10-bit)
	//Timer_1_SetWidth(ADC_raw);
	Timer_3_SetWidth(ADC_raw);
	ADC_Start();
}

/*	Button interrupt handling */
ISR(INT2_vect) {
	// Level on INT2 has changed
	// Button can be pressed or released
	if (Button_PD2 == _State_Button_released)
	{
		// Button is being pressed down, proceed to debounce
		Button_PD2 = _State_Button_to_pressed;
	}
	else if (Button_PD2 == _State_Button_pressed)
	{
		// Button is going be released, proceed to debounce
		Button_PD2 = _State_Button_to_released;
	}
}