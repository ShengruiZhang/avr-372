#include <avr/io.h>
#include "lcd.h"
#include "timer.h"


int main(){

  // Initialze timer, LCD, and write Hello!
  initTimer1();
  initLCD();
  moveCursor(0, 4);
  writeString("Hello!");

  /*
  * No state machine this time around.
  */
  while(1){

  }

  return 0;
}
