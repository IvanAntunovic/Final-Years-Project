#ifndef _MESSAGE_SERIALIZATION_H_
#define _MESSAGE_SERIALIZATION_H_

#include <stdint.h>
#include "MessageProcessorCodes.h"

class Message;

class MessageSerialization
{
  public:
    const char* serialize(Message* serialMessage);
};

#endif