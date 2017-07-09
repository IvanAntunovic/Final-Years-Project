#include "Joystick.h"
#include "PasswordLoggerJoystickMode.h"
#include "PasswordVerificationJoystickMode.h"
#include "ControllerJoystickMode.h"

Joystick::Joystick(uint8_t xPin, uint8_t yPin, uint8_t passwordLength)
{
	this->xPin = xPin;
	this->yPin = yPin;
	this->passwordLength = passwordLength;

	this->currentState = IdleJoystickState::getInstance();
	this->currentMode = PasswordVerificationJoystickMode::getInstance();
	
	memset ( this->passwordPositionBuffer, NULL, passwordLength );
}

void Joystick::changeMode(uint8_t newMode)
{
	this->currentMode = newMode;
}

void Joystick::changeState(JoystickState * newState)
{
	this->currentState = newState;
}

int8_t Joystick::getZone(int nX, int nY)
{
	if (nX < 0 && nX > 1023 || nY < 0 && nY > 1023)
	{
		return INVALID_PARAMETER;
	}

	if (nX > MAX_X_POSITION || nX < MIN_X_POSITION || nY > MAX_Y_POSITION || nY < MIN_Y_POSITION)
	{
		return NOT_IN_DEADZONE;
	}
	return IN_DEADZONE;
}

int8_t Joystick::getPosition(void)
{
	int nX;
	int nY;

	nX = analogRead(this->xPin);
	nY = analogRead(this->yPin);
	this->currentState->handleCoordinates(nX, nY, *this);
	Serial.println( this->currentState->toString() );
	
	if (this->currentState == RightJoystickState::getInstance())
	{
		return eRight;
	}
	else if (this->currentState  == LeftJoystickState::getInstance())
	{
		return eLeft;
	}
	else if (this->currentState  == UpJoystickState::getInstance())
	{
		return eUp;
	}
	else if (this->currentState  == DownJoystickState::getInstance()) 
	{
		return eDown;
	}
	else if (this->currentState  == IdleJoystickState::getInstance()) 
	{
		return eIdle;
	}
	else
	{
		return eInvalidJoystickState;
	}
}

int8_t Joystick::logPassword(void)
{
	if ( this->currentMode != PasswordLoggerJoystickMode::getInstance() )
	{
		this->currentMode = PasswordLoggerJoystickMode::getInstance();
		memset ( this->passwordPositionBuffer, NULL, passwordLength );
	}
	this->getPosition();
	/*if ( this->currentMode == PasswordVerificationJoystickMode::getInstance() )
	{
		return JOYSTICK_LOG_PASSWORD_SET;
	}*/
	
	if (this->passwordPositionBuffer[3] != NULL)
	{
		this->storePasswordInEEPROM();
		return JOYSTICK_LOG_PASSWORD_SET;
	}
	return JOYSTICK_LOG_PASSWORD_NOT_SET;
}

void Joystick::storePasswordPositionInEEPROM()
{
	int8_t bufferFreeIndexNum;
	
	bufferFreeIndexNum = getBufferFreeIndex();
	this->passwordPositionBuffer[bufferFreeIndexNum] = this->currentState;
	this->currentState->toString();
	if ( bufferFreeIndexNum == JOYSTICK_NOK )
	{
		this->currentMode = PasswordVerificationJoystickMode::getInstance();
	}
}

int8_t Joystick::getBufferFreeIndex()
{
	if (this->passwordPositionBuffer[2] != NULL && this->passwordPositionBuffer[3] == IdleJoystickState::getInstance())
	{
		return JOYSTICK_NOK;
	}

	for (int8_t bufferFreeIndexNum = 0; bufferFreeIndexNum < this->passwordLength; ++bufferFreeIndexNum)
	{
		if (this->passwordPositionBuffer[bufferFreeIndexNum] == NULL)
		{
			return bufferFreeIndexNum;
		}
	}
	return JOYSTICK_NOK;
}

void Joystick::storePasswordInEEPROM(void)
{
	for (uint8_t currentPosition = 0; currentPosition < this->passwordLength; ++currentPosition)
	{
		if (this->passwordPositionBuffer[currentPosition] == RightJoystickState::getInstance())
		{
			Serial.println("EEPROM Stored Right");
			EEPROM.write(currentPosition, eRight);
		}
		else if (this->passwordPositionBuffer[currentPosition] == LeftJoystickState::getInstance())
		{
			Serial.println("EEPROM Stored Left");
			EEPROM.write(currentPosition, eLeft);
		}
		else if (this->passwordPositionBuffer[currentPosition] == UpJoystickState::getInstance())
		{
			Serial.println("EEPROM Stored Up");
			EEPROM.write(currentPosition, eUp);
		}
		else if (this->passwordPositionBuffer[currentPosition] == DownJoystickState::getInstance()) 
		{
			Serial.println("EEPROM Stored Down");
			EEPROM.write(currentPosition, eDown);
		}
		else
		{
			Serial.println("Error while storing password in EEPROM - Unknown Position");
		}
	}
}

void Joystick::printCurrentPositions(void)
{
	
	Serial.println("You have entered the following positions: ");
	for (uint8_t currentPosition = 0; currentPosition < this->passwordLength; ++currentPosition)
	{
		Serial.print(currentPosition);
		Serial.print(".: ");
		if (EEPROM.read(currentPosition) == eRight)
		{
			Serial.println("Right Position");
		}
		else if (EEPROM.read(currentPosition) == eLeft)
		{
			Serial.println("Left Position");
		}
		else if (EEPROM.read(currentPosition) == eUp)
		{
			Serial.println("Up Position");
		}
		else if (EEPROM.read(currentPosition) == eDown) 
		{
			Serial.println("Down Position");
		}
		else
		{
			Serial.println("Unknown Position");
		}
	}
	Serial.println("");
}

