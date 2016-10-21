#  ----------------------------------------------------------------------------
#          SAM Software Package License
#  ----------------------------------------------------------------------------
#  Copyright (c) 2013, Atmel Corporation
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
# List of target supported by SAM-BA software
# Board folder MUST have the same name as the board

array set boards {
    "rf231usb-rd"       "rf231usb-rd/rf231usb-rd.tcl"
    "at91sam4s2-ek"     "at91sam4s2-ek/at91sam4s2-ek.tcl"
}

#
 # Add user board here, for example add 
 # "devicename-userboard" "devicename-userboard/devicename-userboard.tcl"
 # Note2: devicename should also add with chip id in devices list in devices/devices.tcl
 # Please see user guide to get more information.

 array set user_boards {
}

#example Add:
# "test-stk"      "test-stk/test-stk.tcl"
