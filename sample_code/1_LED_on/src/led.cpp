// Dale Hetherington
// January 23, 2019
// Assignment:  Classroom example program
//
// Description: Initializing LEDS using PORTB5 and PORTB4
//----------------------------------------------------------------------

#include <avr/io.h>
#include "led.h"

void initLEDs()  {

    //DDRBBXn set pin direction as output
    DDRB |=  (1<<DDB7) | (1<<DDB4);
    // PORTB5 and PORTB4 pins to one
    PORTB |= (1<<PORTB7) | (1<<PORTB4);

}