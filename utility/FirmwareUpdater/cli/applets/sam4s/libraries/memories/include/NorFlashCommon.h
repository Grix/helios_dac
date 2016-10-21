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

/**
 * \file
 *
 * \section Purpose
 *
 * The Hardware Adaptation Layer manages the hardware functions of the %NORFLASH
 * %Flash. It implements a low level driver to manage the hardware functionality
 * of %NORFLASH.
 *
 * \section Usage
 *
 * -# WriteRawData() is used to write data to the %NorFlash device.
 * -# ReadRawData() is used to read data from the %NorFlash device.
 * -# The specified address for read/write opertion is an linear byte
 *    address of targer application byte address space represented by
 *    WORD((8-bit, 16-bit, 32-bit). The start (base) address of the
 *    flash memory in this address space is defined in board.h file
 *    as BOARD_NORFLASH_ADDR and users might need to change it.
 * -# WriteCommand() is used to write a command to specified command
 *    address.
 *
 * \section NorFlash_Error_Codes
 *
 * It provides detailed error codes to describe the various errors
 * that may occur during the operation. Some functions return an error
 * number directly as the function value. These functions return a value
 * of zero (NorCommon_ERROR_NONE) to indicate a success.
 */

#ifndef NORFLASHCOMMON_H
#define NORFLASHCOMMON_H

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** The function completed successfully. */
#define NorCommon_ERROR_NONE               0

/** Can not detect common flash infterface. */
#define NorCommon_ERROR_UNKNOWNMODEL       1

/** A read operation cannot be carried out. */
#define NorCommon_ERROR_CANNOTREAD         2

/** A write operation cannot be carried out. */
#define NorCommon_ERROR_CANNOTWRITE        3

/** A erase operation cannot be carried out. */
#define NorCommon_ERROR_CANNOTERASE        4

/** A locked operation cannot be carried out. */
#define NorCommon_ERROR_PROTECT            5

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern unsigned char WriteCommand(
    unsigned char portWidth,
    unsigned int commandAddress,
    unsigned int command);

extern void ReadRawData(
    unsigned char portWidth,
    unsigned int  dataAddress,
    unsigned char *buffer);

extern void WriteRawData(
    unsigned char portWidth,
    unsigned int  dataAddress,
    unsigned char *buffer);

#endif /* #ifndef NORFLASHCOMMON_H */
