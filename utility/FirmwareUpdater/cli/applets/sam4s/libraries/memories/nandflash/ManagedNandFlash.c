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
 * The lower layer of nandflash block management, it is called by MappedNandFlash layer, and
 * it will call EccNandFlash layer.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "memories.h"

#include <string.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** Casts */
#define ECC(managed)    ((struct EccNandFlash *) managed)
#define RAW(managed)    ((struct RawNandFlash *) managed)
#define MODEL(managed)  ((struct NandFlashModel *) managed)

/** Values returned by the CheckBlock() function */
#define BADBLOCK        255
#define GOODBLOCK       254

/*----------------------------------------------------------------------------
 *        External Variables
 *----------------------------------------------------------------------------*/
/** Global nand flash temp buffer */
extern uint8_t gdwNandFlashTempBuffer[];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief  Check if the device is virgin.
 *
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \param spare    Pointer to allocated spare area (must be assigned)
 * \return 1 if a nandflash device is virgin (i.e. has never been used as a
 * managed nandflash); otherwise return 0.
 */
static uint8_t IsDeviceVirgin( const struct ManagedNandFlash *managed, uint8_t* spare )
{
    struct NandBlockStatus blockStatus;
    const struct NandSpareScheme *scheme =
                            NandFlashModel_GetScheme(MODEL(managed));
    uint16_t baseBlock = managed->baseBlock;
    uint8_t badBlockMarker;

    uint8_t error;

    assert( spare ) ; /* "ManagedNandFlash_IsDeviceVirgin: spare\n\r" */

    /* Read spare area of page #0. */
    error = RawNandFlash_ReadPage(RAW(managed), baseBlock, 0, 0, spare);
    assert( !error ) ; /* "ManagedNandFlash_IsDeviceVirgin: Failed to read page #0\n\r" */
#ifdef NDEBUG
    error = error; /* stop warnings */
#endif

    /* Retrieve bad block marker and block status from spare area*/
    NandSpareScheme_ReadBadBlockMarker(scheme, spare, &badBlockMarker);
    NandSpareScheme_ReadExtra(scheme, spare, &blockStatus, 4, 0);

    /* Check if block is marked as bad*/
    if ( badBlockMarker != 0xFF )
    {
        /* Device is not virgin, since page #0 is guaranteed to be good*/
        return 0 ;
    }
    /* If device is not virgin, then block status will be set to either
       FREE, DIRTY or LIVE */
    else
    {
        if ( blockStatus.status != NandBlockStatus_DEFAULT )
        {
            /* Device is not virgin */
            return 0 ;
        }
    }

    return 1 ;
}

/**
 * \brief  Check if the given block is bad.
 *
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \param block Raw block to check.
 * \param spare  Pointer to allocated spare area (must be assigned)
 * \return 1 if a nandflash device is virgin (i.e. has never been used as a
 * managed nandflash); otherwise return 0.
 */
static uint8_t CheckBlock( const struct ManagedNandFlash *managed, uint16_t block, uint8_t* spare )
{
    uint8_t error ;
    uint32_t i ;
    uint8_t pageSpareSize = NandFlashModel_GetPageSpareSize( MODEL( managed ) ) ;

    assert( spare != NULL ) ; /* "ManagedNandFlash_CheckBlock: spare\n\r" */

    /* Read spare area of first page of block */
    error = RawNandFlash_ReadPage( RAW( managed ), block, 0, 0, spare ) ;
    if ( error )
    {
        TRACE_ERROR( "CheckBlock: Cannot read page #0 of block #%d\n\r", block ) ;
        return error ;
    }

    /* Make sure it is all 0xFF */
    for ( i=0 ; i < pageSpareSize ; i++ )
    {
        if ( spare[i] != 0xFF )
        {
            return BADBLOCK ;
        }
    }

    /* Read spare area of second page of block */
    error = RawNandFlash_ReadPage( RAW( managed ), block, 1, 0, spare ) ;
    if ( error )
    {
        TRACE_ERROR( "CheckBlock: Cannot read page #1 of block #%d\n\r", block ) ;
        return error ;
    }

    /* Make sure it is all 0xFF */
    for ( i=0 ; i < pageSpareSize ; i++ )
    {
        if ( spare[i] != 0xFF )
        {
            return BADBLOCK ;
        }
    }

    return GOODBLOCK ;
}

/**
 * \brief  Physically writes the status of a block inside its first page spare area.
 *
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \param block Raw block to check.
 * \param pStatus  Pointer to status data.
 * \param spare  Pointer to allocated spare area (must be assigned)
 * \return 0 if successful; otherwise returns a NandCommon_ERROR_xx code.
 */
static uint8_t WriteBlockStatus( const struct ManagedNandFlash *managed, uint16_t block, struct NandBlockStatus *pStatus, uint8_t *spare )
{
    assert( spare != NULL ) ; /* "ManagedNandFlash_WriteBlockStatus: spare\n\r" */

    memset( spare, 0xFF, NandCommon_MAXPAGESPARESIZE ) ;
    NandSpareScheme_WriteExtra( NandFlashModel_GetScheme( MODEL( managed ) ), spare, pStatus, 4, 0 ) ;

    return RawNandFlash_WritePage( RAW( managed ), block, 0, 0, spare ) ;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief  Initializes a ManagedNandFlash instance. Scans the device to retrieve or
 * create block status information.
 *
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \param model  Pointer to the underlying nand chip model. Can be 0.
 * \param commandAddress  Address at which commands are sent.
 * \param addressAddress  Address at which addresses are sent.
 * \param dataAddress  Address at which data is sent.
 * \param pinChipEnable  Pin controlling the CE signal of the NandFlash.
 * \param pinReadyBusy  Pin used to monitor the ready/busy signal of the Nand.
 * \param baseBlock Base physical block address of managed area, managed 0.
 * \param sizeInBlocks Number of blocks that is managed.
 * \return 0 if the initialization is done; or returns a error code.
 */
uint8_t ManagedNandFlash_Initialize(
    struct ManagedNandFlash *managed,
    const struct NandFlashModel *model,
    uint32_t commandAddress,
    uint32_t addressAddress,
    uint32_t dataAddress,
    const Pin pinChipEnable,
    const Pin pinReadyBusy,
    uint16_t baseBlock,
    uint16_t sizeInBlocks)
{
    uint8_t error;
    uint8_t spare[NandCommon_MAXPAGESPARESIZE];
    uint16_t numBlocks;
    //uint32_t pageSpareSize;
    const struct NandSpareScheme *scheme;
    uint32_t block, phyBlock;
    struct NandBlockStatus blockStatus;
    uint8_t badBlockMarker;
    uint32_t eraseCount, minEraseCount, maxEraseCount;

    TRACE_DEBUG("ManagedNandFlash_Initialize()\n\r");

    /* Initialize EccNandFlash */
    error = EccNandFlash_Initialize(ECC(managed),
                                    model,
                                    commandAddress,
                                    addressAddress,
                                    dataAddress,
                                    pinChipEnable,
                                    pinReadyBusy);
    if (error) {

        return error;
    }

    /* Retrieve model information */
    numBlocks = NandFlashModel_GetDeviceSizeInBlocks(MODEL(managed));
    //pageSpareSize = NandFlashModel_GetPageSpareSize(MODEL(managed));
    scheme = NandFlashModel_GetScheme(MODEL(managed));

    /* Initialize base & size */
    if (sizeInBlocks == 0) sizeInBlocks = numBlocks;
    if (baseBlock > numBlocks) {
        baseBlock = 0;
    }
    else if (baseBlock + sizeInBlocks > numBlocks) {
        sizeInBlocks = numBlocks - baseBlock;
    }
    TRACE_INFO("Managed NF area: %d + %d\n\r", baseBlock, sizeInBlocks);

    if (sizeInBlocks > NandCommon_MAXNUMBLOCKS) {
        TRACE_ERROR("Out of Maxmized Managed Size: %d > %d\n\r",
                    sizeInBlocks, NandCommon_MAXNUMBLOCKS);
        TRACE_INFO("Change NandCommon_MAXNUMBLOCKS or sizeInBlocks\n\r");
        return NandCommon_ERROR_OUTOFBOUNDS;
    }

    managed->baseBlock = baseBlock;
    managed->sizeInBlocks = sizeInBlocks;

    /* Initialize block statuses */
    /* First, check if device is virgin*/
    if (IsDeviceVirgin(managed, spare)) {

        TRACE_WARNING("Device is virgin, doing initial block scanning ...\n\r");

        /* Perform initial scan of the device area */
        for (block=0; block < sizeInBlocks; block++) {

            phyBlock = baseBlock + block;

            /* Check if physical block is bad */
            error = CheckBlock(managed, phyBlock, spare);
            if (error == BADBLOCK) {

                /* Mark block as bad */
                TRACE_DEBUG("Block #%d is bad\n\r", block);
                managed->blockStatuses[block].status = NandBlockStatus_BAD;
            }
            else if (error == GOODBLOCK) {

                /* Mark block as free with erase count 0 */
                TRACE_DEBUG("Block #%d is free\n\r", block);
                managed->blockStatuses[block].status = NandBlockStatus_FREE;
                managed->blockStatuses[block].eraseCount = 0;

                /* Write status in spare of block first page */
                error = WriteBlockStatus(managed,
                                         phyBlock,
                                         &(managed->blockStatuses[block]),
                                         spare);
                if (error) {

                    TRACE_ERROR("ManagedNandFlash_Initialize: WR spare\n\r");
                    return error;
                }
            }
            else {

                TRACE_ERROR("ManagedNandFlash_Initialize: Scan device\n\r");
                return error;
            }
        }
    }
    else {

        TRACE_INFO("Managed, retrieving information ...\n\r");

        /* Retrieve block statuses from their first page spare area
          (find maximum and minimum wear at the same time) */
        minEraseCount = 0xFFFFFFFF;
        maxEraseCount = 0;
        for ( block=0 ; block < sizeInBlocks; block++ )
        {
            phyBlock = baseBlock + block;

            /* Read spare of first page */
            error = RawNandFlash_ReadPage(RAW(managed), phyBlock, 0, 0, spare);
            if ( error )
            {

                TRACE_ERROR("ManagedNandFlash_Initialize: Read block #%d(%d)\n\r",
                            (int)block, (int)phyBlock);
            }

            /* Retrieve bad block marker and block status */
            NandSpareScheme_ReadBadBlockMarker(scheme, spare, &badBlockMarker);
            NandSpareScheme_ReadExtra(scheme, spare, &blockStatus, 4, 0);

            /* If they do not match, block must be bad */
            if ( (badBlockMarker != 0xFF) && (blockStatus.status != NandBlockStatus_BAD) )
            {
                TRACE_DEBUG("Block #%d(%d) is bad\n\r", block, phyBlock);
                managed->blockStatuses[block].status = NandBlockStatus_BAD;
            }
            /* Check that block status is not default (meaning block is not managed) */
            else
            {
                if ( blockStatus.status == NandBlockStatus_DEFAULT )
                {
                    assert( 0 ) ; /* "Block #%d(%d) is not managed\n\r", block, phyBlock */
                }
                /* Otherwise block status is accurate */
                else
                {
                    TRACE_DEBUG("Block #%03d(%d) : status = %2d | eraseCount = %d\n\r",
                                block, phyBlock,
                                blockStatus.status, blockStatus.eraseCount);
                    managed->blockStatuses[block] = blockStatus;

                    /* Check for min/max erase counts */
                    if ( blockStatus.eraseCount < minEraseCount )
                    {
                        minEraseCount = blockStatus.eraseCount;
                    }
                    if ( blockStatus.eraseCount > maxEraseCount )
                    {
                        maxEraseCount = blockStatus.eraseCount;
                    }

                    /* Clean block*/
                    /*Release LIVE blocks */
                    /*
                    if (managed->blockStatuses[block].status == NandBlockStatus_LIVE) {

                        ManagedNandFlash_ReleaseBlock(managed, block);
                    }
                     Erase DIRTY blocks
                    if (managed->blockStatuses[block].status == NandBlockStatus_DIRTY) {

                        ManagedNandFlash_EraseBlock(managed, block);
                    }*/
                }
            }
        }

        /* Display erase count information*/
        TRACE_ERROR_WP("|--------|------------|--------|--------|--------|\n\r");
        TRACE_ERROR_WP("|  Wear  |   Count    |  Free  |  Live  | Dirty  |\n\r");
        TRACE_ERROR_WP("|--------|------------|--------|--------|--------|\n\r");

        for ( eraseCount=minEraseCount ; eraseCount <= maxEraseCount ; eraseCount++ )
        {
            uint32_t count = 0 ;
            uint32_t live = 0 ;
            uint32_t dirty = 0 ;
            uint32_t free = 0 ;

            for ( block=0 ; block < sizeInBlocks ; block++ )
            {
                if ( (managed->blockStatuses[block].eraseCount == eraseCount) && (managed->blockStatuses[block].status != NandBlockStatus_BAD) )
                {
                    count++ ;

                    switch ( managed->blockStatuses[block].status )
                    {
                        case NandBlockStatus_LIVE:
                            live++ ;
                        break ;

                        case NandBlockStatus_DIRTY:
                            dirty++ ;
                        break ;

                        case NandBlockStatus_FREE:
                            free++ ;
                        break ;
                    }
                }
            }

            if ( count > 0 )
            {
                TRACE_ERROR_WP( "|  %4d  |  %8d  |  %4d  |  %4d  |  %4d  |\n\r",
                          (int)eraseCount, (int)count, (int)free, (int)live, (int)dirty);
            }
        }
        TRACE_ERROR_WP("|--------|------------|--------|--------|--------|\n\r");
    }

    return 0;
}

/**
 * \brief  Allocates a FREE block of a managed nandflash and marks it as LIVE.
 * create block status information.
 *
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \param block    Block to allocate, in managed area.
 * \return 0 if successful; otherwise returns NandCommon_ERROR_WRONGSTATUS if
 * the block is not FREE.
 */
uint8_t ManagedNandFlash_AllocateBlock(
    struct ManagedNandFlash *managed,
    uint16_t block)
{
    uint8_t spare[NandCommon_MAXPAGESPARESIZE];
    TRACE_INFO("ManagedNandFlash_AllocateBlock(%d)\n\r", block);

    /* Check that block is FREE*/
    if (managed->blockStatuses[block].status != NandBlockStatus_FREE) {

        TRACE_ERROR("ManagedNandFlash_AllocateBlock: Block must be FREE\n\r");
        return NandCommon_ERROR_WRONGSTATUS;
    }

    /* Change block status to LIVE*/
    managed->blockStatuses[block].status = NandBlockStatus_LIVE;
    return WriteBlockStatus(managed,
                            managed->baseBlock + block,
                            &(managed->blockStatuses[block]),
                            spare);
}

/**
 * \brief  Releases a LIVE block of a nandflash and marks it as DIRTY.
 * create block status information.
 *
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \param block    Block to release, based on managed area.
 * \return 0 if successful; otherwise returns NandCommon_ERROR_WRONGSTATUS if
 * the block is not LIVE, or a RawNandFlash_WritePage error.
 */
uint8_t ManagedNandFlash_ReleaseBlock(
    struct ManagedNandFlash *managed,
    uint16_t block)
{
    uint8_t spare[NandCommon_MAXPAGESPARESIZE];
    TRACE_INFO("ManagedNandFlash_ReleaseBlock(%d)\n\r", block);

    /* Check that block is LIVE*/
    if (managed->blockStatuses[block].status != NandBlockStatus_LIVE) {

        TRACE_ERROR("ManagedNandFlash_ReleaseBlock: Block must be LIVE\n\r");
        return NandCommon_ERROR_WRONGSTATUS;
    }

    /* Change block status to DIRTY*/
    managed->blockStatuses[block].status = NandBlockStatus_DIRTY;
    return WriteBlockStatus(managed,
                            managed->baseBlock + block,
                            &(managed->blockStatuses[block]),
                            spare);
}

/**
 * \brief Erases a DIRTY block of a managed NandFlash.
 * create block status information.
 *
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \param block  Block to erase, in managed area.
 * \return the RawNandFlash_EraseBlock code or NandCommon_ERROR_WRONGSTATUS.
 */
uint8_t ManagedNandFlash_EraseBlock(
    struct ManagedNandFlash *managed,
    uint16_t block)
{
    uint32_t phyBlock = managed->baseBlock + block;
    uint8_t spare[NandCommon_MAXPAGESPARESIZE];
    uint8_t error;
    TRACE_INFO("ManagedNandFlash_EraseBlock(%d)\n\r", block);

    /* Check block status*/
    if (managed->blockStatuses[block].status != NandBlockStatus_DIRTY) {

        TRACE_ERROR("ManagedNandFlash_EraseBlock: Block must be DIRTY\n\r");
        return NandCommon_ERROR_WRONGSTATUS;
    }

    /* Erase block*/
    error = RawNandFlash_EraseBlock(RAW(managed), phyBlock);
    if (error) {

        return error;
    }

    /* Update block status*/
    managed->blockStatuses[block].status = NandBlockStatus_FREE;
    managed->blockStatuses[block].eraseCount++;
    return WriteBlockStatus(managed,
                            phyBlock,
                            &(managed->blockStatuses[block]),
                            spare);
}

/**
 * \brief  Reads the data and/or the spare area of a page on a managed nandflash. If
 * the data pointer is not 0, then the block MUST be LIVE.
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \param block  Number of block to read from.
 * \param page  Number of page to read inside given block.
 * \param data  Data area buffer, can be 0.
 * \param spare  Spare area buffer, can be 0.
 * \return NandCommon_ERROR_WRONGSTATUS if the block is not LIVE and the data
 * pointer is not null; Otherwise, returns EccNandFlash_ReadPage().
 */
uint8_t ManagedNandFlash_ReadPage(
    const struct ManagedNandFlash *managed,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    /* Check that the block is LIVE if data is requested*/
    if ((managed->blockStatuses[block].status != NandBlockStatus_LIVE)
        && (managed->blockStatuses[block].status != NandBlockStatus_DIRTY)) {

        TRACE_ERROR("ManagedNandFlash_ReadPage: Block must be LIVE or DIRTY.\n\r");
        return NandCommon_ERROR_WRONGSTATUS;
    }

    /* Read data with ECC verification*/
    return EccNandFlash_ReadPage(ECC(managed),
                                 managed->baseBlock + block,
                                 page, data, spare);
}

/**
 * \brief  Writes the data and/or spare area of a LIVE page on a managed NandFlash.
 * ECC for the data area and storing it in the spare. If no data buffer is
 * provided, the ECC is read from the existing page spare. If no spare buffer
 * is provided, the spare area is still written with the ECC information
 * calculated on the data buffer.
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \param block  Number of block to read from.
 * \param page  Number of page to read inside given block.
 * \param data  Data area buffer.
 * \param spare  Spare area buffer.
 * \return NandCommon_ERROR_WRONGSTATUS if the page is not LIVE; otherwise,
 * returns EccNandFlash_WritePage().
 */
uint8_t ManagedNandFlash_WritePage(
    const struct ManagedNandFlash *managed,
    uint16_t block,
    uint16_t page,
    void *data,
    void *spare)
{
    /* Check that the block is LIVE*/
    if (managed->blockStatuses[block].status != NandBlockStatus_LIVE) {

        TRACE_ERROR("ManagedNandFlash_WritePage: Block must be LIVE.\n\r");
        return NandCommon_ERROR_WRONGSTATUS;
    }

    /* Write data with ECC calculation*/
    return EccNandFlash_WritePage(ECC(managed),
                                  managed->baseBlock + block,
                                  page, data, spare);
}

/**
 * \brief Copy the data & spare area of one page to another page. The source block
 * can be either LIVE or DIRTY, and the destination block must be LIVE; they
 * must both have the same parity.
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \param sourceBlock  Source block number based on managed area.
 * \param sourcePage  Number of source page inside the source block.
 * \param destBlock  Destination block number based on managed area.
 * \param destPage  Number of destination page inside the dest block.
 * \return 0 if successful; NandCommon_ERROR_WRONGSTATUS if one or more page
 * is not live; otherwise returns an NandCommon_ERROR_xxx code.
 */
uint8_t ManagedNandFlash_CopyPage(
    const struct ManagedNandFlash *managed,
    uint16_t sourceBlock,
    uint16_t sourcePage,
    uint16_t destBlock,
    uint16_t destPage)
{
    uint8_t error;

    assert( (sourcePage & 1) == (destPage & 1) ) ; /* "ManagedNandFlash_CopyPage: source & dest pages must have the same parity\n\r" */

    TRACE_INFO("ManagedNandFlash_CopyPage(B#%d:P#%d -> B#%d:P#%d)\n\r",
              sourceBlock, sourcePage, destBlock, destPage);

    /* Check block statuses */
    if ((managed->blockStatuses[sourceBlock].status != NandBlockStatus_LIVE)
         && (managed->blockStatuses[sourceBlock].status != NandBlockStatus_DIRTY)) {

        TRACE_ERROR("ManagedNandFlash_CopyPage: Source block must be LIVE or DIRTY.\n\r");
        return NandCommon_ERROR_WRONGSTATUS;
    }
    if (managed->blockStatuses[destBlock].status != NandBlockStatus_LIVE) {

        TRACE_ERROR("ManagedNandFlash_CopyPage: Destination block must be LIVE.\n\r");
        return NandCommon_ERROR_WRONGSTATUS;
    }

    /* If destination page is page #0, block status information must not be
      overwritten*/
    if (destPage == 0) {

//        uint8_t data[NandCommon_MAXPAGEDATASIZE];
        uint8_t spare[NandCommon_MAXPAGESPARESIZE];

        /* Read data & spare to copy*/
        error = EccNandFlash_ReadPage(ECC(managed),
                                      managed->baseBlock + sourceBlock,
                                      sourcePage,
                                      gdwNandFlashTempBuffer, spare);
        if (error) {

            return error;
        }

        /* Write destination block status information in spare*/
        NandSpareScheme_WriteExtra(NandFlashModel_GetScheme(MODEL(managed)),
                                   spare,
                                   &(managed->blockStatuses[destBlock]),
                                   4,
                                   0);

        /* Write page*/
        error = RawNandFlash_WritePage(RAW(managed),
                                       managed->baseBlock + destBlock,
                                       destPage,
                                       gdwNandFlashTempBuffer, spare);
        if (error) {

            return error;
        }
    }
    /* Otherwise, a normal copy can be done*/
    else {

        return RawNandFlash_CopyPage(RAW(managed),
                                     managed->baseBlock + sourceBlock,
                                     sourcePage,
                                     managed->baseBlock + destBlock,
                                     destPage);
    }

    return 0;
}

/**
 * \brief Copies the data from a whole block to another block on a nandflash. Both
 *  blocks must be LIVE.
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \param sourceBlock  Source block number.
 * \param destBlock  Destination block number.
 * \return 0 if successful; NandCommon_ERROR_WRONGSTATUS if one or more page
 * is not live; otherwise returns an NandCommon_ERROR_xxx code.
 */
uint8_t ManagedNandFlash_CopyBlock(
    const struct ManagedNandFlash *managed,
    uint16_t sourceBlock,
    uint16_t destBlock)
{
    uint16_t numPages = NandFlashModel_GetBlockSizeInPages(MODEL(managed));
    uint8_t error;
    uint16_t page;

    assert( sourceBlock != destBlock ) ; /* "ManagedNandFlash_CopyBlock: Source block must be different from dest. block\n\r" */

    TRACE_INFO( "ManagedNandFlash_CopyBlock(B#%d->B#%d)\n\r", sourceBlock, destBlock ) ;

    /* Copy all pages*/
    for ( page=0 ; page < numPages ; page++ )
    {
        error = ManagedNandFlash_CopyPage( managed, sourceBlock, page, destBlock, page ) ;
        if ( error )
        {
            TRACE_ERROR( "ManagedNandFlash_CopyPage: Failed to copy page %d\n\r", page ) ;

            return error ;
        }
    }

    return 0;
}

/**
 * \brief Erases all the blocks which are currently marked as DIRTY.
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \return 0 if successful; otherwise, returns a NandCommon_ERROR code.
 * is not live; otherwise returns an NandCommon_ERROR_xxx code.
 */
uint8_t ManagedNandFlash_EraseDirtyBlocks( struct ManagedNandFlash *managed )
{
    uint32_t i ;
    uint8_t error ;

    /* Erase all dirty blocks*/
    for ( i=0 ; i < managed->sizeInBlocks ; i++ )
    {
        if ( managed->blockStatuses[i].status == NandBlockStatus_DIRTY )
        {
            error = ManagedNandFlash_EraseBlock( managed, i ) ;

            if ( error )
            {
                return error ;
            }
        }
    }

    return 0 ;
}

/**
 * \brief Looks for the youngest block having the desired status among the blocks
 * of a managed nandflash. If a block is found, its index is stored inside
 * the provided variable (if pointer is not 0).
 *
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \param block  Pointer to the block number variable, based on managed area.
 * \return 0 if a block has been found; otherwise returns either status.
 */
uint8_t ManagedNandFlash_FindYoungestBlock( const struct ManagedNandFlash *managed, uint8_t status, uint16_t *block )
{
    uint8_t found = 0;
    uint16_t bestBlock = 0;
    uint32_t i;

    /* Go through the block array*/
    for ( i=0 ; i < managed->sizeInBlocks ; i++ )
    {
        /* Check status*/
        if ( managed->blockStatuses[i].status == status )
        {
            /* If no block was found, i becomes the best block*/
            if ( !found )
            {
                found = 1;
                bestBlock = i;
            }
            /* Compare the erase counts otherwise*/
            else
            {
                if ( managed->blockStatuses[i].eraseCount < managed->blockStatuses[bestBlock].eraseCount )
                {
                    bestBlock = i;
                }
            }
        }
    }

    if ( found )
    {
        if ( block )
        {
            *block = bestBlock ;
        }
        return 0 ;
    }
    else
    {
        return NandCommon_ERROR_NOBLOCKFOUND ;
    }
}

/**
 * \brief Counts and returns the number of blocks having the given status in a
 * managed nandflash.
 *
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \param status  Desired block status.
 * \return the number of blocks.
 */
uint16_t ManagedNandFlash_CountBlocks(
    const struct ManagedNandFlash *managed,
    uint8_t status)
{
    uint32_t i;
    uint16_t count = 0;

    /* Examine each block*/
    for (i=0; i < managed->sizeInBlocks; i++) {

        if (managed->blockStatuses[i].status == status) {

            count++;
        }
    }

    return count;
}

/**
 * \brief Returns the number of available blocks in a managed nandflash.
 *
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \return the number of blocks.
 */
uint16_t ManagedNandFlash_GetDeviceSizeInBlocks(
    const struct ManagedNandFlash *managed)
{
    return managed->sizeInBlocks;
}


/**
 * \brief Erase all blocks in the managed area of nand flash.
 *
 * \param managed  Pointer to a ManagedNandFlash instance.
 * \param level    Erase level.
 * \return  the RawNandFlash_EraseBlock code or NandCommon_ERROR_WRONGSTATUS.
 */
uint8_t ManagedNandFlash_EraseAll(struct ManagedNandFlash *managed,
                                        uint8_t level)
{
    uint32_t i;
    uint8_t error = 0;

    if (level == NandEraseFULL) {
        for (i=0; i < managed->sizeInBlocks; i++) {
            error = RawNandFlash_EraseBlock(RAW(managed),
                                            managed->baseBlock + i);
            /* Reset block status*/
            managed->blockStatuses[i].eraseCount = 0;
            if (error) {
                TRACE_WARNING("Managed_FullErase: %d(%d)\n\r",
                              (int)i, (int)(managed->baseBlock + i));
                managed->blockStatuses[i].status     = NandBlockStatus_BAD;
                continue;
            }
            managed->blockStatuses[i].status     = NandBlockStatus_FREE;
        }
    }
    else if (level == NandEraseDATA) {
        for (i=0; i < managed->sizeInBlocks; i++) {
            error = ManagedNandFlash_EraseBlock(managed, i);
            if (error) {
                TRACE_WARNING("Managed_DataErase: %d(%d)\n\r",
                              (int)i, (int)(managed->baseBlock + i));
            }
        }
    }
    else {
        for (i=0; i < managed->sizeInBlocks; i++) {
            if (managed->blockStatuses[i].status == NandBlockStatus_DIRTY) {
                error = ManagedNandFlash_EraseBlock(managed, i);
                if (error) {
                    TRACE_WARNING("Managed_DirtyErase: %d(%d)\n\r",
                                  (int)i, (int)(managed->baseBlock + i));
                }
            }
        }
    }

    return error;
}
