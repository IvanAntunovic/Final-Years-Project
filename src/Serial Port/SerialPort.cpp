#include "SerialPort.h"

#ifndef F_CPU
#define		F_CPU	16000000UL
#endif

#if defined(__AVR_ATmega324p__)
	#define		F_CPU	1000000UL
#endif

#if defined(__AVR_ATmega2560__)
	#define			F_CPU	16000000UL
#endif

#if (BUFFER_SIZE & BUFFER_MASK)
	#error RX buffer size is not a power of 2
#endif 
#if (BUFFER_SIZE & BUFFER_MASK)
	#error TX buffer size is not a power of 2
#endif

void SerialPort::open(uint16_t baudRate, uint8_t portSelected)
{
	uint16_t baud_setting = (F_CPU / 4 / baudRate - 1) / 2;
	
	this->portSelected = portSelected;
	this->serialTransmitter = new SerialCommTransmitter(portSelected);
	this->serialReceiver = new SerialCommReceiver(portSelected);
	
	if (portSelected == 0)
	{
		/* Initialize USART0 */
			
		/* Set the baud rate */
		UBRR0H = (unsigned char) (baud_setting >> 8);
		UBRR0L = (unsigned char) baud_setting;
			
		/* Enable USART receiver and transmitter */
		UCSR0B = ((1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0));
			
		/* Double the USART Transmission Speed */
		UCSR0A = (1 << U2X0);
			
		/* Set frame format: 8 data bits 1 stop bit */
		UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	}
	else if (portSelected == 1)
	{
		/* Initialize USART1 */
		
		/* Set the baud rate */
		UBRR1H = (unsigned char) (baud_setting >> 8);
		UBRR1L = (unsigned char) baud_setting;
		
		/* Enable USART receiver and transmitter */
		UCSR1B = (1 << RXCIE1) | (1 << RXEN1) | (1 << TXEN1);
		
		/* Double the USART Transmission Speed */
		UCSR1A = (1 << U2X1);
		
		/* Set frame format: 8 data bits 1 stop bit */
		UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);
	}
	else if (portSelected == 2)
	{
		/* Initialize USART1 */
		
		/* Set the baud rate */
		UBRR2H = (unsigned char) (baud_setting >> 8);
		UBRR2L = (unsigned char) baud_setting;
		
		/* Enable USART receiver and transmitter */
		UCSR2B = (1 << RXCIE2) | (1 << RXEN2) | (1 << TXEN2);
		
		/* Double the USART Transmission Speed */
		UCSR2A = (1 << U2X2);
		
		/* Set frame format: 8 data bits 1 stop bit */
		UCSR2C = (1 << UCSZ21) | (1 << UCSZ20);
	}
	else if (portSelected == 3)
	{
		/* Initialize USART1 */
		
		/* Set the baud rate */
		UBRR3H = (unsigned char) (baud_setting >> 8);
		UBRR3L = (unsigned char) baud_setting;
		
		/* Enable USART receiver and transmitter */
		UCSR3B = (1 << RXCIE3) | (1 << RXEN3) | (1 << TXEN3);
		
		/* Double the USART Transmission Speed */
		UCSR3A = (1 << U2X3);
		
		/* Set frame format: 8 data bits 1 stop bit */
		UCSR3C = (1 << UCSZ31) | (1 << UCSZ30);
	}
	sei();
}

void SerialPort::close()
{
	delete this->serialTransmitter;
	delete this->serialReceiver;
	
	if (this->portSelected == 0)
	{
		UCSR0B = ~((1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0));
	}
	else if (this->portSelected == 1)
	{
		UCSR1B &= ~((1 << RXCIE1) | (1 << RXEN1) | (1 << TXEN1));
	}
}

int8_t SerialPort::getRxInterruptStatusCode(void)
{
	return this->serialReceiver->getInterruptStatusCode();
}

unsigned char SerialPort::available()
{
	return SerialPort::serialReceiver->available();
}

unsigned char SerialPort::availableForWrite()
{
	return SerialPort::serialTransmitter->availableForWrite();
}

int8_t SerialPort::readBytes(uint8_t* buffer, uint8_t length)
{
	return SerialPort::serialReceiver->readBytes(buffer, length);
}

int8_t SerialPort::writeBytes(uint8_t* bytes, uint8_t length)
{
	return SerialPort::serialTransmitter->writeBytes(bytes, length);
}

int8_t SerialPort::writeString(const char* string)
{
	uint8_t bytesWritten;
	
	for (bytesWritten = 0; *string; bytesWritten++)
	{
		this->serialTransmitter->writeByte(*string++);
	}
	return bytesWritten;
}

int8_t SerialPort::write(int integerVal)
{
	uint8_t numberOfDigits;
	uint8_t* buffer = NULL;
	int tempValue;
	int8_t retVal = -1;
	
	tempValue = integerVal;
	for (numberOfDigits = 0; tempValue != 0; numberOfDigits++)
	{
		tempValue = tempValue / 10;
	}
	
	if (integerVal < 0)
	{
		// We need to allocate extra byte for '-' sign
		numberOfDigits++;	
	}

	buffer = new uint8_t[numberOfDigits + 1];
	if (buffer != NULL)
	{
		itoa(integerVal, (char*)buffer, 10);
		memset(&buffer[numberOfDigits + 1], '\0', 1);
		retVal = writeBytes(buffer, numberOfDigits);
		delete[] buffer;
	}
	return retVal;
}


int8_t SerialPort::writeInteger(int value, uint8_t base)
{
	int integerCopy;
	uint8_t digitCnt = 0;
	char* buffer;
	int8_t retVal;
	
	while (integerCopy > 0)
	{
		integerCopy /= 10;
		digitCnt++;
	}
	
	buffer = new char[digitCnt];
	this->integerToArray(value, buffer, base);
	retVal = this->writeString(buffer);
	delete [] buffer;
	
	return retVal;
}


char* SerialPort::integerToArray(int value, char *result, int base)
{
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
	} while ( value );

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while (ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr--= *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;

}

int8_t SerialPort::writeFloat(double floatNo)
{
	int integerNo;
	int integerPartCnt = 0;
	int fractionalPartCnt = 0;
	uint8_t buffer[10];
	bool isNumberNegative = false;

	if (floatNo < 0.0)
	{
		isNumberNegative = true;
	}
	
	integerNo = (int)floatNo;
	while (integerNo > 0)
	{
		floatNo /= 10;
		integerNo = (int)floatNo;
		integerPartCnt++;
	}
	
	//// If number is negative add '-' sign
	//if (isNumberNegative)
	//{
	//buffer[0] = '-';
	//floatNo = -floatNo;
	//// Increment counter in order to place '.' sign at right index position
	//integerPartCnt++;
	//}

	*(buffer + integerPartCnt) = '.';
	floatNo *= 10;
	integerNo = (int)floatNo;
	floatNo = floatNo - integerNo;

	// Until fractional number is greater than 0
	while (integerNo > 0)
	{
		// Skip storing character at index where '.' has already been placed
		if (fractionalPartCnt == integerPartCnt)
		{
			fractionalPartCnt++;
		}
		// Add fractional number
		*(buffer + fractionalPartCnt) = '0' + integerNo;
		floatNo *= 10;
		integerNo = (int)floatNo;
		floatNo = floatNo - integerNo;

		fractionalPartCnt++;
	}
	*(buffer + fractionalPartCnt) = '\0';
	
	return this->writeString( (const char*)buffer );
}
