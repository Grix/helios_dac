/*
Helios Laser DAC SDK shared library, HEADER
By Gitle Mikkelsen
gitlem@gmail.com

Dependencies:
Libusb 1.0 (GNU Lesser General Public License, see libusb.h)
HeliosDAC class
OpenLaserShowControllerV1.0.0 header and .def file (only on windows)

Standard: C++14

BASIC USAGE:
1.	Call OpenDevices() or OLSC_Initialize() to open devices, returns number of available devices
2.	To send a new frame, first call GetStatus() or OLSC_GetStatus(). If the function returns ready
	(1 for GetStatus, OLSC_STATUS_BUFFER_EMPTY for OLSC_GetStatus), then you can call WriteFrame()
	or OLSC_WriteFrame() / OLSC_WriteFrameEx().
	The status should be polled until it returns ready. It can and sometimes will fail to return ready on the first try.
3.  To stop output, use Stop() or OLSC_Pause(). To restart output you must send a new frame as described above.
4.	When the DAC is no longer needed, free it using CloseDevices() or OLSC_Shutdown()
See OpenLaserShowControllerV1.0.0-Mod.h for documentation on OLSC_* functions. Not recommended for cross-platform apps

The DAC is double-buffered. When it receives its first frame, it starts outputting it. When a second frame is sent to
the DAC while the first frame is being played, the second frame is stored in the DACs memory until the first frame
finishes playback, at which point the second, buffered frame will start playing. If the DAC finished playback of a frame
without having received and buffered a second frame, it will by default loop the first frame until a new frame is
received (but the flag HELIOS_FLAG_SINGLE_MODE will make it stop playback instead).
The GetStatus() function actually checks whether or not the buffer on the DAC is empty or full. If it is full, the DAC
cannot receive a new frame until the currently playing frame finishes, freeing up the buffer.
*/

#pragma once

#include "HeliosDac.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#include "OpenLaserShowControllerV1.0.0-Mod.h"
	#define HELIOS_EXPORT extern "C" __declspec (dllexport)
#else
	#define HELIOS_EXPORT extern "C"
#endif

#define STDCALL __stdcall

bool inited = false;
bool flipX = true;

HeliosDac* dacController;

//initializes drivers, opens connection to all devices.
//Returns number of available devices.
//NB: To re-scan for newly connected DACs after this function has once been called before, you must first call CloseDevices()
HELIOS_EXPORT int OpenDevices();

//Gets status from the specified dac.
//Return 1 if ready to receive new frame, 0 if not, -1 if communcation failed
HELIOS_EXPORT int GetStatus(unsigned int dacNum);

//Sets libusb debug log level
//See libusb.h for log level values
HELIOS_EXPORT int SetLibusbDebugLogLevel(int logLevel);

//writes and outputs a frame to the speficied dac
//dacNum: dac number (0 to n where n+1 is the return value from OpenDevices() )
//pps: rate of output in points per second
//flags: (default is 0)
//	Bit 0 (LSB) = if true, start output immediately, instead of waiting for current frame (if there is one) to finish playing
//	Bit 1 = if true, play frame only once, instead of repeating until another frame is written
//	Bit 2-7 = reserved
//points: pointer to point data. See point structure documentation in HeliosDac.h
//numOfPoints: number of points in the frame
//returns 1 if successful
HELIOS_EXPORT int WriteFrame(unsigned int dacNum, int pps, std::uint8_t flags, HeliosPoint* points, int numOfPoints);

//sets the shutter of the specified dac.
//value 1 = shutter open, value 0 = shutter closed
//returns 1 if successful
HELIOS_EXPORT int SetShutter(unsigned int dacNum, bool shutterValue);

//Returns the firmware version number. Returns -1 if communcation failed.
HELIOS_EXPORT int GetFirmwareVersion(unsigned int dacNum);

//gets a descriptive name of the specified dac
//name is max 32 bytes long, char needs to be able to hold 32 bytes
//returns 1 if successful, return 0 if the proper name couldn't be fetched from the DAC, but name is
//still populated with a fallback numbered name based on order of discovery by the library
//return -1 if unsuccessful and name is not populated.
HELIOS_EXPORT int GetName(unsigned int dacNum, char* name);

//gets a descriptive name of the specified dac
//name is max 31 bytes long including null terminator
//returns 1 if successful, return 0 if the transfer failed
HELIOS_EXPORT int SetName(unsigned int dacNum, char* name);

//stops, blanks and centers output on the specified dac
//returns 1 if successful
HELIOS_EXPORT int Stop(unsigned int dacNum);

//closes connection to all dacs and frees resources
//should be called when library is no longer needed (program exit for example)
HELIOS_EXPORT int CloseDevices();

//Clears the GPNVM1 bit on the DACs microcontroller. This will cause the DAC to boot into SAM-BA bootloader
//which allows new firmware to be uploaded over USB.
HELIOS_EXPORT int EraseFirmware(unsigned int dacNum);


/* EzAudDac API */
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

	struct EAD_Pnt_s {
		int16_t X;
		int16_t Y;
		int16_t R;
		int16_t G;
		int16_t B;
		int16_t I;
		int16_t AL;
		int16_t AR;
	};

	HELIOS_EXPORT int STDCALL EzAudDacGetCardNum(void);
	HELIOS_EXPORT bool STDCALL EzAudDacWriteFrame(const int *CardNum, const struct EAD_Pnt_s* data, int Bytes, uint16_t PPS);
	HELIOS_EXPORT bool STDCALL EzAudDacWriteFrameNR(const int *CardNum, const struct EAD_Pnt_s* data, int Bytes, uint16_t PPS, uint16_t Reps);
	HELIOS_EXPORT int STDCALL EzAudDacGetStatus(const int *CardNum);
	HELIOS_EXPORT bool STDCALL EzAudDacStop(const int *CardNum);
	HELIOS_EXPORT bool STDCALL EzAudDacClose(void);

#endif