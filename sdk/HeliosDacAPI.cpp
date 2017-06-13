/*
Helios Laser DAC SDK shared library
By Gitle Mikkelsen

See HeliosDacAPI.h for documentation

Dependencies:
Libusb 1.0 (GNU Lesser General Public License, see libusb.h)
HeliosDAC class
OpenLaserShowControllerV1.0.0 header and .def file (only on windows)

git repo: https://github.com/Grix/helios_dac.git
*/

#include "HeliosDacAPI.h"

int OpenDevices()
{
	if (inited)
		return dacController->OpenDevices();

	dacController = new HeliosDac();

	int result = dacController->OpenDevices();

	if (result <= 0)
		delete dacController;
	else
		inited = true;

	return result;
}

int WriteFrame(unsigned int dacNum, int pps, std::uint8_t flags, HeliosPoint* points, int numOfPoints)
{
	if (!inited)
		return HELIOS_ERROR;

	return dacController->WriteFrame(dacNum, pps, flags, points, numOfPoints);
}

int Stop(unsigned int dacNum)
{
	if (!inited)
		return HELIOS_ERROR;

	return dacController->Stop(dacNum);
}

int GetName(unsigned int dacNum, char* name)
{
	if (!inited)
		return  HELIOS_ERROR;

	return dacController->GetName(dacNum, name);
}

int SetName(unsigned int dacNum, char* name)
{
	if (!inited)
		return  HELIOS_ERROR;

	return dacController->SetName(dacNum, name);
}

int GetStatus(unsigned int dacNum)
{
	if (!inited)
		return HELIOS_ERROR;

	return (int)dacController->GetStatus(dacNum);
}

int SetShutter(unsigned int dacNum, bool value)
{
	if (!inited)
		return HELIOS_ERROR;

	return dacController->SetShutter(dacNum, value);
}

int GetFirmwareVersion(unsigned int dacNum)
{
	if (!inited)
		return HELIOS_ERROR;

	return dacController->GetFirmwareVersion(dacNum);
}

int EraseFirmware(unsigned int dacNum)
{
	if (!inited)
		return  HELIOS_ERROR;

	return dacController->EraseFirmware(dacNum);
}

int CloseDevices()
{
	if (inited)
	{
		inited = false;
		delete dacController;
		return HELIOS_SUCCESS;
	}
	else
		return HELIOS_ERROR;
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
		return dacController->OpenDevices();
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
	return SetShutter(device_number, (state == 1));
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

	//convert frame structure
	HeliosPoint frameBuffer[HELIOS_MAX_POINTS * 7 + 5];
	for (int i = 0; i < frame.point_count; i++)
	{
		frameBuffer[i].x = (frame.points[i].x >> 4);
		frameBuffer[i].y = (frame.points[i].y >> 4);
		frameBuffer[i].r = (std::uint8_t)frame.points[i].r;
		frameBuffer[i].g = (std::uint8_t)frame.points[i].g;
		frameBuffer[i].b = (std::uint8_t)frame.points[i].b;
		frameBuffer[i].i = (std::uint8_t)frame.points[i].i;
	}

	//send frame to dac
	return dacController->WriteFrame(device_number, frame.display_speed, HELIOS_FLAGS_DEFAULT, frameBuffer, frame.point_count);
}

OLSC_API int __stdcall OLSC_GetStatus(int device_number, DWORD& status)
{
	if (!inited)
		return OLSC_ERROR_NONE;

	std::uint8_t statusResult = GetStatus(device_number);
	if (statusResult == HELIOS_ERROR)
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

OLSC_API int __stdcall OLSC_WriteDMX(int device_number, int start_address, std::uint8_t *data_pointer, int length)
{
	//not supported
	return OLSC_ERROR_NONE;
}

OLSC_API int __stdcall OLSC_ReadDMX(int device_number, int start_address, std::uint8_t *data_pointer, int length)
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
