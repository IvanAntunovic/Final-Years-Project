#pragma once
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

#include "JoystickState.h"
#include "IdleJoystickState.h"
#include "Arduino.h"
#include "HardwareSerial.h"
#include "EEPROM.h"
#include "JoystickErrorCodes.h"

class JoystickMode;
extern HardwareSerial Serial;

class JoystickMode;
class Joystick
{

private:
	JoystickMode* currentMode;
	JoystickState* currentState;
	JoystickState* passwordPositionBuffer[4];
	uint8_t passwordLength;
	uint8_t xPin;
	uint8_t yPin;
	
public:
	Joystick(uint8_t xPin, uint8_t yPin, uint8_t passwordLength);
	int8_t logPassword(void);
	void verifyPassword(void);
	int8_t getPosition();
	
	JoystickMode* getCurrentMode() {return this->currentMode;}
	JoystickState* getCurrentState() {return this->currentState;}
	void storePasswordPositionInEEPROM();
	
	uint8_t getPasswordLength() {return this->passwordLength;}
	
	Joystick& operator=(const Joystick& other);
	friend bool operator==(const Joystick& joystickOne, const Joystick& joystickTwo);
	int8_t getZone(int nX, int nY);
	void changeState(JoystickState* newState);
	void printCurrentPositions(void);
	
private:
	bool isEqualToEEPROM(void);
	void storePasswordInEEPROM(void);
	void changeMode(uint8_t newMode);
	int8_t getBufferFreeIndex();
};

#endif // !_JOYSTICK_H_
