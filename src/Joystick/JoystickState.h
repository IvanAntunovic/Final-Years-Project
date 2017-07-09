#pragma once

#ifndef _JOYSTICK_STATE_H_
#define _JOYSTICK_STATE_H_

#include <Arduino.h>
#include "JoystickErrorCodes.h"
#include "HardwareSerial.h"
#include "EEPROM.h"
extern HardwareSerial Serial;

#include <stdint.h>
class Joystick;


#ifndef NULL
#define NULL 0
#endif


class JoystickState
{
	protected:
		JoystickState() {};
		
	public:
		virtual void handleCoordinates(int, int, Joystick&) = 0;
		virtual String toString() = 0;
		virtual uint8_t toInteger() = 0;
};

#endif

