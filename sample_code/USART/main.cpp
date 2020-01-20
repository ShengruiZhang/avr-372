// Author:         Dale Hetherington
// Net ID:         
// Date:
// Assignment:
//
// Description: Simple USART serial transmission
//-------------------------------------------------------------//
#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"

// create char index
unsigned int char_index = 0;

// initialize a message
char message[8] = "Hello!\n";

int main() {

  // initialize USART
  initUSART0();

  // enable global interrupts
  sei();

  // have to fill the UDR register first to get things started
  UDR0 = 'H';

  while(1){

  }

  return 0;
}

// USART ISR
ISR(USART0_UDRE_vect){
  UDR0 = message[char_index];
  if(char_index == 8){
    char_index = 0;
  }
  else{
    char_index++;
  }
}
