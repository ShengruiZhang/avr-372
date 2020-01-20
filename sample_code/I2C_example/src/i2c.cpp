// Initialization for I2C and a function sendatai2c that sends data using I2C
#include <Arduino.h>
#include "i2c.h"



void initI2C() 
{
  TWSR |= (1 << TWPS0);
  //TWSR |= (1 << TWPS0) | (1 << TWPS1);
  TWSR &= ~(1 << TWPS1); // prescaler = 1
  TWBR = 0xC6; // bit rate generator = 10k  (TWBR = 198)
  
  TWCR |= (1 << TWINT | 1 << TWEN); // enable two wire interface
 

  
}

void sendDataI2C(unsigned char i2c_address, unsigned char data_to_send) {
 
 TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN); // reset flag and intiate a start condition

 while (!(TWCR & (1<<TWINT)));  // wait while flag is low
 TWDR = (i2c_address << 1); //load i2c address and write bit (0)
 TWCR = (1<<TWINT)|(1<<TWEN);  // clear flag and enable TWI

 while (!(TWCR & (1<<TWINT)));
 TWDR = data_to_send;
 TWCR = (1<<TWINT)|(1<<TWEN);  // clear flag and enable TWI

 while (!(TWCR & (1<<TWINT)));
 TWCR = (1<<TWINT)|(1<<TWEN)|(1<< TWSTO); //send stop condition
}

 