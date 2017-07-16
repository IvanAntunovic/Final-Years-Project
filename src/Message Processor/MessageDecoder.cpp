/*
 * MessageDecoder.cpp
 *
 * Created: 7/16/2017 3:57:28 PM
 *  Author: fairenough
 */ 
#include "MessageDecoder.h"
#include "Message.h"
#include "SerialPort.h"

Message MessageDecoder::decode(uint8_t* deserializedBuffer, uint8_t deserializedBufferLen)
{
   uint8_t dataType;
   uint8_t dataLength;
   uint8_t* data;
	
   dataType = deserializedBuffer[MESSAGE_DATA_TYPE_INDEX];
   dataLength = deserializedBuffer[MESSAGE_DATA_LENGTH_INDEX];
   data = new uint8_t[ dataLength ];
   //if ( data == NULL )
   //{
	  //return NULL;
   //}
   memcpy( &data[0], &deserializedBuffer[ MESSAGE_DATA_START_INDEX ], dataLength );
   Message message( dataType, dataLength, data);
	
   delete data;
   return message;	
}