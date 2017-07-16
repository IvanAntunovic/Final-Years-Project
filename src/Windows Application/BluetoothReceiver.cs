using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace BluetoothApplication
{
    class BluetoothReceiver 
    {
        NetworkStream bluetoothStream;

        public BluetoothReceiver(NetworkStream bluetoothStream) 
        {
            this.bluetoothStream = bluetoothStream;
            DataAvailable        = this.bluetoothStream.DataAvailable;
            CanRead              = this.bluetoothStream.CanRead;
        }

        public bool DataAvailable { get; }
        public bool CanRead { get; }

        public void readBytes(byte[] buffer, int offset, int size)
        {
            if (this.bluetoothStream.CanRead)
            {
                this.bluetoothStream.Read(buffer, offset, size);
            }
        }

        public byte readByte()
        {
            return (byte)this.bluetoothStream.ReadByte();
        }

        public string readString()
        {
            const int BUFFER_MAX_SIZE = 1024;
            string bufferString;
            List<byte> buffer = new List<byte>();

            do
            {
                buffer.Add(this.readByte());
            }
            while (this.DataAvailable && buffer.Count < BUFFER_MAX_SIZE);

            try
            {
                bufferString = Encoding.ASCII.GetString(buffer.ToArray());
                return bufferString;
            }
            catch(ArgumentException ex)
            {
                Console.WriteLine(ex);
                return null;
            }
        }

        public void close()
        {
            this.bluetoothStream.Close();
            this.bluetoothStream = null;
        }
    }
}
