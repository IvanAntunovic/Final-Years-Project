using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using InTheHand;
using InTheHand.Net.Bluetooth;
using InTheHand.Net.Ports;
using InTheHand.Net.Sockets;
using System.IO;
using System.Net.Sockets;
using System.IO.Ports;
using System.Diagnostics;

namespace BluetoothApplication
{
    class BluetoothCommPort
    {
        private ApplicationForm btForm;
        private TemperatureGraphForm tempGraph;

        public BluetoothClient BluetoothClient { set; get;}
        public BluetoothListener BluetoothListener { set; get; }
        public BluetoothTransmitter BluetoothTransmitter { set; get; }
        public BluetoothReceiver BluetoothReceiver { set; get; }
        public BluetoothDeviceRepository BluetoothDeviceRepository { private set; get; }
        public BluetoothDeviceScanner BluetoothDeviceScanner { private set; get; }
        public BluetoothDeviceInfo DeviceInfo { set; get; }

        private MessageDeserialization messageDeserialization;
        private MessageDecoder         messageDecoder;

        public string Pin { private set; get; }
        public byte[] TransmitBuffer { set; get; }

        readonly Guid mUUID = new Guid("00001101-0000-1000-8000-00805F9B34FB");

        public BluetoothCommPort(ApplicationForm bluetoothForm, TemperatureGraphForm tempGraph)
        {
            this.btForm = bluetoothForm;
            this.tempGraph = tempGraph;

            this.BluetoothClient = null;
            this.BluetoothListener = null;
            this.BluetoothTransmitter = null;
            this.BluetoothReceiver = null;
            this.BluetoothDeviceRepository  = new BluetoothDeviceRepository();
            this.BluetoothDeviceScanner     = new BluetoothDeviceScanner(bluetoothForm);

            this.messageDeserialization = new MessageDeserialization();
            this.messageDecoder         = new MessageDecoder();
            this.TransmitBuffer = new byte[1024];
            this.Pin = "1234";

        }

        public void listen()
        {
            this.BluetoothListener = new BluetoothListener(mUUID);
            this.BluetoothListener.Start();
            this.BluetoothClient = this.BluetoothListener.AcceptBluetoothClient();
        }

        public void setDeviceName(string remoteMachineName)
        {
            this.DeviceInfo.DeviceName = remoteMachineName;
        }

        public void scanDevices()
        {

        }

        public void open(IAsyncResult result)
        {
            try
            {
                this.BluetoothClient = result.AsyncState as BluetoothClient;
                this.BluetoothClient.EndConnect(result);
                this.btForm.updateBluetoothUI("Connected succesfully to bluetooth device");

                this.BluetoothDeviceRepository.DiscoveredBluetoothDevices = this.BluetoothDeviceRepository.DiscoveredBluetoothDevices.Where
                                                                                              (device => device.DeviceName != this.BluetoothDeviceRepository.SelectedBluetoothDevice.DeviceName).ToList();
                this.btForm.updateAvailableDeviceList(this.BluetoothDeviceRepository.DiscoveredBluetoothDevices);
                this.btForm.updateConnectedDeviceList(this.BluetoothDeviceRepository.SelectedBluetoothDevice);

                this.BluetoothClient.GetStream().ReadTimeout = 1000;
                this.BluetoothReceiver      = new BluetoothReceiver(this.BluetoothClient.GetStream());
                this.BluetoothTransmitter   = new BluetoothTransmitter(this.BluetoothClient.GetStream());

                //this.startTimer();

                this.startMultiTaskingInputOutput();
            }
            catch (Exception ex)
            {
                this.BluetoothClient.GetStream().Close();
                this.btForm.updateBluetoothUI(ex.ToString());
                this.BluetoothClient = null;
            }
        }

        public void close()
        {
            try
            {
                if (this.BluetoothClient != null)
                {
                    this.BluetoothClient.Close();
                    this.BluetoothClient.GetStream().Close();
                    
                }
            }
            catch (InvalidOperationException ex)
            {
                this.btForm.updateBluetoothUI(ex.ToString());
            }
        }

        private void startMultiTaskingInputOutput()
        {
            Thread bluetoothClientTxThread;
            Thread bluetoothClientRxThread;
            //Thread deviceConnectedCheckUpThread;

            bluetoothClientTxThread = new Thread(new ThreadStart(bluetoothClientTransmitterThreadFunction));
            bluetoothClientRxThread = new Thread(new ThreadStart(bluetoothClientReceiverThreadFunction));
            //deviceConnectedCheckUpThread = new Thread(new ThreadStart(DeviceConnectedCheckUpThread));

            bluetoothClientTxThread.Start();
            bluetoothClientRxThread.Start();
            //deviceConnectedCheckUpThread.Start();
        }

        private void bluetoothClientTransmitterThreadFunction()
        {
            while (true)
            {
                if (this.TransmitBuffer != null)
                {
                    this.BluetoothTransmitter.writeBytes(this.TransmitBuffer, 0, this.TransmitBuffer.Length);
                    this.btForm.updateBluetoothUI(string.Format("Transmitted byte: " + Encoding.ASCII.GetString(this.TransmitBuffer)) + "\n\r");
                    this.TransmitBuffer = null;
                }
            }
        }

        private void bluetoothClientReceiverThreadFunction()
        {
            byte[] btReceiveByte = new byte[1];
            List<Message> messages = new List<Message>();
            Message message;
            byte[] btreceiveBuffer = new byte[1024];
            const int MESSAGE_TYPE_TEMPERATURE = 0x04;

            while (true)
            {
                if (this.BluetoothClient.GetStream().DataAvailable)
                {
                    this.BluetoothReceiver.readBytes(btReceiveByte, 0, 1);
                    this.messageDeserialization.addBytes(btReceiveByte);
                    this.btForm.updateBluetoothUI(string.Format("Received byte: {0}", Encoding.ASCII.GetString(btReceiveByte)) + "\n\r");
                   // btreceiveBuffer = getSerializedBytes(btReceiveByte[0]);
                   // if ( btreceiveBuffer != null )
                    //{

                   // }
                }

                if (this.messageDeserialization.isDeserializated())
                {
                    messages.Add(this.messageDecoder.decode(messageDeserialization.getDeserializedBuffer()));
                    message = this.messageDecoder.decode(messageDeserialization.getDeserializedBuffer());
                    //this.tempGraph.Temperature = this.temperatureMessageHandler.getTemperature(message);
                    
       
                    if (message.Type == MESSAGE_TYPE_TEMPERATURE)
                    {
                        double temperature = Convert.ToDouble(Encoding.ASCII.GetString(message.Data.ToArray()));
                        this.btForm.updateBluetoothUI( string.Format("Tempearture: {0}\n\r", temperature) );
                        this.tempGraph.Temperature = temperature;
                    }
                    
                }

            }
        }

        private static List<byte> bytes = new List<byte>();
        const int STX = 0x02;
        const int ETX = 0x03;

        private static byte[] getSerializedBytes(byte nByte)
        {
            bytes.Add(nByte);
            if ( bytes.Count < 0 )
            {
                return null;
            }

            if ( bytes.Contains(STX) )
            {
                if ( bytes.Contains(ETX) )
                {
                    int endIndex = bytes.Count;
                    byte[] byteArray;

                    bytes.RemoveAt( endIndex - 1 );
                    bytes.RemoveAt( 0 );
                    byteArray = bytes.ToArray();
                    bytes.Clear();
                    return byteArray;
                }
            }
            else
            {
                bytes.Clear();
                return null;
            }
            return null;
        }

        private void BluetoothTimerElapsed(object sender, System.Timers.ElapsedEventArgs e)
        {
            const int ACK = 0x06;

            this.BluetoothTransmitter.writeString(ACK.ToString());
        }

  
        private void DeviceConnectedCheckUpThread()
        {
            //if (!this.BluetoothDeviceRepository.SelectedBluetoothDevice.DeviceInfo.Connected)
            //{
            //    this.btForm.updateBluetoothUI("Device has disconnected!");
            //}
            Application.Exit();
        }

    }
}
