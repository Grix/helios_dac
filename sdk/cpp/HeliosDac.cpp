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
	if (idnInited)
		plt_sockCleanup();
}

int HeliosDac::OpenDevices()
{
	if (inited)
		return (int)deviceList.size();

	// TODO: Make option to keep existing DACs in their current indexes, e.g only scan for changes. Currently this function only works after all DACs have been closed.

	unsigned int numDevices = _OpenUsbDevices();

	numDevices += _OpenIdnDevices();

	if (numDevices > 0)
		inited = true;

	return numDevices;
}


int HeliosDac::OpenDevicesOnlyUsb()
{
	if (inited)
		return (int)deviceList.size();

	// TODO: Make option to keep existing DACs in their current indexes, e.g only scan for changes. Currently this function only works after all DACs have been closed.

	unsigned int numDevices = _OpenUsbDevices();

	if (numDevices > 0)
		inited = true;

	return numDevices;
}


int HeliosDac::OpenDevicesOnlyNetwork()
{
	if (inited)
		return (int)deviceList.size();

	// TODO: Make option to keep existing DACs in their current indexes, e.g only scan for changes. Currently this function only works after all DACs have been closed.

	unsigned int numDevices = _OpenIdnDevices();

	if (numDevices > 0)
		inited = true;

	return numDevices;
}

// Internal function
int HeliosDac::_OpenUsbDevices()
{
	// Scanning for USB devices

	int result = libusb_init(NULL);
	if (result < 0)
		return result;

	libusb_set_option(NULL, LIBUSB_OPTION_LOG_LEVEL, LIBUSB_LOG_LEVEL);

	libusb_device** devs;
	ssize_t cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0)
		return (int)cnt;

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

	return numDevices;
}

// Internal function
int HeliosDac::_OpenIdnDevices()
{
	// Scanning for IDN (network) devices

	unsigned int numDevices = 0;

	plt_sockStartup();
	idnInited = true;
	std::vector<IDNCONTEXT*> idnContexts;

#ifndef WIN32 // Unix

	unsigned msTimeout = 600;
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
						bool unitIdMismatch = false;
						for (int j = 0; j < IDNSL_UNITID_LENGTH; j++)
						{
							if (serverInfo->unitID[j] != idnContexts[contextId]->unitId[j])
							{
								unitIdMismatch = true;
								break;
							}
						}
						if (idnContexts[contextId]->serverSockAddr.sin_addr.s_addr == serverInfo->addressTable[i].addr.s_addr || !unitIdMismatch)
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
	timeBeginPeriod(2);
	unsigned msTimeout = 600;
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
						bool unitIdMismatch = false;
						for (int j = 0; j < IDNSL_UNITID_LENGTH; j++)
						{
							if (serverInfo->unitID[j] != idnContexts[contextId]->unitId[j])
							{
								unitIdMismatch = true;
								break;
							}
						}
						if (idnContexts[contextId]->serverSockAddr.sin_addr.S_un.S_addr == serverInfo->addressTable[i].addr.S_un.S_addr || !unitIdMismatch)
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
							ctx->closed = true;
							ctx->packetNumFragments = 1;
							memcpy(ctx->unitId, serverInfo->unitID, IDNSL_UNITID_LENGTH);

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

	return numDevices;
}

int HeliosDac::CloseDevices()
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	std::lock_guard<std::mutex> lock(threadLock);
	inited = false;
	deviceList.clear(); // Various destructors will clean all devices

	libusb_exit(NULL);

	return HELIOS_SUCCESS;
}

int HeliosDac::WriteFrame(unsigned int devNum, unsigned int pps, std::uint8_t flags, HeliosPoint* points, unsigned int numOfPoints)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	if (points == NULL || numOfPoints == 0)
		return HELIOS_ERROR_NULL_POINTS;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();

	if (dev == NULL)
		return HELIOS_ERROR_INVALID_DEVNUM;

	return dev->SendFrame(pps, flags, points, numOfPoints);
}

int HeliosDac::WriteFrameHighResolution(unsigned int devNum, unsigned int pps, unsigned int flags, HeliosPointHighRes* points, unsigned int numOfPoints)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	if (points == NULL || numOfPoints == 0)
		return HELIOS_ERROR_NULL_POINTS;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();

	if (dev == NULL)
		return HELIOS_ERROR_INVALID_DEVNUM;

	return dev->SendFrameHighResolution(pps, flags, points, numOfPoints);
}

int HeliosDac::WriteFrameExtended(unsigned int devNum, unsigned int pps, unsigned int flags, HeliosPointExt* points, unsigned int numOfPoints)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	if (points == NULL || numOfPoints == 0)
		return HELIOS_ERROR_NULL_POINTS;

	std::unique_lock<std::mutex> lock(threadLock);
	HeliosDacDevice* dev = NULL;
	if (devNum < deviceList.size())
		dev = deviceList[devNum].get();
	lock.unlock();

	if (dev == NULL)
		return HELIOS_ERROR_INVALID_DEVNUM;

	return dev->SendFrameExtended(pps, flags, points, numOfPoints);
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

int HeliosDac::GetSupportsHigherResolutions(unsigned int devNum)
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

int HeliosDac::GetIsUsb(unsigned int devNum)
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

	return dev->GetIsUsb();
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

	frameBuffer = new std::uint8_t[HELIOS_MAX_POINTS * 7 + 5];
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

	// If pps is too low, try to duplicate frames to simulate a higher pps rather than failing
	bool freePoints = false;
	if (pps < GetMinSampleRate())
	{
		if (pps == 0)
			return HELIOS_ERROR_PPS_TOO_LOW;

		unsigned int samplingFactor = GetMinSampleRate() / pps + 1;
		if (numOfPoints * samplingFactor > GetMaxFrameSize())
			return HELIOS_ERROR_PPS_TOO_LOW;

		HeliosPoint* duplicatedPoints = new HeliosPoint[numOfPoints * samplingFactor];
		freePoints = true;

		unsigned int adjustedBufferPos = 0;
		for (unsigned int i = 0; i < numOfPoints; i++)
		{
			for (unsigned int j = 0; j < samplingFactor; j++)
			{
				duplicatedPoints[adjustedBufferPos++] = points[i];
			}
		}
		numOfPoints = numOfPoints * samplingFactor;
		pps = pps * samplingFactor;
		points = duplicatedPoints;
	}

	// If pps is too high or frame size too high, subsample frames to simulate a lower pps/size rather than failing
	unsigned int samplingFactor = 1;
	if (pps > GetMaxSampleRate() || numOfPoints > GetMaxFrameSize())
	{
		samplingFactor = pps / GetMaxSampleRate() + 1;
		if ((numOfPoints / GetMaxFrameSize() + 1) > samplingFactor)
			samplingFactor = numOfPoints / GetMaxFrameSize() + 1;

		pps = pps / samplingFactor;
		numOfPoints = numOfPoints / samplingFactor;

		if (pps < GetMinSampleRate())
			return HELIOS_ERROR_TOO_MANY_POINTS;
	}

	// This is a bug workaround, the mcu won't correctly receive transfers with these sizes
	unsigned int ppsActual = pps;
	unsigned int numOfPointsActual = numOfPoints;
	if ((((int)numOfPoints - 45) % 64) == 0)
	{
		numOfPointsActual--;
		//adjust pps to keep the same frame duration even with one less point
		ppsActual = (unsigned int)((pps * (double)numOfPointsActual / (double)numOfPoints) + 0.5);
	}

	unsigned int bufPos = 0;

	// Prepare frame buffer
	unsigned int loopLength = numOfPointsActual * samplingFactor;
	for (unsigned int i = 0; i < loopLength; i += samplingFactor)
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

	if (freePoints)
		delete points;

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

	// If pps is too low, try to duplicate frames to simulate a higher pps rather than failing
	bool freePoints = false;
	if (pps < GetMinSampleRate())
	{
		if (pps == 0)
			return HELIOS_ERROR_PPS_TOO_LOW;

		unsigned int samplingFactor = GetMinSampleRate() / pps + 1;
		if (numOfPoints * samplingFactor > GetMaxFrameSize())
			return HELIOS_ERROR_PPS_TOO_LOW;

		HeliosPointHighRes* duplicatedPoints = new HeliosPointHighRes[numOfPoints * samplingFactor];
		freePoints = true;

		unsigned int adjustedBufferPos = 0;
		for (unsigned int i = 0; i < numOfPoints; i++)
		{
			for (unsigned int j = 0; j < samplingFactor; j++)
			{
				duplicatedPoints[adjustedBufferPos++] = points[i];
			}
		}
		numOfPoints = numOfPoints * samplingFactor;
		pps = pps * samplingFactor;
		points = duplicatedPoints;
	}

	// If pps is too high or frame size too high, subsample frames to simulate a lower pps/size rather than failing
	unsigned int samplingFactor = 1;
	if (pps > GetMaxSampleRate() || numOfPoints > GetMaxFrameSize())
	{
		samplingFactor = pps / GetMaxSampleRate() + 1;
		if ((numOfPoints / GetMaxFrameSize() + 1) > samplingFactor)
			samplingFactor = numOfPoints / GetMaxFrameSize() + 1;

		pps = pps / samplingFactor;
		numOfPoints = numOfPoints / samplingFactor;

		if (pps < GetMinSampleRate())
			return HELIOS_ERROR_TOO_MANY_POINTS;
	}


	// This is a bug workaround, the mcu won't correctly receive transfers with these sizes
	unsigned int ppsActual = pps;
	unsigned int numOfPointsActual = numOfPoints;
	if ((((int)numOfPoints - 45) % 64) == 0)
	{
		numOfPointsActual--;
		// Adjust pps to keep the same frame duration even with one less point
		ppsActual = (unsigned int)((pps * (double)numOfPointsActual / (double)numOfPoints) + 0.5);
	}

	unsigned int bufPos = 0;

	// Prepare frame buffer
	// Converting to non-high-res for unsupported models
	unsigned int loopLength = numOfPointsActual * samplingFactor;
	for (unsigned int i = 0; i < loopLength; i += samplingFactor)
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

	if (freePoints)
		delete points;

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

	// If pps is too low, try to duplicate frames to simulate a higher pps rather than failing
	bool freePoints = false;
	if (pps < GetMinSampleRate())
	{
		if (pps == 0)
			return HELIOS_ERROR_PPS_TOO_LOW;

		unsigned int samplingFactor = GetMinSampleRate() / pps + 1;
		if (numOfPoints * samplingFactor > GetMaxFrameSize())
			return HELIOS_ERROR_PPS_TOO_LOW;

		HeliosPointExt* duplicatedPoints = new HeliosPointExt[numOfPoints * samplingFactor];
		freePoints = true;

		unsigned int adjustedBufferPos = 0;
		for (unsigned int i = 0; i < numOfPoints; i++)
		{
			for (unsigned int j = 0; j < samplingFactor; j++)
			{
				duplicatedPoints[adjustedBufferPos++] = points[i];
			}
		}
		numOfPoints = numOfPoints * samplingFactor;
		pps = pps * samplingFactor;
		points = duplicatedPoints;
	}

	// If pps is too high or frame size too high, subsample frames to simulate a lower pps/size rather than failing
	unsigned int samplingFactor = 1;
	if (pps > GetMaxSampleRate() || numOfPoints > GetMaxFrameSize())
	{
		samplingFactor = pps / GetMaxSampleRate() + 1;
		if ((numOfPoints / GetMaxFrameSize() + 1) > samplingFactor)
			samplingFactor = numOfPoints / GetMaxFrameSize() + 1;

		pps = pps / samplingFactor;
		numOfPoints = numOfPoints / samplingFactor;

		if (pps < GetMinSampleRate())
			return HELIOS_ERROR_TOO_MANY_POINTS;
	}


	// This is a bug workaround, the mcu won't correctly receive transfers with these sizes
	unsigned int ppsActual = pps;
	unsigned int numOfPointsActual = numOfPoints;
	if ((((int)numOfPoints - 45) % 64) == 0)
	{
		numOfPointsActual--;
		// Adjust pps to keep the same frame duration even with one less point
		ppsActual = (unsigned int)((pps * (double)numOfPointsActual / (double)numOfPoints) + 0.5);
	}

	unsigned int bufPos = 0;

	// Prepare frame buffer
	// Converting to non-high-res for unsupported models
	unsigned int loopLength = numOfPointsActual * samplingFactor;
	for (unsigned int i = 0; i < loopLength; i += samplingFactor)
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

	if (freePoints)
		delete points;

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
			plt_usleep(100);

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

//Gets name of DAC
int HeliosDac::HeliosDacUsbDevice::GetName(char* dacName)
{
	if (closed)
	{
		return HELIOS_ERROR_DEVICE_CLOSED;
	}

	int errorCode;

	std::lock_guard<std::mutex> lock(frameLock);

	for (int i = 0; i < 2; i++) //retry command if necessary
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
					ctrlBuffer5[31] = '\0'; // Just in case
					memcpy(name, &ctrlBuffer5[1], 32);
					memcpy(dacName, &ctrlBuffer5[1], 32);
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
		plt_usleep(100);
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
	plt_usleep(5);

	for (int i = 0; i < 32; i++)
		name[i] = 0;

	context->bufferLen = IDN_BUFFER_SIZE;
	context->bufferPtr = new uint8_t[IDN_BUFFER_SIZE];
	context->queuedBufferPtr = new uint8_t[IDN_BUFFER_SIZE];
	context->controlBufferPtr = new uint8_t[200];
	context->startTime = plt_getMonoTimeUS();

#if defined(_WIN32) || defined(WIN32)

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
	context->fdSocket = plt_sockOpen(AF_INET, SOCK_DGRAM, 0);
	if (context->fdSocket < 0)
	{
		logError("socket() error when initing IDN device connection: %d", plt_sockGetLastError());

		return;
	}

	// Ensure UDP socket buffer size is big enough. No longer required after switching to wave mode.
/*#if defined(_WIN32) || defined(WIN32)
	DWORD bufferSize = 0xFFFF;
	int res = setsockopt(context->fdSocket, SOL_SOCKET, SO_SNDBUF, (const char*)&bufferSize, sizeof(bufferSize));
#else
	int bufferSize = 0xFFFF;
	int res = setsockopt(context->fdSocket, SOL_SOCKET, SO_SNDBUF, (const void*)&bufferSize, sizeof(bufferSize));
#endif
	if (res != 0)
	{
		logError("Error setting max UDP buffer size for IDN device: %d", plt_sockGetLastError());
		//return;
	}
	*/

	managementSocketAddr = { 0 };

	managementSocketAddr.sin_family = AF_INET;
	managementSocketAddr.sin_port = htons(MANAGEMENT_PORT);
	managementSocketAddr.sin_addr = context->serverSockAddr.sin_addr;
	managementSocket = plt_sockOpen(AF_INET, SOCK_DGRAM, 0);
	if (managementSocket < 0)
	{
		fprintf(stderr, "managementSocket open failed (error: %d)", plt_sockGetLastError());
	}

#ifdef WIN32
	DWORD ms = 1000;
	setsockopt(managementSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&ms, sizeof(ms));
#else
	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	setsockopt(managementSocket, SOL_SOCKET, SO_RCVTIMEO, (const void*)&tv, sizeof(tv));
#endif

	closed = false;

	std::thread frameHandlerThread(&HeliosDac::HeliosDacIdnDevice::BackgroundFrameHandler, this);
	frameHandlerThread.detach();
}

// Queues up a raw frame buffer to be sent to the DAC. Legacy low-res point format.
// Returns 1 if success
int HeliosDac::HeliosDacIdnDevice::SendFrame(unsigned int pps, std::uint8_t flags, HeliosPoint* points, unsigned int numOfPoints)
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	std::lock_guard<std::mutex>lock(frameLock);

	if (context->frameReady)
		return HELIOS_ERROR_DEVICE_FRAME_READY;

	if (pps == 0)
		return HELIOS_ERROR_PPS_TOO_LOW;

	// If pps is too low or frame too small, try to duplicate points to simulate a larger, slower frame rather than failing
	bool freePoints = false;
	if (pps < GetMinSampleRate() || numOfPoints < GetMinFrameSize())
	{
		if (pps == 0)
			return HELIOS_ERROR_PPS_TOO_LOW;

		unsigned int samplingFactor = GetMinSampleRate() / pps + 1;
		if ((GetMinFrameSize() / numOfPoints + 1) > samplingFactor)
			samplingFactor = GetMinFrameSize() / numOfPoints + 1;

		if (numOfPoints * samplingFactor > GetMaxFrameSize(XYRGBI_SAMPLE_SIZE))
			return HELIOS_ERROR_PPS_TOO_LOW;
		else if (pps * samplingFactor > GetMaxSampleRate())
			return HELIOS_ERROR_FRAME_TOO_SMALL;

		HeliosPoint* duplicatedPoints = new HeliosPoint[numOfPoints * samplingFactor];
		freePoints = true;

		unsigned int adjustedBufferPos = 0;
		for (unsigned int i = 0; i < numOfPoints; i++)
		{
			for (unsigned int j = 0; j < samplingFactor; j++)
			{
				duplicatedPoints[adjustedBufferPos++] = points[i];
			}
		}
		numOfPoints = numOfPoints * samplingFactor;
		pps = pps * samplingFactor;
		points = duplicatedPoints;
	}

	// If pps is too high or frame size too high, subsample frames to simulate a lower pps/size rather than failing
	unsigned int samplingFactor = 1;
	if (pps > GetMaxSampleRate() || numOfPoints > GetMaxFrameSize(XYRGBI_SAMPLE_SIZE))
	{
		samplingFactor = pps / GetMaxSampleRate() + 1;
		if ((numOfPoints / GetMaxFrameSize(XYRGBI_SAMPLE_SIZE) + 1) > samplingFactor)
			samplingFactor = numOfPoints / GetMaxFrameSize(XYRGBI_SAMPLE_SIZE) + 1;

		pps = pps / samplingFactor;
		numOfPoints = numOfPoints / samplingFactor;

		if (pps < GetMinSampleRate())
			return HELIOS_ERROR_TOO_MANY_POINTS;
	}

	if (idnOpenFrameXYRGBI(context, false))
		return false;

	context->queuedFrameScanSpeed = pps;
	//context->jitterFreeFlag = (flags & HELIOS_FLAGS_SINGLE_MODE) != 0;

	unsigned int loopLength = numOfPoints * samplingFactor;
	for (unsigned int i = 0; i < loopLength; i += samplingFactor)
	{
		if (idnPutSampleXYRGBI(context, (points[i].x << 4) - 0x8000, (points[i].y << 4) - 0x8000, points[i].r, points[i].g, points[i].b, points[i].i))
			return false;
	}

	if (freePoints)
		delete points;

	context->frameReady = true;
	firstFrame = false;

	return HELIOS_SUCCESS;
	/*if ((flags & HELIOS_FLAGS_DONT_BLOCK) != 0)
	{
		context->frameReady = true;
		return HELIOS_SUCCESS;
	}
	else
	{
		return DoFrame();
	}*/
}

// Queues up a raw frame buffer to be sent to the DAC. Modern high-res point format.
// Returns 1 if success
int HeliosDac::HeliosDacIdnDevice::SendFrameHighResolution(unsigned int pps, std::uint8_t flags, HeliosPointHighRes* points, unsigned int numOfPoints)
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	std::lock_guard<std::mutex>lock(frameLock);

	if (context->frameReady)
		return HELIOS_ERROR_DEVICE_FRAME_READY;

	if (pps == 0)
		return HELIOS_ERROR_PPS_TOO_LOW;

	// If pps is too low or frame too small, try to duplicate points to simulate a larger, slower frame rather than failing
	bool freePoints = false;
	if (pps < GetMinSampleRate() || numOfPoints < GetMinFrameSize())
	{
		if (pps == 0)
			return HELIOS_ERROR_PPS_TOO_LOW;

		unsigned int samplingFactor = GetMinSampleRate() / pps + 1;
		if ((GetMinFrameSize() / numOfPoints + 1) > samplingFactor)
			samplingFactor = GetMinFrameSize() / numOfPoints + 1;

		if (numOfPoints * samplingFactor > GetMaxFrameSize(XYRGB_HIGHRES_SAMPLE_SIZE))
			return HELIOS_ERROR_PPS_TOO_LOW;
		else if (pps * samplingFactor > GetMaxSampleRate())
			return HELIOS_ERROR_FRAME_TOO_SMALL;

		HeliosPointHighRes* duplicatedPoints = new HeliosPointHighRes[numOfPoints * samplingFactor];
		freePoints = true;

		unsigned int adjustedBufferPos = 0;
		for (unsigned int i = 0; i < numOfPoints; i++)
		{
			for (unsigned int j = 0; j < samplingFactor; j++)
			{
				duplicatedPoints[adjustedBufferPos++] = points[i];
			}
		}
		numOfPoints = numOfPoints * samplingFactor;
		pps = pps * samplingFactor;
		points = duplicatedPoints;
	}

	// If pps is too high or frame size too high, subsample frames to simulate a lower pps/size rather than failing
	unsigned int samplingFactor = 1;
	if (pps > GetMaxSampleRate() || numOfPoints > GetMaxFrameSize(XYRGB_HIGHRES_SAMPLE_SIZE))
	{
		samplingFactor = pps / GetMaxSampleRate() + 1;
		if ((numOfPoints / GetMaxFrameSize(XYRGB_HIGHRES_SAMPLE_SIZE) + 1) > samplingFactor)
			samplingFactor = numOfPoints / GetMaxFrameSize(XYRGB_HIGHRES_SAMPLE_SIZE) + 1;

		pps = pps / samplingFactor;
		numOfPoints = numOfPoints / samplingFactor;

		if (pps < GetMinSampleRate())
			return HELIOS_ERROR_TOO_MANY_POINTS;
	}

	if (idnOpenFrameHighResXYRGB(context, false))
		return false;

	context->queuedFrameScanSpeed = pps;
	//context->jitterFreeFlag = (flags & HELIOS_FLAGS_SINGLE_MODE) != 0;

	unsigned int loopLength = numOfPoints * samplingFactor;
	for (unsigned int i = 0; i < loopLength; i += samplingFactor)
	{
		if (idnPutSampleHighResXYRGB(context, points[i].x - 0x8000, points[i].y - 0x8000, points[i].r, points[i].g, points[i].b))
			return false;
	}

	if (freePoints)
		delete points;

	context->frameReady = true;
	firstFrame = false;

	return HELIOS_SUCCESS;
}


// Queues up a raw frame buffer to be sent to the DAC. Extended point format with optional user1-4 channels.
// Returns 1 if success
int HeliosDac::HeliosDacIdnDevice::SendFrameExtended(unsigned int pps, std::uint8_t flags, HeliosPointExt* points, unsigned int numOfPoints)
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	std::lock_guard<std::mutex>lock(frameLock);

	if (context->frameReady)
		return HELIOS_ERROR_DEVICE_FRAME_READY;

	if (pps == 0)
		return HELIOS_ERROR_PPS_TOO_LOW;

	// If pps is too low or frame too small, try to duplicate points to simulate a larger, slower frame rather than failing
	bool freePoints = false;
	if (pps < GetMinSampleRate() || numOfPoints < GetMinFrameSize())
	{
		if (pps == 0)
			return HELIOS_ERROR_PPS_TOO_LOW;

		unsigned int samplingFactor = GetMinSampleRate() / pps + 1;
		if ((GetMinFrameSize() / numOfPoints + 1) > samplingFactor)
			samplingFactor = GetMinFrameSize() / numOfPoints + 1;

		if (numOfPoints * samplingFactor > GetMaxFrameSize(EXTENDED_SAMPLE_SIZE))
			return HELIOS_ERROR_PPS_TOO_LOW;
		else if (pps * samplingFactor > GetMaxSampleRate())
			return HELIOS_ERROR_FRAME_TOO_SMALL;

		HeliosPointExt* duplicatedPoints = new HeliosPointExt[numOfPoints * samplingFactor];
		freePoints = true;

		unsigned int adjustedBufferPos = 0;
		for (unsigned int i = 0; i < numOfPoints; i++)
		{
			for (unsigned int j = 0; j < samplingFactor; j++)
			{
				duplicatedPoints[adjustedBufferPos++] = points[i];
			}
		}
		numOfPoints = numOfPoints * samplingFactor;
		pps = pps * samplingFactor;
		points = duplicatedPoints;
	}

	// If pps is too high or frame size too high, subsample frames to simulate a lower pps/size rather than failing
	unsigned int samplingFactor = 1;
	if (pps > GetMaxSampleRate() || numOfPoints > GetMaxFrameSize(EXTENDED_SAMPLE_SIZE))
	{
		samplingFactor = pps / GetMaxSampleRate() + 1;
		if ((numOfPoints / GetMaxFrameSize(EXTENDED_SAMPLE_SIZE) + 1) > samplingFactor)
			samplingFactor = numOfPoints / GetMaxFrameSize(EXTENDED_SAMPLE_SIZE) + 1;

		pps = pps / samplingFactor;
		numOfPoints = numOfPoints / samplingFactor;

		if (pps < GetMinSampleRate())
			return HELIOS_ERROR_TOO_MANY_POINTS;
	}

	if (idnOpenFrameExtended(context, false))
		return false;

	context->queuedFrameScanSpeed = pps;
	//context->jitterFreeFlag = (flags & HELIOS_FLAGS_SINGLE_MODE) != 0;

	unsigned int loopLength = numOfPoints * samplingFactor;
	for (unsigned int i = 0; i < loopLength; i += samplingFactor)
	{
		if (idnPutSampleExtended(context, (int16_t)(points[i].x - 0x8000), (int16_t)(points[i].y - 0x8000), points[i].r, points[i].g, points[i].b, points[i].i, points[i].user1, points[i].user2, points[i].user3, points[i].user4))
			return false;
	}

	if (freePoints)
		delete points;

	context->frameReady = true;
	firstFrame = false;

	return HELIOS_SUCCESS;
}



// Gets status of DAC, 1 means DAC is ready to receive frame, 0 means it's not
int HeliosDac::HeliosDacIdnDevice::GetStatus()
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	std::lock_guard<std::mutex>lock(frameLock);

	if (context->frameReady)// || (plt_getMonoTimeUS() < (statusReadyTime - bufferTimeMs * 1000)))
	{
		 // Simulate a small delay to mimic behavior of USB device, for backwards compatibility
		if (!useBusyWaiting)
			plt_usleep(50);
		else
		{
			auto then = std::chrono::steady_clock::now() + std::chrono::microseconds(100);
			while (std::chrono::steady_clock::now() < then)
				std::this_thread::yield();
		}
		return false;
	}

	return true; // No true feedback in IDN
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
void HeliosDac::HeliosDacIdnDevice::BackgroundFrameHandler()
{
	while (!closed)
	{
		// This sleep timer is not entirely accurate, as any sleep function. 
		// If you want lower jitter and thus latency, you can set useBusyWaiting to true, but this ravages the CPU time
		uint64_t now = plt_getMonoTimeUS();

		if (context->frameTimestamp == 0)
			context->frameTimestamp = now;

		long timeLeft = context->frameTimestamp - now;
		if (timeLeft <= 0 && !firstFrame)
		{
			timeLeft = 0;
			numLateWaits++;

			if (numLateWaits > 10 && context->packetNumFragments < 6)
			{
				context->packetNumFragments++; // Increase max UDP packet size to have better sleep time error margins.
				printf("IDN - NB: Increased max UDP packet size multiplier to %d to increase sleep error margin.\n", context->packetNumFragments);
				numLateWaits = -30;
			}
				
		}
		else
		{
			numLateWaits--;
			if (numLateWaits < -30)
				numLateWaits = -30;
		}

		if (!useBusyWaiting)
		{
			if (timeLeft > 0)
				plt_usleep(timeLeft);
		}
		else
		{
			while (plt_getMonoTimeUS() < context->frameTimestamp)
			{
				auto then = std::chrono::steady_clock::now() + std::chrono::microseconds(100);
				while (std::chrono::steady_clock::now() < then)
					std::this_thread::yield();
			}
		}

		if (closed)
			return;

		#ifdef _DEBUG
			uint64_t sleepError = (plt_getMonoTimeUS() - now) - timeLeft;
			context->averageSleepError = (context->averageSleepError * NUM_SLEEP_ERROR_SAMPLES + sleepError) / (NUM_SLEEP_ERROR_SAMPLES + 1);
			//printf("IDN timing: Time now: %d, left: %d, sleep err: %d\n", now, timeLeft, context->averageSleepError);
		#endif

		DoFrame();
	}
}


// Gets firmware version of DAC
int HeliosDac::HeliosDacIdnDevice::GetFirmwareVersion()
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	if (firmwareVersion > 0)
		return firmwareVersion;

	char buffer[20] = { (char)0xE5, (char)0x2 };
	int sentBytes = 0;
	sentBytes = sendto(managementSocket, buffer, 2, 0, (const sockaddr*)&managementSocketAddr, sizeof(managementSocketAddr));

	if (sentBytes != 2)
	{
		int error = plt_sockGetLastError();
		printf("Failed to send command for firmware check: %d\n", error);
		return HELIOS_ERROR_NETWORK;
	}

	struct sockaddr responseAddr;
	memcpy(&responseAddr, &managementSocketAddr, sizeof(managementSocketAddr));
	socklen_t responseAddrLength = sizeof(managementSocketAddr);

	int numBytes = recvfrom(managementSocket, buffer, sizeof(buffer), 0, &responseAddr, &responseAddrLength);
	if (numBytes > 3)
	{
		if (buffer[0] == (char)0xE6 && buffer[1] == (char)0x2)
		{
			buffer[numBytes - 1] = '\0'; // Safety
			int major = 0;
			int minor = 0;
			int patch = 0;
#ifdef WIN32
			if (sscanf_s(buffer + 2, "%d.%d.%d", &major, &minor, &patch) == 3)
#else
			if (sscanf(buffer + 2, "%d.%d.%d", &major, &minor, &patch) == 3)
#endif
			{
				firmwareVersion = major * 10000 + minor * 100 + patch;
				return firmwareVersion;
			}
			else
				return HELIOS_ERROR_NOT_SUPPORTED;
		}
		else
			return HELIOS_ERROR_NOT_SUPPORTED;
	}
	else
	{
		int error = plt_sockGetLastError();
		printf("Failed to receive response for firmware check: %d\n", error);
		return HELIOS_ERROR_NOT_SUPPORTED;
	}

	return firmwareVersion;
}

// Gets name of DAC (populates name with max 32 bytes).
int HeliosDac::HeliosDacIdnDevice::GetName(char* dacName)
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	size_t length = context->name.length();
	if (length > 3) // Empty name has 3 chars
	{
		// Use name of IDN service
		char* idnName = new char[length + 1];
#ifdef WIN32
		strcpy_s(idnName, length + 1, context->name.c_str());
#else
		strcpy(idnName, context->name.c_str());
#endif
		if (length > 31)
			idnName[31] = '\0';
		memcpy(name, idnName, length + 1);
	}
	else
	{
		// Use IP address
		char ip[32]{ 0 };
		inet_ntop(AF_INET, &context->serverSockAddr.sin_addr.s_addr, ip, 32);
		memcpy(name, "IDN: ", 6);
		memcpy(name + 5, ip, 17);
	}
	name[31] = 0; // Just in case

	memcpy(dacName, name, 32);

	return HELIOS_SUCCESS;
}

// Set shutter level of DAC
// Value 1 = shutter open, value 0 = shutter closed
int HeliosDac::HeliosDacIdnDevice::SetShutter(bool level)
{
	return HELIOS_SUCCESS; // IDN handles shutter automatically
}

// Stops output of DAC
int HeliosDac::HeliosDacIdnDevice::Stop()
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	std::lock_guard<std::mutex>lock(frameLock);

	context->frameReady = false;

	/*HeliosPoint blankFrame[20];
	for (int i = 0; i < 20; i++)
	{
		blankFrame->x = 0x800;
		blankFrame->y = 0x800;
		blankFrame->r = 0;
		blankFrame->g = 0;
		blankFrame->b = 0;
		blankFrame->i = 0;
	}
	SendFrame(1000, HELIOS_FLAGS_DEFAULT, blankFrame, 20);*/

	firstFrame = true;

	if (idnSendClose(context) == 0)
		return HELIOS_SUCCESS;
	else
		return HELIOS_ERROR_NETWORK;
}

// Sets persistent name of DAC
int HeliosDac::HeliosDacIdnDevice::SetName(char* name)
{
	if (closed)
		return HELIOS_ERROR_DEVICE_CLOSED;

	char buffer[35] = { (char)0xE5, (char)0x3 };
#ifdef WIN32
	strcpy_s(buffer + 2, 33, name);
#else
	strcpy(buffer + 2, name);
#endif
	buffer[22] = '\0'; // Safety
	int sentBytes = 0;
	sentBytes = sendto(managementSocket, buffer, 22, 0, (const sockaddr*)&managementSocketAddr, sizeof(managementSocketAddr));

	if (sentBytes != 22)
	{
		int error = plt_sockGetLastError();
		printf("Failed to send command for setting name: %d\n", error);
		return HELIOS_ERROR_NETWORK;
	}

	struct sockaddr responseAddr;
	memcpy(&responseAddr, &managementSocketAddr, sizeof(managementSocketAddr));
	socklen_t responseAddrLength = sizeof(managementSocketAddr);

	int numBytes = recvfrom(managementSocket, buffer, sizeof(buffer), 0, &responseAddr, &responseAddrLength);
	if (numBytes >= 2)
	{
		if (buffer[0] == (char)0xE6 && buffer[1] == (char)0x3)
		{
			return HELIOS_SUCCESS;
		}
	}
	else
	{
		int error = plt_sockGetLastError();
		printf("Failed to receive response for set name command: %d\n", error);
		return HELIOS_ERROR_NOT_SUPPORTED;
	}

	return HELIOS_ERROR_NOT_SUPPORTED;
}

// Erases the firmware of the DAC, allowing it to be updated
int HeliosDac::HeliosDacIdnDevice::EraseFirmware()
{
	return HELIOS_ERROR_NOT_SUPPORTED;
}

HeliosDac::HeliosDacIdnDevice::~HeliosDacIdnDevice()
{
	Stop();

	closed = true;
	std::lock_guard<std::mutex>lock(frameLock); // Wait until all threads have closed

	if (context != NULL)
	{
		if (context->bufferPtr)
			delete context->bufferPtr;

		// Close socket
		if (context->fdSocket >= 0)
		{
			plt_sockClose(context->fdSocket);
		}

		delete context;
		context = NULL;
	}

	if (managementSocket >= 0)
	{
		if (plt_sockClose(managementSocket))
			fprintf(stderr, "close() failed (error: %d)", plt_sockGetLastError());
		managementSocket = -1;
	}
}
