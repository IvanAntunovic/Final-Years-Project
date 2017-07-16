/*
 * I2CPort.cpp
 *
 * Created: 5/20/2017 6:34:51 PM
 *  Author: fairenough
 */ 
#ifndef _I2C_PORT_H_
#define _I2C_PORT_H_

#include "I2CTransmitter.h"
#include "I2CReceiver.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define SCL_CLOCK 100000UL

class I2CPort
{
	private:
		I2CTransmitter i2cTransmitter;
		I2CReceiver    i2cReceiver;
		uint8_t slaveAddress;
		bool isRepeateadStart;
		
	public:
		I2CPort();
		void open(uint16_t sclClockFrequency);
		void close();
		void selectSlaveDevice(uint8_t slaveAddress, bool isRepeateadStart = false);
		int8_t writeBytes(uint8_t* buffer, uint8_t length);
		int8_t readBytes(uint8_t* buffer, uint8_t length);
		
	private:
		int8_t start(uint8_t address, const uint8_t readWriteBit);
		void stop(void);
};

#endif