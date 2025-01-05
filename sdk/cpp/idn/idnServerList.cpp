// -------------------------------------------------------------------------------------------------
//  File idnServerList.c
//
//  Copyright (c) 2016, 2017 DexLogic, Dirk Apitz
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
// -------------------------------------------------------------------------------------------------
//  Change History:
//
//  06/2016 Dirk Apitz, created
//  01/2017 Dirk Apitz, ServiceMap
//  06/2017 Dirk Apitz, Windows port, GitHub release
// -------------------------------------------------------------------------------------------------

// Standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>


// Platform includes
#if defined(_WIN32) || defined(WIN32)

    #include "plt-windows.h"

#else

    #include <unistd.h>
    #include <ifaddrs.h>

    #include "plt-posix.h"

#endif

#include "idn-hello.h"
#include "idnServerList.h"


// -------------------------------------------------------------------------------------------------
//  Defines
// -------------------------------------------------------------------------------------------------

#define APPEND_NODE(first, last, node)                                                      \
    {                                                                                       \
        if(!first) { node->prev = NULL; first = node; }                                     \
        else { node->prev = last; last->next = node; }                                      \
                                                                                            \
        node->next = NULL;                                                                  \
        last = node;                                                                        \
    }

#define LINKOUT_NODE(first, last, node)                                                     \
    {                                                                                       \
        if(node->prev) node->prev->next = node->next;                                       \
        else first = node->next;                                                            \
                                                                                            \
        if(node->next) node->next->prev = node->prev;                                       \
        else last = node->prev;                                                             \
                                                                                            \
        node->prev = NULL;                                                                  \
        node->next = NULL;                                                                  \
    }

#define COPY_NAME_NULLTERM(dstField, srcField)                                              \
    {                                                                                       \
        unsigned cpyCount = sizeof(dstField) - 1;                                           \
        if(sizeof(srcField) < cpyCount) cpyCount = sizeof(srcField);                        \
                                                                                            \
        unsigned i = 0;                                                                     \
        char *dst = dstField;                                                               \
        uint8_t *src = srcField;                                                            \
        for(; (i < cpyCount) && (*src != 0); i++) *dst++ = *src++;                          \
        for(; i < sizeof(dstField); i++) *dst = 0;                                          \
    }


// -------------------------------------------------------------------------------------------------
//  Typedefs
// -------------------------------------------------------------------------------------------------

typedef struct _INTERFACE_NODE
{
    struct _INTERFACE_NODE* prev, * next;        // Doubly linked list of interface records

    char ifName[40];

    int fdSocket;                               // Broadcast socket file descriptor
    uint16_t scanSequenceNum;                   // Broadcast scan sequence number
    uint32_t ipAddr;
    uint32_t ipMask;

} INTERFACE_NODE;


typedef struct _RESPONSE_INFO
{
    struct _RESPONSE_INFO* prev, * next;         // Doubly linked list of response info records

    struct in_addr addr;                        // Remote address the response was received from
    IDNSL_SERVER_INFO* serverInfo;              // Associated server info record

    uint16_t ambiguousErrorFlag;                // Set in case multiple servers responded on the address
    uint16_t infoRequestFlag;                   // Set for default address in case info was requested
    uint16_t checkSequenceNum;                  // Reachability check sequence number
    uint16_t serviceMapSequenceNum;             // Service map info request sequence number

} RESPONSE_INFO;


typedef struct _REQUEST_JOB
{
    struct _REQUEST_JOB* prev, * next;           // Doubly linked list of request jobs

    struct in_addr addr;                        // Remote address the request shall be sent to
    uint16_t packetLength;                      // Length of the data

    // Followed by packet data bytes

} REQUEST_JOB;


typedef struct
{
    REQUEST_JOB* firstRequest;                  // Head of request job list
    REQUEST_JOB* lastRequest;                   // Tail of request job list

    int fdSocket;                               // Unicast socket file descriptor

} REQUEST_QUEUE;


typedef struct
{
    uint8_t clientGroup;                        // The client group to run on

    IDNSL_SERVER_INFO* firstServerInfo;         // The resulting server info list

    INTERFACE_NODE* firstIfNode;                // Head of interface record list
    INTERFACE_NODE* lastIfNode;                 // Tail of interface record list

    RESPONSE_INFO* firstResponseInfo;           // Head of response info record list
    RESPONSE_INFO* lastResponseInfo;            // Tail of response info record list

    REQUEST_QUEUE checkRequestQueue;            // Check request jobs
    REQUEST_QUEUE infoRequestQueue;             // Info request jobs

    uint16_t sequenceNum;                       // Next sequence number to be used
    uint8_t packetBuffer[0x10000];              // Receive packet buffer

} SCAN_CONTEXT;


// -------------------------------------------------------------------------------------------------
//  Tools
// -------------------------------------------------------------------------------------------------

static void logError(const char* fmt, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, fmt);

    //    printf("\x1B[1;31m");
    vfprintf(stderr, fmt, arg_ptr);
    //    printf("\x1B[0m");

    fprintf(stderr, "\n");
    fflush(stderr);
}


static void logInfo(const char* fmt, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, fmt);

    vfprintf(stdout, fmt, arg_ptr);

    fprintf(stdout, "\n");
    fflush(stdout);
}


// -------------------------------------------------------------------------------------------------
//  Interface list management
// -------------------------------------------------------------------------------------------------

static void createInterfaceNode(void* callbackArg, const char* ifName, uint32_t ifIP4Addr, uint32_t ifIP4Mask)
{
    SCAN_CONTEXT* scanCtx = (SCAN_CONTEXT*)callbackArg;

    // Allocate node memory
    INTERFACE_NODE* ifNode = (INTERFACE_NODE*)calloc(1, sizeof(INTERFACE_NODE));
    if (ifNode == (INTERFACE_NODE*)0)
    {
        logError("calloc(INTERFACE_NODE) failed");
        return;
    }

    do
    {
        // Create socket
        ifNode->fdSocket = plt_sockOpen(AF_INET, SOCK_DGRAM, 0);
        if (ifNode->fdSocket < 0)
        {
            logError("socket() failed (error: %d)", plt_sockGetLastError());
            break;
        }

        ifNode->ipAddr = ifIP4Addr;
        ifNode->ipMask = ifIP4Mask;

        // Remember interface name
        snprintf(ifNode->ifName, sizeof(ifNode->ifName), ifName ? ifName : "<?>");

        // Allow broadcast on socket
        if (plt_sockSetBroadcast(ifNode->fdSocket) < 0)
        {
            logError("setsockopt(broadcast) failed (error: %d) when scanning IDN DACs (not necessarily a problem, but one of the network interfaces is not usable)", plt_sockGetLastError());
            break;
        }

        // Bind to local interface (any! port)
        // Note: This bind is needed to send the broadcast on the specific (virtual) interface,
        struct sockaddr_in bindSockAddr = { 0, 0, 0, 0 };
        bindSockAddr.sin_family = AF_INET;
        bindSockAddr.sin_port = 0;
        bindSockAddr.sin_addr.s_addr = ifIP4Addr;

        if (bind(ifNode->fdSocket, (struct sockaddr*)&bindSockAddr, sizeof(bindSockAddr)) < 0)
        {
            logError("bind() failed (error: %d) when scanning IDN DACs (not necessarily a problem, but one of the network interfaces is not usable)", plt_sockGetLastError());
            break;
        }

        //struct sockaddr_in *ifSockAddr = (struct sockaddr_in *)ifa->ifa_addr;
        //logInfo("Interface %s(%s)", ifa->ifa_name, inet_ntoa(*(in_addr *)&(ifSockAddr->sin_addr.s_addr)));

        // Node successfully created, append to list and return.
        APPEND_NODE(scanCtx->firstIfNode, scanCtx->lastIfNode, ifNode);
        return;
    } while (0);

    // Error: Close socket
    if (ifNode->fdSocket >= 0)
    {
        if (plt_sockClose(ifNode->fdSocket)) 
            logError("close() failed (error: %d)", plt_sockGetLastError());
    }

    // Error: Free node memory
    free(ifNode);
}


static void deleteInterfaceNode(INTERFACE_NODE* ifNode)
{
    if (!ifNode) 
        return;

    // Close socket
    if (ifNode->fdSocket >= 0)
    {
        if (plt_sockClose(ifNode->fdSocket)) 
            logError("close() failed (error: %d)", plt_sockGetLastError());
    }

    // Free node memory
    free(ifNode);
}


// -------------------------------------------------------------------------------------------------
//  Request jobs and response mapping
// -------------------------------------------------------------------------------------------------

static int sendNextRequest(REQUEST_QUEUE* requestQueue)
{
    // Get next request
    REQUEST_JOB* reqJob = requestQueue->firstRequest;
    if (reqJob == (REQUEST_JOB*)0) return 0;

    // Populate remote socket address struct
    struct sockaddr_in remoteSockAddr;
    remoteSockAddr.sin_family = AF_INET;
    remoteSockAddr.sin_port = htons(IDNVAL_HELLO_UDP_PORT);
    remoteSockAddr.sin_addr = reqJob->addr;

    // Send the check request
    if (sendto(requestQueue->fdSocket, (char*)&reqJob[1], reqJob->packetLength, 0, (struct sockaddr*)&remoteSockAddr, sizeof(remoteSockAddr)) < 0)
    {
        logError("sendto() failed (error: %d)", plt_sockGetLastError());
        return -1;
    }

    // Remove from pending request list and free memory
    LINKOUT_NODE(requestQueue->firstRequest, requestQueue->lastRequest, reqJob);
    free(reqJob);

    return 0;
}


static int scheduleQueryRequest(REQUEST_QUEUE* requestQueue, uint8_t cmd, uint8_t clientGroup, uint16_t sequenceNum, struct in_addr* addr)
{
    // Allocate request job memory
    size_t memSize = sizeof(REQUEST_JOB) + sizeof(IDNHDR_PACKET);
    REQUEST_JOB* reqJob = (REQUEST_JOB*)calloc(1, memSize);
    if (reqJob == (REQUEST_JOB*)0)
    {
        logError("calloc(REQUEST_JOB) failed");
        return -1;
    }

    // Populate request job fields
    reqJob->addr = *addr;
    reqJob->packetLength = (uint16_t)(memSize - sizeof(REQUEST_JOB));

    // Populate packet fields
    IDNHDR_PACKET* reqPacketHdr = (IDNHDR_PACKET*)&reqJob[1];
    reqPacketHdr->command = cmd;
    reqPacketHdr->flags = clientGroup & IDNMSK_PKTFLAGS_GROUP;
    reqPacketHdr->sequence = htons(sequenceNum);

    // Schedule for transmission
    APPEND_NODE(requestQueue->firstRequest, requestQueue->lastRequest, reqJob);

    return 0;
}


static RESPONSE_INFO* getResponseInfo(SCAN_CONTEXT* scanCtx, struct in_addr* addr)
{
    // In case the address is already known: Return response info
    RESPONSE_INFO* responseInfo;
    for (responseInfo = scanCtx->firstResponseInfo; responseInfo; responseInfo = responseInfo->next)
    {
        // Check address. On match, return info record
        if (memcmp(&responseInfo->addr, addr, sizeof(responseInfo->addr)) == 0) 
            return responseInfo;
    }

    // New response address - allocate info record
    responseInfo = (RESPONSE_INFO*)calloc(1, sizeof(RESPONSE_INFO));
    if (responseInfo == (RESPONSE_INFO*)0)
    {
        logError("calloc(RESPONSE_INFO) failed");
        return (RESPONSE_INFO*)0;
    }

    // Populate fields - server address
    responseInfo->addr = *addr;

    // Append to response info list and return info record
    APPEND_NODE(scanCtx->firstResponseInfo, scanCtx->lastResponseInfo, responseInfo);
    return responseInfo;
}


// -------------------------------------------------------------------------------------------------
//  Device info handling
// -------------------------------------------------------------------------------------------------

static int scheduleInfoRequests(SCAN_CONTEXT* scanCtx, RESPONSE_INFO* responseInfo)
{
    uint8_t cmd = IDNCMD_SERVICEMAP_REQUEST;
    uint16_t sequenceNum = responseInfo->serviceMapSequenceNum = scanCtx->sequenceNum++;
    int rc = scheduleQueryRequest(&(scanCtx->infoRequestQueue), cmd, scanCtx->clientGroup, sequenceNum, &(responseInfo->addr));
    if (rc < 0) 
        return rc;

    // Additional requests (properies, ...) could go here.

    return 0;
}


static int serviceMapResponse(SCAN_CONTEXT* scanCtx, RESPONSE_INFO* responseInfo, void* payloadPtr, size_t payloadLen)
{
    // Convert IP address to string
    char strRemoteAddr[20];
    if (inet_ntop(AF_INET, &responseInfo->addr, strRemoteAddr, sizeof(strRemoteAddr)) == (char*)0)
    {
        logError("inet_ntop() failed (error: %d)", plt_sockGetLastError());
        return -1;
    }

    // -------------------------------------------------------------------------
    //  Check response
    // -------------------------------------------------------------------------

    if (payloadLen < sizeof(IDNHDR_SERVICEMAP_RESPONSE))
    {
        logError("ServiceMapRsp(%s): Invalid response length %u", strRemoteAddr, payloadLen);
        return 0;
    }

    IDNHDR_SERVICEMAP_RESPONSE* serviceMapHdr = (IDNHDR_SERVICEMAP_RESPONSE*)payloadPtr;
    if (serviceMapHdr->structSize != sizeof(IDNHDR_SERVICEMAP_RESPONSE))
    {
        logError("ServiceMapRsp(%s): Invalid header size %u", strRemoteAddr, serviceMapHdr->structSize);
        return 0;
    }

    // Check entry table
    payloadPtr = &serviceMapHdr[1];
    payloadLen -= sizeof(IDNHDR_SERVICEMAP_RESPONSE);
    if (serviceMapHdr->entrySize != sizeof(IDNHDR_SERVICEMAP_ENTRY))
    {
        logError("ServiceMapRsp(%s): Invalid entry struct size %u", strRemoteAddr, serviceMapHdr->entrySize);
        return 0;
    }

    unsigned entryCount = serviceMapHdr->relayEntryCount + serviceMapHdr->serviceEntryCount;
    if (payloadLen != entryCount * serviceMapHdr->entrySize)
    {
        logError("ServiceMapRsp(%s): Invalid entry table %u != %u * %u", strRemoteAddr, payloadLen, entryCount, serviceMapHdr->entrySize);
        return 0;
    }


    // -------------------------------------------------------------------------
    //  Read relay table and service table
    // -------------------------------------------------------------------------

    IDNHDR_SERVICEMAP_ENTRY* serviceMapEntry = (IDNHDR_SERVICEMAP_ENTRY*)payloadPtr;
    IDNSL_RELAY_INFO* relayTable = (IDNSL_RELAY_INFO*)0;
    IDNSL_SERVICE_INFO* serviceTable = (IDNSL_SERVICE_INFO*)0;
    do
    {
        // Read relay entries
        if (serviceMapHdr->relayEntryCount > 0)
        {
            // Allocate memory
            relayTable = (IDNSL_RELAY_INFO*)calloc(serviceMapHdr->relayEntryCount, sizeof(IDNSL_RELAY_INFO));
            if (relayTable == (IDNSL_RELAY_INFO*)0)
            {
                logError("calloc(IDNSL_RELAY_INFO) failed");
                break;
            }

            // Copy entries
            unsigned relayIndex;
            for (relayIndex = 0; relayIndex < serviceMapHdr->relayEntryCount; relayIndex++)
            {
                // Validate input fields
                if (serviceMapEntry->serviceID != 0)
                {
                    logError("ServiceMapRsp(%s, relay): Invalid serviceID %u", strRemoteAddr, serviceMapEntry->serviceID);
                    break;
                }
                else if (serviceMapEntry->serviceType != 0)
                {
                    logError("ServiceMapRsp(%s, relay): Invalid serviceType %u", strRemoteAddr, serviceMapEntry->serviceType);
                    break;
                }
                else if (serviceMapEntry->relayNumber == 0)
                {
                    logError("ServiceMapRsp(%s, relay): Invalid relayNumber %u", strRemoteAddr, serviceMapEntry->relayNumber);
                    break;
                }

                // Copy fields
                IDNSL_RELAY_INFO* relayEntry = &relayTable[relayIndex];
                relayEntry->relayNumber = serviceMapEntry->relayNumber;
                relayEntry->flags = serviceMapEntry->flags;
                COPY_NAME_NULLTERM(relayEntry->relayName, serviceMapEntry->name);

                // Next entry
                serviceMapEntry = &serviceMapEntry[1];
            }
            if (relayIndex < serviceMapHdr->relayEntryCount) 
                break;
        }

        // Read service entries
        if (serviceMapHdr->serviceEntryCount > 0)
        {
            // Allocate memory
            serviceTable = (IDNSL_SERVICE_INFO*)calloc(serviceMapHdr->serviceEntryCount, sizeof(IDNSL_SERVICE_INFO));
            if (serviceTable == (IDNSL_SERVICE_INFO*)0)
            {
                logError("calloc(IDNSL_SERVICE_INFO) failed");
                break;
            }

            // Copy entries
            unsigned serviceIndex;
            for (serviceIndex = 0; serviceIndex < serviceMapHdr->serviceEntryCount; serviceIndex++)
            {
                // Validate input fields
                if (serviceMapEntry->serviceID == 0)
                {
                    logError("ServiceMapRsp(%s, service): Invalid serviceID %u", strRemoteAddr, serviceMapEntry->serviceID);
                    break;
                }

                // Copy fields
                IDNSL_SERVICE_INFO* serviceEntry = &serviceTable[serviceIndex];
                serviceEntry->serviceID = serviceMapEntry->serviceID;
                serviceEntry->serviceType = serviceMapEntry->serviceType;
                serviceEntry->flags = serviceMapEntry->flags;
                COPY_NAME_NULLTERM(serviceEntry->serviceName, serviceMapEntry->name);

                // In case associated with a relay: Link into relay service list
                if (serviceMapEntry->relayNumber != 0)
                {
                    unsigned relayIndex;
                    for (relayIndex = 0; relayIndex < serviceMapHdr->relayEntryCount; relayIndex++)
                    {
                        IDNSL_RELAY_INFO* relayEntry = &relayTable[relayIndex];
                        if (relayEntry->relayNumber != serviceMapEntry->relayNumber) continue;

                        // First in list - or append to end of list
                        if (relayEntry->firstRelayService == (IDNSL_SERVICE_INFO*)0)
                        {
                            relayEntry->firstRelayService = serviceEntry;
                        }
                        else
                        {
                            IDNSL_SERVICE_INFO* cursor = relayEntry->firstRelayService;
                            while (cursor->nextRelayService != (IDNSL_SERVICE_INFO*)0) 
                                cursor = cursor->nextRelayService;
                            cursor->nextRelayService = serviceEntry;
                        }

                        // Found / done
                        serviceEntry->parentRelay = relayEntry;
                        break;
                    }
                    if (relayIndex == serviceMapHdr->relayEntryCount)
                    {
                        logError("ServiceMapRsp(%s, service): Invalid relayNumber %u", strRemoteAddr, serviceMapEntry->relayNumber);
                        break;
                    }
                }

                // Next entry
                serviceMapEntry = &serviceMapEntry[1];
            }
            if (serviceIndex < serviceMapHdr->serviceEntryCount) break;
        }

        // Assign relay table
        responseInfo->serverInfo->relayCount = serviceMapHdr->relayEntryCount;
        responseInfo->serverInfo->relayTable = relayTable;
        relayTable = (IDNSL_RELAY_INFO*)0;

        // Assign service table
        responseInfo->serverInfo->serviceCount = serviceMapHdr->serviceEntryCount;
        responseInfo->serverInfo->serviceTable = serviceTable;
        serviceTable = (IDNSL_SERVICE_INFO*)0;

        // No error
        return 1;
    } while (0);

    // Free memory in case of errors (service map not available)
    if (relayTable) free(relayTable);
    if (serviceTable) free(serviceTable);

    return 0;
}


static int recvInfoResponse(SCAN_CONTEXT* scanCtx)
{
    struct sockaddr_in recvSockAddr;
    struct sockaddr* recvAddr = (struct sockaddr*)&recvSockAddr;
    socklen_t recvAddrSize = sizeof(recvSockAddr);
    int fdSocket = scanCtx->infoRequestQueue.fdSocket;

    // Receive reply from scan request
    int nBytes = recvfrom(fdSocket, (char*)scanCtx->packetBuffer, sizeof(scanCtx->packetBuffer), 0, recvAddr, &recvAddrSize);
    if (nBytes < 0)
    {
        logError("recvfrom() failed (error: %d)", plt_sockGetLastError());
        return -1;
    }

    // Convert IP address to string
    char strRemoteAddr[20];
    if (inet_ntop(AF_INET, &recvSockAddr.sin_addr, strRemoteAddr, sizeof(strRemoteAddr)) == (char*)0)
    {
        logError("inet_ntop() failed (error: %d)", plt_sockGetLastError());
        return -1;
    }

    // Check sender port
    if (ntohs(recvSockAddr.sin_port) != IDNVAL_HELLO_UDP_PORT)
    {
        logError("InfoRsp(%s): Invalid sender port %u", strRemoteAddr, ntohs(recvSockAddr.sin_port));
        return 0;
    }

    // Get info record for address from which the datagram was received
    RESPONSE_INFO* responseInfo = getResponseInfo(scanCtx, &(recvSockAddr.sin_addr));
    if (responseInfo == (RESPONSE_INFO*)0) 
        return -1;


    // -------------------------------------------------------------------------
    //  Check IDN-Hello packet header
    // -------------------------------------------------------------------------

    if ((size_t)nBytes < sizeof(IDNHDR_PACKET))
    {
        logError("InfoRsp(%s): Invalid packet size %u", strRemoteAddr, nBytes);
        return 0;
    }

    // Calculate pointers
    IDNHDR_PACKET* recvPacketHdr = (IDNHDR_PACKET*)scanCtx->packetBuffer;
    void* payloadPtr = &recvPacketHdr[1];
    size_t payloadLen = (size_t)nBytes - sizeof(IDNHDR_PACKET);

    // Dispatch based response
    if (recvPacketHdr->command == IDNCMD_SERVICEMAP_RESPONSE)
    {
        uint16_t sequenceNum = responseInfo->serviceMapSequenceNum;
        if (ntohs(recvPacketHdr->sequence) != sequenceNum)
        {
            logError("ServiceMapRsp(%s): Invalid sequence %04X %04X", strRemoteAddr, recvPacketHdr->sequence, sequenceNum);
            return 0;
        }

        // Process service map response
        int rcRsp = serviceMapResponse(scanCtx, responseInfo, payloadPtr, payloadLen);
        if (rcRsp <= 0) 
            return rcRsp;
    }
    else
    {
        logError("%s: Invalid command 0x%02X", strRemoteAddr, recvPacketHdr->command);
        return 0;
    }

    return 0;
}


// -------------------------------------------------------------------------------------------------
//  Discovery broadcast and reachability handling
// -------------------------------------------------------------------------------------------------

static int sendBroadcastRequest(SCAN_CONTEXT* scanCtx, INTERFACE_NODE* ifNode)
{
    // Remember request packet sequence number
    ifNode->scanSequenceNum = scanCtx->sequenceNum++;
    // Use network broadcast address (to find all servers)
    struct sockaddr_in remoteSockAddr;
    remoteSockAddr.sin_family = AF_INET;
    remoteSockAddr.sin_port = htons(IDNVAL_HELLO_UDP_PORT);
    remoteSockAddr.sin_addr.s_addr = ifNode->ipAddr | ~ifNode->ipMask; //| (255 << (8 * 3));//INADDR_BROADCAST;

    // Populate IDN-Hello request packet
    IDNHDR_PACKET reqPacketHdr;
    reqPacketHdr.command = IDNCMD_SCAN_REQUEST;
    reqPacketHdr.flags = scanCtx->clientGroup & IDNMSK_PKTFLAGS_GROUP;
    reqPacketHdr.sequence = htons(ifNode->scanSequenceNum);

    // Broadcast the scan request
    if (sendto(ifNode->fdSocket, (char*)&reqPacketHdr, sizeof(reqPacketHdr), 0, (struct sockaddr*)&remoteSockAddr, sizeof(remoteSockAddr)) < 0)
    {
        logError("sendto() failed (error: %d)", plt_sockGetLastError());
        return -1;
    }

    return 0;
}


static int scheduleCheckRequest(SCAN_CONTEXT* scanCtx, RESPONSE_INFO* responseInfo)
{
    uint8_t cmd = IDNCMD_SCAN_REQUEST;
    uint16_t sequenceNum = responseInfo->checkSequenceNum = scanCtx->sequenceNum++;
    return scheduleQueryRequest(&(scanCtx->checkRequestQueue), cmd, scanCtx->clientGroup, sequenceNum, &(responseInfo->addr));
}


static IDNSL_SERVER_INFO* getServerInfo(SCAN_CONTEXT* scanCtx, IDNHDR_SCAN_RESPONSE* scanRspHdr)
{
    // In case the server is already known: Return server info
    IDNSL_SERVER_INFO** ppServerInfo = &scanCtx->firstServerInfo;
    for (; *ppServerInfo; ppServerInfo = &((*ppServerInfo)->next))
    {
        IDNSL_SERVER_INFO* serverInfo = *ppServerInfo;

        // Check UnitID length (stored in first byte)
        if (serverInfo->unitID[0] != scanRspHdr->unitID[0]) 
            continue;

        // Check UnitID. On match, return info record
        if (!memcmp(&serverInfo->unitID[1], &scanRspHdr->unitID[1], scanRspHdr->unitID[0])) 
            return serverInfo;
    }

    // Check unit ID length
    uint8_t unitIDLen = scanRspHdr->unitID[0];
    if ((unitIDLen >= sizeof(scanRspHdr->unitID)) || (unitIDLen >= sizeof(((IDNSL_SERVER_INFO*)0)->unitID)))
    {
        logError("serverInfo: Invalid unitID length %u", unitIDLen);
        return (IDNSL_SERVER_INFO*)0;
    }

    // New server - allocate info record and append to list
    *ppServerInfo = (IDNSL_SERVER_INFO*)calloc(1, sizeof(IDNSL_SERVER_INFO));
    if (*ppServerInfo == (IDNSL_SERVER_INFO*)0)
    {
        logError("calloc(IDN_SERVER_INFO) failed");
        return (IDNSL_SERVER_INFO*)0;
    }

    // Populate unitID (Note: Field 0-initialized - calloc) and host name.
    IDNSL_SERVER_INFO* serverInfo = *ppServerInfo;
    serverInfo->unitID[0] = unitIDLen;
    memcpy(&serverInfo->unitID[1], &scanRspHdr->unitID[1], unitIDLen);
    COPY_NAME_NULLTERM(serverInfo->hostName, scanRspHdr->hostName);

    // Return new server info record
    return serverInfo;
}


static int getServerAddressIndex(IDNSL_SERVER_INFO* serverInfo, struct in_addr* addr)
{
    // In case the address is already known: return the index
    for (unsigned i = 0; i < serverInfo->addressCount; i++)
    {
        IDNSL_SERVER_ADDRESS* serverAddr = &serverInfo->addressTable[i];
        if (memcmp(&serverAddr->addr, addr, sizeof(struct in_addr)) == 0) 
            return i;
    }

    // New address - reallocate address table
    size_t newSize = (serverInfo->addressCount + 1) * sizeof(IDNSL_SERVER_ADDRESS);
    serverInfo->addressTable = (IDNSL_SERVER_ADDRESS*)realloc(serverInfo->addressTable, newSize);
    if (serverInfo->addressTable == (IDNSL_SERVER_ADDRESS*)0) 
    { 
        serverInfo->addressCount = 0; 
        return -1; 
    }

    // Populate info entry fields, assume unreachable
    unsigned addrIndex = serverInfo->addressCount++;
    IDNSL_SERVER_ADDRESS* serverAddr = &serverInfo->addressTable[addrIndex];
    memset(serverAddr, 0, sizeof(IDNSL_SERVER_ADDRESS));
    serverAddr->errorFlags = IDNSL_ADDR_ERRORFLAG_UNREACHABLE;
    serverAddr->addr = *addr;

    return addrIndex;
}


static int putScannedAddress(IDNSL_SERVER_INFO* serverInfo, struct in_addr* addr)
{
    return getServerAddressIndex(serverInfo, addr);
}


static int putCheckedAddress(IDNSL_SERVER_INFO* serverInfo, struct in_addr* addr)
{
    int addrIndex = getServerAddressIndex(serverInfo, addr);
    if (addrIndex < 0) 
        return addrIndex;

    // Reachability has been checked - remove error flag.
    serverInfo->addressTable[addrIndex].errorFlags &= ~IDNSL_ADDR_ERRORFLAG_UNREACHABLE;
    if (serverInfo->addressTable[addrIndex].errorFlags != 0) 
        return addrIndex;

    // Maintain address info list order (reachable first, erroneous last)
    for (; addrIndex > 0; addrIndex--)
    {
        IDNSL_SERVER_ADDRESS checkInfo = serverInfo->addressTable[addrIndex - 1];
        if (checkInfo.errorFlags == 0) 
            break;

        // Swap in case entry is preceeded by an erroneous entry
        serverInfo->addressTable[addrIndex - 1] = serverInfo->addressTable[addrIndex];
        serverInfo->addressTable[addrIndex] = checkInfo;
    }

    return addrIndex;
}


static int putAmbiguousAddress(IDNSL_SERVER_INFO* serverInfo, struct in_addr* addr)
{
    int addrIndex = getServerAddressIndex(serverInfo, addr);
    if (addrIndex < 0) 
        return addrIndex;

    // Set error flag
    serverInfo->addressTable[addrIndex].errorFlags |= IDNSL_ADDR_ERRORFLAG_AMBIGUOUS;

    // Maintain address info list order (reachable first, erroneous last)
    int addrLimit = (int)(serverInfo->addressCount) - 1;
    for (; addrIndex < addrLimit; addrIndex++)
    {
        IDNSL_SERVER_ADDRESS checkInfo = serverInfo->addressTable[addrIndex + 1];
        if (checkInfo.errorFlags != 0) 
            break;

        // Swap in case entry is followed by a reachable entry
        serverInfo->addressTable[addrIndex + 1] = serverInfo->addressTable[addrIndex];
        serverInfo->addressTable[addrIndex] = checkInfo;
    }

    return addrIndex;
}


static int recvScanResponse(SCAN_CONTEXT* scanCtx, INTERFACE_NODE* ifNode)
{
    struct sockaddr_in recvSockAddr;
    struct sockaddr* recvAddr = (struct sockaddr*)&recvSockAddr;
    socklen_t recvAddrSize = sizeof(recvSockAddr);
    int fdSocket = ifNode ? ifNode->fdSocket : scanCtx->checkRequestQueue.fdSocket;

    // Receive reply from scan request
    int nBytes = recvfrom(fdSocket, (char*)scanCtx->packetBuffer, sizeof(scanCtx->packetBuffer), 0, recvAddr, &recvAddrSize);
    if (nBytes < 0)
    {
        logError("recvfrom() failed (error: %d)", plt_sockGetLastError());
        return -1;
    }

    // Convert IP address to string
    char strRemoteAddr[20];
    if (inet_ntop(AF_INET, &recvSockAddr.sin_addr, strRemoteAddr, sizeof(strRemoteAddr)) == (char*)0)
    {
        logError("inet_ntop() failed (error: %d)", plt_sockGetLastError());
        return -1;
    }

    // Check sender port
    if (ntohs(recvSockAddr.sin_port) != IDNVAL_HELLO_UDP_PORT)
    {
        logError("ScanRsp(%s): Invalid sender port %u", strRemoteAddr, ntohs(recvSockAddr.sin_port));
        return 0;
    }

    // Get info record for address from which the datagram was received
    RESPONSE_INFO* responseInfo = getResponseInfo(scanCtx, &(recvSockAddr.sin_addr));
    if (responseInfo == (RESPONSE_INFO*)0) 
        return -1;


    // -------------------------------------------------------------------------
    //  Check IDN-Hello packet header
    // -------------------------------------------------------------------------

    if ((size_t)nBytes < sizeof(IDNHDR_PACKET))
    {
        logError("ScanRsp(%s): Invalid packet size %u", strRemoteAddr, nBytes);
        return 0;
    }

    // Calculate pointers
    IDNHDR_PACKET* recvPacketHdr = (IDNHDR_PACKET*)scanCtx->packetBuffer;
    void* payloadPtr = &recvPacketHdr[1];
    size_t payloadLen = (size_t)nBytes - sizeof(IDNHDR_PACKET);

    // Check packet command
    if (recvPacketHdr->command != IDNCMD_SCAN_RESPONSE)
    {
        logError("scanRsp(%s): Invalid command 0x%02X", strRemoteAddr, recvPacketHdr->command);
        return 0;
    }

    // Check sequence number (distinguish broadcast discovery and unicast check)
    uint16_t sequenceNum = ifNode ? ifNode->scanSequenceNum : responseInfo->checkSequenceNum;
    if (ntohs(recvPacketHdr->sequence) != sequenceNum)
    {
        logError("scanRsp(%s): Invalid sequence %04X %04X", strRemoteAddr, recvPacketHdr->sequence, sequenceNum);
        return 0;
    }


    // -------------------------------------------------------------------------
    //  Check scan response header
    // -------------------------------------------------------------------------

    if (payloadLen < sizeof(IDNHDR_SCAN_RESPONSE))
    {
        logError("scanRsp(%s): Invalid response length %u", strRemoteAddr, payloadLen);
        return 0;
    }

    IDNHDR_SCAN_RESPONSE* scanRspHdr = (IDNHDR_SCAN_RESPONSE*)payloadPtr;
    if (scanRspHdr->structSize < sizeof(IDNHDR_SCAN_RESPONSE))
    {
        logError("scanRsp(%s): Invalid header size %u", strRemoteAddr, scanRspHdr->structSize);
        return 0;
    }

    if (payloadLen < scanRspHdr->structSize)
    {
        logError("scanRsp(%s): Invalid payload length %u %u", strRemoteAddr, payloadLen, scanRspHdr->structSize);
        return 0;
    }


    // -------------------------------------------------------------------------
    //  Update server info
    // -------------------------------------------------------------------------

    IDNSL_SERVER_INFO* serverInfo = getServerInfo(scanCtx, scanRspHdr);
    if (serverInfo == (IDNSL_SERVER_INFO*)0) 
        return -1;

    // Check for server/responseInfo match
    int addrIndex;
    if ((responseInfo->serverInfo != (IDNSL_SERVER_INFO*)0) && (responseInfo->serverInfo != serverInfo))
    {
        // Pointer mismatch / Different servers on same address - ignore both
        int addrIndex1 = putAmbiguousAddress(serverInfo, &(recvSockAddr.sin_addr));
        if (addrIndex1 < 0) 
            return -1;

        int addrIndex2 = putAmbiguousAddress(responseInfo->serverInfo, &(recvSockAddr.sin_addr));
        if (addrIndex2 < 0) 
            return -1;

        // Set error for response info record, abort in case there is no (error-free) default address
        // Note: There is at least one address in the address table!
        responseInfo->ambiguousErrorFlag = 1;
        if (serverInfo->addressTable[0].errorFlags != 0) 
            return 0;

        // Find the info record for the default address
        // Note: Address order may have shifted because erroneous addresses are moved to the end
        responseInfo = getResponseInfo(scanCtx, &(serverInfo->addressTable[0].addr));
        if (responseInfo == (RESPONSE_INFO*)0) 
            return -1;

        // Check for info retrieval on default address
        addrIndex = 0;
    }
    else
    {
        // Check for new server
        if (responseInfo->serverInfo == (IDNSL_SERVER_INFO*)0)
        {
            // Link response address info record with server to find misconfigured servers
            responseInfo->serverInfo = serverInfo;

            // Schedule reachability check. Note: Since broadcasts are sent on 255.255.255.255 
            // ('this network'), any device (configured correctly or wrong) can send a response.
            // Depending on IP-Stack and firewall setup this might be received or not. However,
            // reception does not mean that the device is reachable (there may be no route).
            if (scheduleCheckRequest(scanCtx, responseInfo)) 
                return -1;
        }

        // Add/Modify address for broadcast(scan/uncertain) or unicast(checked/reachable) reply
        if (ifNode) 
            addrIndex = putScannedAddress(serverInfo, &recvSockAddr.sin_addr);
        else 
            addrIndex = putCheckedAddress(serverInfo, &recvSockAddr.sin_addr);

        if (addrIndex < 0) 
            return -1;
    }

    // In case the server got a default address, schedule info requests (if not done yet)
    // Note: There is at least one address in the address table!
    if ((addrIndex == 0) && (serverInfo->addressTable[0].errorFlags == 0) && (responseInfo->infoRequestFlag == 0))
    {
        if (scheduleInfoRequests(scanCtx, responseInfo)) 
            return -1;
        responseInfo->infoRequestFlag = 1;
    }

    return 0;
}


// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------


static int runScan(SCAN_CONTEXT* scanCtx, unsigned msTimeout)
{
    // File descriptor sets
    fd_set rfdsPrm, wfdsPrm;
    FD_ZERO(&rfdsPrm);
    FD_ZERO(&wfdsPrm);
    int maxSocket = 0;

    // Add interface broadcast socket descriptors
    for (INTERFACE_NODE* ifNode = scanCtx->firstIfNode; ifNode; ifNode = ifNode->next)
    {
        FD_SET(ifNode->fdSocket, &wfdsPrm);
        FD_SET(ifNode->fdSocket, &rfdsPrm);
        if (ifNode->fdSocket > maxSocket) maxSocket = ifNode->fdSocket;
    }

    // Add reachability check socket descriptor
    FD_SET(scanCtx->checkRequestQueue.fdSocket, &wfdsPrm);
    FD_SET(scanCtx->checkRequestQueue.fdSocket, &rfdsPrm);
    if (scanCtx->checkRequestQueue.fdSocket > maxSocket) maxSocket = scanCtx->checkRequestQueue.fdSocket;

    // Add device info socket descriptor
    FD_SET(scanCtx->infoRequestQueue.fdSocket, &wfdsPrm);
    FD_SET(scanCtx->infoRequestQueue.fdSocket, &rfdsPrm);
    if (scanCtx->infoRequestQueue.fdSocket > maxSocket) maxSocket = scanCtx->infoRequestQueue.fdSocket;

    // Remember start time
    uint64_t usStart = plt_getMonoTimeUS();

    // Send requests, receive replies
    while (1)
    {
        // Calculate time left
        uint64_t usNow = plt_getMonoTimeUS();
        uint32_t usElapsed = usNow - usStart;
        uint32_t usLeft = (msTimeout * 1000) - usElapsed;
        if ((int32_t)usLeft <= 0) 
            break;

        // Populate select timeout
        struct timeval tv;
        tv.tv_sec = usLeft / 1000000;
        tv.tv_usec = usLeft % 1000000;

        // Get writability and readability on sockets. On timeout just terminate the loop
        fd_set rfdsResult = rfdsPrm, wfdsResult = wfdsPrm;
        int numReady = select(maxSocket + 1, &rfdsResult, &wfdsResult, 0, &tv);
        if (numReady < 0)
        {
            logError("select() failed (error: %d)", plt_sockGetLastError());
            return -1;
        }
        else if (numReady == 0)
        {
            // Timeout - no packets received, no more packets to send
            break;
        }

        // -------------------------------------------------------------------------

        // Check broadcast/discovery sockets
        for (INTERFACE_NODE* ifNode = scanCtx->firstIfNode; ifNode; ifNode = ifNode->next)
        {
            if (FD_ISSET(ifNode->fdSocket, &wfdsResult))
            {
                FD_CLR(ifNode->fdSocket, &wfdsPrm);
                if (sendBroadcastRequest(scanCtx, ifNode))
                    return -1;
            }

            if (FD_ISSET(ifNode->fdSocket, &rfdsResult))
            {
                if (recvScanResponse(scanCtx, ifNode))
                    continue;

                // In case of pending check requests: Set socket write interest
                if (scanCtx->checkRequestQueue.firstRequest != (REQUEST_JOB*)0)
                {
                    FD_SET(scanCtx->checkRequestQueue.fdSocket, &wfdsPrm);
                }

                // In case of pending info requests: Set socket write interest
                if (scanCtx->infoRequestQueue.firstRequest != (REQUEST_JOB*)0)
                {
                    FD_SET(scanCtx->infoRequestQueue.fdSocket, &wfdsPrm);
                }
            }
        }

        // -------------------------------------------------------------------------

        // Check for reachability check socket to be writable (send check requests)
        if (FD_ISSET(scanCtx->checkRequestQueue.fdSocket, &wfdsResult))
        {
            if (sendNextRequest(&(scanCtx->checkRequestQueue))) 
                return -1;

            // In case no more check requests are pending: Reset socket write interest
            if (scanCtx->checkRequestQueue.firstRequest == (REQUEST_JOB*)0)
            {
                FD_CLR(scanCtx->checkRequestQueue.fdSocket, &wfdsPrm);
            }
        }

        // Check for reachability check socket to be readable (receive check responses)
        if (FD_ISSET(scanCtx->checkRequestQueue.fdSocket, &rfdsResult))
        {
            if (recvScanResponse(scanCtx, (INTERFACE_NODE*)0)) 
                return -1;

            // In case of pending info requests: Set socket write interest
            if (scanCtx->infoRequestQueue.firstRequest != (REQUEST_JOB*)0)
            {
                FD_SET(scanCtx->infoRequestQueue.fdSocket, &wfdsPrm);
            }
        }

        // -------------------------------------------------------------------------

        // Check for device info socket to be writable (send info requests)
        if (FD_ISSET(scanCtx->infoRequestQueue.fdSocket, &wfdsResult))
        {
            if (sendNextRequest(&(scanCtx->infoRequestQueue))) 
                return -1;

            // In case no more info requests are pending: Reset socket write interest
            if (scanCtx->infoRequestQueue.firstRequest == (REQUEST_JOB*)0)
            {
                FD_CLR(scanCtx->infoRequestQueue.fdSocket, &wfdsPrm);
            }
        }

        // Check for device info socket to be readable (receive info responses)
        if (FD_ISSET(scanCtx->infoRequestQueue.fdSocket, &rfdsResult))
        {
            if (recvInfoResponse(scanCtx)) 
                return -1;
        }
    }

    return 0;
}


// -------------------------------------------------------------------------------------------------
//  API functions
// -------------------------------------------------------------------------------------------------

int getIDNServerList(IDNSL_SERVER_INFO** ppFirstServerInfo, uint8_t clientGroup, unsigned msTimeout)
{
    // Validate/Initialize result argument
    if (ppFirstServerInfo == (IDNSL_SERVER_INFO**)NULL) 
        return -1;
    *ppFirstServerInfo = (IDNSL_SERVER_INFO*)NULL;

    // Validate client group argument
    if (clientGroup > 15) 
        return -1;

    // Validate monotonic time reference
    if (plt_validateMonoTime() != 0)
    {
        logError("Monotonic time init failed");
        return -1;
    }

    // Allocate a context to keep variables for this scan. Note: Contains receive packet buffer
    SCAN_CONTEXT* scanCtx = (SCAN_CONTEXT*)calloc(1, sizeof(SCAN_CONTEXT));
    if (scanCtx == (SCAN_CONTEXT*)0)
    {
        logError("calloc(SCAN_CONTEXT) failed");
        return -1;
    }

    // Populate context
    scanCtx->clientGroup = clientGroup;


    // -------------------------------------------------------------------------
    //  Run the scan
    // -------------------------------------------------------------------------

    int result = -1;
    do
    {
        // Get a start sequence number
        scanCtx->sequenceNum = (uint16_t)clock();

        // Walk all interfaces - creating interface structs containing broadcast sockets and state
        if (plt_ifAddrListVisitor(createInterfaceNode, scanCtx)) 
            break;

        // Create unicast socket (for reachability check requests)
        scanCtx->checkRequestQueue.fdSocket = plt_sockOpen(AF_INET, SOCK_DGRAM, 0);
        if (scanCtx->checkRequestQueue.fdSocket < 0)
        {
            logError("socket() failed (error: %d)", plt_sockGetLastError());
            break;
        }

        // Create unicast socket (for device info requests)
        scanCtx->infoRequestQueue.fdSocket = plt_sockOpen(AF_INET, SOCK_DGRAM, 0);
        if (scanCtx->infoRequestQueue.fdSocket < 0)
        {
            logError("socket() failed (error: %d)", plt_sockGetLastError());
            break;
        }

        // Find the devices
        if (runScan(scanCtx, msTimeout)) 
            break;

        // Successful - set result
        *ppFirstServerInfo = scanCtx->firstServerInfo;
        scanCtx->firstServerInfo = (IDNSL_SERVER_INFO*)0;
        result = 0;
    } while (0);


    // -------------------------------------------------------------------------
    //  Cleanup
    // -------------------------------------------------------------------------

    // Delete interface structs
    while (scanCtx->firstIfNode)
    {
        INTERFACE_NODE* ifNode = scanCtx->firstIfNode;
        LINKOUT_NODE(scanCtx->firstIfNode, scanCtx->lastIfNode, ifNode);
        deleteInterfaceNode(ifNode);
    }

    // Delete device response info list
    while (scanCtx->firstResponseInfo)
    {
        RESPONSE_INFO* responseInfo = scanCtx->firstResponseInfo;
        LINKOUT_NODE(scanCtx->firstResponseInfo, scanCtx->lastResponseInfo, responseInfo);
        free(responseInfo);
    }

    // Delete check request list
    while (scanCtx->checkRequestQueue.firstRequest)
    {
        REQUEST_JOB* reqJob = scanCtx->checkRequestQueue.firstRequest;
        LINKOUT_NODE(scanCtx->checkRequestQueue.firstRequest, scanCtx->checkRequestQueue.lastRequest, reqJob);
        free(reqJob);
    }

    // Delete info request list
    while (scanCtx->infoRequestQueue.firstRequest)
    {
        REQUEST_JOB* reqJob = scanCtx->infoRequestQueue.firstRequest;
        LINKOUT_NODE(scanCtx->infoRequestQueue.firstRequest, scanCtx->infoRequestQueue.lastRequest, reqJob);
        free(reqJob);
    }

    // Close unicast device info socket
    if (scanCtx->checkRequestQueue.fdSocket >= 0)
    {
        int fdSocket = scanCtx->checkRequestQueue.fdSocket;
        if (plt_sockClose(fdSocket)) 
            logError("close() failed (error: %d)", plt_sockGetLastError());
    }

    // Close unicast reachability check socket
    if (scanCtx->infoRequestQueue.fdSocket >= 0)
    {
        int fdSocket = scanCtx->infoRequestQueue.fdSocket;
        if (plt_sockClose(fdSocket)) 
            logError("close() failed (error: %d)", plt_sockGetLastError());
    }

    // In case of errors - free device list memory
    if (scanCtx->firstServerInfo) 
        freeIDNServerList(scanCtx->firstServerInfo);

    // Free context struct memory
    free(scanCtx);

    return result;
}


void freeIDNServerList(IDNSL_SERVER_INFO* firstServerInfo)
{
    if (firstServerInfo == (IDNSL_SERVER_INFO*)0) return;

    // Delete server info list
    while (firstServerInfo)
    {
        IDNSL_SERVER_INFO* serverInfo = firstServerInfo;
        firstServerInfo = firstServerInfo->next;

        // Free table memories
        if (serverInfo->addressTable) 
            free(serverInfo->addressTable);
        if (serverInfo->serviceTable) 
            free(serverInfo->serviceTable);
        if (serverInfo->relayTable) 
            free(serverInfo->relayTable);

        // Free server info struct memory
        free(serverInfo);
    }
}

