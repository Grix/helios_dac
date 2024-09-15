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

	if (sendto(ctx->fdSocket, (const char*)packetHdr, packetLen, 0, (struct sockaddr*) & ctx->serverSockAddr, sizeof(ctx->serverSockAddr)) < 0)
	{
		logError("sendto() failed (error: %d)", plt_sockGetLastError());
		return -1;
	}

	return 0;
}


// -------------------------------------------------------------------------------------------------
//  IDN
// -------------------------------------------------------------------------------------------------

int idnOpenFrameXYRGB(void* context)
{
	IDNCONTEXT* ctx = (IDNCONTEXT*)context;

	// IDN-Hello packet header. Note: Sequence number populated on push
	IDNHDR_PACKET* packetHdr = (IDNHDR_PACKET*)ctx->bufferPtr;
	packetHdr->command = IDNCMD_RT_CNLMSG;
	packetHdr->flags = ctx->clientGroup;

	// ---------------------------------------------------------------------------------------------

	// IDN-Stream channel message header. Note: Remaining fields populated on push
	IDNHDR_CHANNEL_MESSAGE* channelMsgHdr = (IDNHDR_CHANNEL_MESSAGE*)& packetHdr[1];
	uint16_t contentID = IDNFLG_CONTENTID_CHANNELMSG;
	contentID |= (((ctx->serviceId - 1) & 0x3F) << 8); // channel ID

	// Insert channel config header every 200 ms
	unsigned now = plt_getMonoTimeUS();
	IDNHDR_SAMPLE_CHUNK* sampleChunkHdr = (IDNHDR_SAMPLE_CHUNK*)& channelMsgHdr[1];
	//if ((ctx->frameCnt == 0) || ((now - ctx->cfgTimestamp) > 200000)) always add header for now, causes problems in IDN toolbox otherwise
	{
		// IDN-Stream channel configuration header
		IDNHDR_CHANNEL_CONFIG* channelConfigHdr = (IDNHDR_CHANNEL_CONFIG*)sampleChunkHdr;
		channelConfigHdr->wordCount = 4;
		channelConfigHdr->flags = IDNFLG_CHNCFG_ROUTING;
		channelConfigHdr->serviceID = ctx->serviceId;
		channelConfigHdr->serviceMode = IDNVAL_SMOD_LPGRF_DISCRETE;

		// Standard IDTF-to-IDN descriptors
		uint16_t* descriptors = (uint16_t*)& channelConfigHdr[1];
		descriptors[0] = htons(0x4200);     // X
		descriptors[1] = htons(0x4010);     // 16 bit precision
		descriptors[2] = htons(0x4210);     // Y
		descriptors[3] = htons(0x4010);     // 16 bit precision
		descriptors[4] = htons(0x527E);     // Red, 638 nm
		descriptors[5] = htons(0x5214);     // Green, 532 nm
		descriptors[6] = htons(0x51CC);     // Blue, 460 nm
		descriptors[7] = htons(0x0000);     // Void for alignment

		// Move sample chunk start and set flag in contentID field
		sampleChunkHdr = (IDNHDR_SAMPLE_CHUNK*)& descriptors[8];
		contentID |= IDNFLG_CONTENTID_CONFIG_LSTFRG;

		ctx->cfgTimestamp = now;
	}
	channelMsgHdr->contentID = htons(contentID);

	// ---------------------------------------------------------------------------------------------

	// Chunk data pointer setup
	ctx->sampleChunkHdr = sampleChunkHdr;
	ctx->payload = (uint8_t*)& sampleChunkHdr[1];
	ctx->sampleCnt = 0;

	return 0;
}


int idnPutSampleXYRGB(void* context, int16_t x, int16_t y, uint8_t r, uint8_t g, uint8_t b)
{
	IDNCONTEXT* ctx = (IDNCONTEXT*)context;

	// Sanity check
	if (ctx->payload == (uint8_t*)0) return -1;

	// Make sure there is enough buffer. Note: payload and bufferPtr are (uint8_t *) - and 
	// pointer substraction is defined as the difference of (array) elements.
	unsigned lenUsed = (unsigned)(ctx->payload - ctx->bufferPtr);
	unsigned lenNeeded = lenUsed + ((1 + ctx->colorShift) * XYRGB_SAMPLE_SIZE);


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

	// Check for color shift init
	if (ctx->sampleCnt == 0)
	{
		// Color shift samples
		for (unsigned i = 0; i < ctx->colorShift; i++)
		{
			p[0] = 0;
			p[1] = 0;
			p[2] = 0;
			p += XYRGB_SAMPLE_SIZE;
		}
	}
	else
	{
		// Other samples - just move the pointer
		p += XYRGB_SAMPLE_SIZE * ctx->colorShift;
	}

	// Store color sample bytes
	*p++ = r;
	*p++ = g;
	*p++ = b;

	// Update pointer to next sample, update sample count
	ctx->payload += XYRGB_SAMPLE_SIZE;
	ctx->sampleCnt++;

	return 0;
}


int idnPushFrameXYRGB(void* context)
{
	IDNCONTEXT* ctx = (IDNCONTEXT*)context;

	// Sanity check
	if (ctx->payload == (uint8_t*)0) return -1;
	if (ctx->sampleCnt < 2) { logError("[IDN] Invalid sample count %u", ctx->sampleCnt); return -1; }

	// ---------------------------------------------------------------------------------------------

	// Duplicate last position for color shift samples
	for (unsigned i = 0; i < ctx->colorShift; i++)
	{
		// Get pointer to last position and next sample (already has color due to shift)
		uint16_t* src = (uint16_t*)(ctx->payload - XYRGB_SAMPLE_SIZE);
		uint16_t* dst = (uint16_t*)ctx->payload;

		// Duplicate position
		*dst++ = *src++;
		*dst++ = *src++;

		// Update pointer to next sample, update sample count
		ctx->payload += XYRGB_SAMPLE_SIZE;
		ctx->sampleCnt++;
	}

	// Sample chunk header: Calculate frame duration based on scan speed.
	// In case jitter-free option is set: Scan frames 2.. ony once.

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

	// Wait between frames to match frame rate
	/*if (ctx->frameCnt != 0)
	{
		unsigned usWait = ctx->usFrameTime - (plt_getMonoTimeUS() - ctx->frameTimestamp);
		if ((int)usWait > 0) plt_usleep(usWait);
	}*/
	

	// ---------------------------------------------------------------------------------------------

	// Calculate header pointers, get message contentID (because of byte order)
	IDNHDR_PACKET* packetHdr = (IDNHDR_PACKET*)ctx->bufferPtr;
	IDNHDR_CHANNEL_MESSAGE* channelMsgHdr = (IDNHDR_CHANNEL_MESSAGE*)& packetHdr[1];
	uint16_t contentID = ntohs(channelMsgHdr->contentID);
	contentID |= (((ctx->serviceId - 1) & 0x3F) << 8); // channel ID

	// IDN channel message header: Set timestamp; Update internal timestamps.
	//unsigned now = plt_getMonoTimeUS();
	//if (contentID & IDNFLG_CONTENTID_CONFIG_LSTFRG) ctx->cfgTimestamp = now;
	
	channelMsgHdr->timestamp = htonl(ctx->frameTimestamp);
	ctx->frameCnt++;
	ctx->frameTimestamp += frameDuration;
//#ifdef DEBUG
	//printf("frameduration: %d\n", frameDuration);
//#endif

	// Message header: Calculate message length. Must not exceed 0xFF00 octets !! In LSG, never does
	unsigned msgLength = ctx->payload - (uint8_t*)channelMsgHdr;
	/*if (msgLength > MAX_IDN_MESSAGE_LEN)
	{
		// Fragmented frame (split across multiple messages), set message length and chunk type
		channelMsgHdr->totalSize = htons(MAX_IDN_MESSAGE_LEN);
		channelMsgHdr->contentID = htons(contentID | IDNVAL_CNKTYPE_LPGRF_FRAME_FIRST);
		uint8_t* splitPtr = (uint8_t*)channelMsgHdr + MAX_IDN_MESSAGE_LEN;

		// Set IDN-Hello sequence number (used on UDP for lost packet tracking)
		packetHdr->sequence = htons(ctx->sequence++);

		// Send the packet
		if (idnSend(ctx, packetHdr, splitPtr - (uint8_t*)packetHdr)) return -1;

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
				if (idnSend(ctx, packetHdr, splitPtr - (uint8_t*)packetHdr)) return -1;
			}
			else
			{
				// Last sequel fragment, set last fragment flag
				channelMsgHdr->totalSize = htons((unsigned short)msgLength);
				channelMsgHdr->contentID = htons(contentID | IDNFLG_CONTENTID_CONFIG_LSTFRG);

				// Send the packet
				if (idnSend(ctx, packetHdr, ctx->payload - (uint8_t*)packetHdr)) return -1;

				// Done sending the packet
				break;
			}
		}
	}
	else*/
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


int idnSendVoid(void* context)
{
	IDNCONTEXT* ctx = (IDNCONTEXT*)context;

	// IDN-Hello packet header
	IDNHDR_PACKET* packetHdr = (IDNHDR_PACKET*)ctx->bufferPtr;
	packetHdr->command = IDNCMD_RT_CNLMSG;
	packetHdr->flags = ctx->clientGroup;
	packetHdr->sequence = htons(ctx->sequence++);

	// IDN-Stream channel message header
	IDNHDR_CHANNEL_MESSAGE* channelMsgHdr = (IDNHDR_CHANNEL_MESSAGE*)& packetHdr[1];
	uint16_t contentID = IDNFLG_CONTENTID_CHANNELMSG | IDNVAL_CNKTYPE_VOID;
	contentID |= (((ctx->serviceId - 1) & 0x3F) << 8); // channel ID
	channelMsgHdr->contentID = htons(contentID);

	// Pointer to the end of the buffer for message length and packet length calculation
	ctx->payload = (uint8_t*)& channelMsgHdr[1];

	// Populate message header fields
	channelMsgHdr->totalSize = htons((unsigned short)(ctx->payload - (uint8_t*)channelMsgHdr));
	channelMsgHdr->timestamp = htonl(plt_getMonoTimeUS());
	ctx->frameCnt = 0;

	// Send the packet
	if (idnSend(context, packetHdr, ctx->payload - (uint8_t*)packetHdr)) return -1;

	return 0;
}


int idnSendClose(void* context)
{
	IDNCONTEXT* ctx = (IDNCONTEXT*)context;


	// Close the channel: IDN-Hello packet header
	IDNHDR_PACKET* packetHdr = (IDNHDR_PACKET*)ctx->bufferPtr;
	packetHdr->command = IDNCMD_RT_CNLMSG;
	packetHdr->flags = ctx->clientGroup;
	packetHdr->sequence = htons(ctx->sequence++);

	// IDN-Stream channel message header
	IDNHDR_CHANNEL_MESSAGE* channelMsgHdr = (IDNHDR_CHANNEL_MESSAGE*)& packetHdr[1];
	uint16_t contentID = IDNFLG_CONTENTID_CHANNELMSG | IDNFLG_CONTENTID_CONFIG_LSTFRG | IDNVAL_CNKTYPE_VOID;
	contentID |= (((ctx->serviceId - 1) & 0x3F) << 8); // channel ID
	channelMsgHdr->contentID = htons(contentID);

	// IDN-Stream channel config header (close channel)
	IDNHDR_CHANNEL_CONFIG* channelConfigHdr = (IDNHDR_CHANNEL_CONFIG*)& channelMsgHdr[1];
	channelConfigHdr->wordCount = 0;
	channelConfigHdr->flags = IDNFLG_CHNCFG_CLOSE;
	channelConfigHdr->serviceID = ctx->serviceId;
	channelConfigHdr->serviceMode = 0;

	// Pointer to the end of the buffer for message length and packet length calculation
	ctx->payload = (uint8_t*)& channelConfigHdr[1];

	// Populate message header fields
	channelMsgHdr->totalSize = htons((unsigned short)(ctx->payload - (uint8_t*)channelMsgHdr));
	channelMsgHdr->timestamp = htonl(plt_getMonoTimeUS());

	// Send the packet
	if (idnSend(context, packetHdr, ctx->payload - (uint8_t*)packetHdr)) return -1;

	// ---------------------------------------------------------------------------------------------

	// Close the connection/session: IDN-Hello packet header
	packetHdr->command = IDNCMD_RT_CNLMSG_CLOSE;
	packetHdr->flags = ctx->clientGroup;
	packetHdr->sequence = htons(ctx->sequence++);

	// Send the packet (gracefully close session)
	if (idnSend(context, packetHdr, sizeof(IDNHDR_PACKET))) return -1;

	return 0;
}


std::vector<int>* idnHelloScan(const char* ifName, uint32_t adapterIpAddr)
{
	// Socket file descriptor
	int fdSocket = -1;

	fprintf(stderr, "IDN Hello Scan starting, %d , %s\n", adapterIpAddr, ifName);

	std::vector<int>* foundIps = new std::vector<int>();

	if (plt_validateMonoTime() != 0)
		return foundIps;

	do
	{
		// Print interface info
		char ifAddrString[20];
		if (inet_ntop(AF_INET, &adapterIpAddr, ifAddrString, sizeof(ifAddrString)) == (char*)0)
		{
			logError("inet_ntop() failed (error: %d)", plt_sockGetLastError());
			break;
		}
		logInfo("Scanning interface %s (IP4: %s)", ifName ? ifName : "<?>", ifAddrString);
		fprintf(stderr, "Scanning interface %s (IP4: %s)", ifName ? ifName : "<?>", ifAddrString);

		// Create socket
		fdSocket = plt_sockOpen(AF_INET, SOCK_DGRAM, 0);
		if (fdSocket < 0)
		{
			logError("socket() failed (error: %d)", plt_sockGetLastError());
			fprintf(stderr, "socket() failed (error: %d)", plt_sockGetLastError());
			break;
		}

		// Allow broadcast on socket
		if (plt_sockSetBroadcast(fdSocket) < 0)
		{
			logError("setsockopt(broadcast) failed (error: %d)", plt_sockGetLastError());
			fprintf(stderr, "setsockopt(broadcast) failed (error: %d)", plt_sockGetLastError());
			break;
		}
        
		// Bind to local interface (any! port)
		// Note: This bind is needed to send the broadcast on the specific (virtual) interface,
		struct sockaddr_in bindSockAddr = { 0 };
		bindSockAddr.sin_family = AF_INET;
		bindSockAddr.sin_port = 0;
		bindSockAddr.sin_addr.s_addr = adapterIpAddr;

		if (bind(fdSocket, (struct sockaddr*) & bindSockAddr, sizeof(bindSockAddr)) < 0)
		{
			logError("bind() failed (error: %d)", plt_sockGetLastError());
			fprintf(stderr, "bind() failed (error: %d)", plt_sockGetLastError());
			break;
		}

		// ----------------------------------------------------------------------------------------
		// Send request, use network broadcast address

		struct sockaddr_in sendSockAddr;
		sendSockAddr.sin_family = AF_INET;
		sendSockAddr.sin_port = htons(IDNVAL_HELLO_UDP_PORT);
		sendSockAddr.sin_addr.s_addr = adapterIpAddr | (255 << (8 * 3));//INADDR_BROADCAST;

		IDNHDR_PACKET sendPacketHdr;
		sendPacketHdr.command = IDNCMD_SCAN_REQUEST;
		sendPacketHdr.flags = 0;
		sendPacketHdr.sequence = htons(rand() & 0xFFFF);

		if (sendto(fdSocket, (char*)& sendPacketHdr, sizeof(sendPacketHdr), 0, (struct sockaddr*) & sendSockAddr, sizeof(sendSockAddr)) < 0)
		{
			logError("sendto() failed (error: %d)", plt_sockGetLastError());
			fprintf(stderr, "sendto() failed (error: %d)", plt_sockGetLastError());
			break;
		}


		// ----------------------------------------------------------------------------------------
		// Receive response(s)

		fd_set rfdsPrm;
		FD_ZERO(&rfdsPrm);
		FD_SET(fdSocket, &rfdsPrm);

		unsigned msTimeout = 500;

		// Remember start time
		uint32_t usStart = plt_getMonoTimeUS();

		while (1)
		{
			// Calculate time left
			uint32_t usNow = plt_getMonoTimeUS();
			uint32_t usElapsed = usNow - usStart;
			uint32_t usLeft = (msTimeout * 1000) - usElapsed;
			if ((int32_t)usLeft <= 0) break;

			// Populate select timeout
			struct timeval tv;
			tv.tv_sec = usLeft / 1000000;
			tv.tv_usec = usLeft % 1000000;

			// Wait for incoming datagrams
			fd_set rfdsResult = rfdsPrm;
			int numReady = select(fdSocket + 1, &rfdsResult, 0, 0, &tv);
			if (numReady < 0)
			{
				logError("select() failed (error: %d)", plt_sockGetLastError());
				fprintf(stderr, "select() failed (error: %d)", plt_sockGetLastError());
				break;
			}
			else if (numReady == 0)
			{
				continue;
			}

			// Receive scan response
			struct sockaddr_in recvSockAddr;
			struct sockaddr* recvAddrPre = (struct sockaddr*) & recvSockAddr;
			socklen_t recvAddrSize = sizeof(recvSockAddr);


			int nBytes = recvfrom(fdSocket, (char*)gbl_packetBuffer, sizeof(gbl_packetBuffer), 0, recvAddrPre, &recvAddrSize);
			if (nBytes < 0)
			{
				logError("recvfrom() failed (error: %d)", plt_sockGetLastError());
				break;
			}

			// Convert IP address to string
			char recvAddrString[20];
			if (inet_ntop(AF_INET, &recvSockAddr.sin_addr, recvAddrString, sizeof(recvAddrString)) == (char*)0)
			{
				logError("inet_ntop() failed (error: %d)", plt_sockGetLastError());
				break;
			}

			int ipAddr;
			if (!inet_pton(AF_INET, recvAddrString, &ipAddr))
				break;

			// Check sender port
			if (ntohs(recvSockAddr.sin_port) != IDNVAL_HELLO_UDP_PORT)
			{
				logError("%s: Invalid sender port %u", recvAddrString, ntohs(recvSockAddr.sin_port));
				break;
			}

			// Check packet size
			if (nBytes != (sizeof(IDNHDR_PACKET) + sizeof(IDNHDR_SCAN_RESPONSE)))
			{
				logError("%s: Invalid packet size %u\n", recvAddrString, nBytes);
				break;
			}

			// Check IDN-Hello packet header
			IDNHDR_PACKET* recvPacketHdr = (IDNHDR_PACKET*)gbl_packetBuffer;
			if (recvPacketHdr->command != IDNCMD_SCAN_RESPONSE)
			{
				logError("%s: Invalid command 0x%02X\n", recvAddrString, recvPacketHdr->command);
				break;
			}
			if (recvPacketHdr->sequence != sendPacketHdr.sequence)
			{
				logError("%s: Invalid sequence\n", recvAddrString);
				break;
			}

			// Check scan response header
			IDNHDR_SCAN_RESPONSE* scanResponseHdr = (IDNHDR_SCAN_RESPONSE*)& recvPacketHdr[1];
			if (scanResponseHdr->structSize != sizeof(IDNHDR_SCAN_RESPONSE))
			{
				logError("%s: Invalid scan response header size %u\n", recvAddrString, scanResponseHdr->structSize);
				break;
			}

			// Allocate log buffer
			/*char logString[200], * logPtr = logString, * logLimit = &logString[sizeof(logString)];

			// Print unitID as a string
			unsigned unitIDLen = scanResponseHdr->unitID[0];
			unsigned char* src = (unsigned char*)& scanResponseHdr->unitID[1];
			for (unsigned i = 0; i < unitIDLen; i++)
			{
				logPtr = bufPrintf(logPtr, logLimit, "%02X", *src++);
				if (i == 0) logPtr = bufPrintf(logPtr, logLimit, "-");
			}

			// Append host name (in case available)
			if (scanResponseHdr->hostName[0])
			{
				logPtr = bufPrintf(logPtr, logLimit, "(%s)", scanResponseHdr->hostName);
			}*/

			// Print server information
			//logInfo("%s at %s", logString, recvAddrString);

			foundIps->push_back(ipAddr);
		}
	} while (0);

	// Close socket
	if (fdSocket >= 0)
	{
		if (plt_sockClose(fdSocket)) logError("close() failed (error: %d)", plt_sockGetLastError());
	}

	return foundIps;
}
