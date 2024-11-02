//Example program scanning a line from top to bottom on the Helios

#include "../../cpp/HeliosDac.h"

int main(void)
{
	//make frames
	//this is a simple scanning line, but for real graphics you should optimize with evenly spaced points, added points in sharp corners, inserting blanking lines, etc.
	HeliosPointHighRes** frame = new HeliosPointHighRes *[30];
	int x = 0;
	int y = 0;
	for (int i = 0; i < 30; i++)
	{
		frame[i] = new HeliosPointHighRes[1000];
		y = i * 0xFFFF / 30;
		for (int j = 0; j < 1000; j++)
		{
			if (j < 500)
				x = j * 0xFFFF / 500;
			else
				x = 0xFFFF - ((j - 500) * 0xFFFF / 500);

			frame[i][j].x = x;
			frame[i][j].y = y;
			frame[i][j].r = 0xD000;
			frame[i][j].g = 0xFFFF;
			frame[i][j].b = 0xD000;
			//frame[i][j].user1 = 0; // Use HeliosPointExt with WriteFrameExtended() if you need more channels
			//frame[i][j].user2 = 0;
			//frame[i][j].user3 = 0;
			//frame[i][j].user4 = 0;
			//frame[i][j].i = 0xFFFF;
		}
	}

	// Connect to DACs and output frames
	// First scan for connected devices and open the connection(s).
	HeliosDac helios;
	int numDevs = helios.OpenDevices();

	if (numDevs <= 0)
	{
		printf("No DACs found.\n");
		return 0;
	}
	printf("Found %d DACs:\n", numDevs);
	for (int j = 0; j < numDevs; j++)
	{
		char name[32];
		if (helios.GetName(j, name) == HELIOS_SUCCESS)
			printf("- %s\n", name);
		else
			printf("- (unknown dac)\n");
	}
	printf("Outputting animation...\n");

	int i = 0;
	while (1)
	{
		i++;
		if (i > 150)
			break;

		for (int j = 0; j < numDevs; j++)
		{
			// Wait for ready status. You must call GetStatus() until it returns 1 before each and every WriteFrame*() call that you do.
			for (unsigned int k = 0; k < 512; k++)
			{
				if (helios.GetStatus(j) == 1)
					break;
			}
			helios.WriteFrameHighResolution(j, 40000, HELIOS_FLAGS_DEFAULT, frame[i % 30], 1000); // Send the next frame to the DAC.
		}
	}

	// Freeing connection when we're done
	helios.CloseDevices();

	return 0;
}