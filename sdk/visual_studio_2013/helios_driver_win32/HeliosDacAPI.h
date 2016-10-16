/*
Driver API for Helios Laser DACs , HEADER
By Gitle Mikkelsen, Creative Commons Attribution-NonCommercial 4.0 International Public License
gitlem@gmail.com

Dependencies:
Libusb 1.0 (GNU Lesser General Public License, see libusb.h)
HeliosDAC class (part of this driver)
OpenLaserShowControllerV1.0.0 header and .def file

BASIC USAGE:

1.	Call OpenDevices() or OLSC_Initialize() to open devices, returns number of available devices

2.	To send a new frame, first call GetStatus() or OLSC_GetStatus. If the function returns ready
	(1 for GetStatus, OLSC_STATUS_BUFFER_EMPTY for OLSC_GetStatus), then you can call WriteFrame()
	or OLSC_WriteFrame() / OLSC_WriteFrameEx(). 

	You must get the status every time before a frame is written. The status will usually take about 2 ms to fetch.
	The status should be polled until it returns ready. It can and sometimes will fail to return ready on the first try.
	Care should be taken not to have multiple status requests or frame transfers run at the same time. Use a
	mutex or something similar to force correct order and timing when interfacing with the DAC.
	Both the status getters and frame write functions are BLOCKING and can take many milliseconds to finish if the frame is large.
	It is recommended to run them in a separate thread from your main program.

3.  To stop output, use Stop() or OLSC_Pause(). To restart output you must send a new frame as described above.
4.	When the DAC is no longer needed, free it using CloseDevices() or OLSC_Shutdown()

See OpenLaserShowControllerV1.0.0-Mod.h for documentation on OLSC_* functions. Not recommended for cross-platform apps

*/

#pragma once

//#include "libusb.h"
#include "stdio.h"
#include "HeliosDac.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#include "OpenLaserShowControllerV1.0.0-Mod.h"
#endif

#define HELIOS_EXPORT extern "C" __declspec (dllexport)

bool inited = false;
HeliosDac* dacController;

//point data structure
typedef struct 
{
	uint16_t x; //12 bit (from 0 to 0xFFF)
	uint16_t y; //12 bit (from 0 to 0xFFF)
	uint8_t r;	//8 bit	(from 0 to 0xFF)
	uint8_t g;	//8 bit (from 0 to 0xFF)
	uint8_t b;	//8 bit (from 0 to 0xFF)
	uint8_t i;	//8 bit (from 0 to 0xFF)
} HeliosPoint;

//initializes drivers, opens connection to all devices. 
//Returns number of available devices.
HELIOS_EXPORT int OpenDevices();

//Gets status from the specified dac. 
//Return 1 if ready to receive new frame, 0 if not, -1 if communcation failed
HELIOS_EXPORT int GetStatus(int dacNum);

//writes and outputs a frame to the speficied dac
//dacNum: dac number (0 to n where n+1 is the return value from OpenDevices() )
//pps: rate of output in points per second
//flags: (default is 0)
//	Bit 0 (LSB) = if true, start output immediately, instead of waiting for current frame (if there is one) to finish playing
//	Bit 1 = if true, play frame only once, instead of repeating until another frame is written
//	Bit 2-7 = reserved
//points: pointer to point data. See point structure documentation in main.h
//numOfPoints: number of points in the frame
//returns 1 if successful
HELIOS_EXPORT int WriteFrame(int dacNum, int pps, uint8_t flags, HeliosPoint* points, int numOfPoints);

//sets the shutter of the specified dac. 
//value 1 = shutter on, value 0 = shutter off
//returns 1 if successful
HELIOS_EXPORT int SetShutter(int dacNum, bool shutterValue);

//Returns the firmware version number. Returns -1 if communcation failed.
HELIOS_EXPORT int GetFirmwareVersion(int dacNum);

//gets a descriptive name of the specified dac
//name is max 32 bytes long, char needs to be able to hold 32 bytes
//returns 1 if successful, return 0 if the proper name couldn't be fetched from the DAC, but name is
//still populated with a fallback numbered name based on order of discovery by the library
//return -1 if unsuccessful and name is not populated.
HELIOS_EXPORT int GetName(int dacNum, char* name);

//stops, blanks and centers output on the specified dac
//returns 1 if successful
HELIOS_EXPORT int Stop(int dacNum);

//closes connection to all dacs and frees resources
//should be called when library is no longer needed (program exit for example)
HELIOS_EXPORT int CloseDevices();