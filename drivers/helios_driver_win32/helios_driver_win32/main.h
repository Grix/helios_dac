/*
Driver API for Helios Laser DACs , HEADER
By Gitle Mikkelsen, Creative Commons Attribution-NonCommercial 4.0 International Public License

Dependencies:
Libusb 1.0 (GNU Lesser General Public License, see libusb.h)
HeliosDAC class (part of this driver)
*/

#pragma once

#include "libusb.h"
#include "stdio.h"
#include "HeliosDac.h"
#include "OpenLaserShowControllerV1.0.0-Mod.h"

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
//	Bit 2 = if true, do NOT check if DAC is ready before sending a frame (must be done manually using GetStatus instead otherwise the write will fail)
//	Bit 3-7 = reserved
//points: pointer to point data. See point structure documentation in main.h
//numOfPoints: number of points in the frame
//returns 1 if successful
HELIOS_EXPORT int WriteFrame(int dacNum, int pps, uint8_t flags, HeliosPoint* points, int numOfPoints);

//sets the shutter of the specified dac. 
//value 1 = shutter on, value 0 = shutter off
//returns 1 if successful
HELIOS_EXPORT int SetShutter(int dacNum, bool shutterValue);

//gets a descriptive name of the specified dac
//name is max 32 bytes long
//returns 1 if successful
HELIOS_EXPORT int GetName(int dacNum, char* name);

//stops, blanks and centers output on the specified dac
//returns 1 if successful
HELIOS_EXPORT int Stop(int dacNum);

//closes connection to all dacs and frees resources
//should be called when library is no longer needed (program exit for example)
HELIOS_EXPORT int CloseDevices();