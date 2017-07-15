#include "DCMotorController.h"

DCMotorController* DCMotorController::sInstance = NULL;

DCMotorController* DCMotorController::getInstance()
{
	if (DCMotorController::sInstance == NULL)
	{
		DCMotorController::sInstance = new DCMotorController();
	}
	return DCMotorController::sInstance;
}

void DCMotorController::setPwmFrequency(uint8_t pwmFreq)
{
	this->pwmController.setPwmFreq(pwmFreq);
}

void DCMotorController::writePin(uint8_t pin, uint8_t level)
{
	this->shiftRegister.writePin(pin, level);
}

void DCMotorController::latch_tx()
{
	this->shiftRegister.shiftOut();
}

void DCMotorController::initPwm(uint8_t motorNum, uint8_t pwmFreq)
{
	switch(motorNum)
	{
		case 1:
			this-> pwmController.initPWM1(pwmFreq); break;
		case 2:
			this->pwmController.initPWM2(pwmFreq);	break;
		case 3:
			this->pwmController.initPWM3(pwmFreq);	break;
		case 4:
			this->pwmController.initPWM4(pwmFreq); break;
	}
}

void DCMotorController::setPwm(uint8_t motorNum, uint8_t speed)
{
	switch(motorNum)
	{
		case 1:
			this->pwmController.setPWM1(speed); break;
		case 2:
			this->pwmController.setPWM2(speed);	break;
		case 3:
			this->pwmController.setPWM3(speed);	break;
		case 4:
			this->pwmController.setPWM4(speed); break;
	}
}