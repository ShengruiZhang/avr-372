// Author:         
// Net ID:         
// Date:           
// Assignment:     Lab 1 example for you with homemade timer
//----------------------------------------------------------------------//

#include <avr/io.h>

// initSwitch returns void and takes no parameters
void initSwitch(){
  // Set switch header pin 1 as pull-up enabled input
  DDRE &= ~(1 << DDE1);  //data direction register set for input
  PORTE |= (1 << PORTE1);  //pullup resistor on PORTE1 inside microcontroller enabled
  
}
