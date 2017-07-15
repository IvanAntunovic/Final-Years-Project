#include "ShiftRegister.h"

ShiftRegister::ShiftRegister(uint8_t dataPin, uint8_t enablePin, uint8_t clockPin, uint8_t latchPin)
{
	this->dataPin = dataPin;
	this->enablePin = enablePin;
	this->clockPin = clockPin;
	this->latchPin = latchPin;
	
	LATCH_DDR	|= 1 << latchPin;
	ENABLE_DDR	|= 1 << enablePin;
	CLK_DDR		|= 1 << clockPin;
	DATA_DDR	|= 1 << dataPin;
	
	this->storageRegister = 0;
	this->shiftOut();
	
	ENABLE_PORT &= ~(1 << enablePin);
}


void ShiftRegister::writePin(uint8_t pin, uint8_t level)
{
	if (level == HIGH)
	{
		this->storageRegister |= (1 << pin);
	}
	else
	{
		this->storageRegister &= ~(1 << pin);
	}
}

void ShiftRegister::shiftOut(void)
{
	LATCH_PORT &= ~(1 << latchPin);
	DATA_PORT &= ~(1 << dataPin);
	
	for (uint8_t bitPosition = SHIFT_REGISTER_MSB; bitPosition < SHIFT_REGISTER_LSB + 1; bitPosition++)
	{
		//Clock pin LOW
		CLK_PORT &= ~(1 << clockPin);
		//Check if bit is set to HIGH and shift it in the Shift Register buffer
		if (this->storageRegister & (1 << (SHIFT_REGISTER_MSB_POSITION - bitPosition)) )
		{
			DATA_PORT |= 1 << dataPin;
		}
		else
		{
			DATA_PORT &= ~(1 << dataPin);
		}
		//Clock pin LOW->HIGH to shift out one bit
		CLK_PORT |= 1 << clockPin;
	}
	//Latch data out from the Shift Register buffer
	LATCH_PORT |= 1 << latchPin;
}

