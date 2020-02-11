#include <avr/io.h>

#include "global_macro.h"
#include "led.h"

void init_LED_PA() {
	 DDRA |= (1 << DDA0) | (1 << DDA1) | (1 << DDA2) | (1 << DDA3);
}

void LED_set_status(uchar led_status_bit) {
	PORTA = (PORTA & 0xF0) | (0x0F & led_status_bit);
}
