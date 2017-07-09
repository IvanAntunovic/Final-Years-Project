#ifndef _MESSAGE_ENCODER_H_
#define _MESSAGE_ENCODER_H_

#define STX 0x02
#define ETX 0x03

class Message

class MessageEncoder
{
	public:
		Message encode(String inputDataBuffer, uint8_t dataType, uint8_t dataLength);
};

#endif