
/*
 * MessageDeserialization.cpp
 *
 * Created: 7/16/2017 12:55:41 PM
 *  Author: fairenough
 */ 
#include "MessageDeserializaton.h"
#include "SerialPort.h"

MessageDeserialization::MessageDeserialization()
{
  this->receiveByteBuffer = new uint8_t[RECEIVE_BUFFER_START_SIZE];
  this->receiveByteBufferCurrentSize = RECEIVE_BUFFER_START_SIZE;
  this->receiveByteBufferLen = 0;
}

/*
*	@Return value: returns length
*/
int8_t MessageDeserialization::getDeserializedBuffer(uint8_t* buffer, uint8_t bufferLength)
{
	uint8_t  deserializedBufferLen;
	
	if ( this->isDeserialized() != MESSAGE_DESERIALIZATION_OK )
	{
	  return MESSAGE_DESERIALIZATION_NOK;
	}
	
	if ( bufferLength < this->receiveByteBufferLen )
	{
	  return MESSAGE_DESERIALIZATION_BUFFER_LENGTH_NOT_ENOUGH;
	}
	
	// copy current data to temporary buffer
	memcpy ( &buffer[0], &(this->receiveByteBuffer[0]), this->receiveByteBufferLen );
	memset ( &(this->receiveByteBuffer[0]), '\0', this->receiveByteBufferLen );
	
	deserializedBufferLen = this->receiveByteBufferLen;
	this->receiveByteBufferLen = 0;
	return deserializedBufferLen;
}

int8_t MessageDeserialization::isDeserialized(void)
{
	if ( this->receiveByteBufferLen < 0 )
	{
		return false;
	}

	if ( this->contains( STX, this->receiveByteBuffer, this->receiveByteBufferLen )  )
	{
	  if ( this->contains( ETX, this->receiveByteBuffer, this->receiveByteBufferLen ) )
	  {
		int8_t endIndex;
		int8_t startIndex;
			
		startIndex = 0;
		endIndex = this->receiveByteBufferLen;
		if ( this->receiveByteBufferCurrentSize - endIndex  <= 0 )
		{
			return MESSAGE_DESERIALIZATION_NOK;
		}
		// Clear data buffer from end of index to the end of its own size
		memset( &( this->receiveByteBuffer[endIndex] ), '\0', this->receiveByteBufferCurrentSize - endIndex );
		this->receiveByteBufferLen = endIndex - startIndex;
		return MESSAGE_DESERIALIZATION_OK;
	  }
	}
	else
	{
	  this->receiveByteBufferLen = 0;
	  return MESSAGE_DESERIALIZATION_NOK;
	}
	return MESSAGE_DESERIALIZATION_NOK;
}

int8_t MessageDeserialization::deserialize(uint8_t byte)
{
	uint8_t* tempBuffer;

	// check if we current buffer index is equal to buffer size
	if ( this->receiveByteBufferLen >= this->receiveByteBufferCurrentSize - 1 )
	{
	  // allocate temporary buffer
	  tempBuffer = new uint8_t[ this->receiveByteBufferLen ];
	  if ( tempBuffer == NULL )
	  {
		return MESSAGE_DESERIALIZATION_NULL_PTR;
	  }
	  // copy current data to temporary buffer
	  memcpy ( &tempBuffer[0], &(this->receiveByteBuffer[0]), this->receiveByteBufferLen );
	  // Allocate new buffer with size 2x bigger than the previous one
	  this->receiveByteBufferCurrentSize = ( (int)( (this->receiveByteBufferLen + 1) / 10) * 2 * RECEIVE_BUFFER_START_SIZE );
	  this->receiveByteBuffer = new uint8_t[ this->receiveByteBufferCurrentSize ];
	  if ( this->receiveByteBuffer == NULL )
	  {
	 	return MESSAGE_DESERIALIZATION_NULL_PTR;
	  }
		
	  // copy data from temporary buffer to the new buffer
	  memcpy ( &(this->receiveByteBuffer[0]), &tempBuffer[0], this->receiveByteBufferLen );
	  // store byte to the buffer
	  this->receiveByteBuffer[ ++(this->receiveByteBufferLen) ] = byte;
	  delete tempBuffer;
	}
	else
	{
	  this->receiveByteBuffer[ (this->receiveByteBufferLen)++ ] = byte;	
	}
	return MESSAGE_DESERIALIZATION_OK;
}

bool MessageDeserialization::contains(uint8_t character, uint8_t* buffer, int8_t bufferLength)
{
	for (int8_t index = 0; index < bufferLength; ++index)
	{
	  if ( memcmp( &buffer[index], &character, 1 ) == 0 )
	  {
	  	return true;
	  }
	}
	return false;
}