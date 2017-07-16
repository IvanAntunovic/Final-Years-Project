#include "MessageProcessor.h"
#include "MessageEncoder.h"
#include "MessageSerialization.h"
#include "MessageDecoder.h"
#include "MessageDeserializaton.h"
#include "Message.h"
#include "SerialPort.h"

MessageProcessor::MessageProcessor(SerialPort* serialPort) 
{
  this->serialPort = serialPort;
  this->messageSerialization = new MessageSerialization();
  this->messageEncoder = new MessageEncoder();
  this->messageDeserialization = new MessageDeserialization();
  this->messageDecoder = new MessageDecoder();

}

MessageProcessor::~MessageProcessor()
{
  delete this->messageSerialization;
  delete this->messageEncoder;
  delete this->messageDeserialization;
  delete this->messageDecoder;

}

int8_t MessageProcessor::processTransmitData(uint8_t dataType, uint8_t dataLength, uint8_t* dataBuffer)
{
	Message* encodedMessage;
	const char* serializedBuffer; 
	
	encodedMessage = this->messageEncoder->encode(dataType, dataLength, dataBuffer);
	if ( encodedMessage == NULL )
	{
	  return MESSAGE_PROCESSOR_NULL_PTR;
	}
	
	serializedBuffer = this->messageSerialization->serialize(encodedMessage);
	if ( serializedBuffer == NULL )
	{
	  return MESSAGE_PROCESSOR_NULL_PTR;
	}
	
	this->serialPort->writeString(serializedBuffer);
	
	delete encodedMessage;
	delete[] serializedBuffer;
	return MESSAGE_PROCESSOR_OK;
}

Message MessageProcessor::processReceivedData(void)
{
	uint8_t receivedByte;
	
	if ( this->serialPort->available() )
	{
	  this->serialPort->readBytes(&receivedByte, 1);
	  this->messageDeserialization->deserialize(receivedByte);
	  if ( this->messageDeserialization->isDeserialized() == MESSAGE_DESERIALIZATION_OK )
	  {
	    int8_t receieveBufferLen;
		uint8_t* receieveBuffer;
		int8_t retVal;
			
		receieveBufferLen = this->messageDeserialization->getReceiveBufferLen();
		receieveBuffer = new uint8_t[receieveBufferLen];
		retVal = this->messageDeserialization->getDeserializedBuffer(receieveBuffer, receieveBufferLen);
		return this->messageDecoder->decode( receieveBuffer, receieveBufferLen );
	  }
	}
	return Message(0, 0, NULL);
}

