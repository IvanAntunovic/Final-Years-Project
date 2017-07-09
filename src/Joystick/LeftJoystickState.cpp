#include "LeftJoystickState.h"

JoystickState* LeftJoystickState::sInstance = NULL;

JoystickState * LeftJoystickState::getInstance()
{
	if (LeftJoystickState::sInstance == NULL)
	{
		LeftJoystickState::sInstance = new LeftJoystickState();
	}
	return LeftJoystickState::sInstance;
}

void LeftJoystickState::handleCoordinates(int nX, int nY, Joystick & joystick)
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

String LeftJoystickState::toString()
{
	return "Joystick moved to left position";
}

uint8_t LeftJoystickState::toInteger()
{
	return eLeft;
}