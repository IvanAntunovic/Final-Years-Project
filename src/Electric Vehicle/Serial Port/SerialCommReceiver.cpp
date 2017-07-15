#include "SerialCommReceiver.h"

#ifndef extern "C" { void __cxa_pure_virtual() { while (1); }}
#endif

SerialCommReceiver* SerialCommReceiver::sInstance[] = {NULL};

SerialCommReceiver::SerialCommReceiver(uint8_t portSelected)
{
	this->currentState = RELEASED;
	this->interruptStatusCode = SERIAL_OK;
	
	if (portSelected == 0)
	{
		SerialCommReceiver::sInstance[portSelected] = this;
	}
	else if (portSelected == 1)
	{
		SerialCommReceiver::sInstance[portSelected] = this;
	}
	else if (portSelected == 2)
	{
		SerialCommReceiver::sInstance[portSelected] = this;
	}

	//this->rxBinarySemaphore = xSemaphoreCreateBinary();
	//
	//if (this->rxBinarySemaphore != NULL)
	//{
		////Handle error
	//}
}

unsigned char SerialCommReceiver::available()
{
	return rxQueue.getAvailableItems();
}

int8_t SerialCommReceiver::getInterruptStatusCode()
{
	return this->interruptStatusCode;
}

int8_t SerialCommReceiver::readByte(uint8_t* byte)
{
	//if ( xSemaphoreTake(this->rxBinarySemaphore, 0) == pdPASS)
	int8_t retVal;
	
	if (this->currentState == LOCKED)
	{
		return SERIAL_NOK;
	}
	
	if (!rxQueue.isEmpty())
	{
		retVal = rxQueue.dequeue(byte);
		if (retVal != QUEUE_NOK)
		{
			return SERIAL_DEQUEUE_NOK;
		}
		return SERIAL_OK;
	}
	return SERIAL_NOK;
}

int8_t SerialCommReceiver::readBytes(uint8_t* buffer, uint8_t length)
{
	uint8_t bytesRead = 0;

	for (uint8_t index = 0; index < length && this->rxQueue.isAvailable(); ++index)
	{
		if(this->readByte(&buffer[index]) == SERIAL_OK)
		{
			bytesRead++;
		}
	}
	return bytesRead;
}

void SerialCommReceiver::interrupt_RX0_Handler(void)
{
	uint8_t readByte;
	
	readByte = UDR0;
	if (!this->rxQueue.isFull())
	{
		this->currentState = LOCKED;
		// add new item to queue
		if (this->rxQueue.enqueue(readByte) != QUEUE_OK)
		{
			// Flag ERROR - receive queue overflow!
			this->interruptStatusCode = SERIAL_BUFFER_OVERFLOW;
		}
		else
		{
			this->interruptStatusCode = SERIAL_OK;
		}
		this->currentState = RELEASED;
		//xSemaphoreGiveFromISR(this->serialReceiver.rxBinarySemaphore, NULL);
	}
	else
	{
		//Handle buffer overflow
		this->interruptStatusCode = SERIAL_BUFFER_FULL;
	}
}

void SerialCommReceiver::interrupt_RX1_Handler(void)
{
	uint8_t readByte;
	
	readByte = UDR1;
	//Check if queue is not full
	if (!this->rxQueue.isFull())
	{
		this->currentState = LOCKED;
		// add new item to the queue
		if (this->rxQueue.enqueue(readByte) != QUEUE_OK)
		{
			// Flag ERROR - receive queue overflow!
			this->interruptStatusCode = SERIAL_BUFFER_OVERFLOW;
		}
		else
		{
			this->interruptStatusCode = SERIAL_OK;
		}
		this->currentState = RELEASED;
		//xSemaphoreGiveFromISR(this->serialReceiver.rxBinarySemaphore, NULL);
	}
	else
	{
		//Handle buffer overflow
		this->interruptStatusCode = SERIAL_BUFFER_FULL;
	}
}

void SerialCommReceiver::interrupt_RX2_Handler(void)
{
	uint8_t readByte;
	
	readByte = UDR2;
	//Check if queue is not full
	if (!this->rxQueue.isFull())
	{
		this->currentState = LOCKED;
		// add new item to the queue
		if (this->rxQueue.enqueue(readByte) != QUEUE_OK)
		{
			// Flag ERROR - receive queue overflow!
			this->interruptStatusCode = SERIAL_BUFFER_OVERFLOW;
		}
		else
		{
			this->interruptStatusCode = SERIAL_OK;
		}
		this->currentState = RELEASED;
		//xSemaphoreGiveFromISR(this->serialReceiver.rxBinarySemaphore, NULL);
	}
	else
	{
		//Handle buffer overflow
		this->interruptStatusCode = SERIAL_BUFFER_FULL;
	}
}


ISR(USART0_RX_vect)
{
	SerialCommReceiver::sInstance[0]->interrupt_RX0_Handler();
}

ISR(USART1_RX_vect)
{
	SerialCommReceiver::sInstance[1]->interrupt_RX1_Handler();
}

ISR(USART2_RX_vect)
{
	SerialCommReceiver::sInstance[2]->interrupt_RX2_Handler();
}

