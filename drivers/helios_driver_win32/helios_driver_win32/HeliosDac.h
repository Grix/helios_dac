#pragma once

#include <stdint.h>
#include "libusb.h"

#define HELIOS_MAX_DEVICES	16
#define HELIOS_MAX_POINTS	3000
#define HELIOS_MAX_RATE		0xFFFF

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
	uint16_t SendControl(int devNum, uint8_t* bufferAddress, bool getResponse);
	int SendFrame(int devNum, uint8_t* bufferAddress, int bufferSize);

	int numOfDevices = 0;
	const int maxPoints = HELIOS_MAX_POINTS;
	const int maxRate = HELIOS_MAX_RATE;

private:

	struct libusb_device_handle* deviceList[HELIOS_MAX_DEVICES];
	bool inited = false;
};

