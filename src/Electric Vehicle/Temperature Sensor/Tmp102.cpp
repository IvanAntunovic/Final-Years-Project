/*
 * Tmp102.cpp
 *
 * Created: 7/1/2017 11:13:59 PM
 *  Author: fairenough
 */ 
#include "Tmp102.h"

Tmp102::Tmp102(I2CPort* i2cPort, uint8_t address)
{
	this->i2cPort = i2cPort;
	this->address = address;
}

void Tmp102::setAddress(uint8_t address)
{
	this->address = address;
}

int8_t Tmp102::getTemperature(float* temperatureCelsius)
{
	uint8_t buffer[2];
	uint8_t mostSignificantBit;
	uint8_t leastSignificantBit;
	int temperatureSum;
	int8_t retVal;
	
	retVal = this->i2cPort->readBytes(buffer, 2);
	if (retVal != I2C_OK)
	{
		return retVal;
	}

	mostSignificantBit = buffer[0];
	leastSignificantBit = buffer[1];

	//it's a 12bit int, using two's compliment for negative
	temperatureSum = ((mostSignificantBit << 8) | leastSignificantBit) >> 4;	
	*temperatureCelsius = temperatureSum * 0.0625;
	
	return TMP_102_OK;
}