#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "global_macro.h"
#include "timer.h"

int main(void)
{
	DDRB |= 1 << DDB7;	// PB7 as output
	
	//init_timer_16(CTC);	// For now, use CTC as test
	init_timer_8(CTC);
	
    while (1)
	
	return 0;
}

