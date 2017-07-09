#pragma once
#ifndef _DOWN_JOYSTICK_STATE_H_
#define _DOWN_JOYSTICK_STATE_H_

#include "JoystickState.h"
#include "Joystick.h"
#include "IdleJoystickState.h"
#include "HardwareSerial.h"

extern HardwareSerial Serial;

class DownJoystickState : public JoystickState
{
private:
	static JoystickState* sInstance;
public:
	static JoystickState* getInstance();
	void handleCoordinates(int nX, int nY, Joystick& joystick);
	String toString();
	uint8_t toInteger();
};

#endif