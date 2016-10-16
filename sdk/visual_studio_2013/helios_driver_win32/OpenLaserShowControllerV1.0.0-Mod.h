/*

OpenLaserShowController.h : main header file for the OpenLaserShowController DLL

[!! Slightly modified for Helios]
-> Changes:
	- Not dependent on windows.h
		- stdint types
		- OLSC_SetCallback removed
	- OPEN_LASER_SHOW_DEVICE_API_VERSION defined

Copyright (c) 2009 Dennis Kromhout, Chris Favreau, Andreas Unger

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

*/

// ****************************************************************************************************************
// ** Open Laser Show Controler Version 1 API
// ****************************************************************************************************************

#ifndef __OPENLASERSHOWCONTROLLER_H__
#define __OPENLASERSHOWCONTROLLER_H__

#include <stdint.h>

#pragma pack(1)

// ****************************************************************************************************************
// ** Constants
// ****************************************************************************************************************

#define OPEN_LASER_SHOW_DEVICE_API_VERSION	1

// Shutter State
#define LASER_SHOW_DEVICE_SHUTTER_STATE_ON		0
#define LASER_SHOW_DEVICE_SHUTTER_STATE_OFF		1

// Standard Errors
// TODO - add errors to this list so we can be more verbose in describing the particular error that occurred.
#define OLSC_ERROR_SUCCESS						1
#define OLSC_ERROR_NONE							0
#define OLSC_ERROR_INVALID_PARAMETER			-1
#define OLSC_ERROR_FAILED						-2

// Status Bits
// Status Clear
#define OLSC_STATUS_NONE                       0x00000000
// Bit 0 = Buffer Full
#define OLSC_STATUS_BUFFER_FULL                0x00000001
// Bit 1 = Buffer Empty
#define OLSC_STATUS_BUFFER_EMPTY               0x00000002
// Bit 2 = DMX Out Complete
#define OLSC_STATUS_DMX_OUT_COMPLETE           0x00000004
// Bit 3 = DMX In Ready
#define OLSC_STATUS_DMX_IN_READY               0x00000008
// Bit 4 = TTL Out Complete
#define OLSC_STATUS_TTL_OUT_COMPLETE           0x00000010
// Bit 5 = TLL In Ready
#define OLSC_STATUS_TTL_IN_READY               0x00000020
// Bit 6 = Resreved
// Bit 7 = Reserved
// Bit 8 = Reserved
// Bit 9-30 = Reserved
// Bit 31 = An Error Occured
#define OLSC_STATUS_ERROR                      0x80000000

// ****************************************************************************************************************
// ** Data Structures
// ****************************************************************************************************************

struct LASER_SHOW_DEVICE_CAPABILITIES
{
	// Device Name
	char name[1024];
	// Device Version
	int	version_major;
	int	version_minor;
	// Min Speed/Max Speed
	int min_speed;
	int max_speed;
	// Min Frame Size/Max Frame Size
	int min_frame_size;
	int max_frame_size;
	// DMX In/Out?
	bool has_dmx_in;
	bool has_dmx_out;
	// TTL In/Out?
	bool has_ttl_in;
	bool has_ttl_out;
	// X/Y Resolution (8 to 16 bits)
	int	xy_resolution;
	// Color Resolution (1 to 16 bits)
	int color_resolution;
	// Uses callbacks?
	bool uses_callbacks;
};


struct LASER_SHOW_DEVICE_POINT
{
	uint16_t x; //16bit
	uint16_t y; //16bit
	uint16_t r; //8bit !!
	uint16_t g; //8bit !!
	uint16_t b; //8bit !!
	uint16_t i; //8bit !!
};


struct LASER_SHOW_DEVICE_FRAME
{
	int display_speed;
	int point_count;
	struct LASER_SHOW_DEVICE_POINT *points;
};

// ****************************************************************************************************************
// ** Function Prototypes
// ****************************************************************************************************************

// Comment out if this .H file is part of an application
// This needs to be defined if this .H file is part of a driver DLL
// *** BE SURE TO DEFINE OLSC_EXPORTS if you are writing an OLSC Driver DLL
#define OLSC_EXPORTS 1

#ifdef OLSC_EXPORTS
#define OLSC_API __declspec(dllexport)
#else
#define OLSC_API __declspec(dllimport)
#endif

#ifdef __cplusplus 
extern "C" {
#endif

// OLSC_GetAPIVersion
// Inputs: None
// Outputs: Returns a single integer that represents the version number
// Description: Returns the version of the OpenDAC API
//				so we don't make any critical errors when using this DLL
OLSC_API int WINAPI OLSC_GetAPIVersion(void);

// OLSC_GetInterfaceName
// Inputs: Pointer to a string at least 64 characters in length
// Outputs: Returns success or failure
// Description: Returns the string name of the OpenDC Interface
OLSC_API int WINAPI OLSC_GetInterfaceName(char *pString);

// OLSC_Initialize
// Inputs: None
// Outputs: Returns the number of available devices.
// Description: Initializes the hardware
OLSC_API int WINAPI OLSC_Initialize(void);

// OLSC_Shutdown
// Inputs: None
// Outputs: Returns success or failure
// Description: Shuts down all devices
OLSC_API int WINAPI OLSC_Shutdown(void);

// OLSC_GetDeviceCount
// Inputs: None
// Outputs: Returns the number of available devices
// Description: Has to be called AFTER Intialize has been called.  Thsi function
// is to be used to query the number of available devices without calling
// intialize again and again
OLSC_API int WINAPI OLSC_GetDeviceCount(void);

// OLSC_GetCapabilities
// Inputs:  device Number, device capabilties structure to be filled in
// Outputs: Returns success or failure
// Description: Gets the capabilties of each device attached
//				Caps:
//				Device Name
//				Device Version
//				Min Speed/Max Speed
//				Min Frame Size/Max Frame Size
//				DMX In/Out?
//				TTL In/Out?
//				X/Y Resolution (8 to 16 bits)
//				Color Resolution (1 to 16 bits)
//				Uses callbacks?
//				Some reserved space for future use
OLSC_API int WINAPI OLSC_GetDeviceCapabilities(int device_number, struct LASER_SHOW_DEVICE_CAPABILITIES &device_capabilities);

// OLSC_GetLastErrorNumber
// Inputs: device number, error string pointer, and string length max.
// Outputs: error number, and actual error string
// Description: Get the string and/or number associated with the last error
OLSC_API int WINAPI OLSC_GetLastErrorNumber(int device_number, int &number, char *string_pointer, int string_length);

// OLSC_Play
// Inputs: device number
// Outputs: Returns success or failure
// Description: Starts the output on a particular device or all devices
OLSC_API int WINAPI OLSC_Play(int device_number);

// OLSC_Pause
// Inputs: device number
// Outputs: Returns success or failure
// Description: Stops the output on a particular device or all devices
OLSC_API int WINAPI OLSC_Pause(int device_number);

// OLSC_Shutter
// Inputs: device number, shutter state (LASER_SHOW_DEVICE_SHUTTER_STATE)
// Outputs: Returns success or failure
// Description: Turns the laser show device's shutter On/Off
OLSC_API int WINAPI OLSC_Shutter(int device_number, int state);

// OLSC_WriteFrameEx
// Inputs: device number, display speed (pps), point count, point to array of LASER_SHOW_DEVICE_POINTs 
// Outputs: Returns success or failure
// Description:
// Writes a frame to a particular device or all devices
// Point Array:
// X 16 bit unsigned
// Y 16 bit unsigned
// R 16 bit unsigned
// G 16 bit unsigned
// B 16 bit unsigned
// I 16 bit unsigned
//
// ** Any frame that is written will be displayed until another frame is written to take its place or the Output is Paused
//
OLSC_API int WINAPI OLSC_WriteFrameEx(int device_number, int display_speed, int point_count, struct LASER_SHOW_DEVICE_POINT *points);

// OLSC_WriteFrame
// Inputs: device number, frame structure (LASER_SHOW_DEIVCE_FRAME)
// Outputs: Returns success or failure
// Description:
// Writes a frame to a particular device or all devices
// Pass in a frame:
// Point Count
// Display Speed PPS
// Point Array:
// X 16 bit unsigned
// Y 16 bit unsigned
// R 16 bit unsigned
// G 16 bit unsigned
// B 16 bit unsigned
// I 16 bit unsigned
//
// ** Any frame that is written will be displayed until another frame is written to take its place or the Output is Paused
//
OLSC_API int WINAPI OLSC_WriteFrame(int device_number, struct LASER_SHOW_DEVICE_FRAME frame);

// OLSC_GetStatus()
// Inputs: device number, status DWORD
// Outputs:  Returns success or failure
// Description:
// Gets the status of a particular device
// Can be used for polling or in conjunction with Windows Message Callback
// Status Structure or Bit Mask:
// Bit 0 = Buffer Full
// Bit 1 = Buffer Empty
// Bit 2 = DMX Out Complete
// Bit 3 = DMX In Ready
// Bit 4 = TTL Out Complete
// Bit 5 = TLL In Ready
// Bit 6 = Resreved
// Bit 7 = Reserved
// Bit 8 = Reserved
// Bit 9-30 = Reserved
// Bit 31 = An Error Occured
OLSC_API int WINAPI OLSC_GetStatus(int device_number, uint32_t &status);


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#include <Windows.h>
	// OLSC_SetCallback()
	// Inputs: device number, parent window handle (for SendMessage), message DWORD
	// Outputs:  Returns success or failure
	// Description:
	// Sets the call back window parent handle and windows message to send to run the callback
	// and set the call back notification mask bits per the GetStatus mask.  The Callback message
	// will return the Device Number in the wParam and the Status mask in the lParam.
	// We all work in windows right?
	// This interface is optional in the DLL and in the application.  The DLL writers should take this into account.
	// So if you use the callback ... be able to function without it... it is used for efficiency.
	OLSC_API int WINAPI OLSC_SetCallback(int device_number, HWND parent_window_handle, uint32_t message);
#endif

// OLSC_WriteDMX()
// Inputs: device number, start address, data pointer, data length
// Outputs:  Returns success or failure
// Description:
// Writes DMX data to a particular device
	OLSC_API int WINAPI OLSC_WriteDMX(int device_number, int start_address, uint8_t *data_pointer, int length);

// OLSC_ReadDMX()
// Inputs: device number, start address, data pointer, data length
// Outputs:  Returns success or failure
// Description:
// Reads DMX data from a particular device
	OLSC_API int WINAPI OLSC_ReadDMX(int device_number, int start_address, uint8_t *data_pointer, int length);

// OLSC_WriteTTL()
// Inputs: device number, data DWORD (up to 32 bits of TTL outputs)
// Outputs:  Returns success or failure
// Description:
// Writes TTL data from a particular device
OLSC_API int WINAPI OLSC_WriteTTL(int device_number, uint32_t data);

// OLSC_ReadTTL()
// Inputs: device number, data DWORD (up to 32 bits of TTL inputs)
// Outputs:  Returns success or failure
// Description:
// Reads TTL data from a particular device
OLSC_API int WINAPI OLSC_ReadTTL(int device_number, uint32_t &data);

#ifdef __cplusplus 
}
#endif

#endif	// __OPENLASERSHOWCONTROLLER_H__
