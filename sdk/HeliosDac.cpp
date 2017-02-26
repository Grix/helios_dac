/*
Class controlling lower-level communication with Helios Laser DACs.
By Gitle Mikkelsen, Creative Commons Attribution-NonCommercial 4.0 International Public License

See HeliosDacAPI.h or HeliosDacClass.h instead for top level functions

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
			deviceList.push_back(std::make_unique<HeliosDacDevice>(devHandle));

			uint8_t ctrlBuffer[2] = { 0x07, HELIOS_SDK_VERSION };
			SendControl(devNum, &ctrlBuffer[0], 2);

			devNum++;
		}

		libusb_free_device_list(devs, 1);
		inited = true;

		return devNum;
	}
	catch(...)
	{
		CloseDevices();
		return 0;
	}
}

int HeliosDac::GetDeviceCount()
{
	try
	{
		if (!inited)
			return 0;

		return deviceList.size();
	}
	catch(...)
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
		if ((!inited) || (devNum >= deviceList.size()))
			return 0;

		std::unique_lock<std::mutex> lock(threadLock, std::defer_lock);
		lock.lock();
			HeliosDacDevice* dev = deviceList.at(devNum).get();
		lock.unlock();
		if (dev == NULL)
			return 0;

		return dev->SendFrame(bufferAddress, bufferSize);
	}
	catch(...)
	{
		return 0;
	}
}

//Gets status of DAC, true means DAC is ready to receive frame
int HeliosDac::GetStatus(int devNum)
{
	try
	{
		if ((!inited) || (devNum >= deviceList.size()))
			return -1;

		std::unique_lock<std::mutex> lock(threadLock, std::defer_lock);
		lock.lock();
			HeliosDacDevice* dev = deviceList.at(devNum).get();
		lock.unlock();
		if (dev == NULL)
			return -1;

		return dev->GetStatus();
	}
	catch(...)
	{
		return -1;
	}
}

//sends a raw control signal (implemented as interrupt transfer) to a dac device
//returns 1 if successful
int HeliosDac::SendControl(int devNum, uint8_t* bufferAddress, int length)
{
	try
	{
		if ((!inited) || (devNum >= deviceList.size()))
			return 0;

		std::unique_lock<std::mutex> lock(threadLock, std::defer_lock);
		lock.lock();
			HeliosDacDevice* dev = deviceList.at(devNum).get();
		lock.unlock();
		if (dev == NULL)
			return 0;

		return dev->SendControl(bufferAddress, length);
	}
	catch(...)
	{
		return 0;
	}
}

//Attempts to receive a response to a previous control transfer.
//Returns 1 and populates bufferAddress if successful
int HeliosDac::GetControlResponse(int devNum, uint8_t* bufferAddress, int length)
{
	try
	{
		if ((!inited) || (devNum >= deviceList.size()))
			return 0;

		std::unique_lock<std::mutex> lock(threadLock, std::defer_lock);
		lock.lock();
			HeliosDacDevice* dev = deviceList.at(devNum).get();
		lock.unlock();
		if (dev == NULL)
			return 0;

		return dev->GetControlResponse(bufferAddress, length);
	}
	catch(...)
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
		deviceList.clear(); //various destructors will clean all devices
		libusb_exit(NULL);

		return 1;
	}
	catch(...)
	{
		return 0;
	}
}

/// -----------------------------------------------------------------------
/// HELIOSDACDEVICE START
/// -----------------------------------------------------------------------

HeliosDac::HeliosDacDevice::HeliosDacDevice(libusb_device_handle* handle)
{
	usbHandle = handle;
	std::thread statusHandlerThread(&HeliosDac::HeliosDacDevice::InterruptTransferHandler, this);
	statusHandlerThread.detach();
}

//sends a raw frame buffer (implemented as bulk transfer) to a dac device
//returns 1 if transfer succeeds
int HeliosDac::HeliosDacDevice::SendFrame(uint8_t* bufferAddress, int bufferSize)
{
	try
	{
		if ((bufferAddress == NULL) || (closed) || (bufferSize > HELIOS_MAX_POINTS * 7 + 5))
			return 0;

		int actualLength = 0;

		int transferResult = libusb_bulk_transfer(usbHandle, EP_BULK_OUT, bufferAddress, bufferSize, &actualLength, 500);

		if ((transferResult == 0) && (actualLength == bufferSize))
		{
			std::lock_guard<std::mutex> lock(threadLock);
			status = 0;
			return 1;
		}
		else
			return 0;
	}
	catch(...)
	{
		return 0;
	}
}

//Gets status of DAC, 1 means DAC is ready to receive frame, 0 means it's not
int HeliosDac::HeliosDacDevice::GetStatus()
{
	try
	{
		if (closed)
			return -1;

		std::lock_guard<std::mutex> lock(threadLock);
		return status;
	}
	catch(...)
	{
		return -1;
	}
}

//sends a raw control signal (implemented as interrupt transfer) to a dac device
//returns 1 if successful
int HeliosDac::HeliosDacDevice::SendControl(uint8_t* bufferAddress, int length)
{
	try
	{
		if ((bufferAddress == NULL) || (closed) || (length > 32) || (length <= 0))
			return 0;

		int actualLength = 0;
		int transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_OUT, bufferAddress, length, &actualLength, 32);

		if ((transferResult == 0) && (actualLength == length))
			return 1;
		else
			return transferResult;
	}
	catch(...)
	{
		return 0;
	}
}

//Attempts to receive a response to a previous control transfer.
//Returns 1 and populates bufferAddress if successful
int HeliosDac::HeliosDacDevice::GetControlResponse(uint8_t* bufferAddress, int length)
{
	try
	{
		if ((bufferAddress == NULL) || (closed) || (length > 32) || (length <= 0))
			return 0;

		uint8_t data[32];
		int actualLength = 0;
		int transferResult = libusb_bulk_transfer(usbHandle, EP_BULK_IN, &data[0], length, &actualLength, 32);

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
	catch(...)
	{
		return 0;
	}
}

void HeliosDac::HeliosDacDevice::InterruptTransferHandler()
{
	try
	{
		uint8_t data[2];
		int actualLength;
		int transferResult;
		std::unique_lock<std::mutex> lock(threadLock, std::defer_lock);

		while (!closed)
		{
			//try three times to check for incoming status transfers
			transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &data[0], 2, &actualLength, 2);
			if (transferResult < 0)
			{
				transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &data[0], 2, &actualLength, 5);
				if (transferResult < 0)
				{
					transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &data[0], 2, &actualLength, 20);
				}
			}

			if ((transferResult == 0) && (data[0] == 0x83)) //status transfer code
			{
				lock.lock();
					status = (data[1] == 1);
				lock.unlock();
			}
		}	
	}
	catch(...)
	{
		if (!closed) InterruptTransferHandler();
		return;
	}
}

int HeliosDac::HeliosDacDevice::CloseDevice()
{
	closed = true;
	libusb_close(usbHandle);
	return 1;
}

HeliosDac::HeliosDacDevice::~HeliosDacDevice()
{
	CloseDevice();
}