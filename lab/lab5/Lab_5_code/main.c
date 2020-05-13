#define F_CPU 16000000UL


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include "usart.h"
#include "i2c.h"

uint8_t Data_H = 0;
uint8_t Data_L = 0;
int16_t Data[3];
char buffer[5];

int main(void) {
	init_usart();
	initI2C();
	StartI2C_Trans(0x53);
	write(0x2D);
	write(0x08);
	StopI2C_Trans();
	
	while (1)
	{
		_delay_ms(1000);
		
		// read x data: LSB
		Read_from(0x53, 0x32);
		Data_H = Read_data();
		// read x data: MSB
		Read_from(0x53, 0x33);
		Data_L = Read_data();
		// merge MSB with LSB
		Data[0] = (Data_L << 8) | Data_H;
		
		// read y data: LSB
		Read_from(0x53, 0x34);
		Data_H = Read_data();
		// read y data: MSB
		Read_from(0x53, 0x35);
		Data_L = Read_data();
		// merge MSB with LSB
		Data[1] = (Data_L << 8) | Data_H;
		
		// read z data: LSB
		Read_from(0x53, 0x36);
		Data_H = Read_data();
		// read z data: MSB
		Read_from(0x53, 0x37);
		Data_L = Read_data();
		// merge MSB with LSB
		Data[2] = (Data_L << 8) | Data_H;
		
		
		// print the content of xyz data
		usart_sendStr2("X: ");
		itoa(Data[0], buffer, 10);
		usart_sendStr2(buffer);
		usart_sendChar('\n');
		
		usart_sendStr2("Y: ");
		itoa(Data[1], buffer, 10);
		usart_sendStr2(buffer);
		usart_sendChar('\n');
		
		usart_sendStr2("Z: ");
		itoa(Data[2], buffer, 10);
		usart_sendStr2(buffer);
		usart_sendStr2("\n\n\n");
		
	}
	
}
