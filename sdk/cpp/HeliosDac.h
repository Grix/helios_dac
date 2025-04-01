/*
SDK for Helios Laser DAC class
By Gitle Mikkelsen
gitlem@gmail.com
MIT License

Dependencies:
Libusb 1.0 (GNU Lesser General Public License, see libusb.h)

Standard: C++14
git repo: https://github.com/Grix/helios_dac.git

BASIC USAGE:
1.	Call OpenDevices() to scan and open devices, returns number of available devices.
2.	To send a new frame, first call GetStatus(). The status should be polled until it returns ready. It can and sometimes will fail to return ready on the first try.
3.  When GetStatus() has returned ready (1), then you can call one of the WriteFrame*() functions with image data, to output a frame.
4.  Repeat steps 2-3 continuously while you have data to output.
5.  To stop output, use Stop(). To restart output you must send a new frame as described above.
6.	When the DAC(s) are no longer needed, free the connections using CloseDevices().

More more information on all functions, see their declarations below. There is also an example C++ app that outputs a simple animation in the Github repo.
Unless otherwise specified, functions return a negative error code on failure.

*/

#pragma once

#define _WINSOCKAPI_   // Prevent inclusion of winsock.h in windows.h from libusb.h
#include "libusb.h"
#include "idn/idn.h"
#include "idn/idnServerList.h"
#include <cstring>
#include <cstdint>
#include <thread>
#include <mutex>
#include <vector>
#include <memory>
#include <chrono>
#include <algorithm>
#include <queue>
#ifdef WIN32
#pragma comment(lib, "winmm.lib")
#endif

#define HELIOS_SDK_VERSION	11

// Frame limits
// For original USB model
#define HELIOS_MAX_POINTS	0xFFF
#define HELIOS_MAX_PPS		0xFFFF
#define HELIOS_MIN_PPS		7
// For IDN, max points depend on the complexity of those points
// In theory, many of these limits could be improved, by smarter PPS calculation etc, but I keep it simple to minimize compatibility problems.
#define HELIOS_MAX_POINTS_IDN	0x2000
#define IDN_BUFFER_SIZE			(HELIOS_MAX_POINTS_IDN*EXTENDED_SAMPLE_SIZE+200)
#define HELIOS_MAX_PPS_IDN		100000
#define HELIOS_MIN_PPS_IDN		HELIOS_MIN_PPS // 7

// Default return value of functions
#define HELIOS_SUCCESS		1	

// Functions return negative values if something went wrong:

// Attempted to perform an action before calling OpenDevices().
#define HELIOS_ERROR_NOT_INITIALIZED	-1

// Attempted to perform an action with an invalid device number.
#define HELIOS_ERROR_INVALID_DEVNUM		-2

// WriteFrame() called with null pointer to points or number of points being zero.
#define HELIOS_ERROR_NULL_POINTS		-3

// WriteFrame() called with a frame containing too many points.
#define HELIOS_ERROR_TOO_MANY_POINTS	-4

// WriteFrame() called with pps higher than maximum allowed.
#define HELIOS_ERROR_PPS_TOO_HIGH		-5

// WriteFrame() called with pps lower than minimum allowed.
#define HELIOS_ERROR_PPS_TOO_LOW		-6

// WriteFrame() called with too few points
#define HELIOS_ERROR_FRAME_TOO_SMALL	-7

// Errors from the HeliosDacDevice class begin at -1000:

// Attempted to perform an operation on a closed DAC device.
#define HELIOS_ERROR_DEVICE_CLOSED			-1000

// Attempted to send a new frame with HELIOS_FLAGS_DONT_BLOCK before previous frame has completed transfer.
#define HELIOS_ERROR_DEVICE_FRAME_READY		-1001

// Operation failed because SendControl() failed (if operation failed because of libusb_interrupt_transfer failure, the error code will be a libusb error instead).
#define HELIOS_ERROR_DEVICE_SEND_CONTROL	-1002

// Received an unexpected result from a call to SendControl().
#define HELIOS_ERROR_DEVICE_RESULT			-1003

// Attempted to call SendControl() with a null buffer pointer.
#define HELIOS_ERROR_DEVICE_NULL_BUFFER		-1004

// Attempted to call SendControl() with a control signal that is too long.
#define HELIOS_ERROR_DEVICE_SIGNAL_TOO_LONG	-1005

// Attempted to call a function that isn't supported for this particular DAC model (for example SetShutter on network DACs, since they handle shutter logic automatically instead of manually).
#define HELIOS_ERROR_NOT_SUPPORTED			-1006

// Error during sending network packet for IDN DACs. See console output for more information, or errno on Unix or WSAGetLastError() on Windows.
#define HELIOS_ERROR_NETWORK				-1007

// Errors from libusb are the libusb error code added to -5000. See libusb.h for libusb error codes.
#define HELIOS_ERROR_LIBUSB_BASE			-5000

// ---------------------------------

// Bitmask flags used in flags parameter for WriteFrame*(). Can be OR'ed together to enable multiple flags:

// Written frame should start playing immediately, even if previously submitted frames are queued up in the frame buffer.
// NB: This flag is not supported by network-enabled DACs and is thus considered deprecated.
#define HELIOS_FLAGS_START_IMMEDIATELY	(1 << 0)

// Written frame should only be played exactly once, instead of being looped indefinitely if no more frames are written after this one.
// NB: This flag is not yet supported on network (IDN) DACs, they always play the frame only once. Therefore, it is recommended to always 
// use this flag, and instead implement your own frame looping system if you need to repeat the frame.
#define HELIOS_FLAGS_SINGLE_MODE		(1 << 1)

// WriteFrame() should not block execution while the frame is transfered to the DAC, instead the transfer is processed a separate thread.
// NB: This flag is not applicable on network (IDN) DACs, they always schedule transfers in a separate thread since frames are split up internally.
#define HELIOS_FLAGS_DONT_BLOCK			(1 << 2)

// Default flags. This results in the same behavior for USB and network DACs (network DACs do not support all the flags of the USB models).
#define HELIOS_FLAGS_DEFAULT		(HELIOS_FLAGS_SINGLE_MODE)


// USB properties
#define HELIOS_VID	0x1209
#define HELIOS_PID	0xE500
#define EP_BULK_OUT	0x02
#define EP_BULK_IN	0x81
#define EP_INT_OUT	0x06
#define EP_INT_IN	0x83

#define MANAGEMENT_PORT 7355

#ifdef _DEBUG
#define LIBUSB_LOG_LEVEL LIBUSB_LOG_LEVEL_WARNING
#else
#define LIBUSB_LOG_LEVEL LIBUSB_LOG_LEVEL_NONE
#endif

// Point data structures
typedef struct
{
	std::uint16_t x; // Unsigned 12 bit (valid values from 0 to 0xFFF). X position.
	std::uint16_t y; // Unsigned 12 bit (valid values from 0 to 0xFFF). Y position.
	std::uint8_t r;	// Unsigned 8 bit (valid values from 0 to 0xFF). Red.
	std::uint8_t g;	// Unsigned 8 bit (valid values from 0 to 0xFF). Green.
	std::uint8_t b;	// Unsigned 8 bit (valid values from 0 to 0xFF). Blue.
	std::uint8_t i;	// Unsigned 8 bit (valid values from 0 to 0xFF). Intensity. Optional and should be set to max value if not used.
} HeliosPoint;

typedef struct
{
	std::uint16_t x; // Unsigned 16 bit (valid values from 0 to 0xFFFF). X position.
	std::uint16_t y; // Unsigned 16 bit (valid values from 0 to 0xFFFF). Y position.
	std::uint16_t r; // Unsigned 16 bit (valid values from 0 to 0xFFFF). Red.
	std::uint16_t g; // Unsigned 16 bit (valid values from 0 to 0xFFFF). Green.
	std::uint16_t b; // Unsigned 16 bit (valid values from 0 to 0xFFFF). Blue.
} HeliosPointHighRes;

typedef struct
{
	std::uint16_t x; // Unsigned 16 bit (valid values from 0 to 0xFFFF). X position.
	std::uint16_t y; // Unsigned 16 bit (valid values from 0 to 0xFFFF). Y position.
	std::uint16_t r; // Unsigned 16 bit (valid values from 0 to 0xFFFF). Red.
	std::uint16_t g; // Unsigned 16 bit (valid values from 0 to 0xFFFF). Green.
	std::uint16_t b; // Unsigned 16 bit (valid values from 0 to 0xFFFF). Blue.
	std::uint16_t i; // Unsigned 16 bit (valid values from 0 to 0xFFFF). Intensity. Optional and should be set to max value if not used.
	std::uint16_t user1; // Unsigned 16 bit (valid values from 0 to 0xFFFF). Deep blue or custom. Optional.
	std::uint16_t user2; // Unsigned 16 bit (valid values from 0 to 0xFFFF). Yellow or custom. Optional.
	std::uint16_t user3; // Unsigned 16 bit (valid values from 0 to 0xFFFF). Cyan, beam brush, or custom. Optional.
	std::uint16_t user4; // Unsigned 16 bit (valid values from 0 to 0xFFFF). Z position, X-prime, field change, or custom. Optional.
} HeliosPointExt;

class HeliosDac
{
public:

	HeliosDac();
	~HeliosDac();

	// Unless otherwise specified, functions return HELIOS_SUCCESS if OK, and some negative error code (see above) if something went wrong.

	// Initializes drivers, opens connection to all devices.
	// Returns number of available devices.
	// NB: To re-scan for newly connected DACs after this function has once been called before, you must first call CloseDevices().
	int OpenDevices();

	// Initializes drivers, opens connection to only USB devices (skips IDN/network scan).
	// Can be used if you have already implemented an IDN client separately.
	// Returns number of available devices.
	// NB: To re-scan for newly connected DACs after this function has once been called before, you must first call CloseDevices().
	int OpenDevicesOnlyUsb();

	// Initializes drivers, opens connection to only IDN network devices (skips USB scan).
	// Can be used if you have already implemented a Helios USB interface separately.
	// Returns number of available devices.
	// NB: To re-scan for newly connected DACs after this function has once been called before, you must first call CloseDevices().
	int OpenDevicesOnlyNetwork();

	// Closes and frees all devices.
	int CloseDevices();

	// Writes and outputs a frame to the speficied dac.
	// WriteFrame() uses the lightweight point structure designed for the original Helios DAC.
	// WriteFrameHighResolution() uses a higher resolution point structure supported by newer DAC models. If unsure, this one is recommended.
	// WriteFrameExtended() has additional optional channels and a higher resolution point structure supported by newer DAC models.
	// 
	// It is safe to call any of these functions even for DACs that don't support higher resolution data. In that case the data will automatically be converted (though at a slight performance cost).
	// NB: You should make frames large enough to account for transfer overheads and timing jitter. Recommended to have frames last 10 milliseconds or longer on average, generally speaking.
	// 
	// devNum: dac number (0 to n where n+1 is the return value from OpenDevices() ).
	// pps: rate of output in points per second.
	// flags: (If unsure, use HELIOS_FLAGS_DEFAULT)
	//	 Bit 0 (LSB) = if 1, start output immediately, instead of waiting for current frame (if there is one) to finish playing. 
	//			(NB: This flag does not apply to network DACs. For identical behavior of USB DACs, DISABLE this flag (set bit to 0).
	//	 Bit 1 = if 1, play frame only once, instead of repeating until another frame is written
	//			(NB: This flag does not apply to network DACs. For identical behavior of USB DACs, ENABLE this flag (set bit to 1).
	//   Bit 2 = if 1, don't let WriteFrame() block execution while waiting for the transfer to finish 
	//			(NB: then the function might return 1 even if the transfer fails)
	//			(NB: This flag does not apply to network DACs. For identical behavior of USB DACs, ENABLE this flag (set bit to 1).
	//	 Bit 3-7 = reserved
	// points: pointer to point data. See point structure declarations earlier in this document.
	// numOfPoints: number of points in the frame.
	int WriteFrame(unsigned int devNum, unsigned int pps, std::uint8_t flags, HeliosPoint* points, unsigned int numOfPoints);
	int WriteFrameHighResolution(unsigned int devNum, unsigned int pps, unsigned int flags, HeliosPointHighRes* points, unsigned int numOfPoints);
	int WriteFrameExtended(unsigned int devNum, unsigned int pps, unsigned int flags, HeliosPointExt* points, unsigned int numOfPoints);

	// Gets status of DAC, 1 means DAC is ready to receive frame, 0 means it is not.
	// You MUST poll this function until it returns true, before every call to WriteFrame*().
	int GetStatus(unsigned int devNum);

	// Gets name of DAC (populates name with at most 32 characters).
	int GetName(unsigned int devNum, char* name);

	// Sets name of DAC (Name must be max 20 characters long, or 21 bytes including null terminator).
	int SetName(unsigned int devNum, char* name);

	// Stops output of DAC until new frame is written (NB: blocks for 100ms).
	int Stop(unsigned int devNum);

	// Sets shutter level of DAC.
	// This is no longer strictly necessary to call, the library automatically opens the shutter when you write a frame.
	// Value 1 = shutter open, value 0 = shutter closed
	int SetShutter(unsigned int devNum, bool level);

	// Returns firmware version of DAC.
	// For Helios USB, the firmware version is just one simple integer, which is never higher than 255.
	// For Helios IDN DACs, the firmware version is an integer in this format: AABBCC, which corresponds to vAA.BB.CC. For example 10002 would be v1.0.2.
	// For non-Helios IDN DACs, this function may not work, as firmware version getting is not a part of the IDN spec. In that case, the function may block for around 0.5s and then return a negative number.
	int GetFirmwareVersion(unsigned int devNum);

	// Returns whether a specific DAC supports the higher resolutions color/postion data of new WriteFrameHighResolution() and WriteFrameExtended() functions. 
	// The Original Helios USB device does not, at least not all firmware versions. HeliosPRO / IDN devices supports it.
	// Note that it is safe to call these function even for DACs that don't support higher resolution data, in that case the data will automatically be converted (though at a performance cost).
	// Returns 1 if yes, 0 if no, and a negative number on error.
	int GetSupportsHigherResolutions(unsigned int devNum);

	// Returns whether a specific DAC is a USB Helios DAC (as opposed to an IDN network DAC).
	// Returns 1 if yes, 0 if no, and a negative number on error.
	int GetIsUsb(unsigned int devNum);

	// Sets debug log level in libusb.
	int SetLibusbDebugLogLevel(int logLevel);

	// Erase the firmware of the DAC, allowing it to be updated by accessing the SAM-BA bootloader. 
	// NB: For advanced use only, most software should never call this. 
	int EraseFirmware(unsigned int devNum);

private:

	// Base class for individual DAC, for internal use
	class HeliosDacDevice
	{

	public:

		virtual ~HeliosDacDevice() {}

		virtual int SendFrame(unsigned int pps, std::uint8_t flags, HeliosPoint* points, unsigned int numOfPoints) = 0;
		virtual int SendFrameHighResolution(unsigned int pps, std::uint8_t flags, HeliosPointHighRes* points, unsigned int numOfPoints) = 0;
		virtual int SendFrameExtended(unsigned int pps, std::uint8_t flags, HeliosPointExt* points, unsigned int numOfPoints) = 0;
		virtual int GetStatus() = 0;
		virtual int GetFirmwareVersion() = 0;
		virtual int GetName(char* name) = 0;
		virtual int SetName(char* name) = 0;
		virtual int GetSupportsHigherResolutions() = 0;
		virtual int GetIsUsb() = 0;
		virtual int SetShutter(bool level) = 0;
		virtual int Stop() = 0;
		virtual int EraseFirmware() = 0;

	};

	// Class for USB-connected Helios DACs, for internal use
	class HeliosDacUsbDevice : public HeliosDacDevice
	{
	public:

		HeliosDacUsbDevice(libusb_device_handle*);
		~HeliosDacUsbDevice();

		int SendFrame(unsigned int pps, std::uint8_t flags, HeliosPoint* points, unsigned int numOfPoints);
		int SendFrameHighResolution(unsigned int pps, std::uint8_t flags, HeliosPointHighRes* points, unsigned int numOfPoints);
		int SendFrameExtended(unsigned int pps, std::uint8_t flags, HeliosPointExt* points, unsigned int numOfPoints);
		int GetStatus();
		int GetSupportsHigherResolutions() { return 0; } // TODO read capabilities from DAC
		int GetIsUsb() { return 1; }
		int GetFirmwareVersion();
		int GetName(char* name);
		int SetName(char* name);
		int SetShutter(bool level);
		int Stop();
		int EraseFirmware();


	private:

		int DoFrame();
		void BackgroundFrameHandler();
		int SendControl(std::uint8_t* buffer, unsigned int bufferSize);

		unsigned int GetMaxSampleRate() { return HELIOS_MAX_PPS; } // TODO read exact capabilities from DAC
		unsigned int GetMinSampleRate() { return HELIOS_MIN_PPS; } // TODO read exact capabilities from DAC
		unsigned int GetMaxFrameSize() { return HELIOS_MAX_POINTS; } // TODO read exact capabilities from DAC

		struct libusb_transfer* interruptTransfer = NULL;
		struct libusb_device_handle* usbHandle;
		std::mutex frameLock;
		bool frameReady = false;
		int firmwareVersion = 0;
		char name[32];
		bool closed = true;
		std::uint8_t* frameBuffer;
		unsigned int frameBufferSize;
		int frameResult = -1;
		bool shutterIsOpen = false;
		int maxSampleRate = 0xffff;
		int minSampleRate = 7;
	};

	// Class for network (IDN) connected DACs such as HeliosPRO (but also work with other DACs supporting IDN), for internal use
	class HeliosDacIdnDevice : public HeliosDacDevice
	{
	public:

		HeliosDacIdnDevice(IDNCONTEXT* idnContext);
		~HeliosDacIdnDevice();

		int SendFrame(unsigned int pps, std::uint8_t flags, HeliosPoint* points, unsigned int numOfPoints);
		int SendFrameHighResolution(unsigned int pps, std::uint8_t flags, HeliosPointHighRes* points, unsigned int numOfPoints);
		int SendFrameExtended(unsigned int pps, std::uint8_t flags, HeliosPointExt* points, unsigned int numOfPoints);
		int GetStatus();
		int GetSupportsHigherResolutions() { return 1; }
		int GetIsUsb() { return 0; }
		int GetFirmwareVersion();
		int GetName(char* name);
		int SetName(char* name);
		int SetShutter(bool level);
		int Stop();
		int EraseFirmware();

	private:

		int DoFrame();
		void BackgroundFrameHandler();
		unsigned int GetMaxSampleRate() { return HELIOS_MAX_PPS_IDN; }
		unsigned int GetMinSampleRate() { return HELIOS_MIN_PPS_IDN; }
		unsigned int GetMaxFrameSize(unsigned int bytesPerPoint) { return ((IDN_BUFFER_SIZE - 100) / bytesPerPoint); }
		unsigned int GetMinFrameSize() { return 20; }

		IDNCONTEXT* context;
		int firmwareVersion = 0;
		char name[32];
		bool closed = true;
		bool useBusyWaiting = false;
		bool finishedClosing = false;

		int managementSocket = -1;
		sockaddr_in managementSocketAddr = { 0, 0, 0, 0 };
		std::mutex frameLock;
		int frameResult = -1;
		long numLateWaits = 0;

	};

	int _OpenUsbDevices();
	int _OpenIdnDevices();
	void _SortDeviceList();

	std::vector<std::unique_ptr<HeliosDacDevice>> deviceList;
	std::mutex threadLock;
	bool inited = false;
	bool idnInited = false;
};
