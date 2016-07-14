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

#define HELIOS_EXPORT extern "C" __declspec (dllexport)
#define OLSC_EXPORT extern "C" __declspec(dllexport)

bool inited = false;
HeliosDac* dacController;
uint8_t* frameBuffer;

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

//for function documentations, see main.cpp
HELIOS_EXPORT int OpenDevices();
HELIOS_EXPORT uint8_t GetStatus(int dacNum);
HELIOS_EXPORT int WriteFrame(int dacNum, int pps, uint8_t flags, uint8_t* points, int numOfPoints);
HELIOS_EXPORT int SetShutter(int dacNum, bool shutterValue);
HELIOS_EXPORT int GetName(int dacNum, char* name);
HELIOS_EXPORT int Stop(int dacNum);
HELIOS_EXPORT int CloseDevices();

//Below is OLSC implementation only
//OLSC API is designed by Chris Favreau, MIT License

#define OLSC_VERSION	1

typedef struct
{
	WORD x; //16 bit (from 0 to 0xFFFF)
	WORD y; //16 bit (from 0 to 0xFFFF)
	WORD r; //8 bit (from 0 to 0xFF)
	WORD g; //8 bit (from 0 to 0xFF)
	WORD b; //8 bit (from 0 to 0xFF)
	WORD i; //8 bit (from 0 to 0xFF)
	//color resolution is unspecified in olsc v1.0 but in the olsd driver it is implemented as 8bit so I do the same
} OLSC_Point;

typedef struct
{
	int display_speed; //pps
	int point_count;
	OLSC_Point* points;
} OLSC_Frame;

typedef struct 
{
	char name[1024];
	int	version_major;
	int	version_minor;
	int min_speed;
	int max_speed;
	int min_frame_size;
	int max_frame_size;
	bool has_dmx_in;
	bool has_dmx_out;
	bool has_ttl_in;
	bool has_ttl_out;
	int	xy_resolution;
	int color_resolution;
	bool uses_callbacks;
} OLSC_DeviceCapabilites;

OLSC_EXPORT int WINAPI OLSC_GetAPIVersion(void);
OLSC_EXPORT int WINAPI OLSC_GetInterfaceName(char* pString);
OLSC_EXPORT int WINAPI OLSC_Initialize(void);
OLSC_EXPORT int WINAPI OLSC_Shutdown(void);
OLSC_EXPORT int WINAPI OLSC_GetDeviceCount(void);
OLSC_EXPORT int WINAPI OLSC_GetDeviceCapabilities(int device_number, OLSC_DeviceCapabilites& device_capabilities);
OLSC_EXPORT int WINAPI OLSC_GetLastErrorNumber(int device_number, int& number, char* string_pointer, int string_length);
OLSC_EXPORT int WINAPI OLSC_Play(int device_number);
OLSC_EXPORT int WINAPI OLSC_Pause(int device_number);
OLSC_EXPORT int WINAPI OLSC_Shutter(int device_number, int state);
OLSC_EXPORT int WINAPI OLSC_WriteFrame(int device_number, OLSC_Frame frame);
OLSC_EXPORT int WINAPI OLSC_GetStatus(int device_number, DWORD& status);
OLSC_EXPORT int WINAPI OLSC_WriteDMX(int device_number, int start_address, unsigned char *data_pointer, int length);
OLSC_EXPORT int WINAPI OLSC_ReadDMX(int device_number, int start_address, unsigned char *data_pointer, int length);
OLSC_EXPORT int WINAPI OLSC_WriteTTL(int device_number, DWORD data);
OLSC_EXPORT int WINAPI OLSC_ReadTTL(int device_number, DWORD& data);
