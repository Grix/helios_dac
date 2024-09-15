// -------------------------------------------------------------------------------------------------
//  File idnServerList.h
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


#ifndef IDNSERVERLIST_H
#define IDNSERVERLIST_H


// Standard libraries
#include <stdint.h>


// Platform includes
#if defined(_WIN32) || defined(WIN32)

    #include <winsock2.h>

#else

    #include <arpa/inet.h>

#endif


// -------------------------------------------------------------------------------------------------
//  Defines
// -------------------------------------------------------------------------------------------------

#define IDNSL_UNITID_LENGTH                 16
#define IDNSL_HOST_NAME_LENGTH              24
#define IDNSL_SERVICE_NAME_LENGTH           24
#define IDNSL_RELAY_NAME_LENGTH             24

#define IDNSL_ADDR_ERRORFLAG_UNREACHABLE    1           // The address has no route
#define IDNSL_ADDR_ERRORFLAG_AMBIGUOUS      2           // Multiple servers responded on the address


// -------------------------------------------------------------------------------------------------
//  Typedefs
// -------------------------------------------------------------------------------------------------

typedef struct
{
    unsigned errorFlags;

    struct in_addr addr;

} IDNSL_SERVER_ADDRESS;


typedef struct _IDNSL_SERVICE_INFO
{
    uint8_t serviceID;                                  // Needed for service parameter retrival
    uint8_t serviceType;                                // The type of the service reported by IDN-Hello
    uint8_t flags;                                      // The service flags reported by IDN-Hello
    char serviceName[IDNSL_SERVICE_NAME_LENGTH];        // The name reported by IDN-Hello (0-terminated)

    struct _IDNSL_RELAY_INFO *parentRelay;              // The relay the service is related to, null = none/root
    struct _IDNSL_SERVICE_INFO *nextRelayService;       // The next service related to the same relay

} IDNSL_SERVICE_INFO;


typedef struct _IDNSL_RELAY_INFO
{
    uint8_t relayNumber;                                // Needed for relay parameter retrival
    uint8_t flags;                                      // The relay flags reported by IDN-Hello
    char relayName[IDNSL_RELAY_NAME_LENGTH];            // The name reported by IDN-Hello (0-terminated)

    struct _IDNSL_SERVICE_INFO *firstRelayService;      // The list of services managed by the relay

} IDNSL_RELAY_INFO;


typedef struct _IDN_SERVER_INFO
{
    struct _IDN_SERVER_INFO *next;                      // Next server in list

    uint8_t unitID[IDNSL_UNITID_LENGTH];                // The unique unit ID reported by IDN-Hello
    char hostName[IDNSL_HOST_NAME_LENGTH];              // The name of the host (0-terminated)

    unsigned addressCount;
    IDNSL_SERVER_ADDRESS *addressTable;                 // The server addresses (ordered by reachability)

    unsigned serviceCount;
    IDNSL_SERVICE_INFO *serviceTable;                   // The services, the server provides

    unsigned relayCount;
    IDNSL_RELAY_INFO *relayTable;                       // Hidden servers, the server provides a relay for

} IDNSL_SERVER_INFO;


// -------------------------------------------------------------------------------------------------
//  Prototypes
// -------------------------------------------------------------------------------------------------

int getIDNServerList(IDNSL_SERVER_INFO **ppFirstServerInfo, uint8_t clientGroup, unsigned msTimeout);
void freeIDNServerList(IDNSL_SERVER_INFO *firstServerInfo);


#endif

