//Example program scanning a line from top to bottom on the Helios

#include "main.h"

int main(void)
{
	//make frames
	HeliosDacClass::HeliosPoint frame[30][1000];
	int x = 0;
	int y = 0;
	for (int i = 0; i < 30; i++)
	{
		y = i * 0xFFF / 30;
		for (int j = 0; j < 1000; j++)
		{
			if (j < 500)
				x = j * 0xFFF / 500;
			else
				x = 0xFFF - ((j-500) * 0xFFF / 500);

			frame[i][j].x = x;
			frame[i][j].y = y;
			frame[i][j].r = 0xFF;
			frame[i][j].g = 0xFF;
			frame[i][j].b = 0xFF;
			frame[i][j].i = 0xFF;
		}
	}

	//connect to DAC and output frames
	HeliosDacClass helios;
	if (helios.OpenDevices() > 0)
	{
		int i = 0;
		while (1)
		{
			if (i > 300) 
				break;

			if (helios.GetStatus(0) == 1)
			{
				helios.WriteFrame(0, 30000, 0, &frame[i++ % 30][0], 1000);
			}
		}
	}
	helios.Stop(0);
}