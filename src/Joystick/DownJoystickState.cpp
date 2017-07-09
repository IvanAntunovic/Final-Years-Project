#include "DownJoystickState.h"

JoystickState* DownJoystickState::sInstance = NULL;

JoystickState* DownJoystickState::getInstance() 
{
	if (DownJoystickState::sInstance == NULL)
	{
		DownJoystickState::sInstance = new DownJoystickState();
	}
	return DownJoystickState::sInstance;
}

void DownJoystickState::handleCoordinates(int nX, int nY, Joystick & joystick)
{
	int8_t retVal;
	
	retVal = joystick.getZone(nX, nY);
	if (retVal == IN_DEADZONE)
	{
		joystick.changeState(IdleJoystickState::getInstance());

	}
	else if (retVal == NOT_IN_DEADZONE)
	{
		//Serial.println("Joystick is not in Deadzone! - Down");
		//Serial.println("");
	}
	else if (retVal == INVALID_PARAMETER)
	{
		//Serial.println("Invalid parameters!");
	}
}

String DownJoystickState::toString()
{
	return "Joystick moved to down position";
}

uint8_t DownJoystickState::toInteger()
{
	return eDown;
}



