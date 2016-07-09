//function relating to usb transfer

#include "usb.h"
#include "main.h"
#include <string.h>

void usb_iso_received()
{
	//	Byte 0-3: First packet control bits (0xAAAAAAAA)
	//	Byte 4-5: Scanning speed in pps (big endian)
	//	Byte 6-7: Size of frame in points (big endian)
	//	Byte 8-X: Point data
	//		Each point: 8 MSB of x, 4 LSB of x + 4 MSB of y, 8 LSB of y, r, g, b, i (7 bytes total)
	//	Byte X-4: Last packet control bits (0xBBBBBBBB)
	
	uint8_t* data = usbIsoBufferAddress;
	bool processPacket = false;
	bool lastPacket = false;
	uint8_t intraFramePos = 0;
	
	if (!newFrameReady)
	{
		//if control bits indicate first packet in frame
		if (	(data[0] == 0xAA) &&
		(data[1] == 0xAA) &&
		(data[2] == 0xAA) &&
		(data[3] == 0xAA) )
		{
			outputSpeed = ( (data[4] << 8) + data[5] );
			newFrameSize = ( ((data[6] << 8) + data[7]) * 7 + 4);
			
			if ((outputSpeed > MAXSPEED) || (outputSpeed < MINSPEED))
			{
				//error: wrong speed
			}
			else if (newFrameSize > MAXFRAMESIZE)
			{
				//error: wrong size
			}
			else
			{
				intraFramePos = 8;
				newFramePos = 0;
				processPacket = true;
			}
		}
		else if (newFramePos != 0)
		{
			processPacket = true;
		}
	}
	
	if (processPacket)
	{
		uint16_t bytesToCopy = 512 - intraFramePos;
		
		//if last packet in frame expected
		if ( (newFrameSize - newFramePos) <= bytesToCopy )
		{
			//adjust copy size and position
			bytesToCopy = newFrameSize - newFramePos;
			lastPacket = true;
		}
		
		//TODO copy data, below works?
		memcpy(&newFrameAddress[newFramePos], &data[intraFramePos], bytesToCopy);
		newFramePos += bytesToCopy;
		
		//if last packet in frame expected
		if (lastPacket)
		{
			//if control bytes indicates last packet in frame
			uint8_t* frameEnd = newFrameAddress+newFrameSize;
			
			if (	( *(frameEnd-0) == 0xBB) &&
			( *(frameEnd-1) == 0xBB) &&
			( *(frameEnd-2) == 0xBB) &&
			( *(frameEnd-3) == 0xBB) )
			{
				//frame successfully received
				newFrameReady = true;
				if (!playing)
				{
					playing = true;
					speed_set(outputSpeed);
				}
				
			}
			else
			{
				//faulty frame, discard
				newFramePos = 0;
			}
		}
	}
	
	udi_vendor_iso_out_run(usbIsoBufferAddress, 512, usb_iso_received);
}

void usb_control_received(void)
{
	uint8_t data[4];
	//	Byte 0: Command
	//	Byte 1-3: Data (big endian)
	
	if (data[0] == 0x01)		//STOP
	{
		playing = false;
		statusled_set(LOW);
	}
	else if (data[0] == 0x02)	//SHUTTER
	{
		
		if (data[3] == 0)
		shutter_set(LOW);
		else
		shutter_set(HIGH);
	}
	else if (data[0] == 0x03)	//STATUS_REQUEST
	{
		//TODO
	}
	else if (data[0] == 0x04)	//CLOSE
	{
		//TODO
	}
}

int callback_vendor_enable(void)
{
	start();
	udi_vendor_iso_out_run(usbIsoBufferAddress, 512, usb_iso_received);
	return 1;
}

void callback_vendor_disable(void)
{
	stop();
}