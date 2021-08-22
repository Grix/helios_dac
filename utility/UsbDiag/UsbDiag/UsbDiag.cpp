// UsbDiag.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "HeliosDac.h"
#include <cstdio>

int main()
{

	HeliosDac* dac = new HeliosDac();
	int numDacs = dac->OpenDevices();

	printf("\nSuccessfully found and opened %d Helios DACs.\n", numDacs);

	for (int i = 0; i < numDacs; i++)
	{
		char name[32];
		int fw = dac->GetFirmwareVersion(i);
		dac->GetName(i, name);
		printf("DAC %d: Name: %s , Current Firmware version: %d\n", i, name, fw);
	}

	dac->CloseDevices();
	delete dac;
	std::string halt;
	std::cin >> halt;
}