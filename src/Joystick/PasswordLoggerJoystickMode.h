#ifndef _PASSWORD_LOGGER_H_
#define _PASSWORD_LOGGER_H_

#include "JoystickMode.h"
#include <EEPROM.h>
#include "Arduino.h"
#include "HardwareSerial.h"

extern HardwareSerial Serial;

#define PASSWORD_LOGGER_PASSWORD_LOGGED 1
#define PASSWORD_LOGGER_OK   0
#define PASSWORD_LOGGER_NOK -1


class Joystick;
class JoystickState;

class PasswordLoggerJoystickMode : public JoystickMode
{
	private:
		static JoystickMode* sInstance;
		JoystickState* tempPositionStates[5];

	public:
		static JoystickMode* getInstance(void);
		String toString(void);
		int8_t handle(Joystick& joystick);
		bool hasFinished(Joystick& joystick);
		bool isLogged(void);
	
	protected:
		PasswordLoggerJoystickMode();
	
	private:
		int8_t getFreeMemoryAddress(Joystick& joystick);
		int8_t getFreeTempBufferIndex(Joystick& joystick);
		int8_t getBufferFreeIndex();
};

#endif