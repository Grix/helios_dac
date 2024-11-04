// -------------------------------------------------------------------------------------------------
//  File idn-hello.h
// 
//  Copyright (c) 2013-2018 DexLogic, Dirk Apitz
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
//  07/2013 Dirk Apitz, created
//  06/2015 Dirk Apitz, Scan response: protocol version moved, name len changed
//  12/2015 Dirk Apitz, Service map
//  05/2016 Dirk Apitz, Generic data types
//  01/2017 Dirk Apitz, ServiceMap
//  06/2017 Dirk Apitz, moved udp port to hello header
//  12/2017 Dirk Apitz, client groups, unit/link status, RT Close/Acknowledge
//
//  Version: 2018-07-01
// -------------------------------------------------------------------------------------------------


#ifndef IDN_HELLO_H
#define IDN_HELLO_H


// Standard libraries
#include <stdint.h>


// -------------------------------------------------------------------------------------------------
//  Defines
// -------------------------------------------------------------------------------------------------

// UDP protocol
#define IDNVAL_HELLO_UDP_PORT               7255

// Packet commands
#define IDNCMD_VOID                         0x00
#define IDNCMD_PING_REQUEST                 0x08    // Can be used for round trip measurements
#define IDNCMD_PING_RESPONSE                0x09    // Request payload data copied into response.

#define IDNCMD_GROUP_REQUEST                0x0C    // Client group mask retrieval/modification
#define IDNCMD_GROUP_RESPONSE               0x0D    // Result and current client group mask

#define IDNCMD_SCAN_REQUEST                 0x10    // Network scan for units
#define IDNCMD_SCAN_RESPONSE                0x11    // Unit identification and status
#define IDNCMD_SERVICEMAP_REQUEST           0x12    // Request for unit services
#define IDNCMD_SERVICEMAP_RESPONSE          0x13    // Map of supported services

#define IDNCMD_SERVICE_PARAMETERS_REQUEST   0x20
#define IDNCMD_SERVICE_PARAMETERS_RESPONSE  0x21
#define IDNCMD_UNIT_PARAMETERS_REQUEST      0x22
#define IDNCMD_UNIT_PARAMETERS_RESPONSE     0x23
#define IDNCMD_LINK_PARAMETERS_REQUEST      0x28
#define IDNCMD_LINK_PARAMETERS_RESPONSE     0x29

#define IDNCMD_RT_CNLMSG                    0x40    // Realtime channel message (empty: keepalive)
#define IDNCMD_RT_CNLMSG_ACKREQ             0x41    // Realtime channel message + request acknowledge
#define IDNCMD_RT_CNLMSG_CLOSE              0x44    // Gracefully close (if msg: process, then close)
#define IDNCMD_RT_CNLMSG_CLOSE_ACKREQ       0x45    // Gracefully close + request acknowledge
#define IDNCMD_RT_ACKNOWLEDGE               0x47    // Acknowledgement response

// Packet flags masks
#define IDNMSK_PKTFLAGS_GROUP               0x0F    // The lower 4 bits are the client group

// Client group operation codes
#define IDNVAL_GROUPOP_SUCCESS              0x00    // Successful operation
#define IDNVAL_GROUPOP_GETMASK              0x01    // Get the group mask
#define IDNVAL_GROUPOP_SETMASK              0x02    // Set the group mask
#define IDNVAL_GROUPOP_ERR_AUTH             0xFD    // Authentication error
#define IDNVAL_GROUPOP_ERR_OPERATION        0xFE    // Invalid operation
#define IDNVAL_GROUPOP_ERR_REQUEST          0xFF    // Invalid request

// SCAN response status flags
#define IDNFLG_SCAN_STATUS_MALFUNCTION      0x80    // The unit has a permanent malfunction
#define IDNFLG_SCAN_STATUS_OFFLINE          0x40    // Currently unavailable (bootup, overheat, eStop)
#define IDNFLG_SCAN_STATUS_EXCLUDED         0x20    // The client group is excluded from streaming
#define IDNFLG_SCAN_STATUS_OCCUPIED         0x10    // All sessions are occupied by clients
#define IDNFLG_SCAN_STATUS_REALTIME         0x01    // Offers realtime streaming through IDN-Hello

// Realtime command acknowledgement
#define IDNVAL_RTACK_SUCCESS                0x00    // Successfully accepted
#define IDNVAL_RTACK_ERR_NOT_CONNECTED      0xEB    // Empty close without connection
#define IDNVAL_RTACK_ERR_OCCUPIED           0xEC    // All sessions are occupied by clients
#define IDNVAL_RTACK_ERR_EXCLUDED           0xED    // The client group is excluded from streaming
#define IDNVAL_RTACK_ERR_PAYLOAD            0xEE    // Invalid payload
#define IDNVAL_RTACK_ERR_GENERIC            0xEF    // Any other processing error

#define IDNVAL_RTACK_EVFLG_NEW              0x0001  // New connection
#define IDNVAL_RTACK_EVFLG_SEQERR_LVL1      0x0010  // Sequence error (not strictly increased by 1)
#define IDNMSK_RTACK_EVFLG_SEQERR           0x00F0  // Any sequence error


// -------------------------------------------------------------------------------------------------
//  Typedefs
// -------------------------------------------------------------------------------------------------

typedef struct
{
    uint8_t command;                            // The command code (IDNCMD_*)
    uint8_t flags;                              // Upper 4 bits: Flags; Lower 4 bits: Client group
    uint16_t sequence;                          // Sequence counter, must count up
    
} IDNHDR_PACKET;


typedef struct _IDNHDR_GROUP_REQUEST
{
    uint8_t structSize;                         // Size of this struct.
    int8_t opCode;                              // Operation - set/get
    uint16_t groupMask;                         // Mask for the client groups that shall be enabled
    uint8_t authCode[12];                       // Authentication, not terminated, padded with '\0'

} IDNHDR_GROUP_REQUEST;


typedef struct _IDNHDR_GROUP_RESPONSE
{
    uint8_t structSize;                         // Size of this struct.
    int8_t opCode;                              // Operation (>0 success, <0 error)
    uint16_t groupMask;                         // Mask for the client groups that are enabled

} IDNHDR_GROUP_RESPONSE;


typedef struct _IDNHDR_SCAN_RESPONSE
{
    uint8_t structSize;                         // Size of this struct.
    uint8_t protocolVersion;                    // Upper 4 bits: Major; Lower 4 bits: Minor
    uint8_t status;                             // Unit and link status flags
    uint8_t reserved;
    uint8_t unitID[16];                         // [0]: Len, [1]: Cat, [2..Len]: ID, padded with '\0'
    uint8_t hostName[20];                       // Not terminated, padded with '\0'

} IDNHDR_SCAN_RESPONSE;


typedef struct _IDNHDR_SERVICEMAP_RESPONSE
{
    uint8_t structSize;                         // Size of this struct.
    uint8_t entrySize;                          // Size of an entry - sizeof(IDNHDR_SERVICEMAP_ENTRY)
    uint8_t relayEntryCount;                    // Number of relay entries
    uint8_t serviceEntryCount;                  // Number of service entries

    // Followed by the relay table (of relayEntryCount entries)
    // Followed by the service table (of serviceEntryCount entries)

} IDNHDR_SERVICEMAP_RESPONSE;


typedef struct _IDNHDR_SERVICEMAP_ENTRY
{
    uint8_t serviceID;                          // Service: The ID (!=0); Relay: Must be 0
    uint8_t serviceType;                        // The type of the service; Relay: Must be 0
    uint8_t flags;                              // Status flags and options
    uint8_t relayNumber;                        // Service: Root(0)/Relay(>0); Relay: Number (!=0)
    uint8_t name[20];                           // Not terminated, padded with '\0'

} IDNHDR_SERVICEMAP_ENTRY;


typedef struct _IDNHDR_RT_ACKNOWLEDGE
{
    uint8_t structSize;                         // Size of this struct.
    int8_t resultCode;                          // Acknowledgement result (>0 success, <0 error)
    uint16_t eventFlags;                        // Connection/Session events since last acknowledge

} IDNHDR_RT_ACKNOWLEDGE;



#endif

