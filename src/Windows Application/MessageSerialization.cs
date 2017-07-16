using System.Collections.Generic;
using System.Text;

namespace BluetoothApplication
{
    class MessageSerialization
    {
        private const int STX = 0x02;
        private const int ETX = 0x03;
        private const int MESSAGE_DATA_TYPE_INDEX = 1;
        private const int MESSAGE_DATA_LENGTH_INDEX = 2;
        private const int MESSAGE_DATA_START_INDEX = 3;

        private const int MESSAGE_SERIALIZATION_OK = 0;
        private const int MESSAGE_SERIALIZATION_NOK = -1;

        public byte[] serialize(Message serialMessage)
        {
            int serializedBufferLen;
            byte[] serializedBuffer;
            List<byte> tempDataBuffer;

            // We add five more bytes - STX, ETX, dataType, dataLength
            serializedBufferLen = serialMessage.DataLength + 4;
            serializedBuffer = new byte[serializedBufferLen];

            serializedBuffer[0] = STX;
            serializedBuffer[serializedBufferLen - 1] = ETX;
            serializedBuffer[MESSAGE_DATA_TYPE_INDEX] = serialMessage.Type;
            serializedBuffer[MESSAGE_DATA_LENGTH_INDEX] = serialMessage.DataLength;
            tempDataBuffer = serialMessage.Data;
            for (int i = MESSAGE_DATA_START_INDEX; i < serialMessage.DataLength + MESSAGE_DATA_START_INDEX; ++i)
            {
                serializedBuffer[i] = tempDataBuffer[i - MESSAGE_DATA_START_INDEX];
            }
            
            return serializedBuffer;
        }
    }
}