/*
 * I2CTransmitter.cpp
 *
 * Created: 5/20/2017 6:16:40 PM
 *  Author: fairenough
 */ 

#include "I2CTransmitter.h"

#ifndef extern "C" { void __cxa_pure_virtual() { while (1); }}
#endif

int8_t I2CTransmitter::writeByte(uint8_t byte)
{
	uint8_t   twStatusRegister;
	
	// send data to the previously addressed device
	TWDR = byte;
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits
	twStatusRegister = TW_STATUS & 0xF8;
	if( twStatusRegister != TW_MT_DATA_ACK)
	{
		return I2C_TRANSMIT_NAK;
	}
	return I2C_OK;
}

int8_t I2CTransmitter::writeBytes(uint8_t* buffer, uint8_t length)
{
	if (buffer == NULL || length < 1)
	{
		return I2C_INVALID_PARAMETER;
	}
	
	for (uint8_t index = 0; index < length; ++index)
	{
		if (this->writeByte(buffer[index]) != I2C_OK)
		{
			return I2C_TRANSMIT_NAK;
		}
	}	
	return I2C_OK;
}

