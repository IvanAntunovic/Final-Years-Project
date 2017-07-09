#include "IdleJoystickState.h"
#include "PasswordLoggerJoystickMode.h"
#include "EEPROM.h"

JoystickState* IdleJoystickState::sInstance = NULL;

JoystickState * IdleJoystickState::getInstance()
{
	if (IdleJoystickState::sInstance == NULL)
	{
		IdleJoystickState::sInstance = new IdleJoystickState();
	}
	return IdleJoystickState::sInstance;
}

void IdleJoystickState::handleCoordinates(int nX, int nY, Joystick & joystick)
{
	int8_t retVal;

	retVal = joystick.getZone(nX, nY);
	if (retVal == NOT_IN_DEADZONE)
	{	
		if (nX > MAX_X_POSITION)
		{
			joystick.changeState( RightJoystickState::getInstance() );
			if ( joystick.getCurrentMode() == PasswordLoggerJoystickMode::getInstance() )
			{
				joystick.getCurrentMode()->handle(joystick);
			}
		}
		else if (nX < MIN_X_POSITION)
		{
			joystick.changeState( LeftJoystickState::getInstance() );
			if ( joystick.getCurrentMode() == PasswordLoggerJoystickMode::getInstance() )
			{
				joystick.getCurrentMode()->handle(joystick);
			}

		}
		else if (nY > MAX_Y_POSITION)
		{
			joystick.changeState( DownJoystickState::getInstance() );
			if ( joystick.getCurrentMode() == PasswordLoggerJoystickMode::getInstance() )
			{
				joystick.getCurrentMode()->handle(joystick);
			}
		}
		else if (nY < MIN_Y_POSITION)
		{
			joystick.changeState( UpJoystickState::getInstance() );
			if ( joystick.getCurrentMode() == PasswordLoggerJoystickMode::getInstance() )
			{
				joystick.getCurrentMode()->handle(joystick);
			}

		}
	}
	else if (retVal == IN_DEADZONE)
	{

	}
	else if (retVal == INVALID_PARAMETER)
	{
		//Serial.println("Invalid parameters!" );
	}
	
}


String IdleJoystickState::toString()
{
	return "Joystick moved to idle position";
}

uint8_t IdleJoystickState::toInteger( )
{
	return eIdle;
}
