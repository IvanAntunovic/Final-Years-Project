/*
 * Tmp102.cpp
 *
 * Created: 7/1/2017 11:12:07 PM
 *  Author: fairenough
 */ 

#ifndef _TMP_102_H_
#define _TMP_102_H_

#include "I2CPort.h"

#define TMP_102_OK	 0
#define TMP_102_NOK -1

class Tmp102
{
	private:
		float currentTemperature;
		uint8_t address;
		I2CPort* i2cPort;
		
	public:
		Tmp102(I2CPort* i2cPort, uint8_t address);
		void setAddress(uint8_t address);
		int8_t getTemperature(float* temperatureCelsius);
};

#endif