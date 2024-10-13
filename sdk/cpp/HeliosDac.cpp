/*
SDK for Helios Laser DAC class
By Gitle Mikkelsen
gitlem@gmail.com
MIT License

Dependencies:
Libusb 1.0 (GNU Lesser General Public License, see libusb.h)

Standard: C++14
git repo: https://github.com/Grix/helios_dac.git

See header HeliosDac.h for function and usage documentation
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

int HeliosDac::OpenDevices()
{
	if (inited)
		return deviceList.size();

	// TODO: Make option to keep existing DACs in their current indexes, e.g only scan for changes. Currently this function only works after all DACs have been closed.

	// Scanning for USB devices

	int result = libusb_init(NULL);
	if (result < 0)
		return result;

	libusb_set_option(NULL, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL);

	libusb_device** devs;
	ssize_t cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0)
		return (int)cnt;

	std::lock_guard<std::mutex> lock(threadLock);

	unsigned int numDevices = 0;
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
		deviceList.push_back(std::make_unique<HeliosDacUsbDevice>(devHandle));

		numDevices++;
	}

	libusb_free_device_list(devs, 1);


	// Scanning IDN (Network) devices

	std::vector<IDNCONTEXT*> idnContexts;

#ifndef WIN32 

	unsigned msTimeout = 500;
	IDNSL_SERVER_INFO* firstServerInfo;
	int rcGetList = getIDNServerList(&firstServerInfo, 0, msTimeout);
	if (rcGetList != 0)
	{
		logError("getIDNServerList() failed (error: %d)", rcGetList);
	}
	else
	{
		for (IDNSL_SERVER_INFO* serverInfo = firstServerInfo; serverInfo != 0; serverInfo = serverInfo->next)
		{
			for (unsigned int i = 0; i < serverInfo->addressCount; i++)
			{
				if (serverInfo->addressTable[i].errorFlags == 0 && idnContexts.size() < 999)
				{
					bool found = false;
					int contextId = 0;
					for (; contextId < idnContexts.size(); contextId++) // Check for duplicate entries
					{
						if (idnContexts[contextId]->serverSockAddr.sin_addr.s_addr == serverInfo->addressTable[i].addr.s_addr) // todo: and name / unit id?
							found = true;
					}
					if (!found)
					{
						for (unsigned int j = 0; j < serverInfo->serviceCount && idnContexts.size() < 999; j++)
						{
							IDNCONTEXT* ctx = new IDNCONTEXT{ 0 };
							ctx->serverSockAddr.sin_family = AF_INET;
							ctx->serverSockAddr.sin_port = htons(IDN_PORT);
							ctx->serverSockAddr.sin_addr.s_addr = serverInfo->addressTable[i].addr.s_addr;
							ctx->name = std::string(serverInfo->hostName).append(" - ").append(serverInfo->serviceTable[j].serviceName);
							ctx->serviceId = serverInfo->serviceTable[j].serviceID;

							idnContexts.push_back(ctx);
						}

					}
				}
			}
		}

		freeIDNServerList(firstServerInfo);  // Server list is dynamically allocated and must be freed
	}
#else
	unsigned msTimeout = 500;
	IDNSL_SERVER_INFO* firstServerInfo;
	int rcGetList = getIDNServerList(&firstServerInfo, 0, msTimeout);
	if (rcGetList != 0)
	{
		logError("getIDNServerList() failed (error: %d)", rcGetList);
	}
	else
	{
		for (IDNSL_SERVER_INFO* serverInfo = firstServerInfo; serverInfo != 0; serverInfo = serverInfo->next)
		{
			for (unsigned int i = 0; i < serverInfo->addressCount; i++)
			{
				if (serverInfo->addressTable[i].errorFlags == 0 && idnContexts.size() < 999)
				{
					bool found = false;
					int contextId = 0;
					for (; contextId < idnContexts.size(); contextId++) // Check for duplicate entries
					{
						if (idnContexts[contextId]->serverSockAddr.sin_addr.S_un.S_addr == serverInfo->addressTable[i].addr.S_un.S_addr) // todo: and name / unit id?
							found = true;
					}
					if (!found)
					{
						for (unsigned int j = 0; j < serverInfo->serviceCount && idnContexts.size() < 999; j++)
						{
							IDNCONTEXT* ctx = new IDNCONTEXT{ 0 };
							ctx->serverSockAddr.sin_family = AF_INET;
							ctx->serverSockAddr.sin_port = htons(IDN_PORT);
							ctx->serverSockAddr.sin_addr.s_addr = serverInfo->addressTable[i].addr.S_un.S_addr;
							ctx->name = std::string(serverInfo->hostName).append(" - ").append(serverInfo->serviceTable[j].serviceName);
							ctx->serviceId = serverInfo->serviceTable[j].serviceID;

							idnContexts.push_back(ctx);
						}

					}
				}
			}
		}

		freeIDNServerList(firstServerInfo);  // Server list is dynamically allocated and must be freed
	}

#endif

	for (int i = 0; i < idnContexts.size(); i++)
	{
		IDNCONTEXT* idnContext = idnContexts[i];
		deviceList.push_back(std::make_unique<HeliosDacIdnDevice>(idnContext));
		numDevices++;
	}

	if (numDevices > 0)
		inited = true;

	return numDevices;
}

int HeliosDac::CloseDevices()
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;
	
	std::lock_guard<std::mutex> lock(threadLock);
	inited = false;
	deviceList.clear(); //various destructors will clean all devices

	libusb_exit(NULL);

	return HELIOS_SUCCESS;
}

int HeliosDac::WriteFrame(unsigned int devNum, unsigned int pps, std::uint8_t flags, HeliosPoint* points, unsigned int numOfPoints)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	if (points == NULL || numOfPoints == 0)
		return HELIOS_ERROR_NULL_POINTS;

	if (pps > HELIOS_MAX_RATE_LEGACY) // TODO get limits specific to DAC model
		return HELIOS_ERROR_PPS_TOO_HIGH;

	if (pps < HELIOS_MIN_RATE_LEGACY)
		return HELIOS_ERROR_PPS_TOO_LOW;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL; 
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();

	if (dev == NULL)
		return HELIOS_ERROR_INVALID_DEVNUM;

	return dev->SendFrame(pps, flags, points, std::min<int>(numOfPoints, HELIOS_MAX_POINTS_LEGACY));
}

int HeliosDac::WriteFrameHighResolution(unsigned int devNum, unsigned int pps, unsigned int flags, HeliosPointHighRes* points, unsigned int numOfPoints)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	if (points == NULL || numOfPoints == 0)
		return HELIOS_ERROR_NULL_POINTS;

	if (pps > HELIOS_MAX_RATE_LEGACY) // TODO get limits specific to DAC model
		return HELIOS_ERROR_PPS_TOO_HIGH;

	if (pps < HELIOS_MIN_RATE_LEGACY)
		return HELIOS_ERROR_PPS_TOO_LOW;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();

	if (dev == NULL)
		return HELIOS_ERROR_INVALID_DEVNUM;

	return dev->SendFrameHighResolution(pps, flags, points, std::min<int>(numOfPoints, HELIOS_MAX_POINTS_LEGACY));
}

int HeliosDac::WriteFrameExtended(unsigned int devNum, unsigned int pps, unsigned int flags, HeliosPointExt* points, unsigned int numOfPoints)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	if (points == NULL || numOfPoints == 0)
		return HELIOS_ERROR_NULL_POINTS;

	if (pps > HELIOS_MAX_RATE_LEGACY) // TODO get limits specific to DAC model
		return HELIOS_ERROR_PPS_TOO_HIGH;

	if (pps < HELIOS_MIN_RATE_LEGACY)
		return HELIOS_ERROR_PPS_TOO_LOW;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();

	if (dev == NULL)
		return HELIOS_ERROR_INVALID_DEVNUM;

	return dev->SendFrameExtended(pps, flags, points, std::min<int>(numOfPoints, HELIOS_MAX_POINTS_LEGACY));
}

int HeliosDac::GetStatus(unsigned int devNum)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return HELIOS_ERROR_INVALID_DEVNUM;

	return dev->GetStatus();
}

int HeliosDac::GetFirmwareVersion(unsigned int devNum)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return HELIOS_ERROR_INVALID_DEVNUM;

	return dev->GetFirmwareVersion();
}

int HeliosDac::GetName(unsigned int devNum, char* name)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return HELIOS_ERROR_INVALID_DEVNUM;

	char dacName[32];
	if (dev->GetName(dacName) < 0)
	{
		// The device didn't return a name so build a generic name
		memcpy(name, "Unknown Helios ", 16);
		name[15] = (char)((int)(devNum >= 10) + 48);
		name[16] = (char)((int)(devNum % 10) + 48);
		name[17] = '\0';
	}
	else
	{
		memcpy(name, dacName, 32);
	}
	return HELIOS_SUCCESS;
}

int HeliosDac::SetName(unsigned int devNum, char* name)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return HELIOS_ERROR_INVALID_DEVNUM;

	return dev->SetName(name);
}

int HeliosDac::Stop(unsigned int devNum)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return HELIOS_ERROR_INVALID_DEVNUM;

	return dev->Stop();
}

int HeliosDac::SetShutter(unsigned int devNum, bool level)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return HELIOS_ERROR_INVALID_DEVNUM;

	return dev->SetShutter(level);
}

int HeliosDac::SetLibusbDebugLogLevel(int logLevel)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	libusb_set_option(NULL, LIBUSB_OPTION_LOG_LEVEL, logLevel);

	return HELIOS_SUCCESS;
}

int HeliosDac::EraseFirmware(unsigned int devNum)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();
	if (dev == NULL)
		return HELIOS_ERROR_INVALID_DEVNUM;

	return dev->EraseFirmware();
}


/// -----------------------------------------------------------------------
/// HeliosDacUsbDevice START (one instance for each connected USB DAC)
/// -----------------------------------------------------------------------

HeliosDac::HeliosDacUsbDevice::HeliosDacUsbDevice(libusb_device_handle* handle)
{
	closed = true;
	usbHandle = handle;
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::lock_guard<std::mutex>lock(frameLock);

	int actualLength = 0;
	for (int i = 0; i < 32; i++)
		name[i] = 0;

	//catch any lingering transfers
	std::uint8_t ctrlBuffer0[32];
	while (libusb_interrupt_transfer(usbHandle, EP_INT_IN, ctrlBuffer0, 32, &actualLength, 5) == LIBUSB_SUCCESS);

	//get firmware version
	firmwareVersion = 0;
	bool repeat = true;
	for (int i = 0; ((i < 2) && repeat); i++) //retry command if necessary
	{
		std::uint8_t ctrlBuffer[2] = { 0x04, 0 };
		int transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_OUT, ctrlBuffer, 2, &actualLength, 32);
		if ((transferResult == LIBUSB_SUCCESS) && (actualLength == 2))
		{
			for (int j = 0; ((j < 3) && repeat); j++) //retry response getting if necessary
			{
				std::uint8_t ctrlBuffer2[32];
				transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, ctrlBuffer2, 32, &actualLength, 32);
				if (transferResult == LIBUSB_SUCCESS)
				{
					if (ctrlBuffer2[0] == 0x84)
					{
						firmwareVersion = ((ctrlBuffer2[1] << 0) |
							(ctrlBuffer2[2] << 8) |
							(ctrlBuffer2[3] << 16) |
							(ctrlBuffer2[4] << 24));
						repeat = false;
					}
				}
			}
		}
	}


	//send sdk firmware version
	repeat = true;
	for (int i = 0; ((i < 2) && repeat); i++) //retry command if necessary
	{
		std::uint8_t ctrlBuffer3[2] = { 0x07, HELIOS_SDK_VERSION };
		int transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_OUT, ctrlBuffer3, 2, &actualLength, 32);
		if ((transferResult == LIBUSB_SUCCESS) && (actualLength == 2))
			repeat = false;
	}

	frameBuffer = new std::uint8_t[HELIOS_MAX_POINTS_LEGACY * 7 + 5];
	frameBufferSize = 0;

	closed = false;

	std::thread frameHandlerThread(&HeliosDac::HeliosDacUsbDevice::BackgroundFrameHandler, this);
	frameHandlerThread.detach();
}

// Sends a raw frame buffer (implemented as bulk transfer) to a dac device
// Returns 1 if success
int HeliosDac::HeliosDacUsbDevice::SendFrame(unsigned int pps, std::uint8_t flags, HeliosPoint* points, unsigned int numOfPoints)
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	if (frameReady)
		return HELIOS_ERROR_DEVICE_FRAME_READY;

	// This is a bug workaround, the mcu won't correctly receive transfers with these sizes
	unsigned int ppsActual = pps;
	unsigned int numOfPointsActual = numOfPoints;
	if ((((int)numOfPoints-45) % 64) == 0)
	{
		numOfPointsActual--;
		//adjust pps to keep the same frame duration even with one less point
		ppsActual = (unsigned int)((pps * (double)numOfPointsActual / (double)numOfPoints) + 0.5); 
	}
	if (numOfPointsActual > HELIOS_MAX_POINTS_LEGACY)
		return HELIOS_ERROR_TOO_MANY_POINTS; // Todo subsample instead

	unsigned int bufPos = 0;

	// Prepare frame buffer
	for (unsigned int i = 0; i < numOfPointsActual; i++)
	{
		frameBuffer[bufPos++] = (points[i].x >> 4);
		frameBuffer[bufPos++] = ((points[i].x & 0x0F) << 4) | (points[i].y >> 8);
		frameBuffer[bufPos++] = (points[i].y & 0xFF);
		frameBuffer[bufPos++] = points[i].r;
		frameBuffer[bufPos++] = points[i].g;
		frameBuffer[bufPos++] = points[i].b;
		frameBuffer[bufPos++] = points[i].i;
	}
	frameBuffer[bufPos++] = (ppsActual & 0xFF);
	frameBuffer[bufPos++] = (ppsActual >> 8);
	frameBuffer[bufPos++] = (numOfPointsActual & 0xFF);
	frameBuffer[bufPos++] = (numOfPointsActual >> 8);
	frameBuffer[bufPos++] = flags;

	frameBufferSize = bufPos;

	if (!shutterIsOpen)
		SetShutter(1);

	if ((flags & HELIOS_FLAGS_DONT_BLOCK) != 0)
	{
		frameReady = true;
		return HELIOS_SUCCESS;
	}
	else
	{
		return DoFrame();
	}
}

// Sends a raw frame buffer (implemented as bulk transfer) to a dac device, using high-res point structure (but simply convert down to low-res)
// Returns 1 if success
int HeliosDac::HeliosDacUsbDevice::SendFrameHighResolution(unsigned int pps, std::uint8_t flags, HeliosPointHighRes* points, unsigned int numOfPoints)
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	if (frameReady)
		return HELIOS_ERROR_DEVICE_FRAME_READY;

	// This is a bug workaround, the mcu won't correctly receive transfers with these sizes
	unsigned int ppsActual = pps;
	unsigned int numOfPointsActual = numOfPoints;
	if ((((int)numOfPoints - 45) % 64) == 0)
	{
		numOfPointsActual--;
		// Adjust pps to keep the same frame duration even with one less point
		ppsActual = (unsigned int)((pps * (double)numOfPointsActual / (double)numOfPoints) + 0.5);
	}
	if (numOfPointsActual > HELIOS_MAX_POINTS_LEGACY)
		return HELIOS_ERROR_TOO_MANY_POINTS; // Todo subsample instead

	unsigned int bufPos = 0;

	// Prepare frame buffer
	// Converting to non-high-res for unsupported models
	for (unsigned int i = 0; i < numOfPointsActual; i++)
	{
		std::uint16_t x = points[i].x >> 4;
		std::uint16_t y = points[i].y >> 4;
		frameBuffer[bufPos++] = (x >> 4);
		frameBuffer[bufPos++] = ((x & 0x0F) << 4) | (y >> 8);
		frameBuffer[bufPos++] = (y & 0xFF);
		frameBuffer[bufPos++] = points[i].r >> 8;
		frameBuffer[bufPos++] = points[i].g >> 8;
		frameBuffer[bufPos++] = points[i].b >> 8;
		frameBuffer[bufPos++] = 0xFF;
	}
	frameBuffer[bufPos++] = (ppsActual & 0xFF);
	frameBuffer[bufPos++] = (ppsActual >> 8);
	frameBuffer[bufPos++] = (numOfPointsActual & 0xFF);
	frameBuffer[bufPos++] = (numOfPointsActual >> 8);
	frameBuffer[bufPos++] = flags;

	frameBufferSize = bufPos;

	if (!shutterIsOpen)
		SetShutter(1);

	if ((flags & HELIOS_FLAGS_DONT_BLOCK) != 0)
	{
		frameReady = true;
		return HELIOS_SUCCESS;
	}
	else
	{
		return DoFrame();
	}
}
// Sends a raw frame buffer (implemented as bulk transfer) to a dac device, using extended point structure (but simply convert down to low-res)
// Returns 1 if success
int HeliosDac::HeliosDacUsbDevice::SendFrameExtended(unsigned int pps, std::uint8_t flags, HeliosPointExt* points, unsigned int numOfPoints)
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	if (frameReady)
		return HELIOS_ERROR_DEVICE_FRAME_READY;

	// This is a bug workaround, the mcu won't correctly receive transfers with these sizes
	unsigned int ppsActual = pps;
	unsigned int numOfPointsActual = numOfPoints;
	if ((((int)numOfPoints - 45) % 64) == 0)
	{
		numOfPointsActual--;
		// Adjust pps to keep the same frame duration even with one less point
		ppsActual = (unsigned int)((pps * (double)numOfPointsActual / (double)numOfPoints) + 0.5);
	}
	if (numOfPointsActual > HELIOS_MAX_POINTS_LEGACY)
		return HELIOS_ERROR_TOO_MANY_POINTS; // Todo subsample instead

	unsigned int bufPos = 0;

	// Prepare frame buffer
	// Converting to non-high-res for unsupported models
	for (unsigned int i = 0; i < numOfPointsActual; i++)
	{
		std::uint16_t x = points[i].x >> 4;
		std::uint16_t y = points[i].y >> 4;
		frameBuffer[bufPos++] = (x >> 4);
		frameBuffer[bufPos++] = ((x & 0x0F) << 4) | (y >> 8);
		frameBuffer[bufPos++] = (y & 0xFF);
		frameBuffer[bufPos++] = points[i].r >> 8;
		frameBuffer[bufPos++] = points[i].g >> 8;
		frameBuffer[bufPos++] = points[i].b >> 8;
		frameBuffer[bufPos++] = points[i].i >> 8;
	}
	frameBuffer[bufPos++] = (ppsActual & 0xFF);
	frameBuffer[bufPos++] = (ppsActual >> 8);
	frameBuffer[bufPos++] = (numOfPointsActual & 0xFF);
	frameBuffer[bufPos++] = (numOfPointsActual >> 8);
	frameBuffer[bufPos++] = flags;

	frameBufferSize = bufPos;

	if (!shutterIsOpen)
		SetShutter(1);

	if ((flags & HELIOS_FLAGS_DONT_BLOCK) != 0)
	{
		frameReady = true;
		return HELIOS_SUCCESS;
	}
	else
	{
		return DoFrame();
	}
}

// Sends frame to DAC
int HeliosDac::HeliosDacUsbDevice::DoFrame()
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	int actualLength = 0;
	int transferResult = libusb_bulk_transfer(usbHandle, EP_BULK_OUT, frameBuffer, frameBufferSize, &actualLength, 8 + (frameBufferSize >> 5));

	if (transferResult == LIBUSB_SUCCESS)
		return HELIOS_SUCCESS;
	else
		return HELIOS_ERROR_LIBUSB_BASE + transferResult;
}

// Continually running thread, when a frame is ready, it is sent to the DAC
// Only used if HELIOS_FLAGS_DONT_BLOCK is used with WriteFrame
void HeliosDac::HeliosDacUsbDevice::BackgroundFrameHandler()
{ 
	while (!closed)
	{
		// Wait until frame is ready to be sent
		while ((!frameReady) && (!closed))
			std::this_thread::sleep_for(std::chrono::microseconds(100));

		if (closed)
			return;

		DoFrame();

		frameReady = false;
	}
}


//Gets firmware version of DAC
int HeliosDac::HeliosDacUsbDevice::GetFirmwareVersion()
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	return firmwareVersion;
}

//Gets firmware version of DAC
int HeliosDac::HeliosDacUsbDevice::GetName(char* dacName)
{
	if (closed)
	{
		return HELIOS_ERROR_DEVICE_CLOSED;
	}
	
	int errorCode;

	std::lock_guard<std::mutex> lock(frameLock);

	for (int i = 0; (i < 2); i++) //retry command if necessary
	{
		int actualLength = 0;
		std::uint8_t ctrlBuffer4[2] = { 0x05, 0 };
		if (SendControl(ctrlBuffer4, 2) == HELIOS_SUCCESS)
		{
			std::uint8_t ctrlBuffer5[32];
			int transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, ctrlBuffer5, 32, &actualLength, 32);

			if (transferResult == LIBUSB_SUCCESS)
			{
				if (ctrlBuffer5[0] == 0x85)
				{
					ctrlBuffer5[31] = '\0';
					memcpy(name, &ctrlBuffer5[1], 31);
					memcpy(dacName, &ctrlBuffer5[1], 31);
					return HELIOS_SUCCESS;
				}
				else
				{
					errorCode = HELIOS_ERROR_DEVICE_RESULT;
				}
			}
			else
			{
				errorCode = HELIOS_ERROR_LIBUSB_BASE + transferResult;
			}
		}
		else
		{
			errorCode = HELIOS_ERROR_DEVICE_SEND_CONTROL;
		}
	}

	return errorCode;
}

//Gets status of DAC, 1 means DAC is ready to receive frame, 0 means it's not
int HeliosDac::HeliosDacUsbDevice::GetStatus()
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	int errorCode;

	std::lock_guard<std::mutex> lock(frameLock);

	int actualLength = 0;
	std::uint8_t ctrlBuffer[2] = { 0x03, 0 };
	if (SendControl(ctrlBuffer, 2) == HELIOS_SUCCESS)
	{
		std::uint8_t ctrlBuffer2[32];
		int transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_IN, ctrlBuffer2, 32, &actualLength, 16);
		if (transferResult == LIBUSB_SUCCESS)
		{
			if (ctrlBuffer2[0] == 0x83) //STATUS ID
			{
				if (ctrlBuffer2[1] == 0)
					return 0;
				else
					return 1;
			}
			else
			{
				errorCode = HELIOS_ERROR_DEVICE_RESULT;
			}
		}
		else
		{
			errorCode = HELIOS_ERROR_LIBUSB_BASE + transferResult;
		}
	}
	else
	{
		errorCode = HELIOS_ERROR_DEVICE_SEND_CONTROL;
	}

	return errorCode;
}

//Set shutter level of DAC
//Value 1 = shutter open, value 0 = shutter closed
int HeliosDac::HeliosDacUsbDevice::SetShutter(bool level)
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	std::lock_guard<std::mutex> lock(frameLock);

	std::uint8_t txBuffer[2] = { 0x02, level };
	if (SendControl(txBuffer, 2) == HELIOS_SUCCESS)
	{
		shutterIsOpen = level;
		return HELIOS_SUCCESS;
	}
	else
		return HELIOS_ERROR_DEVICE_SEND_CONTROL;
}

//Stops output of DAC
int HeliosDac::HeliosDacUsbDevice::Stop()
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	std::lock_guard<std::mutex> lock(frameLock);

	std::uint8_t txBuffer[2] = { 0x01, 0 };
	if (SendControl(txBuffer, 2) == HELIOS_SUCCESS)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		return HELIOS_SUCCESS;
	}
	else
		return HELIOS_ERROR_DEVICE_SEND_CONTROL;
}

//Sets persistent name of DAC
int HeliosDac::HeliosDacUsbDevice::SetName(char* name)
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	std::lock_guard<std::mutex> lock(frameLock);

	std::uint8_t txBuffer[32] = { 0x06 };
	memcpy(&txBuffer[1], name, 30);
	txBuffer[31] = '\0';
	if (SendControl(txBuffer, 32) == HELIOS_SUCCESS)
		return HELIOS_SUCCESS;
	else
		return HELIOS_ERROR_DEVICE_SEND_CONTROL;
}

//Erases the firmware of the DAC, allowing it to be updated
int HeliosDac::HeliosDacUsbDevice::EraseFirmware()
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	std::lock_guard<std::mutex> lock(frameLock);

	std::uint8_t txBuffer[2] = { 0xDE, 0 };
	if (SendControl(txBuffer, 2) == HELIOS_SUCCESS)
	{
		closed = true;
		return HELIOS_SUCCESS;
	}
	else
		return HELIOS_ERROR_DEVICE_SEND_CONTROL;
}

//sends a raw control signal (implemented as interrupt transfer) to a dac device
//returns 1 if successful
int HeliosDac::HeliosDacUsbDevice::SendControl(std::uint8_t* bufferAddress, unsigned int length)
{
	if (bufferAddress == NULL)
		return HELIOS_ERROR_DEVICE_NULL_BUFFER;

	if (length > 32)
		return HELIOS_ERROR_DEVICE_SIGNAL_TOO_LONG;

	int actualLength = 0;
	int transferResult = libusb_interrupt_transfer(usbHandle, EP_INT_OUT, bufferAddress, length, &actualLength, 16);

	if (transferResult == LIBUSB_SUCCESS)
		return HELIOS_SUCCESS;
	else
		return HELIOS_ERROR_LIBUSB_BASE + transferResult;
}

HeliosDac::HeliosDacUsbDevice::~HeliosDacUsbDevice()
{
	closed = true;
	std::lock_guard<std::mutex>lock(frameLock); //wait until all threads have closed

	libusb_close(usbHandle);
	delete frameBuffer;
}




/// -----------------------------------------------------------------------
/// HeliosDacIdnDevice START (one instance for each connected IDN/network DAC)
/// -----------------------------------------------------------------------

HeliosDac::HeliosDacIdnDevice::HeliosDacIdnDevice(IDNCONTEXT* _context)
{
	closed = true;
	context = _context;
	std::lock_guard<std::mutex> lock(frameLock);
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	int actualLength = 0;
	for (int i = 0; i < 32; i++)
		name[i] = 0;

	statusReadyTime = std::chrono::high_resolution_clock::now();

	context->bufferLen = 0x4000;
	context->bufferPtr = new uint8_t[0x4000];
	context->startTime = plt_getMonoTimeUS();

#if defined(_WIN32) || defined(WIN32)
	// Initialize Winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		logError("WSAStartup failed with error: %d", iResult);
		return;
	}
#else
	// Initialize time reference and initialize the current time randomly
	extern struct timespec plt_monoRef;
	extern uint32_t plt_monoTimeUS;
#ifdef __APPLE__
	if (mach_clock_gettime(SYSTEM_CLOCK, &plt_monoRef) < 0)
#else
	if (clock_gettime(CLOCK_MONOTONIC, &plt_monoRef) < 0)
#endif
	{
		logError("clock_gettime(CLOCK_MONOTONIC) errno = %d", errno);
		return;
	}
	plt_monoTimeUS = (uint32_t)((plt_monoRef.tv_sec * 1000000ul) + (plt_monoRef.tv_nsec / 1000));
#endif

	// Open UDP socket
	context->fdSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (context->fdSocket < 0)
	{
#if defined(_WIN32) || defined(WIN32)
		logError("socket() error %d", WSAGetLastError());
#else
		logError("socket() errno = %d", errno);
#endif

		return;
	}

	//get firmware version
	// TODO 

	closed = false;

	std::thread frameHandlerThread(&HeliosDac::HeliosDacIdnDevice::BackgroundFrameHandler, this);
	frameHandlerThread.detach();
}

// Sends a raw frame buffer (implemented as bulk transfer) to a dac device
// Returns 1 if success
int HeliosDac::HeliosDacIdnDevice::SendFrame(unsigned int pps, std::uint8_t flags, HeliosPoint* points, unsigned int numOfPoints)
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	if (frameReady)
		return HELIOS_ERROR_DEVICE_FRAME_READY;

	if (numOfPoints == 0)
		return HELIOS_ERROR_NULL_POINTS;

	if (pps == 0)
		return HELIOS_ERROR_PPS_TOO_LOW;

	if (idnOpenFrameXYRGB(context))
		return false;

	context->scanSpeed = pps;
	context->jitterFreeFlag = (flags & HELIOS_FLAGS_SINGLE_MODE) != 0;

	if (((flags & HELIOS_FLAGS_DONT_SIMULATE_TIMING) == 0) && !firstFrame)
	{
		statusReadyTime = std::chrono::high_resolution_clock::now() + std::chrono::microseconds((long long)((1000000 / ((double)pps / numOfPoints)) * 0.98)); // Now plus duration of frame
	}
	firstFrame = false;

	for (int i = 0; i < numOfPoints; i++)
	{
		if (idnPutSampleXYRGB(context, (points[i].x << 4) - 0x8000, (points[i].y << 4) - 0x8000, points[i].r, points[i].g, points[i].b))
			return false;
	}

	if ((flags & HELIOS_FLAGS_DONT_BLOCK) != 0)
	{
		frameReady = true;
		return HELIOS_SUCCESS;
	}
	else
	{
		return DoFrame();
	}
}

// Sends a raw frame buffer (implemented as bulk transfer) to a dac device
// Returns 1 if success
int HeliosDac::HeliosDacIdnDevice::SendFrameHighResolution(unsigned int pps, std::uint8_t flags, HeliosPointHighRes* points, unsigned int numOfPoints)
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	if (frameReady)
		return HELIOS_ERROR_DEVICE_FRAME_READY;

	if (numOfPoints == 0)
		return HELIOS_ERROR_NULL_POINTS;

	if (idnOpenFrameHighResXYRGB(context))
		return false;

	context->scanSpeed = pps;
	context->jitterFreeFlag = (flags & HELIOS_FLAGS_SINGLE_MODE) != 0;

	if (((flags & HELIOS_FLAGS_DONT_SIMULATE_TIMING) == 0) && !firstFrame)
	{
		statusReadyTime = std::chrono::high_resolution_clock::now() + std::chrono::microseconds((long long)((1000000 / ((double)pps / numOfPoints)) * 0.98)); // Now plus duration of frame
	}
	firstFrame = false;

	for (int i = 0; i < numOfPoints; i++)
	{
		if (idnPutSampleHighResXYRGB(context, points[i].x - 0x8000, points[i].y - 0x8000, points[i].r, points[i].g, points[i].b))
			return false;
	}

	if ((flags & HELIOS_FLAGS_DONT_BLOCK) != 0)
	{
		frameReady = true;
		return HELIOS_SUCCESS;
	}
	else
	{
		return DoFrame();
	}
}


// Sends a raw frame buffer (implemented as bulk transfer) to a dac device
// Returns 1 if success
int HeliosDac::HeliosDacIdnDevice::SendFrameExtended(unsigned int pps, std::uint8_t flags, HeliosPointExt* points, unsigned int numOfPoints)
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	if (frameReady)
		return HELIOS_ERROR_DEVICE_FRAME_READY;

	if (numOfPoints == 0)
		return HELIOS_ERROR_NULL_POINTS;

	if (idnOpenFrameExtended(context))
		return false;

	context->scanSpeed = pps;
	context->jitterFreeFlag = (flags & HELIOS_FLAGS_SINGLE_MODE) != 0;

	if (((flags & HELIOS_FLAGS_DONT_SIMULATE_TIMING) == 0) && !firstFrame)
	{
		statusReadyTime = std::chrono::high_resolution_clock::now() + std::chrono::microseconds((long long)((1000000 / ((double)pps / numOfPoints)) * 0.98)); // Now plus duration of frame
	}
	firstFrame = false;

	for (int i = 0; i < numOfPoints; i++)
	{
		if (idnPutSampleExtended(context, (int16_t)(points[i].x - 0x8000), (int16_t)(points[i].y - 0x8000), points[i].r, points[i].g, points[i].b, points[i].i, points[i].user1, points[i].user2, points[i].user3, points[i].user4))
			return false;
	}

	if ((flags & HELIOS_FLAGS_DONT_BLOCK) != 0)
	{
		frameReady = true;
		return HELIOS_SUCCESS;
	}
	else
	{
		return DoFrame();
	}
}



// Gets status of DAC, 1 means DAC is ready to receive frame, 0 means it's not
int HeliosDac::HeliosDacIdnDevice::GetStatus()
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	if (frameReady || (std::chrono::high_resolution_clock::now() < statusReadyTime))
		return false;

	return true; // No feedback in IDN
}

// Returns whether a specific DAC supports the new WriteFrameHighResolution() and WriteFrameExtended() functions. 
bool HeliosDac::GetSupportsHigherResolutions(unsigned int devNum)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();

	if (dev == NULL)
		return HELIOS_ERROR_INVALID_DEVNUM;

	return dev->GetSupportsHigherResolutions();
}


// Sends frame to DAC
int HeliosDac::HeliosDacIdnDevice::DoFrame()
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	if (idnPushFrame(context) != 0)
		return HELIOS_ERROR_NETWORK; // TODO return more specific error code

	return HELIOS_SUCCESS;
}

// Continually running thread, when a frame is ready, it is sent to the DAC
// Only used if HELIOS_FLAGS_DONT_BLOCK is used with WriteFrame
void HeliosDac::HeliosDacIdnDevice::BackgroundFrameHandler()
{
	while (!closed)
	{
		// Wait until frame is ready to be sent
		while ((!frameReady) && (!closed))
			std::this_thread::sleep_for(std::chrono::microseconds(100));

		if (closed)
			return;

		DoFrame();

		frameReady = false;
	}
}


// Gets firmware version of DAC
int HeliosDac::HeliosDacIdnDevice::GetFirmwareVersion()
{
	return HELIOS_ERROR_NOT_SUPPORTED; // TODO

	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	return firmwareVersion;
}

// Gets name of DAC (populates name with max 32 characters).
int HeliosDac::HeliosDacIdnDevice::GetName(char* dacName)
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	int length = context->name.length();
	if (length > 3) // Empty name has 3 chars
	{
		// Use name of IDN service
		if (length > 31)
			length = 31;
		memcpy(name, context->name.c_str(), length + 1);
	}
	else
	{
		// Use IP address
		char ip[32];
		inet_ntop(AF_INET, &context->serverSockAddr.sin_addr.s_addr, ip, 32);
		memcpy(name, "IDN: ", 6);
		memcpy(name + 5, ip, 17);
	}
	name[31] = 0; // Just in case

	memcpy(dacName, name, 31);

	return HELIOS_SUCCESS;
}

//Set shutter level of DAC
//Value 1 = shutter open, value 0 = shutter closed
int HeliosDac::HeliosDacIdnDevice::SetShutter(bool level)
{
	return HELIOS_ERROR_NOT_SUPPORTED; // IDN handles shutter automatically
}

//Stops output of DAC
int HeliosDac::HeliosDacIdnDevice::Stop()
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	idnSendVoid(context);

	std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Send again after 10ms to make sure it stopped

	firstFrame = true;
	statusReadyTime = std::chrono::high_resolution_clock::now();

	if (idnSendVoid(context) == 0)
		return HELIOS_SUCCESS;
	else
		return HELIOS_ERROR_NETWORK;
}

//Sets persistent name of DAC
int HeliosDac::HeliosDacIdnDevice::SetName(char* name)
{
	return HELIOS_ERROR_NOT_SUPPORTED; // TODO
}

//Erases the firmware of the DAC, allowing it to be updated
int HeliosDac::HeliosDacIdnDevice::EraseFirmware()
{
	return HELIOS_ERROR_NOT_SUPPORTED;
}

HeliosDac::HeliosDacIdnDevice::~HeliosDacIdnDevice()
{
	closed = true;
	std::lock_guard<std::mutex>lock(frameLock); //wait until all threads have closed
	
	if (context != NULL)
	{
		idnSendClose(context);

		if (context->bufferPtr)
			delete context->bufferPtr;

		// Close socket
		if (context->fdSocket >= 0)
		{
#if defined(_WIN32) || defined(WIN32)
			closesocket(context->fdSocket);
#else
			close(context->fdSocket);
#endif
		}

		delete context;
		context = NULL;
	}
}
