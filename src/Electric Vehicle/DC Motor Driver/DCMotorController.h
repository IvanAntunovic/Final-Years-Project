#ifndef _MOTOR_CONTROLLER_H_
#define _MOTOR_CONTROLLER_H_

#include "ShiftRegister.h"
#include "PWMController.h"

class DCMotorController
{
	private:
		ShiftRegister shiftRegister;
		PWMController pwmController;
		static DCMotorController* sInstance;
			
	protected:
		DCMotorController(){};

	public:
		static DCMotorController* getInstance();
		void setPwmFrequency(uint8_t pwmFreq);
		void setPwm(uint8_t motorNum, uint8_t speed);
		void initPwm(uint8_t motorNum, uint8_t pwmFreq);
		void latch_tx(void);
		void writePin(uint8_t pin, uint8_t level);
};

#endif