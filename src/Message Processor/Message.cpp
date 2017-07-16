#include "Message.h"

Message::Message(uint8_t dataType, uint8_t dataLength, uint8_t* dataBuffer)
{
	this->dataType = dataType;
	this->dataLength = dataLength;
	this->dataBuffer = new uint8_t[dataLength];
	memcpy(this->dataBuffer, dataBuffer, dataLength);
}

Message::~Message()
{
	delete[] this->dataBuffer;
}

uint8_t Message::getDataType()
{
	return this->dataType;
}

uint8_t Message::getDataLength()
{
	return this->dataLength;
}

const char* Message::getDataBuffer()
{
	uint8_t* returnDataBuffer;
	
	returnDataBuffer = new uint8_t[this->dataLength + 1];
	memcpy(returnDataBuffer, this->dataBuffer, this->dataLength);
	returnDataBuffer[this->dataLength] = '\0';
	return (const char*)returnDataBuffer;
}