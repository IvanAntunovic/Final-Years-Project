/*
 * RC_CAR_Working.cpp
 *
 * Created: 5/28/2017 10:52:51 AM
 * Author : fairenough
 */ 

#include <avr/io.h>
#include "RCCar.h"
#include "SerialPort.h"
#include "Timer.h"
#include "I2CPort.h"
#include "Tmp102.h"
#include "MessageProcessor.h"
#include "MessageDeserializaton.h"
#include "MessageDecoder.h"
#include "Message.h"

uint8_t receivedCommand;
uint8_t transmittedCommand;

#define COMMAND_FORWARD 51
#define COMMAND_BACKWARD 52
#define COMMAND_RIGHT 49
#define COMMAND_LEFT 50
#define COMMAND_STOP 53
#define TMP_102_ADDRESS  0x48
#define ACK_SIGNAL 0x06

RCCar car(210);
SerialPort serialPortBt;
SerialPort serialPortPc;
I2CPort i2cPort;
Tmp102 tmp102(&i2cPort, TMP_102_ADDRESS);
MessageProcessor messageProcessor(&serialPortBt);
MessageDeserialization messageDeserialization;
MessageDecoder messageDecoder;

float temperature;
int8_t retVal;
uint8_t dataBuffer[5];

void floatToArray(float floatNo, uint8_t* dataBuffer, uint8_t bufferLen);

int main(void)
{	
	serialPortBt.open(9600, 3);
	serialPortPc.open(9600, 0);
	i2cPort.open(100000);
	i2cPort.selectSlaveDevice(TMP_102_ADDRESS);

    while (true)
    {
		//retVal = tmp102.getTemperature(&temperature);
		//if ( retVal == TMP_102_OK )
		//{
			//floatToArray(temperature, dataBuffer, 5);
			//messageProcessor.processTransmitData(MESSAGE_DATA_TYPE_TEMPERATURE, 5, dataBuffer);
			//pcMessageProcessor.processTransmitData(MESSAGE_DATA_TYPE_TEMPERATURE, 5, dataBuffer);
			//serialPortPc.writeString("\n\r");
		//}
		Message* message = messageProcessor.processReceivedData();
		if ( message != NULL )
		{
			if ( message->getDataType() == MESSAGE_DATA_TYPE_KEEP_ALIVE )
			{
				serialPortPc.writeString("I AM ALIVE\n\r");
			}
		}
		else
		{
			
		}
		delete message;
		
		//if ( serialPortBt.available() )
	
			//
			//switch (receivedCommand)
			//{
				//case COMMAND_FORWARD:
					//car.run(CAR_FORWARD);
					//break;
				//case COMMAND_BACKWARD:
					//car.run(CAR_BACKWARD);
					//break;
				//case COMMAND_RIGHT:
					//car.run(CAR_RIGHT);
					//break;
				//case COMMAND_LEFT:
					//car.run(CAR_LEFT);
					//break;
				//case COMMAND_STOP:
					//car.run(CAR_STOP);
					//break;
				//default:
					//break;
			//}	
		}
}

void floatToArray(float floatNo, uint8_t* dataBuffer, uint8_t bufferLen)
{
	int8_t fracPart;
	
	if (bufferLen < 5)
	{
		return;
	}
	
	dataBuffer[0] = (int)temperature / 10 + '0';
	dataBuffer[1] = (int)temperature % 10 + '0';
	dataBuffer[2] = '.';
	
	fracPart = ( floatNo - (int8_t) floatNo ) * 100;
	
	dataBuffer[3] = (int)fracPart / 10 + '0';
	dataBuffer[4] = (int)fracPart % 10 + '0';

}