/*
 * Header - Serial Peripheral Interface
 *
 * Created: 2020-05-01 17:58:21
 *
 * Author: Shengrui Zhang
			Zepeng Cai
 */ 
#ifndef _SPI_H
#define _SPI_H

#define SPI_WRITE		0b00000000
#define SPI_READ		0b10000000
#define SPI_RW_MB		0b01000000

#define SPI_PORT		PORTB
#define SPI_PIN_SS		PB0
#define SPI_PIN_SCLK	PB1
#define SPI_PIN_MOSI	PB2

void init_SPI_Master();
void SPI_end();
uint8_t SPI_Reading(uint8_t _addr);
int16_t SPI_Reading_2Byte(uint8_t _addr);
void SPI_Reading_MB(uint8_t _addr, uint _num, uint8_t _buf[]);
void SPI_Writing(uint8_t _addr, uint8_t _data);

uint8_t SPI_transfer(uint8_t _data);

#endif