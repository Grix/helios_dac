// Example program scanning a line from top to bottom on the Helios

#include "../../cpp/HeliosDac.h"

int main(void)
{
	// Assemble test frames
	// This is a simple line moving upward in a loop, but for real graphics you should optimize the point stream for laser scanners by 
	// interpolating long vectors including blanked sections, adding points at sharp corners, etc.
	HeliosPointHighRes** frame = new HeliosPointHighRes*[30];
	const int numPointsPerFrame = 2000;
	const int pointsPerSecond = 50000;
	int x = 0;
	int y = 0;
	for (int i = 0; i < 30; i++)
	{
		frame[i] = new HeliosPointHighRes[numPointsPerFrame];
		y = i * 0xFFFF / 30;
		for (int j = 0; j < numPointsPerFrame; j++)
		{
			if (j < (numPointsPerFrame/2))
				x = j * 0xFFFF / (numPointsPerFrame/2);
			else
				x = 0xFFFF - ((j - (numPointsPerFrame / 2)) * 0xFFFF / (numPointsPerFrame / 2));

			frame[i][j].x = x;
			frame[i][j].y = y;
			frame[i][j].r = 0xD0FF;
			frame[i][j].g = 0xFFFF;
			frame[i][j].b = 0xD0FF;
			//frame[i][j].user1 = 0; // Use HeliosPointExt with WriteFrameExtended() if you need more channels
			//frame[i][j].user2 = 10;
			//frame[i][j].user3 = 20;
			//frame[i][j].user4 = 30;
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
		if (i > 2000)
		{
			break;
		}

		// Send each frame to the DAC.
		for (int j = 0; j < numDevs; j++)
		{
			// Wait for ready status. You must call GetStatus() until it returns 1 before each and every WriteFrame*() call that you do.
			for (unsigned int k = 0; k < 1024; k++)
			{ 
				int status = helios.GetStatus(j);
				if (status == 1)
				{
					helios.WriteFrameHighResolution(j, pointsPerSecond, HELIOS_FLAGS_DEFAULT | HELIOS_FLAGS_DONT_BLOCK | HELIOS_FLAGS_SINGLE_MODE, frame[i % 30], numPointsPerFrame);
					break;
				}
				else if (status < 0)
				{
					printf("Error when polling status for device #%d: %d\n", j, status);
					break;
				}
			}
			// In this loop, timing is handled by the GetStatus polling, which only returns 1 once there is room in the DAC to send the next frame.
			// You need to call WriteFrame*() in time (before the previously written frame finished playing), to not let the buffers in the DAC underrun.
			// You should also make frames large enough to account for transfer overheads and timing jitter. Frames should be 10 milliseconds or longer on average, generally speaking.

			// Here we use the HELIOS_FLAGS_DONT_BLOCK flag in WriteFrame() because this test app can connect to several DACs from the single-threaded main loop.
			// But if your app is already handling each DAC in its own thread, like it probably should, you can remove that flag.

			// We also use the HELIOS_FLAGS_SINGLE_MODE flag, because network (IDN) DACs always play the frame only once. Therefore, it is recommended to always 
			// use this flag to make the behavior of USB and IDN devices the same, and instead implement your own frame looping system if you need to repeat a frame.
		}
	}

	// Freeing connection when we're done
	helios.CloseDevices();

	return 0;
}