// Author:         
// Net ID:         
// Date:           
// Assignment:    Lab1 example for you
//----------------------------------------------------------------------//
#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

// initLED which returns void and takes no parameters
void initLED(){
  //Initialize physical pins on the development board to outputs.
  //PORTC0 is header pin 37 on the development board.
  //PORTC2 is header pin 35.
  //PORTC4 is header pin 33.
  //PORTC6 is header pin 31.
  // set data direction register (DDRC) bits C0,C2, C4, C6 to output
  DDRC |= (1<< DDC0) |(1<< DDC2) |(1<< DDC4) | (1 << DDC6);

}

// turnOnLED which returns void and takes an integer parameter
void turnOnLED(unsigned int LEDNUM){
switch(LEDNUM) {
      case 1:
      PORTC |= (1 << PORTC0); // turnon LED at header pin 37
      break;

      case 2:
      PORTC |= (1 << PORTC2); // turnon LED at header pin 35
      break;

      case 3:
      PORTC |= (1 << PORTC4); // turnon LED at header pin 33
      break;

      case 4:
      PORTC |= (1 << PORTC6); // turnon LED at header pin 31
      break;
      }
      
}

// turnOffLED which returns void
void turnOffLED(unsigned int LEDNUM){
 switch(LEDNUM) {
       
     case 1:
         PORTC &= ~(1 << PORTC0); // turnoff LED at header pin 37
      break;

      case 2:
        PORTC &= ~(1 << PORTC2); // turnoff LED at header pin 35
      break;

      case 3:
         PORTC &= ~(1 << PORTC4); // turnoff LED at header pin 33
      break;

      case 4:
          PORTC &= ~(1 << PORTC6); // turnoff LED at header pin 31
      break;
      }
}
void testLED(unsigned int LEDNUM){

      turnOnLED(LEDNUM); // turn on assigned led
      if (LEDNUM == 1) // check for special case led at the beginning;
      {
            turnOffLED(4); // special case turn off led at the end;
      }
      else
      {
            turnOffLED(LEDNUM -1); // turn off led previously turned on;
      }
}