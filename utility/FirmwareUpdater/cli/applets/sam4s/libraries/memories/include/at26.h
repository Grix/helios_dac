/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
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
//------------------------------------------------------------------------------
/// \unit
///
/// !Purpose
///
/// The AT26 serial firmware Dataflash driver is based on top of the
/// corresponding Spi driver. A Dataflash structure instance has to be
/// initialized using the DF_Init function. Then basic dataflash
/// operations can be launched using macros such as DF_continuous_read.
/// These macros invoke the DF_Command() function which invokes the
/// DPI low driver using the SPI_SendCommand() function.
/// Beware to compute the dataflash internal address, the dataflash sector
/// description must be known (DataflashDesc). Dataflash can be automatically
/// detected using the DF_Scan() function.
///
/// !Usage
///
/// -# Initializes an AT26 instance and configures SPI chip select pin
///    using AT26_Configure().
/// -# Detect DF and returns DF description corresponding to the device
///    connected using AT26_FindDevice().This function shall be called by
///    the application before AT26_SendCommand().
/// -# Sends a command to the DF through the SPI using AT26_SendCommand().
///    The command is identified by its command code and the number of
///    bytes to transfer.
///    -# Example code for sending command to write a page to DF.
/// \code
///    // Program page
///    error = AT26_SendCommand(pAt26, AT26_BYTE_PAGE_PROGRAM, 4,
///            pData, writeSize, address, 0, 0);
/// \endcode
///    -# Example code for sending command to read a page from DF.
///       If data needs to be received, then a data buffer must be
///       provided.
/// \code
///    // Start a read operation
///    error = AT26_SendCommand(pAt26, AT26_READ_ARRAY_LF,
///            4, pData, size, address, 0, 0);
/// \endcode
///    -# This function does not block; its optional callback will
///       be invoked when the transfer completes.
/// -# Check the AT26 driver is ready or not by polling AT26_IsBusy().
///
//------------------------------------------------------------------------------
#ifndef AT26_H
#define AT26_H

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

//#include "chip.h"

//------------------------------------------------------------------------------
//         Macros
//------------------------------------------------------------------------------

#define AT26_Size(pAt26)            ((pAt26)->pDesc->size)
#define AT26_PageSize(pAt26)        ((pAt26)->pDesc->pageSize)
#define AT26_BlockSize(pAt26)       ((pAt26)->pDesc->blockSize)
#define AT26_Name(pAt26)            ((pAt26)->pDesc->name)
#define AT26_PageNumber(pAt26)      (AT26_Size(pAt26) / AT26_PageSize(pAt26))
#define AT26_BlockNumber(pAt26)     (AT26_Size(pAt26) / AT26_BlockSize(pAt26))
#define AT26_PagePerBlock(pAt26)    (AT26_BlockSize(pAt26) / AT26_PageSize(pAt26))
#define AT26_BlockEraseCmd(pAt26)   ((pAt26)->pDesc->blockEraseCmd)

//------------------------------------------------------------------------------
//         Definitions
//------------------------------------------------------------------------------

/// Device is protected, operation cannot be carried out.
#define AT26_ERROR_PROTECTED        1
/// Device is busy executing a command.
#define AT26_ERROR_BUSY             2
/// There was a problem while trying to program page data.
#define AT26_ERROR_PROGRAM          3
/// There was an SPI communication error.
#define AT26_ERROR_SPI              4

/// Device ready/busy status bit.
#define AT26_STATUS_RDYBSY          (1 << 0)
/// Device is ready.
#define AT26_STATUS_RDYBSY_READY    (0 << 0)
/// Device is busy with internal operations.
#define AT26_STATUS_RDYBSY_BUSY     (1 << 0)
/// Write enable latch status bit.
#define AT26_STATUS_WEL             (1 << 1)
/// Device is not write enabled.
#define AT26_STATUS_WEL_DISABLED    (0 << 1)
/// Device is write enabled.
#define AT26_STATUS_WEL_ENABLED     (1 << 1)
/// Software protection status bitfield.
#define AT26_STATUS_SWP             (3 << 2)
/// All sectors are software protected.
#define AT26_STATUS_SWP_PROTALL     (3 << 2)
/// Some sectors are software protected.
#define AT26_STATUS_SWP_PROTSOME    (1 << 2)
/// No sector is software protected.
#define AT26_STATUS_SWP_PROTNONE    (0 << 2)
/// Write protect pin status bit.
#define AT26_STATUS_WPP             (1 << 4)
/// Write protect signal is not asserted.
#define AT26_STATUS_WPP_NOTASSERTED (0 << 4)
/// Write protect signal is asserted.
#define AT26_STATUS_WPP_ASSERTED    (1 << 4)
/// Erase/program error bit.
#define AT26_STATUS_EPE             (1 << 5)
/// Erase or program operation was successful.
#define AT26_STATUS_EPE_SUCCESS     (0 << 5)
/// Erase or program error detected.
#define AT26_STATUS_EPE_ERROR       (1 << 5)
/// Sector protection registers locked bit.
#define AT26_STATUS_SPRL            (1 << 7)
/// Sector protection registers are unlocked.
#define AT26_STATUS_SPRL_UNLOCKED   (0 << 7)
/// Sector protection registers are locked.
#define AT26_STATUS_SPRL_LOCKED     (1 << 7)

/// Read array command code.
#define AT26_READ_ARRAY             0x0B
/// Read array (low frequency) command code.
#define AT26_READ_ARRAY_LF          0x03
/// Block erase command code (4K block).
#define AT26_BLOCK_ERASE_4K         0x20
/// Block erase command code (32K block).
#define AT26_BLOCK_ERASE_32K        0x52
/// Block erase command code (64K block).
#define AT26_BLOCK_ERASE_64K        0xD8
/// Chip erase command code 1.
#define AT26_CHIP_ERASE_1           0x60
/// Chip erase command code 2.
#define AT26_CHIP_ERASE_2           0xC7
/// Byte/page program command code.
#define AT26_BYTE_PAGE_PROGRAM      0x02
/// Sequential program mode command code 1.
#define AT26_SEQUENTIAL_PROGRAM_1   0xAD
/// Sequential program mode command code 2.
#define AT26_SEQUENTIAL_PROGRAM_2   0xAF
/// Write enable command code.
#define AT26_WRITE_ENABLE           0x06
/// Write disable command code.
#define AT26_WRITE_DISABLE          0x04
/// Protect sector command code.
#define AT26_PROTECT_SECTOR         0x36
/// Unprotect sector command code.
#define AT26_UNPROTECT_SECTOR       0x39
/// Read sector protection registers command code.
#define AT26_READ_SECTOR_PROT       0x3C
/// Read status register command code.
#define AT26_READ_STATUS            0x05
/// Write status register command code.
#define AT26_WRITE_STATUS           0x01
/// Read manufacturer and device ID command code.
#define AT26_READ_JEDEC_ID          0x9F
/// Deep power-down command code.
#define AT26_DEEP_PDOWN             0xB9
/// Resume from deep power-down command code.
#define AT26_RES_DEEP_PDOWN         0xAB

//------------------------------------------------------------------------------
//         Types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Describes a serial firmware flash device parameters.
//------------------------------------------------------------------------------
typedef struct _At26Desc {

    /// Device string name.
    const char *name;
    /// JEDEC ID of device.
    unsigned int jedecId;
    /// Size of device in bytes.
	unsigned int size;
    /// Size of one page in bytes.
	unsigned int pageSize;
    /// Block erase size in bytes.
	unsigned int blockSize;
    /// Block erase command.
    unsigned int blockEraseCmd;

} At26Desc;

//------------------------------------------------------------------------------
/// Serial flash driver structure. Holds the current state of the driver,
/// including the current command and the descriptor for the underlying device.
//------------------------------------------------------------------------------
typedef struct _At26 {

    /// Pointer to the underlying SPI driver.
	Spid *pSpid;
    /// Current SPI command sent to the SPI driver.
	SpidCmd command;
    /// Pointer to a descriptor for the serial firmware flash device.
	const At26Desc *pDesc;
    /// Command buffer.
	unsigned int pCmdBuffer[2];

} At26;

//------------------------------------------------------------------------------
//         Exported functions
//------------------------------------------------------------------------------

extern void AT26_Configure(At26 *pAt26, Spid *pSpid, unsigned char cs);

extern unsigned char AT26_SendCommand(
	At26 *pAt26,
	unsigned char cmd,
	unsigned char cmdSize,
	unsigned char *pData,
	unsigned int dataSize,
	unsigned int address,
    SpidCallback callback,
	void *pArgument);

extern unsigned char AT26_IsBusy(At26 *pAt26);

extern const At26Desc * AT26_FindDevice(
    At26 *pAt26,
    unsigned int jedecId);

#endif //#ifndef AT26_H

