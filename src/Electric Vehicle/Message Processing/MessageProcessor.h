#ifndef _MESSAGE_PROCESSOR_H_
#define _MESSAGE_PROCESSOR_H_

#include <stdint.h>

class MessageSerialization;
class MessageEncoder;
class SerialPort;

#define MESSAGE_PROCESSOR_OK   0
#define MESSAGE_PROCESSOR_NOK -1
#define MESSAGE_PROCESSOR_NULL_PTR -2

class MessageProcessor
{
	public:
		MessageSerialization* messageSerialization;
		MessageEncoder* messageEncoder;
		SerialPort* pcSerialPort;
		MessageProcessor(SerialPort* pcSerialPort);
		~MessageProcessor();
		int8_t processTransmitData(uint8_t dataType, uint8_t dataLength, uint8_t* dataBuffer);
};

#endif