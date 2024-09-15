// -------------------------------------------------------------------------------------------------
//  File idn-stream.h
//
//  Copyright (c) 2013-2017 DexLogic, Dirk Apitz
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
//  07/2014 Dirk Apitz, Frame mode
//  01/2015 Dirk Apitz, IDN-stream standard draft
//  06/2015 Dirk Apitz, Frame chunk fragments
//  05/2016 Dirk Apitz, Generic data types
//  09/2017 Dirk Apitz, Service types
//
//  Version: 2017-09-03
// -------------------------------------------------------------------------------------------------


#ifndef IDN_STREAM_H
#define IDN_STREAM_H


// Standard libraries
#include <stdint.h>


// -------------------------------------------------------------------------------------------------
//  Defines
// -------------------------------------------------------------------------------------------------

// Service types(0x00..0x3F): Interfaces
#define IDNVAL_STYPE_RELAY                  0x00        // Relay
#define IDNVAL_STYPE_UART                   0x04        // Generic UART
#define IDNVAL_STYPE_DMX512                 0x05        // DMX512

// Service types(0x80..0xBF / 2 LSB): Media types
#define IDNVAL_STYPE_LAPRO                  0x80        // Standard laser projector

// Channel message content IDs
#define IDNFLG_CONTENTID_CHANNELMSG         0x8000      // Channel message flag (specific bit assignments)
#define IDNFLG_CONTENTID_CONFIG_LSTFRG      0x4000      // Set for config header or last fragment
#define IDNMSK_CONTENTID_CHANNELID          0x3F00      // Channel ID bit mask
#define IDNMSK_CONTENTID_CNKTYPE            0x00FF      // Data chunk type bit mask

// Data chunk types - singe message / first fragment
#define IDNVAL_CNKTYPE_VOID                 0x00        // Empty chunk (no data)
#define IDNVAL_CNKTYPE_LPGRF_WAVE           0x01        // Sample data array
#define IDNVAL_CNKTYPE_LPGRF_FRAME          0x02        // Sample data array (entirely)
#define IDNVAL_CNKTYPE_LPGRF_FRAME_FIRST    0x03        // Sample data array (first fragment)
#define IDNVAL_CNKTYPE_OCTET_SEGMENT        0x10        // Delimited sequence of octets (can be multiple chunks)
#define IDNVAL_CNKTYPE_OCTET_STRING         0x11        // Discrete sequence of octets (single chunk)
#define IDNVAL_CNKTYPE_DIMMER_LEVELS        0x18        // Dimmer levels for DMX512 packets

// Data chunk types - fragment sequel
#define IDNVAL_CNKTYPE_LPGRF_FRAME_SEQUEL   0xC0        // Sample data array (sequel fragment)

// Channel configuration: Flags
#define IDNMSK_CHNCFG_DATA_MATCH            0x30        // Data/Configuration crosscheck
#define IDNFLG_CHNCFG_ROUTING               0x01        // Verify/Route/Open channel before message processing
#define IDNFLG_CHNCFG_CLOSE                 0x02        // Close channel after message processing

// Channel configuration: Service modes; Note: Must be unique! Used to map "any service" routings
#define IDNVAL_SMOD_VOID                    0x00        // No function, no lookup
#define IDNVAL_SMOD_LPGRF_CONTINUOUS        0x01        // Laser graphic: Stream of waveform segments
#define IDNVAL_SMOD_LPGRF_DISCRETE          0x02        // Laser graphic: Stream of individual frames
#define IDNVAL_SMOD_LPEFX_CONTINUOUS        0x03        // Transparent, octet segments only (includes start code)
#define IDNVAL_SMOD_LPEFX_DISCRETE          0x04        // Buffered, frames of effect data, may mix with strings
#define IDNVAL_SMOD_DMX512_CONTINUOUS       0x05        // Transparent, octet segments only (includes start code)
#define IDNVAL_SMOD_DMX512_DISCRETE         0x06        // Buffered, frames of effect data, may mix with strings

// Chunk header flags
#define IDNMSK_CNKHDR_CONFIG_MATCH          0x30        // Data/Configuration crosscheck
#define IDNFLG_OCTET_SEGMENT_DELIMITER      0x01        // Segment contains octet sequence delimiter
#define IDNFLG_GRAPHIC_FRAME_ONCE           0x01        // Frame is only scanned once

// ----------------------------------------------------------------------------

#define IDNVAL_CHANNEL_COUNT                64


// -------------------------------------------------------------------------------------------------
//  Typedefs
// -------------------------------------------------------------------------------------------------

typedef struct
{
    uint16_t totalSize;
    uint16_t contentID;
    uint32_t timestamp;
    
} IDNHDR_CHANNEL_MESSAGE;


typedef struct
{
    uint8_t wordCount;
    uint8_t flags;                              // Upper 4 bit decoder flags (0x30: Match), lower config
    uint8_t serviceID;
    uint8_t serviceMode;
    
} IDNHDR_CHANNEL_CONFIG;


// --------------------------------------------------------
//  Data chunks
// --------------------------------------------------------

typedef struct _IDNHDR_SAMPLE_CHUNK
{
    uint32_t flagsDuration;                     // Flags: 0x30: Match
    
} IDNHDR_SAMPLE_CHUNK;


typedef struct _IDNHDR_OCTET_SEGMENT
{
    uint8_t flags;
    uint8_t sequence;
    uint16_t offset;
    
} IDNHDR_OCTET_SEGMENT;


typedef struct _IDNHDR_OCTET_STRING
{
    uint8_t flags;
    uint8_t reserved1;
    uint16_t reserved2;
    
} IDNHDR_OCTET_STRING;


typedef struct _IDNHDR_DIMMER_LEVELS
{
    uint8_t flags;
    uint8_t reserved1;
    uint16_t reserved2;
    
} IDNHDR_DIMMER_LEVELS;


#endif

