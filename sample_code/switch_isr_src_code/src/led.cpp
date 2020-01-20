// Author:         
// Net ID:         
// Date:
// Assignment:
//
// Description: File description
//------------------------------------------------------------
//

#include <avr/io.h>
#include "led.h"

void initLED(){
  DDRB |= (1 << DDB7);
// set PORT B7 for output
}
