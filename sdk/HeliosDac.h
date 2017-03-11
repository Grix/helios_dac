//Header for lower level Helios DAC functions. See HeliosDacAPI.h or HeliosDacClass.h instead for top level functions

#pragma once

#include "libusb.h"
#include <cstring>
#include <cstdint>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>
#include <chrono>
#include <future>

#define HELIOS_SDK_VERSION	5

#define HELIOS_MAX_POINTS	0x1000
#define HELIOS_MAX_RATE		0xFFFF
#define HELIOS_MIN_RATE		7

#define HELIOS_SUCCESS		1
#define HELIOS_ERROR		-1

#define HELIOS_FLAGS_DEFAULT			0
#define HELIOS_FLAGS_START_IMMEDIATELY	(1 << 1)
#define HELIOS_FLAGS_SINGLE_MODE		(1 << 2)

//usb properties
#define HELIOS_VID	0x1209
#define HELIOS_PID	0xE500
#define EP_BULK_OUT	0x02
#define EP_BULK_IN	0x81
#define EP_INT_OUT	0x06
#define EP_INT_IN	0x83

#ifdef _DEBUG
#define LIBUSB_LOG_LEVEL LIBUSB_LOG_LEVEL_WARNING
#else
#define LIBUSB_LOG_LEVEL LIBUSB_LOG_LEVEL_NONE
#endif

//point data structure
typedef struct
{
	std::uint16_t x; //12 bit (from 0 to 0xFFF)
	std::uint16_t y; //12 bit (from 0 to 0xFFF)
	std::uint8_t r;	//8 bit	(from 0 to 0xFF)
	std::uint8_t g;	//8 bit (from 0 to 0xFF)
	std::uint8_t b;	//8 bit (from 0 to 0xFF)
	std::uint8_t i;	//8 bit (from 0 to 0xFF)
} HeliosPoint;

class HeliosDac
{
public:

	HeliosDac();
	~HeliosDac();
	int OpenDevices();
	int GetDeviceCount();
	int CloseDevices();
	int GetStatus(unsigned int devNum);
	int GetFirmwareVersion(unsigned int devNum);
	char* GetName(unsigned int devNum);
	int SetName(unsigned int devNum, char* name);
	int SendFrame(unsigned int devNum, unsigned int pps, std::uint8_t flags, HeliosPoint* points, unsigned int numOfPoints);
	int Stop(unsigned int devNum);
	int SetShutter(unsigned int devNum, bool level);
	int EraseFirmware(unsigned int devNum);

private:

	class HeliosDacDevice
	{
	public:

		HeliosDacDevice(libusb_device_handle*);
		~HeliosDacDevice();
		int SendFrame(std::uint8_t* buffer, unsigned int bufferSize);
		int GetStatus();
		int GetFirmwareVersion();
		char* GetName();
		int SetName(char* name);
		int SetShutter(bool level);
		int Stop();
		int EraseFirmware();

	private:

		void DoFrame(std::uint8_t* buffer, unsigned int bufferSize);
		void InterruptTransferHandler();
		int SendControl(std::uint8_t* buffer, unsigned int bufferSize);

		struct libusb_transfer* interruptTransfer = NULL;
		struct libusb_device_handle* usbHandle;
		std::mutex frameLock;
		int firmwareVersion = 0;
		char name[32];
		bool closed = true;
	};

	std::vector<std::unique_ptr<HeliosDacDevice>> deviceList;
	std::mutex threadLock;
	bool inited = false;
};
