using InTheHand.Net.Sockets;
using System;
using System.Collections.Generic;
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


namespace BluetoothApplication
{
    class BluetoothDeviceScanner
    {
        private ApplicationForm bluetoothForm;
        public List<BluetoothDevice> DiscoveredBluetoothDevices { set; get; }

        public BluetoothDeviceScanner(ApplicationForm bluetoothForm)
        {
            this.bluetoothForm = bluetoothForm;
            this.DiscoveredBluetoothDevices = new List<BluetoothDevice>();
        }

        public void start()
        {
            Thread bluetoothScanThread;

            try
            {
                this.DiscoveredBluetoothDevices.Clear();
                this.bluetoothForm.updateBluetoothUI("Starting Scan...");
                bluetoothScanThread = new Thread(new ThreadStart(this.scan));
                bluetoothScanThread.Start();
            }
            catch (Exception ex)
            {
                throw ex;
            }
        }

        private void scan()
        {
            BluetoothDeviceInfo[] devices;
            BluetoothClient client;

            client = new BluetoothClient();
            devices = client.DiscoverDevicesInRange();
            foreach (BluetoothDeviceInfo device in devices)
            {
                this.DiscoveredBluetoothDevices.Add(new BluetoothDevice(device));
            }
            this.bluetoothForm.updateBluetoothUI("Scan has completed");
            
        }

        public void stop()
        {
            this.DiscoveredBluetoothDevices.Clear();
        }

        public List<BluetoothDevice> getDiscoveredDevices()
        {
            return this.DiscoveredBluetoothDevices;
        }
    }
}
