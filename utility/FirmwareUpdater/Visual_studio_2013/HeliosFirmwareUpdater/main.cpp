
#include "main.h"

int main()
{
	HeliosDac dac = HeliosDac();
	int numDacs = dac.OpenDevices();

	std::cout << "Select operation. Enter 1 to erase firmware, enter 2 to update name of DAC, enter 3 to test status getting: \n";
	int c = 0;
	std::cin >> c;
	
	if (numDacs >= 1)
	{
		if (c == 1) //ERASE FIRMWARE
		{
			uint8_t ctrlBuffer[2] = { 0x04, 0 };
			int result = dac.SendControl(0, &ctrlBuffer[0], 2);
			if (result)
			{
				uint8_t response[32];
				result = dac.GetControlResponse(0, &response[0]);
				if ((result > 4) && (response[0] == 0x84))
				{	
					uint32_t version;
					memcpy(&version, &response[1], 4);
					std::cout << "\nCurrent firmware version: " << version << "\n";
				}
				else 
					std::cout << "\nERROR: Could not get current firmware version.\n";
			}
			else
				std::cout << "\nERROR: Could not get current firmware version.\n";

			ctrlBuffer[0] = 0xDE;

			dac.SendControl(0, &ctrlBuffer[0], 2);
			std::cout << "Sent firmware erase command. Disconnect and reconnect the Helios DAC, you can then upload new firmware with SAM-BA. Press any key + enter to exit.\n";
		}
		else if (c == 2) //SET NEW NAME
		{
			uint8_t ctrlBuffer[2] = { 0x05, 0 };
			int result = dac.SendControl(0, &ctrlBuffer[0], 2);
			if (result)
			{
				uint8_t response[32];
				result = dac.GetControlResponse(0, &response[0]);
				if ((result > 0) && (response[0] == 0x85))
				{
					char name[32];
					memcpy(&name[0], &response[1], 32);
					name[31] = '\0'; //just in case the firmware didn't
					std::cout << "\nCurrent DAC name: " << name << "\n";
				}
				else
					std::cout << "\nERROR: Could not get current DAC name: No/Faulty response.\n";
			}
			else
				std::cout << "\nERROR: Could not get current DAC name: Could not query.\n";

			char name[32];
			uint8_t newCtrlBuffer[32];
			newCtrlBuffer[0] = 0x06;
			std::cout << "Please enter new DAC name (max 30 characters): ";
			std::cin >> name;
			memcpy(&newCtrlBuffer[1], &name[0], 31);
			result = dac.SendControl(0, &newCtrlBuffer[0], 32);
			bool success = false;			
			if (result)
			{
				ctrlBuffer[0] = 0x05;
				int result = dac.SendControl(0, &ctrlBuffer[0], 2);
				uint8_t response[32];
				result = dac.GetControlResponse(0, &response[0]);
				if ((result > 0) && (response[0] == 0x85))
				{
					success = true;
					char name[32];
					memcpy(&name[0], &response[1], 31);
					name[31] = '\0'; //just in case the firmware didn't
					std::cout << "\nSuccessful transfers. New DAC name: " << name << ". Press any key + enter to exit.\n";
				}
			}
			if (!success)
				std::cout << "\nERROR: Could not set new DAC name. Press any key + enter to exit.\n";
		}
		else if (c == 3) //TEST STATUS
		{
			uint8_t ctrlBuffer[2] = { 0x03, 0 };
			int result = dac.SendControl(0, &ctrlBuffer[0], 2);
			bool success = false;
			if (result)
			{
				uint8_t response[32];
				result = dac.GetControlResponse(0, &response[0]);
				if ((result > 0) && (response[0] == 0x83))
				{
					std::cout << "\nStatus query returned " << response[1] << "\n";
					success = true;
				}
			}
			if (!success)
				std::cout << "ERROR: Could not get status.\n";
		}
	}
	else
		std::cout << "ERROR: Could not connect to Helios. Press any key + enter to exit.\n";


	dac.CloseDevices();

	c = 0;
	std::cin >> c;

	return 1;
}
