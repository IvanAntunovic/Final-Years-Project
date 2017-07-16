#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <stdint.h>
#include <string.h>

/** _________________________________________________
 * |     |              |        |      |      |     |
 * | STX | MESSAGE TYPE | LENGTH | DATA | '\0' | ETX |
 * |_____|______________|________|______|______|_____|
 */

class Message
{
	private:
		uint8_t dataType;
		uint8_t dataLength;
		uint8_t* dataBuffer;
		
	public:
		Message(uint8_t dataType, uint8_t dataLength, uint8_t* dataBuffer);
		~Message();
		uint8_t getDataType();
		uint8_t getDataLength();
		const char* getDataBuffer();
};

#endif