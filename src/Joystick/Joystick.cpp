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
		memset ( this->passwordPositionBuffer, NULL, this->passwordLength );
	}
	
	this->getPosition();
	if (this->passwordPositionBuffer[3] != NULL)
	{
		this->storePasswordInEEPROM();
		memset ( this->passwordPositionBuffer, NULL, this->passwordLength );
		return JOYSTICK_LOG_PASSWORD_SET;
	}
	return JOYSTICK_LOG_PASSWORD_NOT_SET;
}

int8_t Joystick::verifyPassword(void)
{
	bool isEqual;
	if ( this->currentMode != PasswordVerificationJoystickMode::getInstance() )
	{
		this->currentMode = PasswordVerificationJoystickMode::getInstance();
		//memset ( this->passwordPositionBuffer, NULL, passwordLength );
		Serial.print("Printanje buffera duljine ... ");
		Serial.println(this->passwordLength);
		
		for (int index = 0; index < this->passwordLength; ++index)
		{
			this->passwordPositionBuffer[index] = NULL;
		}
	}

	this->getPosition();
	if (this->passwordPositionBuffer[3] != NULL)
	{
		isEqual = this->isPasswordEqualToEEPROM();
		if ( isEqual )
		{
			memset ( this->passwordPositionBuffer, NULL, this->passwordLength );
			return JOYSTICK_VERIFICATION_PASSWORD_OK;
		}
		memset ( this->passwordPositionBuffer, NULL, this->passwordLength );
		return JOYSTICK_VERIFICATION_PASSWORD_NOK;
	}
	return JOYSTICK_VERIFICATION_PASSWORD_VERIFICATION_NOT_FINISHED;
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
	if (this->passwordPositionBuffer[this->passwordLength - 2] != NULL && this->passwordPositionBuffer[this->passwordLength - 1] == IdleJoystickState::getInstance())
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
	uint8_t currentPosition;
	
	for (currentPosition = 0; currentPosition < this->passwordLength; ++currentPosition)
	{
		if (this->passwordPositionBuffer[currentPosition] == RightJoystickState::getInstance())
		{
			EEPROM.write(currentPosition, eRight);
		}
		else if (this->passwordPositionBuffer[currentPosition] == LeftJoystickState::getInstance())
		{
			EEPROM.write(currentPosition, eLeft);
		}
		else if (this->passwordPositionBuffer[currentPosition] == UpJoystickState::getInstance())
		{
			EEPROM.write(currentPosition, eUp);
		}
		else if (this->passwordPositionBuffer[currentPosition] == DownJoystickState::getInstance()) 
		{
			EEPROM.write(currentPosition, eDown);
		}
		else
		{
			Serial.println("Error while storing password in EEPROM - Unknown Position");
		}
	}
}

bool Joystick::isPasswordEqualToEEPROM(void)
{
	uint8_t* tempBuffer;
	
	tempBuffer = new uint8_t[this->passwordLength];
	for (int currentPosition = 0; currentPosition < this->passwordLength; ++currentPosition)
	{
		if (this->passwordPositionBuffer[currentPosition] == RightJoystickState::getInstance())
		{
			tempBuffer[currentPosition] = eRight;
		}
		else if (this->passwordPositionBuffer[currentPosition] == LeftJoystickState::getInstance())
		{
			tempBuffer[currentPosition] = eLeft;
		}
		else if (this->passwordPositionBuffer[currentPosition] == UpJoystickState::getInstance())
		{
			tempBuffer[currentPosition] = eUp;
		}
		else if (this->passwordPositionBuffer[currentPosition] == DownJoystickState::getInstance()) 
		{
			tempBuffer[currentPosition] = eDown;
		}
		else
		{
			tempBuffer[currentPosition] = eIdle;
		}	
		if ( EEPROM.read(currentPosition) != tempBuffer[currentPosition] )
		{
			delete[] tempBuffer;
			return false;
		}
		_delay_ms(1000);
	}
	delete[] tempBuffer;
	return true;
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

