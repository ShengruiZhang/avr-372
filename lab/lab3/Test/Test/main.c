// Author:
// Net ID:
// Date:
// Assignment:     Lab 3
//
// Description: This file contains a programmatic overall description of the
// program. It should never contain assignments to special function registers
// for the exception key one-line code such as checking the state of the pin.
//
// Requirements:
//----------------------------------------------------------------------//
#define F_CPU 16000000UL
#include <avr/io.h>
#include "lcd.h"
#include "timer.h"


int main(){

  // Initialize timer, LCD, and write Hello!
  initTimer1();
  initLCD();
  moveCursor(0, 4);
  writeString("Fucked");
  //writeCharacter(0b00110000);

  /*
  * No state machine this time around.
  */
  while(1){

  }

  return 0;
}
