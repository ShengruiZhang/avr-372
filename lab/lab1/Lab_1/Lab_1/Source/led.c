
#include <avr/io.h>
#include "led.h"

// initLED which returns void and takes no parameters
void initLED() {
	DDRC |= _BV(0) | _BV(1) | _BV(2) | _BV(3);
	DDRC |= _BV(4) | _BV(5) | _BV(6) | _BV(7);
}

// turnOnLED which returns void and takes in an unsigned int parameter called led
void turnOnLED(unsigned int led) {
	PORTC |= _BV(led);
}

// turnOffLED which returns void and takes in an unsigned int parameter called led
void turnOffLED(unsigned int led) {
	PORTC &= ~ (_BV(led)); 
}

// testLED which returns void and takes in an unsigned int parameter called led
void testLED(unsigned int led) {
	turnOnLED(led);
	turnOnLED(led + 4);
}
