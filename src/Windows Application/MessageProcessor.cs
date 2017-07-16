using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BluetoothApplication
{
    class MessageProcessor
    {
        MessageDecoder messageDecoder;
        MessageDeserialization messageDeserialization;
        MessageEncoder messageEncoder;
        MessageSerialization messageSerialization;
        Message receivedMessage;

        private const int STX = 0x02;
        private const int ETX = 0x03;

        public bool isReceivedMessageProcessed()
        {
            return true;
        }

        public bool isTransmitMessageProcessed()
        {
            return true;
        }

        public Message getProcessedMessage()
        {
            return receivedMessage;
        }

        private void handleReceivedBytes()
        {
            return;
        }

        public int processTransmitData(byte[] dataBuffer, byte type, byte length)
        {
            return 0;
        }

        
    }
}
