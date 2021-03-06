#ifndef _MESSAGE_PROCESSOR_H_
#define _MESSAGE_PROCESSOR_H_

#include "MessageProcessorCodes.h"
#include <stdint.h>

class Message;
class MessageSerialization;
class MessageEncoder;
class MessageDeserialization;
class MessageDecoder;
class SerialPort;

class MessageProcessor
{
  private:
    SerialPort* serialPort;
    MessageSerialization* messageSerialization;
    MessageEncoder* messageEncoder;
    MessageDeserialization* messageDeserialization;
    MessageDecoder* messageDecoder;

  public:
    MessageProcessor(SerialPort* serialPort);
    ~MessageProcessor();
    int8_t processTransmitData(uint8_t dataType, uint8_t dataLength, uint8_t* dataBuffer);
    Message processReceivedData(void);
};

#endif