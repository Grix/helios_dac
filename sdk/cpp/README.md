SDK for Helios Laser DAC class  
By Gitle Mikkelsen  
gitlem@gmail.com  

Dependencies:  
Libusb 1.0 (GNU Lesser General Public License, see libusb.h)

Standard: C++14

git repo: https://github.com/Grix/helios_dac.git

BASIC USAGE:
1.	Call OpenDevices() to open devices, returns number of available devices.
2.	To send a frame to the DAC, first call GetStatus(). If the function returns ready (1), 
	then you can call WriteFrame(). The status should be polled until it returns ready. 
	It can fail to return ready on the first try.
3.  To stop output, use Stop(). To restart output you must send a new frame as described above.
4.	When the DAC is no longer needed, destroy the instance (destructors will free everything and close the connection)

The DAC is double-buffered. When it receives its first frame, it starts outputting it. When a second frame is sent to 
the DAC while the first frame is being played, the second frame is stored in the DACs memory until the first frame 
finishes playback, at which point the second, buffered frame will start playing. If the DAC finished playback of a frame
without having received and buffered a second frame, it will by default loop the first frame until a new frame is
received (but the flag HELIOS_FLAG_SINGLE_MODE will make it stop playback instead).
The GetStatus() function actually checks whether or not the buffer on the DAC is empty or full. If it is full, the DAC
cannot receive a new frame until the currently playing frame finishes, freeing up the buffer.