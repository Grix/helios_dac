/*
Driver API for Helios Laser DACs
By Gitle Mikkelsen, Creative Commons Attribution-NonCommercial 4.0 International Public License

See HeliosDacAPI.h for documentation

Dependencies:
Libusb 1.0 (GNU Lesser General Public License, see libusb.h)
HeliosDAC class (part of this driver)
*/

#include "HeliosDacAPI.h"

#ifdef __linux__
	#include <memory.h>
#endif

int OpenDevices()
{
	CloseDevices();

	dacController = new HeliosDac();

	int result = dacController->OpenDevices();

	if (result <= 0)
		delete dacController;
	else
		inited = true;

	printf("OpenDevices() found: %d", result);

	return result;
}


int WriteFrame(int dacNum, int pps, uint8_t flags, HeliosPoint* points, int numOfPoints)
{
	if ((!inited) || (points == NULL))
		return 0;
	if ((numOfPoints > HELIOS_MAX_POINTS) || (pps > HELIOS_MAX_RATE) || (pps < HELIOS_MIN_RATE))
		return 0;

	//prepare frame buffer
	uint8_t frameBuffer[HELIOS_MAX_POINTS * 7 + 5];
	int bufPos = 0;
	for (int i = 0; i < numOfPoints; i++)
	{
		frameBuffer[bufPos++] = (points[i].x >> 4);
		frameBuffer[bufPos++] = ((points[i].x & 0x0F) << 4) | (points[i].y >> 8);
		frameBuffer[bufPos++] = (points[i].y & 0xFF);
		frameBuffer[bufPos++] = points[i].r;
		frameBuffer[bufPos++] = points[i].g;
		frameBuffer[bufPos++] = points[i].b;
		frameBuffer[bufPos++] = points[i].i;
	}
	frameBuffer[bufPos++] = (pps & 0xFF);
	frameBuffer[bufPos++] = (pps >> 8);
	frameBuffer[bufPos++] = (numOfPoints & 0xFF);
	frameBuffer[bufPos++] = (numOfPoints >> 8);
	frameBuffer[bufPos++] = flags;

	return dacController->SendFrame(dacNum, &frameBuffer[0], bufPos);
}

int Stop(int dacNum)
{
	if (!inited)
		return 0;

	uint8_t ctrlBuffer[2] = { 0x01, 0 };
	if (dacController->SendControl(dacNum, &ctrlBuffer[0], 2))
		return 1;
	else
		return 0;
}


int GetName(int dacNum, char* name)
{
	if (!inited)
		return  -1;

	uint8_t ctrlBuffer[32] = { 0x05, 0 };
	int tx = dacController->SendControl(dacNum, &ctrlBuffer[0], 2);
	if (tx == 1)
	{
		tx = dacController->GetControlResponse(dacNum, &ctrlBuffer[0], 32);
		if (tx == 1)
		{
			if ((ctrlBuffer[0]) == 0x85) //if received control byte is as expected
			{
				memcpy(name, &ctrlBuffer[1], 32);
				return 1;
			}
		}
	}

	//if the above failed, fallback name:
	memcpy(name, "Helios ", 8);
	name[7] = (char)((int)(dacNum >= 10) + 48);
	name[8] = (char)((int)(dacNum % 10) + 48);
	name[9] = '\0';
	return 0;
}

int SetName(int dacNum, char* name)
{
	if (!inited)
		return  -1;

	uint8_t ctrlBuffer[32] = { 0x06 };
	memcpy(&ctrlBuffer[1], name, 31);
	return dacController->SendControl(dacNum, &ctrlBuffer[0], 32);
}


int GetStatus(int dacNum)
{
	if (!inited)
		return -1;

	uint8_t ctrlBuffer[32] = { 0x03, 0 };
	int tx = dacController->SendControl(dacNum, &ctrlBuffer[0], 2);
	if (tx != 1)
		return -1;

	tx = dacController->GetControlResponse(dacNum, &ctrlBuffer[0], 2);
	if (tx == 1)
	{
		if ((ctrlBuffer[0]) == 0x83) //if received control byte is as expected
		{
			if (ctrlBuffer[1] == 1) //if dac is ready
				return 1;
			else
				return 0;
		}
	}
	else
		return -1;
}


int SetShutter(int dacNum, bool value)
{
	if (!inited)
		return 0;

	uint8_t ctrlBuffer[2] = { 0x02, value };
	return dacController->SendControl(dacNum, &ctrlBuffer[0], 2);
}

int GetFirmwareVersion(int dacNum)
{
	if (!inited)
		return -1;

	uint8_t ctrlBuffer[32] = { 0x04, 0 };
	int tx = dacController->SendControl(dacNum, &ctrlBuffer[0], 2);
	if (tx != 1)
		return -1;

	tx = dacController->GetControlResponse(dacNum, &ctrlBuffer[0], 5);
	if (tx == 1)
	{
		if ((ctrlBuffer[0]) == 0x84) //if received control byte is as expected
		{
			return ((ctrlBuffer[1] << 0) |
					(ctrlBuffer[2] << 8) |
					(ctrlBuffer[3] << 16) |
					(ctrlBuffer[4] << 24));
		}
	}
	else
		return 0;
}

int EraseFirmware(int dacNum)
{
	if (!inited)
		return  -1;

	uint8_t ctrlBuffer[2] = { 0xDE, 0 };
	return dacController->SendControl(dacNum, &ctrlBuffer[0], 2);
}

int CloseDevices()
{
	if (inited)
	{
		inited = false;
		delete dacController;
		return 1;
	}
	else
		return 0;
}


//Below is OLSC implementation
//OLSC API is designed by Chris Favreau, MIT License

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

OLSC_API int __stdcall OLSC_GetAPIVersion(void)
{
	return OPEN_LASER_SHOW_DEVICE_API_VERSION;
}

OLSC_API int __stdcall OLSC_GetInterfaceName(char* pString)
{
	memcpy(pString, "Helios", 7);
	return OLSC_ERROR_SUCCESS;
}

OLSC_API int __stdcall OLSC_Initialize(void)
{
	return OpenDevices();
}

OLSC_API int __stdcall OLSC_Shutdown(void)
{
	CloseDevices();
	return OLSC_ERROR_SUCCESS;
}

OLSC_API int __stdcall OLSC_GetDeviceCount(void)
{
	if (!inited)
		return OLSC_ERROR_NONE;
	else
		return dacController->numOfDevices;
}

OLSC_API int __stdcall OLSC_GetDeviceCapabilities(int device_number, struct LASER_SHOW_DEVICE_CAPABILITIES& device_capabilities)
{
	if (!inited)
		return OLSC_ERROR_NONE;

	device_capabilities.color_resolution = 8;
	device_capabilities.xy_resolution = 12;
	device_capabilities.has_dmx_in = false;
	device_capabilities.has_dmx_out = false;
	device_capabilities.has_ttl_in = false;
	device_capabilities.has_ttl_out = false;
	device_capabilities.max_frame_size = HELIOS_MAX_POINTS;
	device_capabilities.max_speed = HELIOS_MAX_RATE;
	device_capabilities.min_frame_size = 1;
	device_capabilities.min_speed = HELIOS_MIN_RATE;
	GetName(device_number, &device_capabilities.name[0]);
	device_capabilities.uses_callbacks = false;
	device_capabilities.version_major = 1;
	device_capabilities.version_minor = 0;

	return OLSC_ERROR_SUCCESS;
}

OLSC_API int __stdcall OLSC_GetLastErrorNumber(int device_number, int& number, char* string_pointer, int string_length)
{
	//not supported yet
	return OLSC_ERROR_NONE;
}

OLSC_API int __stdcall OLSC_Play(int device_number)
{
	//not supported yet, use OLSC_WriteFrame()
	return OLSC_ERROR_NONE;
}

OLSC_API int __stdcall OLSC_Pause(int device_number)
{
	return Stop(device_number);
}

OLSC_API int __stdcall OLSC_Shutter(int device_number, int state)
{
	return SetShutter(device_number, !state); //OLSC uses 0 as ON for some reason
}

OLSC_API int __stdcall OLSC_WriteFrameEx(int device_number, int display_speed, int point_count, struct LASER_SHOW_DEVICE_POINT *points)
{
	struct LASER_SHOW_DEVICE_FRAME frame;
	frame.display_speed = display_speed;
	frame.point_count = point_count;
	frame.points = points;

	return OLSC_WriteFrame(device_number, frame);
}

OLSC_API int __stdcall OLSC_WriteFrame(int device_number, struct LASER_SHOW_DEVICE_FRAME frame)
{
	if (!inited)
		return OLSC_ERROR_FAILED;
	if ((frame.point_count > HELIOS_MAX_POINTS) || (frame.display_speed > HELIOS_MAX_RATE) || (frame.display_speed < HELIOS_MIN_RATE))
		return OLSC_ERROR_INVALID_PARAMETER;

	//prepare frame buffer, 16-bit values are explicitly split into 8-bit to avoid endianness-problems across any architecture
	uint8_t frameBuffer[HELIOS_MAX_POINTS * 7 + 5];
	int bufPos = 0;
	for (int i = 0; i < frame.point_count; i++)
	{
		frameBuffer[bufPos++] = (frame.points[i].x >> 8);
		frameBuffer[bufPos++] = (((frame.points[i].x >> 4) & 0xF) << 4) + (frame.points[i].y >> 12);
		frameBuffer[bufPos++] = ((frame.points[i].y >> 4) & 0xFF);
		frameBuffer[bufPos++] = (uint8_t)frame.points[i].r;
		frameBuffer[bufPos++] = (uint8_t)frame.points[i].g;
		frameBuffer[bufPos++] = (uint8_t)frame.points[i].b;
		frameBuffer[bufPos++] = (uint8_t)frame.points[i].i;
	}
	frameBuffer[bufPos++] = (frame.display_speed & 0xFF);
	frameBuffer[bufPos++] = (frame.display_speed >> 8);
	frameBuffer[bufPos++] = (frame.point_count & 0xFF);
	frameBuffer[bufPos++] = (frame.point_count >> 8);
	frameBuffer[bufPos++] = 0;


	//send frame to dac
	return dacController->SendFrame(device_number, &frameBuffer[0], bufPos);
}

OLSC_API int __stdcall OLSC_GetStatus(int device_number, DWORD& status)
{
	if (!inited)
		return OLSC_ERROR_NONE;

	uint8_t statusResult = GetStatus(device_number);
	if (statusResult == -1)
		return OLSC_ERROR_FAILED;

	if (statusResult == 1)
	{
		status = OLSC_STATUS_BUFFER_EMPTY;
	}
	else
		status = OLSC_STATUS_BUFFER_FULL;

	return OLSC_ERROR_SUCCESS;
}

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	OLSC_API int __stdcall OLSC_SetCallback(int device_number, HWND parent_window_handle, uint32_t message)
	{
		//not supported
		return OLSC_ERROR_NONE;
	}
#endif

OLSC_API int __stdcall OLSC_WriteDMX(int device_number, int start_address, uint8_t *data_pointer, int length)
{
	//not supported
	return OLSC_ERROR_NONE;
}

OLSC_API int __stdcall OLSC_ReadDMX(int device_number, int start_address, uint8_t *data_pointer, int length)
{
	//not supported
	return OLSC_ERROR_NONE;
}

OLSC_API int __stdcall OLSC_WriteTTL(int device_number, DWORD data)
{
	//not supported
	return OLSC_ERROR_NONE;
}

OLSC_API int __stdcall OLSC_ReadTTL(int device_number, DWORD& data)
{
	//not supported
	return OLSC_ERROR_NONE;
}

#endif
