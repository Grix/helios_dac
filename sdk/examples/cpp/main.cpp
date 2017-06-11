//Example program scanning a line from top to bottom on the Helios

#include "HeliosDac.h"

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
			frame[i][j].r = 0x80;
			frame[i][j].g = 0xC0;
			frame[i][j].b = 0x80;
			frame[i][j].i = 0xFF;
		}
	}

	//connect to DACs and output frames
	HeliosDac helios;
	int numDevs = helios.OpenDevices();

	int i = 0;
	while (1)
	{
		i++;
		if (i > 150) //cancel after 5 cycles, 30 frames each
			break;

		for (int j = 0; j < numDevs; j++)
		{
			//wait for ready status
			for (unsigned int k = 0; k < 512; k++)
			{
				if (helios.GetStatus(j) == 1)
					break;
			}
			helios.WriteFrame(j, 20000, HELIOS_FLAGS_DEFAULT, &frame[i % 30][0], 1000); //send the next frame
		}
	}

	//freeing connection
	helios.CloseDevices();
}