#include "UpJoystickState.h"

JoystickState* UpJoystickState::sInstance = NULL;

JoystickState * UpJoystickState::getInstance()
{
	if (UpJoystickState::sInstance == NULL)
	{
		UpJoystickState::sInstance = new UpJoystickState();
	}
	return UpJoystickState::sInstance;
}

void UpJoystickState::handleCoordinates(int nX, int nY, Joystick & joystick)
{
	int8_t retVal = joystick.getZone(nX, nY);
	
	if (retVal == IN_DEADZONE)
	{
		joystick.changeState(IdleJoystickState::getInstance());
		//Serial.println( "Joystick moved to Idle Position!");
	}
	else if (retVal == NOT_IN_DEADZONE)
	{
		//Serial.println("Joystick is not in Deadzone! - Up");
		//Serial.println("");
	}
	else if (retVal == INVALID_PARAMETER)
	{
		//Serial.println("Invalid parameters!");
	}
}

String UpJoystickState::toString()
{
	return "Joystick moved to up position";
}

uint8_t UpJoystickState::toInteger()
{
	return eUp;
}