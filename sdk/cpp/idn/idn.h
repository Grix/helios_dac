// -------------------------------------------------------------------------------------------------
//  File idn.h
//
//  07/2013 Dirk Apitz, created
//  01/2015 Dirk Apitz, IDN standard draft, separate stream header file
//  05/2016 Dirk Apitz, separate hello header file
//  10/2024 Gitle Mikkelsen, extended with more types of data frames, like high res and 8 color channels
// -------------------------------------------------------------------------------------------------


#include "idn-stream.h"
#include "idn-hello.h"
#include <vector>
#include <string>


#ifndef IDN_H
#define IDN_H


// Standard libraries
#include <stdint.h>
#include <stdio.h>


// -------------------------------------------------------------------------------------------------
//  Defines
// -------------------------------------------------------------------------------------------------

#define IDN_PORT                            7255


// -------------------------------------------------------------------------------------------------
//  Messages
// -------------------------------------------------------------------------------------------------

typedef struct
{
    uint16_t totalSize;
    uint16_t contentID;
    
} IDNHDR_MESSAGE;

// Many functions taken from idtfPlayer/main.cpp: Copyright (c) 2016 DexLogic, Dirk Apitz. MIT License


#if defined(_WIN32) || defined(WIN32)
	//#include <windows.h>
	#include <tchar.h>
#else
	#include <stdlib.h>
	#include <unistd.h>
	#include <string.h>
	#include <arpa/inet.h>
#endif

#include <time.h>

#if defined(_WIN32) || defined(WIN32)

	#include "plt-windows.h"

#else

	#include <stdlib.h>
	#include <ifaddrs.h>

	#include "plt-posix.h"
	#include <netdb.h>

#endif


// -------------------------------------------------------------------------------------------------
//  Defines
// -------------------------------------------------------------------------------------------------

#define DEFAULT_FRAMERATE               30
#define DEFAULT_SCANSPEED               30000

#define MAX_IDN_MESSAGE_LEN             0xFF00      // IDN-Message maximum length (due to lower layer transport)
//#define MAX_IDN_MESSAGE_LEN             0x0800      // Message len for fragmentation tests

#define XYRGB_SAMPLE_SIZE               7
#define XYRGBI_SAMPLE_SIZE              8
#define XYRGB_HIGHRES_SAMPLE_SIZE       10
#define EXTENDED_SAMPLE_SIZE			20



// -------------------------------------------------------------------------------------------------
//  Typedefs
// -------------------------------------------------------------------------------------------------

typedef struct
{
	int fdSocket;                           // Socket file descriptor
	struct sockaddr_in serverSockAddr;      // Target server address
	unsigned char clientGroup;              // Client group to send on
	//unsigned usFrameTime;                   // Time for one frame in microseconds (1000000/frameRate)
	int jitterFreeFlag;                     // Scan frames only once to exactly match frame rate
	unsigned scanSpeed;                     // Scan speed in samples per second

	unsigned bufferLen;                     // Length of work buffer
	uint8_t* bufferPtr;                     // Pointer to work buffer

	uint32_t startTime;                     // System time at stream start (log reference)
	uint32_t frameCnt;                      // Number of sent frames
	uint32_t startTimestamp;				// Timestamp of first frame in current active session
	uint32_t frameTimestamp;                // Timestamp of the last frame
	uint32_t cfgTimestamp;                  // Timestamp of the last channel configuration

	// Buffer related
	uint8_t* payload;                       // Pointer to the end of the buffer

	// IDN-Hello related
	uint16_t sequence;                      // IDN-Hello sequence number (UDP packet tracking)

	// IDN-Stream related
	IDNHDR_SAMPLE_CHUNK* sampleChunkHdr;    // Current sample chunk header
	uint32_t sampleCnt;                     // Current number of samples

	std::string name;
	int serviceId;


} IDNCONTEXT;


void logError(const char* fmt, ...);
void logInfo(const char* fmt, ...);
static char int2Hex(unsigned i);
//void binDump(void* buffer, unsigned length);
static int idnSend(void* context, IDNHDR_PACKET* packetHdr, unsigned packetLen);
int idnOpenFrameGeneric(IDNCONTEXT* context, uint16_t* channelDescriptors, size_t numChannelDescriptors, bool forceNewConfig);
int idnPutSampleGeneric(IDNCONTEXT* context, int8_t* sampleBuffer, size_t sampleBufferSize);
int idnOpenFrameXYRGB(IDNCONTEXT* context);
int idnPutSampleXYRGB(IDNCONTEXT* context, int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b);
int idnOpenFrameXYRGBI(IDNCONTEXT* context);
int idnPutSampleXYRGBI(IDNCONTEXT* context, int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t i);
int idnOpenFrameHighResXYRGB(IDNCONTEXT* context);
int idnPutSampleHighResXYRGB(IDNCONTEXT* context, int16_t x, int16_t y, uint16_t r, uint16_t g, uint16_t b);
int idnOpenFrameExtended(IDNCONTEXT* context);
int idnPutSampleExtended(IDNCONTEXT* context, int16_t x, int16_t y, uint16_t r, uint16_t g, uint16_t b, uint16_t i, uint16_t u1, uint16_t u2, uint16_t u3, uint16_t u4);
int idnPushFrame(IDNCONTEXT* context);
int idnSendVoid(IDNCONTEXT* context);
int idnSendClose(IDNCONTEXT* context);


#endif
