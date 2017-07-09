#include "ControllerJoystickMode.h"

JoystickMode* ControllerJoystickMode::sInstance = NULL;

JoystickMode* ControllerJoystickMode::getInstance()
{
	if ( ControllerJoystickMode::sInstance == NULL )
	{
		ControllerJoystickMode::sInstance = new ControllerJoystickMode();
	}
	return ControllerJoystickMode::sInstance;
}

String ControllerJoystickMode::toString(void)
{
	return "Controller mode";
}

int8_t ControllerJoystickMode::handle(Joystick& joystick)
{
	
}

bool ControllerJoystickMode::hasFinished(Joystick& joystick)
{
	
}