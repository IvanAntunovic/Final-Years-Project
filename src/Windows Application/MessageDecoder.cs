using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/** _________________________________________________
 * |     |              |        |      |      |     |
 * | STX | MESSAGE TYPE | LENGTH | DATA | '\0' | ETX |
 * |_____|______________|________|______|______|_____|
 */
namespace BluetoothApplication
{
    class MessageDecoder
    {
        private const int STX = 0x02;
        private const int ETX = 0x03;
        private const int MESSAGE_TYPE_TEMPERATURE = 0x04;
        private const int MESSAGE_TYPE_COMMAND     = 0x11;


        public Message decode(List<byte> deserializedBuffer)
        {
            Message message = new Message();
            int startOfTextIndex;
            int endOfTextIndex;

            // Find index of STX in deserializedBuffer
            startOfTextIndex = deserializedBuffer.FindIndex(deserializedByte => deserializedByte == STX);
            // Find index of ETX in deserializedBuffer
            endOfTextIndex = deserializedBuffer.FindIndex(deserializedByte => deserializedByte == ETX);

            message.Type = deserializedBuffer[startOfTextIndex + 1];
            message.DataLength = deserializedBuffer[startOfTextIndex + 2];
            message.Data = deserializedBuffer.GetRange(startOfTextIndex + 3, message.DataLength);
            
            return message;
        }
    }
}
