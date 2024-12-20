// Many functions taken from idtfPlayer/main.cpp: Copyright (c) 2016 DexLogic, Dirk Apitz. MIT License

// Functions for ILDA Digital Network DAC communication

#include "idn.h"
#include <thread>


// -------------------------------------------------------------------------------------------------
//  Tools
// -------------------------------------------------------------------------------------------------

void logError(const char* fmt, ...)
{
	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	vprintf(fmt, arg_ptr);

	return; // skip

	/*va_list arg_ptr;
	va_start(arg_ptr, fmt);

	//printf("\x1B[1;31m");
	vprintf(fmt, arg_ptr);
	//printf("\x1B[0m");
	printf("\n");
	fflush(stdout);*/
}


void logInfo(const char* fmt, ...)
{
#ifndef NDEBUG
	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	vprintf(fmt, arg_ptr);
#endif

	return; // skip

	/*va_list arg_ptr;
	va_start(arg_ptr, fmt);

	vprintf(fmt, arg_ptr);
	printf("\n");
	fflush(stdout);*/
}


static char int2Hex(unsigned i)
{
	i &= 0xf;
	return (char)((i > 9) ? ((i - 10) + 'A') : (i + '0'));
}


static int idnSend(void* context, IDNHDR_PACKET* packetHdr, unsigned packetLen)
{
	IDNCONTEXT* ctx = (IDNCONTEXT*)context;

	if (sendto(ctx->fdSocket, (const char*)packetHdr, packetLen, 0, (struct sockaddr*)&ctx->serverSockAddr, sizeof(ctx->serverSockAddr)) < 0)
	{
		logError("sendto() failed (error: %d)\n", plt_sockGetLastError());
		return -1;
	}

	return 0;
}


// -------------------------------------------------------------------------------------------------
//  IDN
// -------------------------------------------------------------------------------------------------


int idnMakeConfigXYRGBI(IDNCONTEXT* ctx, IDNHDR_CHANNEL_CONFIG* configPointer)
{
	configPointer->wordCount = 4;
	configPointer->flags = IDNFLG_CHNCFG_ROUTING | (((ctx->serviceDataMatch & 1) | 2) << 4);
	configPointer->serviceID = ctx->serviceId;
	configPointer->serviceMode = IDNVAL_SMOD_LPGRF_CONTINUOUS;

	// Standard IDTF-to-IDN descriptors
	uint16_t* descriptors = (uint16_t*)&configPointer[1];
	descriptors[0] = htons(0x4200);     // X
	descriptors[1] = htons(0x4010);     // 16 bit precision
	descriptors[2] = htons(0x4210);     // Y
	descriptors[3] = htons(0x4010);     // 16 bit precision
	descriptors[4] = htons(0x527E);     // Red, 638 nm
	descriptors[5] = htons(0x5214);     // Green, 532 nm
	descriptors[6] = htons(0x51CC);     // Blue, 460 nm
	descriptors[7] = htons(0x5C10);     // Intensity, legacy signal

	return 0;
}

int idnOpenFrameXYRGBI(IDNCONTEXT* context, bool forceNewConfig)
{
	IDNCONTEXT* ctx = context;

	if (ctx->frameReady)
		return -1;

	if (ctx->isStoppedOrTimeout)
		ctx->frameTimestamp = plt_getMonoTimeUS();

	ctx->queuedBufferPosition = ctx->queuedBufferPtr + 100;
	ctx->queuedFrameSampleCnt = 0;
	ctx->queuedFrameBytesPerSample = XYRGBI_SAMPLE_SIZE;

	return 0;
}


int idnPutSampleXYRGBI(IDNCONTEXT* context, int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t i)
{
	IDNCONTEXT* ctx = context;

	// Sanity check
	if (ctx->queuedBufferPosition == (uint8_t*)0)
		return -1;

	// Get pointer to next sample
	uint8_t* p = ctx->queuedBufferPosition;

	// Store galvo sample bytes
	*p++ = (uint8_t)(x >> 8);
	*p++ = (uint8_t)x;
	*p++ = (uint8_t)(y >> 8);
	*p++ = (uint8_t)y;

	// Store color sample bytes
	*p++ = r;
	*p++ = g;
	*p++ = b;
	*p++ = i;

	// Update pointer to next sample, update sample count
	ctx->queuedBufferPosition += XYRGBI_SAMPLE_SIZE;
	ctx->queuedFrameSampleCnt++;

	return 0;
}

int idnMakeConfigHighResXYRGB(IDNCONTEXT* ctx, IDNHDR_CHANNEL_CONFIG* configPointer)
{
	configPointer->wordCount = 5;
	configPointer->flags = IDNFLG_CHNCFG_ROUTING | (((ctx->serviceDataMatch & 1) | 2) << 4);
	configPointer->serviceID = ctx->serviceId;
	configPointer->serviceMode = IDNVAL_SMOD_LPGRF_CONTINUOUS;

	// Standard IDTF-to-IDN descriptors
	uint16_t* descriptors = (uint16_t*)&configPointer[1];
	descriptors[0] = htons(0x4200);     // X
	descriptors[1] = htons(0x4010);     // 16 bit precision
	descriptors[2] = htons(0x4210);     // Y
	descriptors[3] = htons(0x4010);     // 16 bit precision
	descriptors[4] = htons(0x527E);     // Red, 638 nm
	descriptors[5] = htons(0x4010);     // 16 bit precision
	descriptors[6] = htons(0x5214);     // Green, 532 nm
	descriptors[7] = htons(0x4010);     // 16 bit precision
	descriptors[8] = htons(0x51CC);     // Blue, 460 nm
	descriptors[9] = htons(0x4010);     // 16 bit precision

	return 0;
}



int idnOpenFrameHighResXYRGB(IDNCONTEXT* context, bool forceNewConfig)
{
	IDNCONTEXT* ctx = context;

	if (ctx->frameReady)
		return -1;

	if (ctx->isStoppedOrTimeout)
		ctx->frameTimestamp = plt_getMonoTimeUS();

	ctx->queuedBufferPosition = ctx->queuedBufferPtr + 100;
	ctx->queuedFrameSampleCnt = 0;
	ctx->queuedFrameBytesPerSample = XYRGB_HIGHRES_SAMPLE_SIZE;

	return 0;
}

int idnPutSampleHighResXYRGB(IDNCONTEXT* context, int16_t x, int16_t y, uint16_t r, uint16_t g, uint16_t b)
{
	IDNCONTEXT* ctx = context;

	// Sanity check
	if (ctx->queuedBufferPosition == (uint8_t*)0)
		return -1;

	// Get pointer to next sample
	uint8_t* p = ctx->queuedBufferPosition;

	// Store galvo sample bytes
	*p++ = (uint8_t)(x >> 8);
	*p++ = (uint8_t)x;
	*p++ = (uint8_t)(y >> 8);
	*p++ = (uint8_t)y;

	// Store color sample bytes
	*p++ = (uint8_t)(r >> 8);
	*p++ = (uint8_t)r;
	*p++ = (uint8_t)(g >> 8);
	*p++ = (uint8_t)g;
	*p++ = (uint8_t)(b >> 8);
	*p++ = (uint8_t)b;

	// Update pointer to next sample, update sample count
	ctx->queuedBufferPosition += XYRGB_HIGHRES_SAMPLE_SIZE;
	ctx->queuedFrameSampleCnt++;

	return 0;
}


int idnMakeConfigExtended(IDNCONTEXT* ctx, IDNHDR_CHANNEL_CONFIG* configPointer)
{
	configPointer->wordCount = 10;
	configPointer->flags = IDNFLG_CHNCFG_ROUTING | (((ctx->serviceDataMatch & 1) | 2) << 4);
	configPointer->serviceID = ctx->serviceId;
	configPointer->serviceMode = IDNVAL_SMOD_LPGRF_CONTINUOUS;

	// Standard IDTF-to-IDN descriptors
	uint16_t* descriptors = (uint16_t*)&configPointer[1];
	descriptors[0] = htons(0x4200);     // X
	descriptors[1] = htons(0x4010);     // 16 bit precision
	descriptors[2] = htons(0x4210);     // Y
	descriptors[3] = htons(0x4010);     // 16 bit precision
	descriptors[4] = htons(0x527E);     // Red, 638 nm
	descriptors[5] = htons(0x4010);     // 16 bit precision
	descriptors[6] = htons(0x5214);     // Green, 532 nm
	descriptors[7] = htons(0x4010);     // 16 bit precision
	descriptors[8] = htons(0x51CC);     // Blue, 460 nm
	descriptors[9] = htons(0x4010);     // 16 bit precision
	descriptors[10] = htons(0x5C10);     // Intensity, legacy signal
	descriptors[11] = htons(0x4010);     // 16 bit precision
	descriptors[12] = htons(0x51BD);     // User 1 (Here configured as deep blue)
	descriptors[13] = htons(0x4010);     // 16 bit precision
	descriptors[14] = htons(0x5241);     // User 2 (Here configured as yellow)
	descriptors[15] = htons(0x4010);     // 16 bit precision
	descriptors[16] = htons(0x51E8);     // User 3 (Here configured as cyan)
	descriptors[17] = htons(0x4010);     // 16 bit precision
	descriptors[18] = htons(0x4201);     // User 4 (Here configured as X-prime)
	descriptors[19] = htons(0x4010);     // 16 bit precision

	return 0;
}



int idnOpenFrameExtended(IDNCONTEXT* context, bool forceNewConfig)
{
	IDNCONTEXT* ctx = context;

	if (ctx->frameReady)
		return -1;

	if (ctx->isStoppedOrTimeout)
		ctx->frameTimestamp = plt_getMonoTimeUS();

	ctx->queuedBufferPosition = ctx->queuedBufferPtr + 100;
	ctx->queuedFrameSampleCnt = 0;
	ctx->queuedFrameBytesPerSample = EXTENDED_SAMPLE_SIZE;

	return 0;
}

int idnPutSampleExtended(IDNCONTEXT* context, int16_t x, int16_t y, uint16_t r, uint16_t g, uint16_t b, uint16_t i, uint16_t u1, uint16_t u2, uint16_t u3, uint16_t u4)
{
	IDNCONTEXT* ctx = context;

	// Sanity check
	if (ctx->queuedBufferPosition == (uint8_t*)0)
		return -1;

	// Get pointer to next sample
	uint8_t* p = ctx->queuedBufferPosition;

	// Store galvo sample bytes
	*p++ = (uint8_t)(x >> 8);
	*p++ = (uint8_t)x;
	*p++ = (uint8_t)(y >> 8);
	*p++ = (uint8_t)y;

	// Store color sample bytes
	*p++ = (uint8_t)(r >> 8);
	*p++ = (uint8_t)r;
	*p++ = (uint8_t)(g >> 8);
	*p++ = (uint8_t)g;
	*p++ = (uint8_t)(b >> 8);
	*p++ = (uint8_t)b;
	*p++ = (uint8_t)(i >> 8);
	*p++ = (uint8_t)i;
	*p++ = (uint8_t)(u1 >> 8);
	*p++ = (uint8_t)u1;
	*p++ = (uint8_t)(u2 >> 8);
	*p++ = (uint8_t)u2;
	*p++ = (uint8_t)(u3 >> 8);
	*p++ = (uint8_t)u3;
	*p++ = (uint8_t)(u4 >> 8);
	*p++ = (uint8_t)u4;

	// Update pointer to next sample, update sample count
	ctx->queuedBufferPosition += EXTENDED_SAMPLE_SIZE;
	ctx->queuedFrameSampleCnt++;

	return 0;
}


int idnPushFrame(IDNCONTEXT* context)
{
	IDNCONTEXT* ctx = context;

	if (ctx->sendBufferPosition == (uint8_t*)0)
	{
		// No frame is currently playing
		if (ctx->frameReady)
		{
			// New frame queued, start playing it
			ctx->sendBufferPosition = ctx->queuedBufferPtr + 100;
			ctx->bytesPerSample = ctx->queuedFrameBytesPerSample;
			ctx->sampleCnt = ctx->queuedFrameSampleCnt;
			ctx->scanSpeed = ctx->queuedFrameScanSpeed;

			uint8_t* tempPointer = ctx->bufferPtr;
			ctx->bufferPtr = ctx->queuedBufferPtr;
			ctx->queuedBufferPtr = tempPointer;
			ctx->queuedBufferPosition = (uint8_t*)0;

			ctx->frameReady = false;
		}
		else
		{
			// No new frame in queue, underrun. Timeout if this persists for 200 us
			if (!ctx->isStoppedOrTimeout && (plt_getMonoTimeUS() > (ctx->frameTimestamp + ((uint64_t)ctx->sampleCnt * 1000000ull) / (uint64_t)ctx->scanSpeed + 200)))
			{
				ctx->isStoppedOrTimeout = true;
				logError("[IDN] Buffer underrun. Send frames faster, or make them bigger to get more leeway.\n");
			}

			return -1;
		}
	}
	//printf("Sending frame\n");

	if (ctx->scanSpeed == 0) { logError("[IDN] Invalid scan speed 0"); return -1; }
	if (ctx->sampleCnt < 20) { logError("[IDN] Invalid sample count %u", ctx->sampleCnt); return -1; }

	// ---------------------------------------------------------------------------------------------

	uint64_t now = plt_getMonoTimeUS();
	bool newConfig = ctx->frameCnt == 0 || ((now - ctx->cfgTimestamp) > 250000);
	if (ctx->bytesPerSample != ctx->previousBytesPerSample)
	{
		newConfig = true;
		ctx->serviceDataMatch++;
	}
	uint16_t contentID = IDNFLG_CONTENTID_CHANNELMSG;
	contentID |= (((ctx->serviceId - 1) & 0x3F) << 8); // channel ID

	uint8_t* samples = ctx->sendBufferPosition;
	IDNHDR_SAMPLE_CHUNK* sampleChunkHeader = (IDNHDR_SAMPLE_CHUNK*)((uint8_t*)samples - sizeof(IDNHDR_SAMPLE_CHUNK));
	IDNHDR_CHANNEL_MESSAGE* channelMessageHeader;
	if (newConfig)
	{
		IDNHDR_CHANNEL_CONFIG* channelConfig = (IDNHDR_CHANNEL_CONFIG*)((uint8_t*)sampleChunkHeader - ctx->bytesPerSample * 2 - sizeof(IDNHDR_CHANNEL_CONFIG));
		if (ctx->bytesPerSample == XYRGBI_SAMPLE_SIZE)
			idnMakeConfigXYRGBI(ctx, channelConfig);
		else if (ctx->bytesPerSample == XYRGB_HIGHRES_SAMPLE_SIZE)
			idnMakeConfigHighResXYRGB(ctx, channelConfig);
		else if (ctx->bytesPerSample == EXTENDED_SAMPLE_SIZE)
			idnMakeConfigExtended(ctx, channelConfig);
		else
		{
			logError("[IDN] Invalid number of bytes per sample %u", ctx->bytesPerSample);
			return -1;
		}

		channelMessageHeader = (IDNHDR_CHANNEL_MESSAGE*)((uint8_t*)channelConfig - sizeof(IDNHDR_CHANNEL_MESSAGE));
		contentID |= IDNFLG_CONTENTID_CONFIG_LSTFRG;
		ctx->previousBytesPerSample = ctx->bytesPerSample;
		ctx->cfgTimestamp = now;
	}
	else
		channelMessageHeader = (IDNHDR_CHANNEL_MESSAGE*)((uint8_t*)sampleChunkHeader - sizeof(IDNHDR_CHANNEL_MESSAGE));
	IDNHDR_PACKET* packetHeader = (IDNHDR_PACKET*)((uint8_t*)channelMessageHeader - sizeof(IDNHDR_PACKET));

	packetHeader->command = IDNCMD_RT_CNLMSG;
	packetHeader->flags = ctx->clientGroup;
	packetHeader->sequence = htons(ctx->sequence++); // Set IDN-Hello sequence number (used on UDP for lost packet tracking)

	unsigned int headerSize = samples - (uint8_t*)packetHeader;
	unsigned int maxSamplesPerPacket = ((MAX_IDN_MESSAGE_LEN * context->packetNumFragments) - headerSize) / ctx->bytesPerSample;
	unsigned int numPacketsNeeded = (ctx->sampleCnt / maxSamplesPerPacket) + 1;
	unsigned int samplesInPacket = ctx->sampleCnt / numPacketsNeeded;
	//unsigned int samplesInPacket = (MAX_IDN_MESSAGE_LEN - headerSize) / ctx->bytesPerSample;
	//if (samplesInPacket > ctx->sampleCnt)
	//	samplesInPacket = ctx->sampleCnt;
	//else if (ctx->sampleCnt - samplesInPacket < 20 && samplesInPacket > 40)
	//	samplesInPacket -= 20;
	uint32_t duration = ((uint64_t)samplesInPacket * 1000000ull) / (uint64_t)ctx->scanSpeed;
	unsigned int msgLength = headerSize + samplesInPacket * ctx->bytesPerSample;

	channelMessageHeader->totalSize = htons(msgLength - sizeof(IDNHDR_MESSAGE));
	channelMessageHeader->contentID = htons(contentID | IDNVAL_CNKTYPE_LPGRF_WAVE);
	channelMessageHeader->timestamp = htonl((uint32_t)ctx->frameTimestamp);

	uint8_t frameFlags = (((ctx->serviceDataMatch & 1) | 2) << 4);

	sampleChunkHeader->flagsDuration = htonl((frameFlags << 24) | duration);

	ctx->frameTimestamp += duration;
	ctx->sampleCnt -= samplesInPacket;
	ctx->sendBufferPosition += samplesInPacket * ctx->bytesPerSample;
	ctx->frameCnt++;

	// Send the packet
	if (idnSend(ctx, packetHeader, msgLength) != 0)
	{
		ctx->sendBufferPosition = (uint8_t*)0;
		return -1;
	}

	if (ctx->sampleCnt <= 0 || (ctx->sendBufferPosition + ctx->sampleCnt * ctx->bytesPerSample) > (ctx->bufferPtr + ctx->bufferLen))
	{
		ctx->sendBufferPosition = (uint8_t*)0; // Frame done. Invalidate payload - cause error in case of invalid call order
	}

	return 0;
}


/*int idnSendVoid(IDNCONTEXT* context)
{
	IDNCONTEXT* ctx = context;

	// IDN-Hello packet header
	IDNHDR_PACKET* packetHdr = (IDNHDR_PACKET*)ctx->bufferPtr + ctx->bufferLen - 200; // todo make dedicated buffer
	packetHdr->command = IDNCMD_RT_CNLMSG;
	packetHdr->flags = ctx->clientGroup;
	packetHdr->sequence = htons(ctx->sequence++);

	// IDN-Stream channel message header
	IDNHDR_CHANNEL_MESSAGE* channelMsgHdr = (IDNHDR_CHANNEL_MESSAGE*)&packetHdr[1];
	uint16_t contentID = IDNFLG_CONTENTID_CHANNELMSG | IDNVAL_CNKTYPE_VOID;
	contentID |= (((ctx->serviceId - 1) & 0x3F) << 8); // channel ID
	channelMsgHdr->contentID = htons(contentID);

	// Pointer to the end of the buffer for message length and packet length calculation
	ctx->sendBufferPosition = (uint8_t*)&channelMsgHdr[1];

	// Populate message header fields
	channelMsgHdr->totalSize = htons((unsigned short)(ctx->payload - (uint8_t*)channelMsgHdr));
	//ctx->frameTimestamp = plt_getMonoTimeUS();
	channelMsgHdr->timestamp = htonl((uint32_t)plt_getMonoTimeUS());
	ctx->frameCnt = 0;

	// Send the packet
	if (idnSend(context, packetHdr, ctx->payload - (uint8_t*)packetHdr))
		return -1;
		
	return 0;
}*/


int idnSendClose(IDNCONTEXT* context)
{
	IDNCONTEXT* ctx = context;

	// Close the channel: IDN-Hello packet header
	IDNHDR_PACKET* packetHdr = (IDNHDR_PACKET*)ctx->controlBufferPtr;
	packetHdr->command = IDNCMD_RT_CNLMSG;
	packetHdr->flags = ctx->clientGroup;
	packetHdr->sequence = htons(ctx->sequence++);

	// IDN-Stream channel message header
	IDNHDR_CHANNEL_MESSAGE* channelMsgHdr = (IDNHDR_CHANNEL_MESSAGE*)&packetHdr[1];
	uint16_t contentID = IDNFLG_CONTENTID_CHANNELMSG | IDNFLG_CONTENTID_CONFIG_LSTFRG | IDNVAL_CNKTYPE_VOID;
	contentID |= (((ctx->serviceId - 1) & 0x3F) << 8); // channel ID
	channelMsgHdr->contentID = htons(contentID);

	// IDN-Stream channel config header (close channel)
	IDNHDR_CHANNEL_CONFIG* channelConfigHdr = (IDNHDR_CHANNEL_CONFIG*)&channelMsgHdr[1];
	channelConfigHdr->wordCount = 0;
	channelConfigHdr->flags = IDNFLG_CHNCFG_CLOSE;
	channelConfigHdr->serviceID = ctx->serviceId;
	channelConfigHdr->serviceMode = 0;

	uint8_t* bufferEndPosition = (uint8_t*)&channelConfigHdr[1];

	// Populate message header fields
	channelMsgHdr->totalSize = htons((unsigned short)(bufferEndPosition - (uint8_t*)channelMsgHdr));
	channelMsgHdr->timestamp = htonl((uint32_t)plt_getMonoTimeUS());

	// Send the packet
	if (idnSend(context, packetHdr, bufferEndPosition - (uint8_t*)packetHdr))
		return -1;

	// ---------------------------------------------------------------------------------------------

	// Close the connection/session: IDN-Hello packet header
	packetHdr->command = IDNCMD_RT_CNLMSG_CLOSE;
	packetHdr->flags = ctx->clientGroup;
	packetHdr->sequence = htons(ctx->sequence++);

	// Send the packet (gracefully close session)
	if (idnSend(context, packetHdr, sizeof(IDNHDR_PACKET)))
		return -1;
		
	return 0;
}

