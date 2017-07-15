#pragma once
#ifndef  _SERIALCOMMTRANSMITTER_H_
#define  _SERIALCOMMTRANSMITTER_H_

#include "CircularQueue.h"
#include "Writable.h"
#include "SerialErrno.h"
#include <avr/interrupt.h>
#include <stdlib.h>


class SerialCommTransmitter : public Writable
{
	private:
		CircularQueue txQueue;
		uint8_t portSelected;
		
	public:
		static SerialCommTransmitter* sInstance[3];

	public:
		SerialCommTransmitter(uint8_t portSelected);
		int8_t writeByte(uint8_t byte);
		int8_t writeBytes(uint8_t* bytes, uint8_t length);
		uint8_t availableForWrite(void);
		inline void interrupt_UDRE0_Handler(void);
		inline void interrupt_UDRE1_Handler(void);
		inline void interrupt_UDRE2_Handler(void);
};

#endif // !_SERIALCOMMTRANSMITTER_H_




