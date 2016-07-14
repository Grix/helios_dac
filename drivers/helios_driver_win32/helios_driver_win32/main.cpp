/*
Driver API for Helios Laser DACs
By Gitle Mikkelsen, Creative Commons Attribution-NonCommercial 4.0 International Public License

Dependencies: 
Libusb 1.0 (GNU Lesser General Public License, see libusb.h)
HeliosDAC class (part of this driver)
*/

#include "main.h"


//initializes drivers, opens connection to all devices. 
//Returns number of available devices.
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
		frameBuffer = new uint8_t[dacController->maxPoints * 7 + 5];
	}

	return result;
}


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
int WriteFrame(int dacNum, int pps, uint8_t flags, HeliosPoint* points, int numOfPoints)
{
	if ((!inited) || (points == NULL))
		return 0;
	if ((numOfPoints > dacController->maxPoints) || (pps > dacController->maxRate))
		return 0;

	//prepare frame buffer
	int bufPos = 0;
	for (int i = 0; i < numOfPoints; i++)
	{
		frameBuffer[bufPos++] = (points[i].x >> 4);
		frameBuffer[bufPos++] = ((points[i].x & 0xF) << 4) + (points[i].y >> 8);
		frameBuffer[bufPos++] = (points[i].y & 0xFF);
		frameBuffer[bufPos++] = points[i].r;
		frameBuffer[bufPos++] = points[i].g;
		frameBuffer[bufPos++] = points[i].b;
		frameBuffer[bufPos++] = points[i].i;
	}
	frameBuffer[bufPos++] = (pps >> 8);
	frameBuffer[bufPos++] = (pps & 0xFF);
	frameBuffer[bufPos++] = (numOfPoints >> 8);
	frameBuffer[bufPos++] = (numOfPoints & 0xFF);
	frameBuffer[bufPos++] = flags;

	//send frame to dac
	return dacController->SendFrame(dacNum, frameBuffer, numOfPoints * 7 + 5);
}


//stops, blanks and centers output on the specified dac
//returns 1 if successful
int Stop(int dacNum)
{
	if (!inited)
		return 0;

	uint8_t ctrlBuffer[2] = { 0x01, 0 };
	return dacController->SendControl(dacNum, &ctrlBuffer[0], false);
}

//gets a descriptive name of the specified dac
//name is max 32 bytes long
//returns 1 if successful
int GetName(int dacNum, char* name)
{
	//todo get an actual unique name from the DAC itself
	if (!inited)
		return 0;

	name = "Helios ";
	name[7] = (char)((int)(dacNum >= 10) + 48);
	name[8] = (char)((int)(dacNum % 10) + 48);
	name[9] = '\0';

	return 1;
}


//Gets status from the specified dac. 
//Byte 0 (LSB): True if DAC is ready to receive new frame, false otherwise
//Byte 1-6: reserved
//Byte 7 (MSB): True if function succeeded, false if status could not be retrived
uint8_t GetStatus(int dacNum)
{
	if (!inited)
		return 0;

	uint8_t ctrlBuffer[2] = { 0x03, 0 };
	uint16_t result = dacController->SendControl(dacNum, &ctrlBuffer[0], true);

	uint8_t returnVal = 0;

	if ((result >> 8) == 0x83) //if received control byte is as expected
	{
		returnVal |= (1 << 7); //set function success bit
		if (result & 1) //if dac is ready
			returnVal |= 1; //set ready bit
	}
	return returnVal;
}

//sets the shutter of the specified dac. 
//value 1 = shutter on, value 0 = shutter off
//returns 1 if successful
int SetShutter(int dacNum, bool value)
{
	if (!inited)
		return 0;

	uint8_t ctrlBuffer[2] = { 0x02, value };
	return dacController->SendControl(dacNum, &ctrlBuffer[0], false);
}


//closes connection to all dacs and frees resources
int CloseDevices()
{
	if (inited)
	{
		delete dacController;
		delete frameBuffer;
		inited = false;
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
	device_capabilities.max_frame_size = dacController->maxPoints;
	device_capabilities.max_speed = dacController->maxRate;
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
	if ((frame.point_count > dacController->maxPoints) || (frame.display_speed > dacController->maxRate))
		return 0;

	//prepare frame buffer
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
	return dacController->SendFrame(device_number, frameBuffer, frame.point_count * 7 + 5);
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
