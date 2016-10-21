/*
Class controlling lower-level communication with Helios Laser DACs.
By Gitle Mikkelsen, Creative Commons Attribution-NonCommercial 4.0 International Public License

Dependencies: Libusb 1.0 (GNU Lesser General Public License, see libusb.h)

See HeliosDac.cpp for function documentation
*/

#pragma once

#include <stdint.h>
#include "libusb.h"

#define HELIOS_MAX_DEVICES	16
#define HELIOS_MAX_POINTS	0x1000
#define HELIOS_MAX_RATE		0xFFFF
#define HELIOS_MIN_RATE		7

//usb properties
#define HELIOS_VID	0x1209
#define HELIOS_PID	0xE500
#define EP_BULK_OUT	0x02
#define EP_BULK_IN	0x81
#define EP_INT_OUT	0x06
#define EP_INT_IN	0x83

class HeliosDac
{
public:

	HeliosDac();
	~HeliosDac();
	int OpenDevices();
	int CloseDevices();
	int SendControl(int devNum, uint8_t* bufferAddress, int length);
	int GetControlResponse(int devNum, uint8_t* bufferAddress, int length);
	int SendFrame(int devNum, uint8_t* bufferAddress, int bufferSize);

	int numOfDevices = 0;

private:

	struct libusb_device_handle* deviceList[HELIOS_MAX_DEVICES];
	bool inited = false;
};

