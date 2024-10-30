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
1.	Call OpenDevices() to open devices, returns number of available devices.
2.	To send a frame to the DAC, first call GetStatus(). The status should be polled until it returns ready.
	If the function returns ready (1), then you can call WriteFrame*().
3.  To stop output, use Stop(). To restart output you must send a new frame as described above.
4.	When the DAC is no longer needed, destroy the instance (destructors will free everything and close the connection)

More more information on all functions, see their declarations below.

When the DAC receives its first frame, it starts outputting it. When a second frame is sent to
the DAC while the first frame is being played, the second frame is stored in the DACs memory until the first frame
finishes playback, at which point the second, buffered frame will start playing. If the DAC finished playback of a frame
without having received and buffered a second frame, it will by default loop the first frame until a new frame is
received (but the flag HELIOS_FLAG_SINGLE_MODE will make it stop playback instead).
The GetStatus() function actually checks whether or not the buffer on the DAC is empty or full. If it is full, the DAC
cannot receive a new frame until the currently playing frame finishes, freeing up the buffer. This is not applicable
on IDN network DACs, they will always be ready to receive a new frame, but by default the GetStatus still simulates 
the time it would take for the IDN DAC to play the frame, to stay backwards compatible with programs that depend on
GetStatus() for timing purposes.
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

#define HELIOS_SDK_VERSION	10

#define HELIOS_MAX_POINTS 0x3FFC
#define HELIOS_MAX_PPS 100000
#define HELIOS_MIN_PPS 1
#define HELIOS_MAX_POINTS_OLD 0xFFF // For original USB model
#define HELIOS_MAX_PPS_OLD 0xFFFF // For original USB model
#define HELIOS_MIN_PPS_OLD 7 // For original USB model

#define HELIOS_SUCCESS		1	

// Functions return negative values if something went wrong	
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

// Errors from the HeliosDacDevice class begin at -1000
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
#define HELIOS_ERROR_LIBUSB_BASE		-5000

// Bitmask flags used in flags parameter for WriteFrame*(). Can be OR'ed together to enable multiple flags
// No flags defined.
#define HELIOS_FLAGS_DEFAULT			0
// Written frame should start playing immediately, even if previously submitted frames are queued up in the frame buffer.
// NB: This flag is NOT SUPPORTED by network-enabled DACs and is thus considered deprecated.
#define HELIOS_FLAGS_START_IMMEDIATELY	(1 << 0)
// Written frame should only be played exactly once, instead of being looped indefinitely if no more frames are written after this one.
#define HELIOS_FLAGS_SINGLE_MODE		(1 << 1)
// WriteFrame() should not block execution while the frame is transfered to the DAC, instead the transfer is processed a separate thread.
#define HELIOS_FLAGS_DONT_BLOCK			(1 << 2)
// For network-enabled DACs, there is no status feedback, so GetStatus() could in theory return true immediately. This flag makes it so.
// If the flag is NOT defined (default), then a timer simulates the time it would take the DAC to play the frame and makes GetStatus()
// return false during that time instead. This is done for compatibility reasons if your software depends on this feedback for timing.
#define HELIOS_FLAGS_DONT_SIMULATE_TIMING	(1 << 3)

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

	// Closes and frees all devices.
	int CloseDevices();

	// Writes and outputs a frame to the speficied dac, using the lightweight point structure designed for the original Helios DAC.
	// devNum: dac number (0 to n where n+1 is the return value from OpenDevices() ).
	// pps: rate of output in points per second.
	// flags: (default is 0)
	//	 Bit 0 (LSB) = if 1, start output immediately, instead of waiting for current frame (if there is one) to finish playing
	//	 Bit 1 = if 1, play frame only once, instead of repeating until another frame is written
	//   Bit 2 = if 1, don't let WriteFrame() block execution while waiting for the transfer to finish 
	//			(NB: then the function might return 1 even if the transfer fails)
	//   Bit 3 = IDN (Network) DACs do not provide an actual status feedback, so GetStatus() could in theory just return 1 all the time.
	//			 However, some programs may depends on the timing of the status signal, so by default an approximate status timing is simulated.
	//			 If this flag bit is 1, this timing simulation is disabled, and GetStatus() returns 1 as soon as it can.
	//	 Bit 4-7 = reserved
	// points: pointer to point data. See point structure declaration earlier in this document.
	// numOfPoints: number of points in the frame.
	int WriteFrame(unsigned int devNum, unsigned int pps, std::uint8_t flags, HeliosPoint* points, unsigned int numOfPoints);

	// Writes and outputs a frame to the speficied dac, using a higher resolution point structure supported by newer DAC models.
	// It is safe to call this function even for DACs that don't support higher resolution data. In that case the data will be converted (though at a slight performance cost).
	// devNum: dac number (0 to n, where n+1 is the return value from OpenDevices() ).
	// pps: rate of output in points per second.
	// flags: (default is 0)
	//	 Bit 0 (LSB) = if 1, start output immediately, instead of waiting for current frame (if there is one) to finish playing
	//	 Bit 1 = if 1, play frame only once, instead of repeating until another frame is written
	//   Bit 2 = if 1, don't let WriteFrame() block execution while waiting for the transfer to finish 
	//			(NB: then the function might return 1 even if the transfer fails)
	//   Bit 3 = IDN (Network) DACs do not provide an actual status feedback, so GetStatus() could in theory just return 1 all the time.
	//			 However, some programs may depends on the timing of the status signal, so by default an approximate status timing is simulated.
	//			 If this flag bit is 1, this timing simulation is disabled, and GetStatus() returns 1 as soon as it can.
	//	 Bit 4-7 = reserved
	// points: pointer to point data. See point structure declaration earlier in this document.
	// numOfPoints: number of points in the frame.
	int WriteFrameHighResolution(unsigned int devNum, unsigned int pps, unsigned int flags, HeliosPointHighRes* points, unsigned int numOfPoints);

	// Writes and outputs a frame to the speficied dac, with additional optional channels and a higher resolution point structure supported by newer DAC models.
	// It is safe to call this function even for DACs that don't support higher resolution data. In that case the data will be converted (though at a slight performance cost).
	// devNum: dac number (0 to n, where n+1 is the return value from OpenDevices() ).
	// pps: rate of output in points per second.
	// flags: (default is 0)
	//	 Bit 0 (LSB) = if 1, start output immediately, instead of waiting for current frame (if there is one) to finish playing
	//	 Bit 1 = if 1, play frame only once, instead of repeating until another frame is written
	//   Bit 2 = if 1, don't let WriteFrame() block execution while waiting for the transfer to finish 
	//			(NB: then the function might return 1 even if the transfer fails)
	//   Bit 3 = IDN (Network) DACs do not provide an actual status feedback, so GetStatus() could in theory just return 1 all the time.
	//			 However, some programs may depends on the timing of the status signal, so by default an approximate status timing is simulated.
	//			 If this flag bit is 1, this timing simulation is disabled, and GetStatus() returns 1 as soon as it can.
	//	 Bit 4-7 = reserved
	// points: pointer to point data. See point structure declaration earlier in this document.
	// numOfPoints: number of points in the frame.
	int WriteFrameExtended(unsigned int devNum, unsigned int pps, unsigned int flags, HeliosPointExt* points, unsigned int numOfPoints);

	// Gets status of DAC, 1 means DAC is ready to receive frame, 0 means it is not.
	int GetStatus(unsigned int devNum);

	// Gets name of DAC (populates name, with at most 32 characters).
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
	// For non-Helios IDN DACs, this function may not work, as firmware version getting is not a part of the IDN spec. In that case, the function may block for a second and then return a negative number.
	int GetFirmwareVersion(unsigned int devNum);

	// Returns whether a specific DAC supports the new WriteFrameHighResolution() and WriteFrameExtended() functions. 
	// The Original Helios USB device does not, at least not all firmware versions. HeliosPRO / IDN devices supports it.
	// Note that it is safe to call these function even for DACs that don't support higher resolution data, in that case the data will be converted (though at a performance cost).
	bool GetSupportsHigherResolutions(unsigned int devNum);

	// Gets the maximum point rate in pps (points per second) for this DAC. Can vary between USB and IDN devices.
	// Note that it is safe to write frames outside this limit, as the frame will get automatically subsampled (at a performance cost)
	int GetMaxSampleRate(unsigned int devNum);

	// Gets the minumum point rate in pps (points per second) for this DAC. Can vary between USB and IDN devices.
	// Note that it is safe to write frames outside this limit, as points will get automatically duplicated to increase pps (at a performance cost)
	int GetMinSampleRate(unsigned int devNum);
	
	// Gets the maximum number of points in one frame for this DAC. Can vary between USB and IDN devices.
	// Note that it is safe to write frames outside this limit, as the frame will get automatically subsampled (at a performance cost)
	int GetMaxFrameSize(unsigned int devNum);

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

		virtual int SendFrame(unsigned int pps, std::uint8_t flags, HeliosPoint* points, unsigned int numOfPoints) = 0;
		virtual int SendFrameHighResolution(unsigned int pps, std::uint8_t flags, HeliosPointHighRes* points, unsigned int numOfPoints) = 0;
		virtual int SendFrameExtended(unsigned int pps, std::uint8_t flags, HeliosPointExt* points, unsigned int numOfPoints) = 0;
		virtual int GetStatus() = 0;
		virtual bool GetSupportsHigherResolutions() = 0;
		virtual int GetFirmwareVersion() = 0;
		virtual int GetName(char* name) = 0;
		virtual int SetName(char* name) = 0;
		virtual int SetShutter(bool level) = 0;
		virtual int Stop() = 0;
		virtual unsigned int GetMaxSampleRate() = 0;
		virtual unsigned int GetMinSampleRate() = 0;
		virtual unsigned int GetMaxFrameSize() = 0;
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
		bool GetSupportsHigherResolutions() { return false; } // TODO read capabilities from DAC
		int GetFirmwareVersion();
		int GetName(char* name);
		int SetName(char* name);
		int SetShutter(bool level);
		int Stop();
		unsigned int GetMaxSampleRate() { return HELIOS_MAX_PPS_OLD; } // TODO read exact capabilities from DAC
		unsigned int GetMinSampleRate() { return HELIOS_MIN_PPS_OLD; } // TODO read exact capabilities from DAC
		unsigned int GetMaxFrameSize() { return HELIOS_MAX_POINTS_OLD; } // TODO read exact capabilities from DAC
		int EraseFirmware();


	private:

		int DoFrame();
		void BackgroundFrameHandler();
		int SendControl(std::uint8_t* buffer, unsigned int bufferSize);

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
		bool GetSupportsHigherResolutions() { return true; }
		int GetFirmwareVersion();
		int GetName(char* name);
		int SetName(char* name);
		int SetShutter(bool level);
		int Stop();
		unsigned int GetMaxSampleRate() { return HELIOS_MAX_PPS; } // TODO read exact capabilities from DAC
		unsigned int GetMinSampleRate() { return HELIOS_MIN_PPS; } // TODO read exact capabilities from DAC
		unsigned int GetMaxFrameSize() { return HELIOS_MAX_POINTS; } // TODO read exact capabilities from DAC
		int EraseFirmware();

	private:

		int DoFrame();
		void BackgroundFrameHandler();

		IDNCONTEXT* context;
		int firmwareVersion = 0;
		char name[32];
		bool closed = true;
		std::chrono::time_point<std::chrono::high_resolution_clock> statusReadyTime;
		bool firstFrame = true;
		int managementSocket = -1;
		sockaddr_in managementSocketAddr = { 0 };

		bool frameReady = false;
		std::mutex frameLock;
		int frameResult = -1;
	};

	std::vector<std::unique_ptr<HeliosDacDevice>> deviceList;
	std::mutex threadLock;
	bool inited = false;
	bool idnInited = false;
};
