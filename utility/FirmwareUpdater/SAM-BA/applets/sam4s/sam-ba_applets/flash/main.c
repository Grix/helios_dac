/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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

/** \page flash_applet Flash Applet
 * Flash applet is a small piece of software running on the target board, embedding the
 * flash read, write, and erase algorithms etc. \n
 *
 * SAM-BA host controls commands and data transfering, it loads flash applet and
 * executes it to implement flash memory operation.
 * An applet consists of:
 * <ul>
 * <li>A mailbox which can share information between the applet and SAM-BA host.</li>
 * <li>Implement APPLET_CMD_INIT command to initializes EEFC and reports memory size,
 * number of lock region, lock region size and buffer size through the mailbox.</li>
 * <li>A flash programming algorithm works for APPLET_CMD_WRITE command, it erases and programs
 * flash data in buffer at the address which specified in mailbox.</li>
 * <li>Erase all algorithm is necessary to erasing entire flash memory. </li>
 * <li>Some other commands such as APPLET_CMD_LOCK, APPLET_CMD_UNLOCK and APPLET_CMD_GPNVM
 * all has its process entry to implement.</li>
 * </ul>
 *
 * It reports command status and written/read size (for write/read algorithm) in mailbox to
 * SAM-BA host while the command is achieved.
 *
 * For more accurate information, please look at the \ref flashd_module and \ref efc_module.
 *
 * Related files :\n
 * \ref main.c\n
 * \ref efc.c\n
 * \ref efc.h.\n
 * \ref flashd.c\n
 * \ref flashd.h.\n
*/
/*@{*/
/*@}*/


/**
 * \file
 *
 * Implementation of flash applet for ISP.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "../common/applet.h"
#include "board.h"

#include <string.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/
/** stack size for flash applet */
#define STACK_SIZE (0x400)
#define SECTOR_SIZE (128 * IFLASH_PAGE_SIZE)
/*----------------------------------------------------------------------------
 *        Local structures
 *----------------------------------------------------------------------------*/

/** \brief Structure for storing parameters for each command that can be
 *   performed by the applet. */
struct _Mailbox {

    /** Command send to the monitor to be executed. */
    uint32_t command;
    /** Returned status, updated at the end of the monitor execution.*/
    uint32_t status;

    /** Input Arguments in the argument area. */
    union {

        /** Input arguments for the Init command.*/
        struct {

            /** Communication link used.*/
            uint32_t comType;
            /** Trace level.*/
            uint32_t traceLevel;
            /** Memory Bank to write in.*/
            uint32_t bank;

        } inputInit;

        /** Output arguments for the Init command.*/
        struct {

            /** Memory size.*/
            uint32_t memorySize;
            /** Buffer address.*/
            uint32_t bufferAddress;
            /** Buffer size.*/
            uint32_t bufferSize;
            struct {
                /** Lock region size in byte.*/
                uint16_t lockRegionSize;
                /** Number of Lock Bits.*/
                uint16_t numbersLockBits;
            } memoryInfo;
        } outputInit;

        /** Input arguments for the Write command.*/
        struct {

            /** Buffer address.*/
            uint32_t bufferAddr;
            /** Buffer size.*/
            uint32_t bufferSize;
            /** Memory offset.*/
            uint32_t memoryOffset;

        } inputWrite;

        /** Output arguments for the Write command.*/
        struct {

            /** Bytes written.*/
            uint32_t bytesWritten;
        } outputWrite;

        /** Input arguments for the Read command.*/
        struct {

            /** Buffer address.*/
            uint32_t bufferAddr;
            /** Buffer size.*/
            uint32_t bufferSize;
            /** Memory offset.*/
            uint32_t memoryOffset;

        } inputRead;

        /** Output arguments for the Read command.*/
        struct {

            /** Bytes read.*/
            uint32_t bytesRead;

        } outputRead;

        /** Input arguments for the Full Erase command.*/
        /** NONE*/

         /** Input arguments for the Lock page command.*/
        struct {

            /** Sector number to be lock.*/
            uint32_t sector;

        } inputLock;

        /** Output arguments for the Lock  page command.*/
        /** NONE*/

        /*/ Input arguments for the Unlock  page command.*/
        struct {

            /** Sector number to be unlock.*/
            uint32_t sector;

        } inputUnlock;

        /** Output arguments for the Unlock  page command.*/
        /** NONE*/

         /** Input arguments for the set/clear GPNVM bits command.*/
        struct {

            /** Activates or Deactivates*/
            uint32_t action;
            /** NVM bit to set/clear*/
            uint32_t bitsOfNVM;

        } inputGPNVM;

        /** Output arguments for the set/clear GPNVM bits command.*/
        /** NONE*/

        /** Input arguments for the set secuity bit command.*/
        /** NONE*/

        /** Output arguments for the set secuity bit command.*/
        /** NONE*/

        /** Input arguments for the Read Unique ID command.*/
        struct {

            /** Buffer address.*/
            uint32_t bufferAddr;
        } inputReadUniqueID;

        /** Output arguments for the Read Unique ID command.*/
        /** NONE*/

    } argument;
};

#if defined(EFC) && !defined(EFC0)
    #define EFC0     EFC
#endif

/*----------------------------------------------------------------------------
 *        Global variables
 *----------------------------------------------------------------------------*/
/** End of program space (code + data).*/
extern uint32_t end;

/** Size of the buffer used for read/write operations in bytes.*/
static uint32_t bufferSize;
/** Communication type with SAM-BA GUI.*/
static uint32_t comType;

/** Flash base address*/
static uint32_t flashBaseAddr;
/** Flash base address at applet init*/
static uint32_t flashBaseAddrInit;
/** Flash size*/
static uint32_t flashSize;
/** Flash page size*/
static uint32_t flashPageSize;
/** Flash nb of lock bits*/
static uint32_t flashNbLockBits;
/** Flash lock region size*/
static uint32_t flashLockRegionSize;
/* Address in sector which has been written */
static uint32_t lastWrittenAddr = 0;
/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/
/**
 * \brief  Applet main entry. This function decodes received command and executes it.
 *
 * \param argc  always 1
 * \param argv  Address of the argument area..
 */
int main(int argc, char **argv)
{
    struct _Mailbox *pMailbox = (struct _Mailbox *) argv;

    uint32_t bytesToWrite, bufferAddr, memoryOffset;
    uint32_t l_start, l_end;
    uint32_t *pActualStart = NULL;
    uint32_t *pActualEnd = NULL;
    uint8_t error ;
    uint32_t writeSize;
    /* Save info of communication link */
    comType = pMailbox->argument.inputInit.comType;

    /*----------------------------------------------------------
     * INIT:
     *----------------------------------------------------------*/
    if (pMailbox->command == APPLET_CMD_INIT) {
        /*  Re-configurate UART   (MCK maybe change in LowLevelInit())  */
        UART_Configure(115200, BOARD_MCK);

        /* Set 6 WS for internal Flash writing (refer to errata) */
        EFC_SetWaitState(EFC0, 6);
#if defined (EFC1)
        EFC_SetWaitState(EFC1, 6);
#endif

#if (DYN_TRACES == 1)
        dwTraceLevel = pMailbox->argument.inputInit.traceLevel;
#endif

        flashBaseAddr       = IFLASH_ADDR;
        flashBaseAddrInit   = IFLASH_ADDR;
        flashSize           = IFLASH_SIZE;
        flashPageSize       = IFLASH_PAGE_SIZE;
        flashNbLockBits     = IFLASH_NB_OF_LOCK_BITS;
        flashLockRegionSize = IFLASH_LOCK_REGION_SIZE;

        TRACE_INFO("-- Internal Flash SAM-BA Applet %s --\n\r", SAM_BA_APPLETS_VERSION);
        TRACE_INFO("-- %s\n\r", BOARD_NAME);
        TRACE_INFO("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

        /* Initialize flash driver */
        FLASHD_Initialize(BOARD_MCK, 1);

        /* flash accesses must be 4 bytes aligned */
        pMailbox->argument.outputInit.bufferAddress = ((uint32_t) &end);

        bufferSize = IRAM_SIZE                            /* sram size */
                     - ( ((uint32_t) &end) - IRAM_ADDR )  /* program size (romcode, code+data) */
                     - STACK_SIZE;                         /* stack size at the end */
        /* integer number of pages can be contained in each buffer */
        /* operation is : buffersize -= bufferSize % flashPageSize */
        /* modulo can be done with a mask since flashpagesize is a power of two integer */
        bufferSize = bufferSize > SECTOR_SIZE ? SECTOR_SIZE: (bufferSize - (bufferSize%IFLASH_PAGE_SIZE));
        pMailbox->argument.outputInit.bufferSize = bufferSize;

        pMailbox->argument.outputInit.memorySize = flashSize;
        pMailbox->argument.outputInit.memoryInfo.lockRegionSize = flashLockRegionSize;
        pMailbox->argument.outputInit.memoryInfo.numbersLockBits = flashNbLockBits;

        TRACE_INFO("bufferSize : %d  bufferAddr: 0x%x \n\r",
               (int)pMailbox->argument.outputInit.bufferSize,
               (unsigned int) &end );

        TRACE_INFO("memorySize : %d lockRegionSize : 0x%x numbersLockBits : 0x%x \n\r",
               (int)pMailbox->argument.outputInit.memorySize,
               (unsigned int)pMailbox->argument.outputInit.memoryInfo.lockRegionSize,
               (unsigned int)pMailbox->argument.outputInit.memoryInfo.numbersLockBits);

        pMailbox->status = APPLET_SUCCESS;
    }

    /*----------------------------------------------------------
     * WRITE:
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_WRITE) {

        memoryOffset  = pMailbox->argument.inputWrite.memoryOffset;
        bufferAddr    = pMailbox->argument.inputWrite.bufferAddr;
        bytesToWrite  = pMailbox->argument.inputWrite.bufferSize;

        TRACE_INFO("WRITE at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes (flash base addr : 0x%x)\n\r",
                   (unsigned int)memoryOffset, (unsigned int)bufferAddr,
                   (unsigned int)bytesToWrite, (unsigned int)flashBaseAddr);

        /* Check the giving sector have been locked before. */
        if (FLASHD_IsLocked(flashBaseAddr + memoryOffset, flashBaseAddr + memoryOffset + bytesToWrite) != 0) {

            TRACE_INFO("Error page locked\n\r");
            pMailbox->argument.outputWrite.bytesWritten = 0;
            pMailbox->status = APPLET_PROTECT_FAIL;
            goto exit;
        }

        if (memoryOffset % SECTOR_SIZE) {
            writeSize = SECTOR_SIZE - memoryOffset % SECTOR_SIZE;
            writeSize = writeSize > bufferSize ? bufferSize : writeSize;
        } else {
            writeSize = bytesToWrite;
        }
        TRACE_INFO("Write <%x> bytes from <#%x> \n\r", (unsigned int )writeSize, (unsigned int )memoryOffset );
        
        l_start = memoryOffset / SECTOR_SIZE;
        if ((memoryOffset % SECTOR_SIZE == 0) || 
              ((memoryOffset % SECTOR_SIZE != 0) && ( memoryOffset != (lastWrittenAddr + 1)))) {
            TRACE_INFO("Erase sector <#%d> \n\r", (unsigned int )l_start );
            TRACE_INFO("Unlock from <#%x> to <#%x> for sector erasing \n\r", 
                (unsigned int )(l_start * SECTOR_SIZE), (unsigned int)((l_start + 1) * SECTOR_SIZE -1));
            FLASHD_Unlock(flashBaseAddr + l_start * SECTOR_SIZE, flashBaseAddr + (l_start + 1) * SECTOR_SIZE -1 , pActualStart, pActualEnd);
#if defined (EFC1)
            if (memoryOffset < SECTOR_SIZE) {
                FLASHD_EraseSector(IFLASH_ADDR);             /* Small sector 0: 8K */
                FLASHD_EraseSector(IFLASH_ADDR + 1024 * 8);  /* Small sector 1: 8K */
                FLASHD_EraseSector(IFLASH_ADDR + 1024 * 16); /* Large sector  : 48K */

            } else if ((memoryOffset >= IFLASH_SIZE / 2) && (memoryOffset < (IFLASH_SIZE / 2 + SECTOR_SIZE))) {
                FLASHD_EraseSector(IFLASH_ADDR + IFLASH_SIZE / 2); /* Small sector 0: 8K */
                FLASHD_EraseSector(IFLASH_ADDR + IFLASH_SIZE / 2 + 1024 * 8);  /* Small sector 1: 8K */
                FLASHD_EraseSector(IFLASH_ADDR + IFLASH_SIZE / 2 + 1024 * 16); /* Large sector  : 48K */
            } else {
                /* Common erase Other sectors */
                FLASHD_EraseSector(flashBaseAddr + memoryOffset);
            }
#else
            if (memoryOffset < SECTOR_SIZE) {
                FLASHD_EraseSector(IFLASH_ADDR);             /* Small sector 0: 8K */
                FLASHD_EraseSector(IFLASH_ADDR + 1024 * 8);  /* Small sector 1: 8K */
                FLASHD_EraseSector(IFLASH_ADDR + 1024 * 16); /* Large sector  : 48K */
            } else {
                /* Common erase Other sectors */
                FLASHD_EraseSector(flashBaseAddr + memoryOffset);
            }
#endif
        }
        /* Write data */
        if (FLASHD_Write(flashBaseAddr + memoryOffset, (const void *)bufferAddr, writeSize) != 0) {

            TRACE_INFO("Error write operation\n\r");
            pMailbox->argument.outputWrite.bytesWritten = writeSize ;
            pMailbox->status = APPLET_WRITE_FAIL;
            goto exit;
        }
        lastWrittenAddr = memoryOffset + writeSize - 1;
        TRACE_INFO("Write achieved\n\r");
        pMailbox->argument.outputWrite.bytesWritten = writeSize;
        pMailbox->status = APPLET_SUCCESS;
    }

    /*----------------------------------------------------------
     * READ:
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_READ) {

        memoryOffset = pMailbox->argument.inputRead.memoryOffset;
        bufferAddr   = pMailbox->argument.inputRead.bufferAddr;
        bufferSize   = pMailbox->argument.inputRead.bufferSize;
        TRACE_INFO("READ at offset: 0x%x buffer at : 0x%x of: 0x%x Bytes (flash base addr : 0x%x)\n\r",
                   (unsigned int)memoryOffset, (unsigned int)bufferAddr,
                   (unsigned int)bufferSize,
                   (unsigned int)flashBaseAddr);

        /* read data */
        memcpy((void *)bufferAddr, (void *)(flashBaseAddr + memoryOffset), bufferSize);
        /* workaound for sam4s-xpld */
        memcpy((void *)bufferAddr, (void *)(flashBaseAddr + memoryOffset), bufferSize);
        TRACE_INFO("Read achieved\n\r");
        pMailbox->argument.outputRead.bytesRead = bufferSize;
        pMailbox->status = APPLET_SUCCESS;
    }

    /*----------------------------------------------------------
     * FULL ERASE:
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_FULL_ERASE) {
        TRACE_INFO("FULL ERASE command \n\r");

        /* Check if at least one page has been locked */
        if (FLASHD_IsLocked(flashBaseAddr, flashBaseAddr + flashSize) != 0) {

            TRACE_INFO("Error page locked \n\r");
            pMailbox->status = APPLET_PROTECT_FAIL;
            goto exit;
        }
        /* Implement the erase all command */
        /* Erase the flash */
        if (FLASHD_Erase(flashBaseAddr) != 0) {

            TRACE_INFO("Flash erase failed! \n\r");
            pMailbox->status = APPLET_ERASE_FAIL;
            goto exit;
        }
#if defined (EFC1)
        /* Erase the flash1 */
        if (FLASHD_Erase(flashBaseAddr + flashSize / 2) != 0) {

            TRACE_INFO("Full erase failed! \n\r");
            pMailbox->status = APPLET_ERASE_FAIL;
            goto exit;
        }
#endif
        lastWrittenAddr = 0;
        TRACE_INFO("Full erase achieved\n\r");

        pMailbox->status = APPLET_SUCCESS;
    }
    /*----------------------------------------------------------
     * LOCK SECTOR:
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_LOCK) {
        TRACE_INFO("LOCK command \n\r");
        l_start = (pMailbox->argument.inputLock.sector * flashLockRegionSize) + flashBaseAddr;
        l_end = l_start + flashLockRegionSize;

        if( FLASHD_Lock(l_start, l_end, pActualStart, pActualEnd) != 0) {

            TRACE_INFO("Lock failed! \n\r");
            pMailbox->status = APPLET_PROTECT_FAIL;
            goto exit;
        }

        TRACE_INFO("Lock sector achieved\n\r");

        pMailbox->status = APPLET_SUCCESS;
    }

    /*----------------------------------------------------------
     * UNLOCK SECTOR:
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_UNLOCK) {
        TRACE_INFO("UNLOCK command \n\r");
        l_start = (pMailbox->argument.inputLock.sector * flashLockRegionSize) + flashBaseAddr;
        l_end = l_start + flashLockRegionSize;
        
        if( FLASHD_Unlock(l_start, l_end, pActualStart, pActualEnd) != 0) {

            TRACE_INFO("Unlock failed! \n\r");
            pMailbox->status = APPLET_UNPROTECT_FAIL;
            goto exit;
        }

        TRACE_INFO("Unlock sector achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }

    /*----------------------------------------------------------
     * GPNVM :
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_GPNVM) {
        if( pMailbox->argument.inputGPNVM.action == 0) {
            TRACE_INFO("DEACTIVATES GPNVM command \n\r");
            error = FLASHD_ClearGPNVM(pMailbox->argument.inputGPNVM.bitsOfNVM);
        }
        else {
            TRACE_INFO("ACTIVATES GPNVM command \n\r");
            error = FLASHD_SetGPNVM(pMailbox->argument.inputGPNVM.bitsOfNVM);
        }

        if(error != 0) {
            TRACE_INFO("GPNVM failed! \n\r");
            pMailbox->status = APPLET_FAIL;
            goto exit;
        }

        TRACE_INFO("GPNVM achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }

    /*----------------------------------------------------------
     * READ UNIQUE ID :
     *----------------------------------------------------------*/
    else if (pMailbox->command == APPLET_CMD_READ_UNIQUE_ID) {
        TRACE_INFO("READ UNIQUE ID command \n\r");

        if (FLASHD_ReadUniqueID ((uint32_t *)(pMailbox->argument.inputReadUniqueID.bufferAddr)) != 0) {
            TRACE_INFO("Read Unique ID failed! \n\r");
            pMailbox->status = APPLET_FAIL;
            goto exit;
        }

        TRACE_INFO("Read Unique ID achieved\n\r");
        pMailbox->status = APPLET_SUCCESS;
    }

exit:
    /* Acknowledge the end of command */
    TRACE_INFO("\tEnd of Applet %x %x.\n\r",
              (unsigned int)pMailbox->command,
              (unsigned int)pMailbox->status);
    /* Notify the host application of the end of the command processing */
    pMailbox->command = ~(pMailbox->command);

    if (comType == DBGU_COM_TYPE) {
        UART_PutChar(0x6);
    }

    return 0;
}

