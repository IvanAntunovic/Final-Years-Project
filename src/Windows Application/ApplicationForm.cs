using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
    public partial class ApplicationForm : Form
    {
        BluetoothCommPort bluetoothCommPort;
        SerialPort serialPort;

        TemperatureGraphForm tempGraph;
        MessageDeserialization bluetoothMessageDeserialization;

        MessageSerialization messageSerialization = new MessageSerialization();
        MessageEncoder messageEncoder = new MessageEncoder();

        private System.Timers.Timer bluetoothTimer;

        public static readonly List<string> SupportedBaudRates = new List<string>
        {
            "300",
            "600",
            "1200",
            "2400",
            "4800",
            "9600",
            "19200",
            "38400",
            "57600",
            "115200",
            "230400",
            "460800",
            "921600"
        };

        public ApplicationForm()
        {
            this.tempGraph = new TemperatureGraphForm();
            this.bluetoothCommPort = new BluetoothCommPort(this, tempGraph);
            this.serialPort = new SerialPort();
            this.bluetoothMessageDeserialization = new MessageDeserialization();
            InitializeComponent();


            this.bluetoothTimer = new System.Timers.Timer();
            this.bluetoothTimer.Interval = 1000;
            this.bluetoothTimer.Elapsed += BluetoothKeepAlive;
        }

        private void bluetoothDeviceScanButton_Click(object sender, EventArgs e)
        {
            if (clientRadioButton.Checked)
            {
                this.startDeviceScan();
                return;
            }

            if (serverRadioButton.Checked)
            {
                //if (bluetoothListener == null)
                if (this.bluetoothCommPort.BluetoothListener == null)
                {
                    this.connectAsServer();
                }
                else
                {
                    this.updateBluetoothUI("Server already started!");
                }
                return;
            }

            this.updateBluetoothUI("Select Bluetooth Connection Mode in order to start Device Scan!");
        }

        //private void startDeviceScan()
        //{
        //    availableBluetoothDevicesListBox.DataSource = null;
        //    availableBluetoothDevicesListBox.Items.Clear();

        //    this.bluetoothCommPort.BluetoothDeviceScanner.start();
        //    this.bluetoothCommPort.BluetoothDeviceRepository.DiscoveredBluetoothDevices = this.bluetoothCommPort.BluetoothDeviceScanner.DiscoveredBluetoothDevices;
        //    updateBluetoothUI(this.bluetoothCommPort.BluetoothDeviceRepository.DiscoveredBluetoothDevices.Count.ToString() + " devices discovered");
        //    updateAvailableDeviceList(this.bluetoothCommPort.BluetoothDeviceRepository.DiscoveredBluetoothDevices);
        //}

        private void startDeviceScan()
        {
            Thread bluetoothScanThread;

            try
            {
                availableBluetoothDevicesListBox.DataSource = null;
                availableBluetoothDevicesListBox.Items.Clear();
                this.bluetoothCommPort.BluetoothDeviceRepository.DiscoveredBluetoothDevices.Clear();

                this.updateBluetoothUI("Starting Bluetooth Device Scan...");
                bluetoothScanThread = new Thread(new ThreadStart(this.scan));
                bluetoothScanThread.Start();
            }
            catch (Exception ex)
            {
                this.updateBluetoothUI("Error while scanning for devices " + ex);
            }
        }

        private void scan()
        {
            BluetoothDeviceInfo[] devices;
            BluetoothClient client;

            try
            {
                client = new BluetoothClient();
                devices = client.DiscoverDevicesInRange();
                foreach (BluetoothDeviceInfo device in devices)
                {
                    this.bluetoothCommPort.BluetoothDeviceRepository.DiscoveredBluetoothDevices.Add(new BluetoothDevice(device));
                }

                updateBluetoothUI("Scan has completed");
                updateBluetoothUI(this.bluetoothCommPort.BluetoothDeviceRepository.DiscoveredBluetoothDevices.Count.ToString() + " devices discovered");
                updateAvailableDeviceList(this.bluetoothCommPort.BluetoothDeviceRepository.DiscoveredBluetoothDevices);
            }
            catch (PlatformNotSupportedException ex)
            {
                this.updateBluetoothUI("No supported bluetooth protocol stack found! Please enable bluetooth adapter at your computer.");
            }
        }


        private void connectAsServer()
        {
            Thread bluetoothServerThread;

            bluetoothServerThread = new Thread(new ThreadStart(ServerConnectThread));
            bluetoothServerThread.Start();
        }

        private void ServerConnectThread()
        {
            BluetoothDeviceInfo deviceInfo;

            try
            {
                updateBluetoothUI("Server started, waiting for clients");
                this.bluetoothCommPort.listen();

                deviceInfo = new BluetoothDeviceInfo(this.bluetoothCommPort.BluetoothClient.RemoteEndPoint.Address);
                this.bluetoothCommPort.setDeviceName(this.bluetoothCommPort.BluetoothClient.RemoteMachineName);

                this.updateBluetoothUI(string.Format("Client {0} has connected", this.bluetoothCommPort.DeviceInfo.DeviceName));
                this.updateConnectedDeviceList(new BluetoothDevice(this.bluetoothCommPort.DeviceInfo));

                this.bluetoothCommPort.BluetoothReceiver = new BluetoothReceiver(this.bluetoothCommPort.BluetoothClient.GetStream());
                this.bluetoothCommPort.BluetoothTransmitter = new BluetoothTransmitter(this.bluetoothCommPort.BluetoothClient.GetStream());
            }
            catch (Exception ex)
            {
                this.updateBluetoothUI(ex.ToString());
            }
            //while (true)
            //{
            //    try
            //    {
            //        //Handle server connection
            //        if (bluetoothReceiver.DataAvailable)
            //        {
            //            bluetoothReceiver.readBytes(receiveBuffer, 0, receiveBuffer.Length);
            //            updateBluetoothUI("Received: " + Encoding.ASCII.GetString(receiveBuffer));
            //        }

            //        if (this.transmitBuffer != null)
            //        {
            //            bluetoothTransmitter.writeBytes(this.transmitBuffer, 0, this.transmitBuffer.Length);
            //            this.transmitBuffer = null;
            //        }

            //    }
            //    catch (IOException exception)
            //    {
            //        this.bluetoothListener = null;
            //        this.updateBluetoothUI(string.Format("Client {0} has disconnected!", deviceInfo.DeviceName));

            //        //Remove disconnected device from GUI
            //        this.updateConnectedDeviceList(null);
            //        break;
            //    }
            //}

        }

        //public void ServerConnectThread()
        //{
        //    BluetoothClient bluetoothClient;
        //    string receivedMessage; 

        //    serverStarted = true;

        //    updateBluetoothUI("Server started, waiting for clients");
        //    this.bluetoothListener = new BluetoothListener(mUUID);
        //    this.bluetoothListener.Start();
        //    bluetoothClient = this.bluetoothListener.AcceptBluetoothClient();

        //    updateBluetoothUI("Client has connected");
        //    try
        //    {
        //        this.bluetoothReceiver = new BluetoothReceiver(this.bluetoothClient.GetStream());
        //        this.bluetoothTransmitter = new BluetoothTransmitter(this.bluetoothClient.GetStream());
        //    }
        //    catch (Exception ex)
        //    {
        //        throw ex;
        //    }

        //    while (true)
        //    {
        //        try
        //        {
        //            //handle server connection
        //            if (bluetoothReceiver.DataAvailable)
        //            {
        //                receivedMessage = bluetoothReceiver.readString();
        //                updateBluetoothUI("Received: " + receivedMessage);
        //                this.bluetoothTransmitter.writeString(receivedMessage);
        //            }
        //        }
        //        catch (IOException exception)
        //        {
        //            updateBluetoothUI("Client has disconnected. " + exception);
        //            break;
        //        }
        //        finally
        //        {
        //            this.bluetoothListener.Stop();
        //            this.bluetoothClient.GetStream().Close();
        //            this.bluetoothReceiver.close();
        //            this.bluetoothTransmitter.close();

        //            this.bluetoothClient = null;
        //            this.bluetoothListener = null;

        //            serverStarted = false;
        //        }
        //    }
        //}

        private void ClientConnectThread()
        {
            BluetoothClient client = new BluetoothClient();
            updateBluetoothUI("attempting to connect to the device");
            client.BeginConnect(this.bluetoothCommPort.BluetoothDeviceRepository.SelectedBluetoothDevice.DeviceInfo.DeviceAddress,
                                BluetoothService.SerialPort,
                                new AsyncCallback(BluetoothClientConnectCallback),
                                client);
        }

        void BluetoothClientConnectCallback(IAsyncResult result)
        {
            this.bluetoothCommPort.open(result);
            this.bluetoothTimer.Enabled = true;
        }

        public eDevicePair pairDevice()
        {
            if (this.bluetoothCommPort.BluetoothDeviceRepository.SelectedBluetoothDevice == null)
            {
                return eDevicePair.DEVICE_INDEX_OUT_OF_RANGE;
            }

            if (!this.bluetoothCommPort.BluetoothDeviceRepository.SelectedBluetoothDevice.IsAuthenticated)
            {
                return eDevicePair.DEVICE_ALREADY_PAIRED;
            }

            if (!BluetoothSecurity.PairRequest(this.bluetoothCommPort.BluetoothDeviceRepository.SelectedBluetoothDevice.DeviceInfo.DeviceAddress, this.bluetoothCommPort.Pin))
            {
                return eDevicePair.PAIR_NOK;
            }

            return eDevicePair.PAIR_OK;
        }

        private void tbText_KeyPress(object sender, System.Windows.Forms.KeyPressEventArgs e)
        {
            if (e.KeyChar == (char)Keys.Enter)
            {
                this.bluetoothCommPort.TransmitBuffer = Encoding.ASCII.GetBytes(tbText.Text);
                tbText.Clear();
            }
        }

        private void sendButton_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrEmpty(tbText.Text))
            {
                this.bluetoothCommPort.TransmitBuffer = Encoding.ASCII.GetBytes(tbText.Text);
            }

            tbText.Clear();
        }

        private void availableDevicesListBox_DoubleClick(object sender, EventArgs e)
        {
            BluetoothDeviceInfo selectedDevice;

            try
            {
                // Need to implement error hadnling for clicking on the already connected device
                selectedDevice = this.bluetoothCommPort.BluetoothDeviceRepository.DiscoveredBluetoothDevices[availableBluetoothDevicesListBox.SelectedIndex].DeviceInfo;
                this.bluetoothCommPort.BluetoothDeviceRepository.SelectedBluetoothDevice = new BluetoothDevice(selectedDevice);
                updateBluetoothUI(this.bluetoothCommPort.BluetoothDeviceRepository.SelectedBluetoothDevice.DeviceName + " was selected, attempting to connect");
            }
            catch (NullReferenceException ex)
            {
                updateBluetoothUI("Device selection error" + ex);
            }
            catch (ArgumentOutOfRangeException ex)
            {
                updateBluetoothUI("Device selection error" + ex);
            }

            eDevicePair retValueDevicePair;

            retValueDevicePair = pairDevice();
            if (retValueDevicePair == eDevicePair.PAIR_OK)
            {
                this.updateBluetoothUI("Device " + this.bluetoothCommPort.BluetoothDeviceRepository.SelectedBluetoothDevice.DeviceName + " paired succesfully.");
                this.updateBluetoothUI("Starting bluetooth connect thread...");
                Thread bluetoothClientThread = new Thread(new ThreadStart(ClientConnectThread));
                bluetoothClientThread.Start();
            }
            else if (retValueDevicePair == eDevicePair.DEVICE_ALREADY_PAIRED)
            {
                this.updateBluetoothUI("Device already paired!");
            }
            else if (retValueDevicePair == eDevicePair.DEVICE_INDEX_OUT_OF_RANGE)
            {
                this.updateBluetoothUI("Non existing device selected!");
            }
            else
            {
                this.updateBluetoothUI("Pair failed!");
            }
        }

        public void updateBluetoothUI(string message)
        {
            Func<int> del = delegate ()
            {
                this.bluetoothCommMonitorTextBox.AppendText(string.Format("{0}\n", message));
                return 0;
            };
            try
            {
                Invoke(del);
            }
            catch (Exception ex)
            {

                throw (ex);
            }
        }

        public void updateSerialUI(string message)
        {
            Func<int> del = delegate ()
            {
                this.serialCommMonitorTextBox.AppendText(string.Format("{0}\n", message));
                return 0;
            };
            try
            {
                Invoke(del);
            }
            catch (Exception ex)
            {
                throw (ex);
            }
        }

        public void updateAvailableDeviceList(List<BluetoothDevice> discoveredBluetoothDevices)
        {
            Func<int> del = delegate ()
            {
                List<string> deviceNames = discoveredBluetoothDevices.Select(o => o.DeviceName).ToList();
                this.availableBluetoothDevicesListBox.DataSource = deviceNames;
                return 0;
            };
            Invoke(del);
        }

        public void updateConnectedDeviceList(BluetoothDevice connectedBluetoothDevice)
        {
            Func<int> del = delegate ()
            {
                this.connectedBluetoothDevicesListBox.Items.Clear();
                this.connectedBluetoothDevicesListBox.Items.Add(connectedBluetoothDevice.DeviceName);
                return 0;
            };
            Invoke(del);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.tempGraph.Show();
        }

        private void openSerialPortButton_Click(object sender, EventArgs e)
        {
            Thread serialPortThread;

            try
            {
                if (this.serialPort != null)
                {
                    if (!this.serialPort.IsOpen)
                    {
                        if (this.serialBaudRateComboBox.SelectedIndex == -1)
                        {
                            this.updateSerialUI("Select Baud Rate first!");
                            return;
                        }

                        if (this.serialComPortComboBox.SelectedIndex == -1)
                        {
                            this.updateSerialUI("Select Communication Port first!");
                            return;
                        }

                        this.serialPort.BaudRate = Convert.ToInt32(this.serialBaudRateComboBox.SelectedItem);
                        this.serialPort.PortName = this.serialComPortComboBox.SelectedItem.ToString();
                        this.serialPort.Open();
                        this.updateSerialUI("Serial Port " + this.serialComPortComboBox.SelectedItem.ToString() +
                                            " with baud rate " + Convert.ToInt32(this.serialBaudRateComboBox.SelectedItem) +
                                            " opened successfully."
                                            );

                        serialPortThread = new Thread(handleSerialCommThread);
                        serialPortThread.Start();
                    }
                    else
                    {
                        this.updateSerialUI("Serial Port already opened!");
                    }
                }
            }
            catch (IOException ex)
            {
                this.updateSerialUI("Error while opening Serial port");
                this.updateSerialUI(ex.ToString());
            }

        }

        private void serialComPortComboBox_DropDown(object sender, EventArgs e)
        {
            if (this.serialPort != null)
            {
                string[] portNames = SerialPort.GetPortNames();
                this.serialComPortComboBox.DataSource = null;
                this.serialComPortComboBox.DataSource = portNames;
            }
        }

        private void serialBaudRateComboBox_DropDown(object sender, EventArgs e)
        {
            if (this.serialPort != null)
            {
                string[] portNames = SerialPort.GetPortNames();
                this.serialBaudRateComboBox.DataSource = null;
                this.serialBaudRateComboBox.DataSource = SupportedBaudRates.ToArray<string>();
            }
        }

        private void closeSerialPortButton_Click(object sender, EventArgs e)
        {
            if (this.serialPort != null && this.serialPort.IsOpen)
            {
                this.serialPort.Close();
                this.updateSerialUI("Serial Port closed.");
            }
        }

        const int eRight = 1;
        const int eLeft = 2;
        const int eUp = 3;
        const int eDown = 4;
        const int eIdle = 5;

        private void handleSerialCommThread()
        {
            byte[] bluetoothTransmitByte = new byte[1];
            byte[] serialReceiveByte = new byte[1];
            byte[] previousSerialReceiveByte = new byte[1];
            previousSerialReceiveByte[0] = 0;

            while (true)
            {

                this.serialPort.Read(serialReceiveByte, 0, 1);
                if (serialReceiveByte[0] != previousSerialReceiveByte[0])
                {
                    previousSerialReceiveByte[0] = serialReceiveByte[0];
                    //this.serialMessageCollector.addBytes(serialReceiveByte);
                    //this.updateSerialUI("Received from Serial Port: " + serialReceiveByte[0].ToString() + "\n\r");
                    if (serialReceiveByte[0] - '0' == eRight)
                    {
                        this.updateSerialUI("Right position!" + "\n\r");
                    }
                    if (serialReceiveByte[0] - '0' == eLeft)
                    {
                        this.updateSerialUI("Left position!" + "\n\r");
                    }
                    if (serialReceiveByte[0] - '0' == eUp)
                    {
                        this.updateSerialUI("Up position!" + "\n\r");
                    }
                    if (serialReceiveByte[0] - '0' == eDown)
                    {
                        this.updateSerialUI("Down position!" + "\n\r");
                    }
                    if (serialReceiveByte[0] - '0' == eIdle)
                    {
                        this.updateSerialUI("Idle position!" + "\n\r");
                    }
                    //if (this.bluetoothCommPort.BluetoothClient != null && this.bluetoothCommPort.BluetoothClient.Connected)
                    if (this.bluetoothCommPort.BluetoothClient != null)
                    {
                        this.updateBluetoothUI("Sending to vehicle: " + serialReceiveByte[0].ToString() + "\n\r");
                        this.bluetoothCommPort.BluetoothTransmitter.writeBytes(serialReceiveByte, 0, 1);
                    }

                }
                //if (this.serialMessageCollector.IsCollected)
                //{
                //    joystickMessage = this.serialJoystickMessageProcessor.processEndodedMessage( this.serialMessageCollector.getEncodedMessage() );
                //    if (this.bluetoothClient != null && this.bluetoothClient.Connected)
                //    {
                //        bluetoothTransmitByte = Encoding.ASCII.GetBytes(joystickMessage.getCurrentState().ToString());
                //        this.bluetoothTransmitter.writeBytes(bluetoothTransmitByte, 0, 1);
                //        bluetoothTransmitByte[0] = 0x00;
                //        Thread.Sleep(20);
                //    }
                //}
            }
        }

        private void ApplicationForm_Load(object sender, EventArgs e)
        {
            this.bluetoothCommPort.close();
        }

        const int MESSAGE_DATA_TYPE_KEEP_ALIVE = 0x10;
        const int MESSAGE_DATA_ACK = 0x06;
        private void BluetoothKeepAlive(Object source, System.Timers.ElapsedEventArgs e)
        {
            Message transmitMessage;
            byte[] serializedBytes;
            List<byte> dataBuffer = new List<byte>(1);
            dataBuffer.Add(MESSAGE_DATA_ACK);

            transmitMessage = this.messageEncoder.encode( MESSAGE_DATA_TYPE_KEEP_ALIVE, 1, dataBuffer );
            serializedBytes = this.messageSerialization.serialize( transmitMessage );
            this.bluetoothCommPort.BluetoothTransmitter.writeBytes( serializedBytes, 0, serializedBytes.Length );
        }
    }
}
