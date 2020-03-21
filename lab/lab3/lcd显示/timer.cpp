// Author: 
// Net ID: 
// Date: 
// Assignment: Lab 3
//----------------------------------------------------------------------//

#include "timer.h"

/* Initialize timer 1, you should not turn the timer on here. Use CTC mode  .*/
void initTimer1(){
    TCCR1A &= ~(1 << WGM10);  // set CTC MODE
    TCCR1A |= (1 << WGM11);
    TCCR1B &= ~(1<<WGM12); 
    TCCR1B |=(1<<CS10); // SET prescale to 64
    OCR1A = 16;
}

/* This delays the program an amount specified by unsigned int delay.
*/
void delayUs(unsigned int delay){
   unsigned int delayCnt = 0;
    TIFR1 |= (1<<OCF1A); // flag down
    TCNT1 = 0;
    while(delayCnt<delay){
        if(TIFR1&(1<<OCF1A)){
            delayCnt++;
            TIFR1 |=(1<<OCF1A);
        }
    }
}
