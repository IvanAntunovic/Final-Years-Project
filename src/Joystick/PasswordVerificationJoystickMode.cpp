#include "PasswordVerificationJoystickMode.h"
#include "Joystick.h"

JoystickMode* PasswordVerificationJoystickMode::sInstance = NULL;

JoystickMode* PasswordVerificationJoystickMode::getInstance()
{
	if ( PasswordVerificationJoystickMode::sInstance == NULL )
	{
		PasswordVerificationJoystickMode::sInstance = new PasswordVerificationJoystickMode();
	}
	return PasswordVerificationJoystickMode::sInstance;
}

PasswordVerificationJoystickMode::PasswordVerificationJoystickMode()
{
	this->temporaryPassword = new uint8_t[4];
	this->hasVerificationStarted = false;
	this->previousVerificationMillis = 0;
}

String PasswordVerificationJoystickMode::toString(void)
{
	return "Password verification mode";
}

int8_t PasswordVerificationJoystickMode::handle(Joystick& joystick)
{
	if ( !this->hasVerificationStarted )
	{
		this->hasVerificationStarted = true;
		this->previousVerificationMillis = 0;
	}
	
	if (this->hasVerificationStarted)
	{
		if ( millis() - this->previousVerificationMillis > 10 )
		{
			this->previousVerificationMillis = millis();
		}			
	}
}

bool PasswordVerificationJoystickMode::hasFinished(Joystick& joystick)
{
	
}