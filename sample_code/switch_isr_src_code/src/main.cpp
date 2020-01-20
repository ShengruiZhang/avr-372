// Author:         
// Net ID:         
// Date:
// Assignment:
//
// Description: Main for switch and Led using external interrupt
//--------------------------------------------------------------//
#include <Arduino.h>
#include <avr/io.h>
#include "led.h"
#include "switch.h"

int main() {

  initSwitch();    // initialize devices
  initLED();
  sei(); // enable global interrupts

  while(1){

  }

  return 0;
}

// write ISR for switch
ISR(PCINT0_vect){
  PORTB ^= (1 << PORTB7);
}
