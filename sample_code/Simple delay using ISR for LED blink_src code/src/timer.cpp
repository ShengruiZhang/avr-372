// Author:         
// Net ID:         
// Date:
// Assignment:
//
// Description: File description
//----------------------------------------------------------------------//
#include <avr/io.h>
#include "timer.h"

// Initialize timer 0 to have a 1 ms period.
void initTimer0(){
  // Set the mode to be CTC
  TCCR0A   &=   ~(1 << WGM00);
  TCCR0A   |=    (1 << WGM01);
  TCCR0B   &=   ~(1 << WGM02);

  // Set the pre-scalar to be 64
  TCCR0B |= (1 << CS01) | (1 << CS00);

  // Place the correct value in OCR0A
  OCR0A = 250;

  // enable the timer interrupt
  TIMSK0 |= (1 << OCIE0A);
}
