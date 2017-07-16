using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BluetoothApplication
{
    class BluetoothDeviceRepository
    {
        public BluetoothDeviceRepository()
        {
            this.SelectedBluetoothDevice = null;
            this.ConnectedBluetoothDevice = null;
            this.DiscoveredBluetoothDevices = new List<BluetoothDevice>();
            this.ConnectedBluetoothDevices = new List<BluetoothDevice>();
        }

        public List<BluetoothDevice> DiscoveredBluetoothDevices { set; get; }
        public List<BluetoothDevice> ConnectedBluetoothDevices { set; get; }
        public BluetoothDevice SelectedBluetoothDevice { set; get; }
        public BluetoothDevice ConnectedBluetoothDevice { set; get; }

        public ApplicationForm BluetoothForm
        {
            get
            {
                throw new System.NotImplementedException();
            }

            set
            {
            }
        }

        internal BluetoothCommPort BluetoothCommPort
        {
            get
            {
                throw new System.NotImplementedException();
            }

            set
            {
            }
        }

        internal BluetoothCommPort BluetoothCommPort1
        {
            get
            {
                throw new System.NotImplementedException();
            }

            set
            {
            }
        }
    }
}
