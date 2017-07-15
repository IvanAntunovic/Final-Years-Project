
/*
 * RCCar.cpp
 *
 * Created: 5/27/2017 7:34:27 PM
 *  Author: fairenough
 */ 

#include "RCCar.h"

RCCar::RCCar(uint8_t freq)
{
	for (uint8_t motorNumber = 0; motorNumber < MOTORS_MAX_NUMBER; ++motorNumber)
	{
		this->dcMotors[motorNumber] = new DCMotor(motorNumber + 1, freq);
		this->dcMotors[motorNumber]->run(RELEASE);
	}
}

void RCCar::run(uint8_t direction)
{	
	switch (direction)
	{
		case CAR_FORWARD:
			for (uint8_t motorNumber = 0; motorNumber < MOTORS_MAX_NUMBER; ++motorNumber)
			{
				this->dcMotors[motorNumber]->run(FORWARD);
			}
			break;
			
		case CAR_BACKWARD:
			for (uint8_t motorNumber = 0; motorNumber < MOTORS_MAX_NUMBER; ++motorNumber)
			{
				this->dcMotors[motorNumber]->run(BACKWARD);
			}
			break;
			
		case CAR_LEFT:
			this->dcMotors[MOTOR_1 - 1]->run(FORWARD);
			this->dcMotors[MOTOR_2 - 1]->run(BACKWARD);
			this->dcMotors[MOTOR_3 - 1]->run(BACKWARD);
			this->dcMotors[MOTOR_4 - 1]->run(FORWARD);
			break;
			
		case CAR_RIGHT:
			this->dcMotors[MOTOR_1 - 1]->run(BACKWARD);
			this->dcMotors[MOTOR_2 - 1]->run(FORWARD);
			this->dcMotors[MOTOR_3 - 1]->run(FORWARD);
			this->dcMotors[MOTOR_4 - 1]->run(BACKWARD);
			
			break;
		case CAR_STOP:
			for (uint8_t motorNumber = 0; motorNumber < MOTORS_MAX_NUMBER; ++motorNumber)
			{
				this->dcMotors[motorNumber]->run(RELEASE);
			}
			break;
		default:
			break;
	}
}

void RCCar::setSpeed(uint8_t speed)
{
	for (uint8_t motorNumber = 0; motorNumber < MOTORS_MAX_NUMBER; ++motorNumber)
	{
		this->dcMotors[motorNumber]->setSpeed(speed);
	}
}

DCMotor* RCCar::getMotor(uint8_t motorNumber)
{
	switch (motorNumber)
	{
		case MOTOR_1:
			return dcMotors[MOTOR_1 - 1];
		case MOTOR_2:
			return dcMotors[MOTOR_2 - 1];
		case MOTOR_3:
			return dcMotors[MOTOR_3 - 1];
		case MOTOR_4:
			return dcMotors[MOTOR_4 - 1];
		default:
			break;
	}
}