#include "MessageSerialization.h"
#include "Message.h"

const char* MessageSerialization::serialize(Message* serialMessage)
{
	uint8_t serializedBufferLen;
	uint8_t* serializedBuffer;
	uint8_t* tempDataBuffer;
	
	// We add five more bytes - STX, ETX, dataType, dataLength and '\0' bytes 
	serializedBufferLen = serialMessage->getDataLength() + 4 + 1;
	serializedBuffer = new uint8_t[serializedBufferLen];

	if ( serializedBuffer == nullptr )
	{
      return nullptr;
	}
	
	memset(serializedBuffer, 0, serializedBufferLen);
	serializedBuffer[0] = STX;

	serializedBuffer[serializedBufferLen - 2] = ETX;
	serializedBuffer[serializedBufferLen - 1] = '\0';
	serializedBuffer[MESSAGE_DATA_TYPE_INDEX] = serialMessage->getDataType();
	serializedBuffer[MESSAGE_DATA_LENGTH_INDEX] = serialMessage->getDataLength();
	tempDataBuffer = serialMessage->getDataBuffer();
	memcpy( &serializedBuffer[MESSAGE_DATA_START_INDEX], tempDataBuffer, serialMessage->getDataLength() );

	delete tempDataBuffer;
	return (const char*)serializedBuffer;
}