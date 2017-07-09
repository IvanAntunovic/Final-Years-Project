#ifndef _UP_JOYSTICK_STATE_H_
#define _UP_JOYSTICK_STATE_H_

#include "JoystickState.h"
#include "Joystick.h"
#include "IdleJoystickState.h"

class UpJoystickState : public JoystickState
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