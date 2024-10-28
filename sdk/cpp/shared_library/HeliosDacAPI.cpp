/*
Helios Laser DAC SDK shared library
By Gitle Mikkelsen

See HeliosDacAPI.h for documentation

Dependencies:
Libusb 1.0 (GNU Lesser General Public License, see libusb.h)
HeliosDAC class
OpenLaserShowControllerV1.0.0 header and .def file (only on windows, and optional)

git repo: https://github.com/Grix/helios_dac.git
*/

#include "HeliosDacAPI.h"

int OpenDevices()
{
	if (inited)
		return dacController->OpenDevices();

	dacController = new HeliosDac();

	int result = dacController->OpenDevices();

	if (result <= 0)
		delete dacController;
	else
		inited = true;

	return result;
}

int OpenDevicesOnlyUsb()
{
	if (inited)
		return dacController->OpenDevicesOnlyUsb();

	dacController = new HeliosDac();

	int result = dacController->OpenDevicesOnlyUsb();

	if (result <= 0)
		delete dacController;
	else
		inited = true;

	return result;
}

int GetStatus(unsigned int dacNum)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	return (int)dacController->GetStatus(dacNum);
}

int WriteFrame(unsigned int dacNum, int pps, std::uint8_t flags, HeliosPoint* points, int numOfPoints)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	return dacController->WriteFrame(dacNum, pps, flags, points, numOfPoints);
}

int WriteFrameHighResolution(unsigned int dacNum, int pps, std::uint8_t flags, HeliosPointHighRes* points, int numOfPoints)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	return dacController->WriteFrameHighResolution(dacNum, pps, flags, points, numOfPoints);
}

int WriteFrameExtended(unsigned int dacNum, int pps, std::uint8_t flags, HeliosPointExt* points, int numOfPoints)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	return dacController->WriteFrameExtended(dacNum, pps, flags, points, numOfPoints);
}

int Stop(unsigned int dacNum)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	return dacController->Stop(dacNum);
}

int GetName(unsigned int dacNum, char* name)
{
	if (!inited)
		return  HELIOS_ERROR_NOT_INITIALIZED;

	return dacController->GetName(dacNum, name);
}

int SetName(unsigned int dacNum, char* name)
{
	if (!inited)
		return  HELIOS_ERROR_NOT_INITIALIZED;

	return dacController->SetName(dacNum, name);
}

int SetShutter(unsigned int dacNum, bool value)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	return dacController->SetShutter(dacNum, value);
}

int GetMaxFrameSize(unsigned int dacNum)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	return dacController->GetMaxFrameSize(dacNum);
}

int GetMaxSampleRate(unsigned int dacNum)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	return dacController->GetMaxSampleRate(dacNum);
}

int GetMinSampleRate(unsigned int dacNum)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	return dacController->GetMinSampleRate(dacNum);
}

int GetSupportsHigherResolutions(unsigned int dacNum)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	return dacController->GetSupportsHigherResolutions(dacNum) ? 1 : 0;
}

int GetFirmwareVersion(unsigned int dacNum)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	return dacController->GetFirmwareVersion(dacNum);
}

int SetLibusbDebugLogLevel(int logLevel)
{
	if (!inited)
		return HELIOS_ERROR_NOT_INITIALIZED;

	return dacController->SetLibusbDebugLogLevel(logLevel);
}

int EraseFirmware(unsigned int dacNum)
{
	if (!inited)
		return  HELIOS_ERROR_NOT_INITIALIZED;

	return dacController->EraseFirmware(dacNum);
}

int CloseDevices()
{
	if (inited)
	{
		inited = false;
		delete dacController;
		return HELIOS_SUCCESS;
	}
	else
		return HELIOS_ERROR_NOT_INITIALIZED;
}

//EZAudDAC API wrapper
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

bool STDCALL EzAudDacWriteFrameNR(const int *CardNum, const struct EAD_Pnt_s* data, int Bytes, uint16_t PPS, uint16_t Reps)
{
	if (ezAudDacFrameBuffer == 0)
		ezAudDacFrameBuffer = new HeliosPointHighRes[HELIOS_MAX_POINTS];

	unsigned int dacNum = *CardNum;
	unsigned int numPoints = min(Bytes / sizeof(*data), HELIOS_MAX_POINTS);
	
	for (unsigned int i = 0; i < numPoints; i++)
	{
		ezAudDacFrameBuffer[i].x = data[i].X + 0x8000;
		ezAudDacFrameBuffer[i].y = data[i].Y + 0x8000;
		ezAudDacFrameBuffer[i].r = data[i].R + 0x8000;
		ezAudDacFrameBuffer[i].g = data[i].G + 0x8000;
		ezAudDacFrameBuffer[i].b = data[i].B + 0x8000;
		ezAudDacFrameBuffer[i].user1 = 0;
	}
	if (Reps == 1)
		return WriteFrameHighResolution(dacNum, PPS, HELIOS_FLAGS_SINGLE_MODE | HELIOS_FLAGS_DONT_BLOCK, ezAudDacFrameBuffer, numPoints);
	else
		return WriteFrameHighResolution(dacNum, PPS, HELIOS_FLAGS_DEFAULT | HELIOS_FLAGS_DONT_BLOCK, ezAudDacFrameBuffer, numPoints); //ignore reps over 1, play continuously instead
}

bool STDCALL EzAudDacWriteFrame(const int *CardNum, const struct EAD_Pnt_s* data, int Bytes, uint16_t PPS)
{
	if (ezAudDacFrameBuffer == 0)
		ezAudDacFrameBuffer = new HeliosPointHighRes[HELIOS_MAX_POINTS];

	unsigned int dacNum = *CardNum;
	unsigned int numPoints = min(Bytes / sizeof(*data), HELIOS_MAX_POINTS);

	for (unsigned int i = 0; i < numPoints; i++)
	{
		ezAudDacFrameBuffer[i].x = data[i].X + 0x8000;
		ezAudDacFrameBuffer[i].y = data[i].Y + 0x8000;
		ezAudDacFrameBuffer[i].r = data[i].R + 0x8000;
		ezAudDacFrameBuffer[i].g = data[i].G + 0x8000;
		ezAudDacFrameBuffer[i].b = data[i].B + 0x8000;
		ezAudDacFrameBuffer[i].user1 = 0;
	}
	return WriteFrameHighResolution(dacNum, PPS, HELIOS_FLAGS_DEFAULT | HELIOS_FLAGS_DONT_BLOCK, ezAudDacFrameBuffer, numPoints);
}

int STDCALL EzAudDacGetCardNum(void)
{
	return OpenDevices();
}

int STDCALL EzAudDacGetStatus(const int *CardNum)
{
	unsigned int dacNum = *CardNum;
	return GetStatus(dacNum);
}

bool STDCALL EzAudDacClose(void)
{
	return CloseDevices();
}

bool STDCALL EzAudDacStop(const int *CardNum)
{
	unsigned int dacNum = *CardNum;
	return Stop(dacNum);
}

#endif
