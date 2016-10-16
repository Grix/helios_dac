#  ----------------------------------------------------------------------------
#          ATMEL Microcontroller Software Support
#  ----------------------------------------------------------------------------
#  Copyright (c) 2011, Atmel Corporation
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
set mainOsc(crystalList) [list \
    "11289000" \
    "12000000" \
    "16000000" \
    "18432000"]

set mainOsc(initOsc)  0
set mainOsc(initXal)  12000000

namespace eval LOWLEVEL {
    
    variable appletAddr          0x20000800
    variable appletMailboxAddr   0x20000840
    variable appletFileName      "$libPath(extLib)/$target(board)/applet-lowlevelinit-sam4s2.bin"

}

proc LOWLEVEL::Init {} {

    global mainOsc
    global commandLineMode
    global target
    
    switch $mainOsc(mode) {
        bypassMode {
            set mode 2
        }
    
        boardCrystalMode {
            set mode 1
        }
    
        default {
            set mode 0
        }
    }
    
    if {[catch {GENERIC::Init $LOWLEVEL::appletAddr $LOWLEVEL::appletMailboxAddr $LOWLEVEL::appletFileName [list $::target(comType) $::target(traceLevel) $mode $mainOsc(osc) $mainOsc(xal)]} dummy_err] } {
        set continue no
        if {$commandLineMode == 0} {
            set continue [tk_messageBox -title "Low level init" -message "Low level initialization failed.\nLow level initialization is required to run applets.\nContinue anyway ?" -icon warning -type yesno]
        } else {
            puts "-E- Error during Low level initialization."
            puts "-E- Low level initialization is required to run applets."
            puts "-E- Connection abort!"
        }
        # Close link
        if {$continue == no} {
            TCL_Close $target(handle)
            exit
        }
    } else {
        puts "-I- Low level initialized"
    }
}

