#include <avr/io.h>
#include "Arduino.h"
#include "timer.h"
#include "led.h"
#define DELAY_TIME 10

int main ()    {
   //Serial.begin(9600);
    initLEDs();    // Initialize the LED
    initTIMER0();  // Initailize TIMER0

 int count = 0;

while(1)  {
delayMS(1);  //1 ms delay
  // if count < 1000 , keep counting
  if(count < 1000){
  count++;
 
  }
  else { // otherwise reset count, print
    count = 0;
   
     Toggle_LEDs();
     //TurnOFF_LEDs();
  }

  
  //TurnON_LEDs();
  //delayMS(DELAY_TIME);  // Call delayMS function
  //TurnOFF_LEDs();
  //delayMS(DELAY_TIME);
  
  //Serial.println("I am here");
}
return 0;
}