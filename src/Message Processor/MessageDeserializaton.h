
/*
 * MessageDeserializaton.h
 *
 * Created: 7/16/2017 12:52:21 PM
 *  Author: fairenough
 */ 

#ifndef _MESSAGE_DESERIALIZATION_H_
#define _MESSAGE_DESERIALIZATION_H_

#include <stdint.h>
#include <string.h>
#include "MessageProcessorCodes.h"

class SerialPort;

class MessageDeserialization
{
  private:
    uint8_t* receiveByteBuffer;
    int8_t receiveByteBufferLen;
    int8_t receiveByteBufferCurrentSize;

  public:
    MessageDeserialization();
    int8_t getDeserializedBuffer(uint8_t* buffer, uint8_t bufferLength);
    int8_t getReceiveBufferLen(void) { return this->receiveByteBufferLen; }
    int8_t deserialize(uint8_t byte);
    int8_t isDeserialized(void);
		
  private:	
	bool contains(uint8_t character, uint8_t* buffer, int8_t bufferLength);
};

#endif