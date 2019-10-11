using System;

namespace HeliosDac
{
    public class HeliosController
    {
        HeliosController()
        {

        }

        ~HeliosController()
        {

        }

        public int OpenDevices()
        {
            return 0;
        }

        public void CloseDevices()
        {
        }

        public void WriteFrame(uint deviceNumber, uint scanRate, uint flags, HeliosPoint[] points, uint numPoints)
        {

        }

        public bool GetStatus()
        {
            return true;
        }

        public void StopOutput(uint deviceNumber)
        {

        }

        public void SetShutter(uint deviceNumber, bool isShutterClosed)
        {

        }

        public int GetFirmwareVersion(uint deviceNumber)
        {
            return 0;
        }

        public string GetName(uint deviceNumber)
        {
            return "";
        }

        public void SetName(uint deviceNumber, string name)
        {

        }

        public HeliosDevice GetDevice(uint deviceNumber)
        {
            return null;
        }
    }

    public class HeliosDevice
    {

    }

    public struct HeliosPoint
    {
        ushort x;
        ushort y;
        byte red;
        byte green;
        byte blue;
        byte intensity;
    }
}
