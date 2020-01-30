#define F_CPU 16000000UL

typedef unsigned int uint;
typedef unsigned char uchar;

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	// Set PB7 as output
	//DDRB |= _BV(DDB7);
	DDRB |= 1 << DDB7;
	
    while (1) 
	{
		PORTB &= ~ (1 << PORTB7);
    }
}
