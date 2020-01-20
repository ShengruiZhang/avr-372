// Dale Hetherington
// ECE 372A Fall 19
// Assignment:  Classroom example program
//
// Description: Initializing LEDS using PORTB5 and PORTB4
//----------------------------------------------------------------------

#include <avr/io.h>
#include "led.h"

void initLEDs()  {

    //DDRBBXn set pin direction as output
    DDRB |=  (1<<DDB5) | (1<<DDB4);
    PORTB |= (1<<PORTB4);

}
    // toggle led PORTB5 and PORTB4 pins
    void Toggle_LEDs()  {
        PORTB  ^=  (1 << PORTB4) | (1 << PORTB5);

    }
  /* TURNOFF LED PORTS
void TurnOFF_LEDs() {

PORTB ^= (1 << PORTB5);
}
*/