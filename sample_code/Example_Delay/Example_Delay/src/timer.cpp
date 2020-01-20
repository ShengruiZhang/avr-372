#include <avr/io.h>
#include "timer.h"

/* Initialize timer 0, use CTC mode
*/
void initTIMER0(){
    

//Setting timer 0 into CTC mode by placing 0 into WGM00 & WGM02, then a 1 into WGM01

TCCR0A &= ~(1 << WGM00);
TCCR0A |= (1 << WGM01);
TCCR0B &= ~(1 << WGM02);
}


//1 millisecond delay

void delayMS(unsigned char delay){

// calculate value goes in OCR0A per ms delay (OCR0A = 15.625) and a 1024 prescaler
OCR0B = 249 * delay; 
// set the flag down (remember to set the flag down we set a logic 1)
TIFR0 |= (1 << OCF0B);
// clear the timer 
TCNT0 = 0; 
// turn on the timer by setting the prescaler to 64
TCCR0B |= (1 << CS01) | (1 << CS00);
TCCR0B &= ~(1 << CS02); 

// while flag is down do not do anything
while (!(TIFR0 & (1 << OCF0B)));
// exit while loop when flag is up

// turn clock off
TCCR0B &= ~((1 << CS02) | (1 << CS01)  | (1 << CS00));
}     