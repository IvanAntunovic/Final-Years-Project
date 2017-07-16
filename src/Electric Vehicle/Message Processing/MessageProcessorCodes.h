
/*
 * MessageProcessorCodes.h
 *
 * Created: 7/15/2017 12:36:14 PM
 *  Author: fairenough
 */ 

/* Do not use codes 0x00 (STX) and 0x02 (ETX) for Message CODES! */
#ifndef  _MESSAGE_PROCESSOR_CODES_H_
#define  _MESSAGE_PROCESSOR_CODES_H_

#define STX 0x02
#define ETX 0x03

#define MESSAGE_DATA_TYPE_TEMPERATURE 0x04
#define MESSAGE_DATA_TYPE_KEEP_ALIVE  0x10
#define MESSAGE_DATA_TYPE_COMMAND     0x11


#define MESSAGE_DATA_TYPE_INDEX   1
#define MESSAGE_DATA_LENGTH_INDEX 2
#define MESSAGE_DATA_START_INDEX  3

#define MESSAGE_SERIALIZATION_OK   0
#define MESSAGE_SERIALIZATION_NOK -1

#define MESSAGE_DESERIALIZATION_OK  0
#define MESSAGE_DESERIALIZATION_NOK -1
#define MESSAGE_DESERIALIZATION_NULL_PTR -2
#define MESSAGE_DESERIALIZATION_BUFFER_LENGTH_NOT_ENOUGH -3

#define RECEIVE_BUFFER_START_SIZE 10

#ifndef NULL
#define NULL ( (void*)0 )
#endif

#endif
