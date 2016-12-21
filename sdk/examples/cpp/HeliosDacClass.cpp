#include "HeliosDacClass.h"


HeliosDacClass::HeliosDacClass()
{
	inited = false;
	flipX = true;
}


HeliosDacClass::~HeliosDacClass()
{
	CloseDevices();
}


int HeliosDacClass::OpenDevices()
{
	CloseDevices();

	dacController = new HeliosDac();

	int result = dacController->OpenDevices();

	if (result <= 0)
		delete dacController;
	else
		inited = true;

	return result;
}


int HeliosDacClass::WriteFrame(int dacNum, int pps, uint8_t flags, HeliosPoint* points, int numOfPoints)
{
	if ((!inited) || (points == NULL))
		return 0;
	if ((numOfPoints > HELIOS_MAX_POINTS) || (pps > HELIOS_MAX_RATE) || (pps < HELIOS_MIN_RATE))
		return 0;

	//prepare frame buffer
	uint8_t frameBuffer[HELIOS_MAX_POINTS * 7 + 5];
	int bufPos = 0;
	for (int i = 0; i < numOfPoints; i++)
	{
		if (flipX)
		{
			frameBuffer[bufPos++] = ((0xFFF - points[i].x) >> 4);
			frameBuffer[bufPos++] = (((0xFFF - points[i].x) & 0x0F) << 4) | (points[i].y >> 8);
			frameBuffer[bufPos++] = (points[i].y & 0xFF);
		}
		else
		{
			frameBuffer[bufPos++] = (points[i].x >> 4);
			frameBuffer[bufPos++] = ((points[i].x & 0x0F) << 4) | (points[i].y >> 8);
			frameBuffer[bufPos++] = (points[i].y & 0xFF);
		}
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

	return dacController->SendFrame(dacNum, &frameBuffer[0], bufPos);
}

int HeliosDacClass::Stop(int dacNum)
{
	if (!inited)
		return 0;

	uint8_t ctrlBuffer[2] = { 0x01, 0 };
	if (dacController->SendControl(dacNum, &ctrlBuffer[0], 2))
		return 1;
	else
		return 0;
}


int HeliosDacClass::GetName(int dacNum, char* name)
{
	if (!inited)
		return  -1;

	uint8_t ctrlBuffer[32] = { 0x05, 0 };
	int tx = dacController->SendControl(dacNum, &ctrlBuffer[0], 2);
	if (tx == 1)
	{
		tx = dacController->GetControlResponse(dacNum, &ctrlBuffer[0], 32);
		if (tx == 1)
		{
			if ((ctrlBuffer[0]) == 0x85) //if received control byte is as expected
			{
				memcpy(name, &ctrlBuffer[1], 32);
				return 1;
			}
		}
	}

	//if the above failed, fallback name:
	memcpy(name, "Helios ", 8);
	name[7] = (char)((int)(dacNum >= 10) + 48);
	name[8] = (char)((int)(dacNum % 10) + 48);
	name[9] = '\0';
	return 0;
}

int HeliosDacClass::SetName(int dacNum, char* name)
{
	if (!inited)
		return  -1;

	uint8_t ctrlBuffer[32] = { 0x06 };
	memcpy(&ctrlBuffer[1], name, 31);
	return dacController->SendControl(dacNum, &ctrlBuffer[0], 32);
}


int HeliosDacClass::GetStatus(int dacNum)
{
	if (!inited)
		return -1;

	uint8_t ctrlBuffer[32] = { 0x03, 0 };
	int tx = dacController->SendControl(dacNum, &ctrlBuffer[0], 2);
	if (tx != 1)
		return -1;

	tx = dacController->GetControlResponse(dacNum, &ctrlBuffer[0], 2);
	if (tx == 1)
	{
		if ((ctrlBuffer[0]) == 0x83) //if received control byte is as expected
		{
			if (ctrlBuffer[1] == 1) //if dac is ready
				return 1;
			else
				return 0;
		}
	}

	return -1;
}


int HeliosDacClass::SetShutter(int dacNum, bool value)
{
	if (!inited)
		return 0;

	uint8_t ctrlBuffer[2] = { 0x02, value };
	return dacController->SendControl(dacNum, &ctrlBuffer[0], 2);
}

int HeliosDacClass::GetFirmwareVersion(int dacNum)
{
	if (!inited)
		return -1;

	uint8_t ctrlBuffer[32] = { 0x04, 0 };
	int tx = dacController->SendControl(dacNum, &ctrlBuffer[0], 2);
	if (tx != 1)
		return -1;

	tx = dacController->GetControlResponse(dacNum, &ctrlBuffer[0], 5);
	if (tx == 1)
	{
		if ((ctrlBuffer[0]) == 0x84) //if received control byte is as expected
		{
			return ((ctrlBuffer[1] << 0) |
				(ctrlBuffer[2] << 8) |
				(ctrlBuffer[3] << 16) |
				(ctrlBuffer[4] << 24));
		}
	}
	else
		return 0;
}

int HeliosDacClass::EraseFirmware(int dacNum)
{
	if (!inited)
		return  -1;

	uint8_t ctrlBuffer[2] = { 0xDE, 0 };
	return dacController->SendControl(dacNum, &ctrlBuffer[0], 2);
}

int HeliosDacClass::CloseDevices()
{
	if (inited)
	{
		inited = false;
		delete dacController;
		return 1;
	}
	else
		return 0;
}