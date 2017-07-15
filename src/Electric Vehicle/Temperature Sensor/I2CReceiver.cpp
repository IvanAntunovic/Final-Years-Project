/*
 * I2CReceiver.cpp
 *
 * Created: 5/20/2017 7:24:17 PM
 *  Author: fairenough
 */ 
#include "I2CReceiver.h"

#ifndef extern "C" { void __cxa_pure_virtual() { while (1); }}
#endif
//
//int8_t I2CReceiver::readBytes(uint8_t* buffer, uint8_t length)
//{
	//int8_t returnValue;
	//
	//for (uint8_t index = 0; index < length; ++index)
	//{
		////If there is more than one byte to be read, receive data byte and return an ACK
		//if (index < length - 1)
		//{
			//returnValue = this->readByteAck(&buffer[index]);
			//if (returnValue != I2C_OK)
			//{
				//return I2C_READ_NOK;
			//}
		//}
		//else
		//{
			//returnValue = this->readByteNak(&buffer[index]);
			//if (returnValue != I2C_OK)
			//{
				//return I2C_READ_NOK;
			//}
		//}
	//}
	//return I2C_OK;
//}
//
//int8_t I2CReceiver::readByteAck(uint8_t* byte)
//{
	//uint8_t   twStatusRegister;
	//
	//TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	//while(!(TWCR & (1<<TWINT)));
	//
	//twStatusRegister = TW_STATUS & 0xF8;
	//if (twStatusRegister != TW_MR_DATA_ACK)
	//{
		//return I2C_READ_NOK;
	//}
	//*byte = TWDR;
	//
	//return I2C_OK;
//}
//
//int8_t I2CReceiver::readByteNak(uint8_t* byte)
//{
	//uint8_t   twStatusRegister;
	//
	//TWCR = (1<<TWINT) | (1<<TWEN);
	//while(!(TWCR & (1<<TWINT)));
	//
	//twStatusRegister = TW_STATUS & 0xF8;
	//if (twStatusRegister != TW_MR_DATA_NACK)
	//{
		//return I2C_READ_NOK;
	//}
	//*byte = TWDR;
	//return I2C_OK;
//}


/* ################################################## */
int8_t I2CReceiver::readBytes(uint8_t* buffer, uint8_t length)
{
	int8_t returnValue;

	if (buffer == NULL || length < 1)
	{
		return I2C_INVALID_PARAMETER;
	}

	for (uint8_t index = 0; index < length; ++index)
	{
		//If there is more than one byte to be read, receive data byte and return an ACK
		if (index < length - 1)
		{
			returnValue = this->readByte(&buffer[index], I2C_READ_ACK);
			if (returnValue != I2C_OK)
			{
				return I2C_READ_NOK;
			}
		}
		else
		{
			returnValue = this->readByte(&buffer[index], I2C_READ_NAK);
			if (returnValue != I2C_OK)
			{
				return I2C_READ_NOK;
			}
		}
	}
	return I2C_OK;
}

int8_t I2CReceiver::readByte(uint8_t* byte, uint8_t receiveSignal)
{
	uint8_t   twStatusRegister;
	
	if (receiveSignal == I2C_READ_ACK)
	{
		TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	}
	else if (receiveSignal == I2C_READ_NAK)
	{
		TWCR = (1<<TWINT) | (1<<TWEN);
	}
	else
	{
		return I2C_INVALID_PARAMETER;
	}
	
	while( !(TWCR & (1<<TWINT)) );
	
	twStatusRegister = TW_STATUS & 0xF8;
	if ( (twStatusRegister != TW_MR_DATA_ACK) && (twStatusRegister != TW_MR_DATA_NACK) )
	{
		return I2C_READ_NOK;
	}
	*byte = TWDR;
	
	return I2C_OK;
}
