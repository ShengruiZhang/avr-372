// Author:         
// Net ID:         
// Date:           
// Assignment:     Lab 1 example for you
//----------------------------------------------------------------------//

#include <avr/io.h>
#include <util/delay.h>
#include "led.h"
#include "switch.h"
#define SHORT_DELAY 100  // define the short delay for 100 ms
#define LONG_DELAY 500 // define the long delay for 500 ms

int main(){

  initLED();                    // initialize the LED
  initSwitch();                 // initialize switch

unsigned int LEDNUM = 1;        // set counter to 1 

  while(1){
    if(!(PINE & (1 << PINE1))){  // if switch is pressed SHORT_DELAY
     
      
      testLED(LEDNUM);              // start the LED sequence 
      _delay_ms(SHORT_DELAY); //delay function built into add on library
      
    }
    else{                    // if switch is not pressed LONG_DELAY
      testLED(LEDNUM);             // start the LED sequence 
      _delay_ms(LONG_DELAY); //delay function built into add on library

    }
    
    if (LEDNUM == 4){  // checking for end of LED light string

      LEDNUM = 1; //  set LED light string back to beginning
    }

    else {
      LEDNUM ++;  // otherwise increment LED light
    }
  }

  return 0;
}
