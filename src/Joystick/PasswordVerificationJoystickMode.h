#ifndef _PASSWORD_VERIFICATION_JOYSTICK_MODE_H_
#define _PASSWORD_VERIFICATION_JOYSTICK_MODE_H_

#include "JoystickMode.h"

class PasswordVerificationJoystickMode : public JoystickMode
{
	private:
		static JoystickMode* sInstance;
		uint8_t* temporaryPassword;
		bool hasVerificationStarted;
		unsigned long previousVerificationMillis;

	public:
		static JoystickMode* getInstance(void);
		String toString(void);
		int8_t handle(Joystick& joystick);
		bool hasFinished(Joystick& joystick);
		
	protected:
		PasswordVerificationJoystickMode();
};

#endif