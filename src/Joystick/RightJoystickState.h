#pragma once
#include "JoystickState.h"
#include "Joystick.h"
#include "HardwareSerial.h"

extern HardwareSerial Serial;

class RightJoystickState : public JoystickState
{
private:
	static JoystickState* sInstance;
public:
	static JoystickState* getInstance();
	void handleCoordinates(int nX, int nY, Joystick& joystick);
	String toString();
	uint8_t toInteger();
};
