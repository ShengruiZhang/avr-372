// Author:
// Net ID:
// Date:
// Assignment:
//
// Description:
//----------------------------------------------------------------------//

#include "usart.h"
#include <avr/io.h>

void initUSART0(){

  // enable UDRE interrupt and enable transmit
  UCSR0B |= (1 << UDRIE0) | (1 << TXEN0);

  // set character data size to 8
  UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);

  // baud rate 9600
  UBRR0 = 103;
  
}
