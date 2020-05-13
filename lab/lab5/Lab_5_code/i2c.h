
/*
 * i2c.h
 *
 * Created: 2020-05-03 19:29:44
 *  Author: sheng
 */ 
#ifndef I2C_H
#define I2C_H

#define wait_for_completion while(!(TWCR & (1 << TWINT)));

void initI2C();
void StartI2C_Trans(unsigned char SLA);
void StopI2C_Trans();
void write(unsigned char data);
void Read_from(unsigned char SLA, unsigned char MEMADDRESS);
unsigned char Read_data();
#endif