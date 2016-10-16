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

#ifndef MANAGEDNANDFLASH_H
#define MANAGEDNANDFLASH_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "NandCommon.h"
#include "EccNandFlash.h"

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

#define NandBlockStatus_DEFAULT         0xF
#define NandBlockStatus_FREE            0xE
#define NandBlockStatus_LIVE            0xC
#define NandBlockStatus_DIRTY           0x8
#define NandBlockStatus_BAD             0x0

/** Erase dirty blocks only*/
#define NandEraseDIRTY                  0
/** Erase all data, calculate count*/
#define NandEraseDATA                   1
/** Erase all, reset erase count */
#define NandEraseFULL                   2

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/
struct NandBlockStatus {

    uint32_t status:4,
             eraseCount:28;
};

struct ManagedNandFlash {

    struct EccNandFlash ecc;
    struct NandBlockStatus blockStatuses[NandCommon_MAXNUMBLOCKS];
    uint16_t baseBlock;
    uint16_t sizeInBlocks;
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern uint8_t ManagedNandFlash_Initialize(
    struct ManagedNandFlash *managed,
    const struct NandFlashModel *model,
    uint32_t commandAddress,
    uint32_t addressAddress,
    uint32_t dataAddress,
    const Pin pinChipEnable,
    const Pin pinReadyBusy,
    uint16_t baseBlock,
    uint16_t sizeInBlocks);

extern uint8_t ManagedNandFlash_AllocateBlock(
    struct ManagedNandFlash *managed,
    uint16_t block);

extern uint8_t ManagedNandFlash_ReleaseBlock(
    struct ManagedNandFlash *managed,
    uint16_t block);

extern uint8_t ManagedNandFlash_EraseBlock(
    struct ManagedNandFlash *managed,
    uint16_t block);

extern uint8_t ManagedNandFlash_ReadPage(
    const struct ManagedNandFlash *managed,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare);

extern uint8_t ManagedNandFlash_WritePage(
    const struct ManagedNandFlash *managed,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare);

extern uint8_t ManagedNandFlash_CopyPage(
    const struct ManagedNandFlash *managed,
    uint16_t sourceBlock,
    uint16_t sourcePage,
    uint16_t destBlock,
    uint16_t destPage);

extern uint8_t ManagedNandFlash_CopyBlock(
    const struct ManagedNandFlash *managed,
    uint16_t sourceBlock,
    uint16_t destBlock);

extern uint8_t ManagedNandFlash_EraseDirtyBlocks(
    struct ManagedNandFlash *managed);

extern uint8_t ManagedNandFlash_FindYoungestBlock(
    const struct ManagedNandFlash *managed,
    uint8_t status,
    uint16_t *block);

extern uint16_t ManagedNandFlash_CountBlocks(
    const struct ManagedNandFlash *managed,
    uint8_t status);

extern uint16_t ManagedNandFlash_GetDeviceSizeInBlocks(
    const struct ManagedNandFlash *managed);

extern uint8_t ManagedNandFlash_EraseAll(
    struct ManagedNandFlash *managed,
    uint8_t level);

#endif /*#ifndef MANAGEDNANDFLASH_H*/

