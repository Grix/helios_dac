//Header for lower level Helios DAC functions. See HeliosDacAPI.h or HeliosDacClass.h instead for top level functions

#pragma once

#include <stdint.h>
#include "libusb.h"
#include <thread>
#include <mutex>
#include <vector>
#include <memory>

#define HELIOS_SDK_VERSION	5

#define HELIOS_MAX_POINTS	0x1000
#define HELIOS_MAX_RATE		0xFFFF
#define HELIOS_MIN_RATE		7

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

class HeliosDac
{
public:

	HeliosDac();
	~HeliosDac();
	int OpenDevices();
	int GetDeviceCount();
	int CloseDevices();
	int GetStatus(int devNum);
	int GetFirmwareVersion(int devNum);
	char* GetName(int devNum);
	int SendControl(int devNum, uint8_t* bufferAddress, int length);
	int GetControlResponse(int devNum, uint8_t* bufferAddress);
	int SendFrame(int devNum, uint8_t* bufferAddress, int bufferSize);

private:

	class HeliosDacDevice
	{
	public:

		HeliosDacDevice(libusb_device_handle*);
		~HeliosDacDevice();
		int GetStatus();
		int GetFirmwareVersion();
		char* GetName();
		int SendControl(uint8_t* bufferAddress, int length);
		int GetControlResponse(uint8_t* bufferAddress);
		int SendFrame(uint8_t* bufferAddress, int bufferSize);
		int CloseDevice();

	private:

		void WaitForStatus();
		void InterruptTransferHandler();

		struct libusb_transfer* interruptTransfer = NULL;
		struct libusb_device_handle* usbHandle;
		std::unique_ptr<std::mutex> threadLock;
		bool status = 0;
		int firmwareVersion = 0;
		char name[32];
		bool closed = true;
		bool inited = false;
		bool waitingForStatus = false;
	};

	std::vector<std::unique_ptr<HeliosDacDevice>> deviceList;
	std::mutex threadLock;
	bool inited = false;
};

void LIBUSB_CALL HeliosInterruptTransferHandlerWrapper(struct libusb_transfer*);