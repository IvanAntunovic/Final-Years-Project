using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BluetoothApplication
{
    public enum eDevicePair : int
    {
        DEVICE_INDEX_OUT_OF_RANGE = -3,
        DEVICE_ALREADY_PAIRED = -2,
        PAIR_NOK = -1,
        PAIR_OK = 0
    }
}
