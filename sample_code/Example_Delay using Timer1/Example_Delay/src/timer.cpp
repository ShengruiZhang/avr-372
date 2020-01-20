#include <avr/io.h>
#include "Arduino.h"
#include "timer.h"

/* Initialize timer 0, use CTC mode
*/
void initTIMER0(){
    

//Setting timer 0 into CTC mode by placing 0 into WGM00 & WGM02, then a 1 into WGM01

TCCR0A &= ~(1 << WGM00);
TCCR0A |= (1 << WGM01);
TCCR0B &= ~(1 << WGM02);
}

void initTIMER1(){
 //set timer 1 into CTC mode by placing 1 into WGM12.  all others are zero
    TCCR1A &= ~(1 << WGM10);
	TCCR1A &= ~(1 << WGM11);
	TCCR1B|= (1 << WGM12);
	TCCR1B &= ~(1 << WGM13);


// start the clock with prescaler 8 and OCR1A = 20000
    TCCR1B &= ~((1 << CS12)| (1 << CS10));
    TCCR1B |=  (1 << CS11);
     //OCR1A = 20000;
    OCR1AH = 0x4E;
    OCR1AL = 0x20;


// start the clock with prescaler 64 and OCR1A = 2500
   //TCCR1B &= ~(1 << CS12);
   // TCCR1B |=  (1 << CS11) | (1 << CS10);

    //OCR1AH = 0x09;
    //OCR1AL = 0xC4;
    //OCR1A  = 2500;
    //
   
}
//1 millisecond delay for TIMER 0

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


// 10 ms delay basis using Timer1
void timer1delay_10ms(unsigned char delay) {


unsigned int count = 0;


// set the counter to 0
TIFR1 |= (1 << OCF1A);
TCNT1 = 0;


while (count < delay){
    if ((TIFR1 & (1 << OCF1A))){ //increment every time the timer raises a flag (counting 10 ms flags)
    
			count++;

			TIFR1 |= (1 << OCF1A); 	//set timer to start counting again
}

} 
}   