#include "MessageEncoder.h"
#include "Message.h"

Message* MessageEncoder::encode(uint8_t dataType, uint8_t dataLength, uint8_t* dataBuffer)
{
	return new Message(dataType, dataLength, dataBuffer);
}