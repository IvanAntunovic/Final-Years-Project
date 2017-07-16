/*
 * I2CReceiver.cpp
 *
 * Created: 5/20/2017 7:08:36 PM
 *  Author: fairenough
 */ 
#ifndef _I2C_RECEIVER_H_
#define _I2C_RECEIVER_H_

#include "Readable.h"
#include <avr/io.h>
#include "avrtwi.h"

class I2CReceiver : public Readable 
{
	public:
		int8_t readBytes(uint8_t* buffer, uint8_t length);
		
	private:
		int8_t readByte(uint8_t* byte, uint8_t receiveSignal);
};

#endif