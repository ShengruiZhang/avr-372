#include <avr/io.h>
#include "Arduino.h"
#include "timer.h"
#include "led.h"
#define DELAY_TIME 10

int main ()    {
   
    initLEDs();    // Initialize the LED
    initTIMER0();  // Initialize TIMER0
    initTIMER1();  // Initialize TIMER1



while(1)  {

  timer1delay_10ms(100);
  
     Toggle_LEDs();

}
return 0;
}