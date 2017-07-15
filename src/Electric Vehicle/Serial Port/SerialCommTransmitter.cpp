#include "SerialCommTransmitter.h"

#ifndef extern "C" { void __cxa_pure_virtual() { while (1); }}
#endif

SerialCommTransmitter* SerialCommTransmitter::sInstance[] = {NULL};

SerialCommTransmitter::SerialCommTransmitter(uint8_t _portSelected) : portSelected (_portSelected)
{	
	if (portSelected == 0)
	{
		SerialCommTransmitter::sInstance[portSelected] = this;
	}
	else if (portSelected == 1)
	{
		SerialCommTransmitter::sInstance[portSelected] = this;
	}
	else if (portSelected == 2)
	{
		SerialCommTransmitter::sInstance[portSelected] = this;
	}
}

uint8_t SerialCommTransmitter::availableForWrite()
{
	return BUFFER_SIZE - this->txQueue.getAvailableItems();
}

int8_t SerialCommTransmitter::writeByte(uint8_t byte)
{
	// wait until queue is empty
	//unsigned char tempTail = (txQueue.tail + 1) & BUFFER_MASK;b
	while (txQueue.isFull());

	// check if byte is successfully pushed into queue
	if (txQueue.enqueue(byte) == QUEUE_OK)
	{
		// Check which port is selected
		// enable USART Data Register Empty Interrupt
		if (this->portSelected == 0)
		{
			UCSR0B |= (1 << UDRIE0); 
		}
		else if (this->portSelected == 1)
		{
			UCSR1B |= (1 << UDRIE1); 
		}
		else if (this->portSelected == 2)
		{
			UCSR2B |= (1 << UDRIE2); 
		}
			
		return SERIAL_OK;
	}
	return SERIAL_NOK;
}

int8_t SerialCommTransmitter::writeBytes(uint8_t* bytes, uint8_t length)
{
	uint8_t bytesWrittenCnt = 0;
	
	for (uint8_t index = 0; index < length; index++)
	{
		if (this->writeByte(bytes[index]) == SERIAL_OK)
		{
			bytesWrittenCnt++;
		}
	}
	return bytesWrittenCnt;
}

void SerialCommTransmitter::interrupt_UDRE0_Handler(void)
{
	uint8_t tempByte;
	
	//Check if there is available data to transmit
	if (this->txQueue.dequeue(&tempByte) == QUEUE_OK)
	{
		UDR0 = tempByte;
	}
	else
	{
		//If all data is transmitted
		//Disable USART Data Register Interrupt
		//If we do not disable ISR, the program will keep jumping in this routine
		UCSR0B &= ~(1<<UDRIE0);
	}
}

void SerialCommTransmitter::interrupt_UDRE1_Handler(void)
{
	uint8_t tempByte;
	
	//Check if there is available data to transmit
	if (this->txQueue.dequeue(&tempByte) == QUEUE_OK)
	{
		UDR1 = tempByte;
	}
	else
	{
		//If all data is transmitted
		//Disable USART Data Register Interrupt
		//If we do not disable ISR, the program will keep jumping in this routine
		UCSR1B &= ~(1<<UDRIE1);
	}
}

void SerialCommTransmitter::interrupt_UDRE2_Handler(void)
{
	uint8_t tempByte;
	
	//Check if there is available data to transmit
	if (this->txQueue.dequeue(&tempByte) == QUEUE_OK)
	{
		UDR2 = tempByte;
	}
	else
	{
		//If all data is transmitted
		//Disable USART Data Register Interrupt
		//If we do not disable ISR, the program will keep jumping in this routine
		UCSR2B &= ~(1<<UDRIE2);
	}
}

ISR(USART0_UDRE_vect)
{
	SerialCommTransmitter::sInstance[0]->interrupt_UDRE0_Handler();
}

ISR(USART1_UDRE_vect)
{
	SerialCommTransmitter::sInstance[1]->interrupt_UDRE1_Handler();
}

ISR(USART2_UDRE_vect)
{
	SerialCommTransmitter::sInstance[2]->interrupt_UDRE2_Handler();
}

