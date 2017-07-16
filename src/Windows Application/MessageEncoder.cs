using System.Collections.Generic;

namespace BluetoothApplication
{
    internal class MessageEncoder
    {
        private const int STX = 0x02;
        private const int ETX = 0x03;

		public Message encode(byte dataType, byte dataLength, List<byte> dataBuffer)
        {
            return new Message(dataType, dataLength, dataBuffer);
        }

    }
}