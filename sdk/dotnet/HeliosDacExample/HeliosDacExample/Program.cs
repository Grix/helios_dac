using System;
using HeliosDac;

namespace HeliosDacExample
{
    class Program
    {
        static void Main(string[] args)
        {
			// Make frames. This is an animation of a simple line scanning upward.
			HeliosPoint[][] frames = new HeliosPoint[30][];
			int x = 0;
			int y = 0;
			for (int i = 0; i < 30; i++)
			{
				frames[i] = new HeliosPoint[1000];
				y = i * 0xFFF / 30;
				for (int j = 0; j < 1000; j++)
				{
					if (j < 500)
						x = j * 0xFFF / 500;
					else
						x = 0xFFF - ((j - 500) * 0xFFF / 500);

					frames[i][j].X = (ushort)x;
					frames[i][j].Y = (ushort)y;
					frames[i][j].Red = 0xD0;
					frames[i][j].Green = 0xFF;
					frames[i][j].Blue = 0xD0;
					frames[i][j].Intensity = 0xFF;
				}
			}

			// Connect to DACs and output frames
			var heliosController = new HeliosController();
			int numberOfDevices = heliosController.OpenDevices();

			for (int j = 0; j < 150; j++)
			{
				for (int deviceId = 0; deviceId < numberOfDevices; deviceId++)
				{
					// Wait for ready status
					bool isReady = false;
					for (int k = 0; k < 50; k++)
					{
						if (heliosController.GetStatus(deviceId))
						{
							isReady = true;
							break;
						}
					}
					// Send the next frame if received a ready signal
					if (isReady)
						heliosController.WriteFrame(deviceId, 25000, frames[j % 30]);
				}
			}

			// Freeing connection
			heliosController.CloseDevices();
		}
    }
}
