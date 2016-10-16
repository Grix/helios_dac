/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2009, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

#ifndef _NORFLASHCFI_
#define _NORFLASHCFI_

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

#define CFI_MAX_ERASE_REGION    4

/** Common flash interface query command. */
#define CFI_QUERY_COMMAND     0x98
#define CFI_QUERY_ADDRESS     0x55
#define CFI_QUERY_OFFSET      0x10

/** Vendor command set control interface ID code . */
#define CMD_SET_NULL          0x0000
#define CMD_SET_INTEL_EXT     0x0001
#define CMD_SET_AMD           0x0002
#define CMD_SET_INTEL         0x0003
#define CMD_SET_AMD_EXT       0x0004
#define CMD_SET_MISUBISHI     0x0100
#define CMD_SET_MISUBISHI_EXT 0x0101
#define CMD_SET_SST           0x0102

/** Indicates the maximum region for norflash device. */
#define NORFLASH_MAXNUMRIGONS 4
/** Indicates the NorFlash uses an 8-bit address bus. */
#define FLASH_CHIP_WIDTH_8BITS  0x01
/** Indicates the NorFlash uses an 16-bit address bus. */
#define FLASH_CHIP_WIDTH_16BITS 0x02
/** Indicates the NorFlash uses an 32-bit address bus. */
#define FLASH_CHIP_WIDTH_32BITS 0x04
/** Indicates the NorFlash uses an 64-bit address bus. */
#define FLASH_CHIP_WIDTH_64BITS 0x08

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** \brief Describes a Norflash CFI query system interface information. */
#ifdef __ICCARM__          /* IAR */
#pragma pack(1)            /* IAR */
#define __attribute__(...) /* IAR */
#endif                     /* IAR */

typedef struct _NorFlashCfiQueryInfo
{
    /** Query Unique String "QRY". */
    uint8_t queryUniqueString[3];
    /** Primary vendor command set and control interface ID . */
    uint16_t primaryCode;
    /** Address for primary extended query table. */
    uint16_t primaryAddr;
    /** Alternate vendor command set and control interface ID . */
    uint16_t alternateCode;
    /** Address for alternate extended query table. */
    uint16_t alternateAddr;
    /** Vcc logic supply minimum write/erase voltage. */
    uint8_t minVcc;
    /** Vcc logic supply maximum write/erase voltage. */
    uint8_t maxVcc;
    /** Vpp logic supply minimum write/erase voltage. */
    uint8_t minVpp;
    /** Vpp logic supply maximum write/erase voltage. */
    uint8_t maxVpp;
    /** Timeout per single write (2<<n) in microsecond. */
    uint8_t minTimeOutWrite;
    /** Timeout for minimum-size buffer write (2<<n) in microsecond. */
    uint8_t minTimeOutBuffer;
    /** Timeout for block erase (2<<n) in microsecond. */
    uint8_t minTimeOutBlockErase;
    /** Timeout for chip erase (2<<n) in microsecond. */
    uint8_t minTimeOutChipErase;
    /** Maximum timeout per write (2<<n) in microsecond. */
    uint8_t maxTimeOutWrite;
    /** Maximum timeout for buffer write (2<<n) in microsecond. */
    uint8_t maxTimeOutBuffer;
    /** Maximum timeout for block erase (2<<n) in microsecond. */
    uint8_t maxTimeOutBlockErase;
    /** Maximum timeout for chip erase (2<<n) in microsecond. */
    uint8_t maxTimeOutChipErase;
}  __attribute__ ((packed)) NorFlashCfiQueryInfo;

/** \brief Describes a Norflash CFI Erase block Region information. */
typedef struct _EraseRegionInfo
{
    /** Number of erase blocks within the region. */
    uint16_t Y;
    /** Size within the region. */
    uint16_t Z;
} __attribute__ ((packed)) EraseRegionInfo;

/**\brief Describes a Norflash CFI critical details of device geometry. */
typedef struct _NorFlashCfiDeviceGeometry
{
    /** Size of Device (2<<n) in number of bytes. */
    uint8_t deviceSize;
    /** Flash device interface description. */
    uint16_t deviceInterface;
    /** Maximum number of bytes in multi-byte write (2<<n). */
    uint16_t numMultiWrite;
    /** Number of erase block regions. */
    uint8_t numEraseRegion;
    /** Erase block Region information. */
    EraseRegionInfo eraseRegionInfo[16];
} __attribute__ ((packed)) NorFlashCfiDeviceGeometry;

#ifdef __ICCARM__          /* IAR */
#pragma pack()             /* IAR */
#endif                     /* IAR */

/** \brief Describes a Norflash Common Flash Interface information. */
typedef struct _NorFlashCFI
{
    /**CFI query system interface information. */
    NorFlashCfiQueryInfo norFlashCfiQueryInfo;
    /** CFI critical details of device geometry. */
    NorFlashCfiDeviceGeometry norFlashCfiDeviceGeometry;
} NorFlashCFI ;

/** \brief Describes a particular model of NandFlash device. */
typedef struct _NorFlashInfo
{
	/** Base address. */
    uint32_t baseAddress;
    /** Address bus using giving by CFI detection. */
    /** It can not retrieve info directly from  the NorFlashCFI, it depend on hardware connection. */
    uint8_t deviceChipWidth;
    /** Indicate the decive CFI is compatible */
    uint8_t cfiCompatible;
    /** Norflash Common Flash Interface information. */
    NorFlashCFI  cfiDescription;
} NorFlashInfo ;

///** Reset or exit CFI query mode function. */
//typedef void (*fReset) ( NorFlashInfo *, uint32_t ) ;
///** Write buffer to pNorFlash function. */
//typedef uint8_t (*fWriteData)( NorFlashInfo *, uint32_t , uint8_t *, uint32_t ) ;
///** Read manufactory function. */
//typedef uint32_t (*fReadManufactoryID)( NorFlashInfo * ) ;
///** Read device ID code function. */
//typedef uint32_t (*fReadDeviceID)( NorFlashInfo * ) ;
///** Full erase chip function. */
//typedef uint8_t (*fEraseChip) ( NorFlashInfo * ) ;
///** Erase single sector function. */
//typedef uint8_t (*fEraseSector)( NorFlashInfo *, uint32_t ) ;
//

typedef struct _NorFlashOperations
{
    /** Reset or exit CFI query mode function. */
    void (*_fReset)( NorFlashInfo *pNorFlashInfo, uint32_t address ) ;
    /** Write buffer to norflash function. */
    uint8_t (*_fWriteData)( NorFlashInfo *pNorFlashInfo, uint32_t address, uint8_t *buffer, uint32_t size ) ;
    /** Read manufactory function. */
    uint32_t  (*_fReadManufactoryID)( NorFlashInfo *pNorFlashInfo ) ;
    /** Read device ID code function. */
    uint32_t (*_fReadDeviceID)( NorFlashInfo *pNorFlashInfo ) ;
    /** Full erase chip function. */
    uint8_t (*_fEraseChip) ( NorFlashInfo *pNorFlashInfo ) ;
    /** Erase single sector function. */
    uint8_t (*_fEraseSector)( NorFlashInfo *pNorFlashInfo, uint32_t address ) ;
    /** Unlock single sector function. */	
    void (*_fUnlockSector)( NorFlashInfo *pNorFlashInfo, uint32_t address ) ;		
} NorFlashOperations ;

/** \brief Describes a particular model of NandFlash device. */
typedef struct _NorFlash
{
   const NorFlashOperations *pOperations;
   NorFlashInfo norFlashInfo;
} NorFlash ;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern uint8_t NorFlash_CFI_Detect( NorFlash *norFlash, uint8_t hardwareBusWidth ) ;

extern uint32_t NorFlash_GetDeviceNumOfBlocks( NorFlashInfo *pNorFlashInfo);

extern uint32_t NorFlash_GetDeviceMinBlockSize(NorFlashInfo *pNorFlashInfo);

extern uint32_t NorFlash_GetDeviceMaxBlockSize( NorFlashInfo *pNorFlashInfo ) ;

extern uint32_t NorFlash_GetDeviceBlockSize( NorFlashInfo *pNorFlashInfo, uint32_t sector ) ;

extern uint16_t NorFlash_GetDeviceSectorInRegion( NorFlashInfo *pNorFlashInfo, uint32_t memoryOffset ) ;

extern uint32_t NorFlash_GetDeviceSectorAddress( NorFlashInfo *pNorFlashInfo, uint32_t sector ) ;

extern uint32_t NorFlash_GetByteAddress( NorFlashInfo *pNorFlashInfo, uint32_t offset ) ;

extern uint32_t NorFlash_GetByteAddressInChip( NorFlashInfo *pNorFlashInfo, uint32_t offset ) ;

extern uint32_t NorFlash_GetAddressInChip( NorFlashInfo *pNorFlashInfo, uint32_t offset ) ;

extern uint8_t NorFlash_GetDataBusWidth( NorFlashInfo *pNorFlashInfo ) ;

extern uint32_t NorFlash_GetDeviceSizeInBytes( NorFlashInfo *pNorFlashInfo ) ;

#endif /* #ifndef _NORFLASHCFI_ */

