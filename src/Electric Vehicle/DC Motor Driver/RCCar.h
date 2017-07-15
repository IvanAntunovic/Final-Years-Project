
/*
 * RCCar.h
 *
 * Created: 5/27/2017 7:31:44 PM
 *  Author: fairenough
 */ 

#ifndef _RC_CAR_H_
#define _RC_CAR_H_

#include "DCMotor.h"

#define MOTORS_MAX_NUMBER 4

#define CAR_FORWARD		0
#define CAR_BACKWARD	1
#define CAR_LEFT		2
#define CAR_RIGHT		3
#define CAR_STOP		4

class RCCar
{
	private:
		DCMotor* dcMotors[MOTORS_MAX_NUMBER];
		
	public:
		RCCar(uint8_t freq = DC_MOTOR_PWM_RATE);
		void run(uint8_t direction);
		void setSpeed(uint8_t speed);
		DCMotor* getMotor(uint8_t motorNumber);
};

#endif
