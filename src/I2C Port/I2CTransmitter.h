/*
 * I2CTransmitter.cpp
 *
 * Created: 5/20/2017 6:13:05 PM
 *  Author: fairenough
 */ 
#ifndef _I2C_TRANSMITTER_H_
#define _I2C_TRANSMITTER_H_

#include "Writable.h"
#include <avr/io.h>
#include "avrtwi.h"

class I2CTransmitter : public Writable
{
	public:
		int8_t writeBytes(uint8_t* buffer, uint8_t length);
		
	private:
		int8_t writeByte(uint8_t byte);
};

#endif