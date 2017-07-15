#ifndef _PWM_CONTROLLER_H_
#define _PWM_CONTROLLER_H_

#include <avr/io.h>
#include "DCMotorTypes.h"

class PWMController
{
	private:
		uint8_t freq;
		
	public:
		void setPwmFreq(uint8_t freq);
		void initPWM1(uint8_t freq);
		void setPWM1 (uint8_t s);
		void initPWM2(uint8_t freq);
		void setPWM2 (uint8_t s);
		void initPWM3 (uint8_t freq);
		void setPWM3 (uint8_t s);
		void initPWM4 (uint8_t freq);
		void setPWM4 (uint8_t s);
};

#endif

