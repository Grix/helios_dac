#include "HeliosDac.h"
#include <cstdio>

int main()
{
	HeliosDac dac = HeliosDac();
	int numDacs = dac.OpenDevices();

	printf("\nFound %d DACs.\n", numDacs);
	
	for (int i = 0; i < numDacs; i++)
	{
		char name[32];
		int fw = dac.GetFirmwareVersion(i);
		dac.GetName(i, name);
		printf("Erasing DAC %d: Name: %s , Current Firmware version: %d\n", numDacs, name, fw);
		dac.EraseFirmware(i);
	}

	dac.CloseDevices();

	return 1;
}
