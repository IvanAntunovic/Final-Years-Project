#include "DCMotor.h"

DCMotor::DCMotor (uint8_t motorNum, uint8_t pwmFreq) 
{
	this->motorNum = motorNum;
	DCMotorController::getInstance()->setPwmFrequency(pwmFreq);
	
	switch(motorNum)
	{
		case MOTOR_1:
			DCMotorController::getInstance()->writePin(MOTOR1_A, LOW);
			DCMotorController::getInstance()->writePin(MOTOR1_B, LOW);
			DCMotorController::getInstance()->latch_tx();
			DCMotorController::getInstance()->initPwm(MOTOR_1, pwmFreq);
			break;
		case MOTOR_2:
			DCMotorController::getInstance()->writePin(MOTOR2_A, LOW);
			DCMotorController::getInstance()->writePin(MOTOR2_B, LOW);
			DCMotorController::getInstance()->latch_tx();
			DCMotorController::getInstance()->initPwm(MOTOR_2, pwmFreq);
			break;
		case MOTOR_3:
			DCMotorController::getInstance()->writePin(MOTOR3_A, LOW);
			DCMotorController::getInstance()->writePin(MOTOR3_B, LOW);
			DCMotorController::getInstance()->latch_tx();
			DCMotorController::getInstance()->initPwm(MOTOR_3, pwmFreq);
			break;
		case MOTOR_4:
			DCMotorController::getInstance()->writePin(MOTOR4_A, LOW);
			DCMotorController::getInstance()->writePin(MOTOR3_B, LOW);
			DCMotorController::getInstance()->latch_tx();
			DCMotorController::getInstance()->initPwm(MOTOR_4, pwmFreq); 	
		default:
			return;
	}
}

void DCMotor::run (uint8_t cmd)
{
	/*  U konstruktoru se dobiva parametar koji je motor odabran (1, 2, 3, 4)
		Ovisno o kojem od 4 motora se radi, varijable terminalOne i terminalTwo poprimaju zadane vrijednosti
	*/
	switch (this->motorNum)
	{
		case 1:
			this->terminalOne = MOTOR1_A; this->terminalTwo = MOTOR1_B; break;  // MOTOR1_A 2 (Q2) i MOTOR1_B 3 (Q3)
		case 2:
			this->terminalOne = MOTOR2_A; this->terminalTwo = MOTOR2_B; break;  // MOTOR2_A 1 (Q1) i MOTOR2_B 4 (Q4)
		case 3:
			this->terminalOne = MOTOR3_A; this->terminalTwo = MOTOR3_B; break;  // MOTOR3_A 5 ( i  MOTOR3_B 7
		case 4:
			this->terminalOne = MOTOR4_A; this->terminalTwo = MOTOR4_B; break;  // MOTOR4_A 0 i MOTOR4_B 6
		default:
			return;
	}

	switch (cmd)
	{
		case FORWARD:
			DCMotorController::getInstance()->writePin(this->terminalOne, HIGH);
			DCMotorController::getInstance()->writePin(this->terminalTwo, LOW);
			DCMotorController::getInstance()->latch_tx();
			break;
		case BACKWARD:
			DCMotorController::getInstance()->writePin(this->terminalOne, LOW);
			DCMotorController::getInstance()->writePin(this->terminalTwo, HIGH);
			DCMotorController::getInstance()->latch_tx();
			break;
		case RELEASE: 
			DCMotorController::getInstance()->writePin(this->terminalOne, LOW);
			DCMotorController::getInstance()->writePin(this->terminalTwo, LOW);
			DCMotorController::getInstance()->latch_tx();
			break;
		default:
			return;
	}
}


void DCMotor::setSpeed (uint8_t speed)
{
	DCMotorController::getInstance()->setPwm(this->motorNum, speed);
}

