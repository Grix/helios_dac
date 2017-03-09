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
}


//attempts to open connection and initialize dacs
//returns number of connected devices
int HeliosDac::OpenDevices()
{
	if (inited)
		return deviceList.size();

	int result = libusb_init(NULL);
	if (result < 0)
		return result;

	libusb_set_debug(NULL, LIBUSB_LOG_LEVEL);

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

	if (devNum > 0)
		inited = true;

	return devNum;
}

int HeliosDac::GetDeviceCount()
{
	if (!inited)
		return 0;

	return deviceList.size();
}

//sends a raw frame buffer (implemented as bulk transfer) to a dac device
//returns 1 if transfer succeeds
int HeliosDac::SendFrame(int devNum, uint8_t* bufferAddress, int bufferSize)
{
	if ((!inited) || (devNum >= (int)deviceList.size()))
		return 0;

	std::unique_lock<std::mutex> lock(threadLock, std::defer_lock);
	lock.lock();
		HeliosDacDevice* dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return 0;

	return dev->SendFrame(bufferAddress, bufferSize);
}

//Gets status of DAC, true means DAC is ready to receive frame
int HeliosDac::GetStatus(int devNum)
{
	if ((!inited) || (devNum >= (int)deviceList.size()))
		return -1;

	std::unique_lock<std::mutex> lock(threadLock, std::defer_lock);
	lock.lock();
		HeliosDacDevice* dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return -1;

	return dev->GetStatus();
}

//Gets firmware version of DAC
int HeliosDac::GetFirmwareVersion(int devNum)
{
	if ((!inited) || (devNum >= (int)deviceList.size()))
		return -1;

	std::unique_lock<std::mutex> lock(threadLock, std::defer_lock);
	lock.lock();
		HeliosDacDevice* dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return -1;

	return dev->GetFirmwareVersion();
}

//Gets name of DAC ("" if error)
char* HeliosDac::GetName(int devNum)
{
	if ((!inited) || (devNum >= (int)deviceList.size()))
		return "";

	std::unique_lock<std::mutex> lock(threadLock, std::defer_lock);
	lock.lock();
	HeliosDacDevice* dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return "";

	return dev->GetName();
}

//sends a raw control signal (implemented as interrupt transfer) to a dac device
//returns 1 if successful
int HeliosDac::SendControl(int devNum, uint8_t* bufferAddress, int length)
{
	if ((!inited) || (devNum >= (int)deviceList.size()))
		return 0;

	std::unique_lock<std::mutex> lock(threadLock, std::defer_lock);
	lock.lock();
		HeliosDacDevice* dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return 0;

	return dev->SendControl(bufferAddress, length);
}

//Attempts to receive a response to a previous control transfer.
//Returns 1 and populates bufferAddress if successful
int HeliosDac::GetControlResponse(int devNum, uint8_t* bufferAddress)
{
	if ((!inited) || (devNum >= (int)deviceList.size()))
		return 0;

	std::unique_lock<std::mutex> lock(threadLock, std::defer_lock);
	lock.lock();
		HeliosDacDevice* dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return 0;

	return dev->GetControlResponse(bufferAddress);
}

//closes and frees all devices
//returns true if successful
int HeliosDac::CloseDevices()
{
	std::lock_guard<std::mutex> lock(threadLock);
	inited = false;
	deviceList.clear(); //various destructors will clean all devices

	libusb_exit(NULL);

	return 1;
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
	uint8_t ctrlBuffer[2] = { 0x04, 0 };

	int actualLength = 0;
	int transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_OUT, &ctrlBuffer[0], 2, &actualLength, 32);

	if ((transferResult == LIBUSB_SUCCESS) && (actualLength == 2))
	{
		uint8_t ctrlBuffer2[32];
		transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &ctrlBuffer2[0], 5, &actualLength, 32);

		if (transferResult == LIBUSB_SUCCESS)
		{
			firmwareVersion = ((ctrlBuffer2[1] << 0) |
				(ctrlBuffer2[2] << 8) |
				(ctrlBuffer2[3] << 16) |
				(ctrlBuffer2[4] << 24));
		}
	}

	//send sdk firmware version
	uint8_t ctrlBuffer3[2] = { 0x07, HELIOS_SDK_VERSION };
	transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_OUT, &ctrlBuffer3[0], 2, &actualLength, 32);

	//get device name
	bool gotName = false;
	uint8_t ctrlBuffer4[32] = { 0x05, 0 }; //getting name
	transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_OUT, &ctrlBuffer4[0], 2, &actualLength, 32);
	if ((transferResult == LIBUSB_SUCCESS) && (actualLength == 2))
	{
		uint8_t ctrlBuffer5[32];
		transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &ctrlBuffer5[0], 32, &actualLength, 32);

		if (transferResult == LIBUSB_SUCCESS)
		{
			ctrlBuffer5[31] = '\0';
			memcpy(name, &ctrlBuffer5[1], 31);
			gotName = true;
		}
	}

	//if the above failed, fallback name:
	if (!gotName)
	{
		memcpy(name, "", 1);
	}

	threadLock->lock();
	status = true;
	closed = false;
	threadLock->unlock();
}

//sends a raw frame buffer (implemented as bulk transfer) to a dac device
//returns 1 if transfer succeeds
int HeliosDac::HeliosDacDevice::SendFrame(uint8_t* bufferAddress, int bufferSize)
{
	threadLock->lock();
	if (closed)
		return 0;
	threadLock->unlock();
	if ((bufferAddress == NULL) || (bufferSize > HELIOS_MAX_POINTS * 7 + 5))
		return 0;

	int actualLength = 0;

	int transferResult = libusb_bulk_transfer(usbHandle, EP_BULK_OUT, bufferAddress, bufferSize, &actualLength, 500);

	if ((transferResult == 0) && (actualLength == bufferSize))
	{
		threadLock->lock();
		status = false;
		threadLock->unlock();

		std::thread statusHandlerThread(&HeliosDac::HeliosDacDevice::WaitForStatus, this);
		statusHandlerThread.detach();

		return 1;
	}
	else
		return 0;
}

//Gets firmware version of DAC
int HeliosDac::HeliosDacDevice::GetFirmwareVersion()
{
	threadLock->lock();
	if (closed)
		return -1;
	threadLock->unlock();

	return firmwareVersion;
}

//Gets firmware version of DAC
char* HeliosDac::HeliosDacDevice::GetName()
{
	threadLock->lock();
	if (closed)
		return "";
	threadLock->unlock();

	return name;
}

//Gets status of DAC, 1 means DAC is ready to receive frame, 0 means it's not
int HeliosDac::HeliosDacDevice::GetStatus()
{
	threadLock->lock();
	if (closed)
		return -1;
	threadLock->unlock();

	if (firmwareVersion > 4)
	{
		//uint8_t ctrlBuffer[2];
		//int tx = GetControlResponse(&ctrlBuffer[0], 2);
		//if (tx == 1)
		//{
		//	if ((ctrlBuffer[0]) == 0x83) //if received control byte is as expected
		//	{
		//		if (ctrlBuffer[1] == 1) //if dac is ready
		//			return 1;
		//		else
		//			return 0;
		//	}
		//}


		threadLock->lock();
		bool threadOpen = waitingForStatus;
		bool r = status;
		threadLock->unlock();

		if (!r && !threadOpen)
		{
			std::thread statusHandlerThread(&HeliosDac::HeliosDacDevice::WaitForStatus, this);
			statusHandlerThread.detach();
		}

		return r;
	}
	else
	{
		uint8_t ctrlBuffer[32] = { 0x03, 0 };
		int tx = SendControl(&ctrlBuffer[0], 2);
		if (tx != 1)
			return -1;

		tx = GetControlResponse(&ctrlBuffer[0]);
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

//sends a raw control signal (implemented as interrupt transfer) to a dac device
//returns 1 if successful
int HeliosDac::HeliosDacDevice::SendControl(uint8_t* bufferAddress, int length)
{

	threadLock->lock();
	if (closed)
		return 0;
	threadLock->unlock();


	if ((bufferAddress == NULL) || (length > 32) || (length <= 0))
		return 0;

	int actualLength = 0;
	int transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_OUT, bufferAddress, length, &actualLength, 32);

	if ((transferResult == 0) && (actualLength == length))
		return 1;
	else
		return transferResult;
}

//Attempts to receive a response to a previous control transfer.
//Returns 1 and populates bufferAddress if successful
int HeliosDac::HeliosDacDevice::GetControlResponse(uint8_t* bufferAddress)
{
	threadLock->lock();
	if (closed)
		return 0;
	threadLock->unlock();

	if (bufferAddress == NULL)
		return 0;

	uint8_t data[32];
	int actualLength = 0;
	int transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &data[0], 32, &actualLength, 32);

	if (transferResult < 0)
	{
		return transferResult;
	}
	else
	{
		memcpy(bufferAddress, &data[0], 32);
		return 1;
	}
}

void HeliosDac::HeliosDacDevice::WaitForStatus()
{
	threadLock->lock();
	if (closed)
		return;
	waitingForStatus = true;
	threadLock->unlock();

	if (firmwareVersion < 5)
	{
		uint8_t ctrlBuffer[32] = { 0x03, 0 };
		SendControl(&ctrlBuffer[0], 2);
	}

	uint8_t ctrlBuffer2[2];
	int actualLength = 0;
	bool ok = false;
	threadLock->lock();
	while (!ok && !closed)
	{
		threadLock->unlock();
		if (libusb_interrupt_transfer(usbHandle, EP_INT_IN, &ctrlBuffer2[0], 32, &actualLength, 32) == 0)
		{
			if (ctrlBuffer2[0] == 0x83) //status transfer code
			{
				threadLock->lock();
				status = (ctrlBuffer2[1] == 1);
				threadLock->unlock();
				ok = true;
			}
			//else
			//	WaitForStatus();
		}
		threadLock->lock();
	}
	//libusb_interrupt_transfer(usbHandle, EP_INT_IN, &ctrlBuffer[0], 2, &actualLength, 1);
	//else
	//	printf("\n%d\n",tx);

	waitingForStatus = false;
	threadLock->unlock();
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
//		//uint8_t data[2] = { 0, 0 };
//		//int actualLength = 0;
//		//int transferResult = -1;
//
//		//while (1)
//		//{
//		//	transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &data[0], 2, &actualLength, 2);
//
//		//	if (transferResult == LIBUSB_ERROR_NO_DEVICE)
//		//		return;
//		//	else if ((transferResult == 0) && (data[0] == 0x83)) //status transfer code
//		//	{
//		//		threadLock->lock();
//		//		status = (data[1] == 1);
//		//		threadLock->unlock();
//		//	}
//		//}
//	}
//	catch(...)
//	{
//		printf("ERROR InterruptTransferHandler");
//		return;
//	}
//}

int HeliosDac::HeliosDacDevice::CloseDevice()
{
	threadLock->lock();
	if (closed)
		return 0;
	closed = true;
	threadLock->unlock();
	uint8_t data;
	int length;
	//this will time out. Used to give ongoing transfers time to free themselves
	libusb_bulk_transfer(usbHandle, EP_BULK_IN, &data, 1, &length, 100);

	libusb_close(usbHandle);
	return 1;
}

HeliosDac::HeliosDacDevice::~HeliosDacDevice()
{
	CloseDevice();
}
