#ifndef _MESSAGE_SERIALIZATION_H_
#define _MESSAGE_SERIALIZATION_H_

#include <stdint.h>
#include "Arduino.h"
#include "HardwareSerial.h"

extern HardwareSerial Serial;

#define STX 0x02
#define ETX 0x03
#define MESSAGE_DATA_TYPE_INDEX   1
#define MESSAGE_DATA_LENGTH_INDEX 2
#define MESSAGE_DATA_START_INDEX  3

#define MESSAGE_SERIALIZATION_OK   0
#define MESSAGE_SERIALIZATION_NOK -1

class Message;

class MessageSerialization
{
	public:
		const char* serialize(Message* serialMessage);
};

#endif