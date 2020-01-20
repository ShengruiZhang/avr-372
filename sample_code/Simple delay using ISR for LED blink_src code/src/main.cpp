// Author:         
// Net ID:         
// Date:
// Assignment:
//
// Description: File description
//----------------------------------------------------------------------//
#include <Arduino.h>
#include <avr/io.h>
#include "timer.h"
#include "led.h"

// create a count variable
volatile unsigned int count = 0;

int main(){

  initTimer0();   // initialize devices
  initLED();
  sei();          // enable global interrupts

  while(1){

  }

  return 0;
}

// write the ISR for CTC mode
ISR(TIMER0_COMPA_vect){
  if(count < 1000){
    count++;
  }
  else{
    count = 0;
    PORTB ^= (1 << PORTB7);
  }
}
