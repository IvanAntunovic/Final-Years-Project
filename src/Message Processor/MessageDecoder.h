
/*
 * MessageDecoder.h
 *
 * Created: 7/16/2017 3:44:37 PM
 *  Author: fairenough
 */ 
#ifndef _MESSAGE_DECODER_H_
#define _MESSAGE_DECODER_H_

#include "MessageProcessorCodes.h"
#include <stdint.h>
#include <string.h>

class Message;

class MessageDecoder
{
  public: 
    Message decode(uint8_t* deserializedBuffer, uint8_t deserializedBufferLen);	
};

#endif