#include "MessageProcessor.h"
#include "MessageEncoder.h"
#include "MessageSerialization.h"
#include "Message.h"
#include "SerialPort.h"

MessageProcessor::MessageProcessor(SerialPort* pcSerialPort)
{
	this->pcSerialPort = pcSerialPort;
	this->messageSerialization = new MessageSerialization();
	this->messageEncoder = new MessageEncoder();
}

MessageProcessor::~MessageProcessor()
{
	delete this->messageSerialization;
	delete this->messageEncoder;
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
	
	//this->pcSerialPort->println(serializedBuffer);
	this->pcSerialPort->writeString(serializedBuffer);
	
	delete encodedMessage;
	delete[] serializedBuffer;
	return MESSAGE_PROCESSOR_OK;
}