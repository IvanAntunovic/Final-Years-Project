/*
 * SerialTypes.cpp
 *
 * Created: 5/23/2017 11:04:41 PM
 *  Author: fairenough
 */ 

#ifndef  _SERIAL_TYPES_H_
#define  _SERIAL_TYPES_H_

#ifndef NULL
#define NULL 0
#endif

#define SERIAL_OK				 	 0
#define SERIAL_NOK					-1  
#define SERIAL_RX_TIME_OUT			-2
#define SERIAL_READ_LOCKED			-3
#define SERIAL_BYTE_READ_NOK		-4
#define SERIAL_BUFFER_FULL    		-5
#define SERIAL_ENQUEUE_NOK      	-6
#define SERIAL_DEQUEUE_NOK			-7
#define SERIAL_INVALID_PARAMETER    -8
#define SERIAL_RX_LOCKED			-9
#define SERIAL_QUEUE_EMPTY			-10
#define SERIAL_BUFFER_OVERFLOW		-11


#endif
