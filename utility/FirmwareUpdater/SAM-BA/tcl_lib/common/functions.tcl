#  ----------------------------------------------------------------------------
#          ATMEL Microcontroller Software Support
#  ----------------------------------------------------------------------------
#  Copyright (c) 2008, Atmel Corporation
#
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions are met:
#
#  - Redistributions of source code must retain the above copyright notice,
#  this list of conditions and the disclaimer below.
#
#  Atmel's name may not be used to endorse or promote products derived from
#  this software without specific prior written permission. 
#
#  DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
#  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
#  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
#  DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
#  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#  ----------------------------------------------------------------------------


################################################################################
## PROCEDURES FOR COMPATIBILITY WITH OLDER SAM-BA VERSIONS
################################################################################

# DataFlash
set DATAFLASH::MaxBootSize $BOARD::maxBootSize

proc DATAFLASH::SelectDataflash {Dataflash_CS} {
    
    switch $Dataflash_CS {
            "AT91C_SPI0_CS0"   { DATAFLASH::Init 0 }
            "AT91C_SPI0_CS1"   { DATAFLASH::Init 1 }
            default            { puts "-E- This Chip Select does not support Dataflash" }
    }    
}

proc DATAFLASH::SendBootFile {name} {
    GENERIC::SendBootFile $name
}

proc DATAFLASH::sendFile {name address} {
    GENERIC::SendFile $name $address
}

proc DATAFLASH::EraseAllDataFlash {} {
    DATAFLASH::EraseAll
}

# NandFlash
set NANDFLASH::MaxBootSize $BOARD::maxBootSize

proc NANDFLASH::sendBootFile {name} {
    GENERIC::SendBootFile $name
}

proc NANDFLASH::SetNandHeaderValue {args} {
    set ll [llength $args]
    if {$ll == 0} {
       catch [set result [NANDFLASH::NandHeaderValue]]
    }
    if {$ll == 1} {
       catch [set result [NANDFLASH::NandHeaderValue [lindex $args 0]]]
    }
    if {$ll == 2} {
       catch [set result [NANDFLASH::NandHeaderValue [lindex $args 0] [lindex $args 1]]]
    }
    return $result
}

proc NANDFLASH::SendBootFileCmd {name} {
    NANDFLASH::SendBootFilePmeccCmd $name
}

proc NANDFLASH::sendFile {name address} {
    GENERIC::SendFile $name $address
}

proc NANDFLASH::EraseAllNandFlash {} {
    GENERIC::EraseAll
}

proc NANDFLASH::EraseAll {{param 0}} {
     NANDFLASH::BatchEraseAll $param
}


# Flash
proc FLASH::ScriptEraseAllFlash {} {
    FLASH::EraseAll
}

################################################################################
## USER DEFINED PROCEDURES (Place below your own macros or stubs)
################################################################################
