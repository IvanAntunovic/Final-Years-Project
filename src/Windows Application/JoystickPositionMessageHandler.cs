using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BluetoothApplication
{
    class JoystickPositionMessageHandler
    {
        private const int MESSAGE_TYPE_JOYSTICK_POSITION = 0x01;
        private const int MESSAGE_TYPE_INVALID = -1;

        public double getTemperature(Message joystickMessage)
        {
            byte[] joystickDataBuffer;

            if (joystickMessage.Type != MESSAGE_TYPE_JOYSTICK_POSITION)
            {
                return MESSAGE_TYPE_INVALID;
            }

            joystickDataBuffer = joystickMessage.Data.ToArray();
            return Convert.ToDouble(joystickDataBuffer);
        }
    }
}
