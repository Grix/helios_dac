using HeliosDac;

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
int numberOfDevices = 0;
try
{
    numberOfDevices = heliosController.OpenDevices();

    Console.WriteLine($"Found {numberOfDevices} Helios DACs:");
    for (int deviceId = 0; deviceId < numberOfDevices; deviceId++)
    {
        Console.WriteLine(heliosController.GetName(deviceId));
    }
}
catch (Exception ex)
{
    Console.WriteLine("Failure during detecting and opening of Helios DACs: " + ex.Message);
}

Console.WriteLine("\nSending a test animation to each DAC...");

for (int j = 0; j < 150; j++)
{
    for (int deviceId = 0; deviceId < numberOfDevices; deviceId++)
    {
        try
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
        catch (Exception ex)
        {
            Console.WriteLine("Failure during writing of laser frame to Helios DAC: " + ex.Message);
        }
    }
}

// Freeing connection
heliosController.CloseDevices();