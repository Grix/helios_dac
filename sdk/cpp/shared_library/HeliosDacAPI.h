/*
Helios Laser DAC SDK shared library, HEADER
By Gitle Mikkelsen
gitlem@gmail.com

Dependencies:
Libusb 1.0 (GNU Lesser General Public License, see libusb.h)
HeliosDAC.cpp/h and its dependencies in the idn folder

Standard: C++14

This is the shared library extension of the Helios DAC SDK, used to produce a dynamic library file like .dll, .so or .dylib. 
This allows you to call the code from other languages than C++.
If such a file is not neccessary, you can simply use HeliosDAC.cpp/.h and the files in the idn subfolder directly in your 
source code, with no additional files or build steps needed.

BASIC USAGE:
1.	Call OpenDevices() to open devices, returns number of available devices.
2.	To send a new frame, first call GetStatus(). If the function returns ready (1),then you can call WriteFrame*().
	The status should be polled until it returns ready. It can and sometimes will fail to return ready on the first try.
3.  To stop output, use Stop(). To restart output you must send a new frame as described above.
4.	When the DAC is no longer needed, free it using CloseDevices()

More more information on all functions, see their declarations below. 
Unless otherwise specified, functions return a negative error code on failure.

The DAC is double-buffered. When it receives its first frame, it starts outputting it. When a second frame is sent to
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

#include "..\HeliosDac.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	#define HELIOS_EXPORT extern "C" __declspec (dllexport)
#else
	#define HELIOS_EXPORT extern "C"
#endif

#define STDCALL __stdcall

bool inited = false;
HeliosDac* dacController;
HeliosPointHighRes** ezAudDacFrameBuffer = 0;

// Unless otherwise specified, functions return a negative error code on failure and 1 on success.

// Initializes drivers, opens connection to all devices.
// Returns number of available devices.
// NB: To re-scan for newly connected DACs after this function has once been called before, you must first call CloseDevices()
HELIOS_EXPORT int OpenDevices();

// Initializes drivers, opens connection to only USB devices (skips IDN/network scan).
// Returns number of available devices.
// NB: To re-scan for newly connected DACs after this function has once been called before, you must first call CloseDevices()
HELIOS_EXPORT int OpenDevicesOnlyUsb();

// Gets status from the specified dac.
// Return 1 if ready to receive new frame, 0 if not, negative number if communcation failed
HELIOS_EXPORT int GetStatus(unsigned int dacNum);

// Writes and outputs a frame to the speficied dac, with the light-weight frame structure backwards compatible with the old Helios DAC library.
// dacNum: dac number (0 to n where n+1 is the return value from OpenDevices() )
// pps: rate of output in points per second
// flags: (default is 0)
//	 Bit 0 (LSB) = if true, start output immediately, instead of waiting for current frame (if there is one) to finish playing
//	 Bit 1 = if true, play frame only once, instead of repeating until another frame is written
//   Bit 2 = if 1, don't let WriteFrame() block execution while waiting for the transfer to finish 
//			(NB: then the function might return 1 even if the transfer fails)
//   Bit 3 = IDN (Network) DACs do not provide an actual status feedback, so GetStatus() could in theory just return 1 all the time.
//			 However, some programs may depends on the timing of the status signal, so by default an approximate timing is simulated.
//			 If this flag bit is 1, this timing simulation is disabled, and GetStatus() returns 1 as soon as it can.
//	 Bit 4-7 = reserved
// points: pointer to point data. See point structure documentation in HeliosDac.h
// numOfPoints: number of points in the frame
// Returns 1 if successful
HELIOS_EXPORT int WriteFrame(unsigned int dacNum, int pps, std::uint8_t flags, HeliosPoint* points, int numOfPoints);

// Writes and outputs a frame to the speficied dac, with a 16-bit resolution frame structure. Recommended for new integrations.
// It is safe to call this function even for DACs that don't support higher resolution data. In that case the data will be converted (though at a slight performance cost).
// dacNum: dac number (0 to n where n+1 is the return value from OpenDevices() )
// pps: rate of output in points per second
// flags: (default is 0)
//	 Bit 0 (LSB) = if true, start output immediately, instead of waiting for current frame (if there is one) to finish playing
//	 Bit 1 = if true, play frame only once, instead of repeating until another frame is written
//   Bit 2 = if 1, don't let WriteFrame() block execution while waiting for the transfer to finish 
//			(NB: then the function might return 1 even if the transfer fails)
//   Bit 3 = IDN (Network) DACs do not provide an actual status feedback, so GetStatus() could in theory just return 1 all the time.
//			 However, some programs may depends on the timing of the status signal, so by default an approximate timing is simulated.
//			 If this flag bit is 1, this timing simulation is disabled, and GetStatus() returns 1 as soon as it can.
//	 Bit 4-7 = reserved
// points: pointer to point data. See point structure documentation in HeliosDac.h
// numOfPoints: number of points in the frame
// Returns 1 if successful
HELIOS_EXPORT int WriteFrameHighResolution(unsigned int dacNum, int pps, std::uint8_t flags, HeliosPointHighRes* points, int numOfPoints);

// Writes and outputs a frame to the speficied dac, with an extended frame structure providing high resolution and multiple user-defined channels. 
// It is safe to call this function even for DACs that don't support higher resolution data. In that case the data will be converted (though at a slight performance cost).
// dacNum: dac number (0 to n where n+1 is the return value from OpenDevices() )
// pps: rate of output in points per second
// flags: (default is 0)
//	 Bit 0 (LSB) = if true, start output immediately, instead of waiting for current frame (if there is one) to finish playing
//	 Bit 1 = if true, play frame only once, instead of repeating until another frame is written
//   Bit 2 = if 1, don't let WriteFrame() block execution while waiting for the transfer to finish 
//			(NB: then the function might return 1 even if the transfer fails)
//   Bit 3 = IDN (Network) DACs do not provide an actual status feedback, so GetStatus() could in theory just return 1 all the time.
//			 However, some programs may depends on the timing of the status signal, so by default an approximate timing is simulated.
//			 If this flag bit is 1, this timing simulation is disabled, and GetStatus() returns 1 as soon as it can.
//	 Bit 4-7 = reserved
// points: pointer to point data. See point structure documentation in HeliosDac.h
// numOfPoints: number of points in the frame
// Returns 1 if successful
HELIOS_EXPORT int WriteFrameExtended(unsigned int dacNum, int pps, std::uint8_t flags, HeliosPointExt* points, int numOfPoints);

// Sets the shutter of the specified dac.
// Value 1 = shutter open, value 0 = shutter closed
// Returns 1 if successful.
HELIOS_EXPORT int SetShutter(unsigned int dacNum, bool shutterValue);

// Returns the firmware version number.
HELIOS_EXPORT int GetFirmwareVersion(unsigned int dacNum);

// Gets a descriptive name of the specified dac
// Name buffer needs to be able to hold up to 32 bytes.
// Returns 1 if successful, return 0 if the proper name couldn't be fetched from the DAC, but name is still populated with a fallback numbered name based on order of discovery by the library.
// Return negative number if unsuccessful and name is not populated.
HELIOS_EXPORT int GetName(unsigned int dacNum, char* name);

// Gets a descriptive name of the specified dac
// Name must be max 20 characters long (21 bytes including null terminator).
// Returns 1 if successful, return 0 if the transfer failed
HELIOS_EXPORT int SetName(unsigned int dacNum, char* name);

// Stops, blanks and centers output on the specified dac
// Returns 1 if successful
HELIOS_EXPORT int Stop(unsigned int dacNum);

// Closes connection to all dacs and frees resources
// Should be called when library is no longer needed (program exit for example)
HELIOS_EXPORT int CloseDevices();

// Gets the maximum frame size for this type of DAC, in number of points
// Note that it is safe to write frames outside this limit, but the frame will get automatically subsampled (at a performance cost)
HELIOS_EXPORT int GetMaxFrameSize(unsigned int dacNum);

// Gets the maximum sample rate in pps (points per second) for this type of DAC
// Note that it is safe to write frames outside this limit, but the frame will get automatically subsampled (at a performance cost)
HELIOS_EXPORT int GetMaxSampleRate(unsigned int dacNum);

// Gets the minimum sample rate in pps (points per second) for this type of DAC
// Note that it is safe to write frames outside this limit, but points will get automatically duplicated to increase pps (at a performance cost)
HELIOS_EXPORT int GetMinSampleRate(unsigned int dacNum);

// Gets whether the specific DAC support 16-bit resolutions for position and color data. 
// Note that it is safe to write high-res frames to low-res DACs, but points will get automatically converted (at a performance cost)
// Returns 1 if yes, 0 if no, and a negative number on error.
HELIOS_EXPORT int GetSupportsHigherResolutions(unsigned int dacNum);

// Sets libusb debug log level. May be needed for advanced debugging.
// See libusb.h for log level values
HELIOS_EXPORT int SetLibusbDebugLogLevel(int logLevel);

// Clears the GPNVM1 bit on the DACs microcontroller. This will cause the DAC to boot into SAM-BA bootloader which allows new firmware to be uploaded over USB.
// Don't call this unless you know what you are doing.
HELIOS_EXPORT int EraseFirmware(unsigned int dacNum);


/* EzAudDac API */
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

	struct EAD_Pnt_s {
		int16_t X;
		int16_t Y;
		int16_t R;
		int16_t G;
		int16_t B;
		int16_t I;
		int16_t AL;
		int16_t AR;
	};

	HELIOS_EXPORT int STDCALL EzAudDacGetCardNum(void);
	HELIOS_EXPORT bool STDCALL EzAudDacWriteFrame(const int *CardNum, const struct EAD_Pnt_s* data, int Bytes, uint16_t PPS);
	HELIOS_EXPORT bool STDCALL EzAudDacWriteFrameNR(const int *CardNum, const struct EAD_Pnt_s* data, int Bytes, uint16_t PPS, uint16_t Reps);
	HELIOS_EXPORT int STDCALL EzAudDacGetStatus(const int *CardNum);
	HELIOS_EXPORT bool STDCALL EzAudDacStop(const int *CardNum);
	HELIOS_EXPORT int STDCALL EzAudDacSetShutter(const int *CardNum, bool level);
	HELIOS_EXPORT bool STDCALL EzAudDacClose(void);

#endif