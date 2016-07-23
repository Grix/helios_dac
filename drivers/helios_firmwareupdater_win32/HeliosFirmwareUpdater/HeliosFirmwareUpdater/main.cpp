
#include "main.h"

int main()
{
	HeliosDac dac = HeliosDac();
	if (dac.OpenDevices() < 1)
		return 0;

	uint8_t controlBuffer[2] = { 0xDE, 0 };
	dac.SendControl(0, &controlBuffer[0], false);

	dac.CloseDevices();

	return 1;
}
