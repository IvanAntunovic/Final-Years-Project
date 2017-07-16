using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace BluetoothApplication
{
    class MessageDeserialization
    {
        private List<byte> buffer;
        private const int STX = 0x02;
        private const int ETX = 0x03;

        public MessageDeserialization()
        {
            this.buffer = new List<byte>();
        }

        public void addBytes(byte[] buffer)
        {
            // Add all bytes to internal buffer
            for (int index = 0; index < buffer.Length; ++index)
            {
                this.buffer.Add(buffer[index]);
            }
        }

        public bool isDeserializated()
        {
            const int DATA_LENGTH_FIELD_INDEX = 2;
            int startOfTextIndex = this.buffer.FindIndex(nByte => nByte == STX);
            int dataLength;

            if (this.buffer.Contains(STX) && this.buffer.Contains(ETX))
            {
                int endOfTextIndex = this.buffer.FindIndex(nByte => nByte == ETX);
                if (endOfTextIndex - startOfTextIndex < 0)
                {
                    this.buffer.RemoveAt(endOfTextIndex);
                    return false;
                }
                if ( this.buffer.Count <= startOfTextIndex + DATA_LENGTH_FIELD_INDEX )
                {
                    return false;
                }
                dataLength = this.buffer[startOfTextIndex + DATA_LENGTH_FIELD_INDEX];
                return this.buffer[startOfTextIndex + DATA_LENGTH_FIELD_INDEX + dataLength + 1] == ETX;
            }
            return false;
        }

        public List<byte> getDeserializedBuffer()
        {
            List<byte> bufferCopy = new List<byte>(this.buffer);
            this.buffer.Clear();
            return bufferCopy;
        }
    }
}
