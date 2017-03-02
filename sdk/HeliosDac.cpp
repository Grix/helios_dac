/*
Class controlling lower-level communication with Helios Laser DACs.
By Gitle Mikkelsen

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
	libusb_exit(NULL);
}


//attempts to open connection and initialize dacs
//returns number of connected devices
int HeliosDac::OpenDevices()
{
	try
	{
		CloseDevices();

		int result = libusb_init(NULL);
		if (result < 0)
			return result;

		libusb_device** devs;
		ssize_t cnt = libusb_get_device_list(NULL, &devs);
		if (cnt < 0)
			return (int)cnt;

		std::lock_guard<std::mutex> lock(threadLock);

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
		if ((!inited) || (devNum >= (int)deviceList.size()))
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
		if ((!inited) || (devNum >= (int)deviceList.size()))
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

//Gets firmware version of DAC
int HeliosDac::GetFirmwareVersion(int devNum)
{
	try
	{
		if ((!inited) || (devNum >= (int)deviceList.size()))
			return -1;

		std::unique_lock<std::mutex> lock(threadLock, std::defer_lock);
		lock.lock();
			HeliosDacDevice* dev = deviceList.at(devNum).get();
		lock.unlock();
		if (dev == NULL)
			return -1;

		return dev->GetFirmwareVersion();
	}
	catch (...)
	{
		return -1;
	}
}

//Gets name of DAC ("" if error)
char* HeliosDac::GetName(int devNum)
{
	try
	{
		if ((!inited) || (devNum >= (int)deviceList.size()))
			return "";

		std::unique_lock<std::mutex> lock(threadLock, std::defer_lock);
		lock.lock();
		HeliosDacDevice* dev = deviceList.at(devNum).get();
		lock.unlock();
		if (dev == NULL)
			return "";

		return dev->GetName();
	}
	catch (...)
	{
		return "";
	}
}

//sends a raw control signal (implemented as interrupt transfer) to a dac device
//returns 1 if successful
int HeliosDac::SendControl(int devNum, uint8_t* bufferAddress, int length)
{
	try
	{
		if ((!inited) || (devNum >= (int)deviceList.size()))
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
		if ((!inited) || (devNum >= (int)deviceList.size()))
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
		std::lock_guard<std::mutex> lock(threadLock);
		inited = false;
		deviceList.clear(); //various destructors will clean all devices

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

	threadLock = std::make_unique<std::mutex>();

	//get firmware version
	firmwareVersion = 0;
	uint8_t ctrlBuffer[32] = { 0x04, 0 };
	int tx = SendControl(&ctrlBuffer[0], 2);
	if (tx == 1)
	{
		tx = GetControlResponse(&ctrlBuffer[0], 5);
		if (tx == 1)
		{
			if ((ctrlBuffer[0]) == 0x84) //if received control byte is as expected
			{
				firmwareVersion = ((ctrlBuffer[1] << 0) |
					(ctrlBuffer[2] << 8) |
					(ctrlBuffer[3] << 16) |
					(ctrlBuffer[4] << 24));
			}
			else
				tx = 0;
		}
		else
			tx = 0;
	}

	if (tx != 1) //try new control transfer format
	{
		firmwareVersion = 5;
		uint8_t ctrlBuffer[32] = { 0x04, 0 };
		tx = SendControl(&ctrlBuffer[0], 2);
		if (tx == 1)
		{
			tx = GetControlResponse(&ctrlBuffer[0], 5);
			if (tx == 1)
			{
				if ((ctrlBuffer[0]) == 0x84) //if received control byte is as expected
				{
					firmwareVersion = ((ctrlBuffer[1] << 0) |
						(ctrlBuffer[2] << 8) |
						(ctrlBuffer[3] << 16) |
						(ctrlBuffer[4] << 24));
				}
				else
					tx = 0;
			}
			else
				tx = 0;
		}
	}

	uint8_t ctrlBuffer2[2] = { 0x07, HELIOS_SDK_VERSION };
	SendControl(&ctrlBuffer2[0], 2);

	bool gotName = false;
	uint8_t ctrlBuffer3[32] = { 0x05, 0 }; //getting name
	tx = SendControl(&ctrlBuffer[0], 2);
	if (tx == 1)
	{
		tx = GetControlResponse(&ctrlBuffer[0], 32);
		if (tx == 1)
		{
			if ((ctrlBuffer[0]) == 0x85) //if received control byte is as expected
			{
				memcpy(name, &ctrlBuffer[1], 32);
				gotName = true;
			}
		}
	}

	//if the above failed, fallback name:
	if (!gotName)
	{
		memcpy(name, "", 1);
	}

	/*if (firmwareVersion > 4)
	{
		std::thread statusHandlerThread(&HeliosDac::HeliosDacDevice::InterruptTransferHandler, this);
		statusHandlerThread.detach();
	}*/
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
			threadLock->lock();
			status = 0;
			threadLock->unlock();

			uint8_t ctrlBuffer[32] = { 0x03, 0 };
			if (firmwareVersion < 5)
				int tx = SendControl(&ctrlBuffer[0], 2);

			std::thread statusHandlerThread(&HeliosDac::HeliosDacDevice::WaitForStatus, this);
			statusHandlerThread.detach();

			return 1;
		}
		else
			return 0;
	}
	catch(...)
	{
		printf("ERROR SendFrame");
		return 0;
	}
}

//Gets firmware version of DAC
int HeliosDac::HeliosDacDevice::GetFirmwareVersion()
{
	try
	{
		if (closed)
			return -1;

		return firmwareVersion;
	}
	catch (...)
	{
		printf("ERROR GetFirmwareVersion");
		return -1;
	}
}

//Gets firmware version of DAC
char* HeliosDac::HeliosDacDevice::GetName()
{
	try
	{
		if (closed)
			return "";

		return name;
	}
	catch (...)
	{
		printf("ERROR GetName");
		return "";
	}
}

//Gets status of DAC, 1 means DAC is ready to receive frame, 0 means it's not
int HeliosDac::HeliosDacDevice::GetStatus()
{
	try
	{
		if (closed)
			return -1;

		if (firmwareVersion > 4)
		{
			threadLock->lock();
			int r = status;
			threadLock->unlock();
			return r;
		}
		else
		{
			uint8_t ctrlBuffer[32] = { 0x03, 0 };
			int tx = SendControl(&ctrlBuffer[0], 2);
			if (tx != 1)
				return -1;

			tx = GetControlResponse(&ctrlBuffer[0], 2);
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
				
			return -1;
		}
	}
	catch(...)
	{
		printf("ERROR GetSTatus");
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
		printf("ERROR SendControl");
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
		int transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &data[0], length, &actualLength, 32);

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
		printf("ERROR GetControlResponse");
		return 0;
	}
}

void HeliosDac::HeliosDacDevice::WaitForStatus()
{
	int tx;
	uint8_t ctrlBuffer[32] = { 0x03, 0 };
	if (firmwareVersion < 5)
		tx = SendControl(&ctrlBuffer[0], 2);

	int actualLength = 0;
	tx = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &ctrlBuffer[0], 2, &actualLength, 0);
	
	if (tx == LIBUSB_SUCCESS)
	{
		if ((tx == 0) && (ctrlBuffer[0] == 0x83)) //status transfer code
		{
			threadLock->lock();
			status = (ctrlBuffer[1] == 1);
			threadLock->unlock();
		}
	}
}

//void LIBUSB_CALL HeliosInterruptTransferHandlerWrapper(struct libusb_transfer* transfer)
//{
//	HeliosDac::HeliosDacDevice* instance = static_cast<HeliosDac::HeliosDacDevice*>(transfer->user_data);
//	instance->InterruptTransferHandler(transfer);
//}

//void HeliosDac::HeliosDacDevice::InterruptTransferHandler()
//{
//	try
//	{
//		/*if (transfer->status == LIBUSB_TRANSFER_COMPLETED)
//		{
//			if (transfer->buffer[0] == 0x83)
//			{
//				//threadLock->lock();
//				status = (transfer->buffer[1] == 1);
//				//threadLock->unlock();
//			}
//		}*/
//
//		//libusb_free_transfer(transfer);
//		//transfer = libusb_alloc_transfer(0);
//		//libusb_fill_interrupt_transfer(transfer, usbHandle, EP_INT_IN, interruptBuffer, 2, HeliosInterruptTransferHandlerWrapper, this, 0);
//		//libusb_submit_transfer(transfer);
//		uint8_t data[2] = { 0, 0 };
//		int actualLength = 0;
//		int transferResult = -1;
//
//		while (1)
//		{
//			transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &data[0], 2, &actualLength, 0);
//
//			if (transferResult == LIBUSB_ERROR_NO_DEVICE)
//				return;
//			else if ((transferResult == 0) && (data[0] == 0x83)) //status transfer code
//			{
//				threadLock.lock();
//				status = (data[1] == 1);
//				threadLock.unlock();
//			}
//		}	
//	}
//	catch(...)
//	{
//		printf("ERROR InterruptTransferHandler");
//		return;
//	}
//}

int HeliosDac::HeliosDacDevice::CloseDevice()
{ 
	closed = 1;
	libusb_close(usbHandle);
	return 1;
}

HeliosDac::HeliosDacDevice::~HeliosDacDevice()
{
	CloseDevice();
}