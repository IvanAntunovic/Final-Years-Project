#include "IdleJoystickState.h"
#include "PasswordLoggerJoystickMode.h"
#include "EEPROM.h"
#include "JoystickMode.h"

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
	JoystickMode* currentJoystickMode;

	retVal = joystick.getZone(nX, nY);
	if (retVal == NOT_IN_DEADZONE)
	{	
		currentJoystickMode = joystick.getCurrentMode();
		if (nX > MAX_X_POSITION)
		{
			joystick.changeState( RightJoystickState::getInstance() );
			if ( currentJoystickMode == PasswordLoggerJoystickMode::getInstance() )
			{
				joystick.storePasswordPositionInEEPROM();
			}
		}
		else if (nX < MIN_X_POSITION)
		{
			joystick.changeState( LeftJoystickState::getInstance() );
			if ( currentJoystickMode == PasswordLoggerJoystickMode::getInstance() )
			{
				joystick.storePasswordPositionInEEPROM();
			}
		}
		else if (nY > MAX_Y_POSITION)
		{
			joystick.changeState( DownJoystickState::getInstance() );
			if ( currentJoystickMode == PasswordLoggerJoystickMode::getInstance() )
			{
				joystick.storePasswordPositionInEEPROM();
			}
		}
		else if (nY < MIN_Y_POSITION)
		{
			joystick.changeState( UpJoystickState::getInstance() );
			if ( currentJoystickMode == PasswordLoggerJoystickMode::getInstance() )
			{
				joystick.storePasswordPositionInEEPROM();
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
