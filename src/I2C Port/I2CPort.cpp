/*
 * I2CPort.cpp
 *
 * Created: 5/20/2017 6:37:47 PM
 *  Author: fairenough
 */ 
#include "I2CPort.h"

I2CPort::I2CPort()
{
	/* initialize DEFAULT TWI clock: 100 kHz clock, TWPS = 0 => prescaler = 1 */
	TWSR = 0;                         /* no prescaler */
	TWBR = ((F_CPU/SCL_CLOCK) - 16) / 2;  /* must be > 10 for stable operation */
	
	this->slaveAddress = -1;
	this->isRepeateadStart = false;
}

void I2CPort::open(uint16_t sclClockFrequency)
{
	TWSR = 0;                         /* no prescaler */
	TWBR = ((F_CPU/sclClockFrequency) - 16) / 2;  /* must be > 10 for stable operation */
}

void I2CPort::close()
{
	// SCL = 0 Hz
	TWBR = 0;
}

void I2CPort::selectSlaveDevice(uint8_t slaveAddress, bool isRepeateadStart)
{
	this->slaveAddress = slaveAddress;
	this->isRepeateadStart = isRepeateadStart;
}

int8_t I2CPort::start(unsigned char address, const unsigned char readWriteBit)
{
	uint8_t  twStatusRegister;
	
	if (readWriteBit == I2C_WRITE)
	{
		address = address << 1;
	}
	else if (readWriteBit == I2C_READ)
	{
		address = (address << 1) | 0x01;
	}
	
	// send START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits.
	twStatusRegister = TW_STATUS & 0xF8;
	if ( (twStatusRegister != TW_START) && (twStatusRegister != TW_REP_START))
	{
		return I2C_START_NOK;
	}
	//TW_START = 0x08	        TW_REP_START = 0x10
	// send device address
	TWDR = address;
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wail until transmission completed and ACK/NACK has been received
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits.
	twStatusRegister = TW_STATUS & 0xF8;
	if ( (twStatusRegister != TW_MT_SLA_ACK) && (twStatusRegister != TW_MR_SLA_ACK) )
	{
		return I2C_SLA_NAK;
	}
	//TW_MT_SLA_ACK	0x18		TW_MR_SLA_ACK = 0x40
	return I2C_OK;
}

void I2CPort::stop(void)
{
	/* send stop condition */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	
	// wait until stop condition is executed and bus released
	while (TWCR & (1<<TWSTO));
}

int8_t I2CPort::writeBytes(uint8_t* buffer, uint8_t length)
{
	int8_t retVal;
	
	retVal = this->start(this->slaveAddress, I2C_WRITE);
	if (retVal  != I2C_OK )
	{
		return retVal;
	}
	
	retVal = this->i2cTransmitter.writeBytes(buffer, length);
	if (retVal != I2C_OK)
	{
		return retVal;
	}
	
	if (this->isRepeateadStart)
	{
		retVal = this->start(this->slaveAddress, I2C_WRITE);
		if ( retVal != I2C_OK )
		{
			return retVal;
		}
		return I2C_OK;
	}
	this->stop();
	return I2C_OK;
}

int8_t I2CPort::readBytes(uint8_t* buffer, uint8_t length)
{
	int8_t retVal;
	
	retVal = this->start(this->slaveAddress, I2C_READ);
	if (retVal  != I2C_OK )
	{
		return retVal;
	}
	
	retVal = this->i2cReceiver.readBytes(buffer, length);
	if (retVal != I2C_OK)
	{
		return retVal;
	}
	
	if (this->isRepeateadStart)
	{
		retVal = this->start(this->slaveAddress, I2C_READ);
		if ( retVal != I2C_OK )
		{
			return retVal;
		}
		return I2C_OK;
	}
	this->stop();
	return I2C_OK;
}
