
#include "main.h"

int main()
{
	HeliosDac dac = HeliosDac();
	int numDacs = dac.OpenDevices();
	
	if (numDacs >= 1)
	{
		uint8_t ctrlBuffer[2] = { 0x04, 0 };
		int result = dac.SendControl(0, &ctrlBuffer[0], 2);
		if (result)
		{
			uint8_t response[32];
			result = dac.GetControlResponse(0, &response[0], 5);
			if ((result > 4) && (response[0] == 0x84))
			{	
				uint32_t version;
				memcpy(&version, &response[1], 4);
				std::cout << "\nCurrent firmware version: " << version << "\n";
			}
			else 
				std::cout << "\nCould not get current firmware version.\n";
		}
		else
			std::cout << "\nECould not get current firmware version.\n";

		ctrlBuffer[0] = 0xDE;

		dac.SendControl(0, &ctrlBuffer[0], 2);
		std::cout << "Sent firmware erase command.\n";
	}
	else
	{
		std::cout << "ERROR: Could not connect to Helios.";
	}
		

	dac.CloseDevices();

	return 1;
}
