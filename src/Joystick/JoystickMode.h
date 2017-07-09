#ifndef _JOYSTICK_MODE_H_
#define _JOYSTICK_MODE_H_

#include "Arduino.h"

class Joystick;

class JoystickMode 
{
	public:
		virtual String toString(void) = 0;
		virtual int8_t handle(Joystick& joystick) = 0;
		virtual bool hasFinished(Joystick& joystick) = 0;
};

#endif