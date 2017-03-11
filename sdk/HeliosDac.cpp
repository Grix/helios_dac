/*
Class controlling lower-level communication with Helios Laser DACs.
By Gitle Mikkelsen

See HeliosDacAPI.h or HeliosDacClass.h instead for top level functions

Dependencies: Libusb 1.0 (GNU Lesser General Public License, see libusb.h)
Standard: C++14

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

	unsigned int devNum = 0;
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
int HeliosDac::SendFrame(unsigned int devNum, int pps, std::uint8_t flags, HeliosPoint* points, int numOfPoints)
{
	if (!inited)
		return 0;

	if ((points == NULL) || (numOfPoints > HELIOS_MAX_POINTS) || (pps > HELIOS_MAX_RATE) || (pps < HELIOS_MIN_RATE))
		return 0;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL; 
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();

	if (dev == NULL)
		return 0;

	//prepare frame buffer
	std::uint8_t frameBuffer[HELIOS_MAX_POINTS * 7 + 5];
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

	return dev->SendFrame(frameBuffer, bufPos);
}

//Gets status of DAC, true means DAC is ready to receive frame
int HeliosDac::GetStatus(unsigned int  devNum)
{
	if (!inited)
		return -1;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return -1;

	return dev->GetStatus();
}

//Gets firmware version of DAC
int HeliosDac::GetFirmwareVersion(unsigned int  devNum)
{
	if (!inited)
		return -1;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return -1;

	return dev->GetFirmwareVersion();
}

//Gets name of DAC ("" if error)
char* HeliosDac::GetName(unsigned int devNum)
{
	if (!inited)
		return "";

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return "";

	return dev->GetName();
}

//Sets name of DAC
int HeliosDac::SetName(unsigned int devNum, char* name)
{
	if (!inited)
		return HELIOS_ERROR;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return HELIOS_ERROR;

	return dev->SetName(name);
}

//Stops output of DAC
int HeliosDac::Stop(unsigned int devNum)
{
	if (!inited)
		return HELIOS_ERROR;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return HELIOS_ERROR;

	return dev->Stop();
}

//Sets shutter level of DAC
int HeliosDac::SetShutter(unsigned int devNum, bool level)
{
	if (!inited)
		return HELIOS_ERROR;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return HELIOS_ERROR;

	return dev->SetShutter(level);
}

//Erase the firmware of the DAC, allowing it to be updated
int HeliosDac::EraseFirmware(unsigned int devNum)
{
	if (!inited)
		return HELIOS_ERROR;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return HELIOS_ERROR;

	return dev->EraseFirmware();
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
	closed = true;
	usbHandle = handle;
	std::lock_guard<std::mutex>lock(frameLock);

	//get firmware version
	firmwareVersion = 0;
	std::uint8_t ctrlBuffer[2] = { 0x04, 0 };

	int actualLength = 0;
	int transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_OUT, &ctrlBuffer[0], 2, &actualLength, 32);

	if ((transferResult == LIBUSB_SUCCESS) && (actualLength == 2))
	{
		std::uint8_t ctrlBuffer2[32];
		transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &ctrlBuffer2[0], 5, &actualLength, 32);

		if (transferResult == LIBUSB_SUCCESS)
		{
			//todo check for id
			firmwareVersion = ((ctrlBuffer2[1] << 0) |
				(ctrlBuffer2[2] << 8) |
				(ctrlBuffer2[3] << 16) |
				(ctrlBuffer2[4] << 24));
		}
	}

	//send sdk firmware version
	std::uint8_t ctrlBuffer3[2] = { 0x07, HELIOS_SDK_VERSION };
	transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_OUT, &ctrlBuffer3[0], 2, &actualLength, 32);

	//get device name
	bool gotName = false;
	std::uint8_t ctrlBuffer4[32] = { 0x05, 0 }; //getting name
	transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_OUT, &ctrlBuffer4[0], 2, &actualLength, 32);

	if ((transferResult == LIBUSB_SUCCESS) && (actualLength == 2))
	{
		std::uint8_t ctrlBuffer5[32];
		transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &ctrlBuffer5[0], 32, &actualLength, 32);

		if (transferResult == LIBUSB_SUCCESS)
		{
			//todo check for id
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

	closed = false;
}

//sends a raw frame buffer (implemented as bulk transfer) to a dac device
//returns 1 if success
int HeliosDac::HeliosDacDevice::SendFrame(std::uint8_t* bufferAddress, int bufferSize)
{
	if (closed)
		return HELIOS_ERROR;

	if (GetStatus() == 1)
	{
		std::thread statusHandlerThread(&HeliosDac::HeliosDacDevice::DoFrame, this, bufferAddress, bufferSize);
		statusHandlerThread.detach();
		return HELIOS_SUCCESS;
	}
	else
		return HELIOS_ERROR;
}

void HeliosDac::HeliosDacDevice::DoFrame(std::uint8_t* buffer, int bufferSize)
{
	std::lock_guard<std::mutex> lock(frameLock);
	int actualLength = 0;
	int transferResult = libusb_bulk_transfer(usbHandle, EP_BULK_OUT, buffer, bufferSize, &actualLength, 256);

	bool quit = false;

	while (!quit && !closed)
	{
		if ((transferResult == LIBUSB_SUCCESS) && (actualLength == bufferSize))
		{
			std::uint8_t ctrlBuffer[32] = { 0x03, 0 };
			if (SendControl(&ctrlBuffer[0], 2))
			{
				std::uint8_t ctrlBuffer2[32];
				transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &ctrlBuffer2[0], 32, &actualLength, 32);
				if (transferResult == LIBUSB_SUCCESS)
				{
					if (ctrlBuffer2[0] == 0x83) //STATUS
					{
						if (ctrlBuffer2[1] == 1)
						{
							quit = true; //lock will be freed on returning, effectively setting status to 1
						}
					}
				}
			}
		}
	}
}

//Gets firmware version of DAC
int HeliosDac::HeliosDacDevice::GetFirmwareVersion()
{
	if (closed)
		return HELIOS_ERROR;

	return firmwareVersion;
}

//Gets firmware version of DAC
char* HeliosDac::HeliosDacDevice::GetName()
{
	if (closed)
		return "";

	return name;
}

//Gets status of DAC, 1 means DAC is ready to receive frame, 0 means it's not
int HeliosDac::HeliosDacDevice::GetStatus()
{
	if (closed)
		return HELIOS_ERROR;

	std::unique_lock<std::mutex> lock(frameLock, std::try_to_lock);
	return lock.owns_lock();
	//while (closed); //wait until init is done

	///*if (firmwareVersion > 4)
	//{*/
	//	//std::uint8_t ctrlBuffer[2];
	//	//int tx = GetControlResponse(&ctrlBuffer[0], 2);
	//	//if (tx == 1)
	//	//{
	//	//	if ((ctrlBuffer[0]) == 0x83) //if received control byte is as expected
	//	//	{
	//	//		if (ctrlBuffer[1] == 1) //if dac is ready
	//	//			return 1;
	//	//		else
	//	//			return 0;
	//	//	}
	//	//}


	//	threadLock->lock();
	//	bool threadOpen = waitingForStatus;
	//	bool r = status;
	//	threadLock->unlock();

	//	if (!r && !threadOpen)
	//	{
	//		std::uint8_t ctrlBuffer[32] = { 0x03, 0 };
	//		int tx = SendControl(&ctrlBuffer[0], 2);

	//		threadLock->lock();
	//		waitingForStatus = true;
	//		threadLock->unlock();

	//		std::thread statusHandlerThread(&HeliosDac::HeliosDacDevice::InterruptTransferHandler, this);
	//		statusHandlerThread.detach();
	//	}

	//	return r;
	//}
	//else
	//{
	//	std::uint8_t ctrlBuffer[32] = { 0x03, 0 };
	//	/*int tx = SendControl(&ctrlBuffer[0], 2);
	//	if (tx != 1)
	//		return -1;*/

	//	int tx = GetControlResponse(&ctrlBuffer[0]);
	//	if (tx == 1)
	//	{
	//		if ((ctrlBuffer[0]) == 0x83) //if received control byte is as expected
	//		{
	//			if (ctrlBuffer[1] == 1) //if dac is ready
	//				return 1;
	//			else
	//				return 0;
	//		}
	//	}

	//	return -1;
	//}
}

//Set shutter level of DAc
int HeliosDac::HeliosDacDevice::SetShutter(bool level)
{
	if (closed)
		return HELIOS_ERROR;

	std::lock_guard<std::mutex> lock(frameLock);

	std::uint8_t txBuffer[2] = { 0x02, level };
	if (SendControl(txBuffer, 2) == HELIOS_SUCCESS)
		return HELIOS_SUCCESS;
	else
		return HELIOS_ERROR;
}

//Stops output of DAC
int HeliosDac::HeliosDacDevice::Stop()
{
	if (closed)
		return HELIOS_ERROR;

	std::lock_guard<std::mutex> lock(frameLock);

	std::uint8_t txBuffer[2] = { 0x01, 0 };
	if (SendControl(txBuffer, 2) == HELIOS_SUCCESS)
		return HELIOS_SUCCESS;
	else
		return HELIOS_ERROR;
}

//Sets persistent name of DAC
int HeliosDac::HeliosDacDevice::SetName(char* name)
{
	if (closed)
		return HELIOS_ERROR;

	std::lock_guard<std::mutex> lock(frameLock);

	std::uint8_t txBuffer[32] = { 0x06 };
	memcpy(&txBuffer[1], name, 30);
	txBuffer[31] = '\0';
	if (SendControl(txBuffer, 32) == HELIOS_SUCCESS)
		return HELIOS_SUCCESS;
	else
		return HELIOS_ERROR;
}

//Erases the firmware of the DAC, allowing it to be updated
int HeliosDac::HeliosDacDevice::EraseFirmware()
{
	if (closed)
		return HELIOS_ERROR;

	std::lock_guard<std::mutex> lock(frameLock);

	std::uint8_t txBuffer[2] = { 0xDE, 0 };
	if (SendControl(txBuffer, 2) == HELIOS_SUCCESS)
		return HELIOS_SUCCESS;
	else
		return HELIOS_ERROR;
}

//sends a raw control signal (implemented as interrupt transfer) to a dac device
//returns 1 if successful
int HeliosDac::HeliosDacDevice::SendControl(std::uint8_t* bufferAddress, int length)
{
	if ((bufferAddress == NULL) || (length > 32) || (length <= 0))
		return HELIOS_ERROR;

	int actualLength = 0;
	int transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_OUT, bufferAddress, length, &actualLength, 32);

	if ((transferResult == 0) && (actualLength == length))
		return HELIOS_SUCCESS;
	else
		return transferResult;
}

//Attempts to receive a response to a previous control transfer.
//Returns 1 and populates bufferAddress if successful
//int HeliosDac::HeliosDacDevice::GetControlResponse(std::uint8_t* bufferAddress)
//{
//	while (closed); //wait until init is done
//
//	if (bufferAddress == NULL)
//		return 0;
//
//	std::uint8_t data[32];
//	int actualLength = 0;
//	int transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &data[0], 32, &actualLength, 32);
//
//	if (transferResult < 0)
//	{
//		return transferResult;
//	}
//	else
//	{
//		memcpy(bufferAddress, &data[0], 32);
//		return 1;
//	}
//}

//void HeliosDac::HeliosDacDevice::WaitForStatus()
//{
//	while (closed); //wait until init is done
//	waitingForStatus = true;
//
//	if (firmwareVersion < 5)
//	{
//		std::uint8_t ctrlBuffer[32] = { 0x03, 0 };
//		SendControl(&ctrlBuffer[0], 2);
//	}
//
//	std::uint8_t ctrlBuffer2[2];
//	int actualLength = 0;
//	bool ok = false;
//	threadLock->lock();
//	while (!ok && !closed)
//	{
//		threadLock->unlock();
//		if (libusb_interrupt_transfer(usbHandle, EP_INT_IN, &ctrlBuffer2[0], 32, &actualLength, 32) == 0)
//		{
//			if (ctrlBuffer2[0] == 0x83) //status transfer code
//			{
//				threadLock->lock();
//				status = (ctrlBuffer2[1] == 1);
//				threadLock->unlock();
//				ok = true;
//			}
//			//else
//			//	WaitForStatus();
//		}
//		threadLock->lock();
//	}
//	//libusb_interrupt_transfer(usbHandle, EP_INT_IN, &ctrlBuffer[0], 2, &actualLength, 1);
//	//else
//	//	printf("\n%d\n",tx);
//
//	waitingForStatus = false;
//	threadLock->unlock();
//}

//void HeliosDac::HeliosDacDevice::InterruptTransferHandler()
//{
//	//std::lock_guard<std::mutex>lock(intLock);
//	std::uint8_t ctrlBuffer[32];
//	int actualLength = 0;
//	int transferResult = -1;
//	bool quit = false;
//	while (!quit)
//	{
//		quit = true;
//		transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, &ctrlBuffer[0], 32, &actualLength, 64);
//		if (transferResult == LIBUSB_SUCCESS)
//		{
//			if (ctrlBuffer[0] == 0x83) //STATUS
//			{
//				if (ctrlBuffer[1] == 1)
//				{
//					threadLock->lock();
//					status = true;
//					waitingForStatus = false;
//					threadLock->unlock();
//				}
//				else
//				{
//					std::uint8_t ctrlBuffer[32] = { 0x03, 0 };
//					SendControl(&ctrlBuffer[0], 2);
//					quit = false;
//					return;
//				}
//			}
//			//else if (ctrlBuffer[0] == 0x84) //FIRMWARE VERSION
//			//{
//			//	threadLock->lock();
//			//	firmwareVersion = ((ctrlBuffer[1] << 0) |
//			//		(ctrlBuffer[2] << 8) |
//			//		(ctrlBuffer[3] << 16) |
//			//		(ctrlBuffer[4] << 24));
//			//	threadLock->unlock();
//			//}
//			//else if (ctrlBuffer[0] == 0x85) //NAME
//			//{
//			//	ctrlBuffer[31] = '\0'; //just in case
//			//	threadLock->lock();
//			//	memcpy(name, &ctrlBuffer[1], 31);
//			//	threadLock->unlock();
//			//}
//			//else
//			//{
//			//	//unknown transfer id
//			//	//quit = false;
//			//}
//		}
//	}
//}

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
//		//std::uint8_t data[2] = { 0, 0 };
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

HeliosDac::HeliosDacDevice::~HeliosDacDevice()
{
	closed = true;
	std::lock_guard<std::mutex>lock(frameLock);

	libusb_close(usbHandle);
}
