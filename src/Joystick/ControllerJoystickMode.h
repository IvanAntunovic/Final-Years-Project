#ifndef _CONTROLLER_JOYSTICK_MODE_H_
#define _CONTROLLER_JOYSTICK_MODE_H_

#include "JoystickMode.h"

class ControllerJoystickMode : public JoystickMode
{
	private:
		static JoystickMode* sInstance;
	
	protected:
		ControllerJoystickMode(){}
		
	public:
		String toString(void);
		int8_t handle(Joystick& joystick);
		bool hasFinished(Joystick& joystick);
		static JoystickMode* getInstance();
};

#endif