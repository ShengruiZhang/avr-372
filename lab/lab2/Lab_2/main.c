#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "global_macro.h"
#include "timer.h"
#include "led.h"
#include "button.h"

volatile uint _LED_frequency = 300;
volatile uint _LED_delay = 0;
volatile uint _LED_status = 0;

volatile enum LED_State _LED_Speed = _State_LED_slow;
volatile enum Button_State _Button_State_PB3 = _State_Button_released;

int main(void)
{
	sei();	// Enable global interrupt
	
	init_LED_PA();
	init_button_PA();
	
	init_timer_8();
		
    while (1)
	{
		switch(_Button_State_PB3) {
			case _State_Button_to_pressed:
				_delay_ms(30);	// Debounce
				_Button_State_PB3 = _State_Button_pressed;
			break;
			
			
			case _State_Button_pressed:
				PORTB |= 1 << PB7;	// Turn on indicator
			break;
			
			
			case _State_Button_to_released:
				_delay_ms(30);	// Debounce
				
				if (_LED_Speed == _State_LED_slow)
				{
					_LED_Speed = _State_LED_fast;
				}
				else {
					_LED_Speed = _State_LED_slow;
				}
				
				_Button_State_PB3 = _State_Button_released;
			break;
			
			
			case _State_Button_released:
				PORTB &= ~(1 << PB7);	// Turn off indicator
			break;
		}
		
		switch(_LED_Speed) {
			case _State_LED_slow:
				_LED_frequency = 700;
			break;
			
			case _State_LED_fast:
				_LED_frequency = 250;
			break;
		}
	}
}


// Timer0 Compare Match Interrupt Vector
ISR(TIMER0_COMPA_vect) {
	
	++_LED_delay;
	
	if (_LED_delay == _LED_frequency)
	{
		++_LED_status;	// Increment decimal digit
		
		if (_LED_status > 15)
		{
			_LED_status = 0;	// Reset when excesses 4 bits
		}
		
		LED_set_status(_LED_status);	// Set LEDs
	}
	else if (_LED_delay > _LED_frequency)
	{
		_LED_delay = 0;
	}
}


// Pin Change Interrupt Vector
ISR(PCINT0_vect) {
	// Button can either be pressed or released
	if (_Button_State_PB3 == _State_Button_released)
	{
		// The button is being pressed, so process to debounce
		_Button_State_PB3 = _State_Button_to_pressed;
	}
	else if (_Button_State_PB3 == _State_Button_pressed)
	{
		// The button is being released, process debounce
		_Button_State_PB3 = _State_Button_to_released;
	}
}
