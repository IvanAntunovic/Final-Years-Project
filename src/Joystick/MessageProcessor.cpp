#include "MessageProcessor.h"
#include "MessageEncoder.h"
#include "MessageSerialization.h"
#include "Message.h"

MessageProcessor::MessageProcessor(HardwareSerial* pcSerialPort)
{
	this->pcSerialPort = pcSerialPort;
	this->pcSerialPort->begin(9600);
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
	if ( encodedMessage == nullptr )
	{
	  return MESSAGE_PROCESSOR_NULL_PTR;
	}
	
	serializedBuffer = this->messageSerialization->serialize(encodedMessage);
	if ( serializedBuffer == nullptr )
	{
	  return MESSAGE_PROCESSOR_NULL_PTR;
	}
	
	//this->pcSerialPort->println(serializedBuffer);
	this->pcSerialPort->write(serializedBuffer);
	
	delete encodedMessage;
	delete[] serializedBuffer;
	return MESSAGE_PROCESSOR_OK;
}