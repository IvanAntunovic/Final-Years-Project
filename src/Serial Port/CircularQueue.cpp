#include "CircularQueue.h"

CircularQueue::CircularQueue()
{
	this->head = 0;
	this->tail = 0;
	this->availableItems = 0;

	for (uint8_t index = 0; index < BUFFER_SIZE; ++index)
	{
		this->buffer[index] = 0;
	}
}

/**
 * @brief Returns if data available in the Circular Queue
 *
 * @param none
 *
 * @return true if any data is available for read
 * @return false if no data is available for read
 */
bool CircularQueue::isAvailable()
{
	if (this->availableItems)
	{
		return true;
	}
	return false;
}

/**
 * @brief 
 *
 * @param none
 *
 * @return  Returns number of available data in the Circular Queue
 */
uint8_t CircularQueue::getAvailableItems()
{
	return this->availableItems;
}

/**
 * @brief Method for checking if any data can be read from the Queue
 *
 * @param none
 *
 * @return true if Queue is empty
 * @return false if there is any data stored in Queue 
 */
bool CircularQueue::isEmpty()
{
	if (this->availableItems)
	{
		return false;
	}
	return true;
}

/**
 * @brief Method for checking if data can be stored in the Queue
 *
 * @param none
 *
 * @return true if Queue is fully
 * @return false if there one or more data available to be stored in queue
 */
bool CircularQueue::isFull()
{
	if (this->availableItems == BUFFER_SIZE)
	{
		return true;
	}
	return false;
}

/**
 * @brief Method for storing data in the Queue
 *
 * @param byte to be written on the Queue
 *
 * @return QUEUE_OK if write to the Queue was succesful
 * @return QUEUE_NOK if write to the Queue was unsuccesful
 */
int8_t CircularQueue::enqueue(uint8_t byte)
{
	if (this->isFull())
	{
		return QUEUE_NOK;
	}
	
	this->tail = (this->tail + 1) & BUFFER_MASK;
	this->buffer[this->tail] = byte;
	this->availableItems++;
	
	return QUEUE_OK;
}

/**
 * @brief Method for reading data from the Queue
 *
 * @param byte for storing read data from the queue
 *
 * @return QUEUE_OK if read from the Queue was succesful
 * @return QUEUE_NOK if read from the Queue was unsuccesful
 */
int8_t CircularQueue::dequeue(uint8_t* byte)
{
	if (this->isEmpty())
	{
		return QUEUE_NOK;
	}
	
	this->head = (this->head + 1) & BUFFER_MASK;
	*byte = this->buffer[this->head];
	this->availableItems--;
	
	return QUEUE_OK;
}

