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
using System.Text;
using System.Threading;
using LibUsbDotNet;
using LibUsbDotNet.LibUsb;
using LibUsbDotNet.Main;
using LibUsbDotNet.WinUsb;

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

        //UsbDeviceFinder usbDeviceFinder = new UsbDeviceFinder(HELIOS_VID, HELIOS_PID);

        private readonly List<HeliosDevice> dacs = new List<HeliosDevice>();


        public HeliosController()
        {

        }

        ~HeliosController()
        {
            CloseDevices();
        }

        /// <summary>
        /// Search for and open all Helios Laser DACs connected to the computer.
        /// </summary>
        /// <returns>The number of DACs found.</returns>
        public int OpenDevices()
        {
            CloseDevices();

            foreach (UsbRegistry usbRegistry in UsbDevice.AllDevices)
            {
                if (usbRegistry.Pid == HELIOS_PID && usbRegistry.Vid == HELIOS_VID)
                {
                    if (usbRegistry.Open(out UsbDevice dac))
                    {
                        IUsbDevice libUsbDevice = dac as IUsbDevice;
                        if (libUsbDevice != null)
                        {
                            libUsbDevice.ClaimInterface(0);
                            libUsbDevice.SetAltInterface(1);
                        }
                        dacs.Add(new HeliosDevice(dac));
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
        /// <param name="flags">Optional frame settings, each bit is a bool. Bits defined in enum HeliosFrameFlags</param>
        public void WriteFrame(int deviceNumber, ushort scanRate, HeliosPoint[] points, byte flags = 0)
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

        private UsbDevice usbDevice;
        private UsbEndpointReader interruptEndpointReader;
        private UsbEndpointWriter interruptEndpointWriter;
        private UsbEndpointWriter bulkEndpointWriter;
        private Mutex mutex = new Mutex();
        private byte[] frameBuffer = new byte[MAX_POINTS];

        public HeliosDevice(UsbDevice usbDevice)
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
        /// <param name="flags">Optional frame settings, each bit is a bool. Bits defined in enum HeliosFrameFlags</param>
        public void WriteFrame(ushort scanRate, HeliosPoint[] points, byte flags = 0)
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

                // This is a bug workaround, the MCU won't correctly receive transfers with these specific sizes
                int scanRateActual = scanRate;
                int numOfPointsActual = points.Length;
                if (((points.Length - 45) % 64) == 0)
                {
                    numOfPointsActual--;
                    scanRateActual = (int)Math.Round(scanRate * (double)numOfPointsActual / (double)points.Length); // Adjust pps to keep the same frame duration even with one less point
                }

                // Prepare frame buffer
                int bufPos = 0;
                for (int i = 0; i < numOfPointsActual; i++)
                {
                    frameBuffer[bufPos++] = (byte)(points[i].X >> 4);
                    frameBuffer[bufPos++] = (byte)(((points[i].X & 0x0F) << 4) | (points[i].Y >> 8));
                    frameBuffer[bufPos++] = (byte)(points[i].Y & 0xFF);
                    frameBuffer[bufPos++] = points[i].Red;
                    frameBuffer[bufPos++] = points[i].Green;
                    frameBuffer[bufPos++] = points[i].Blue;
                    frameBuffer[bufPos++] = points[i].Intensity;
                }
                frameBuffer[bufPos++] = (byte)(scanRateActual & 0xFF);
                frameBuffer[bufPos++] = (byte)(scanRateActual >> 8);
                frameBuffer[bufPos++] = (byte)(numOfPointsActual & 0xFF);
                frameBuffer[bufPos++] = (byte)(numOfPointsActual >> 8);
                frameBuffer[bufPos++] = flags;

                // Send USB transaction
                var result = bulkEndpointWriter.Write(frameBuffer, 0, bufPos, 8 + (bufPos >> 5), out int transferLength);

                if (result != ErrorCode.Ok || transferLength == bufPos)
                {
                    throw new Exception("Could not send frame USB transaction. Error code: " + result.ToString() + ". Make sure you first poll GetStatus() before writing a frame.");
                }

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
                        return false;
                }
                else
                    throw new Exception("Failed to send USB interrupt packet. Error code: " + errorCode.ToString());
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
                    throw new Exception("Failed to send USB interrupt packet. Error code: " + errorCode.ToString());
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
        /// <param name="shutterClosed">Whether the shutter should be closed (prevents laser output)</param>
        public void SetShutter(bool shutterClosed)
        {
            // Send {0x02, shutterValue}

            try
            {
                if (!mutex.WaitOne(5000))
                    throw new Exception("Could not acquire mutex.");

                var errorCode = interruptEndpointWriter.Write(new byte[] { 0x02, shutterClosed ? (byte)0 : (byte)1 }, 64, out int writeTransferLength);
                if (errorCode == ErrorCode.Ok && writeTransferLength == 2)
                    return;
                else
                    throw new Exception("Failed to send USB interrupt packet. Error code: " + errorCode.ToString());
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
        /// Gets the firmware version of the DAC.
        /// </summary>
        /// <returns>Firmware version</returns>
        public int GetFirmwareVersion()
        {
            // Send {0x04, 0} and get {0x84, firmwareVersion} in return

            try
            {
                if (!mutex.WaitOne(3000))
                    throw new Exception("Could not acquire mutex.");

                var errorCode = interruptEndpointWriter.Write(new byte[] { 0x04, 0 }, 64, out int writeTransferLength);
                if (errorCode == ErrorCode.Ok && writeTransferLength == 2)
                {
                    byte[] readData = new byte[32];
                    errorCode = interruptEndpointReader.Read(readData, 16, out int readTransferLength);
                    if (errorCode == ErrorCode.Ok && readTransferLength > 1 && readData[0] == 0x84)
                    {
                        return readData[1];
                    }
                    else
                        throw new Exception("Invalid response to firmware version request. Error code: " + errorCode.ToString());
                }
                else
                    throw new Exception("Failed to send USB interrupt packet. Error code: " + errorCode.ToString());
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
        /// Gets the name of the DAC.
        /// </summary>
        /// <returns>DAC name</returns>
        public string GetName()
        {
            // If we send {0x05, 0} we should get {0x85, [name]} in return.

            try
            {
                if (!mutex.WaitOne(3000))
                    throw new Exception("Could not acquire mutex.");

                var errorCode = interruptEndpointWriter.Write(new byte[] { 0x05, 0 }, 16, out int writeTransferLength);
                if (errorCode == ErrorCode.Ok && writeTransferLength == 2)
                {
                    byte[] readData = new byte[32];
                    errorCode = interruptEndpointReader.Read(readData, 32, out int readTransferLength);
                    if (errorCode == ErrorCode.Ok && readTransferLength > 2 && readData[0] == 0x85)
                        return Encoding.ASCII.GetString(readData, 1, readTransferLength-1);
                    else
                        throw new Exception("Did not get valid response from DAC. Error code: " + errorCode.ToString());
                }
                else
                    throw new Exception("Failed to send USB interrupt packet. Error code: " + errorCode.ToString());
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
        /// Sets the name of the DAC.
        /// </summary>
        /// <param name="name">DAC name (max 30 characters, ascii only)</param>
        public void SetName(string name)
        {
            // Send {0x06, [name]}

            try
            {
                if (!mutex.WaitOne(5000))
                    throw new Exception("Could not acquire mutex.");

                var message = new byte[32];
                message[0] = 0x06;
                var nameBytes = ASCIIEncoding.ASCII.GetBytes(name);
                for (int i = 0; i < nameBytes.Length && i < 31; i++)
                    message[1 + i] = nameBytes[i];

                message[31] = 0;

                var errorCode = interruptEndpointWriter.Write(message, 64, out int writeTransferLength);
                if (errorCode == ErrorCode.Ok && writeTransferLength == message.Length)
                    return;
                else
                    throw new Exception("Failed to send USB interrupt packet. Error code: " + errorCode.ToString());
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
            this.X = x;
            this.Y = y;
            this.Red = red;
            this.Green = green;
            this.Blue = blue;
            this.Intensity = intensity;
        }
        public ushort X;       // From 0 to 0xFFF
        public ushort Y;       // From 0 to 0xFFF
        public byte Red;       // From 0 to 0xFF
        public byte Green;     // From 0 to 0xFF
        public byte Blue;      // From 0 to 0xFF
        public byte Intensity; // From 0 to 0xFF
    }

    [Flags]
    public enum HeliosFrameFlags : ushort
    {
        StartImmediately = 0b1,
        DoNotLoop = 0b10,
    }
}
