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
 * The INTERL %norflash Low-level driver code implement procedures to program
 * basic operations described INTEL-specified command set flash devices.
 * The various commands recognized by the devices are listed in the Commands
 * Tables provided in the corresponding INTEL command set compatible flash
 * datasheets. All operation functions are blocked, they wait for the
 * completion of an operation by polling the status register.
 *
 * \section Usage
 * -# Flash program using INTEL_Write_Data().
 *    - The Program command is used to modify the data stored at the
 *      specified device address. Programming can only change bits
 *      from ¡®1¡¯ to ¡®0¡¯. It may be necessary to erase the block before
 *      programming to addresses within it. Programming modifies a single
 *      Word at a time using static function intel_Program(). Programming
 *      larger amounts of data must be done in one Word at a time by
 *      giving a Program command, waiting for the command to complete,
 *      giving the next Program command and so on.
 * -# erase a block within the flash using INTEL_EraseSector().
 *    - Flash erase is performed on a block basis. An entire block is
 *      erased each time an erase command sequence is given.
 * -# erase whole blocks within the flash using INTEL_EraseChip().
 * -# INTEL_Reset() function can be issued, between Bus Write cycles
 *    before the start of a program or erase operation, to return the
 *    device to read mode.
 * -# INTEL_ReadDeviceID() is used to retrieve information
 *    about the Flash Device type.
 * -# INTEL_ReadManufactoryId() is used to retrieve information
 *    about the Flash Device Manufactory ID.
 */

#ifndef _NORFLASH_INTEL_
#define _NORFLASH_INTEL_

#include "NorFlashApi.h"

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern void INTEL_Reset( NorFlashInfo *pNorFlashInfo, uint32_t address ) ;

extern uint32_t INTEL_ReadManufactoryId( NorFlashInfo *NorFlashInfo ) ;

extern uint32_t INTEL_ReadDeviceID( NorFlashInfo *pNorFlashInfo ) ;

extern uint8_t INTEL_EraseSector( NorFlashInfo *NorFlashInfo, uint32_t sectorAddr ) ;

extern uint8_t INTEL_EraseChip( NorFlashInfo *NorFlashInfo ) ;

extern uint8_t INTEL_Write_Data( NorFlashInfo *NorFlashInfo, uint32_t address, uint8_t *buffer, uint32_t size ) ;

extern const NorFlashOperations intelOperations ;

#endif /* #ifndef _NORFLASH_INTEL_ */

