#include "PWMController.h"
 
void PWMController::setPwmFreq(uint8_t freq)
{
	this->initPWM1(freq);
	this->initPWM2(freq);
	this->initPWM3(freq);
	this->initPWM4(freq);
}

void PWMController::initPWM1(uint8_t freq)
{
	#if defined(__AVR_ATmega324p__)
		 // koristi PWM od timer2A na PB3 
		TCCR2A |= 1 << COM2A1 | 1 << WGM20) | (1 << WGM21); // fast PWM, turn on oc2a
		TCCR2B = freq & 0x7;
		OCR2A = 0;
	#elif defined(__AVR_ATmega2560__)
		// na Atmega2560 , pin 11 = PB5 (OC1A)
		TCCR1A |= (1 << COM1A1) | (1 << WGM10); // fast PWM, turn on
		TCCR1B = (freq & 0x7) | (1 << WGM12);
		OCR1A = 0;
		
		DDRB |= 1 << PB5;
	#else
		#error "This chip is not supported!"
	#endif
	
	//pinMode(11, OUTPUT);
}

void PWMController::setPWM1(uint8_t s)
{
	#if defined(__AVR_ATmega324p__)
		OCR2A = s;
	#elif defined(__AVR_ATmega2560__)
		OCR1A = s;
	#else
		#error "This chip is not supported!"
	#endif
}

void PWMController::initPWM2(uint8_t freq)
{
	#if defined(__AVR_ATmega324p__)
		TCCR2A |= (1 << COM2B1) | (1 << WGM20) | (1 << WGM21); // fast PWM, turn on oc2b
		TCCR2B = freq & 0x7;
		OCR2B = 0;
	#elif defined(__AVR_ATmega2560__)
		// Nna arduino mega, pin 3 = PE5 (OC3C)
		TCCR3A |= (1 << COM1C1) | (1 << WGM10); // fast PWM, turn on oc3c
		TCCR3B = (freq & 0x7) | (1 << WGM12);
		OCR3C = 0;
		
		DDRE |= 1 << PE5;
	#else
		#error "This chip is not supported!"
	#endif
}


void PWMController::setPWM2 (uint8_t s)
{
	#if defined(__AVR__ATmega324p)
		OCR2B = s;
	#elif defined(__AVR_ATmega2560__)
		// atmega2560, pin 11 = PB5 (OC1A)
		OCR3C = s;
	#else
		#error "This chip is not supported!"
	#endif
}

void PWMController::initPWM3 (uint8_t freq)
{
	#if defined(__AVR_ATmega324p__)
		 // use PWM from timer0A / PD6 (pin 6)
		 TCCR0A |= _BV(COM0A1) | _BV(WGM00) | _BV(WGM01); // fast PWM, turn on OC0A
		 //TCCR0B = freq & 0x7;
		 OCR0A = 0;
	#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
		// na ATmega2560 , pin 6 = PH3 (OC4A)
		TCCR4A |= _BV(COM1A1) | _BV(WGM10); // fast PWM, turn on oc4a
		TCCR4B = (freq & 0x7) | _BV(WGM12);
		//TCCR4B = 1 | _BV(WGM12);
		OCR4A = 0;
	
		DDRH |= 1 << PH3; 
	#else
		#error "This chip is not supported!"
	#endif
	//pinMode(6,OUTPUT);
}

void PWMController::setPWM3 (uint8_t s)
{
	#if defined(__AVR_ATmega324p__)
		OCR0A = s;
	#elif defined(__AVR_ATmega2560__)
		OCR4A = s;
	#else	
		#error "This chip is not supported!"
	#endif
}

void PWMController::initPWM4 (uint8_t freq)
{
	#if defined(__AVR_ATmega324p)
		// use PWM from timer0B / PD5 (pin 5)
		TCCR0A |= _BV(COM0B1) | _BV(WGM00) | _BV(WGM01); // fast PWM, turn on oc0a
		//TCCR0B = freq & 0x7;
		OCR0B = 0;
	#elif defined(__AVR_ATmega2560__)
		 // on ATmega2560, pin 5 = PE3 (OC3A)
		 TCCR3A |= _BV(COM1A1) | _BV(WGM10); // fast PWM, turn on oc3a
		 TCCR3B = (freq & 0x7) | _BV(WGM12);
		 //TCCR4B = 1 | _BV(WGM12);
		 OCR3A = 0;
		
		 DDRE |= 1 << PE3;
	#else
		#error "This chip is not supported"!
	#endif
	//pinMode(5, OUTPUT);
}


void PWMController::setPWM4 (uint8_t s)
{
	#if defined(__AVR_ATmega324p__)
		OCR0B = s;
	#elif defined(__AVR_ATmega2560__)
		OCR3A = s;
	#else	
		#error "This chips is not supported!"
	#endif
}


