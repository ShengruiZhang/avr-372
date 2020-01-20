// Author:         
// Net ID:         
// Date:
// Assignment:
//
// Description: switch using ISR 
//--------------------------------------------------------------//
#include <avr/io.h>
#include "switch.h"


// initialize switch using pin 11 on the development board
void initSwitch(){
  DDRB &= ~(1 << DDB5);
  PORTB |= (1 << PORTB5); // enable pull-up for PORTB5

  PCICR |= (1 << PCIE0);      // enable PCINT for 7-0
  PCMSK0 |= (1 << PCINT5);    // enable PCINT for PCINT5
}
