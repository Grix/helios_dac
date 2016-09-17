
#include "main.h"

int main()
{
	HeliosDac dac = HeliosDac();
	int numDacs = dac.OpenDevices();

	if (numDacs >= 1)
	{
		uint8_t controlBuffer[2] = { 0xDE, 0 };
		dac.SendControl(0, &controlBuffer[0], false);
		std::cout << "Sent firmware erase command. You can now upload new firmware with SAM-BA.";
	}
	else
		std::cout << "ERROR: Could not connect to Helios.";

	dac.CloseDevices();

	int c = 0;
	std::cin >> c;

	return 1;
}
