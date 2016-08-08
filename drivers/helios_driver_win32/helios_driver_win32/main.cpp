/*
Driver API for Helios Laser DACs
By Gitle Mikkelsen, Creative Commons Attribution-NonCommercial 4.0 International Public License

Dependencies: 
Libusb 1.0 (GNU Lesser General Public License, see libusb.h)
HeliosDAC class (part of this driver)
*/

#include "main.h"


int OpenDevices()
{
	CloseDevices();

	dacController = new HeliosDac();

	int result = dacController->OpenDevices();

	if (result <= 0)
		delete dacController;
	else
	{
		inited = true;

		/*frameMutex = new std::mutex*[dacController->numOfDevices * 2];
		for (int i = 0; i < dacController->numOfDevices*2; i++)
			frameMutex[i] = new std::mutex;*/
	}

	return result;
}


int WriteFrame(int dacNum, int pps, uint8_t flags, HeliosPoint* points, int numOfPoints)
{
	if ((!inited) || (points == NULL))
		return 0;
	if ((numOfPoints > HELIOS_MAX_POINTS) || (pps > HELIOS_MAX_RATE))
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
	return dacController->SendControl(dacNum, &ctrlBuffer[0], false);
}


int GetName(int dacNum, char* name)
{
	if (!inited)
		return 0;

	//todo: something better than this horseshit
	name[0] = 'H';
	name[1] = 'e';
	name[2] = 'l';
	name[3] = 'i';
	name[4] = 'o';
	name[5] = 's';
	name[6] = ' ';
	name[7] = (char)((int)(dacNum >= 10) + 48);
	name[8] = (char)((int)(dacNum % 10) + 48);
	name[9] = '\0';

	return 1;
}


int GetStatus(int dacNum)
{
	if (!inited)
		return -1;

	uint8_t ctrlBuffer[2] = { 0x03, 0 };
	uint16_t result = dacController->SendControl(dacNum, &ctrlBuffer[0], true);

	if ((result >> 8) == 0x83) //if received control byte is as expected
	{
		if (result & 1) //if dac is ready
			return 1;
		else
			return 0;
	}
	else
		return -1;
}


int SetShutter(int dacNum, bool value)
{
	if (!inited)
		return 0;

	uint8_t ctrlBuffer[2] = { 0x02, value };
	return dacController->SendControl(dacNum, &ctrlBuffer[0], false);
}


int CloseDevices()
{
	if (inited)
	{
		inited = false;
		//for (int i = 0; i < dacController->numOfDevices * 2; i++)
		//	delete frameMutex[i];
		//delete frameMutex;
		delete dacController;
		return 1;
	}
	else
		return 0;
}


//Below is OLSC implementation only
//OLSC API is designed by Chris Favreau, MIT License

int WINAPI OLSC_GetAPIVersion(void)
{
	return OLSC_VERSION;
}

int WINAPI OLSC_GetInterfaceName(char* pString)
{
	pString = "Helios";
	return 1;
}

int WINAPI OLSC_Initialize(void)
{
	return OpenDevices();
}

int WINAPI OLSC_Shutdown(void)
{
	CloseDevices();
	return 1;
}

int WINAPI OLSC_GetDeviceCount(void)
{
	if (!inited)
		return 0;
	else
		return dacController->numOfDevices;
}

int WINAPI OLSC_GetDeviceCapabilities(int device_number, OLSC_DeviceCapabilites& device_capabilities)
{
	if (!inited)
		return 0;

	device_capabilities.color_resolution = 8;
	device_capabilities.xy_resolution = 12;
	device_capabilities.has_dmx_in = false;
	device_capabilities.has_dmx_out = false;
	device_capabilities.has_ttl_in = false;
	device_capabilities.has_ttl_out = false;
	device_capabilities.max_frame_size = HELIOS_MAX_POINTS;
	device_capabilities.max_speed = HELIOS_MAX_RATE;
	device_capabilities.min_frame_size = 1;
	device_capabilities.min_speed = 6;
	GetName(device_number, device_capabilities.name);
	device_capabilities.uses_callbacks = false;
	device_capabilities.version_major = 1;
	device_capabilities.version_minor = 0;

	return 1;
}

int WINAPI OLSC_GetLastErrorNumber(int device_number, int& number, char* string_pointer, int string_length)
{
	//not supported yet
	return 0;
}

int WINAPI OLSC_Play(int device_number)
{
	//not supported yet, use WriteFrame
	return 0;
}

int WINAPI OLSC_Pause(int device_number)
{
	return Stop(device_number);
}

int WINAPI OLSC_Shutter(int device_number, int state)
{
	return SetShutter(device_number, !state); //OLSC uses 0 as ON for some reason
}

int WINAPI OLSC_WriteFrame(int device_number, OLSC_Frame frame)
{
	if (!inited)
		return 0;
	if ((frame.point_count > HELIOS_MAX_POINTS) || (frame.display_speed > HELIOS_MAX_RATE))
		return 0;

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
	frameBuffer[bufPos++] = (frame.display_speed >> 8);
	frameBuffer[bufPos++] = (frame.display_speed & 0xFF);
	frameBuffer[bufPos++] = (frame.point_count >> 8);
	frameBuffer[bufPos++] = (frame.point_count & 0xFF);
	frameBuffer[bufPos++] = 0;

	//send frame to dac
	return dacController->SendFrame(device_number, &frameBuffer[0], bufPos);
}

int WINAPI OLSC_GetStatus(int device_number, DWORD& status)
{
	if (!inited)
		return 0;

	uint8_t statusResult = GetStatus(device_number);
	if ((statusResult & (1 << 7)) == 0)
		return 0;

	if (statusResult & 1)
		status |= 2;
	else
		status |= 1;

	return 1;
}

int WINAPI OLSC_WriteDMX(int device_number, int start_address, unsigned char *data_pointer, int length)
{
	//not supported
	return 0;
}

int WINAPI OLSC_ReadDMX(int device_number, int start_address, unsigned char *data_pointer, int length)
{
	//not supported
	return 0;
}

int WINAPI OLSC_WriteTTL(int device_number, DWORD data)
{
	//not supported
	return 0;
}

int WINAPI OLSC_ReadTTL(int device_number, DWORD& data)
{
	//not supported
	return 0;
}
