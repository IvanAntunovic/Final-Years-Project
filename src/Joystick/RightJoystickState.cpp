#include "RightJoystickState.h"

JoystickState* RightJoystickState::sInstance = NULL;

JoystickState * RightJoystickState::getInstance()
{
	if (RightJoystickState::sInstance == NULL)
	{
		RightJoystickState::sInstance = new RightJoystickState();
	}
	return RightJoystickState::sInstance;
}

void RightJoystickState::handleCoordinates(int nX, int nY, Joystick & joystick)
{
	int8_t retVal = joystick.getZone(nX, nY);
	if (retVal == IN_DEADZONE)
	{
		joystick.changeState(IdleJoystickState::getInstance());
	}
	else if (retVal == NOT_IN_DEADZONE)
	{

	}
	else if (retVal == INVALID_PARAMETER)
	{

	}
}

String RightJoystickState::toString()
{
	return "Joystick moved to right position";
}

uint8_t RightJoystickState::toInteger()
{
	return eRight;
}
