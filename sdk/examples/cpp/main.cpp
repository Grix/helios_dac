// Example program scanning a line from top to bottom on each Helios that is connected.
// Also periodically rescans for new connected devices.

#include "../../cpp/HeliosDac.h"
#include <thread>
#include <mutex>

int numDevices = 0;
bool stopThreads = false;
HeliosDac helios;
std::mutex deviceDetectionMutex;

void deviceDetectionHandler(void);

int main(void)
{
	// Assemble test frames
	// This is a simple line moving upward in a loop, but for real graphics you should optimize the point stream for laser scanners by 
	// interpolating long vectors including blanked sections, adding points at sharp corners, etc.
	const int numFramesInLoop = 20;
	const int numPointsPerFrame = 1500;
	const int pointsPerSecond = 40000;
	HeliosPointHighRes** frame = new HeliosPointHighRes*[numFramesInLoop];
	int x = 0;
	int y = 0;

	std::uint16_t xToggle = 1;

	for (int i = 0; i < numFramesInLoop; i++)
	{
		frame[i] = new HeliosPointHighRes[numPointsPerFrame];
		y = i * 0xFFFF / numFramesInLoop;
		for (int j = 0; j < numPointsPerFrame; j++)
		{
			if (j < (numPointsPerFrame/2))
				x = j * 0xFFFF / (numPointsPerFrame/2);
			else
				x = 0xFFFF - ((j - (numPointsPerFrame / 2)) * 0xFFFF / (numPointsPerFrame / 2));

			frame[i][j].x = x;		// xToggle * 0xFFFF; xToggle = (xToggle == 1 ? 0 : 1); // for debug
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
	numDevices = helios.OpenDevices();

	// Simple hot-plugging implementation. Optional, you could simply manually scan once using OpenDevices() instead.
	std::thread deviceDetectionThread(deviceDetectionHandler); 
	deviceDetectionThread.detach();

	// Print some info about connected DACs
	if (numDevices <= 0)
	{
		printf("No DACs found (but we are scanning again every 5 seconds..)\n");
	}
	printf("Found %d DACs:\n", numDevices);
	for (int j = 0; j < numDevices; j++)
	{
		char name[32];
		if (helios.GetName(j, name) == HELIOS_SUCCESS)
			printf("- %s: type: %s, FW: %d\n", name, helios.GetIsUsb(j) ? "USB" : "IDN/Network", helios.GetFirmwareVersion(j));
		else
			printf("- (unknown dac): USB?: %d, FW %d\n", helios.GetIsUsb(j), helios.GetFirmwareVersion(j));
	}
	printf("Outputting animation...\n");

	// Output animation to the DAC(s) in a loop.
	bool anyDeviceOpened = false;
	int i = 0;
	while (1)
	{
		i++;
		if (i % 3000 == 1000)
		{
			Sleep(3000); // Just for testing purposes, simulates a buffer underrun which should turn lasers off for a few seconds.
		}

		if (!anyDeviceOpened)
			std::this_thread::sleep_for(std::chrono::milliseconds(100)); // To avoid loading the CPU 100% if there is no connected devices that we can wait for.

		// Send each frame to the DACs.
		for (int j = 0; j < numDevices; j++)
		{
			if (helios.GetIsClosed(j))
				continue;

			anyDeviceOpened = true;

			// Wait for ready status. You must call GetStatus() until it returns 1 before each and every WriteFrame*() call that you do.
			for (unsigned int k = 0; k < 1024; k++)
			{ 
				int status = helios.GetStatus(j);
				if (status == 1)
				{
					helios.WriteFrameHighResolution(j, pointsPerSecond, HELIOS_FLAGS_DEFAULT, frame[i % numFramesInLoop], numPointsPerFrame);
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
			// You should also make frames large enough to account for transfer overheads and timing jitter. 
			// Frames should be 10 milliseconds long at an absolute minimum, but 20-40ms is recommended, generally speaking.
			
			// NB: In a real app, each DAC should have its own thread to avoid having them wait on each other. 
			// This simple single-threaded example will not work properly with multiple DACs for that reason.
		}
	}

	// Freeing connection when we're done
	stopThreads = true;
	helios.CloseDevices();

	return 0;
}



// Simple hot-plugging implementation. Optional, you could simply manually scan once using OpenDevices() instead.
void deviceDetectionHandler(void)
{
	while (!stopThreads)
	{
		std::this_thread::sleep_for(std::chrono::seconds(10));

		// NB: In your app you should try to avoiding polling for device changes while output is turned on,
		// as the scanning process could potentially disrupt output for a few milliseconds.

		numDevices = helios.ReScanDevices();
	}
}