/*
Helios Laser DAC main AS project (for SAM4S2B board)
By Gitle Mikkelsen, Creative Commons Attribution-NonCommercial 4.0 International Public License
gitlem@gmail.com


Required Atmel Software Framework modules:
	DACC - Digital-to-Analog Converter
	Flash
	Generic Board Support (ATSAM4S2B)
	GPIO
	IOPORT
	SPI - Serial Peripheral Interface
	USB Device Vendor Class
	WDT - Watchdog Timer
*/

#ifndef MAIN_H_
#define MAIN_H_

#include "asf.h"
#include <malloc.h>
#include <string.h> //for memcpy

//macros
#define FIRMWARE_VERSION 5			//firmware version number
#define MAXSPEED 0xFFFF				//in pps
#define MINSPEED 7					//in pps
#define MAXFRAMESIZE 0xE00			//in points
#define WDT_PERIOD 500				//watchdog timer period in ms

//global variables
uint16_t frameSize = 0;					//size of frame buffer in points
uint16_t framePos = 0;					//current position in frame in points
uint16_t newFrameSize = 0;				//incoming frame total size in points
bool newFrameReady = false;				//signals a new frame has been received and is ready to play when the current one ends
bool playing = false;					//signals a point should be output next systick
uint32_t outputSpeed = 20000;			//points per second rate
bool notRepeat = true;					//signals that current frame should be only be played once even if no new frame arrives before it ends
bool newNotRepeat = true;				//notRepeat value for pending frame
bool stopFlag = false;					//delayed stop in effect, won't write new frame during this period
uint32_t stopTimerCounts;				//num of cycles to delay stop, defined in timer_init
uint32_t posData;						//XY position data
uint8_t sdkVersion = 4;					//host driver version, for backwards compatibility 
bool connected = false;					//connected to host driver or not

uint8_t* frameAddress;					//frame currently being played
uint8_t* newFrameAddress;				//buffer to receive usb transfer with frame
uint8_t* usbInterruptBufferAddress;		//usb interrupt transfer buffer

//functions
void speed_set(uint32_t rate);			//sets up the systick interrupt to match the playback rate (in pps)
void shutter_set(bool level);			//sets the shutter level
void statusled_set(bool level);			//sets the status LED level
void point_output(void);				//outputs current point (controlled by framePos and frameAddress variables)
void stop(void);						//blanks and centers output and stops playback (plus timed safety period)
void stop_weak(void);					//blanks and centers output and stops playback
void spi_init(void);					//sets up SPI module
void dac_init(void);					//sets up DACC module
void iopins_init(void);					//sets up IO module and pins
void timer_init(void);					//sets up TC0 module for stop delay timer
void wdt_setup(void);					//initialize watchdog timer
void assign_default_name(void);			//on first ever boot, assign default name and store to flash
void update_status(void);				//sends the new status to the host driver

//USB transfer interrupts
void usb_bulk_out_callback(udd_ep_status_t status, iram_size_t length, udd_ep_id_t ep);
void usb_interrupt_out_callback(udd_ep_status_t status, iram_size_t length, udd_ep_id_t ep);


// Below is part of setup to make Windows automatically install driver when plugged in
// Credits: https://github.com/cjameshuff/m1k-fw

/// Microsoft WCID descriptor
typedef struct USB_MicrosoftCompatibleDescriptor_Interface {
	uint8_t bFirstInterfaceNumber;
	uint8_t reserved1;
	uint8_t compatibleID[8];
	uint8_t subCompatibleID[8];
	uint8_t reserved2[6];
} __attribute__((packed)) USB_MicrosoftCompatibleDescriptor_Interface;

typedef struct USB_MicrosoftCompatibleDescriptor {
	uint32_t dwLength;
	uint16_t bcdVersion;
	uint16_t wIndex;
	uint8_t bCount;
	uint8_t reserved[7];
	USB_MicrosoftCompatibleDescriptor_Interface interfaces[];
} __attribute__((packed)) USB_MicrosoftCompatibleDescriptor;

#endif /* MAIN_H_ */