#include "PasswordLoggerJoystickMode.h"
#include "Joystick.h"
#include "IdleJoystickState.h"
#include "JoystickErrorCodes.h"

JoystickMode* PasswordLoggerJoystickMode::sInstance = NULL;

JoystickMode* PasswordLoggerJoystickMode::getInstance()
{
	if ( PasswordLoggerJoystickMode::sInstance == NULL )
	{
		PasswordLoggerJoystickMode::sInstance = new PasswordLoggerJoystickMode();
	}
	return PasswordLoggerJoystickMode::sInstance;
}

PasswordLoggerJoystickMode::PasswordLoggerJoystickMode()
{
	for (uint8_t memoryIndex = PASSWORD_LOGGER_TEMP_MEMORY_START_INDEX; memoryIndex < PASSWORD_LOGGER_TEMP_MEMORY_STOP_INDEX; ++memoryIndex)
	{
		EEPROM.write(memoryIndex, PASSWORD_LOGGER_AVAILABLE_MEMORY_BYTE);
	}
}

String PasswordLoggerJoystickMode::toString(void)
{
	return "Password logger mode";
}

int8_t PasswordLoggerJoystickMode::handle(Joystick& joystick)
{
	int8_t memoryIndex;
	JoystickState* previousState;
	
	if ( joystick.getCurrentState() == IdleJoystickState::getInstance() )
	{
		return PASSWORD_LOGGER_NOK;
	}
	
	if ( joystick.getCurrentState() == previousState )
	{
		return PASSWORD_LOGGER_NOK;
	}
	
	memoryIndex = this->getFreeMemoryAddress(joystick);
	if ( memoryIndex == PASSWORD_LOGGER_NO_MEMORY_BYTE_AVAILABLE)
	{
		return PASSWORD_LOGGER_OK;
	}
	previousState = joystick.getPosition();
	EEPROM.write( memoryIndex, previousState->toInteger() );
	Serial.print("Memory index: ");
	Serial.println(memoryIndex);
	Serial.print( "Stored in memory position " );
	Serial.println(  joystick.getCurrentState()->toString() );
	return PASSWORD_LOGGER_NOK;
		
}

int8_t PasswordLoggerJoystickMode::getFreeMemoryAddress(Joystick& joystick)
{
	uint8_t passwordLength = joystick.getPasswordLength();
	
	for (uint8_t memoryAddress = 0; memoryAddress < passwordLength; ++memoryAddress)
	{
		if (EEPROM.read(memoryAddress) == PASSWORD_LOGGER_AVAILABLE_MEMORY_BYTE)
		{
			return memoryAddress;
		}
	}
	
	return PASSWORD_LOGGER_NO_MEMORY_BYTE_AVAILABLE;
}

int8_t PasswordLoggerJoystickMode::getFreeTempBufferIndex(Joystick& joystick)
{
	uint8_t passwordLength = joystick.getPasswordLength();
	
	for (uint8_t memoryIndex = 8; memoryIndex < passwordLength + 8; ++memoryIndex)
	{
		if (EEPROM.read(memoryIndex) == PASSWORD_LOGGER_AVAILABLE_MEMORY_BYTE)
		{
			return memoryIndex;
		}
	}
	
	return PASSWORD_LOGGER_NO_MEMORY_BYTE_AVAILABLE;
}

bool PasswordLoggerJoystickMode::hasFinished(Joystick& joystick)
{
	return this->getFreeMemoryAddress(joystick) >= joystick.getPasswordLength();
}



