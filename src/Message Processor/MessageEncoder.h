#ifndef _MESSAGE_ENCODER_H_
#define _MESSAGE_ENCODER_H_

#include <stdint.h>

class Message;

class MessageEncoder
{
	public:
		Message* encode(uint8_t dataType, uint8_t dataLength, uint8_t* dataBuffer);
};

#endif