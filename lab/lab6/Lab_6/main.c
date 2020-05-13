/*
 * Main Function
 *
 * Timer1 used to delay milliseconds
 * Timer3 used to generate PWM signal for buzzer
 *
 * Author: Shengrui Zhang
 * 			Zepeng Cai
 * 			
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <math.h>
#include "global_macro.h"

#include "usart.h"
#include "timer.h"
#include "pwm.h"
#include "switch.h"
#include "spi.h"

#define ACCEL_THRESHOLD_X 150
#define ACCEL_THRESHOLD_Y 150
#define ACCEL_THRESHOLD_Z 200

char c_buffer[10] = {0};
int16_t Data[3] = {65535};
uint8_t Data_raw[6] = {255};

int main(void)
{
	init_timer_1(_Timer_Mode_CTC);
	init_timer_3(_Timer_Mode_FastPWM);
	init_button_PD0();
	init_usart();
	init_SPI_Master();
	sei();
	
	// Sensor: Set range +/- 4Gs
	SPI_Writing(0x31, 0x01);
	
	// Sensor: Enter measuring mode
	SPI_Writing(0x2D, 0x08);
	
	// mute buzzer at start
	Timer_3_SetWidth(0);
	
    while (1) 
    {
		// Get data from sensor
		SPI_Reading_MB(0x32, 6, Data_raw);
		
		// Merge Data
		Data[0] = (Data_raw[1] << 8) | Data_raw[0];
		Data[1] = (Data_raw[3] << 8) | Data_raw[2];
		Data[2] = (Data_raw[5] << 8) | Data_raw[4];
		
		// Display result
		usart_sendStr2("X: ");
		itoa(Data[0], c_buffer, 10);
		usart_sendStrln(c_buffer);
		
		usart_sendStr2("Y: ");
		itoa(Data[1], c_buffer, 10);
		usart_sendStrln(c_buffer);
		
		usart_sendStr2("Z: ");
		itoa(Data[2], c_buffer, 10);
		usart_sendStrln(c_buffer);
		usart_sendChar('\n');
		
		/* Compare with threshold value,
			trigger buzzer if exceeded */
		if ( abs(Data[0]) >= ACCEL_THRESHOLD_X ||
				abs(Data[1]) >= ACCEL_THRESHOLD_Y ||
				abs(Data[2]) >= ACCEL_THRESHOLD_Z )
		{
			Timer_3_SetWidth(0.1);
		}
		
		Timer_1_delay_ms(1000);
    }
}

ISR(INT0_vect) {
	// When button is pressed, mute the buzzer
	Timer_3_SetWidth(0);
}
