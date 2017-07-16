#pragma once
#ifndef _WRITABLE_H_
#define _WRITABLE_H_

#include <stdint.h>

class Writable
{
	public:
		~Writable() {}
		virtual int8_t writeBytes(uint8_t* buffer, uint8_t length) = 0;
		//virtual uint8_t availableForWrite() = 0;
};

#endif // !_TRANSMITTER_H_
