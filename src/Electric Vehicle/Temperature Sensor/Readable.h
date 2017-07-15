#pragma once
#ifndef _READABLE_H_
#define _READABLE_H_

#include <stdint.h>

class Readable
{
	public:
	    ~Readable() {}
		virtual int8_t readBytes(uint8_t* buffer, uint8_t length) = 0;
		//virtual int8_t readByte(uint8_t byte) = 0;
		//virtual uint8_t available() = 0;
};

#endif
