#pragma once
#ifndef _IDLE_JOYSTICK_STATE_H_
#define _IDLE_JOYSTICK_STATE_H_

#include "Joystick.h"

#include "JoystickState.h"
#include "DownJoystickState.h"
#include "RightJoystickState.h"
#include "LeftJoystickState.h"
#include "RightJoystickState.h"
#include "UpJoystickState.h"

#include "HardwareSerial.h"

extern HardwareSerial Serial;

class IdleJoystickState : public JoystickState
{
	private:
		static JoystickState* sInstance;

	private:
		int8_t getMemoryFreeIndex(Joystick & joystick);
		
	public:
		static JoystickState* getInstance();
		void handleCoordinates(int nX, int nY, Joystick& joystick);	
		uint8_t toInteger();
		String toString();
};
#endif