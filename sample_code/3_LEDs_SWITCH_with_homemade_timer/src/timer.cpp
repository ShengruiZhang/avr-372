// Author:         
// Net ID:         
// Date:           
// Assignment:     Lab 1 example for you with homemade timer
//----------------------------------------------------------------------//

#include <avr/io.h>
#include "timer.h"

/* Initialize timer 0, use CTC mode */
void init_Timer0(){ //Setting timer 0 into CTC mode 
TCCR0A &= ~( 1 << WGM00 ); //Place 0 into WGM00 & WGM02, then a 1 into WGM01
TCCR0A |=  ( 1 << WGM01 );
TCCR0B &= ~( 1 << WGM02 );
}

//1 millisecond delay
void delayMS( int delay) {
int count = 0;

// calculate value goes in OCR0A for a 1 ms delay
// OCR0A = (Td * freq)/ Prescaler
// freq = 16 Mhz, Td = 1 ms, Prescaler = 64 
 OCR0A = 250;
while (count < delay){
 // set the flag down (remember to set the flag down we set a logic 1)
TIFR0 |=  (1 << OCF0A);
// clear the counter
TCNT0 = 0;
// turn the clock on with the prescaler of 64 
// Table 16-9 in datasheet CS00 = 1, CS01 = 1, CS02 = 0
TCCR0B |= (1<<CS00) | (1<<CS01); 
TCCR0B &= ~ (1<<CS02); 
// while flag is down do not do anything
while ( ! (TIFR0 & (1 << OCF0A)));
// exit when flag is up and turn the clock off
//TCCR0B &= ~ ((1<<CS02) | (1<<CS01) | (1<<CS00)) ;

count++;
}

}





  

