#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "led.h"

#define SHORT_DELAY 100  // define the short delay for 100 ms
#define LONG_DELAY 500 // define the long delay for 500 ms

volatile unsigned int LEDNUM = 0;
volatile unsigned int direction = 0;

int main() {
	
	initLED();
	
	// Set direction for Button pin as input
	DDRB &= ~ ( _BV(0) );
	// Enable the pull-up resistor
	PORTB |= _BV(0);

	while(1)
	{
		if( ! (PINB & (1 << PINB0) ) ){  // if switch is pressed SHORT_DELAY
			testLED(LEDNUM);              // start the LED sequence
			_delay_ms(SHORT_DELAY); //delay function built into add on library
			turnOffLED(LEDNUM);
			turnOffLED(LEDNUM + 4);
		}
		else{                    // if switch is not pressed LONG_DELAY
			testLED(LEDNUM);             // start the LED sequence
			_delay_ms(LONG_DELAY); //delay function built into add on library
			turnOffLED(LEDNUM);
			turnOffLED(LEDNUM + 4);
		}
		
		if (LEDNUM == 3) {  // checking for the end of the string
			direction = 1; //  change the direction
		}
		else if (LEDNUM == 0) {
			direction = 0;  // otherwise increment LED light
		}
		
		if (direction == 1)
		{
			--LEDNUM;
		}
		else {
			++LEDNUM;
		}
	}
	
	return 0;
}
