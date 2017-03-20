//Example program scanning a line from top to bottom on the Helios

#include "main.h"

int main(void)
{
	//make frames
	HeliosPoint frame[30][1000];
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
				x = 0xFFF - ((j - 500) * 0xFFF / 500);

			frame[i][j].x = x;
			frame[i][j].y = y;
			frame[i][j].r = 0xFF;
			frame[i][j].g = 0xFF;
			frame[i][j].b = 0xFF;
			frame[i][j].i = 0xFF;
		}
	}

	//connect to DACs and output frames
	HeliosDac helios;
	int numDevs = helios.OpenDevices();

	int i = 0;
	while (1)
	{
		if (i > 150) //cancel after 5 animations
			break;

		for (int j = 0; j < numDevs; j++)
		{
			if (helios.GetStatus(j) == 1)
			{
				helios.WriteFrame(j, 30000, 0, &frame[i++ % 30][0], 1000);
			}
		}
	}

	//freeing connection
	helios.CloseDevices();
}