/*
 * Implementation - Serial Peripheral Interface
 *
 * Created: 2020-05-01 17:58:07
 *
 * Author: Shengrui Zhang
			Zepeng Cai
 */
#include <avr/io.h>
#include "global_macro.h"

#include "spi.h"

void init_SPI_Master() {
	
	/* SPI Pins:		Arduino Pin:
			SS				53
			SCLK			52
			MOSI			51
			MISO			50
	*/				
	
	PRR0 &= ~_BV(PRSPI);
	
	/* Pull SS low, PB0, Arduino Pin 53
		If master's SS is pulled low,
		master will turn into a slave */
	DDRB |= _BV(DDB0);
	PORTB |= _BV(PB0);
	
	/* Set SCK, MOSI as output,
		MISO (Arduino Pin 50) is automatically overridden
		to INPUT by SPI module */
	DDRB |= _BV(DDB1);	// SCK: Arduino Pin 52
	DDRB |= _BV(DDB2);	// MOSI: Arduino Pin 51
	
	/* SPI Control Reg.
		//Enable SPI Interrupt
		Enable SPI
		Select SPI Master
		Clock Polarity 1
		Clock Phase 1
		128 Frequency Division factor */
	SPCR = _BV(SPE) | _BV(MSTR) |
			_BV(CPOL) | _BV(CPHA) | _BV(SPR1) | _BV(SPR0);
	
	// Clear interrupt flat by reading SPSR and SPDR
	if( SPSR | 0xFF );
	if( SPDR | 0xFF );
	
	/* SPI initialization finished */
}

void SPI_end() {
	
	// Turn off SPI interface by clearing SPE
	SPCR &= ~_BV(SPE);
}

// SPI Reading, read 1 byte at a time
uint8_t SPI_Reading(uint8_t _addr) {
	uint8_t _temp = 0;
	
	// Pull SS low to select slave
	SPI_PORT &= ~_BV(SPI_PIN_SS);
	
	SPI_transfer(_addr | SPI_READ);
	_temp = SPI_transfer(_addr);
	
	// Pull SS high to free bus
	SPI_PORT |= _BV(SPI_PIN_SS);
	
	return _temp;
}

/* SPI Reading 2 consecutive registers
	Set the MB bit following the R/W byte,
	the sensor sends the data of consecutive registers */
int16_t SPI_Reading_2Byte(uint8_t _addr) {
	
	uint8_t _temp[2] = {255, 255};
	
	_addr |= SPI_READ;
	_addr |= SPI_RW_MB;
		
	// Pull SS low to select slave
	SPI_PORT &= ~_BV(SPI_PIN_SS);
	
	// Set MB bit along w/ read addr
	SPI_transfer(_addr);
	
	// Receive data
	_temp[0] = SPI_transfer(0x00);	// LSB of the data
	_temp[1] = SPI_transfer(0x00); // MSB of the data
	
	// Pull SS high to release
	SPI_PORT |= _BV(SPI_PIN_SS);
	
	// Return 2 byte of data, 16-bit
	return (_temp[1] << 8 | _temp[0]);
}

/* Reading multiple bytes for consecutive registers */
void SPI_Reading_MB(uint8_t _addr, uint _num, uint8_t _buf[]) {
	
	// Set R, MB bit
	_addr |= SPI_READ;
	_addr |= SPI_RW_MB;
	
	// Pull SS low to select slave
	SPI_PORT &= ~_BV(SPI_PIN_SS);
	
	// Set addr of first byte
	SPI_transfer(_addr);
	
	for (uint i = 0; i < _num; ++i)
	{
		_buf[i] = SPI_transfer(0x00);
	}
	// Pull SS high to free bus
	SPI_PORT |= _BV(SPI_PIN_SS);
}

/* SPI Writing, write 1 byte at a time
	Data sent by slave is ignored during writing */
void SPI_Writing(uint8_t _addr, uint8_t _data) {
	
	// Pull SS low to select slave
	SPI_PORT &= ~_BV(SPI_PIN_SS);
	
	SPI_transfer(_addr);	// Tell slave the addr to write
	SPI_transfer(_data);	// Write the data
	
	// Pull SS high to free bus
	SPI_PORT |= _BV(SPI_PIN_SS);
}

uint8_t SPI_transfer(uint8_t _data) {
	
	// Initiating SPI transmission by putting a byte in SPDR
	SPDR = _data;
	
	// Wait for transmission
	while( (SPSR & _BV(SPIF)) == 0 );
	
	// Return SPDR if slave sent any data
	return SPDR;
}
