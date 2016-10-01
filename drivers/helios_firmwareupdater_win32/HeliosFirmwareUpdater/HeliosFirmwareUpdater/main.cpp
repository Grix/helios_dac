
#include "main.h"

int main()
{
	HeliosDac dac = HeliosDac();
	int numDacs = dac.OpenDevices();

	if (numDacs >= 1)
	{
		uint8_t ctrlBuffer[2] = { 0x04, 0 };
		uint16_t result = dac.SendControl(0, &ctrlBuffer[0], true);

		if ((result >> 8) == 0x84)
			std::cout << "Current firmware version: " << (result & 0xFF) << "\n";
		else
			std::cout << "ERROR: Could not get current firmware version.\n";

		uint8_t controlBuffer[2] = { 0xDE, 0 };
		dac.SendControl(0, &controlBuffer[0], false);
		std::cout << "Sent firmware erase command. Disconnect and reconnect the Helios DAC, you can then upload new firmware with SAM-BA. Press any key + enter to exit.\n";
	}
	else
		std::cout << "ERROR: Could not connect to Helios. Press any key + enter to exit.\n";

	dac.CloseDevices();

	int c = 0;
	std::cin >> c;

	return 1;
}
