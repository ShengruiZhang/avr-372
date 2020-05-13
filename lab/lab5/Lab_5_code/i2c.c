/*
 * i2c.c
 *
 * Created: 2020-05-03 19:31:22
 *  Author: sheng
 */ 
#include <avr/io.h>
#include "i2c.h"
void initI2C() {
	
	
	TWSR |= (1 << TWPS0);  // prescaler power = 1
	TWSR &= ~(1 << TWPS1); // prescaler power = 1
	TWBR = 0xC6; // bit rate generator = 10k  (TWBR = 198)

	TWCR |= (1 << TWINT )| (1 << TWEN); // enable two wire interface

}


void StartI2C_Trans(unsigned char SLA) {
	// this function initiates a start condition and calls slave device with SLA
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // clear TWINT, intiate a start condition and enable
	wait_for_completion;
	TWDR = (SLA << 1); // slave address + write bit '0'
	TWCR = (1<<TWINT)|(1<<TWEN);  // trigger action:clear flag and enable TWI
	wait_for_completion;
}

void StopI2C_Trans() {
	// this function sends a stop condition to stop I2C transmission

	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO); //trigger action:  send stop condition

}
void write(unsigned char data){
	// this function loads the data passed into the I2C data register and transmits
	TWDR = data; //load data into TWDR register
	TWCR = (1<<TWINT)|(1<<TWEN);  // trigger action:  clear flag and enable TWI
	wait_for_completion;
}
void Read_from(unsigned char SLA, unsigned char MEMADDRESS){
	// this function sets up reading from SLA at the SLA MEMADDRESS

	StartI2C_Trans(SLA);
	
	write(MEMADDRESS);
	
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // restart to switch to read mode
	wait_for_completion;
	TWDR = (SLA << 1) | 0x01; // 7 bit address for slave plus read bit
	TWCR = (1 << TWINT) | (1 << TWEN)| (1 << TWEA);// trigger with master sending ack
	wait_for_completion;
	TWCR = (1<< TWINT) | (1 << TWEN);  // master can send a nack now
	wait_for_completion;
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); // Stop condition
	// after this function is executed the TWDR register has the data from SLA that Master wants to read
}

unsigned char Read_data() // Returns the last byte  from the data register
{

	return TWDR;
}
