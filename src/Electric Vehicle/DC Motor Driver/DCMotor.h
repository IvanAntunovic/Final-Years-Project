#ifndef MOTOR_H
#define MOTOR_H

#include <inttypes.h>
#include <avr/io.h>
#include "ShiftRegister.h"
#include "DCMotorController.h"

class DCMotor
{
	private:
		uint8_t motorNum;
		uint8_t terminalOne;
		uint8_t terminalTwo;
		
	public:
		DCMotor(uint8_t motorNum, uint8_t freq = DC_MOTOR_PWM_RATE);
		void run(uint8_t command);
		void setSpeed(uint8_t speed);
		
};

#endif
