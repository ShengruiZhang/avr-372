// Description: This file describes functions used by the timer
//----------------------------------------------------------------------//

#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include "Arduino.h"

void initTIMER0();
void initTIMER1();
void delayMS(unsigned char delay);
void timer1delay_10ms(unsigned char delay);

#endif