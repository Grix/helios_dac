/*
Class controlling lower-level communication with Helios Laser DACs.
By Gitle Mikkelsen, Creative Commons Attribution-NonCommercial 4.0 International Public License

See HeliosDacAPI.h instead for top level functions

Dependencies: Libusb 1.0 (GNU Lesser General Public License, see libusb.h)

git repo: https://github.com/Grix/helios_dac.git
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
	try
	{
		CloseDevices();

		deviceList.clear();

		int result = libusb_init(NULL);
		if (result < 0)
			return result;

		libusb_device** devs;
		ssize_t cnt = libusb_get_device_list(NULL, &devs);
		if (cnt < 0)
			return (int)cnt;

		inited = true;

		int devNum = 0;
		for (int i = 0; i < cnt; i++)
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
			std::lock_guard<std::mutex> lock(threadLock.at(devNum));
			status[devNum] = true;
			deviceList[devNum] = devHandle;

			std::thread statusHandlerThread(&HeliosDac::InterruptTransferHandler, this, devNum);
			statusHandlerThread.detach();

			devNum++;
		}

		libusb_free_device_list(devs, 1);

		numOfDevices = devNum;

		return devNum;
	}
	catch (std::exception e)
	{
		return 0;
	}
}

//sends a raw frame buffer (implemented as bulk transfer) to a dac device
//returns 1 if transfer succeeds
int HeliosDac::SendFrame(int devNum, uint8_t* bufferAddress, int bufferSize)
{
	try
	{
		if ((bufferAddress == NULL) || (!inited) || (devNum >= numOfDevices) || (bufferSize > HELIOS_MAX_POINTS * 7 + 5))
			return 0;

		int actualLength = 0;

		int transferResult = libusb_bulk_transfer(deviceList.at(devNum), EP_BULK_OUT, bufferAddress, bufferSize, &actualLength, 500);

		if ((transferResult == 0) && (actualLength == bufferSize))
		{
			std::lock_guard<std::mutex> lock(threadLock.at(devNum));
			status[devNum] = false;
			return 1;
		}
		else
			return 0;
	}
	catch (std::exception e)
	{
		return 0;
	}
}

//Gets status of DAC, true means DAC is ready to receive frame
bool HeliosDac::GetStatus(int devNum)
{
	try
	{
		if (!inited)
			return false;

		std::lock_guard<std::mutex> lock(threadLock.at(devNum));
		return status.at(devNum);
	}
	catch (std::exception e)
	{
		return false;
	}
}

//sends a raw control signal (implemented as interrupt transfer) to a dac device
//returns 1 if successful
int HeliosDac::SendControl(int devNum, uint8_t* bufferAddress, int length)
{
	try
	{
		if ((bufferAddress == NULL) || (!inited) || (devNum >= numOfDevices) || (length > 32) || (length <= 0))
			return 0;

		int actualLength = 0;
		int transferResult = libusb_interrupt_transfer(deviceList.at(devNum), EP_INT_OUT, bufferAddress, length, &actualLength, 32);

		if ((transferResult == 0) && (actualLength == length))
			return 1;
		else
			return transferResult;
	}
	catch (std::exception e)
	{
		return 0;
	}
}

//Attempts to receive a response to a previous control transfer.
//Returns 1 if successful, and populates bufferAddress on success
int HeliosDac::GetControlResponse(int devNum, uint8_t* bufferAddress, int length)
{
	try
	{
		if ((bufferAddress == NULL) || (!inited) || (devNum >= numOfDevices) || (length > 32) || (length <= 0))
			return 0;

		uint8_t data[32];
		int actualLength = 0;
		int transferResult = libusb_bulk_transfer(deviceList.at(devNum), EP_BULK_IN, &data[0], length, &actualLength, 32);

		if (transferResult < 0)
		{
			return transferResult;
		}
		else
		{
			memcpy(bufferAddress, &data[0], length);
			return 1;
		}
	}
	catch (std::exception e)
	{
		return 0;
	}
}

//closes and frees all devices
//returns true if successful
int HeliosDac::CloseDevices()
{
	try
	{
		if (!inited)
			return 0;

		inited = false;

		for (int i = 0; i < numOfDevices; i++)
		{
			libusb_close(deviceList.at(i));
		}

		libusb_exit(NULL);
		numOfDevices = 0;

		return 1;
	}
	catch (std::exception e)
	{
		return 0;
	}
}

//buffers interrupt usb transfers (status)
void HeliosDac::InterruptTransferHandler(int devNum)
{
	//todo mutex to protect stuff
	try 
	{
		if ((inited) && (devNum < numOfDevices)) 
		{
			uint8_t data[2];
			int actualLength;

			int transferResult = libusb_interrupt_transfer(deviceList.at(devNum), EP_INT_IN, &data[0], 2, &actualLength, 2);
			if (transferResult < 0)
			{
				transferResult = libusb_interrupt_transfer(deviceList.at(devNum), EP_INT_IN, &data[0], 2, &actualLength, 5);
				if (transferResult < 0)
				{
					transferResult = libusb_interrupt_transfer(deviceList.at(devNum), EP_INT_IN, &data[0], 2, &actualLength, 20);
				}
			}

			if ((data[0]) == 0x83) //status transfer code
			{
				std::lock_guard<std::mutex> lock(threadLock.at(devNum));
				status[devNum] = (data[1] == 1);
			}
			InterruptTransferHandler(devNum);
		}
	}
	catch (std::exception e)
	{
		InterruptTransferHandler(devNum);
		return;
	}
}