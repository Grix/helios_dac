/*
Helios Laser DAC SDK shared library
MIT License
By Gitle Mikkelsen
gitlem@gmail.com

Dependencies:
Libusb 1.0 (GNU Lesser General Public License, see libusb.h)
HeliosDAC.cpp/h and its dependencies in the idn folder

Standard: C++14

This is the shared library extension of the Helios DAC SDK, used to produce a dynamic library file like .dll, .so or .dylib. 
This allows you to call the code from other languages than C++.
If a shared library is not neccessary, you can simply use HeliosDAC.cpp/.h and the files in the idn subfolder directly in your 
source code, with no additional files or linking needed.

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

// Initializes drivers, opens connection to only IDN/network devices (skips USB scan).
// Returns number of available devices.
// NB: To re-scan for newly connected DACs after this function has once been called before, you must first call CloseDevices()
HELIOS_EXPORT int OpenDevicesOnlyNetwork();

// Gets status from the specified dac.
// You MUST poll this function until it returns true, before every call to WriteFrame*().
// Return 1 if ready to receive new frame, 0 if not, negative number if communcation failed
HELIOS_EXPORT int GetStatus(unsigned int dacNum);

// Writes and outputs a frame to the speficied dac.
// WriteFrame() uses the lightweight point structure designed for the original Helios DAC.
// WriteFrameHighResolution() uses a higher resolution point structure supported by newer DAC models. If unsure, this one is recommended.
// WriteFrameExtended() has additional optional channels and a higher resolution point structure supported by newer DAC models.
// 
// It is safe to call any of these functions even for DACs that don't support higher resolution data. In that case the data will automatically be converted (though at a slight performance cost).
// NB: You should make frames large enough to account for transfer overheads and timing jitter. Frames should be 10 milliseconds or longer on average, generally speaking.
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
HELIOS_EXPORT int WriteFrame(unsigned int dacNum, int pps, std::uint8_t flags, HeliosPoint* points, int numOfPoints);
HELIOS_EXPORT int WriteFrameHighResolution(unsigned int dacNum, int pps, std::uint8_t flags, HeliosPointHighRes* points, int numOfPoints);
HELIOS_EXPORT int WriteFrameExtended(unsigned int dacNum, int pps, std::uint8_t flags, HeliosPointExt* points, int numOfPoints);

// Sets the shutter of the specified dac. 
// This is no longer strictly necessary to call, the library automatically opens the shutter when you write a frame.
// Value 1 = shutter open, value 0 = shutter closed
// Returns 1 if successful.
HELIOS_EXPORT int SetShutter(unsigned int dacNum, bool shutterValue);

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

// Returns whether a specific DAC is a USB Helios DAC (as opposed to an IDN network DAC).
// Returns 1 if yes, 0 if no, and a negative number on error.
HELIOS_EXPORT int GetIsUsb(unsigned int dacNum);

// Returns the firmware version number.
// For Helios USB, the firmware version is just one simple integer, which is never higher than 255.
// For Helios IDN DACs, the firmware version is an integer in this format: AABBCC, which corresponds to vAA.BB.CC. For example 10002 would be v1.0.2.
// For non-Helios IDN DACs, this function may not work, as firmware version getting is not a part of the IDN spec. In that case, the function may block for a second and then return a negative number.
HELIOS_EXPORT int GetFirmwareVersion(unsigned int dacNum);

// Returns whether a specific DAC supports the higher resolutions color/postion data of new WriteFrameHighResolution() and WriteFrameExtended() functions. 
// The Original Helios USB device does not, at least not all firmware versions. HeliosPRO / IDN devices supports it.
// Note that it is safe to call these function even for DACs that don't support higher resolution data, in that case the data will automatically be converted (though at a performance cost).
// Returns 1 if yes, 0 if no, and a negative number on error.
HELIOS_EXPORT int GetSupportsHigherResolutions(unsigned int dacNum);

// Sets libusb debug log level. May be needed for advanced debugging.
// See libusb.h for log level values
HELIOS_EXPORT int SetLibusbDebugLogLevel(int logLevel);

// Clears the GPNVM1 bit on the DACs microcontroller. This will cause the DAC to boot into SAM-BA bootloader which allows new firmware to be uploaded over USB.
// Don't call this unless you know what you are doing.
HELIOS_EXPORT int EraseFirmware(unsigned int dacNum);


// EzAudDac API compatibility wrapper
// Probably only relevant on Windows, hence the ifdef block.
// Remember to use EzAudDacExports.def to export functions without mangling.
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