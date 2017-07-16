#ifndef  _SERIALCOMMRECEIVER_H_
#define	 _SERIALCOMMRECEIVER_H_

#include "Readable.h"
#include "CircularQueue.h"
#include "SerialErrno.h"
#include <avr/interrupt.h>
//#include "FreeRTOS.h"
//#include "semphr.h"

class SerialCommReceiver : public Readable
{
	private:
		CircularQueue rxQueue;
		int8_t interruptStatusCode;
		uint8_t currentState;
		enum _t_eState
		{
			LOCKED       = 0,
			RELEASED     = 1
		};
		//SemaphoreHandle_t rxBinarySemaphore;
	public:
		static SerialCommReceiver* sInstance[4];

	public:
		SerialCommReceiver(uint8_t portSelected);
		int8_t readBytes(uint8_t* buffer, uint8_t length);
		inline int8_t readByte(uint8_t* byte);
		uint8_t available(void);
		int8_t getInterruptStatusCode(void);
		inline void interrupt_RX0_Handler(void);
		inline void interrupt_RX1_Handler(void);
		inline void interrupt_RX2_Handler(void);
		inline void interrupt_RX3_Handler(void);
};

#endif
