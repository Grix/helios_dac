/*
Class controlling lower-level communication with Helios Laser DACs.
By Gitle Mikkelsen, Creative Commons Attribution-NonCommercial 4.0 International Public License

Dependencies: Libusb 1.0 (GNU Lesser General Public License, see libusb.h)
*/

#include "HeliosDac.h"


HeliosDac::HeliosDac()
{
	inited = false;
}

HeliosDac::~HeliosDac()
{
	CloseDevices();
}


//attempts to open connection and initialize dacs
//returns number of connected devices
int HeliosDac::OpenDevices()
{
	CloseDevices();

	for (int i = 0; i < HELIOS_MAX_DEVICES; i++)
		deviceList[i] = NULL;

	int result = libusb_init(NULL);
	if (result < 0)
		return result;

	libusb_device** devs;
	ssize_t cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0)
		return (int)cnt;

	int devNum = 0;
	for (int i = 0; ((i < cnt) && (devNum < HELIOS_MAX_DEVICES)); i++)
	{
		struct libusb_device_descriptor devDesc;
		int result = libusb_get_device_descriptor(devs[i], &devDesc);
		if (result < 0)
			continue;

		if ((devDesc.idProduct != HELIOS_PID) || (devDesc.idVendor != HELIOS_VID))
			continue;

		libusb_device_handle* devHandle;
		result = libusb_open(devs[i], &devHandle);
		if (result < 0)
			continue;

		result = libusb_claim_interface(devHandle, 0);
		if (result < 0)
			continue;

		result = libusb_set_interface_alt_setting(devHandle, 0, 1);
		if (result < 0)
			continue;

		//successfully opened, add to device list
		deviceList[devNum++] = devHandle;
	}

	libusb_free_device_list(devs, 1);

	numOfDevices = devNum;
	inited = true;

	return devNum;
}

//sends a raw frame buffer (implemented as bulk transfer) to a dac device
//returns true if transfer succeeds
int HeliosDac::SendFrame(int devNum, uint8_t* bufferAddress, int bufferSize)
{
	if ((bufferAddress == NULL) || (!inited) || (devNum > numOfDevices) || (bufferSize > HELIOS_MAX_POINTS * 7 + 5))
		return 0;

	int actualLength = 0;

	int transferResult = libusb_bulk_transfer(deviceList[devNum], EP_BULK_OUT, bufferAddress, bufferSize, &actualLength, 500);

	return ((transferResult == 0) && (actualLength == bufferSize));
}

//sends a raw control signal (implemented as interrupt transfer) to a dac device
//returns 1 if successful, unless getResponse is true in which case it
//waits for a response (incoming interrupt transfer) and returns its content
uint16_t HeliosDac::SendControl(int devNum, uint8_t* bufferAddress, bool getResponse)
{
	if ((bufferAddress == NULL) || (!inited) || (devNum >= numOfDevices))
		return 0;

	int actualLength = 0;
	int transferResult = libusb_interrupt_transfer(deviceList[devNum], EP_INT_OUT, bufferAddress, 2, &actualLength, 32);

	if (getResponse)
	{
		if ((transferResult < 0) || (actualLength != 2))
			return 0;

		uint8_t data[2] = { 0, 0 }; 
		actualLength = 0;
		transferResult = libusb_interrupt_transfer(deviceList[devNum], EP_INT_IN, &data[0], 2, &actualLength, 64);

		if ((transferResult < 0) || (actualLength != 2))
			return 0;
		else
			return (uint16_t)((data[0] << 8) | data[1]);
	}
	else
	{
		if ((transferResult == 0) && (actualLength == 2))
			return 1;
		else
			return 0;
	}
}

//closes and frees all devices
//returns true if successful
int HeliosDac::CloseDevices()
{
	if (!inited)
		return 0;

	for (int i = 0; i < numOfDevices; i++)
	{
		libusb_close(deviceList[i]);
	}

	libusb_exit(NULL);
	inited = false;
	numOfDevices = 0;

	return 1;
}
