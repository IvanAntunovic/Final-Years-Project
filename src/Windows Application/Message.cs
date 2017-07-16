using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BluetoothApplication
{
    class Message
    {
        public byte Type { set; get; }
        public byte DataLength { set; get; }
        public List<byte> Data { set; get; }

        public Message()
        {
            this.Type = 0;
            this.DataLength = 0;
            this.Data = new List<byte>();
        }

        public Message(byte dataType, byte dataLength, List<byte> dataBuffer)
        {
            this.Type = dataType;
            this.DataLength = dataLength;
            this.Data = new List<byte>(dataBuffer);
        }

        public void addByte(byte nByte)
        {
            this.Data.Add(nByte);
        }

        public override string ToString()
        {
            string returnString;

            returnString = string.Format("Type: {0}\n\rData Length: {1}\n\rData: ");
            returnString += Encoding.ASCII.GetBytes(Data.ToArray<byte>().ToString()).ToString();
            return returnString;
        }

    }
}
