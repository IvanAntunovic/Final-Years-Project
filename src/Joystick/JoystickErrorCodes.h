#ifndef _JOYSTICK_ERROR_CODES_H_
#define _JOYSTICK_ERROR_CODES_H_

#define PASSWORD_LENGTH		4

#define MAX_X_POSITION		1000
#define MIN_X_POSITION		20
#define MAX_Y_POSITION		1000
#define MIN_Y_POSITION		20

#define MODE_KORISTI        0
#define MODE_POSTAVI		1

#define INVALID_PARAMETER   -1
#define IN_DEADZONE          0
#define NOT_IN_DEADZONE      1

#define JOYSTICK_LOG_PASSWORD_SET 1
#define JOYSTICK_LOG_PASSWORD_OK 0
#define JOYSTICK_LOG_PASSWORD_NOK -1
#define JOYSTICK_LOG_PASSWORD_NOT_SET -2
#define JOYSTICK_LOG_NOT_MOVED -3
#define JOYSTICK_INCORRECT_PASSWORD -4

#define JOYSTICK_OK 0
#define JOYSTICK_NOK -1


#define PASSWORD_LOGGER_NO_MEMORY_BYTE_AVAILABLE -1
#define PASSWORD_LOGGER_AVAILABLE_MEMORY_BYTE     0
#define PASSWORD_LOGGER_TEMP_MEMORY_START_INDEX   8
#define PASSWORD_LOGGER_TEMP_MEMORY_STOP_INDEX   (PASSWORD_LOGGER_TEMP_MEMORY_START_INDEX + 8)


// Enums for storing in the EEPROM
enum eJoystickState_t
{
	eRight = 1,
	eLeft = 2,
	eUp = 3,
	eDown = 4,
	eIdle = 5,
	eInvalidJoystickState = -1
};


#endif