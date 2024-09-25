// Many functions taken from idtfPlayer/main.cpp: Copyright (c) 2016 DexLogic, Dirk Apitz. MIT License

// Functions for ILDA Digital Network DAC communication

#include "idn.h"



static uint8_t gbl_packetBuffer[0x10000];   // Work buffer

// -------------------------------------------------------------------------------------------------
//  Tools
// -------------------------------------------------------------------------------------------------

void logError(const char* fmt, ...)
{
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


/*void binDump(void* buffer, unsigned length)
{
	if (!length || !buffer) return;

	char send[80];
	char* dst1 = 0, *dst2 = 0;
	char* src = (char*)buffer;
	unsigned k = 0;

	printf("dump buffer %08X; %d Bytes\n", (uint32_t)(uintptr_t)buffer, length);

	while (k < length)
	{
		if (!dst1)
		{
			memset(send, ' ', 80);
			send[79] = 0;

			send[0] = int2Hex((k >> 12) & 0x0f);
			send[1] = int2Hex((k >> 8) & 0x0f);
			send[2] = int2Hex((k >> 4) & 0x0f);
			send[3] = int2Hex(k & 0x0f);
			dst1 = &send[5];
			dst2 = &send[57];
		}

		unsigned char c = *src++;
		*dst1++ = int2Hex(c >> 4);
		*dst1++ = int2Hex(c);
		*dst1++ = ' ';
		if ((k % 16) == 7)
		{
			*dst1++ = ' '; *dst1++ = ' ';
		}
		if (c < 0x20) c = '.';
		if (c > 0x7F) c = '.';
		*dst2++ = c;

		if ((k % 16) == 15)
		{
			*dst2++ = 0;
			printf("%s\n", send);
			dst1 = 0;
			dst2 = 0;
		}
		k++;
	}

	if (k % 16) printf("%s\n", send);

	fflush(stdout);
}*/


static int idnSend(void* context, IDNHDR_PACKET* packetHdr, unsigned packetLen)
{
	IDNCONTEXT* ctx = (IDNCONTEXT*)context;

	/*
		printf("\n%u\n", (plt_getMonoTimeUS() - ctx->startTime) / 1000);
		binDump(packetHdr, packetLen);
	*/

	if (sendto(ctx->fdSocket, (const char*)packetHdr, packetLen, 0, (struct sockaddr*)&ctx->serverSockAddr, sizeof(ctx->serverSockAddr)) < 0)
	{
		logError("sendto() failed (error: %d)", plt_sockGetLastError());
		return -1;
	}

	return 0;
}


// -------------------------------------------------------------------------------------------------
//  IDN
// -------------------------------------------------------------------------------------------------


int idnOpenFrameGeneric(IDNCONTEXT* context, uint16_t* channelDescriptors, size_t numChannelDescriptors, bool forceNewConfig)
{
	IDNCONTEXT* ctx = context;

	// IDN-Hello packet header. Note: Sequence number populated on push
	IDNHDR_PACKET* packetHdr = (IDNHDR_PACKET*)ctx->bufferPtr;
	packetHdr->command = IDNCMD_RT_CNLMSG;
	packetHdr->flags = ctx->clientGroup;

	// ---------------------------------------------------------------------------------------------

	// IDN-Stream channel message header. Note: Remaining fields populated on push
	IDNHDR_CHANNEL_MESSAGE* channelMsgHdr = (IDNHDR_CHANNEL_MESSAGE*)&packetHdr[1];
	uint16_t contentID = IDNFLG_CONTENTID_CHANNELMSG;
	contentID |= (((ctx->serviceId - 1) & 0x3F) << 8); // channel ID

	// Insert channel config header every 250 ms
	unsigned now = plt_getMonoTimeUS();
	IDNHDR_SAMPLE_CHUNK* sampleChunkHdr = (IDNHDR_SAMPLE_CHUNK*)&channelMsgHdr[1];
	if (forceNewConfig || (ctx->frameCnt == 0) || ((now - ctx->cfgTimestamp) > 250000))
	{
		// IDN-Stream channel configuration header update
		IDNHDR_CHANNEL_CONFIG* channelConfigHdr = (IDNHDR_CHANNEL_CONFIG*)sampleChunkHdr;
		channelConfigHdr->wordCount = numChannelDescriptors / 2;
		if (numChannelDescriptors % 2 == 1)
			channelConfigHdr->wordCount++;
		channelConfigHdr->flags = IDNFLG_CHNCFG_ROUTING;
		channelConfigHdr->serviceID = ctx->serviceId;
		channelConfigHdr->serviceMode = IDNVAL_SMOD_LPGRF_DISCRETE;

		uint16_t* descriptors = (uint16_t*)&channelConfigHdr[1];
		int i;
		for (i = 0; i < numChannelDescriptors; i++)
			descriptors[i] = htons(channelDescriptors[i]);

		if (numChannelDescriptors % 2 == 1)
			descriptors[i++] = htons(0x0000);     // Void for alignment

		// Move sample chunk start and set flag in contentID field
		sampleChunkHdr = (IDNHDR_SAMPLE_CHUNK*)&descriptors[i];
		contentID |= IDNFLG_CONTENTID_CONFIG_LSTFRG;

		ctx->cfgTimestamp = now;
	}
	channelMsgHdr->contentID = htons(contentID);

	// ---------------------------------------------------------------------------------------------

	// Chunk data pointer setup
	ctx->sampleChunkHdr = sampleChunkHdr;
	ctx->payload = (uint8_t*)&sampleChunkHdr[1];
	ctx->sampleCnt = 0;

	return 0;
}


int idnPutSampleGeneric(IDNCONTEXT* context, int8_t* sampleBuffer, size_t sampleBufferSize)
{
	IDNCONTEXT* ctx = context;

	// Sanity check
	if (ctx->payload == (uint8_t*)0)
		return -1;

	// Make sure there is enough buffer. Note: payload and bufferPtr are (uint8_t *) - and 
	// pointer substraction is defined as the difference of (array) elements.
	unsigned lenUsed = (unsigned)(ctx->payload - ctx->bufferPtr);
	unsigned lenNeeded = lenUsed + (sampleBufferSize);


	// Note: With IDN, the first two points and the last two points of a frame have special 
	// meanings, The first point is the start point and shall be invisible (not part of the frame, 
	// not taken into account with duration calculations) and is used to move the draw cursor 
	// only. This is because a shape of n points has n-1 connecting segments (with associated time
	// and color). The shape is closed when last point and first point are equal and the shape is
	// continuous when first segment and last segment are continuous. Hidden lines or bends shall 
	// be inserted on the fly in case of differing start point and end point or discontinuity.


	// Get pointer to next sample
	uint8_t* p = ctx->payload;

	memcpy(p, sampleBuffer, sampleBufferSize);

	// Update pointer to next sample, update sample count
	ctx->payload += sampleBufferSize;
	ctx->sampleCnt++;

	return 0;
}



int idnOpenFrameXYRGBI(IDNCONTEXT* context)
{
	IDNCONTEXT* ctx = context;

	// IDN-Hello packet header. Note: Sequence number populated on push
	IDNHDR_PACKET* packetHdr = (IDNHDR_PACKET*)ctx->bufferPtr;
	packetHdr->command = IDNCMD_RT_CNLMSG;
	packetHdr->flags = ctx->clientGroup;

	// ---------------------------------------------------------------------------------------------

	// IDN-Stream channel message header. Note: Remaining fields populated on push
	IDNHDR_CHANNEL_MESSAGE* channelMsgHdr = (IDNHDR_CHANNEL_MESSAGE*)&packetHdr[1];
	uint16_t contentID = IDNFLG_CONTENTID_CHANNELMSG;
	contentID |= (((ctx->serviceId - 1) & 0x3F) << 8); // channel ID

	// Insert channel config header every 250 ms
	unsigned now = plt_getMonoTimeUS();
	IDNHDR_SAMPLE_CHUNK* sampleChunkHdr = (IDNHDR_SAMPLE_CHUNK*)&channelMsgHdr[1];
	if ((ctx->frameCnt == 0) || ((now - ctx->cfgTimestamp) > 250000))
	{
		// IDN-Stream channel configuration header
		IDNHDR_CHANNEL_CONFIG* channelConfigHdr = (IDNHDR_CHANNEL_CONFIG*)sampleChunkHdr;
		channelConfigHdr->wordCount = 4;
		channelConfigHdr->flags = IDNFLG_CHNCFG_ROUTING;
		channelConfigHdr->serviceID = ctx->serviceId;
		channelConfigHdr->serviceMode = IDNVAL_SMOD_LPGRF_DISCRETE;

		// Standard IDTF-to-IDN descriptors
		uint16_t* descriptors = (uint16_t*)&channelConfigHdr[1];
		descriptors[0] = htons(0x4200);     // X
		descriptors[1] = htons(0x4010);     // 16 bit precision
		descriptors[2] = htons(0x4210);     // Y
		descriptors[3] = htons(0x4010);     // 16 bit precision
		descriptors[4] = htons(0x527E);     // Red, 638 nm
		descriptors[5] = htons(0x5214);     // Green, 532 nm
		descriptors[6] = htons(0x51CC);     // Blue, 460 nm
		descriptors[7] = htons(0x5C10);     // Intensity, legacy signal

		// Move sample chunk start and set flag in contentID field
		sampleChunkHdr = (IDNHDR_SAMPLE_CHUNK*)&descriptors[8];
		contentID |= IDNFLG_CONTENTID_CONFIG_LSTFRG;

		ctx->cfgTimestamp = now;
	}
	channelMsgHdr->contentID = htons(contentID);

	// ---------------------------------------------------------------------------------------------

	// Chunk data pointer setup
	ctx->sampleChunkHdr = sampleChunkHdr;
	ctx->payload = (uint8_t*)&sampleChunkHdr[1];
	ctx->sampleCnt = 0;

	return 0;
}




int idnPutSampleXYRGBI(IDNCONTEXT* context, int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t i)
{
	IDNCONTEXT* ctx = context;

	// Sanity check
	if (ctx->payload == (uint8_t*)0)
		return -1;

	// Make sure there is enough buffer. Note: payload and bufferPtr are (uint8_t *) - and 
	// pointer substraction is defined as the difference of (array) elements.
	unsigned lenUsed = (unsigned)(ctx->payload - ctx->bufferPtr);
	unsigned lenNeeded = lenUsed + (XYRGBI_SAMPLE_SIZE); // Todo remove?


	// Note: With IDN, the first two points and the last two points of a frame have special 
	// meanings, The first point is the start point and shall be invisible (not part of the frame, 
	// not taken into account with duration calculations) and is used to move the draw cursor 
	// only. This is because a shape of n points has n-1 connecting segments (with associated time
	// and color). The shape is closed when last point and first point are equal and the shape is
	// continuous when first segment and last segment are continuous. Hidden lines or bends shall 
	// be inserted on the fly in case of differing start point and end point or discontinuity.


	// Get pointer to next sample
	uint8_t* p = ctx->payload;

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
	ctx->payload += XYRGBI_SAMPLE_SIZE;
	ctx->sampleCnt++;

	return 0;
}



int idnOpenFrameXYRGB(IDNCONTEXT* context)
{
	IDNCONTEXT* ctx = context;

	// IDN-Hello packet header. Note: Sequence number populated on push
	IDNHDR_PACKET* packetHdr = (IDNHDR_PACKET*)ctx->bufferPtr;
	packetHdr->command = IDNCMD_RT_CNLMSG;
	packetHdr->flags = ctx->clientGroup;

	// ---------------------------------------------------------------------------------------------

	// IDN-Stream channel message header. Note: Remaining fields populated on push
	IDNHDR_CHANNEL_MESSAGE* channelMsgHdr = (IDNHDR_CHANNEL_MESSAGE*)&packetHdr[1];
	uint16_t contentID = IDNFLG_CONTENTID_CHANNELMSG;
	contentID |= (((ctx->serviceId - 1) & 0x3F) << 8); // channel ID

	// Insert channel config header every 250 ms
	unsigned now = plt_getMonoTimeUS();
	IDNHDR_SAMPLE_CHUNK* sampleChunkHdr = (IDNHDR_SAMPLE_CHUNK*)&channelMsgHdr[1];
	if ((ctx->frameCnt == 0) || ((now - ctx->cfgTimestamp) > 250000))
	{
		// IDN-Stream channel configuration header
		IDNHDR_CHANNEL_CONFIG* channelConfigHdr = (IDNHDR_CHANNEL_CONFIG*)sampleChunkHdr;
		channelConfigHdr->wordCount = 4;
		channelConfigHdr->flags = IDNFLG_CHNCFG_ROUTING;
		channelConfigHdr->serviceID = ctx->serviceId;
		channelConfigHdr->serviceMode = IDNVAL_SMOD_LPGRF_DISCRETE;

		// Standard IDTF-to-IDN descriptors
		uint16_t* descriptors = (uint16_t*)&channelConfigHdr[1];
		descriptors[0] = htons(0x4200);     // X
		descriptors[1] = htons(0x4010);     // 16 bit precision
		descriptors[2] = htons(0x4210);     // Y
		descriptors[3] = htons(0x4010);     // 16 bit precision
		descriptors[4] = htons(0x527E);     // Red, 638 nm
		descriptors[5] = htons(0x5214);     // Green, 532 nm
		descriptors[6] = htons(0x51CC);     // Blue, 460 nm
		descriptors[7] = htons(0x0000);     // Void for alignment

		// Move sample chunk start and set flag in contentID field
		sampleChunkHdr = (IDNHDR_SAMPLE_CHUNK*)&descriptors[8];
		contentID |= IDNFLG_CONTENTID_CONFIG_LSTFRG;

		ctx->cfgTimestamp = now;
	}
	channelMsgHdr->contentID = htons(contentID);

	// ---------------------------------------------------------------------------------------------

	// Chunk data pointer setup
	ctx->sampleChunkHdr = sampleChunkHdr;
	ctx->payload = (uint8_t*)&sampleChunkHdr[1];
	ctx->sampleCnt = 0;

	return 0;
}




int idnPutSampleXYRGB(IDNCONTEXT* context, int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b)
{
	IDNCONTEXT* ctx = context;

	// Sanity check
	if (ctx->payload == (uint8_t*)0) 
		return -1;

	// Make sure there is enough buffer. Note: payload and bufferPtr are (uint8_t *) - and 
	// pointer substraction is defined as the difference of (array) elements.
	unsigned lenUsed = (unsigned)(ctx->payload - ctx->bufferPtr);
	unsigned lenNeeded = lenUsed + (XYRGB_SAMPLE_SIZE); // Todo remove?

	// Get pointer to next sample
	uint8_t* p = ctx->payload;

	// Store galvo sample bytes
	*p++ = (uint8_t)(x >> 8);
	*p++ = (uint8_t)x;
	*p++ = (uint8_t)(y >> 8);
	*p++ = (uint8_t)y;

	// Store color sample bytes
	*p++ = r;
	*p++ = g;
	*p++ = b;

	// Update pointer to next sample, update sample count
	ctx->payload += XYRGB_SAMPLE_SIZE;
	ctx->sampleCnt++;

	return 0;
}

int idnOpenFrameHighResXYRGB(IDNCONTEXT* context)
{
	IDNCONTEXT* ctx = context;

	// IDN-Hello packet header. Note: Sequence number populated on push
	IDNHDR_PACKET* packetHdr = (IDNHDR_PACKET*)ctx->bufferPtr;
	packetHdr->command = IDNCMD_RT_CNLMSG;
	packetHdr->flags = ctx->clientGroup;

	// ---------------------------------------------------------------------------------------------

	// IDN-Stream channel message header. Note: Remaining fields populated on push
	IDNHDR_CHANNEL_MESSAGE* channelMsgHdr = (IDNHDR_CHANNEL_MESSAGE*)&packetHdr[1];
	uint16_t contentID = IDNFLG_CONTENTID_CHANNELMSG;
	contentID |= (((ctx->serviceId - 1) & 0x3F) << 8); // channel ID

	// Insert channel config header every 250 ms
	unsigned now = plt_getMonoTimeUS();
	IDNHDR_SAMPLE_CHUNK* sampleChunkHdr = (IDNHDR_SAMPLE_CHUNK*)&channelMsgHdr[1];
	if ((ctx->frameCnt == 0) || ((now - ctx->cfgTimestamp) > 250000))
	{
		// IDN-Stream channel configuration header
		IDNHDR_CHANNEL_CONFIG* channelConfigHdr = (IDNHDR_CHANNEL_CONFIG*)sampleChunkHdr;
		channelConfigHdr->wordCount = 5;
		channelConfigHdr->flags = IDNFLG_CHNCFG_ROUTING;
		channelConfigHdr->serviceID = ctx->serviceId;
		channelConfigHdr->serviceMode = IDNVAL_SMOD_LPGRF_DISCRETE;

		uint16_t* descriptors = (uint16_t*)&channelConfigHdr[1];
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

		// Move sample chunk start and set flag in contentID field
		sampleChunkHdr = (IDNHDR_SAMPLE_CHUNK*)&descriptors[10];
		contentID |= IDNFLG_CONTENTID_CONFIG_LSTFRG;

		ctx->cfgTimestamp = now;
	}
	channelMsgHdr->contentID = htons(contentID);

	// ---------------------------------------------------------------------------------------------

	// Chunk data pointer setup
	ctx->sampleChunkHdr = sampleChunkHdr;
	ctx->payload = (uint8_t*)&sampleChunkHdr[1];
	ctx->sampleCnt = 0;

	return 0;
}

int idnPutSampleHighResXYRGB(IDNCONTEXT* context, int16_t x, int16_t y, uint16_t r, uint16_t g, uint16_t b)
{
	IDNCONTEXT* ctx = context;

	// Sanity check
	if (ctx->payload == (uint8_t*)0)
		return -1;

	// Make sure there is enough buffer. Note: payload and bufferPtr are (uint8_t *) - and 
	// pointer substraction is defined as the difference of (array) elements.
	unsigned lenUsed = (unsigned)(ctx->payload - ctx->bufferPtr);
	unsigned lenNeeded = lenUsed + (XYRGB_HIGHRES_SAMPLE_SIZE); // Todo remove?

	// Get pointer to next sample
	uint8_t* p = ctx->payload;

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
	ctx->payload += XYRGB_HIGHRES_SAMPLE_SIZE;
	ctx->sampleCnt++;

	return 0;
}


int idnOpenFrameExtended(IDNCONTEXT* context)
{
	IDNCONTEXT* ctx = context;

	// IDN-Hello packet header. Note: Sequence number populated on push
	IDNHDR_PACKET* packetHdr = (IDNHDR_PACKET*)ctx->bufferPtr;
	packetHdr->command = IDNCMD_RT_CNLMSG;
	packetHdr->flags = ctx->clientGroup;

	// ---------------------------------------------------------------------------------------------

	// IDN-Stream channel message header. Note: Remaining fields populated on push
	IDNHDR_CHANNEL_MESSAGE* channelMsgHdr = (IDNHDR_CHANNEL_MESSAGE*)&packetHdr[1];
	uint16_t contentID = IDNFLG_CONTENTID_CHANNELMSG;
	contentID |= (((ctx->serviceId - 1) & 0x3F) << 8); // channel ID

	// Insert channel config header every 250 ms
	unsigned now = plt_getMonoTimeUS();
	IDNHDR_SAMPLE_CHUNK* sampleChunkHdr = (IDNHDR_SAMPLE_CHUNK*)&channelMsgHdr[1];
	if ((ctx->frameCnt == 0) || ((now - ctx->cfgTimestamp) > 250000))
	{
		// IDN-Stream channel configuration header
		IDNHDR_CHANNEL_CONFIG* channelConfigHdr = (IDNHDR_CHANNEL_CONFIG*)sampleChunkHdr;
		channelConfigHdr->wordCount = 10;
		channelConfigHdr->flags = IDNFLG_CHNCFG_ROUTING;
		channelConfigHdr->serviceID = ctx->serviceId;
		channelConfigHdr->serviceMode = IDNVAL_SMOD_LPGRF_DISCRETE;

		uint16_t* descriptors = (uint16_t*)&channelConfigHdr[1];
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
		descriptors[12] = htons(0x51BD);     // User 1 (Deep blue)
		descriptors[13] = htons(0x4010);     // 16 bit precision
		descriptors[14] = htons(0x5241);     // User 2 (Here configured as yellow)
		descriptors[15] = htons(0x4010);     // 16 bit precision
		descriptors[16] = htons(0x51E8);     // User 3 (Here configured as cyan)
		descriptors[17] = htons(0x4010);     // 16 bit precision
		descriptors[18] = htons(0x4201);     // User 4 (Here configured as X-prime) TODO cannot use X-prime because ISP-DB25 expects +-10V, HeliosPRO can only do 5V on U4.
		descriptors[19] = htons(0x4010);     // 16 bit precision

		// Move sample chunk start and set flag in contentID field
		sampleChunkHdr = (IDNHDR_SAMPLE_CHUNK*)&descriptors[20];
		contentID |= IDNFLG_CONTENTID_CONFIG_LSTFRG;

		ctx->cfgTimestamp = now;
	}
	channelMsgHdr->contentID = htons(contentID);

	// ---------------------------------------------------------------------------------------------

	// Chunk data pointer setup
	ctx->sampleChunkHdr = sampleChunkHdr;
	ctx->payload = (uint8_t*)&sampleChunkHdr[1];
	ctx->sampleCnt = 0;

	return 0;
}

int idnPutSampleExtended(IDNCONTEXT* context, int16_t x, int16_t y, uint16_t r, uint16_t g, uint16_t b, uint16_t i, uint16_t u1, uint16_t u2, uint16_t u3, uint16_t u4)
{
	IDNCONTEXT* ctx = context;

	// Sanity check
	if (ctx->payload == (uint8_t*)0)
		return -1;

	// Make sure there is enough buffer. Note: payload and bufferPtr are (uint8_t *) - and 
	// pointer substraction is defined as the difference of (array) elements.
	unsigned lenUsed = (unsigned)(ctx->payload - ctx->bufferPtr);
	unsigned lenNeeded = lenUsed + (EXTENDED_SAMPLE_SIZE); // Todo remove?

	// Get pointer to next sample
	uint8_t* p = ctx->payload;

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
	ctx->payload += EXTENDED_SAMPLE_SIZE;
	ctx->sampleCnt++;

	return 0;
}


int idnPushFrame(IDNCONTEXT* context)
{
	IDNCONTEXT* ctx = context;

	// Sanity check
	if (ctx->payload == (uint8_t*)0) return -1;
	if (ctx->sampleCnt < 2) { logError("[IDN] Invalid sample count %u", ctx->sampleCnt); return -1; }

	// ---------------------------------------------------------------------------------------------

	// Sample chunk header: Calculate frame duration based on scan speed.
	// In case jitter-free option is set: Scan frames 2.. only once.

	// IDN channel message header: Set timestamp; Update internal timestamps.
	unsigned now = plt_getMonoTimeUS();
	//if (ctx->frameCnt == 0 || (now-1000 < ctx->frameTimestamp))
	ctx->frameTimestamp = now;
	//else
	//	ctx->scanSpeed = (((uint64_t)(ctx->sampleCnt - 1)) * 1000000ull) / (now - ctx->frameTimestamp);

	uint32_t frameDuration = (((uint64_t)(ctx->sampleCnt - 1)) * 1000000ull) / (uint64_t)ctx->scanSpeed;
	uint8_t frameFlags = 0;
	if (ctx->jitterFreeFlag && ctx->frameCnt != 0)
		frameFlags |= IDNFLG_GRAPHIC_FRAME_ONCE;
	ctx->sampleChunkHdr->flagsDuration = htonl((frameFlags << 24) | frameDuration);

	// Should wait between frames to match frame rate, but instead we trust the host application to do this. 
	/*if (ctx->frameCnt != 0)
	{
		unsigned usWait = ctx->usFrameTime - (plt_getMonoTimeUS() - ctx->frameTimestamp);
		if ((int)usWait > 0) plt_usleep(usWait);
	}*/


	// ---------------------------------------------------------------------------------------------

	// Calculate header pointers, get message contentID (because of byte order)
	IDNHDR_PACKET* packetHdr = (IDNHDR_PACKET*)ctx->bufferPtr;
	IDNHDR_CHANNEL_MESSAGE* channelMsgHdr = (IDNHDR_CHANNEL_MESSAGE*)&packetHdr[1];
	uint16_t contentID = ntohs(channelMsgHdr->contentID);
	contentID |= (((ctx->serviceId - 1) & 0x3F) << 8); // channel ID


	channelMsgHdr->timestamp = htonl(ctx->frameTimestamp);
	ctx->frameCnt++;
	ctx->frameTimestamp += frameDuration;
	//#ifdef DEBUG
		//printf("frameduration: %d\n", frameDuration);
	//#endif

	// Message header: Calculate message length. Must not exceed 0xFF00 octets !!
	unsigned msgLength = ctx->payload - (uint8_t*)channelMsgHdr;
	if (msgLength > MAX_IDN_MESSAGE_LEN)
	{
		// Fragmented frame (split across multiple messages), set message length and chunk type
		channelMsgHdr->totalSize = htons(MAX_IDN_MESSAGE_LEN);
		channelMsgHdr->contentID = htons(contentID | IDNVAL_CNKTYPE_LPGRF_FRAME_FIRST);
		uint8_t* splitPtr = (uint8_t*)channelMsgHdr + MAX_IDN_MESSAGE_LEN;

		// Set IDN-Hello sequence number (used on UDP for lost packet tracking)
		packetHdr->sequence = htons(ctx->sequence++);

		// Send the packet
		if (idnSend(ctx, packetHdr, splitPtr - (uint8_t*)packetHdr)) 
			return -1;

		// Delete config flag (in case set - not config headers in fragments), set sequel fragment chunk type
		contentID &= ~IDNFLG_CONTENTID_CONFIG_LSTFRG;
		contentID |= IDNVAL_CNKTYPE_LPGRF_FRAME_SEQUEL;

		// Send remaining fragments
		while (1)
		{
			// Allocate message header (overwrite previous packet data), fragment number shared with timestamp
			channelMsgHdr = (IDNHDR_CHANNEL_MESSAGE*)(splitPtr - sizeof(IDNHDR_CHANNEL_MESSAGE));
			channelMsgHdr->timestamp = htonl(++now);

			// Allocate and populate packet header
			packetHdr = (IDNHDR_PACKET*)((uint8_t*)channelMsgHdr - sizeof(IDNHDR_PACKET));
			packetHdr->command = IDNCMD_RT_CNLMSG;
			packetHdr->flags = ctx->clientGroup;
			packetHdr->sequence = htons(ctx->sequence++);

			// Calculate remaining message length
			msgLength = ctx->payload - (uint8_t*)channelMsgHdr;
			if (msgLength > MAX_IDN_MESSAGE_LEN)
			{
				// Middle sequel fragment
				channelMsgHdr->totalSize = htons(MAX_IDN_MESSAGE_LEN);
				channelMsgHdr->contentID = htons(contentID);
				splitPtr = (uint8_t*)channelMsgHdr + MAX_IDN_MESSAGE_LEN;

				// Send the packet
				if (idnSend(ctx, packetHdr, splitPtr - (uint8_t*)packetHdr)) 
					return -1;
			}
			else
			{
				// Last sequel fragment, set last fragment flag
				channelMsgHdr->totalSize = htons((unsigned short)msgLength);
				channelMsgHdr->contentID = htons(contentID | IDNFLG_CONTENTID_CONFIG_LSTFRG);

				// Send the packet
				if (idnSend(ctx, packetHdr, ctx->payload - (uint8_t*)packetHdr)) 
					return -1;

				// Done sending the packet
				break;
			}
		}
	}
	else
	{
		// Regular frame (single message), set message length and chunk type
		channelMsgHdr->totalSize = htons((unsigned short)msgLength);
		channelMsgHdr->contentID = htons(contentID | IDNVAL_CNKTYPE_LPGRF_FRAME);

		// Set IDN-Hello sequence number (used on UDP for lost packet tracking)
		packetHdr->sequence = htons(ctx->sequence++);

		// Send the packet
		if (idnSend(ctx, packetHdr, ctx->payload - (uint8_t*)packetHdr))
			return -1;
	}

	// Invalidate payload - cause error in case of invalid call order
	ctx->payload = (uint8_t*)0;

	return 0;
}


int idnSendVoid(IDNCONTEXT* context)
{
	IDNCONTEXT* ctx = context;

	// IDN-Hello packet header
	IDNHDR_PACKET* packetHdr = (IDNHDR_PACKET*)ctx->bufferPtr;
	packetHdr->command = IDNCMD_RT_CNLMSG;
	packetHdr->flags = ctx->clientGroup;
	packetHdr->sequence = htons(ctx->sequence++);

	// IDN-Stream channel message header
	IDNHDR_CHANNEL_MESSAGE* channelMsgHdr = (IDNHDR_CHANNEL_MESSAGE*)&packetHdr[1];
	uint16_t contentID = IDNFLG_CONTENTID_CHANNELMSG | IDNVAL_CNKTYPE_VOID;
	contentID |= (((ctx->serviceId - 1) & 0x3F) << 8); // channel ID
	channelMsgHdr->contentID = htons(contentID);

	// Pointer to the end of the buffer for message length and packet length calculation
	ctx->payload = (uint8_t*)&channelMsgHdr[1];

	// Populate message header fields
	channelMsgHdr->totalSize = htons((unsigned short)(ctx->payload - (uint8_t*)channelMsgHdr));
	channelMsgHdr->timestamp = htonl(plt_getMonoTimeUS());
	ctx->frameCnt = 0;

	// Send the packet
	if (idnSend(context, packetHdr, ctx->payload - (uint8_t*)packetHdr))
		return -1;

	return 0;
}


int idnSendClose(IDNCONTEXT* context)
{
	IDNCONTEXT* ctx = context;


	// Close the channel: IDN-Hello packet header
	IDNHDR_PACKET* packetHdr = (IDNHDR_PACKET*)ctx->bufferPtr;
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

	// Pointer to the end of the buffer for message length and packet length calculation
	ctx->payload = (uint8_t*)&channelConfigHdr[1];

	// Populate message header fields
	channelMsgHdr->totalSize = htons((unsigned short)(ctx->payload - (uint8_t*)channelMsgHdr));
	channelMsgHdr->timestamp = htonl(plt_getMonoTimeUS());

	// Send the packet
	if (idnSend(context, packetHdr, ctx->payload - (uint8_t*)packetHdr))
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

