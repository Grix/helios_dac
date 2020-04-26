/*
SDK for Helios Laser DAC C# class
By Gitle Mikkelsen
gitlem@gmail.com

Dependencies:
LibUsbDotNet

git repo: https://github.com/Grix/helios_dac.git
*/

using System;
using System.Collections.Generic;
using System.Threading;
using LibUsbDotNet;
using LibUsbDotNet.LibUsb;
using LibUsbDotNet.Main;

namespace HeliosDac
{
    /// <summary>
    /// Contains functionality for controlling all Helios Laser DACs including searching for connected devices.
    /// </summary>
    public class HeliosController
    {
        // USB consts
        public const ushort HELIOS_VID = 0x1209;
        public const ushort HELIOS_PID = 0xE500;

        UsbDeviceFinder usbDeviceFinder = new UsbDeviceFinder(HELIOS_VID, HELIOS_PID);
        
        List<HeliosDevice> dacs;


        HeliosController()
        {

        }

        ~HeliosController()
        {

        }

        /// <summary>
        /// Search for and open all Helios Laser DACs connected to the computer.
        /// </summary>
        /// <returns>The number of DACs found.</returns>
        public int OpenDevices()
        {
            CloseDevices();

            foreach (UsbRegistry usbRegistry in UsbDevice.AllLibUsbDevices)
            {
                if (usbRegistry.Pid == HELIOS_PID && usbRegistry.Vid == HELIOS_VID)
                {
                    if (usbRegistry.Open(out UsbDevice dac))
                    {
                        IUsbDevice libUsbDevice = dac as IUsbDevice;
                        libUsbDevice.ClaimInterface(0);
                        libUsbDevice.SetAltInterface(1);
                        dacs.Add(new HeliosDevice(libUsbDevice));
                    }
                }
            }

            return dacs.Count;
        }

        /// <summary>
        /// Close the connection to all Helios DACs. This invalidates all device numbers and HeliosDevice references, to use a DAC again you need to call OpenDevices() once more.
        /// </summary>
        public void CloseDevices()
        {
            foreach (var dac in dacs)
                dac.Close();
            dacs.Clear();
        }

        /// <summary>
        /// Outputs a frame to the specified DAC. This blocks the thread while the transfer happens, which can take up to tens of milliseconds, therefore it is recommended to run this in a thread. 
        /// NB: Before a frame can be written, GetStatus() must be polled and return true.
        /// </summary>
        /// <param name="deviceNumber">DAC number. Valid range is 0 up to the number of DACs as returned by OpenDevices() minus one.</param>
        /// <param name="scanRate">Number of points per second. Valid range is 7 to 0xFFFF</param>
        /// <param name="points">Array of point data (X,Y,R,G,B,I) in the frame. Max number of points is 0x1000</param>
        /// <param name="flags">Optional frame settings. OR'd bits defined in enum HeliosFrameFlags</param>
        public void WriteFrame(int deviceNumber, ushort scanRate, HeliosPoint[] points, ushort flags = 0xFF )
        {
            dacs[deviceNumber].WriteFrame(scanRate, points, flags);
        }

        /// <summary>
        /// Checks whether the specified DAC is ready to receive a new frame. NB: Not optional, must be polled and return true before every frame can be sent.
        /// </summary>
        /// <param name="deviceNumber">DAC number. Valid range is 0 up to the number of DACs as returned by OpenDevices() minus one.</param>
        /// <returns>true if the DAC is ready to receive a new frame, false otherwise.</returns>
        public bool GetStatus(int deviceNumber)
        {
            return dacs[deviceNumber].GetStatus();
        }

        /// <summary>
        /// Stops output from the specified DAC.
        /// </summary>
        /// <param name="deviceNumber">DAC number. Valid range is 0 up to the number of DACs as returned by OpenDevices() minus one.</param>
        public void StopOutput(int deviceNumber)
        {
            dacs[deviceNumber].StopOutput();
        }

        /// <summary>
        /// Sets the shutter pin of the specified DAC.
        /// </summary>
        /// <param name="deviceNumber">DAC number. Valid range is 0 up to the number of DACs as returned by OpenDevices() minus one.</param>
        /// <param name="isShutterClosed">Whether the shutter should be closed (prevents laser output)</param>
        public void SetShutter(int deviceNumber, bool isShutterClosed)
        {
            dacs[deviceNumber].SetShutter(isShutterClosed);
        }

        /// <summary>
        /// Gets the firmware version of the specified DAC.
        /// </summary>
        /// <param name="deviceNumber">DAC number. Valid range is 0 up to the number of DACs as returned by OpenDevices() minus one.</param>
        /// <returns>Firmware version</returns>
        public int GetFirmwareVersion(int deviceNumber)
        {
            return dacs[deviceNumber].GetFirmwareVersion();
        }

        /// <summary>
        /// Gets the name of the specified DAC.
        /// </summary>
        /// <param name="deviceNumber">DAC number. Valid range is 0 up to the number of DACs as returned by OpenDevices() minus one.</param>
        /// <returns>DAC name</returns>
        public string GetName(int deviceNumber)
        {
            return dacs[deviceNumber].GetName();
        }

        /// <summary>
        /// Sets the name of the specified DAC.
        /// </summary>
        /// <param name="deviceNumber">DAC number. Valid range is 0 up to the number of DACs as returned by OpenDevices() minus one.</param>
        /// <param name="name">DAC name</param>
        public void SetName(int deviceNumber, string name)
        {
            dacs[deviceNumber].SetName(name);
        }

        /// <summary>
        /// Closes the USB connection to the specified DAC. This object will no longer be usable and if the DAC is needed again you must search for it via HeliosController.OpenDevices() once more.
        /// </summary>
        /// <param name="deviceNumber">DAC number. Valid range is 0 up to the number of DACs as returned by OpenDevices() minus one.</param>
        public void Close(int deviceNumber)
        {
            dacs[deviceNumber].Close();
        }

        /// <summary>
        /// Gets a reference to a specified DAC so that you can call its control functions directly, rather than through HeliosController using its device number.
        /// </summary>
        /// <param name="deviceNumber">DAC number. Valid range is 0 up to the number of DACs as returned by OpenDevices() minus one.</param>
        /// <returns>HeliosDevice object for the specified DAC number.</returns>
        public HeliosDevice GetDevice(int deviceNumber)
        {
            return dacs[deviceNumber];
        }
    }

    /// <summary>
    /// Represents a single connected Helios Laser DAC.
    /// </summary>
    public class HeliosDevice
    {
        // Limits
        public const uint MAX_POINTS = 0x1000;
        public const uint MIN_RATE = 7;
        public const uint HELIOS_SDK_VERSION = 6;

        IUsbDevice usbDevice;
        UsbEndpointReader interruptEndpointReader;
        UsbEndpointWriter interruptEndpointWriter;
        UsbEndpointWriter bulkEndpointWriter;
        Mutex mutex;

        public HeliosDevice(IUsbDevice usbDevice)
        {
            this.usbDevice = usbDevice;

            interruptEndpointReader = usbDevice.OpenEndpointReader(ReadEndpointID.Ep03, 32, EndpointType.Interrupt);
            interruptEndpointWriter = usbDevice.OpenEndpointWriter(WriteEndpointID.Ep06, EndpointType.Interrupt);
            bulkEndpointWriter = usbDevice.OpenEndpointWriter(WriteEndpointID.Ep02, EndpointType.Bulk);
        }

        ~HeliosDevice()
        {
            Close();
        }

        /// <summary>
        /// Outputs a frame to the DAC. This blocks the thread while the transfer happens, which can take up to tens of milliseconds, therefore it is recommended to run this in a thread. 
        /// NB: Before a frame can be written, GetStatus() must be polled and return true.
        /// </summary>
        /// <param name="scanRate">Number of points per second. Valid range is 7 to 0xFFFF</param>
        /// <param name="points">Array of point data (X,Y,R,G,B,I) in the frame. Max number of points is 0x1000</param>
        /// <param name="flags">Optional frame settings. OR'd bits defined in enum HeliosFrameFlags</param>
        public void WriteFrame(ushort scanRate, HeliosPoint[] points, ushort flags = 0)
        {
            // Status OK if we send {0x03, 0} and get {0x83, 1} in return

            try
            {
                if (points.Length > MAX_POINTS || points.Length == 0)
                    throw new Exception("Invalid number of points.");
                if (scanRate < MIN_RATE)
                    throw new Exception("Invalid scanrate.");

                if (!mutex.WaitOne(1000))
                    throw new Exception("Could not acquire mutex.");



            }
            catch (Exception e)
            {
                throw e;
            }
            finally
            {
                mutex.ReleaseMutex();
            }
        }

        /// <summary>
        /// Checks whether the DAC is ready to receive a new frame. NB: Not optional, must be polled and return true before every frame can be sent.
        /// </summary>
        /// <returns>true if the DAC is ready to receive a new frame, false otherwise.</returns>
        public bool GetStatus()
        {
            // Status OK if we send {0x03, 0} and get {0x83, 1} in return

            try
            {
                if (!mutex.WaitOne(3000))
                    throw new Exception("Could not acquire mutex.");

                var errorCode = interruptEndpointWriter.Write(new byte[] { 0x03, 0 }, 16, out int writeTransferLength);
                if (errorCode == ErrorCode.Ok && writeTransferLength == 2)
                {
                    byte[] readData = new byte[32];
                    errorCode = interruptEndpointReader.Read(readData, 16, out int readTransferLength);
                    if (errorCode == ErrorCode.Ok && readTransferLength > 1 && readData[0] == 0x83)
                    {
                        return readData[1] != 0;
                    }
                    else
                        throw new Exception("Failed to receive USB interrupt response packet.");
                }
                else
                    throw new Exception("Failed to send USB interrupt packet.");
            }
            catch (Exception e)
            {
                throw e;
            }
            finally
            {
                mutex.ReleaseMutex();
            }
        }

        /// <summary>
        /// Stops output from the DAC.
        /// </summary>
        public void StopOutput()
        {
            // Send {0x01, 0}

            try
            {
                if (!mutex.WaitOne(5000))
                    throw new Exception("Could not acquire mutex.");

                var errorCode = interruptEndpointWriter.Write(new byte[] { 0x01, 0 }, 64, out int writeTransferLength);
                if (errorCode == ErrorCode.Ok && writeTransferLength == 2)
                    return;
                else
                    throw new Exception("Failed to send USB interrupt packet.");
            }
            catch (Exception e)
            {
                throw e;
            }
            finally
            {
                mutex.ReleaseMutex();
            }
        }

        /// <summary>
        /// Sets the shutter pin of the DAC.
        /// </summary>
        /// <param name="isShutterClosed">Whether the shutter should be closed (prevents laser output)</param>
        public void SetShutter(bool isShutterClosed)
        {

        }

        /// <summary>
        /// Gets the firmware version of the DAC.
        /// </summary>
        /// <returns>Firmware version</returns>
        public int GetFirmwareVersion()
        {
            return 5;
        }

        /// <summary>
        /// Gets the name of the DAC.
        /// </summary>
        /// <returns>DAC name</returns>
        public string GetName()
        {
            return "";
        }

        /// <summary>
        /// Sets the name of the DAC.
        /// </summary>
        /// <param name="name">DAC name</param>
        public void SetName(string name)
        {

        }

        /// <summary>
        /// Closes the USB connection to the DAC. This object will no longer be usable and if the DAC is needed again you must search for it via HeliosController.OpenDevices() once more.
        /// </summary>
        public void Close()
        {
            usbDevice.Close();
        }
    }

    /// <summary>
    /// Coordinates and color data for a point. Valid range for X,Y is 0 to 0xFFF (65535). Valid range for color channels is 0 to 0xFF (255).
    /// </summary>
    public struct HeliosPoint
    {
        public HeliosPoint(ushort x, ushort y, byte red, byte green, byte blue, byte intensity = 0xFF)
        {
            this.x = x;
            this.y = y;
            this.red = red;
            this.green = green;
            this.blue = blue;
            this.intensity = intensity;
        }
        ushort x;       // From 0 to 0xFFF
        ushort y;       // From 0 to 0xFFF
        byte red;       // From 0 to 0xFF
        byte green;     // From 0 to 0xFF
        byte blue;      // From 0 to 0xFF
        byte intensity; // From 0 to 0xFF
    }

    [Flags]
    public enum HeliosFrameFlags : ushort
    {
        StartImmediately = 0b1,
        DoNotLoop = 0b10,
    }
}
