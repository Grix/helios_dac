# ----------------------------------------------------------------------------
#          ATMEL Microcontroller Software Support  -  ROUSSET  -
# ----------------------------------------------------------------------------
#  DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
#  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
#  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
#  DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
#  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
#  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
#  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
#  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ----------------------------------------------------------------------------
# File Name           : AT91SAM3S4.tcl
# Object              : AT91SAM3S4 definitions
# Generated           : AT91 SW Application Group  09/30/2009 (16:16:09)
# 
# CVS Reference       : /AT91SAM3S4.pl/1.24/Wed Jul 29 14:55:43 2009//
# CVS Reference       : /ACC_SAM3S4.pl/1.3/Wed Feb 25 13:14:09 2009//
# CVS Reference       : /ADC_SAM3XE.pl/1.5/Tue Jan 27 10:29:26 2009//
# CVS Reference       : /CORTEX_M3_MPU.pl/1.3/Mon Sep 15 12:43:55 2008//
# CVS Reference       : /CORTEX_M3.pl/1.1/Mon Sep 15 15:22:06 2008//
# CVS Reference       : /CORTEX_M3_NVIC.pl/1.8/Wed Sep 30 14:11:09 2009//
# CVS Reference       : /DAC_SAM3S4.pl/1.2/Fri Mar 13 08:50:25 2009//
# CVS Reference       : /DBGU_SAM3UE256.pl/1.3/Wed Sep 30 14:11:10 2009//
# CVS Reference       : /EFC2_SAM3UE256.pl/1.3/Wed Sep 30 14:11:11 2009//
# CVS Reference       : /HCBDMA_sam3S4.pl/1.1/Fri Mar 13 09:02:46 2009//
# CVS Reference       : /HECC_6143A.pl/1.1/Wed Feb  9 17:16:57 2005//
# CVS Reference       : /HMATRIX2_SAM3UE256.pl/1.5/Wed Sep 30 14:11:13 2009//
# CVS Reference       : /SFR_SAM3S4.pl/1.3/Wed Jan 14 15:06:20 2009//
# CVS Reference       : /MCI_6101F.pl/1.3/Wed Sep 30 14:11:15 2009//
# CVS Reference       : /PDC_6074C.pl/1.2/Thu Feb  3 09:02:11 2005//
# CVS Reference       : /PIO3_SAM3S4.pl/1.1/Tue Feb 17 08:07:35 2009//
# CVS Reference       : /PITC_6079A.pl/1.2/Thu Nov  4 13:56:22 2004//
# CVS Reference       : /PMC_SAM3S4.pl/1.8/Fri Mar 13 08:49:01 2009//
# CVS Reference       : /PWM_SAM3S4.pl/1.1/Wed Feb 25 13:18:50 2009//
# CVS Reference       : /RSTC_6098A.pl/1.4/Wed Sep 30 14:11:19 2009//
# CVS Reference       : /RTC_1245D.pl/1.3/Fri Sep 17 14:01:31 2004//
# CVS Reference       : /RTTC_6081A.pl/1.2/Thu Nov  4 13:57:22 2004//
# CVS Reference       : /HSDRAMC1_6100A.pl/1.2/Mon Aug  9 10:52:25 2004//
# CVS Reference       : /SHDWC_6122A.pl/1.3/Wed Oct  6 14:16:58 2004//
# CVS Reference       : /HSMC3_SAM3S4.pl/1.1/Fri Mar 13 09:20:27 2009//
# CVS Reference       : /SPI2.pl/1.6/Wed Sep 30 14:11:20 2009//
# CVS Reference       : /SSC_SAM3S4.pl/1.1/Thu Apr  9 10:54:32 2009//
# CVS Reference       : /SUPC_SAM3UE256.pl/1.2/Tue May 27 08:20:16 2008//
# CVS Reference       : /SYS_SAM3S4.pl/1.4/Thu Mar  5 09:10:26 2009//
# CVS Reference       : /TC_6082A.pl/1.8/Wed Sep 30 14:11:24 2009//
# CVS Reference       : /TWI_6061B.pl/1.3/Wed Sep 30 14:11:24 2009//
# CVS Reference       : /UDP_sam3S4.pl/1.1/Fri Mar 13 09:03:58 2009//
# CVS Reference       : /US_6089J.pl/1.4/Wed Sep 30 14:11:25 2009//
# CVS Reference       : /WDTC_6080A.pl/1.3/Thu Nov  4 13:58:52 2004//
# ----------------------------------------------------------------------------


# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR System Peripherals
# *****************************************************************************
# -------- GPBR : (SYS Offset: 0x1490) GPBR General Purpose Register -------- 
set AT91C_GPBR_GPRV       [expr 0x0 <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Static Memory Controller Interface
# *****************************************************************************
# -------- SMC_SETUP : (SMC Offset: 0x0) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x4) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x8) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0xc) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]
# -------- SMC_SETUP : (SMC Offset: 0x10) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x14) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x18) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0x1c) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]
# -------- SMC_SETUP : (SMC Offset: 0x20) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x24) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x28) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0x2c) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]
# -------- SMC_SETUP : (SMC Offset: 0x30) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x34) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x38) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0x3c) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]
# -------- SMC_SETUP : (SMC Offset: 0x40) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x44) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x48) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0x4c) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]
# -------- SMC_SETUP : (SMC Offset: 0x50) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x54) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x58) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0x5c) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]
# -------- SMC_SETUP : (SMC Offset: 0x60) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x64) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x68) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0x6c) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]
# -------- SMC_SETUP : (SMC Offset: 0x70) Setup Register for CS x -------- 
set AT91C_SMC_NWESETUP    [expr 0x3F <<  0 ]
set AT91C_SMC_NCSSETUPWR  [expr 0x3F <<  8 ]
set AT91C_SMC_NRDSETUP    [expr 0x3F << 16 ]
set AT91C_SMC_NCSSETUPRD  [expr 0x3F << 24 ]
# -------- SMC_PULSE : (SMC Offset: 0x74) Pulse Register for CS x -------- 
set AT91C_SMC_NWEPULSE    [expr 0x7F <<  0 ]
set AT91C_SMC_NCSPULSEWR  [expr 0x7F <<  8 ]
set AT91C_SMC_NRDPULSE    [expr 0x7F << 16 ]
set AT91C_SMC_NCSPULSERD  [expr 0x7F << 24 ]
# -------- SMC_CYC : (SMC Offset: 0x78) Cycle Register for CS x -------- 
set AT91C_SMC_NWECYCLE    [expr 0x1FF <<  0 ]
set AT91C_SMC_NRDCYCLE    [expr 0x1FF << 16 ]
# -------- SMC_CTRL : (SMC Offset: 0x7c) Control Register for CS x -------- 
set AT91C_SMC_READMODE    [expr 0x1 <<  0 ]
set AT91C_SMC_WRITEMODE   [expr 0x1 <<  1 ]
set AT91C_SMC_NWAITM      [expr 0x3 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_DISABLE        [expr 0x0 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  [expr 0x2 <<  5 ]
set 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   [expr 0x3 <<  5 ]
set AT91C_SMC_BAT         [expr 0x1 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_SELECT          [expr 0x0 <<  8 ]
set 	AT91C_SMC_BAT_BYTE_WRITE           [expr 0x1 <<  8 ]
set AT91C_SMC_DBW         [expr 0x3 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     [expr 0x0 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   [expr 0x1 << 12 ]
set 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS [expr 0x2 << 12 ]
set AT91C_SMC_TDF         [expr 0xF << 16 ]
set AT91C_SMC_TDFEN       [expr 0x1 << 20 ]
set AT91C_SMC_PMEN        [expr 0x1 << 24 ]
set AT91C_SMC_PS          [expr 0x3 << 28 ]
set 	AT91C_SMC_PS_SIZE_FOUR_BYTES      [expr 0x0 << 28 ]
set 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     [expr 0x1 << 28 ]
set 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   [expr 0x2 << 28 ]
set 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES [expr 0x3 << 28 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR AHB Matrix2 Interface
# *****************************************************************************
# -------- MATRIX_MCFG0 : (HMATRIX2 Offset: 0x0) Master Configuration Register ARM bus I and D -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_MCFG1 : (HMATRIX2 Offset: 0x4) Master Configuration Register ARM bus S -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_MCFG2 : (HMATRIX2 Offset: 0x8) Master Configuration Register -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_MCFG3 : (HMATRIX2 Offset: 0xc) Master Configuration Register -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_MCFG4 : (HMATRIX2 Offset: 0x10) Master Configuration Register -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_MCFG5 : (HMATRIX2 Offset: 0x14) Master Configuration Register -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_MCFG6 : (HMATRIX2 Offset: 0x18) Master Configuration Register -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_MCFG7 : (HMATRIX2 Offset: 0x1c) Master Configuration Register -------- 
set AT91C_MATRIX_ULBT     [expr 0x7 <<  0 ]
set 	AT91C_MATRIX_ULBT_INFINIT_LENGTH       0x0
set 	AT91C_MATRIX_ULBT_SINGLE_ACCESS        0x1
set 	AT91C_MATRIX_ULBT_4_BEAT               0x2
set 	AT91C_MATRIX_ULBT_8_BEAT               0x3
set 	AT91C_MATRIX_ULBT_16_BEAT              0x4
set 	AT91C_MATRIX_ULBT_32_BEAT              0x5
set 	AT91C_MATRIX_ULBT_64_BEAT              0x6
set 	AT91C_MATRIX_ULBT_128_BEAT             0x7
# -------- MATRIX_SCFG0 : (HMATRIX2 Offset: 0x40) Slave Configuration Register 0 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG0 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG0_ARMS                 [expr 0x1 << 18 ]
# -------- MATRIX_SCFG1 : (HMATRIX2 Offset: 0x44) Slave Configuration Register 1 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG1 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG1_ARMS                 [expr 0x1 << 18 ]
# -------- MATRIX_SCFG2 : (HMATRIX2 Offset: 0x48) Slave Configuration Register 2 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG2 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG2_ARMS                 [expr 0x1 << 18 ]
# -------- MATRIX_SCFG3 : (HMATRIX2 Offset: 0x4c) Slave Configuration Register 3 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG3 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG3_ARMC                 [expr 0x0 << 18 ]
# -------- MATRIX_SCFG4 : (HMATRIX2 Offset: 0x50) Slave Configuration Register 4 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG4 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG4_ARMC                 [expr 0x0 << 18 ]
# -------- MATRIX_SCFG5 : (HMATRIX2 Offset: 0x54) Slave Configuration Register 5 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG5 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG5_ARMS                 [expr 0x1 << 18 ]
# -------- MATRIX_SCFG6 : (HMATRIX2 Offset: 0x58) Slave Configuration Register 6 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG6 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG6_ARMS                 [expr 0x1 << 18 ]
# -------- MATRIX_SCFG7 : (HMATRIX2 Offset: 0x5c) Slave Configuration Register 7 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG7 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG7_ARMS                 [expr 0x1 << 18 ]
# -------- MATRIX_SCFG8 : (HMATRIX2 Offset: 0x60) Slave Configuration Register 8 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG8 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG8_ARMS                 [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG8_HDMA                 [expr 0x4 << 18 ]
# -------- MATRIX_SCFG9 : (HMATRIX2 Offset: 0x64) Slave Configuration Register 9 -------- 
set AT91C_MATRIX_SLOT_CYCLE [expr 0xFF <<  0 ]
set AT91C_MATRIX_DEFMSTR_TYPE [expr 0x3 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           [expr 0x0 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         [expr 0x1 << 16 ]
set 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        [expr 0x2 << 16 ]
set AT91C_MATRIX_FIXED_DEFMSTR_SCFG9 [expr 0x7 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG9_ARMS                 [expr 0x1 << 18 ]
set 	AT91C_MATRIX_FIXED_DEFMSTR_SCFG9_HDMA                 [expr 0x4 << 18 ]
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x110) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x114) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x118) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x11c) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x120) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x124) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x128) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x12c) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x130) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x134) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x138) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x13c) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x140) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x144) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x148) Special Function Register 0 -------- 
# -------- MATRIX_SFR0 : (HMATRIX2 Offset: 0x14c) Special Function Register 0 -------- 
# -------- HMATRIX2_VER : (HMATRIX2 Offset: 0x1fc)  VERSION  Register -------- 
set AT91C_HMATRIX2_VER    [expr 0xF <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR AHB CCFG Interface
# *****************************************************************************
# -------- CCFG_RAM0 : (CCFG Offset: 0x0) RAM0 Configuration -------- 
# -------- CCFG_ROM : (CCFG Offset: 0x4) ROM configuration -------- 
# -------- CCFG_FLASH0 : (CCFG Offset: 0x8) FLASH0 configuration -------- 
# -------- CCFG_EBICSA : (CCFG Offset: 0xc) EBI Chip Select Assignement Register -------- 
set AT91C_EBI_CS0A        [expr 0x1 <<  0 ]
set 	AT91C_EBI_CS0A_SMC                  0x0
set 	AT91C_EBI_CS0A_SM                   0x1
set AT91C_EBI_CS1A        [expr 0x1 <<  1 ]
set 	AT91C_EBI_CS1A_SMC                  [expr 0x0 <<  1 ]
set 	AT91C_EBI_CS1A_SM                   [expr 0x1 <<  1 ]
set AT91C_EBI_CS2A        [expr 0x1 <<  2 ]
set 	AT91C_EBI_CS2A_SMC                  [expr 0x0 <<  2 ]
set 	AT91C_EBI_CS2A_SM                   [expr 0x1 <<  2 ]
set AT91C_EBI_CS3A        [expr 0x1 <<  3 ]
set 	AT91C_EBI_CS3A_SMC                  [expr 0x0 <<  3 ]
set 	AT91C_EBI_CS3A_SM                   [expr 0x1 <<  3 ]
# -------- CCFG_BRIDGE : (CCFG Offset: 0x10) BRIDGE configuration -------- 

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR NESTED vector Interrupt Controller
# *****************************************************************************
# -------- NVIC_ICTR : (NVIC Offset: 0x4) Interrupt Controller Type Register -------- 
set AT91C_NVIC_INTLINESNUM [expr 0xF <<  0 ]
set 	AT91C_NVIC_INTLINESNUM_32                   0x0
set 	AT91C_NVIC_INTLINESNUM_64                   0x1
set 	AT91C_NVIC_INTLINESNUM_96                   0x2
set 	AT91C_NVIC_INTLINESNUM_128                  0x3
set 	AT91C_NVIC_INTLINESNUM_160                  0x4
set 	AT91C_NVIC_INTLINESNUM_192                  0x5
set 	AT91C_NVIC_INTLINESNUM_224                  0x6
set 	AT91C_NVIC_INTLINESNUM_256                  0x7
set 	AT91C_NVIC_INTLINESNUM_288                  0x8
set 	AT91C_NVIC_INTLINESNUM_320                  0x9
set 	AT91C_NVIC_INTLINESNUM_352                  0xA
set 	AT91C_NVIC_INTLINESNUM_384                  0xB
set 	AT91C_NVIC_INTLINESNUM_416                  0xC
set 	AT91C_NVIC_INTLINESNUM_448                  0xD
set 	AT91C_NVIC_INTLINESNUM_480                  0xE
set 	AT91C_NVIC_INTLINESNUM_496                  0xF
# -------- NVIC_STICKCSR : (NVIC Offset: 0x10) SysTick Control and Status Register -------- 
set AT91C_NVIC_STICKENABLE [expr 0x1 <<  0 ]
set AT91C_NVIC_STICKINT   [expr 0x1 <<  1 ]
set AT91C_NVIC_STICKCLKSOURCE [expr 0x1 <<  2 ]
set AT91C_NVIC_STICKCOUNTFLAG [expr 0x1 << 16 ]
# -------- NVIC_STICKRVR : (NVIC Offset: 0x14) SysTick Reload Value Register -------- 
set AT91C_NVIC_STICKRELOAD [expr 0xFFFFFF <<  0 ]
# -------- NVIC_STICKCVR : (NVIC Offset: 0x18) SysTick Current Value Register -------- 
set AT91C_NVIC_STICKCURRENT [expr 0x7FFFFFFF <<  0 ]
# -------- NVIC_STICKCALVR : (NVIC Offset: 0x1c) SysTick Calibration Value Register -------- 
set AT91C_NVIC_STICKTENMS [expr 0xFFFFFF <<  0 ]
set AT91C_NVIC_STICKSKEW  [expr 0x1 << 30 ]
set AT91C_NVIC_STICKNOREF [expr 0x1 << 31 ]
# -------- NVIC_IPR : (NVIC Offset: 0x400) Interrupt Priority Registers -------- 
set AT91C_NVIC_PRI_N      [expr 0xFF <<  0 ]
set AT91C_NVIC_PRI_N1     [expr 0xFF <<  8 ]
set AT91C_NVIC_PRI_N2     [expr 0xFF << 16 ]
set AT91C_NVIC_PRI_N3     [expr 0xFF << 24 ]
# -------- NVIC_CPUID : (NVIC Offset: 0xd00) CPU ID Base Register -------- 
set AT91C_NVIC_REVISION   [expr 0xF <<  0 ]
set AT91C_NVIC_PARTNO     [expr 0xFFF <<  4 ]
set AT91C_NVIC_CONSTANT   [expr 0xF << 16 ]
set AT91C_NVIC_VARIANT    [expr 0xF << 20 ]
set AT91C_NVIC_IMPLEMENTER [expr 0xFF << 24 ]
# -------- NVIC_ICSR : (NVIC Offset: 0xd04) Interrupt Control State Register -------- 
set AT91C_NVIC_VECTACTIVE [expr 0x1FF <<  0 ]
set AT91C_NVIC_RETTOBASE  [expr 0x1 << 11 ]
set AT91C_NVIC_VECTPENDING [expr 0x1FF << 12 ]
set AT91C_NVIC_ISRPENDING [expr 0x1 << 22 ]
set AT91C_NVIC_ISRPREEMPT [expr 0x1 << 23 ]
set AT91C_NVIC_PENDSTCLR  [expr 0x1 << 25 ]
set AT91C_NVIC_PENDSTSET  [expr 0x1 << 26 ]
set AT91C_NVIC_PENDSVCLR  [expr 0x1 << 27 ]
set AT91C_NVIC_PENDSVSET  [expr 0x1 << 28 ]
set AT91C_NVIC_NMIPENDSET [expr 0x1 << 31 ]
# -------- NVIC_VTOFFR : (NVIC Offset: 0xd08) Vector Table Offset Register -------- 
set AT91C_NVIC_TBLOFF     [expr 0x3FFFFF <<  7 ]
set AT91C_NVIC_TBLBASE    [expr 0x1 << 29 ]
set 	AT91C_NVIC_TBLBASE_CODE                 [expr 0x0 << 29 ]
set 	AT91C_NVIC_TBLBASE_RAM                  [expr 0x1 << 29 ]
# -------- NVIC_AIRCR : (NVIC Offset: 0xd0c) Application Interrupt and Reset Control Register -------- 
set AT91C_NVIC_VECTRESET  [expr 0x1 <<  0 ]
set AT91C_NVIC_VECTCLRACTIVE [expr 0x1 <<  1 ]
set AT91C_NVIC_SYSRESETREQ [expr 0x1 <<  2 ]
set AT91C_NVIC_PRIGROUP   [expr 0x7 <<  8 ]
set 	AT91C_NVIC_PRIGROUP_3                    [expr 0x3 <<  8 ]
set 	AT91C_NVIC_PRIGROUP_4                    [expr 0x4 <<  8 ]
set 	AT91C_NVIC_PRIGROUP_5                    [expr 0x5 <<  8 ]
set 	AT91C_NVIC_PRIGROUP_6                    [expr 0x6 <<  8 ]
set 	AT91C_NVIC_PRIGROUP_7                    [expr 0x7 <<  8 ]
set AT91C_NVIC_ENDIANESS  [expr 0x1 << 15 ]
set AT91C_NVIC_VECTKEY    [expr 0xFFFF << 16 ]
# -------- NVIC_SCR : (NVIC Offset: 0xd10) System Control Register -------- 
set AT91C_NVIC_SLEEPONEXIT [expr 0x1 <<  1 ]
set AT91C_NVIC_SLEEPDEEP  [expr 0x1 <<  2 ]
set AT91C_NVIC_SEVONPEND  [expr 0x1 <<  4 ]
# -------- NVIC_CCR : (NVIC Offset: 0xd14) Configuration Control Register -------- 
set AT91C_NVIC_NONEBASETHRDENA [expr 0x1 <<  0 ]
set AT91C_NVIC_USERSETMPEND [expr 0x1 <<  1 ]
set AT91C_NVIC_UNALIGN_TRP [expr 0x1 <<  3 ]
set AT91C_NVIC_DIV_0_TRP  [expr 0x1 <<  4 ]
set AT91C_NVIC_BFHFNMIGN  [expr 0x1 <<  8 ]
set AT91C_NVIC_STKALIGN   [expr 0x1 <<  9 ]
# -------- NVIC_HAND4PR : (NVIC Offset: 0xd18) System Handlers 4-7 Priority Register -------- 
set AT91C_NVIC_PRI_4      [expr 0xFF <<  0 ]
set AT91C_NVIC_PRI_5      [expr 0xFF <<  8 ]
set AT91C_NVIC_PRI_6      [expr 0xFF << 16 ]
set AT91C_NVIC_PRI_7      [expr 0xFF << 24 ]
# -------- NVIC_HAND8PR : (NVIC Offset: 0xd1c) System Handlers 8-11 Priority Register -------- 
set AT91C_NVIC_PRI_8      [expr 0xFF <<  0 ]
set AT91C_NVIC_PRI_9      [expr 0xFF <<  8 ]
set AT91C_NVIC_PRI_10     [expr 0xFF << 16 ]
set AT91C_NVIC_PRI_11     [expr 0xFF << 24 ]
# -------- NVIC_HAND12PR : (NVIC Offset: 0xd20) System Handlers 12-15 Priority Register -------- 
set AT91C_NVIC_PRI_12     [expr 0xFF <<  0 ]
set AT91C_NVIC_PRI_13     [expr 0xFF <<  8 ]
set AT91C_NVIC_PRI_14     [expr 0xFF << 16 ]
set AT91C_NVIC_PRI_15     [expr 0xFF << 24 ]
# -------- NVIC_HANDCSR : (NVIC Offset: 0xd24) System Handler Control and State Register -------- 
set AT91C_NVIC_MEMFAULTACT [expr 0x1 <<  0 ]
set AT91C_NVIC_BUSFAULTACT [expr 0x1 <<  1 ]
set AT91C_NVIC_USGFAULTACT [expr 0x1 <<  3 ]
set AT91C_NVIC_SVCALLACT  [expr 0x1 <<  7 ]
set AT91C_NVIC_MONITORACT [expr 0x1 <<  8 ]
set AT91C_NVIC_PENDSVACT  [expr 0x1 << 10 ]
set AT91C_NVIC_SYSTICKACT [expr 0x1 << 11 ]
set AT91C_NVIC_USGFAULTPENDED [expr 0x1 << 12 ]
set AT91C_NVIC_MEMFAULTPENDED [expr 0x1 << 13 ]
set AT91C_NVIC_BUSFAULTPENDED [expr 0x1 << 14 ]
set AT91C_NVIC_SVCALLPENDED [expr 0x1 << 15 ]
set AT91C_NVIC_MEMFAULTENA [expr 0x1 << 16 ]
set AT91C_NVIC_BUSFAULTENA [expr 0x1 << 17 ]
set AT91C_NVIC_USGFAULTENA [expr 0x1 << 18 ]
# -------- NVIC_CFSR : (NVIC Offset: 0xd28) Configurable Fault Status Registers -------- 
set AT91C_NVIC_MEMMANAGE  [expr 0xFF <<  0 ]
set AT91C_NVIC_BUSFAULT   [expr 0xFF <<  8 ]
set AT91C_NVIC_USAGEFAULT [expr 0xFF << 16 ]
# -------- NVIC_BFAR : (NVIC Offset: 0xd38) Bus Fault Address Register -------- 
set AT91C_NVIC_IBUSERR    [expr 0x1 <<  0 ]
set AT91C_NVIC_PRECISERR  [expr 0x1 <<  1 ]
set AT91C_NVIC_IMPRECISERR [expr 0x1 <<  2 ]
set AT91C_NVIC_UNSTKERR   [expr 0x1 <<  3 ]
set AT91C_NVIC_STKERR     [expr 0x1 <<  4 ]
set AT91C_NVIC_BFARVALID  [expr 0x1 <<  7 ]
# -------- NVIC_PFR0 : (NVIC Offset: 0xd40) Processor Feature register0 (ID_PFR0) -------- 
set AT91C_NVIC_ID_PFR0_0  [expr 0xF <<  0 ]
set AT91C_NVIC_ID_PRF0_1  [expr 0xF <<  4 ]
# -------- NVIC_PFR1 : (NVIC Offset: 0xd44) Processor Feature register1 (ID_PFR1) -------- 
set AT91C_NVIC_ID_PRF1_MODEL [expr 0xF <<  8 ]
# -------- NVIC_DFR0 : (NVIC Offset: 0xd48) Debug Feature register0 (ID_DFR0) -------- 
set AT91C_NVIC_ID_DFR0_MODEL [expr 0xF << 20 ]
# -------- NVIC_MMFR0 : (NVIC Offset: 0xd50) Memory Model Feature register0 (ID_MMFR0) -------- 
set AT91C_NVIC_ID_MMFR0_PMSA [expr 0xF <<  4 ]
set AT91C_NVIC_ID_MMFR0_CACHE [expr 0xF <<  8 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR NESTED vector Interrupt Controller
# *****************************************************************************
# -------- MPU_TYPE : (MPU Offset: 0x0)  -------- 
set AT91C_MPU_SEPARATE    [expr 0x1 <<  0 ]
set AT91C_MPU_DREGION     [expr 0xFF <<  8 ]
set AT91C_MPU_IREGION     [expr 0xFF << 16 ]
# -------- MPU_CTRL : (MPU Offset: 0x4)  -------- 
set AT91C_MPU_ENABLE      [expr 0x1 <<  0 ]
set AT91C_MPU_HFNMIENA    [expr 0x1 <<  1 ]
set AT91C_MPU_PRIVDEFENA  [expr 0x1 <<  2 ]
# -------- MPU_REG_NB : (MPU Offset: 0x8)  -------- 
set AT91C_MPU_REGION      [expr 0xFF <<  0 ]
# -------- MPU_REG_BASE_ADDR : (MPU Offset: 0xc)  -------- 
set AT91C_MPU_REG         [expr 0xF <<  0 ]
set AT91C_MPU_VALID       [expr 0x1 <<  4 ]
set AT91C_MPU_ADDR        [expr 0x3FFFFFF <<  5 ]
# -------- MPU_ATTR_SIZE : (MPU Offset: 0x10)  -------- 
set AT91C_MPU_ENA         [expr 0x1 <<  0 ]
set AT91C_MPU_SIZE        [expr 0xF <<  1 ]
set AT91C_MPU_SRD         [expr 0xFF <<  8 ]
set AT91C_MPU_B           [expr 0x1 << 16 ]
set AT91C_MPU_C           [expr 0x1 << 17 ]
set AT91C_MPU_S           [expr 0x1 << 18 ]
set AT91C_MPU_TEX         [expr 0x7 << 19 ]
set AT91C_MPU_AP          [expr 0x7 << 24 ]
set AT91C_MPU_XN          [expr 0x7 << 28 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR CORTEX_M3 Registers
# *****************************************************************************
# -------- CM3_CPUID : (CM3 Offset: 0x0)  -------- 
# -------- CM3_AIRCR : (CM3 Offset: 0xc)  -------- 
set AT91C_CM3_SYSRESETREQ [expr 0x1 <<  2 ]
# -------- CM3_SCR : (CM3 Offset: 0x10)  -------- 
set AT91C_CM3_SLEEPONEXIT [expr 0x1 <<  1 ]
set AT91C_CM3_SLEEPDEEP   [expr 0x1 <<  2 ]
set AT91C_CM3_SEVONPEND   [expr 0x1 <<  4 ]
# -------- CM3_SHCSR : (CM3 Offset: 0x24)  -------- 
set AT91C_CM3_SYSTICKACT  [expr 0x1 << 11 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Peripheral DMA Controller
# *****************************************************************************
# -------- PDC_PTCR : (PDC Offset: 0x20) PDC Transfer Control Register -------- 
set AT91C_PDC_RXTEN       [expr 0x1 <<  0 ]
set AT91C_PDC_RXTDIS      [expr 0x1 <<  1 ]
set AT91C_PDC_TXTEN       [expr 0x1 <<  8 ]
set AT91C_PDC_TXTDIS      [expr 0x1 <<  9 ]
# -------- PDC_PTSR : (PDC Offset: 0x24) PDC Transfer Status Register -------- 
set AT91C_PDC_RXTEN       [expr 0x1 <<  0 ]
set AT91C_PDC_TXTEN       [expr 0x1 <<  8 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Debug Unit
# *****************************************************************************
# -------- DBGU_CR : (DBGU Offset: 0x0) Debug Unit Control Register -------- 
set AT91C_DBGU_RSTRX      [expr 0x1 <<  2 ]
set AT91C_DBGU_RSTTX      [expr 0x1 <<  3 ]
set AT91C_DBGU_RXEN       [expr 0x1 <<  4 ]
set AT91C_DBGU_RXDIS      [expr 0x1 <<  5 ]
set AT91C_DBGU_TXEN       [expr 0x1 <<  6 ]
set AT91C_DBGU_TXDIS      [expr 0x1 <<  7 ]
set AT91C_DBGU_RSTSTA     [expr 0x1 <<  8 ]
# -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- 
set AT91C_DBGU_PAR        [expr 0x7 <<  9 ]
set 	AT91C_DBGU_PAR_EVEN                 [expr 0x0 <<  9 ]
set 	AT91C_DBGU_PAR_ODD                  [expr 0x1 <<  9 ]
set 	AT91C_DBGU_PAR_SPACE                [expr 0x2 <<  9 ]
set 	AT91C_DBGU_PAR_MARK                 [expr 0x3 <<  9 ]
set 	AT91C_DBGU_PAR_NONE                 [expr 0x4 <<  9 ]
set AT91C_DBGU_CHMODE     [expr 0x3 << 14 ]
set 	AT91C_DBGU_CHMODE_NORMAL               [expr 0x0 << 14 ]
set 	AT91C_DBGU_CHMODE_AUTO                 [expr 0x1 << 14 ]
set 	AT91C_DBGU_CHMODE_LOCAL                [expr 0x2 << 14 ]
set 	AT91C_DBGU_CHMODE_REMOTE               [expr 0x3 << 14 ]
# -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
set AT91C_DBGU_RXRDY      [expr 0x1 <<  0 ]
set AT91C_DBGU_TXRDY      [expr 0x1 <<  1 ]
set AT91C_DBGU_ENDRX      [expr 0x1 <<  3 ]
set AT91C_DBGU_ENDTX      [expr 0x1 <<  4 ]
set AT91C_DBGU_OVRE       [expr 0x1 <<  5 ]
set AT91C_DBGU_FRAME      [expr 0x1 <<  6 ]
set AT91C_DBGU_PARE       [expr 0x1 <<  7 ]
set AT91C_DBGU_TXEMPTY    [expr 0x1 <<  9 ]
set AT91C_DBGU_TXBUFE     [expr 0x1 << 11 ]
set AT91C_DBGU_RXBUFF     [expr 0x1 << 12 ]
set AT91C_DBGU_COMM_TX    [expr 0x1 << 30 ]
set AT91C_DBGU_COMM_RX    [expr 0x1 << 31 ]
# -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- 
set AT91C_DBGU_RXRDY      [expr 0x1 <<  0 ]
set AT91C_DBGU_TXRDY      [expr 0x1 <<  1 ]
set AT91C_DBGU_ENDRX      [expr 0x1 <<  3 ]
set AT91C_DBGU_ENDTX      [expr 0x1 <<  4 ]
set AT91C_DBGU_OVRE       [expr 0x1 <<  5 ]
set AT91C_DBGU_FRAME      [expr 0x1 <<  6 ]
set AT91C_DBGU_PARE       [expr 0x1 <<  7 ]
set AT91C_DBGU_TXEMPTY    [expr 0x1 <<  9 ]
set AT91C_DBGU_TXBUFE     [expr 0x1 << 11 ]
set AT91C_DBGU_RXBUFF     [expr 0x1 << 12 ]
set AT91C_DBGU_COMM_TX    [expr 0x1 << 30 ]
set AT91C_DBGU_COMM_RX    [expr 0x1 << 31 ]
# -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- 
set AT91C_DBGU_RXRDY      [expr 0x1 <<  0 ]
set AT91C_DBGU_TXRDY      [expr 0x1 <<  1 ]
set AT91C_DBGU_ENDRX      [expr 0x1 <<  3 ]
set AT91C_DBGU_ENDTX      [expr 0x1 <<  4 ]
set AT91C_DBGU_OVRE       [expr 0x1 <<  5 ]
set AT91C_DBGU_FRAME      [expr 0x1 <<  6 ]
set AT91C_DBGU_PARE       [expr 0x1 <<  7 ]
set AT91C_DBGU_TXEMPTY    [expr 0x1 <<  9 ]
set AT91C_DBGU_TXBUFE     [expr 0x1 << 11 ]
set AT91C_DBGU_RXBUFF     [expr 0x1 << 12 ]
set AT91C_DBGU_COMM_TX    [expr 0x1 << 30 ]
set AT91C_DBGU_COMM_RX    [expr 0x1 << 31 ]
# -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- 
set AT91C_DBGU_RXRDY      [expr 0x1 <<  0 ]
set AT91C_DBGU_TXRDY      [expr 0x1 <<  1 ]
set AT91C_DBGU_ENDRX      [expr 0x1 <<  3 ]
set AT91C_DBGU_ENDTX      [expr 0x1 <<  4 ]
set AT91C_DBGU_OVRE       [expr 0x1 <<  5 ]
set AT91C_DBGU_FRAME      [expr 0x1 <<  6 ]
set AT91C_DBGU_PARE       [expr 0x1 <<  7 ]
set AT91C_DBGU_TXEMPTY    [expr 0x1 <<  9 ]
set AT91C_DBGU_TXBUFE     [expr 0x1 << 11 ]
set AT91C_DBGU_RXBUFF     [expr 0x1 << 12 ]
set AT91C_DBGU_COMM_TX    [expr 0x1 << 30 ]
set AT91C_DBGU_COMM_RX    [expr 0x1 << 31 ]
# -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- 
set AT91C_DBGU_FORCE_NTRST [expr 0x1 <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Parallel Input Output Controler
# *****************************************************************************

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Power Management Controler
# *****************************************************************************
# -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_UDP         [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2        [expr 0x1 << 10 ]
# -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_UDP         [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2        [expr 0x1 << 10 ]
# -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- 
set AT91C_PMC_PCK         [expr 0x1 <<  0 ]
set AT91C_PMC_UDP         [expr 0x1 <<  7 ]
set AT91C_PMC_PCK0        [expr 0x1 <<  8 ]
set AT91C_PMC_PCK1        [expr 0x1 <<  9 ]
set AT91C_PMC_PCK2        [expr 0x1 << 10 ]
# -------- CKGR_UCKR : (PMC Offset: 0x1c) UTMI Clock Configuration Register -------- 
set AT91C_CKGR_UPLLEN     [expr 0x1 << 16 ]
set 	AT91C_CKGR_UPLLEN_DISABLED             [expr 0x0 << 16 ]
set 	AT91C_CKGR_UPLLEN_ENABLED              [expr 0x1 << 16 ]
set AT91C_CKGR_UPLLCOUNT  [expr 0xF << 20 ]
set AT91C_CKGR_BIASEN     [expr 0x1 << 24 ]
set 	AT91C_CKGR_BIASEN_DISABLED             [expr 0x0 << 24 ]
set 	AT91C_CKGR_BIASEN_ENABLED              [expr 0x1 << 24 ]
set AT91C_CKGR_BIASCOUNT  [expr 0xF << 28 ]
# -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- 
set AT91C_CKGR_MOSCXTEN   [expr 0x1 <<  0 ]
set AT91C_CKGR_MOSCXTBY   [expr 0x1 <<  1 ]
set AT91C_CKGR_WAITMODE   [expr 0x1 <<  2 ]
set AT91C_CKGR_MOSCRCEN   [expr 0x1 <<  3 ]
set AT91C_CKGR_MOSCRCF    [expr 0x7 <<  4 ]
set AT91C_CKGR_MOSCXTST   [expr 0xFF <<  8 ]
set AT91C_CKGR_KEY        [expr 0xFF << 16 ]
set AT91C_CKGR_MOSCSEL    [expr 0x1 << 24 ]
set AT91C_CKGR_CFDEN      [expr 0x1 << 25 ]
# -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- 
set AT91C_CKGR_MAINF      [expr 0xFFFF <<  0 ]
set AT91C_CKGR_MAINRDY    [expr 0x1 << 16 ]
# -------- CKGR_PLLAR : (PMC Offset: 0x28) PLL A Register -------- 
set AT91C_CKGR_DIVA       [expr 0xFF <<  0 ]
set 	AT91C_CKGR_DIVA_0                    0x0
set 	AT91C_CKGR_DIVA_BYPASS               0x1
set AT91C_CKGR_PLLACOUNT  [expr 0x3F <<  8 ]
set AT91C_CKGR_STMODE     [expr 0x3 << 14 ]
set 	AT91C_CKGR_STMODE_0                    [expr 0x0 << 14 ]
set 	AT91C_CKGR_STMODE_1                    [expr 0x1 << 14 ]
set 	AT91C_CKGR_STMODE_2                    [expr 0x2 << 14 ]
set 	AT91C_CKGR_STMODE_3                    [expr 0x3 << 14 ]
set AT91C_CKGR_MULA       [expr 0x7FF << 16 ]
set AT91C_CKGR_SRC        [expr 0x1 << 29 ]
# -------- CKGR_PLLBR : (PMC Offset: 0x2c) PLL B Register -------- 
set AT91C_CKGR_DIVB       [expr 0xFF <<  0 ]
set 	AT91C_CKGR_DIVB_0                    0x0
set 	AT91C_CKGR_DIVB_BYPASS               0x1
set AT91C_CKGR_PLLBCOUNT  [expr 0x3F <<  8 ]
set AT91C_CKGR_OUTB       [expr 0x3 << 14 ]
set 	AT91C_CKGR_OUTB_0                    [expr 0x0 << 14 ]
set 	AT91C_CKGR_OUTB_1                    [expr 0x1 << 14 ]
set 	AT91C_CKGR_OUTB_2                    [expr 0x2 << 14 ]
set 	AT91C_CKGR_OUTB_3                    [expr 0x3 << 14 ]
set AT91C_CKGR_MULB       [expr 0x7FF << 16 ]
# -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- 
set AT91C_PMC_CSS         [expr 0x7 <<  0 ]
set 	AT91C_PMC_CSS_SLOW_CLK             0x0
set 	AT91C_PMC_CSS_MAIN_CLK             0x1
set 	AT91C_PMC_CSS_PLLA_CLK             0x2
set 	AT91C_PMC_CSS_PLLB_CLK             0x3
set 	AT91C_PMC_CSS_SYS_CLK              0x4
set AT91C_PMC_PRES        [expr 0xF <<  4 ]
set 	AT91C_PMC_PRES_CLK                  [expr 0x0 <<  4 ]
set 	AT91C_PMC_PRES_CLK_2                [expr 0x1 <<  4 ]
set 	AT91C_PMC_PRES_CLK_4                [expr 0x2 <<  4 ]
set 	AT91C_PMC_PRES_CLK_8                [expr 0x3 <<  4 ]
set 	AT91C_PMC_PRES_CLK_16               [expr 0x4 <<  4 ]
set 	AT91C_PMC_PRES_CLK_32               [expr 0x5 <<  4 ]
set 	AT91C_PMC_PRES_CLK_64               [expr 0x6 <<  4 ]
set 	AT91C_PMC_PRES_CLK_3                [expr 0x7 <<  4 ]
set 	AT91C_PMC_PRES_CLK_1_5              [expr 0x8 <<  4 ]
# -------- PMC_UDPR : (PMC Offset: 0x38) USB DEV Clock Configuration Register -------- 
set AT91C_PMC_UDP_CLK_SEL [expr 0x1 <<  0 ]
set 	AT91C_PMC_UDP_CLK_SEL_PLLA                 0x0
set 	AT91C_PMC_UDP_CLK_SEL_PLLB                 0x1
set AT91C_PMC_UDP_DIV     [expr 0xF <<  8 ]
set 	AT91C_PMC_UDP_DIV_DIV                  [expr 0x0 <<  8 ]
set 	AT91C_PMC_UDP_DIV_DIV_2                [expr 0x1 <<  8 ]
# -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- 
set AT91C_PMC_CSS         [expr 0x7 <<  0 ]
set 	AT91C_PMC_CSS_SLOW_CLK             0x0
set 	AT91C_PMC_CSS_MAIN_CLK             0x1
set 	AT91C_PMC_CSS_PLLA_CLK             0x2
set 	AT91C_PMC_CSS_PLLB_CLK             0x3
set 	AT91C_PMC_CSS_SYS_CLK              0x4
set AT91C_PMC_PRES        [expr 0xF <<  4 ]
set 	AT91C_PMC_PRES_CLK                  [expr 0x0 <<  4 ]
set 	AT91C_PMC_PRES_CLK_2                [expr 0x1 <<  4 ]
set 	AT91C_PMC_PRES_CLK_4                [expr 0x2 <<  4 ]
set 	AT91C_PMC_PRES_CLK_8                [expr 0x3 <<  4 ]
set 	AT91C_PMC_PRES_CLK_16               [expr 0x4 <<  4 ]
set 	AT91C_PMC_PRES_CLK_32               [expr 0x5 <<  4 ]
set 	AT91C_PMC_PRES_CLK_64               [expr 0x6 <<  4 ]
set 	AT91C_PMC_PRES_CLK_3                [expr 0x7 <<  4 ]
set 	AT91C_PMC_PRES_CLK_1_5              [expr 0x8 <<  4 ]
# -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- 
set AT91C_PMC_MOSCXTS     [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_LOCKB       [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_PCKRDY0     [expr 0x1 <<  8 ]
set AT91C_PMC_PCKRDY1     [expr 0x1 <<  9 ]
set AT91C_PMC_PCKRDY2     [expr 0x1 << 10 ]
set AT91C_PMC_MOSCSELS    [expr 0x1 << 16 ]
set AT91C_PMC_MOSCRCS     [expr 0x1 << 17 ]
set AT91C_PMC_CFDEV       [expr 0x1 << 18 ]
# -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- 
set AT91C_PMC_MOSCXTS     [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_LOCKB       [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_PCKRDY0     [expr 0x1 <<  8 ]
set AT91C_PMC_PCKRDY1     [expr 0x1 <<  9 ]
set AT91C_PMC_PCKRDY2     [expr 0x1 << 10 ]
set AT91C_PMC_MOSCSELS    [expr 0x1 << 16 ]
set AT91C_PMC_MOSCRCS     [expr 0x1 << 17 ]
set AT91C_PMC_CFDEV       [expr 0x1 << 18 ]
# -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- 
set AT91C_PMC_MOSCXTS     [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_LOCKB       [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_                [expr 0x0 <<  7 ]
set AT91C_PMC_PCKRDY0     [expr 0x1 <<  8 ]
set AT91C_PMC_PCKRDY1     [expr 0x1 <<  9 ]
set AT91C_PMC_PCKRDY2     [expr 0x1 << 10 ]
set AT91C_PMC_MOSCSELS    [expr 0x1 << 16 ]
set AT91C_PMC_MOSCRCS     [expr 0x1 << 17 ]
set AT91C_PMC_CFDEV       [expr 0x1 << 18 ]
set AT91C_PMC_CFDS        [expr 0x1 << 19 ]
set AT91C_PMC_FOS         [expr 0x1 << 20 ]
# -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- 
set AT91C_PMC_MOSCXTS     [expr 0x1 <<  0 ]
set AT91C_PMC_LOCKA       [expr 0x1 <<  1 ]
set AT91C_PMC_LOCKB       [expr 0x1 <<  2 ]
set AT91C_PMC_MCKRDY      [expr 0x1 <<  3 ]
set AT91C_PMC_LOCKU       [expr 0x1 <<  6 ]
set AT91C_PMC_PCKRDY0     [expr 0x1 <<  8 ]
set AT91C_PMC_PCKRDY1     [expr 0x1 <<  9 ]
set AT91C_PMC_PCKRDY2     [expr 0x1 << 10 ]
set AT91C_PMC_MOSCSELS    [expr 0x1 << 16 ]
set AT91C_PMC_MOSCRCS     [expr 0x1 << 17 ]
set AT91C_PMC_CFDEV       [expr 0x1 << 18 ]
# -------- PMC_FSMR : (PMC Offset: 0x70) Fast Startup Mode Register -------- 
set AT91C_PMC_FSTT        [expr 0xFFFF <<  0 ]
set AT91C_PMC_RTTAL       [expr 0x1 << 16 ]
set AT91C_PMC_RTCAL       [expr 0x1 << 17 ]
set AT91C_PMC_USBAL       [expr 0x1 << 18 ]
set AT91C_PMC_LPM         [expr 0x1 << 20 ]
# -------- PMC_FSPR : (PMC Offset: 0x74) Fast Startup Polarity Register -------- 
set AT91C_PMC_FSTP        [expr 0xFFFF <<  0 ]
# -------- PMC_FOCR : (PMC Offset: 0x78) Fault Output Clear Register -------- 
set AT91C_PMC_FOCLR       [expr 0x1 <<  0 ]
# -------- PMC_PCR : (PMC Offset: 0x10c) Peripheral Control Register -------- 
set AT91C_PMC_PID         [expr 0x3F <<  0 ]
set AT91C_PMC_CMD         [expr 0x1 << 12 ]
set AT91C_PMC_DIV         [expr 0x3 << 16 ]
set AT91C_PMC_EN          [expr 0x1 << 28 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Clock Generator Controler
# *****************************************************************************
# -------- CKGR_UCKR : (CKGR Offset: 0x0) UTMI Clock Configuration Register -------- 
set AT91C_CKGR_UPLLEN     [expr 0x1 << 16 ]
set 	AT91C_CKGR_UPLLEN_DISABLED             [expr 0x0 << 16 ]
set 	AT91C_CKGR_UPLLEN_ENABLED              [expr 0x1 << 16 ]
set AT91C_CKGR_UPLLCOUNT  [expr 0xF << 20 ]
set AT91C_CKGR_BIASEN     [expr 0x1 << 24 ]
set 	AT91C_CKGR_BIASEN_DISABLED             [expr 0x0 << 24 ]
set 	AT91C_CKGR_BIASEN_ENABLED              [expr 0x1 << 24 ]
set AT91C_CKGR_BIASCOUNT  [expr 0xF << 28 ]
# -------- CKGR_MOR : (CKGR Offset: 0x4) Main Oscillator Register -------- 
set AT91C_CKGR_MOSCXTEN   [expr 0x1 <<  0 ]
set AT91C_CKGR_MOSCXTBY   [expr 0x1 <<  1 ]
set AT91C_CKGR_WAITMODE   [expr 0x1 <<  2 ]
set AT91C_CKGR_MOSCRCEN   [expr 0x1 <<  3 ]
set AT91C_CKGR_MOSCRCF    [expr 0x7 <<  4 ]
set AT91C_CKGR_MOSCXTST   [expr 0xFF <<  8 ]
set AT91C_CKGR_KEY        [expr 0xFF << 16 ]
set AT91C_CKGR_MOSCSEL    [expr 0x1 << 24 ]
set AT91C_CKGR_CFDEN      [expr 0x1 << 25 ]
# -------- CKGR_MCFR : (CKGR Offset: 0x8) Main Clock Frequency Register -------- 
set AT91C_CKGR_MAINF      [expr 0xFFFF <<  0 ]
set AT91C_CKGR_MAINRDY    [expr 0x1 << 16 ]
# -------- CKGR_PLLAR : (CKGR Offset: 0xc) PLL A Register -------- 
set AT91C_CKGR_DIVA       [expr 0xFF <<  0 ]
set 	AT91C_CKGR_DIVA_0                    0x0
set 	AT91C_CKGR_DIVA_BYPASS               0x1
set AT91C_CKGR_PLLACOUNT  [expr 0x3F <<  8 ]
set AT91C_CKGR_STMODE     [expr 0x3 << 14 ]
set 	AT91C_CKGR_STMODE_0                    [expr 0x0 << 14 ]
set 	AT91C_CKGR_STMODE_1                    [expr 0x1 << 14 ]
set 	AT91C_CKGR_STMODE_2                    [expr 0x2 << 14 ]
set 	AT91C_CKGR_STMODE_3                    [expr 0x3 << 14 ]
set AT91C_CKGR_MULA       [expr 0x7FF << 16 ]
set AT91C_CKGR_SRC        [expr 0x1 << 29 ]
# -------- CKGR_PLLBR : (CKGR Offset: 0x10) PLL B Register -------- 
set AT91C_CKGR_DIVB       [expr 0xFF <<  0 ]
set 	AT91C_CKGR_DIVB_0                    0x0
set 	AT91C_CKGR_DIVB_BYPASS               0x1
set AT91C_CKGR_PLLBCOUNT  [expr 0x3F <<  8 ]
set AT91C_CKGR_OUTB       [expr 0x3 << 14 ]
set 	AT91C_CKGR_OUTB_0                    [expr 0x0 << 14 ]
set 	AT91C_CKGR_OUTB_1                    [expr 0x1 << 14 ]
set 	AT91C_CKGR_OUTB_2                    [expr 0x2 << 14 ]
set 	AT91C_CKGR_OUTB_3                    [expr 0x3 << 14 ]
set AT91C_CKGR_MULB       [expr 0x7FF << 16 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Reset Controller Interface
# *****************************************************************************
# -------- RSTC_RCR : (RSTC Offset: 0x0) Reset Control Register -------- 
set AT91C_RSTC_PROCRST    [expr 0x1 <<  0 ]
set AT91C_RSTC_ICERST     [expr 0x1 <<  1 ]
set AT91C_RSTC_PERRST     [expr 0x1 <<  2 ]
set AT91C_RSTC_EXTRST     [expr 0x1 <<  3 ]
set AT91C_RSTC_KEY        [expr 0xFF << 24 ]
# -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- 
set AT91C_RSTC_URSTS      [expr 0x1 <<  0 ]
set AT91C_RSTC_RSTTYP     [expr 0x7 <<  8 ]
set 	AT91C_RSTC_RSTTYP_GENERAL              [expr 0x0 <<  8 ]
set 	AT91C_RSTC_RSTTYP_WAKEUP               [expr 0x1 <<  8 ]
set 	AT91C_RSTC_RSTTYP_WATCHDOG             [expr 0x2 <<  8 ]
set 	AT91C_RSTC_RSTTYP_SOFTWARE             [expr 0x3 <<  8 ]
set 	AT91C_RSTC_RSTTYP_USER                 [expr 0x4 <<  8 ]
set AT91C_RSTC_NRSTL      [expr 0x1 << 16 ]
set AT91C_RSTC_SRCMP      [expr 0x1 << 17 ]
# -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- 
set AT91C_RSTC_URSTEN     [expr 0x1 <<  0 ]
set AT91C_RSTC_URSTIEN    [expr 0x1 <<  4 ]
set AT91C_RSTC_ERSTL      [expr 0xF <<  8 ]
set AT91C_RSTC_KEY        [expr 0xFF << 24 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Supply Controller Interface
# *****************************************************************************
# -------- SUPC_CR : (SUPC Offset: 0x0) Control Register -------- 
set AT91C_SUPC_SHDW       [expr 0x1 <<  0 ]
set AT91C_SUPC_SHDWEOF    [expr 0x1 <<  1 ]
set AT91C_SUPC_VROFF      [expr 0x1 <<  2 ]
set AT91C_SUPC_XTALSEL    [expr 0x1 <<  3 ]
set AT91C_SUPC_KEY        [expr 0xFF << 24 ]
# -------- SUPC_BOMR : (SUPC Offset: 0x4) Brown Out Mode Register -------- 
set AT91C_SUPC_BODTH      [expr 0xF <<  0 ]
set AT91C_SUPC_BODSMPL    [expr 0x7 <<  8 ]
set 	AT91C_SUPC_BODSMPL_DISABLED             [expr 0x0 <<  8 ]
set 	AT91C_SUPC_BODSMPL_CONTINUOUS           [expr 0x1 <<  8 ]
set 	AT91C_SUPC_BODSMPL_32_SLCK              [expr 0x2 <<  8 ]
set 	AT91C_SUPC_BODSMPL_256_SLCK             [expr 0x3 <<  8 ]
set 	AT91C_SUPC_BODSMPL_2048_SLCK            [expr 0x4 <<  8 ]
set AT91C_SUPC_BODRSTEN   [expr 0x1 << 12 ]
# -------- SUPC_MR : (SUPC Offset: 0x8) Supply Controller Mode Register -------- 
set AT91C_SUPC_LCDOUT     [expr 0xF <<  0 ]
set AT91C_SUPC_LCDMODE    [expr 0x3 <<  4 ]
set 	AT91C_SUPC_LCDMODE_OFF                  [expr 0x0 <<  4 ]
set 	AT91C_SUPC_LCDMODE_OFF_AFTER_EOF        [expr 0x1 <<  4 ]
set 	AT91C_SUPC_LCDMODE_EXTERNAL             [expr 0x2 <<  4 ]
set 	AT91C_SUPC_LCDMODE_INTERNAL             [expr 0x3 <<  4 ]
set AT91C_SUPC_VRDEEP     [expr 0x1 <<  8 ]
set AT91C_SUPC_VRVDD      [expr 0x7 <<  9 ]
set AT91C_SUPC_VRRSTEN    [expr 0x1 << 12 ]
set AT91C_SUPC_GPBRON     [expr 0x1 << 16 ]
set AT91C_SUPC_SRAMON     [expr 0x1 << 17 ]
set AT91C_SUPC_RTCON      [expr 0x1 << 18 ]
set AT91C_SUPC_FLASHON    [expr 0x1 << 19 ]
set AT91C_SUPC_BYPASS     [expr 0x1 << 20 ]
set AT91C_SUPC_MKEY       [expr 0xFF << 24 ]
# -------- SUPC_WUMR : (SUPC Offset: 0xc) Wake Up Mode Register -------- 
set AT91C_SUPC_FWUPEN     [expr 0x1 <<  0 ]
set AT91C_SUPC_BODEN      [expr 0x1 <<  1 ]
set AT91C_SUPC_RTTEN      [expr 0x1 <<  2 ]
set AT91C_SUPC_RTCEN      [expr 0x1 <<  3 ]
set AT91C_SUPC_FWUPDBC    [expr 0x7 <<  8 ]
set 	AT91C_SUPC_FWUPDBC_IMMEDIATE            [expr 0x0 <<  8 ]
set 	AT91C_SUPC_FWUPDBC_3_SLCK               [expr 0x1 <<  8 ]
set 	AT91C_SUPC_FWUPDBC_32_SLCK              [expr 0x2 <<  8 ]
set 	AT91C_SUPC_FWUPDBC_512_SLCK             [expr 0x3 <<  8 ]
set 	AT91C_SUPC_FWUPDBC_4096_SLCK            [expr 0x4 <<  8 ]
set 	AT91C_SUPC_FWUPDBC_32768_SLCK           [expr 0x5 <<  8 ]
set AT91C_SUPC_WKUPDBC    [expr 0x7 << 12 ]
set 	AT91C_SUPC_WKUPDBC_IMMEDIATE            [expr 0x0 << 12 ]
set 	AT91C_SUPC_WKUPDBC_3_SLCK               [expr 0x1 << 12 ]
set 	AT91C_SUPC_WKUPDBC_32_SLCK              [expr 0x2 << 12 ]
set 	AT91C_SUPC_WKUPDBC_512_SLCK             [expr 0x3 << 12 ]
set 	AT91C_SUPC_WKUPDBC_4096_SLCK            [expr 0x4 << 12 ]
set 	AT91C_SUPC_WKUPDBC_32768_SLCK           [expr 0x5 << 12 ]
# -------- SUPC_WUIR : (SUPC Offset: 0x10) Wake Up Inputs Register -------- 
set AT91C_SUPC_WKUPEN0    [expr 0x1 <<  0 ]
set AT91C_SUPC_WKUPEN1    [expr 0x1 <<  1 ]
set AT91C_SUPC_WKUPEN2    [expr 0x1 <<  2 ]
set AT91C_SUPC_WKUPEN3    [expr 0x1 <<  3 ]
set AT91C_SUPC_WKUPEN4    [expr 0x1 <<  4 ]
set AT91C_SUPC_WKUPEN5    [expr 0x1 <<  5 ]
set AT91C_SUPC_WKUPEN6    [expr 0x1 <<  6 ]
set AT91C_SUPC_WKUPEN7    [expr 0x1 <<  7 ]
set AT91C_SUPC_WKUPEN8    [expr 0x1 <<  8 ]
set AT91C_SUPC_WKUPEN9    [expr 0x1 <<  9 ]
set AT91C_SUPC_WKUPEN10   [expr 0x1 << 10 ]
set AT91C_SUPC_WKUPEN11   [expr 0x1 << 11 ]
set AT91C_SUPC_WKUPEN12   [expr 0x1 << 12 ]
set AT91C_SUPC_WKUPEN13   [expr 0x1 << 13 ]
set AT91C_SUPC_WKUPEN14   [expr 0x1 << 14 ]
set AT91C_SUPC_WKUPEN15   [expr 0x1 << 15 ]
set AT91C_SUPC_WKUPT0     [expr 0x1 << 16 ]
set AT91C_SUPC_WKUPT1     [expr 0x1 << 17 ]
set AT91C_SUPC_WKUPT2     [expr 0x1 << 18 ]
set AT91C_SUPC_WKUPT3     [expr 0x1 << 19 ]
set AT91C_SUPC_WKUPT4     [expr 0x1 << 20 ]
set AT91C_SUPC_WKUPT5     [expr 0x1 << 21 ]
set AT91C_SUPC_WKUPT6     [expr 0x1 << 22 ]
set AT91C_SUPC_WKUPT7     [expr 0x1 << 23 ]
set AT91C_SUPC_WKUPT8     [expr 0x1 << 24 ]
set AT91C_SUPC_WKUPT9     [expr 0x1 << 25 ]
set AT91C_SUPC_WKUPT10    [expr 0x1 << 26 ]
set AT91C_SUPC_WKUPT11    [expr 0x1 << 27 ]
set AT91C_SUPC_WKUPT12    [expr 0x1 << 28 ]
set AT91C_SUPC_WKUPT13    [expr 0x1 << 29 ]
set AT91C_SUPC_WKUPT14    [expr 0x1 << 30 ]
set AT91C_SUPC_WKUPT15    [expr 0x1 << 31 ]
# -------- SUPC_SR : (SUPC Offset: 0x14) Status Register -------- 
set AT91C_SUPC_FWUPS      [expr 0x1 <<  0 ]
set AT91C_SUPC_WKUPS      [expr 0x1 <<  1 ]
set AT91C_SUPC_BODWS      [expr 0x1 <<  2 ]
set AT91C_SUPC_VRRSTS     [expr 0x1 <<  3 ]
set AT91C_SUPC_BODRSTS    [expr 0x1 <<  4 ]
set AT91C_SUPC_BODS       [expr 0x1 <<  5 ]
set AT91C_SUPC_BROWNOUT   [expr 0x1 <<  6 ]
set AT91C_SUPC_OSCSEL     [expr 0x1 <<  7 ]
set AT91C_SUPC_LCDS       [expr 0x1 <<  8 ]
set AT91C_SUPC_GPBRS      [expr 0x1 <<  9 ]
set AT91C_SUPC_RTS        [expr 0x1 << 10 ]
set AT91C_SUPC_FLASHS     [expr 0x1 << 11 ]
set AT91C_SUPC_FWUPIS     [expr 0x1 << 12 ]
set AT91C_SUPC_WKUPIS0    [expr 0x1 << 16 ]
set AT91C_SUPC_WKUPIS1    [expr 0x1 << 17 ]
set AT91C_SUPC_WKUPIS2    [expr 0x1 << 18 ]
set AT91C_SUPC_WKUPIS3    [expr 0x1 << 19 ]
set AT91C_SUPC_WKUPIS4    [expr 0x1 << 20 ]
set AT91C_SUPC_WKUPIS5    [expr 0x1 << 21 ]
set AT91C_SUPC_WKUPIS6    [expr 0x1 << 22 ]
set AT91C_SUPC_WKUPIS7    [expr 0x1 << 23 ]
set AT91C_SUPC_WKUPIS8    [expr 0x1 << 24 ]
set AT91C_SUPC_WKUPIS9    [expr 0x1 << 25 ]
set AT91C_SUPC_WKUPIS10   [expr 0x1 << 26 ]
set AT91C_SUPC_WKUPIS11   [expr 0x1 << 27 ]
set AT91C_SUPC_WKUPIS12   [expr 0x1 << 28 ]
set AT91C_SUPC_WKUPIS13   [expr 0x1 << 29 ]
set AT91C_SUPC_WKUPIS14   [expr 0x1 << 30 ]
set AT91C_SUPC_WKUPIS15   [expr 0x1 << 31 ]
# -------- SUPC_FWUTR : (SUPC Offset: 0x18) Flash Wake Up Timer Register -------- 
set AT91C_SUPC_FWUT       [expr 0x3FF <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface
# *****************************************************************************
# -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- 
set AT91C_RTTC_RTPRES     [expr 0xFFFF <<  0 ]
set AT91C_RTTC_ALMIEN     [expr 0x1 << 16 ]
set AT91C_RTTC_RTTINCIEN  [expr 0x1 << 17 ]
set AT91C_RTTC_RTTRST     [expr 0x1 << 18 ]
# -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- 
set AT91C_RTTC_ALMV       [expr 0x0 <<  0 ]
# -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- 
set AT91C_RTTC_CRTV       [expr 0x0 <<  0 ]
# -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- 
set AT91C_RTTC_ALMS       [expr 0x1 <<  0 ]
set AT91C_RTTC_RTTINC     [expr 0x1 <<  1 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface
# *****************************************************************************
# -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- 
set AT91C_WDTC_WDRSTT     [expr 0x1 <<  0 ]
set AT91C_WDTC_KEY        [expr 0xFF << 24 ]
# -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- 
set AT91C_WDTC_WDV        [expr 0xFFF <<  0 ]
set AT91C_WDTC_WDFIEN     [expr 0x1 << 12 ]
set AT91C_WDTC_WDRSTEN    [expr 0x1 << 13 ]
set AT91C_WDTC_WDRPROC    [expr 0x1 << 14 ]
set AT91C_WDTC_WDDIS      [expr 0x1 << 15 ]
set AT91C_WDTC_WDD        [expr 0xFFF << 16 ]
set AT91C_WDTC_WDDBGHLT   [expr 0x1 << 28 ]
set AT91C_WDTC_WDIDLEHLT  [expr 0x1 << 29 ]
# -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- 
set AT91C_WDTC_WDUNF      [expr 0x1 <<  0 ]
set AT91C_WDTC_WDERR      [expr 0x1 <<  1 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Real-time Clock Alarm and Parallel Load Interface
# *****************************************************************************
# -------- RTC_CR : (RTC Offset: 0x0) RTC Control Register -------- 
set AT91C_RTC_UPDTIM      [expr 0x1 <<  0 ]
set AT91C_RTC_UPDCAL      [expr 0x1 <<  1 ]
set AT91C_RTC_TIMEVSEL    [expr 0x3 <<  8 ]
set 	AT91C_RTC_TIMEVSEL_MINUTE               [expr 0x0 <<  8 ]
set 	AT91C_RTC_TIMEVSEL_HOUR                 [expr 0x1 <<  8 ]
set 	AT91C_RTC_TIMEVSEL_DAY24                [expr 0x2 <<  8 ]
set 	AT91C_RTC_TIMEVSEL_DAY12                [expr 0x3 <<  8 ]
set AT91C_RTC_CALEVSEL    [expr 0x3 << 16 ]
set 	AT91C_RTC_CALEVSEL_WEEK                 [expr 0x0 << 16 ]
set 	AT91C_RTC_CALEVSEL_MONTH                [expr 0x1 << 16 ]
set 	AT91C_RTC_CALEVSEL_YEAR                 [expr 0x2 << 16 ]
# -------- RTC_MR : (RTC Offset: 0x4) RTC Mode Register -------- 
set AT91C_RTC_HRMOD       [expr 0x1 <<  0 ]
# -------- RTC_TIMR : (RTC Offset: 0x8) RTC Time Register -------- 
set AT91C_RTC_SEC         [expr 0x7F <<  0 ]
set AT91C_RTC_MIN         [expr 0x7F <<  8 ]
set AT91C_RTC_HOUR        [expr 0x3F << 16 ]
set AT91C_RTC_AMPM        [expr 0x1 << 22 ]
# -------- RTC_CALR : (RTC Offset: 0xc) RTC Calendar Register -------- 
set AT91C_RTC_CENT        [expr 0x3F <<  0 ]
set AT91C_RTC_YEAR        [expr 0xFF <<  8 ]
set AT91C_RTC_MONTH       [expr 0x1F << 16 ]
set AT91C_RTC_DAY         [expr 0x7 << 21 ]
set AT91C_RTC_DATE        [expr 0x3F << 24 ]
# -------- RTC_TIMALR : (RTC Offset: 0x10) RTC Time Alarm Register -------- 
set AT91C_RTC_SEC         [expr 0x7F <<  0 ]
set AT91C_RTC_SECEN       [expr 0x1 <<  7 ]
set AT91C_RTC_MIN         [expr 0x7F <<  8 ]
set AT91C_RTC_MINEN       [expr 0x1 << 15 ]
set AT91C_RTC_HOUR        [expr 0x3F << 16 ]
set AT91C_RTC_AMPM        [expr 0x1 << 22 ]
set AT91C_RTC_HOUREN      [expr 0x1 << 23 ]
# -------- RTC_CALALR : (RTC Offset: 0x14) RTC Calendar Alarm Register -------- 
set AT91C_RTC_MONTH       [expr 0x1F << 16 ]
set AT91C_RTC_MONTHEN     [expr 0x1 << 23 ]
set AT91C_RTC_DATE        [expr 0x3F << 24 ]
set AT91C_RTC_DATEEN      [expr 0x1 << 31 ]
# -------- RTC_SR : (RTC Offset: 0x18) RTC Status Register -------- 
set AT91C_RTC_ACKUPD      [expr 0x1 <<  0 ]
set AT91C_RTC_ALARM       [expr 0x1 <<  1 ]
set AT91C_RTC_SECEV       [expr 0x1 <<  2 ]
set AT91C_RTC_TIMEV       [expr 0x1 <<  3 ]
set AT91C_RTC_CALEV       [expr 0x1 <<  4 ]
# -------- RTC_SCCR : (RTC Offset: 0x1c) RTC Status Clear Command Register -------- 
set AT91C_RTC_ACKUPD      [expr 0x1 <<  0 ]
set AT91C_RTC_ALARM       [expr 0x1 <<  1 ]
set AT91C_RTC_SECEV       [expr 0x1 <<  2 ]
set AT91C_RTC_TIMEV       [expr 0x1 <<  3 ]
set AT91C_RTC_CALEV       [expr 0x1 <<  4 ]
# -------- RTC_IER : (RTC Offset: 0x20) RTC Interrupt Enable Register -------- 
set AT91C_RTC_ACKUPD      [expr 0x1 <<  0 ]
set AT91C_RTC_ALARM       [expr 0x1 <<  1 ]
set AT91C_RTC_SECEV       [expr 0x1 <<  2 ]
set AT91C_RTC_TIMEV       [expr 0x1 <<  3 ]
set AT91C_RTC_CALEV       [expr 0x1 <<  4 ]
# -------- RTC_IDR : (RTC Offset: 0x24) RTC Interrupt Disable Register -------- 
set AT91C_RTC_ACKUPD      [expr 0x1 <<  0 ]
set AT91C_RTC_ALARM       [expr 0x1 <<  1 ]
set AT91C_RTC_SECEV       [expr 0x1 <<  2 ]
set AT91C_RTC_TIMEV       [expr 0x1 <<  3 ]
set AT91C_RTC_CALEV       [expr 0x1 <<  4 ]
# -------- RTC_IMR : (RTC Offset: 0x28) RTC Interrupt Mask Register -------- 
set AT91C_RTC_ACKUPD      [expr 0x1 <<  0 ]
set AT91C_RTC_ALARM       [expr 0x1 <<  1 ]
set AT91C_RTC_SECEV       [expr 0x1 <<  2 ]
set AT91C_RTC_TIMEV       [expr 0x1 <<  3 ]
set AT91C_RTC_CALEV       [expr 0x1 <<  4 ]
# -------- RTC_VER : (RTC Offset: 0x2c) RTC Valid Entry Register -------- 
set AT91C_RTC_NVTIM       [expr 0x1 <<  0 ]
set AT91C_RTC_NVCAL       [expr 0x1 <<  1 ]
set AT91C_RTC_NVTIMALR    [expr 0x1 <<  2 ]
set AT91C_RTC_NVCALALR    [expr 0x1 <<  3 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Analog to Digital Convertor
# *****************************************************************************
# -------- ADC_CR : (ADC Offset: 0x0) ADC Control Register -------- 
set AT91C_ADC_SWRST       [expr 0x1 <<  0 ]
set AT91C_ADC_START       [expr 0x1 <<  1 ]
# -------- ADC_MR : (ADC Offset: 0x4) ADC Mode Register -------- 
set AT91C_ADC_TRGEN       [expr 0x1 <<  0 ]
set 	AT91C_ADC_TRGEN_DIS                  0x0
set 	AT91C_ADC_TRGEN_EN                   0x1
set AT91C_ADC_TRGSEL      [expr 0x7 <<  1 ]
set 	AT91C_ADC_TRGSEL_EXT                  [expr 0x0 <<  1 ]
set 	AT91C_ADC_TRGSEL_TIOA0                [expr 0x1 <<  1 ]
set 	AT91C_ADC_TRGSEL_TIOA1                [expr 0x2 <<  1 ]
set 	AT91C_ADC_TRGSEL_TIOA2                [expr 0x3 <<  1 ]
set 	AT91C_ADC_TRGSEL_PWM0_TRIG            [expr 0x4 <<  1 ]
set 	AT91C_ADC_TRGSEL_PWM1_TRIG            [expr 0x5 <<  1 ]
set 	AT91C_ADC_TRGSEL_RESERVED             [expr 0x6 <<  1 ]
set AT91C_ADC_LOWRES      [expr 0x1 <<  4 ]
set 	AT91C_ADC_LOWRES_10_BIT               [expr 0x0 <<  4 ]
set 	AT91C_ADC_LOWRES_8_BIT                [expr 0x1 <<  4 ]
set AT91C_ADC_SLEEP       [expr 0x1 <<  5 ]
set 	AT91C_ADC_SLEEP_NORMAL_MODE          [expr 0x0 <<  5 ]
set 	AT91C_ADC_SLEEP_MODE                 [expr 0x1 <<  5 ]
set AT91C_ADC_PRESCAL     [expr 0x3F <<  8 ]
set AT91C_ADC_STARTUP     [expr 0x1F << 16 ]
set AT91C_ADC_SHTIM       [expr 0xF << 24 ]
# -------- 	ADC_CHER : (ADC Offset: 0x10) ADC Channel Enable Register -------- 
set AT91C_ADC_CH0         [expr 0x1 <<  0 ]
set AT91C_ADC_CH1         [expr 0x1 <<  1 ]
set AT91C_ADC_CH2         [expr 0x1 <<  2 ]
set AT91C_ADC_CH3         [expr 0x1 <<  3 ]
set AT91C_ADC_CH4         [expr 0x1 <<  4 ]
set AT91C_ADC_CH5         [expr 0x1 <<  5 ]
set AT91C_ADC_CH6         [expr 0x1 <<  6 ]
set AT91C_ADC_CH7         [expr 0x1 <<  7 ]
set AT91C_ADC_CH8         [expr 0x1 <<  8 ]
set AT91C_ADC_CH9         [expr 0x1 <<  9 ]
set AT91C_ADC_CH10        [expr 0x1 << 10 ]
set AT91C_ADC_CH11        [expr 0x1 << 11 ]
set AT91C_ADC_CH12        [expr 0x1 << 12 ]
set AT91C_ADC_CH13        [expr 0x1 << 13 ]
set AT91C_ADC_CH14        [expr 0x1 << 14 ]
set AT91C_ADC_CH15        [expr 0x1 << 15 ]
# -------- 	ADC_CHDR : (ADC Offset: 0x14) ADC Channel Disable Register -------- 
set AT91C_ADC_CH0         [expr 0x1 <<  0 ]
set AT91C_ADC_CH1         [expr 0x1 <<  1 ]
set AT91C_ADC_CH2         [expr 0x1 <<  2 ]
set AT91C_ADC_CH3         [expr 0x1 <<  3 ]
set AT91C_ADC_CH4         [expr 0x1 <<  4 ]
set AT91C_ADC_CH5         [expr 0x1 <<  5 ]
set AT91C_ADC_CH6         [expr 0x1 <<  6 ]
set AT91C_ADC_CH7         [expr 0x1 <<  7 ]
set AT91C_ADC_CH8         [expr 0x1 <<  8 ]
set AT91C_ADC_CH9         [expr 0x1 <<  9 ]
set AT91C_ADC_CH10        [expr 0x1 << 10 ]
set AT91C_ADC_CH11        [expr 0x1 << 11 ]
set AT91C_ADC_CH12        [expr 0x1 << 12 ]
set AT91C_ADC_CH13        [expr 0x1 << 13 ]
set AT91C_ADC_CH14        [expr 0x1 << 14 ]
set AT91C_ADC_CH15        [expr 0x1 << 15 ]
# -------- 	ADC_CHSR : (ADC Offset: 0x18) ADC Channel Status Register -------- 
set AT91C_ADC_CH0         [expr 0x1 <<  0 ]
set AT91C_ADC_CH1         [expr 0x1 <<  1 ]
set AT91C_ADC_CH2         [expr 0x1 <<  2 ]
set AT91C_ADC_CH3         [expr 0x1 <<  3 ]
set AT91C_ADC_CH4         [expr 0x1 <<  4 ]
set AT91C_ADC_CH5         [expr 0x1 <<  5 ]
set AT91C_ADC_CH6         [expr 0x1 <<  6 ]
set AT91C_ADC_CH7         [expr 0x1 <<  7 ]
set AT91C_ADC_CH8         [expr 0x1 <<  8 ]
set AT91C_ADC_CH9         [expr 0x1 <<  9 ]
set AT91C_ADC_CH10        [expr 0x1 << 10 ]
set AT91C_ADC_CH11        [expr 0x1 << 11 ]
set AT91C_ADC_CH12        [expr 0x1 << 12 ]
set AT91C_ADC_CH13        [expr 0x1 << 13 ]
set AT91C_ADC_CH14        [expr 0x1 << 14 ]
set AT91C_ADC_CH15        [expr 0x1 << 15 ]
# -------- ADC_LCDR : (ADC Offset: 0x20) ADC Last Converted Data Register -------- 
set AT91C_ADC_LDATA       [expr 0x3FF <<  0 ]
# -------- ADC_IER : (ADC Offset: 0x24) ADC Interrupt Enable Register -------- 
set AT91C_ADC_EOC0        [expr 0x1 <<  0 ]
set AT91C_ADC_EOC1        [expr 0x1 <<  1 ]
set AT91C_ADC_EOC2        [expr 0x1 <<  2 ]
set AT91C_ADC_EOC3        [expr 0x1 <<  3 ]
set AT91C_ADC_EOC4        [expr 0x1 <<  4 ]
set AT91C_ADC_EOC5        [expr 0x1 <<  5 ]
set AT91C_ADC_EOC6        [expr 0x1 <<  6 ]
set AT91C_ADC_EOC7        [expr 0x1 <<  7 ]
set AT91C_ADC_EOC8        [expr 0x1 <<  8 ]
set AT91C_ADC_EOC9        [expr 0x1 <<  9 ]
set AT91C_ADC_EOC10       [expr 0x1 << 10 ]
set AT91C_ADC_EOC11       [expr 0x1 << 11 ]
set AT91C_ADC_EOC12       [expr 0x1 << 12 ]
set AT91C_ADC_EOC13       [expr 0x1 << 13 ]
set AT91C_ADC_EOC14       [expr 0x1 << 14 ]
set AT91C_ADC_EOC15       [expr 0x1 << 15 ]
set AT91C_ADC_DRDY        [expr 0x1 << 24 ]
set AT91C_ADC_GOVRE       [expr 0x1 << 25 ]
set AT91C_ADC_ENDRX       [expr 0x1 << 27 ]
set AT91C_ADC_RXBUFF      [expr 0x1 << 28 ]
# -------- ADC_IDR : (ADC Offset: 0x28) ADC Interrupt Disable Register -------- 
set AT91C_ADC_EOC0        [expr 0x1 <<  0 ]
set AT91C_ADC_EOC1        [expr 0x1 <<  1 ]
set AT91C_ADC_EOC2        [expr 0x1 <<  2 ]
set AT91C_ADC_EOC3        [expr 0x1 <<  3 ]
set AT91C_ADC_EOC4        [expr 0x1 <<  4 ]
set AT91C_ADC_EOC5        [expr 0x1 <<  5 ]
set AT91C_ADC_EOC6        [expr 0x1 <<  6 ]
set AT91C_ADC_EOC7        [expr 0x1 <<  7 ]
set AT91C_ADC_EOC8        [expr 0x1 <<  8 ]
set AT91C_ADC_EOC9        [expr 0x1 <<  9 ]
set AT91C_ADC_EOC10       [expr 0x1 << 10 ]
set AT91C_ADC_EOC11       [expr 0x1 << 11 ]
set AT91C_ADC_EOC12       [expr 0x1 << 12 ]
set AT91C_ADC_EOC13       [expr 0x1 << 13 ]
set AT91C_ADC_EOC14       [expr 0x1 << 14 ]
set AT91C_ADC_EOC15       [expr 0x1 << 15 ]
set AT91C_ADC_DRDY        [expr 0x1 << 24 ]
set AT91C_ADC_GOVRE       [expr 0x1 << 25 ]
set AT91C_ADC_ENDRX       [expr 0x1 << 27 ]
set AT91C_ADC_RXBUFF      [expr 0x1 << 28 ]
# -------- ADC_IMR : (ADC Offset: 0x2c) ADC Interrupt Mask Register -------- 
set AT91C_ADC_EOC0        [expr 0x1 <<  0 ]
set AT91C_ADC_EOC1        [expr 0x1 <<  1 ]
set AT91C_ADC_EOC2        [expr 0x1 <<  2 ]
set AT91C_ADC_EOC3        [expr 0x1 <<  3 ]
set AT91C_ADC_EOC4        [expr 0x1 <<  4 ]
set AT91C_ADC_EOC5        [expr 0x1 <<  5 ]
set AT91C_ADC_EOC6        [expr 0x1 <<  6 ]
set AT91C_ADC_EOC7        [expr 0x1 <<  7 ]
set AT91C_ADC_EOC8        [expr 0x1 <<  8 ]
set AT91C_ADC_EOC9        [expr 0x1 <<  9 ]
set AT91C_ADC_EOC10       [expr 0x1 << 10 ]
set AT91C_ADC_EOC11       [expr 0x1 << 11 ]
set AT91C_ADC_EOC12       [expr 0x1 << 12 ]
set AT91C_ADC_EOC13       [expr 0x1 << 13 ]
set AT91C_ADC_EOC14       [expr 0x1 << 14 ]
set AT91C_ADC_EOC15       [expr 0x1 << 15 ]
set AT91C_ADC_DRDY        [expr 0x1 << 24 ]
set AT91C_ADC_GOVRE       [expr 0x1 << 25 ]
set AT91C_ADC_ENDRX       [expr 0x1 << 27 ]
set AT91C_ADC_RXBUFF      [expr 0x1 << 28 ]
# -------- ADC_SR : (ADC Offset: 0x30) ADC Status Register -------- 
set AT91C_ADC_EOC0        [expr 0x1 <<  0 ]
set AT91C_ADC_EOC1        [expr 0x1 <<  1 ]
set AT91C_ADC_EOC2        [expr 0x1 <<  2 ]
set AT91C_ADC_EOC3        [expr 0x1 <<  3 ]
set AT91C_ADC_EOC4        [expr 0x1 <<  4 ]
set AT91C_ADC_EOC5        [expr 0x1 <<  5 ]
set AT91C_ADC_EOC6        [expr 0x1 <<  6 ]
set AT91C_ADC_EOC7        [expr 0x1 <<  7 ]
set AT91C_ADC_EOC8        [expr 0x1 <<  8 ]
set AT91C_ADC_EOC9        [expr 0x1 <<  9 ]
set AT91C_ADC_EOC10       [expr 0x1 << 10 ]
set AT91C_ADC_EOC11       [expr 0x1 << 11 ]
set AT91C_ADC_EOC12       [expr 0x1 << 12 ]
set AT91C_ADC_EOC13       [expr 0x1 << 13 ]
set AT91C_ADC_EOC14       [expr 0x1 << 14 ]
set AT91C_ADC_EOC15       [expr 0x1 << 15 ]
set AT91C_ADC_DRDY        [expr 0x1 << 24 ]
set AT91C_ADC_GOVRE       [expr 0x1 << 25 ]
set AT91C_ADC_ENDRX       [expr 0x1 << 27 ]
set AT91C_ADC_RXBUFF      [expr 0x1 << 28 ]
# -------- ADC_OVR : (ADC Offset: 0x3c)  -------- 
set AT91C_ADC_OVRE2       [expr 0x1 << 10 ]
set AT91C_ADC_OVRE3       [expr 0x1 << 11 ]
set AT91C_ADC_OVRE4       [expr 0x1 << 12 ]
set AT91C_ADC_OVRE5       [expr 0x1 << 13 ]
# -------- ADC_CWR : (ADC Offset: 0x40)  -------- 
set AT91C_ADC_OVRE2       [expr 0x1 << 10 ]
set AT91C_ADC_OVRE3       [expr 0x1 << 11 ]
set AT91C_ADC_OVRE4       [expr 0x1 << 12 ]
set AT91C_ADC_OVRE5       [expr 0x1 << 13 ]
# -------- ADC_CWSR : (ADC Offset: 0x44)  -------- 
set AT91C_ADC_OVRE2       [expr 0x1 << 10 ]
set AT91C_ADC_OVRE3       [expr 0x1 << 11 ]
set AT91C_ADC_OVRE4       [expr 0x1 << 12 ]
set AT91C_ADC_OVRE5       [expr 0x1 << 13 ]
# -------- ADC_CGR : (ADC Offset: 0x48)  -------- 
set AT91C_ADC_OVRE2       [expr 0x1 << 10 ]
set AT91C_ADC_OVRE3       [expr 0x1 << 11 ]
set AT91C_ADC_OVRE4       [expr 0x1 << 12 ]
set AT91C_ADC_OVRE5       [expr 0x1 << 13 ]
# -------- ADC_COR : (ADC Offset: 0x4c)  -------- 
set AT91C_ADC_OVRE2       [expr 0x1 << 10 ]
set AT91C_ADC_OVRE3       [expr 0x1 << 11 ]
set AT91C_ADC_OVRE4       [expr 0x1 << 12 ]
set AT91C_ADC_OVRE5       [expr 0x1 << 13 ]
# -------- ADC_CDR0 : (ADC Offset: 0x50) ADC Channel Data Register 0 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR1 : (ADC Offset: 0x54) ADC Channel Data Register 1 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR2 : (ADC Offset: 0x58) ADC Channel Data Register 2 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR3 : (ADC Offset: 0x5c) ADC Channel Data Register 3 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR4 : (ADC Offset: 0x60) ADC Channel Data Register 4 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR5 : (ADC Offset: 0x64) ADC Channel Data Register 5 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR6 : (ADC Offset: 0x68) ADC Channel Data Register 6 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR7 : (ADC Offset: 0x6c) ADC Channel Data Register 7 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR8 : (ADC Offset: 0x70) ADC Channel Data Register 8 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR9 : (ADC Offset: 0x74) ADC Channel Data Register 9 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR10 : (ADC Offset: 0x78) ADC Channel Data Register 10 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR11 : (ADC Offset: 0x7c) ADC Channel Data Register 11 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR12 : (ADC Offset: 0x80) ADC Channel Data Register 12 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR13 : (ADC Offset: 0x84) ADC Channel Data Register 13 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR14 : (ADC Offset: 0x88) ADC Channel Data Register 14 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_CDR15 : (ADC Offset: 0x8c) ADC Channel Data Register 15 -------- 
set AT91C_ADC_DATA        [expr 0x3FF <<  0 ]
# -------- ADC_VER : (ADC Offset: 0xfc) ADC VER -------- 
set AT91C_ADC_VER         [expr 0xF <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Digital to Analog Convertor
# *****************************************************************************
# -------- DAC_CR : (DAC Offset: 0x0) Control Register -------- 
set AT91C_DAC_SWRST       [expr 0x1 <<  0 ]
# -------- DAC_MR : (DAC Offset: 0x4) Mode Register -------- 
set AT91C_DAC_TRGEN       [expr 0x1 <<  0 ]
set AT91C_DAC_TRGSEL      [expr 0x7 <<  1 ]
set 	AT91C_DAC_TRGSEL_EXTRG0               [expr 0x0 <<  1 ]
set 	AT91C_DAC_TRGSEL_EXTRG1               [expr 0x1 <<  1 ]
set 	AT91C_DAC_TRGSEL_EXTRG2               [expr 0x2 <<  1 ]
set 	AT91C_DAC_TRGSEL_EXTRG3               [expr 0x3 <<  1 ]
set 	AT91C_DAC_TRGSEL_EXTRG4               [expr 0x4 <<  1 ]
set 	AT91C_DAC_TRGSEL_EXTRG5               [expr 0x5 <<  1 ]
set 	AT91C_DAC_TRGSEL_EXTRG6               [expr 0x6 <<  1 ]
set AT91C_DAC_WORD        [expr 0x1 <<  4 ]
set AT91C_DAC_SLEEP       [expr 0x1 <<  5 ]
set AT91C_DAC_FASTW       [expr 0x1 <<  6 ]
set AT91C_DAC_REFRESH     [expr 0xFF <<  8 ]
set AT91C_DAC_USER_SEL    [expr 0x3 << 16 ]
set 	AT91C_DAC_USER_SEL_CH0                  [expr 0x0 << 16 ]
set 	AT91C_DAC_USER_SEL_CH1                  [expr 0x1 << 16 ]
set 	AT91C_DAC_USER_SEL_CH2                  [expr 0x2 << 16 ]
set AT91C_DAC_TAG         [expr 0x1 << 20 ]
set AT91C_DAC_MAXSPEED    [expr 0x1 << 21 ]
set AT91C_DAC_STARTUP     [expr 0x3F << 24 ]
# -------- DAC_CHER : (DAC Offset: 0x10) Channel Enable Register -------- 
set AT91C_DAC_CH0         [expr 0x1 <<  0 ]
set AT91C_DAC_CH1         [expr 0x1 <<  1 ]
set AT91C_DAC_CH2         [expr 0x1 <<  2 ]
# -------- DAC_CHDR : (DAC Offset: 0x14) Channel Disable Register -------- 
set AT91C_DAC_CH0         [expr 0x1 <<  0 ]
set AT91C_DAC_CH1         [expr 0x1 <<  1 ]
set AT91C_DAC_CH2         [expr 0x1 <<  2 ]
# -------- DAC_CHSR : (DAC Offset: 0x18) Channel Status Register -------- 
set AT91C_DAC_CH0         [expr 0x1 <<  0 ]
set AT91C_DAC_CH1         [expr 0x1 <<  1 ]
set AT91C_DAC_CH2         [expr 0x1 <<  2 ]
# -------- DAC_CDR : (DAC Offset: 0x20) Conversion Data Register -------- 
set AT91C_DAC_DATA        [expr 0x0 <<  0 ]
# -------- DAC_IER : (DAC Offset: 0x24) DAC Interrupt Enable -------- 
set AT91C_DAC_TXRDY       [expr 0x1 <<  0 ]
set AT91C_DAC_EOC         [expr 0x1 <<  1 ]
set AT91C_DAC_TXDMAEND    [expr 0x1 <<  2 ]
set AT91C_DAC_TXBUFEMPT   [expr 0x1 <<  3 ]
# -------- DAC_IDR : (DAC Offset: 0x28) DAC Interrupt Disable -------- 
set AT91C_DAC_TXRDY       [expr 0x1 <<  0 ]
set AT91C_DAC_EOC         [expr 0x1 <<  1 ]
set AT91C_DAC_TXDMAEND    [expr 0x1 <<  2 ]
set AT91C_DAC_TXBUFEMPT   [expr 0x1 <<  3 ]
# -------- DAC_IMR : (DAC Offset: 0x2c) DAC Interrupt Mask -------- 
set AT91C_DAC_TXRDY       [expr 0x1 <<  0 ]
set AT91C_DAC_EOC         [expr 0x1 <<  1 ]
set AT91C_DAC_TXDMAEND    [expr 0x1 <<  2 ]
set AT91C_DAC_TXBUFEMPT   [expr 0x1 <<  3 ]
# -------- DAC_ISR : (DAC Offset: 0x30) DAC Interrupt Status -------- 
set AT91C_DAC_TXRDY       [expr 0x1 <<  0 ]
set AT91C_DAC_EOC         [expr 0x1 <<  1 ]
set AT91C_DAC_TXDMAEND    [expr 0x1 <<  2 ]
set AT91C_DAC_TXBUFEMPT   [expr 0x1 <<  3 ]
# -------- DAC_ACR : (DAC Offset: 0x94) Analog Current Register -------- 
set AT91C_DAC_IBCTL       [expr 0x1FF <<  0 ]
# -------- DAC_WPMR : (DAC Offset: 0xe4) Write Protect Mode Register -------- 
set AT91C_DAC_WPEN        [expr 0x1 <<  0 ]
set AT91C_DAC_WPKEY       [expr 0xFFFFFF <<  8 ]
# -------- DAC_WPSR : (DAC Offset: 0xe8) Write Protect Status Register -------- 
set AT91C_DAC_WPROTERR    [expr 0x1 <<  0 ]
set AT91C_DAC_WPROTADDR   [expr 0xFF <<  8 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Digital to Analog Convertor
# *****************************************************************************
# -------- ACC_IER : (ACC Offset: 0x24) Data Ready for Conversion Interrupt Enable -------- 
set AT91C_ACC_DATRDY      [expr 0x1 <<  0 ]
# -------- ACC_IDR : (ACC Offset: 0x28) Data Ready for Conversion Interrupt Disable -------- 
set AT91C_ACC_DATRDY      [expr 0x1 <<  0 ]
# -------- ACC_IMR : (ACC Offset: 0x2c) Data Ready for Conversion Interrupt Mask -------- 
set AT91C_ACC_DATRDY      [expr 0x1 <<  0 ]
# -------- ACC_ISR : (ACC Offset: 0x30) Status Register -------- 
set AT91C_ACC_DATRDY      [expr 0x1 <<  0 ]
# -------- ACC_VER : (ACC Offset: 0xfc) ACC VER -------- 
set AT91C_ACC_VER         [expr 0xF <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Context Based Direct Memory Access Controller Interface
# *****************************************************************************
# -------- HCBDMA_CBDSCR : (HCBDMA Offset: 0x0) CB DMA Descriptor Base Register -------- 
set AT91C_HCBDMA_DSCR     [expr 0x0 <<  0 ]
# -------- HCBDMA_CBNXTEN : (HCBDMA Offset: 0x4) Next Descriptor Enable Register -------- 
set AT91C_HCBDMA_NXTID0   [expr 0x1 <<  0 ]
set AT91C_HCBDMA_NXTID1   [expr 0x1 <<  1 ]
set AT91C_HCBDMA_NXTID2   [expr 0x1 <<  2 ]
set AT91C_HCBDMA_NXTID3   [expr 0x1 <<  3 ]
set AT91C_HCBDMA_NXTID4   [expr 0x1 <<  4 ]
set AT91C_HCBDMA_NXTID5   [expr 0x1 <<  5 ]
set AT91C_HCBDMA_NXTID6   [expr 0x1 <<  6 ]
set AT91C_HCBDMA_NXTID7   [expr 0x1 <<  7 ]
set AT91C_HCBDMA_NXTID8   [expr 0x1 <<  8 ]
set AT91C_HCBDMA_NXTID9   [expr 0x1 <<  9 ]
set AT91C_HCBDMA_NXTID10  [expr 0x1 << 10 ]
set AT91C_HCBDMA_NXTID11  [expr 0x1 << 11 ]
set AT91C_HCBDMA_NXTID12  [expr 0x1 << 12 ]
set AT91C_HCBDMA_NXTID13  [expr 0x1 << 13 ]
set AT91C_HCBDMA_NXTID14  [expr 0x1 << 14 ]
set AT91C_HCBDMA_NXTID15  [expr 0x1 << 15 ]
set AT91C_HCBDMA_NXTID16  [expr 0x1 << 16 ]
set AT91C_HCBDMA_NXTID17  [expr 0x1 << 17 ]
set AT91C_HCBDMA_NXTID18  [expr 0x1 << 18 ]
set AT91C_HCBDMA_NXTID19  [expr 0x1 << 19 ]
set AT91C_HCBDMA_NXTID20  [expr 0x1 << 20 ]
set AT91C_HCBDMA_NXTID21  [expr 0x1 << 21 ]
set AT91C_HCBDMA_NXTID22  [expr 0x1 << 22 ]
set AT91C_HCBDMA_NXTID23  [expr 0x1 << 23 ]
set AT91C_HCBDMA_NXTID24  [expr 0x1 << 24 ]
set AT91C_HCBDMA_NXTID25  [expr 0x1 << 25 ]
set AT91C_HCBDMA_NXTID26  [expr 0x1 << 26 ]
set AT91C_HCBDMA_NXTID27  [expr 0x1 << 27 ]
set AT91C_HCBDMA_NXTID28  [expr 0x1 << 28 ]
set AT91C_HCBDMA_NXTID29  [expr 0x1 << 29 ]
set AT91C_HCBDMA_NXTID30  [expr 0x1 << 30 ]
set AT91C_HCBDMA_NXTID31  [expr 0x1 << 31 ]
# -------- HCBDMA_CBEN : (HCBDMA Offset: 0x8) CB DMA Enable Register -------- 
set AT91C_HCBDMA_CBEN0    [expr 0x1 <<  0 ]
set AT91C_HCBDMA_CBEN1    [expr 0x1 <<  1 ]
set AT91C_HCBDMA_CBEN2    [expr 0x1 <<  2 ]
set AT91C_HCBDMA_CBEN3    [expr 0x1 <<  3 ]
set AT91C_HCBDMA_CBEN4    [expr 0x1 <<  4 ]
set AT91C_HCBDMA_CBEN5    [expr 0x1 <<  5 ]
set AT91C_HCBDMA_CBEN6    [expr 0x1 <<  6 ]
set AT91C_HCBDMA_CBEN7    [expr 0x1 <<  7 ]
set AT91C_HCBDMA_CBEN8    [expr 0x1 <<  8 ]
set AT91C_HCBDMA_CBEN9    [expr 0x1 <<  9 ]
set AT91C_HCBDMA_CBEN10   [expr 0x1 << 10 ]
set AT91C_HCBDMA_CBEN11   [expr 0x1 << 11 ]
set AT91C_HCBDMA_CBEN12   [expr 0x1 << 12 ]
set AT91C_HCBDMA_CBEN13   [expr 0x1 << 13 ]
set AT91C_HCBDMA_CBEN14   [expr 0x1 << 14 ]
set AT91C_HCBDMA_CBEN15   [expr 0x1 << 15 ]
set AT91C_HCBDMA_CBEN16   [expr 0x1 << 16 ]
set AT91C_HCBDMA_CBEN17   [expr 0x1 << 17 ]
set AT91C_HCBDMA_CBEN18   [expr 0x1 << 18 ]
set AT91C_HCBDMA_CBEN19   [expr 0x1 << 19 ]
set AT91C_HCBDMA_CBEN20   [expr 0x1 << 20 ]
set AT91C_HCBDMA_CBEN21   [expr 0x1 << 21 ]
set AT91C_HCBDMA_CBEN22   [expr 0x1 << 22 ]
set AT91C_HCBDMA_CBEN23   [expr 0x1 << 23 ]
set AT91C_HCBDMA_CBEN24   [expr 0x1 << 24 ]
set AT91C_HCBDMA_CBEN25   [expr 0x1 << 25 ]
set AT91C_HCBDMA_CBEN26   [expr 0x1 << 26 ]
set AT91C_HCBDMA_CBEN27   [expr 0x1 << 27 ]
set AT91C_HCBDMA_CBEN28   [expr 0x1 << 28 ]
set AT91C_HCBDMA_CBEN29   [expr 0x1 << 29 ]
set AT91C_HCBDMA_CBEN30   [expr 0x1 << 30 ]
set AT91C_HCBDMA_CBEN31   [expr 0x1 << 31 ]
# -------- HCBDMA_CBDIS : (HCBDMA Offset: 0xc) CB DMA Disable Register -------- 
set AT91C_HCBDMA_CBDIS0   [expr 0x1 <<  0 ]
set AT91C_HCBDMA_CBDIS1   [expr 0x1 <<  1 ]
set AT91C_HCBDMA_CBDIS2   [expr 0x1 <<  2 ]
set AT91C_HCBDMA_CBDIS3   [expr 0x1 <<  3 ]
set AT91C_HCBDMA_CBDIS4   [expr 0x1 <<  4 ]
set AT91C_HCBDMA_CBDIS5   [expr 0x1 <<  5 ]
set AT91C_HCBDMA_CBDIS6   [expr 0x1 <<  6 ]
set AT91C_HCBDMA_CBDIS7   [expr 0x1 <<  7 ]
set AT91C_HCBDMA_CBDIS8   [expr 0x1 <<  8 ]
set AT91C_HCBDMA_CBDIS9   [expr 0x1 <<  9 ]
set AT91C_HCBDMA_CBDIS10  [expr 0x1 << 10 ]
set AT91C_HCBDMA_CBDIS11  [expr 0x1 << 11 ]
set AT91C_HCBDMA_CBDIS12  [expr 0x1 << 12 ]
set AT91C_HCBDMA_CBDIS13  [expr 0x1 << 13 ]
set AT91C_HCBDMA_CBDIS14  [expr 0x1 << 14 ]
set AT91C_HCBDMA_CBDIS15  [expr 0x1 << 15 ]
set AT91C_HCBDMA_CBDIS16  [expr 0x1 << 16 ]
set AT91C_HCBDMA_CBDIS17  [expr 0x1 << 17 ]
set AT91C_HCBDMA_CBDIS18  [expr 0x1 << 18 ]
set AT91C_HCBDMA_CBDIS19  [expr 0x1 << 19 ]
set AT91C_HCBDMA_CBDIS20  [expr 0x1 << 20 ]
set AT91C_HCBDMA_CBDIS21  [expr 0x1 << 21 ]
set AT91C_HCBDMA_CBDIS22  [expr 0x1 << 22 ]
set AT91C_HCBDMA_CBDIS23  [expr 0x1 << 23 ]
set AT91C_HCBDMA_CBDIS24  [expr 0x1 << 24 ]
set AT91C_HCBDMA_CBDIS25  [expr 0x1 << 25 ]
set AT91C_HCBDMA_CBDIS26  [expr 0x1 << 26 ]
set AT91C_HCBDMA_CBDIS27  [expr 0x1 << 27 ]
set AT91C_HCBDMA_CBDIS28  [expr 0x1 << 28 ]
set AT91C_HCBDMA_CBDIS29  [expr 0x1 << 29 ]
set AT91C_HCBDMA_CBDIS30  [expr 0x1 << 30 ]
set AT91C_HCBDMA_CBDIS31  [expr 0x1 << 31 ]
# -------- HCBDMA_CBSR : (HCBDMA Offset: 0x10) CB DMA Status Register -------- 
set AT91C_HCBDMA_CBSR0    [expr 0x1 <<  0 ]
set AT91C_HCBDMA_CBSR1    [expr 0x1 <<  1 ]
set AT91C_HCBDMA_CBSR2    [expr 0x1 <<  2 ]
set AT91C_HCBDMA_CBSR3    [expr 0x1 <<  3 ]
set AT91C_HCBDMA_CBSR4    [expr 0x1 <<  4 ]
set AT91C_HCBDMA_CBSR5    [expr 0x1 <<  5 ]
set AT91C_HCBDMA_CBSR6    [expr 0x1 <<  6 ]
set AT91C_HCBDMA_CBSR7    [expr 0x1 <<  7 ]
set AT91C_HCBDMA_CBSR8    [expr 0x1 <<  8 ]
set AT91C_HCBDMA_CBSR9    [expr 0x1 <<  9 ]
set AT91C_HCBDMA_CBSR10   [expr 0x1 << 10 ]
set AT91C_HCBDMA_CBSR11   [expr 0x1 << 11 ]
set AT91C_HCBDMA_CBSR12   [expr 0x1 << 12 ]
set AT91C_HCBDMA_CBSR13   [expr 0x1 << 13 ]
set AT91C_HCBDMA_CBSR14   [expr 0x1 << 14 ]
set AT91C_HCBDMA_CBSR15   [expr 0x1 << 15 ]
set AT91C_HCBDMA_CBSR16   [expr 0x1 << 16 ]
set AT91C_HCBDMA_CBSR17   [expr 0x1 << 17 ]
set AT91C_HCBDMA_CBSR18   [expr 0x1 << 18 ]
set AT91C_HCBDMA_CBSR19   [expr 0x1 << 19 ]
set AT91C_HCBDMA_CBSR20   [expr 0x1 << 20 ]
set AT91C_HCBDMA_CBSR21   [expr 0x1 << 21 ]
set AT91C_HCBDMA_CBSR22   [expr 0x1 << 22 ]
set AT91C_HCBDMA_CBSR23   [expr 0x1 << 23 ]
set AT91C_HCBDMA_CBSR24   [expr 0x1 << 24 ]
set AT91C_HCBDMA_CBSR25   [expr 0x1 << 25 ]
set AT91C_HCBDMA_CBSR26   [expr 0x1 << 26 ]
set AT91C_HCBDMA_CBSR27   [expr 0x1 << 27 ]
set AT91C_HCBDMA_CBSR28   [expr 0x1 << 28 ]
set AT91C_HCBDMA_CBSR29   [expr 0x1 << 29 ]
set AT91C_HCBDMA_CBSR30   [expr 0x1 << 30 ]
set AT91C_HCBDMA_CBSR31   [expr 0x1 << 31 ]
# -------- HCBDMA_CBIER : (HCBDMA Offset: 0x14) CB DMA Interrupt Enable Register -------- 
set AT91C_HCBDMA_CBIER0   [expr 0x1 <<  0 ]
set AT91C_HCBDMA_CBIER1   [expr 0x1 <<  1 ]
set AT91C_HCBDMA_CBIER2   [expr 0x1 <<  2 ]
set AT91C_HCBDMA_CBIER3   [expr 0x1 <<  3 ]
set AT91C_HCBDMA_CBIER4   [expr 0x1 <<  4 ]
set AT91C_HCBDMA_CBIER5   [expr 0x1 <<  5 ]
set AT91C_HCBDMA_CBIER6   [expr 0x1 <<  6 ]
set AT91C_HCBDMA_CBIER7   [expr 0x1 <<  7 ]
set AT91C_HCBDMA_CBIER8   [expr 0x1 <<  8 ]
set AT91C_HCBDMA_CBIER9   [expr 0x1 <<  9 ]
set AT91C_HCBDMA_CBIER10  [expr 0x1 << 10 ]
set AT91C_HCBDMA_CBIER11  [expr 0x1 << 11 ]
set AT91C_HCBDMA_CBIER12  [expr 0x1 << 12 ]
set AT91C_HCBDMA_CBIER13  [expr 0x1 << 13 ]
set AT91C_HCBDMA_CBIER14  [expr 0x1 << 14 ]
set AT91C_HCBDMA_CBIER15  [expr 0x1 << 15 ]
set AT91C_HCBDMA_CBIER16  [expr 0x1 << 16 ]
set AT91C_HCBDMA_CBIER17  [expr 0x1 << 17 ]
set AT91C_HCBDMA_CBIER18  [expr 0x1 << 18 ]
set AT91C_HCBDMA_CBIER19  [expr 0x1 << 19 ]
set AT91C_HCBDMA_CBIER20  [expr 0x1 << 20 ]
set AT91C_HCBDMA_CBIER21  [expr 0x1 << 21 ]
set AT91C_HCBDMA_CBIER22  [expr 0x1 << 22 ]
set AT91C_HCBDMA_CBIER23  [expr 0x1 << 23 ]
set AT91C_HCBDMA_CBIER24  [expr 0x1 << 24 ]
set AT91C_HCBDMA_CBIER25  [expr 0x1 << 25 ]
set AT91C_HCBDMA_CBIER26  [expr 0x1 << 26 ]
set AT91C_HCBDMA_CBIER27  [expr 0x1 << 27 ]
set AT91C_HCBDMA_CBIER28  [expr 0x1 << 28 ]
set AT91C_HCBDMA_CBIER29  [expr 0x1 << 29 ]
set AT91C_HCBDMA_CBIER30  [expr 0x1 << 30 ]
set AT91C_HCBDMA_CBIER31  [expr 0x1 << 31 ]
# -------- HCBDMA_CBIDR : (HCBDMA Offset: 0x18) CB DMA Interrupt Disable Register -------- 
set AT91C_HCBDMA_CBIDR0   [expr 0x1 <<  0 ]
set AT91C_HCBDMA_CBIDR1   [expr 0x1 <<  1 ]
set AT91C_HCBDMA_CBIDR2   [expr 0x1 <<  2 ]
set AT91C_HCBDMA_CBIDR3   [expr 0x1 <<  3 ]
set AT91C_HCBDMA_CBIDR4   [expr 0x1 <<  4 ]
set AT91C_HCBDMA_CBIDR5   [expr 0x1 <<  5 ]
set AT91C_HCBDMA_CBIDR6   [expr 0x1 <<  6 ]
set AT91C_HCBDMA_CBIDR7   [expr 0x1 <<  7 ]
set AT91C_HCBDMA_CBIDR8   [expr 0x1 <<  8 ]
set AT91C_HCBDMA_CBIDR9   [expr 0x1 <<  9 ]
set AT91C_HCBDMA_CBIDR10  [expr 0x1 << 10 ]
set AT91C_HCBDMA_CBIDR11  [expr 0x1 << 11 ]
set AT91C_HCBDMA_CBIDR12  [expr 0x1 << 12 ]
set AT91C_HCBDMA_CBIDR13  [expr 0x1 << 13 ]
set AT91C_HCBDMA_CBIDR14  [expr 0x1 << 14 ]
set AT91C_HCBDMA_CBIDR15  [expr 0x1 << 15 ]
set AT91C_HCBDMA_CBIDR16  [expr 0x1 << 16 ]
set AT91C_HCBDMA_CBIDR17  [expr 0x1 << 17 ]
set AT91C_HCBDMA_CBIDR18  [expr 0x1 << 18 ]
set AT91C_HCBDMA_CBIDR19  [expr 0x1 << 19 ]
set AT91C_HCBDMA_CBIDR20  [expr 0x1 << 20 ]
set AT91C_HCBDMA_CBIDR21  [expr 0x1 << 21 ]
set AT91C_HCBDMA_CBIDR22  [expr 0x1 << 22 ]
set AT91C_HCBDMA_CBIDR23  [expr 0x1 << 23 ]
set AT91C_HCBDMA_CBIDR24  [expr 0x1 << 24 ]
set AT91C_HCBDMA_CBIDR25  [expr 0x1 << 25 ]
set AT91C_HCBDMA_CBIDR26  [expr 0x1 << 26 ]
set AT91C_HCBDMA_CBIDR27  [expr 0x1 << 27 ]
set AT91C_HCBDMA_CBIDR28  [expr 0x1 << 28 ]
set AT91C_HCBDMA_CBIDR29  [expr 0x1 << 29 ]
set AT91C_HCBDMA_CBIDR30  [expr 0x1 << 30 ]
set AT91C_HCBDMA_CBIDR31  [expr 0x1 << 31 ]
# -------- HCBDMA_CBIMR : (HCBDMA Offset: 0x1c) CB DMA Interrupt Mask Register -------- 
set AT91C_HCBDMA_CBIMR0   [expr 0x1 <<  0 ]
set AT91C_HCBDMA_CBIMR1   [expr 0x1 <<  1 ]
set AT91C_HCBDMA_CBIMR2   [expr 0x1 <<  2 ]
set AT91C_HCBDMA_CBIMR3   [expr 0x1 <<  3 ]
set AT91C_HCBDMA_CBIMR4   [expr 0x1 <<  4 ]
set AT91C_HCBDMA_CBIMR5   [expr 0x1 <<  5 ]
set AT91C_HCBDMA_CBIMR6   [expr 0x1 <<  6 ]
set AT91C_HCBDMA_CBIMR7   [expr 0x1 <<  7 ]
set AT91C_HCBDMA_CBIMR8   [expr 0x1 <<  8 ]
set AT91C_HCBDMA_CBIMR9   [expr 0x1 <<  9 ]
set AT91C_HCBDMA_CBIMR10  [expr 0x1 << 10 ]
set AT91C_HCBDMA_CBIMR11  [expr 0x1 << 11 ]
set AT91C_HCBDMA_CBIMR12  [expr 0x1 << 12 ]
set AT91C_HCBDMA_CBIMR13  [expr 0x1 << 13 ]
set AT91C_HCBDMA_CBIMR14  [expr 0x1 << 14 ]
set AT91C_HCBDMA_CBIMR15  [expr 0x1 << 15 ]
set AT91C_HCBDMA_CBIMR16  [expr 0x1 << 16 ]
set AT91C_HCBDMA_CBIMR17  [expr 0x1 << 17 ]
set AT91C_HCBDMA_CBIMR18  [expr 0x1 << 18 ]
set AT91C_HCBDMA_CBIMR19  [expr 0x1 << 19 ]
set AT91C_HCBDMA_CBIMR20  [expr 0x1 << 20 ]
set AT91C_HCBDMA_CBIMR21  [expr 0x1 << 21 ]
set AT91C_HCBDMA_CBIMR22  [expr 0x1 << 22 ]
set AT91C_HCBDMA_CBIMR23  [expr 0x1 << 23 ]
set AT91C_HCBDMA_CBIMR24  [expr 0x1 << 24 ]
set AT91C_HCBDMA_CBIMR25  [expr 0x1 << 25 ]
set AT91C_HCBDMA_CBIMR26  [expr 0x1 << 26 ]
set AT91C_HCBDMA_CBIMR27  [expr 0x1 << 27 ]
set AT91C_HCBDMA_CBIMR28  [expr 0x1 << 28 ]
set AT91C_HCBDMA_CBIMR29  [expr 0x1 << 29 ]
set AT91C_HCBDMA_CBIMR30  [expr 0x1 << 30 ]
set AT91C_HCBDMA_CBIMR31  [expr 0x1 << 31 ]
# -------- HCBDMA_CBISR : (HCBDMA Offset: 0x20) CB DMA Interrupt Satus Register -------- 
set AT91C_HCBDMA_CBISR0   [expr 0x1 <<  0 ]
set AT91C_HCBDMA_CBISR1   [expr 0x1 <<  1 ]
set AT91C_HCBDMA_CBISR2   [expr 0x1 <<  2 ]
set AT91C_HCBDMA_CBISR3   [expr 0x1 <<  3 ]
set AT91C_HCBDMA_CBISR4   [expr 0x1 <<  4 ]
set AT91C_HCBDMA_CBISR5   [expr 0x1 <<  5 ]
set AT91C_HCBDMA_CBISR6   [expr 0x1 <<  6 ]
set AT91C_HCBDMA_CBISR7   [expr 0x1 <<  7 ]
set AT91C_HCBDMA_CBISR8   [expr 0x1 <<  8 ]
set AT91C_HCBDMA_CBISR9   [expr 0x1 <<  9 ]
set AT91C_HCBDMA_CBISR10  [expr 0x1 << 10 ]
set AT91C_HCBDMA_CBISR11  [expr 0x1 << 11 ]
set AT91C_HCBDMA_CBISR12  [expr 0x1 << 12 ]
set AT91C_HCBDMA_CBISR13  [expr 0x1 << 13 ]
set AT91C_HCBDMA_CBISR14  [expr 0x1 << 14 ]
set AT91C_HCBDMA_CBISR15  [expr 0x1 << 15 ]
set AT91C_HCBDMA_CBISR16  [expr 0x1 << 16 ]
set AT91C_HCBDMA_CBISR17  [expr 0x1 << 17 ]
set AT91C_HCBDMA_CBISR18  [expr 0x1 << 18 ]
set AT91C_HCBDMA_CBISR19  [expr 0x1 << 19 ]
set AT91C_HCBDMA_CBISR20  [expr 0x1 << 20 ]
set AT91C_HCBDMA_CBISR21  [expr 0x1 << 21 ]
set AT91C_HCBDMA_CBISR22  [expr 0x1 << 22 ]
set AT91C_HCBDMA_CBISR23  [expr 0x1 << 23 ]
set AT91C_HCBDMA_CBISR24  [expr 0x1 << 24 ]
set AT91C_HCBDMA_CBISR25  [expr 0x1 << 25 ]
set AT91C_HCBDMA_CBISR26  [expr 0x1 << 26 ]
set AT91C_HCBDMA_CBISR27  [expr 0x1 << 27 ]
set AT91C_HCBDMA_CBISR28  [expr 0x1 << 28 ]
set AT91C_HCBDMA_CBISR29  [expr 0x1 << 29 ]
set AT91C_HCBDMA_CBISR30  [expr 0x1 << 30 ]
set AT91C_HCBDMA_CBISR31  [expr 0x1 << 31 ]
# -------- HCBDMA_CBDLIER : (HCBDMA Offset: 0x24) CB DMA Loaded Interrupt Enable Register -------- 
set AT91C_HCBDMA_CBDLIER0 [expr 0x1 <<  0 ]
set AT91C_HCBDMA_CBDLIER1 [expr 0x1 <<  1 ]
set AT91C_HCBDMA_CBDLIER2 [expr 0x1 <<  2 ]
set AT91C_HCBDMA_CBDLIER3 [expr 0x1 <<  3 ]
set AT91C_HCBDMA_CBDLIER4 [expr 0x1 <<  4 ]
set AT91C_HCBDMA_CBDLIER5 [expr 0x1 <<  5 ]
set AT91C_HCBDMA_CBDLIER6 [expr 0x1 <<  6 ]
set AT91C_HCBDMA_CBDLIER7 [expr 0x1 <<  7 ]
set AT91C_HCBDMA_CBDLIER8 [expr 0x1 <<  8 ]
set AT91C_HCBDMA_CBDLIER9 [expr 0x1 <<  9 ]
set AT91C_HCBDMA_CBDLIER10 [expr 0x1 << 10 ]
set AT91C_HCBDMA_CBDLIER11 [expr 0x1 << 11 ]
set AT91C_HCBDMA_CBDLIER12 [expr 0x1 << 12 ]
set AT91C_HCBDMA_CBDLIER13 [expr 0x1 << 13 ]
set AT91C_HCBDMA_CBDLIER14 [expr 0x1 << 14 ]
set AT91C_HCBDMA_CBDLIER15 [expr 0x1 << 15 ]
set AT91C_HCBDMA_CBDLIER16 [expr 0x1 << 16 ]
set AT91C_HCBDMA_CBDLIER17 [expr 0x1 << 17 ]
set AT91C_HCBDMA_CBDLIER18 [expr 0x1 << 18 ]
set AT91C_HCBDMA_CBDLIER19 [expr 0x1 << 19 ]
set AT91C_HCBDMA_CBDLIER20 [expr 0x1 << 20 ]
set AT91C_HCBDMA_CBDLIER21 [expr 0x1 << 21 ]
set AT91C_HCBDMA_CBDLIER22 [expr 0x1 << 22 ]
set AT91C_HCBDMA_CBDLIER23 [expr 0x1 << 23 ]
set AT91C_HCBDMA_CBDLIER24 [expr 0x1 << 24 ]
set AT91C_HCBDMA_CBDLIER25 [expr 0x1 << 25 ]
set AT91C_HCBDMA_CBDLIER26 [expr 0x1 << 26 ]
set AT91C_HCBDMA_CBDLIER27 [expr 0x1 << 27 ]
set AT91C_HCBDMA_CBDLIER28 [expr 0x1 << 28 ]
set AT91C_HCBDMA_CBDLIER29 [expr 0x1 << 29 ]
set AT91C_HCBDMA_CBDLIER30 [expr 0x1 << 30 ]
set AT91C_HCBDMA_CBDLIER31 [expr 0x1 << 31 ]
# -------- HCBDMA_CBDLIDR : (HCBDMA Offset: 0x28) CB DMA Interrupt Disable Register -------- 
set AT91C_HCBDMA_CBDLIDR0 [expr 0x1 <<  0 ]
set AT91C_HCBDMA_CBDLIDR1 [expr 0x1 <<  1 ]
set AT91C_HCBDMA_CBDLIDR2 [expr 0x1 <<  2 ]
set AT91C_HCBDMA_CBDLIDR3 [expr 0x1 <<  3 ]
set AT91C_HCBDMA_CBDLIDR4 [expr 0x1 <<  4 ]
set AT91C_HCBDMA_CBDLIDR5 [expr 0x1 <<  5 ]
set AT91C_HCBDMA_CBDLIDR6 [expr 0x1 <<  6 ]
set AT91C_HCBDMA_CBDLIDR7 [expr 0x1 <<  7 ]
set AT91C_HCBDMA_CBDLIDR8 [expr 0x1 <<  8 ]
set AT91C_HCBDMA_CBDLIDR9 [expr 0x1 <<  9 ]
set AT91C_HCBDMA_CBDLIDR10 [expr 0x1 << 10 ]
set AT91C_HCBDMA_CBDLIDR11 [expr 0x1 << 11 ]
set AT91C_HCBDMA_CBDLIDR12 [expr 0x1 << 12 ]
set AT91C_HCBDMA_CBDLIDR13 [expr 0x1 << 13 ]
set AT91C_HCBDMA_CBDLIDR14 [expr 0x1 << 14 ]
set AT91C_HCBDMA_CBDLIDR15 [expr 0x1 << 15 ]
set AT91C_HCBDMA_CBDLIDR16 [expr 0x1 << 16 ]
set AT91C_HCBDMA_CBDLIDR17 [expr 0x1 << 17 ]
set AT91C_HCBDMA_CBDLIDR18 [expr 0x1 << 18 ]
set AT91C_HCBDMA_CBDLIDR19 [expr 0x1 << 19 ]
set AT91C_HCBDMA_CBDLIDR20 [expr 0x1 << 20 ]
set AT91C_HCBDMA_CBDLIDR21 [expr 0x1 << 21 ]
set AT91C_HCBDMA_CBDLIDR22 [expr 0x1 << 22 ]
set AT91C_HCBDMA_CBDLIDR23 [expr 0x1 << 23 ]
set AT91C_HCBDMA_CBDLIDR24 [expr 0x1 << 24 ]
set AT91C_HCBDMA_CBDLIDR25 [expr 0x1 << 25 ]
set AT91C_HCBDMA_CBDLIDR26 [expr 0x1 << 26 ]
set AT91C_HCBDMA_CBDLIDR27 [expr 0x1 << 27 ]
set AT91C_HCBDMA_CBDLIDR28 [expr 0x1 << 28 ]
set AT91C_HCBDMA_CBDLIDR29 [expr 0x1 << 29 ]
set AT91C_HCBDMA_CBDLIDR30 [expr 0x1 << 30 ]
set AT91C_HCBDMA_CBDLIDR31 [expr 0x1 << 31 ]
# -------- HCBDMA_CBDLIMR : (HCBDMA Offset: 0x2c) CB DMA Interrupt Mask Register -------- 
set AT91C_HCBDMA_CBDLIMR0 [expr 0x1 <<  0 ]
set AT91C_HCBDMA_CBDLIMR1 [expr 0x1 <<  1 ]
set AT91C_HCBDMA_CBDLIMR2 [expr 0x1 <<  2 ]
set AT91C_HCBDMA_CBDLIMR3 [expr 0x1 <<  3 ]
set AT91C_HCBDMA_CBDLIMR4 [expr 0x1 <<  4 ]
set AT91C_HCBDMA_CBDLIMR5 [expr 0x1 <<  5 ]
set AT91C_HCBDMA_CBDLIMR6 [expr 0x1 <<  6 ]
set AT91C_HCBDMA_CBDLIMR7 [expr 0x1 <<  7 ]
set AT91C_HCBDMA_CBDLIMR8 [expr 0x1 <<  8 ]
set AT91C_HCBDMA_CBDLIMR9 [expr 0x1 <<  9 ]
set AT91C_HCBDMA_CBDLIMR10 [expr 0x1 << 10 ]
set AT91C_HCBDMA_CBDLIMR11 [expr 0x1 << 11 ]
set AT91C_HCBDMA_CBDLIMR12 [expr 0x1 << 12 ]
set AT91C_HCBDMA_CBDLIMR13 [expr 0x1 << 13 ]
set AT91C_HCBDMA_CBDLIMR14 [expr 0x1 << 14 ]
set AT91C_HCBDMA_CBDLIMR15 [expr 0x1 << 15 ]
set AT91C_HCBDMA_CBDLIMR16 [expr 0x1 << 16 ]
set AT91C_HCBDMA_CBDLIMR17 [expr 0x1 << 17 ]
set AT91C_HCBDMA_CBDLIMR18 [expr 0x1 << 18 ]
set AT91C_HCBDMA_CBDLIMR19 [expr 0x1 << 19 ]
set AT91C_HCBDMA_CBDLIMR20 [expr 0x1 << 20 ]
set AT91C_HCBDMA_CBDLIMR21 [expr 0x1 << 21 ]
set AT91C_HCBDMA_CBDLIMR22 [expr 0x1 << 22 ]
set AT91C_HCBDMA_CBDLIMR23 [expr 0x1 << 23 ]
set AT91C_HCBDMA_CBDLIMR24 [expr 0x1 << 24 ]
set AT91C_HCBDMA_CBDLIMR25 [expr 0x1 << 25 ]
set AT91C_HCBDMA_CBDLIMR26 [expr 0x1 << 26 ]
set AT91C_HCBDMA_CBDLIMR27 [expr 0x1 << 27 ]
set AT91C_HCBDMA_CBDLIMR28 [expr 0x1 << 28 ]
set AT91C_HCBDMA_CBDLIMR29 [expr 0x1 << 29 ]
set AT91C_HCBDMA_CBDLIMR30 [expr 0x1 << 30 ]
set AT91C_HCBDMA_CBDLIMR31 [expr 0x1 << 31 ]
# -------- HCBDMA_CBDLISR : (HCBDMA Offset: 0x30) CB DMA Interrupt Satus Register -------- 
set AT91C_HCBDMA_CBDLISR0 [expr 0x1 <<  0 ]
set AT91C_HCBDMA_CBDLISR1 [expr 0x1 <<  1 ]
set AT91C_HCBDMA_CBDLISR2 [expr 0x1 <<  2 ]
set AT91C_HCBDMA_CBDLISR3 [expr 0x1 <<  3 ]
set AT91C_HCBDMA_CBDLISR4 [expr 0x1 <<  4 ]
set AT91C_HCBDMA_CBDLISR5 [expr 0x1 <<  5 ]
set AT91C_HCBDMA_CBDLISR6 [expr 0x1 <<  6 ]
set AT91C_HCBDMA_CBDLISR7 [expr 0x1 <<  7 ]
set AT91C_HCBDMA_CBDLISR8 [expr 0x1 <<  8 ]
set AT91C_HCBDMA_CBDLISR9 [expr 0x1 <<  9 ]
set AT91C_HCBDMA_CBDLISR10 [expr 0x1 << 10 ]
set AT91C_HCBDMA_CBDLISR11 [expr 0x1 << 11 ]
set AT91C_HCBDMA_CBDLISR12 [expr 0x1 << 12 ]
set AT91C_HCBDMA_CBDLISR13 [expr 0x1 << 13 ]
set AT91C_HCBDMA_CBDLISR14 [expr 0x1 << 14 ]
set AT91C_HCBDMA_CBDLISR15 [expr 0x1 << 15 ]
set AT91C_HCBDMA_CBDLISR16 [expr 0x1 << 16 ]
set AT91C_HCBDMA_CBDLISR17 [expr 0x1 << 17 ]
set AT91C_HCBDMA_CBDLISR18 [expr 0x1 << 18 ]
set AT91C_HCBDMA_CBDLISR19 [expr 0x1 << 19 ]
set AT91C_HCBDMA_CBDLISR20 [expr 0x1 << 20 ]
set AT91C_HCBDMA_CBDLISR21 [expr 0x1 << 21 ]
set AT91C_HCBDMA_CBDLISR22 [expr 0x1 << 22 ]
set AT91C_HCBDMA_CBDLISR23 [expr 0x1 << 23 ]
set AT91C_HCBDMA_CBDLISR24 [expr 0x1 << 24 ]
set AT91C_HCBDMA_CBDLISR25 [expr 0x1 << 25 ]
set AT91C_HCBDMA_CBDLISR26 [expr 0x1 << 26 ]
set AT91C_HCBDMA_CBDLISR27 [expr 0x1 << 27 ]
set AT91C_HCBDMA_CBDLISR28 [expr 0x1 << 28 ]
set AT91C_HCBDMA_CBDLISR29 [expr 0x1 << 29 ]
set AT91C_HCBDMA_CBDLISR30 [expr 0x1 << 30 ]
set AT91C_HCBDMA_CBDLISR31 [expr 0x1 << 31 ]
# -------- HCBDMA_CBCRCCR : (HCBDMA Offset: 0x34) CB DMA CRC Control Resgister -------- 
set AT91C_CRC_START       [expr 0x1 <<  0 ]
# -------- HCBDMA_CBCRCMR : (HCBDMA Offset: 0x38) CB DMA CRC Mode Resgister -------- 
set AT91C_CRC_ENABLE      [expr 0x1 <<  0 ]
set AT91C_CRC_COMPARE     [expr 0x1 <<  1 ]
set AT91C_CRC_PTYPE       [expr 0x3 <<  2 ]
set 	AT91C_CRC_PTYPE_CCIT802_3            [expr 0x0 <<  2 ]
set 	AT91C_CRC_PTYPE_CASTAGNOLI           [expr 0x1 <<  2 ]
set 	AT91C_CRC_PTYPE_CCIT_16              [expr 0x2 <<  2 ]
set AT91C_CRC_DIVIDER     [expr 0xF <<  4 ]
set AT91C_CRC_ID          [expr 0x1F <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_0            [expr 0x0 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_1            [expr 0x1 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_2            [expr 0x2 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_3            [expr 0x3 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_4            [expr 0x4 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_5            [expr 0x5 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_6            [expr 0x6 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_7            [expr 0x7 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_8            [expr 0x8 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_9            [expr 0x9 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_10           [expr 0xA <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_11           [expr 0xB <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_12           [expr 0xC <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_13           [expr 0xD <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_14           [expr 0xE <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_15           [expr 0xF <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_16           [expr 0x10 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_17           [expr 0x11 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_18           [expr 0x12 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_19           [expr 0x13 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_20           [expr 0x14 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_21           [expr 0x15 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_22           [expr 0x16 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_23           [expr 0x17 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_24           [expr 0x18 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_25           [expr 0x19 <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_26           [expr 0x1A <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_27           [expr 0x1B <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_28           [expr 0x1C <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_29           [expr 0x1D <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_30           [expr 0x1E <<  8 ]
set 	AT91C_CRC_ID_CHANNEL_31           [expr 0x1F <<  8 ]
# -------- HCBDMA_CBCRCSR : (HCBDMA Offset: 0x3c) CB DMA CRC Status Resgister -------- 
set AT91C_HCBDMA_CRCSR    [expr 0x0 <<  0 ]
# -------- HCBDMA_CBCRCIER : (HCBDMA Offset: 0x40) CB DMA CRC Interrupt Enable Resgister -------- 
set AT91C_CRC_ERRIER      [expr 0x1 <<  0 ]
# -------- HCBDMA_CBCRCIDR : (HCBDMA Offset: 0x44) CB DMA CRC Interrupt Enable Resgister -------- 
set AT91C_CRC_ERRIDR      [expr 0x1 <<  0 ]
# -------- HCBDMA_CBCRCIMR : (HCBDMA Offset: 0x48) CB DMA CRC Interrupt Mask Resgister -------- 
set AT91C_CRC_ERRIMR      [expr 0x1 <<  0 ]
# -------- HCBDMA_CBCRCISR : (HCBDMA Offset: 0x4c) CB DMA CRC Interrupt Status Resgister -------- 
set AT91C_CRC_ERRISR      [expr 0x1 <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface
# *****************************************************************************
# -------- TC_CCR : (TC Offset: 0x0) TC Channel Control Register -------- 
set AT91C_TC_CLKEN        [expr 0x1 <<  0 ]
set AT91C_TC_CLKDIS       [expr 0x1 <<  1 ]
set AT91C_TC_SWTRG        [expr 0x1 <<  2 ]
# -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- 
set AT91C_TC_CLKS         [expr 0x7 <<  0 ]
set 	AT91C_TC_CLKS_TIMER_DIV1_CLOCK     0x0
set 	AT91C_TC_CLKS_TIMER_DIV2_CLOCK     0x1
set 	AT91C_TC_CLKS_TIMER_DIV3_CLOCK     0x2
set 	AT91C_TC_CLKS_TIMER_DIV4_CLOCK     0x3
set 	AT91C_TC_CLKS_TIMER_DIV5_CLOCK     0x4
set 	AT91C_TC_CLKS_XC0                  0x5
set 	AT91C_TC_CLKS_XC1                  0x6
set 	AT91C_TC_CLKS_XC2                  0x7
set AT91C_TC_CLKS         [expr 0x7 <<  0 ]
set 	AT91C_TC_CLKS_TIMER_DIV1_CLOCK     0x0
set 	AT91C_TC_CLKS_TIMER_DIV2_CLOCK     0x1
set 	AT91C_TC_CLKS_TIMER_DIV3_CLOCK     0x2
set 	AT91C_TC_CLKS_TIMER_DIV4_CLOCK     0x3
set 	AT91C_TC_CLKS_TIMER_DIV5_CLOCK     0x4
set 	AT91C_TC_CLKS_XC0                  0x5
set 	AT91C_TC_CLKS_XC1                  0x6
set 	AT91C_TC_CLKS_XC2                  0x7
set AT91C_TC_CLKI         [expr 0x1 <<  3 ]
set AT91C_TC_CLKI         [expr 0x1 <<  3 ]
set AT91C_TC_BURST        [expr 0x3 <<  4 ]
set 	AT91C_TC_BURST_NONE                 [expr 0x0 <<  4 ]
set 	AT91C_TC_BURST_XC0                  [expr 0x1 <<  4 ]
set 	AT91C_TC_BURST_XC1                  [expr 0x2 <<  4 ]
set 	AT91C_TC_BURST_XC2                  [expr 0x3 <<  4 ]
set AT91C_TC_BURST        [expr 0x3 <<  4 ]
set 	AT91C_TC_BURST_NONE                 [expr 0x0 <<  4 ]
set 	AT91C_TC_BURST_XC0                  [expr 0x1 <<  4 ]
set 	AT91C_TC_BURST_XC1                  [expr 0x2 <<  4 ]
set 	AT91C_TC_BURST_XC2                  [expr 0x3 <<  4 ]
set AT91C_TC_CPCSTOP      [expr 0x1 <<  6 ]
set AT91C_TC_LDBSTOP      [expr 0x1 <<  6 ]
set AT91C_TC_CPCDIS       [expr 0x1 <<  7 ]
set AT91C_TC_LDBDIS       [expr 0x1 <<  7 ]
set AT91C_TC_ETRGEDG      [expr 0x3 <<  8 ]
set 	AT91C_TC_ETRGEDG_NONE                 [expr 0x0 <<  8 ]
set 	AT91C_TC_ETRGEDG_RISING               [expr 0x1 <<  8 ]
set 	AT91C_TC_ETRGEDG_FALLING              [expr 0x2 <<  8 ]
set 	AT91C_TC_ETRGEDG_BOTH                 [expr 0x3 <<  8 ]
set AT91C_TC_EEVTEDG      [expr 0x3 <<  8 ]
set 	AT91C_TC_EEVTEDG_NONE                 [expr 0x0 <<  8 ]
set 	AT91C_TC_EEVTEDG_RISING               [expr 0x1 <<  8 ]
set 	AT91C_TC_EEVTEDG_FALLING              [expr 0x2 <<  8 ]
set 	AT91C_TC_EEVTEDG_BOTH                 [expr 0x3 <<  8 ]
set AT91C_TC_EEVT         [expr 0x3 << 10 ]
set 	AT91C_TC_EEVT_TIOB                 [expr 0x0 << 10 ]
set 	AT91C_TC_EEVT_XC0                  [expr 0x1 << 10 ]
set 	AT91C_TC_EEVT_XC1                  [expr 0x2 << 10 ]
set 	AT91C_TC_EEVT_XC2                  [expr 0x3 << 10 ]
set AT91C_TC_ABETRG       [expr 0x1 << 10 ]
set AT91C_TC_ENETRG       [expr 0x1 << 12 ]
set AT91C_TC_WAVESEL      [expr 0x3 << 13 ]
set 	AT91C_TC_WAVESEL_UP                   [expr 0x0 << 13 ]
set 	AT91C_TC_WAVESEL_UPDOWN               [expr 0x1 << 13 ]
set 	AT91C_TC_WAVESEL_UP_AUTO              [expr 0x2 << 13 ]
set 	AT91C_TC_WAVESEL_UPDOWN_AUTO          [expr 0x3 << 13 ]
set AT91C_TC_CPCTRG       [expr 0x1 << 14 ]
set AT91C_TC_WAVE         [expr 0x1 << 15 ]
set AT91C_TC_WAVE         [expr 0x1 << 15 ]
set AT91C_TC_ACPA         [expr 0x3 << 16 ]
set 	AT91C_TC_ACPA_NONE                 [expr 0x0 << 16 ]
set 	AT91C_TC_ACPA_SET                  [expr 0x1 << 16 ]
set 	AT91C_TC_ACPA_CLEAR                [expr 0x2 << 16 ]
set 	AT91C_TC_ACPA_TOGGLE               [expr 0x3 << 16 ]
set AT91C_TC_LDRA         [expr 0x3 << 16 ]
set 	AT91C_TC_LDRA_NONE                 [expr 0x0 << 16 ]
set 	AT91C_TC_LDRA_RISING               [expr 0x1 << 16 ]
set 	AT91C_TC_LDRA_FALLING              [expr 0x2 << 16 ]
set 	AT91C_TC_LDRA_BOTH                 [expr 0x3 << 16 ]
set AT91C_TC_ACPC         [expr 0x3 << 18 ]
set 	AT91C_TC_ACPC_NONE                 [expr 0x0 << 18 ]
set 	AT91C_TC_ACPC_SET                  [expr 0x1 << 18 ]
set 	AT91C_TC_ACPC_CLEAR                [expr 0x2 << 18 ]
set 	AT91C_TC_ACPC_TOGGLE               [expr 0x3 << 18 ]
set AT91C_TC_LDRB         [expr 0x3 << 18 ]
set 	AT91C_TC_LDRB_NONE                 [expr 0x0 << 18 ]
set 	AT91C_TC_LDRB_RISING               [expr 0x1 << 18 ]
set 	AT91C_TC_LDRB_FALLING              [expr 0x2 << 18 ]
set 	AT91C_TC_LDRB_BOTH                 [expr 0x3 << 18 ]
set AT91C_TC_AEEVT        [expr 0x3 << 20 ]
set 	AT91C_TC_AEEVT_NONE                 [expr 0x0 << 20 ]
set 	AT91C_TC_AEEVT_SET                  [expr 0x1 << 20 ]
set 	AT91C_TC_AEEVT_CLEAR                [expr 0x2 << 20 ]
set 	AT91C_TC_AEEVT_TOGGLE               [expr 0x3 << 20 ]
set AT91C_TC_ASWTRG       [expr 0x3 << 22 ]
set 	AT91C_TC_ASWTRG_NONE                 [expr 0x0 << 22 ]
set 	AT91C_TC_ASWTRG_SET                  [expr 0x1 << 22 ]
set 	AT91C_TC_ASWTRG_CLEAR                [expr 0x2 << 22 ]
set 	AT91C_TC_ASWTRG_TOGGLE               [expr 0x3 << 22 ]
set AT91C_TC_BCPB         [expr 0x3 << 24 ]
set 	AT91C_TC_BCPB_NONE                 [expr 0x0 << 24 ]
set 	AT91C_TC_BCPB_SET                  [expr 0x1 << 24 ]
set 	AT91C_TC_BCPB_CLEAR                [expr 0x2 << 24 ]
set 	AT91C_TC_BCPB_TOGGLE               [expr 0x3 << 24 ]
set AT91C_TC_BCPC         [expr 0x3 << 26 ]
set 	AT91C_TC_BCPC_NONE                 [expr 0x0 << 26 ]
set 	AT91C_TC_BCPC_SET                  [expr 0x1 << 26 ]
set 	AT91C_TC_BCPC_CLEAR                [expr 0x2 << 26 ]
set 	AT91C_TC_BCPC_TOGGLE               [expr 0x3 << 26 ]
set AT91C_TC_BEEVT        [expr 0x3 << 28 ]
set 	AT91C_TC_BEEVT_NONE                 [expr 0x0 << 28 ]
set 	AT91C_TC_BEEVT_SET                  [expr 0x1 << 28 ]
set 	AT91C_TC_BEEVT_CLEAR                [expr 0x2 << 28 ]
set 	AT91C_TC_BEEVT_TOGGLE               [expr 0x3 << 28 ]
set AT91C_TC_BSWTRG       [expr 0x3 << 30 ]
set 	AT91C_TC_BSWTRG_NONE                 [expr 0x0 << 30 ]
set 	AT91C_TC_BSWTRG_SET                  [expr 0x1 << 30 ]
set 	AT91C_TC_BSWTRG_CLEAR                [expr 0x2 << 30 ]
set 	AT91C_TC_BSWTRG_TOGGLE               [expr 0x3 << 30 ]
# -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- 
set AT91C_TC_COVFS        [expr 0x1 <<  0 ]
set AT91C_TC_LOVRS        [expr 0x1 <<  1 ]
set AT91C_TC_CPAS         [expr 0x1 <<  2 ]
set AT91C_TC_CPBS         [expr 0x1 <<  3 ]
set AT91C_TC_CPCS         [expr 0x1 <<  4 ]
set AT91C_TC_LDRAS        [expr 0x1 <<  5 ]
set AT91C_TC_LDRBS        [expr 0x1 <<  6 ]
set AT91C_TC_ETRGS        [expr 0x1 <<  7 ]
set AT91C_TC_CLKSTA       [expr 0x1 << 16 ]
set AT91C_TC_MTIOA        [expr 0x1 << 17 ]
set AT91C_TC_MTIOB        [expr 0x1 << 18 ]
# -------- TC_IER : (TC Offset: 0x24) TC Channel Interrupt Enable Register -------- 
set AT91C_TC_COVFS        [expr 0x1 <<  0 ]
set AT91C_TC_LOVRS        [expr 0x1 <<  1 ]
set AT91C_TC_CPAS         [expr 0x1 <<  2 ]
set AT91C_TC_CPBS         [expr 0x1 <<  3 ]
set AT91C_TC_CPCS         [expr 0x1 <<  4 ]
set AT91C_TC_LDRAS        [expr 0x1 <<  5 ]
set AT91C_TC_LDRBS        [expr 0x1 <<  6 ]
set AT91C_TC_ETRGS        [expr 0x1 <<  7 ]
# -------- TC_IDR : (TC Offset: 0x28) TC Channel Interrupt Disable Register -------- 
set AT91C_TC_COVFS        [expr 0x1 <<  0 ]
set AT91C_TC_LOVRS        [expr 0x1 <<  1 ]
set AT91C_TC_CPAS         [expr 0x1 <<  2 ]
set AT91C_TC_CPBS         [expr 0x1 <<  3 ]
set AT91C_TC_CPCS         [expr 0x1 <<  4 ]
set AT91C_TC_LDRAS        [expr 0x1 <<  5 ]
set AT91C_TC_LDRBS        [expr 0x1 <<  6 ]
set AT91C_TC_ETRGS        [expr 0x1 <<  7 ]
# -------- TC_IMR : (TC Offset: 0x2c) TC Channel Interrupt Mask Register -------- 
set AT91C_TC_COVFS        [expr 0x1 <<  0 ]
set AT91C_TC_LOVRS        [expr 0x1 <<  1 ]
set AT91C_TC_CPAS         [expr 0x1 <<  2 ]
set AT91C_TC_CPBS         [expr 0x1 <<  3 ]
set AT91C_TC_CPCS         [expr 0x1 <<  4 ]
set AT91C_TC_LDRAS        [expr 0x1 <<  5 ]
set AT91C_TC_LDRBS        [expr 0x1 <<  6 ]
set AT91C_TC_ETRGS        [expr 0x1 <<  7 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Timer Counter Interface
# *****************************************************************************
# -------- TCB_BCR : (TCB Offset: 0xc0) TC Block Control Register -------- 
set AT91C_TCB_SYNC        [expr 0x1 <<  0 ]
# -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- 
set AT91C_TCB_TC0XC0S     [expr 0x3 <<  0 ]
set 	AT91C_TCB_TC0XC0S_TCLK0                0x0
set 	AT91C_TCB_TC0XC0S_NONE                 0x1
set 	AT91C_TCB_TC0XC0S_TIOA1                0x2
set 	AT91C_TCB_TC0XC0S_TIOA2                0x3
set AT91C_TCB_TC1XC1S     [expr 0x3 <<  2 ]
set 	AT91C_TCB_TC1XC1S_TCLK1                [expr 0x0 <<  2 ]
set 	AT91C_TCB_TC1XC1S_NONE                 [expr 0x1 <<  2 ]
set 	AT91C_TCB_TC1XC1S_TIOA0                [expr 0x2 <<  2 ]
set 	AT91C_TCB_TC1XC1S_TIOA2                [expr 0x3 <<  2 ]
set AT91C_TCB_TC2XC2S     [expr 0x3 <<  4 ]
set 	AT91C_TCB_TC2XC2S_TCLK2                [expr 0x0 <<  4 ]
set 	AT91C_TCB_TC2XC2S_NONE                 [expr 0x1 <<  4 ]
set 	AT91C_TCB_TC2XC2S_TIOA0                [expr 0x2 <<  4 ]
set 	AT91C_TCB_TC2XC2S_TIOA1                [expr 0x3 <<  4 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Embedded Flash Controller 2.0
# *****************************************************************************
# -------- EFC_FMR : (EFC Offset: 0x0) EFC Flash Mode Register -------- 
set AT91C_EFC_FRDY        [expr 0x1 <<  0 ]
set AT91C_EFC_FWS         [expr 0xF <<  8 ]
set 	AT91C_EFC_FWS_0WS                  [expr 0x0 <<  8 ]
set 	AT91C_EFC_FWS_1WS                  [expr 0x1 <<  8 ]
set 	AT91C_EFC_FWS_2WS                  [expr 0x2 <<  8 ]
set 	AT91C_EFC_FWS_3WS                  [expr 0x3 <<  8 ]
# -------- EFC_FCR : (EFC Offset: 0x4) EFC Flash Command Register -------- 
set AT91C_EFC_FCMD        [expr 0xFF <<  0 ]
set 	AT91C_EFC_FCMD_GETD                 0x0
set 	AT91C_EFC_FCMD_WP                   0x1
set 	AT91C_EFC_FCMD_WPL                  0x2
set 	AT91C_EFC_FCMD_EWP                  0x3
set 	AT91C_EFC_FCMD_EWPL                 0x4
set 	AT91C_EFC_FCMD_EA                   0x5
set 	AT91C_EFC_FCMD_EPL                  0x6
set 	AT91C_EFC_FCMD_EPA                  0x7
set 	AT91C_EFC_FCMD_SLB                  0x8
set 	AT91C_EFC_FCMD_CLB                  0x9
set 	AT91C_EFC_FCMD_GLB                  0xA
set 	AT91C_EFC_FCMD_SFB                  0xB
set 	AT91C_EFC_FCMD_CFB                  0xC
set 	AT91C_EFC_FCMD_GFB                  0xD
set 	AT91C_EFC_FCMD_STUI                 0xE
set 	AT91C_EFC_FCMD_SPUI                 0xF
set AT91C_EFC_FARG        [expr 0xFFFF <<  8 ]
set AT91C_EFC_FKEY        [expr 0xFF << 24 ]
# -------- EFC_FSR : (EFC Offset: 0x8) EFC Flash Status Register -------- 
set AT91C_EFC_FRDY_S      [expr 0x1 <<  0 ]
set AT91C_EFC_FCMDE       [expr 0x1 <<  1 ]
set AT91C_EFC_LOCKE       [expr 0x1 <<  2 ]
# -------- EFC_FRR : (EFC Offset: 0xc) EFC Flash Result Register -------- 
set AT91C_EFC_FVALUE      [expr 0x0 <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Multimedia Card Interface
# *****************************************************************************
# -------- MCI_CR : (MCI Offset: 0x0) MCI Control Register -------- 
set AT91C_MCI_MCIEN       [expr 0x1 <<  0 ]
set 	AT91C_MCI_MCIEN_0                    0x0
set 	AT91C_MCI_MCIEN_1                    0x1
set AT91C_MCI_MCIDIS      [expr 0x1 <<  1 ]
set 	AT91C_MCI_MCIDIS_0                    [expr 0x0 <<  1 ]
set 	AT91C_MCI_MCIDIS_1                    [expr 0x1 <<  1 ]
set AT91C_MCI_PWSEN       [expr 0x1 <<  2 ]
set 	AT91C_MCI_PWSEN_0                    [expr 0x0 <<  2 ]
set 	AT91C_MCI_PWSEN_1                    [expr 0x1 <<  2 ]
set AT91C_MCI_PWSDIS      [expr 0x1 <<  3 ]
set 	AT91C_MCI_PWSDIS_0                    [expr 0x0 <<  3 ]
set 	AT91C_MCI_PWSDIS_1                    [expr 0x1 <<  3 ]
set AT91C_MCI_IOWAITEN    [expr 0x1 <<  4 ]
set 	AT91C_MCI_IOWAITEN_0                    [expr 0x0 <<  4 ]
set 	AT91C_MCI_IOWAITEN_1                    [expr 0x1 <<  4 ]
set AT91C_MCI_IOWAITDIS   [expr 0x1 <<  5 ]
set 	AT91C_MCI_IOWAITDIS_0                    [expr 0x0 <<  5 ]
set 	AT91C_MCI_IOWAITDIS_1                    [expr 0x1 <<  5 ]
set AT91C_MCI_SWRST       [expr 0x1 <<  7 ]
set 	AT91C_MCI_SWRST_0                    [expr 0x0 <<  7 ]
set 	AT91C_MCI_SWRST_1                    [expr 0x1 <<  7 ]
# -------- MCI_MR : (MCI Offset: 0x4) MCI Mode Register -------- 
set AT91C_MCI_CLKDIV      [expr 0xFF <<  0 ]
set AT91C_MCI_PWSDIV      [expr 0x7 <<  8 ]
set AT91C_MCI_RDPROOF     [expr 0x1 << 11 ]
set 	AT91C_MCI_RDPROOF_DISABLE              [expr 0x0 << 11 ]
set 	AT91C_MCI_RDPROOF_ENABLE               [expr 0x1 << 11 ]
set AT91C_MCI_WRPROOF     [expr 0x1 << 12 ]
set 	AT91C_MCI_WRPROOF_DISABLE              [expr 0x0 << 12 ]
set 	AT91C_MCI_WRPROOF_ENABLE               [expr 0x1 << 12 ]
set AT91C_MCI_PDCFBYTE    [expr 0x1 << 13 ]
set 	AT91C_MCI_PDCFBYTE_DISABLE              [expr 0x0 << 13 ]
set 	AT91C_MCI_PDCFBYTE_ENABLE               [expr 0x1 << 13 ]
set AT91C_MCI_PDCPADV     [expr 0x1 << 14 ]
set AT91C_MCI_PDCMODE     [expr 0x1 << 15 ]
set 	AT91C_MCI_PDCMODE_DISABLE              [expr 0x0 << 15 ]
set 	AT91C_MCI_PDCMODE_ENABLE               [expr 0x1 << 15 ]
set AT91C_MCI_BLKLEN      [expr 0xFFFF << 16 ]
# -------- MCI_DTOR : (MCI Offset: 0x8) MCI Data Timeout Register -------- 
set AT91C_MCI_DTOCYC      [expr 0xF <<  0 ]
set AT91C_MCI_DTOMUL      [expr 0x7 <<  4 ]
set 	AT91C_MCI_DTOMUL_1                    [expr 0x0 <<  4 ]
set 	AT91C_MCI_DTOMUL_16                   [expr 0x1 <<  4 ]
set 	AT91C_MCI_DTOMUL_128                  [expr 0x2 <<  4 ]
set 	AT91C_MCI_DTOMUL_256                  [expr 0x3 <<  4 ]
set 	AT91C_MCI_DTOMUL_1024                 [expr 0x4 <<  4 ]
set 	AT91C_MCI_DTOMUL_4096                 [expr 0x5 <<  4 ]
set 	AT91C_MCI_DTOMUL_65536                [expr 0x6 <<  4 ]
set 	AT91C_MCI_DTOMUL_1048576              [expr 0x7 <<  4 ]
# -------- MCI_SDCR : (MCI Offset: 0xc) MCI SD Card Register -------- 
set AT91C_MCI_SCDSEL      [expr 0x3 <<  0 ]
set 	AT91C_MCI_SCDSEL_SLOTA                0x0
set 	AT91C_MCI_SCDSEL_SLOTB                0x1
set 	AT91C_MCI_SCDSEL_SLOTC                0x2
set 	AT91C_MCI_SCDSEL_SLOTD                0x3
set AT91C_MCI_SCDBUS      [expr 0x3 <<  6 ]
set 	AT91C_MCI_SCDBUS_1BIT                 [expr 0x0 <<  6 ]
set 	AT91C_MCI_SCDBUS_4BITS                [expr 0x2 <<  6 ]
set 	AT91C_MCI_SCDBUS_8BITS                [expr 0x3 <<  6 ]
# -------- MCI_CMDR : (MCI Offset: 0x14) MCI Command Register -------- 
set AT91C_MCI_CMDNB       [expr 0x3F <<  0 ]
set AT91C_MCI_RSPTYP      [expr 0x3 <<  6 ]
set 	AT91C_MCI_RSPTYP_NO                   [expr 0x0 <<  6 ]
set 	AT91C_MCI_RSPTYP_48                   [expr 0x1 <<  6 ]
set 	AT91C_MCI_RSPTYP_136                  [expr 0x2 <<  6 ]
set 	AT91C_MCI_RSPTYP_R1B                  [expr 0x3 <<  6 ]
set AT91C_MCI_SPCMD       [expr 0x7 <<  8 ]
set 	AT91C_MCI_SPCMD_NONE                 [expr 0x0 <<  8 ]
set 	AT91C_MCI_SPCMD_INIT                 [expr 0x1 <<  8 ]
set 	AT91C_MCI_SPCMD_SYNC                 [expr 0x2 <<  8 ]
set 	AT91C_MCI_SPCMD_CE_ATA               [expr 0x3 <<  8 ]
set 	AT91C_MCI_SPCMD_IT_CMD               [expr 0x4 <<  8 ]
set 	AT91C_MCI_SPCMD_IT_REP               [expr 0x5 <<  8 ]
set AT91C_MCI_OPDCMD      [expr 0x1 << 11 ]
set 	AT91C_MCI_OPDCMD_PUSHPULL             [expr 0x0 << 11 ]
set 	AT91C_MCI_OPDCMD_OPENDRAIN            [expr 0x1 << 11 ]
set AT91C_MCI_MAXLAT      [expr 0x1 << 12 ]
set 	AT91C_MCI_MAXLAT_5                    [expr 0x0 << 12 ]
set 	AT91C_MCI_MAXLAT_64                   [expr 0x1 << 12 ]
set AT91C_MCI_TRCMD       [expr 0x3 << 16 ]
set 	AT91C_MCI_TRCMD_NO                   [expr 0x0 << 16 ]
set 	AT91C_MCI_TRCMD_START                [expr 0x1 << 16 ]
set 	AT91C_MCI_TRCMD_STOP                 [expr 0x2 << 16 ]
set AT91C_MCI_TRDIR       [expr 0x1 << 18 ]
set 	AT91C_MCI_TRDIR_WRITE                [expr 0x0 << 18 ]
set 	AT91C_MCI_TRDIR_READ                 [expr 0x1 << 18 ]
set AT91C_MCI_TRTYP       [expr 0x7 << 19 ]
set 	AT91C_MCI_TRTYP_BLOCK                [expr 0x0 << 19 ]
set 	AT91C_MCI_TRTYP_MULTIPLE             [expr 0x1 << 19 ]
set 	AT91C_MCI_TRTYP_STREAM               [expr 0x2 << 19 ]
set 	AT91C_MCI_TRTYP_SDIO_BYTE            [expr 0x4 << 19 ]
set 	AT91C_MCI_TRTYP_SDIO_BLOCK           [expr 0x5 << 19 ]
set AT91C_MCI_IOSPCMD     [expr 0x3 << 24 ]
set 	AT91C_MCI_IOSPCMD_NONE                 [expr 0x0 << 24 ]
set 	AT91C_MCI_IOSPCMD_SUSPEND              [expr 0x1 << 24 ]
set 	AT91C_MCI_IOSPCMD_RESUME               [expr 0x2 << 24 ]
set AT91C_MCI_ATACS       [expr 0x1 << 26 ]
set 	AT91C_MCI_ATACS_NORMAL               [expr 0x0 << 26 ]
set 	AT91C_MCI_ATACS_COMPLETION           [expr 0x1 << 26 ]
# -------- MCI_BLKR : (MCI Offset: 0x18) MCI Block Register -------- 
set AT91C_MCI_BCNT        [expr 0xFFFF <<  0 ]
set AT91C_MCI_BLKLEN      [expr 0xFFFF << 16 ]
# -------- MCI_CSTOR : (MCI Offset: 0x1c) MCI Completion Signal Timeout Register -------- 
set AT91C_MCI_CSTOCYC     [expr 0xF <<  0 ]
set AT91C_MCI_CSTOMUL     [expr 0x7 <<  4 ]
set 	AT91C_MCI_CSTOMUL_1                    [expr 0x0 <<  4 ]
set 	AT91C_MCI_CSTOMUL_16                   [expr 0x1 <<  4 ]
set 	AT91C_MCI_CSTOMUL_128                  [expr 0x2 <<  4 ]
set 	AT91C_MCI_CSTOMUL_256                  [expr 0x3 <<  4 ]
set 	AT91C_MCI_CSTOMUL_1024                 [expr 0x4 <<  4 ]
set 	AT91C_MCI_CSTOMUL_4096                 [expr 0x5 <<  4 ]
set 	AT91C_MCI_CSTOMUL_65536                [expr 0x6 <<  4 ]
set 	AT91C_MCI_CSTOMUL_1048576              [expr 0x7 <<  4 ]
# -------- MCI_SR : (MCI Offset: 0x40) MCI Status Register -------- 
set AT91C_MCI_CMDRDY      [expr 0x1 <<  0 ]
set AT91C_MCI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_MCI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_MCI_BLKE        [expr 0x1 <<  3 ]
set AT91C_MCI_DTIP        [expr 0x1 <<  4 ]
set AT91C_MCI_NOTBUSY     [expr 0x1 <<  5 ]
set AT91C_MCI_ENDRX       [expr 0x1 <<  6 ]
set AT91C_MCI_ENDTX       [expr 0x1 <<  7 ]
set AT91C_MCI_SDIOIRQA    [expr 0x1 <<  8 ]
set AT91C_MCI_SDIOIRQB    [expr 0x1 <<  9 ]
set AT91C_MCI_SDIOIRQC    [expr 0x1 << 10 ]
set AT91C_MCI_SDIOIRQD    [expr 0x1 << 11 ]
set AT91C_MCI_SDIOWAIT    [expr 0x1 << 12 ]
set AT91C_MCI_CSRCV       [expr 0x1 << 13 ]
set AT91C_MCI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_MCI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_MCI_RINDE       [expr 0x1 << 16 ]
set AT91C_MCI_RDIRE       [expr 0x1 << 17 ]
set AT91C_MCI_RCRCE       [expr 0x1 << 18 ]
set AT91C_MCI_RENDE       [expr 0x1 << 19 ]
set AT91C_MCI_RTOE        [expr 0x1 << 20 ]
set AT91C_MCI_DCRCE       [expr 0x1 << 21 ]
set AT91C_MCI_DTOE        [expr 0x1 << 22 ]
set AT91C_MCI_CSTOE       [expr 0x1 << 23 ]
set AT91C_MCI_BLKOVRE     [expr 0x1 << 24 ]
set AT91C_MCI_DMADONE     [expr 0x1 << 25 ]
set AT91C_MCI_FIFOEMPTY   [expr 0x1 << 26 ]
set AT91C_MCI_XFRDONE     [expr 0x1 << 27 ]
set AT91C_MCI_OVRE        [expr 0x1 << 30 ]
set AT91C_MCI_UNRE        [expr 0x1 << 31 ]
# -------- MCI_IER : (MCI Offset: 0x44) MCI Interrupt Enable Register -------- 
set AT91C_MCI_CMDRDY      [expr 0x1 <<  0 ]
set AT91C_MCI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_MCI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_MCI_BLKE        [expr 0x1 <<  3 ]
set AT91C_MCI_DTIP        [expr 0x1 <<  4 ]
set AT91C_MCI_NOTBUSY     [expr 0x1 <<  5 ]
set AT91C_MCI_ENDRX       [expr 0x1 <<  6 ]
set AT91C_MCI_ENDTX       [expr 0x1 <<  7 ]
set AT91C_MCI_SDIOIRQA    [expr 0x1 <<  8 ]
set AT91C_MCI_SDIOIRQB    [expr 0x1 <<  9 ]
set AT91C_MCI_SDIOIRQC    [expr 0x1 << 10 ]
set AT91C_MCI_SDIOIRQD    [expr 0x1 << 11 ]
set AT91C_MCI_SDIOWAIT    [expr 0x1 << 12 ]
set AT91C_MCI_CSRCV       [expr 0x1 << 13 ]
set AT91C_MCI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_MCI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_MCI_RINDE       [expr 0x1 << 16 ]
set AT91C_MCI_RDIRE       [expr 0x1 << 17 ]
set AT91C_MCI_RCRCE       [expr 0x1 << 18 ]
set AT91C_MCI_RENDE       [expr 0x1 << 19 ]
set AT91C_MCI_RTOE        [expr 0x1 << 20 ]
set AT91C_MCI_DCRCE       [expr 0x1 << 21 ]
set AT91C_MCI_DTOE        [expr 0x1 << 22 ]
set AT91C_MCI_CSTOE       [expr 0x1 << 23 ]
set AT91C_MCI_BLKOVRE     [expr 0x1 << 24 ]
set AT91C_MCI_DMADONE     [expr 0x1 << 25 ]
set AT91C_MCI_FIFOEMPTY   [expr 0x1 << 26 ]
set AT91C_MCI_XFRDONE     [expr 0x1 << 27 ]
set AT91C_MCI_OVRE        [expr 0x1 << 30 ]
set AT91C_MCI_UNRE        [expr 0x1 << 31 ]
# -------- MCI_IDR : (MCI Offset: 0x48) MCI Interrupt Disable Register -------- 
set AT91C_MCI_CMDRDY      [expr 0x1 <<  0 ]
set AT91C_MCI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_MCI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_MCI_BLKE        [expr 0x1 <<  3 ]
set AT91C_MCI_DTIP        [expr 0x1 <<  4 ]
set AT91C_MCI_NOTBUSY     [expr 0x1 <<  5 ]
set AT91C_MCI_ENDRX       [expr 0x1 <<  6 ]
set AT91C_MCI_ENDTX       [expr 0x1 <<  7 ]
set AT91C_MCI_SDIOIRQA    [expr 0x1 <<  8 ]
set AT91C_MCI_SDIOIRQB    [expr 0x1 <<  9 ]
set AT91C_MCI_SDIOIRQC    [expr 0x1 << 10 ]
set AT91C_MCI_SDIOIRQD    [expr 0x1 << 11 ]
set AT91C_MCI_SDIOWAIT    [expr 0x1 << 12 ]
set AT91C_MCI_CSRCV       [expr 0x1 << 13 ]
set AT91C_MCI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_MCI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_MCI_RINDE       [expr 0x1 << 16 ]
set AT91C_MCI_RDIRE       [expr 0x1 << 17 ]
set AT91C_MCI_RCRCE       [expr 0x1 << 18 ]
set AT91C_MCI_RENDE       [expr 0x1 << 19 ]
set AT91C_MCI_RTOE        [expr 0x1 << 20 ]
set AT91C_MCI_DCRCE       [expr 0x1 << 21 ]
set AT91C_MCI_DTOE        [expr 0x1 << 22 ]
set AT91C_MCI_CSTOE       [expr 0x1 << 23 ]
set AT91C_MCI_BLKOVRE     [expr 0x1 << 24 ]
set AT91C_MCI_DMADONE     [expr 0x1 << 25 ]
set AT91C_MCI_FIFOEMPTY   [expr 0x1 << 26 ]
set AT91C_MCI_XFRDONE     [expr 0x1 << 27 ]
set AT91C_MCI_OVRE        [expr 0x1 << 30 ]
set AT91C_MCI_UNRE        [expr 0x1 << 31 ]
# -------- MCI_IMR : (MCI Offset: 0x4c) MCI Interrupt Mask Register -------- 
set AT91C_MCI_CMDRDY      [expr 0x1 <<  0 ]
set AT91C_MCI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_MCI_TXRDY       [expr 0x1 <<  2 ]
set AT91C_MCI_BLKE        [expr 0x1 <<  3 ]
set AT91C_MCI_DTIP        [expr 0x1 <<  4 ]
set AT91C_MCI_NOTBUSY     [expr 0x1 <<  5 ]
set AT91C_MCI_ENDRX       [expr 0x1 <<  6 ]
set AT91C_MCI_ENDTX       [expr 0x1 <<  7 ]
set AT91C_MCI_SDIOIRQA    [expr 0x1 <<  8 ]
set AT91C_MCI_SDIOIRQB    [expr 0x1 <<  9 ]
set AT91C_MCI_SDIOIRQC    [expr 0x1 << 10 ]
set AT91C_MCI_SDIOIRQD    [expr 0x1 << 11 ]
set AT91C_MCI_SDIOWAIT    [expr 0x1 << 12 ]
set AT91C_MCI_CSRCV       [expr 0x1 << 13 ]
set AT91C_MCI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_MCI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_MCI_RINDE       [expr 0x1 << 16 ]
set AT91C_MCI_RDIRE       [expr 0x1 << 17 ]
set AT91C_MCI_RCRCE       [expr 0x1 << 18 ]
set AT91C_MCI_RENDE       [expr 0x1 << 19 ]
set AT91C_MCI_RTOE        [expr 0x1 << 20 ]
set AT91C_MCI_DCRCE       [expr 0x1 << 21 ]
set AT91C_MCI_DTOE        [expr 0x1 << 22 ]
set AT91C_MCI_CSTOE       [expr 0x1 << 23 ]
set AT91C_MCI_BLKOVRE     [expr 0x1 << 24 ]
set AT91C_MCI_DMADONE     [expr 0x1 << 25 ]
set AT91C_MCI_FIFOEMPTY   [expr 0x1 << 26 ]
set AT91C_MCI_XFRDONE     [expr 0x1 << 27 ]
set AT91C_MCI_OVRE        [expr 0x1 << 30 ]
set AT91C_MCI_UNRE        [expr 0x1 << 31 ]
# -------- MCI_DMA : (MCI Offset: 0x50) MCI DMA Configuration Register -------- 
set AT91C_MCI_OFFSET      [expr 0x3 <<  0 ]
set AT91C_MCI_CHKSIZE     [expr 0x7 <<  4 ]
set 	AT91C_MCI_CHKSIZE_1                    [expr 0x0 <<  4 ]
set 	AT91C_MCI_CHKSIZE_4                    [expr 0x1 <<  4 ]
set 	AT91C_MCI_CHKSIZE_8                    [expr 0x2 <<  4 ]
set 	AT91C_MCI_CHKSIZE_16                   [expr 0x3 <<  4 ]
set 	AT91C_MCI_CHKSIZE_32                   [expr 0x4 <<  4 ]
set AT91C_MCI_DMAEN       [expr 0x1 <<  8 ]
set 	AT91C_MCI_DMAEN_DISABLE              [expr 0x0 <<  8 ]
set 	AT91C_MCI_DMAEN_ENABLE               [expr 0x1 <<  8 ]
# -------- MCI_CFG : (MCI Offset: 0x54) MCI Configuration Register -------- 
set AT91C_MCI_FIFOMODE    [expr 0x1 <<  0 ]
set 	AT91C_MCI_FIFOMODE_AMOUNTDATA           0x0
set 	AT91C_MCI_FIFOMODE_ONEDATA              0x1
set AT91C_MCI_FERRCTRL    [expr 0x1 <<  4 ]
set 	AT91C_MCI_FERRCTRL_RWCMD                [expr 0x0 <<  4 ]
set 	AT91C_MCI_FERRCTRL_READSR               [expr 0x1 <<  4 ]
set AT91C_MCI_HSMODE      [expr 0x1 <<  8 ]
set 	AT91C_MCI_HSMODE_DISABLE              [expr 0x0 <<  8 ]
set 	AT91C_MCI_HSMODE_ENABLE               [expr 0x1 <<  8 ]
set AT91C_MCI_LSYNC       [expr 0x1 << 12 ]
set 	AT91C_MCI_LSYNC_CURRENT              [expr 0x0 << 12 ]
set 	AT91C_MCI_LSYNC_INFINITE             [expr 0x1 << 12 ]
# -------- MCI_WPCR : (MCI Offset: 0xe4) Write Protection Control Register -------- 
set AT91C_MCI_WP_EN       [expr 0x1 <<  0 ]
set 	AT91C_MCI_WP_EN_DISABLE              0x0
set 	AT91C_MCI_WP_EN_ENABLE               0x1
set AT91C_MCI_WP_KEY      [expr 0xFFFFFF <<  8 ]
# -------- MCI_WPSR : (MCI Offset: 0xe8) Write Protection Status Register -------- 
set AT91C_MCI_WP_VS       [expr 0xF <<  0 ]
set 	AT91C_MCI_WP_VS_NO_VIOLATION         0x0
set 	AT91C_MCI_WP_VS_ON_WRITE             0x1
set 	AT91C_MCI_WP_VS_ON_RESET             0x2
set 	AT91C_MCI_WP_VS_ON_BOTH              0x3
set AT91C_MCI_WP_VSRC     [expr 0xF <<  8 ]
set 	AT91C_MCI_WP_VSRC_NO_VIOLATION         [expr 0x0 <<  8 ]
set 	AT91C_MCI_WP_VSRC_MCI_MR               [expr 0x1 <<  8 ]
set 	AT91C_MCI_WP_VSRC_MCI_DTOR             [expr 0x2 <<  8 ]
set 	AT91C_MCI_WP_VSRC_MCI_SDCR             [expr 0x3 <<  8 ]
set 	AT91C_MCI_WP_VSRC_MCI_CSTOR            [expr 0x4 <<  8 ]
set 	AT91C_MCI_WP_VSRC_MCI_DMA              [expr 0x5 <<  8 ]
set 	AT91C_MCI_WP_VSRC_MCI_CFG              [expr 0x6 <<  8 ]
set 	AT91C_MCI_WP_VSRC_MCI_DEL              [expr 0x7 <<  8 ]
# -------- MCI_VER : (MCI Offset: 0xfc)  VERSION  Register -------- 
set AT91C_MCI_VER         [expr 0xF <<  0 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Two-wire Interface
# *****************************************************************************
# -------- TWI_CR : (TWI Offset: 0x0) TWI Control Register -------- 
set AT91C_TWI_START       [expr 0x1 <<  0 ]
set AT91C_TWI_STOP        [expr 0x1 <<  1 ]
set AT91C_TWI_MSEN        [expr 0x1 <<  2 ]
set AT91C_TWI_MSDIS       [expr 0x1 <<  3 ]
set AT91C_TWI_SVEN        [expr 0x1 <<  4 ]
set AT91C_TWI_SVDIS       [expr 0x1 <<  5 ]
set AT91C_TWI_SWRST       [expr 0x1 <<  7 ]
# -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- 
set AT91C_TWI_IADRSZ      [expr 0x3 <<  8 ]
set 	AT91C_TWI_IADRSZ_NO                   [expr 0x0 <<  8 ]
set 	AT91C_TWI_IADRSZ_1_BYTE               [expr 0x1 <<  8 ]
set 	AT91C_TWI_IADRSZ_2_BYTE               [expr 0x2 <<  8 ]
set 	AT91C_TWI_IADRSZ_3_BYTE               [expr 0x3 <<  8 ]
set AT91C_TWI_MREAD       [expr 0x1 << 12 ]
set AT91C_TWI_DADR        [expr 0x7F << 16 ]
# -------- TWI_SMR : (TWI Offset: 0x8) TWI Slave Mode Register -------- 
set AT91C_TWI_SADR        [expr 0x7F << 16 ]
# -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- 
set AT91C_TWI_CLDIV       [expr 0xFF <<  0 ]
set AT91C_TWI_CHDIV       [expr 0xFF <<  8 ]
set AT91C_TWI_CKDIV       [expr 0x7 << 16 ]
# -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- 
set AT91C_TWI_TXCOMP_SLAVE [expr 0x1 <<  0 ]
set AT91C_TWI_TXCOMP_MASTER [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY_MASTER [expr 0x1 <<  2 ]
set AT91C_TWI_TXRDY_SLAVE [expr 0x1 <<  2 ]
set AT91C_TWI_SVREAD      [expr 0x1 <<  3 ]
set AT91C_TWI_SVACC       [expr 0x1 <<  4 ]
set AT91C_TWI_GACC        [expr 0x1 <<  5 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_NACK_SLAVE  [expr 0x1 <<  8 ]
set AT91C_TWI_NACK_MASTER [expr 0x1 <<  8 ]
set AT91C_TWI_ARBLST_MULTI_MASTER [expr 0x1 <<  9 ]
set AT91C_TWI_SCLWS       [expr 0x1 << 10 ]
set AT91C_TWI_EOSACC      [expr 0x1 << 11 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
# -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- 
set AT91C_TWI_TXCOMP_SLAVE [expr 0x1 <<  0 ]
set AT91C_TWI_TXCOMP_MASTER [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY_MASTER [expr 0x1 <<  2 ]
set AT91C_TWI_TXRDY_SLAVE [expr 0x1 <<  2 ]
set AT91C_TWI_SVREAD      [expr 0x1 <<  3 ]
set AT91C_TWI_SVACC       [expr 0x1 <<  4 ]
set AT91C_TWI_GACC        [expr 0x1 <<  5 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_NACK_SLAVE  [expr 0x1 <<  8 ]
set AT91C_TWI_NACK_MASTER [expr 0x1 <<  8 ]
set AT91C_TWI_ARBLST_MULTI_MASTER [expr 0x1 <<  9 ]
set AT91C_TWI_SCLWS       [expr 0x1 << 10 ]
set AT91C_TWI_EOSACC      [expr 0x1 << 11 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
# -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- 
set AT91C_TWI_TXCOMP_SLAVE [expr 0x1 <<  0 ]
set AT91C_TWI_TXCOMP_MASTER [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY_MASTER [expr 0x1 <<  2 ]
set AT91C_TWI_TXRDY_SLAVE [expr 0x1 <<  2 ]
set AT91C_TWI_SVREAD      [expr 0x1 <<  3 ]
set AT91C_TWI_SVACC       [expr 0x1 <<  4 ]
set AT91C_TWI_GACC        [expr 0x1 <<  5 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_NACK_SLAVE  [expr 0x1 <<  8 ]
set AT91C_TWI_NACK_MASTER [expr 0x1 <<  8 ]
set AT91C_TWI_ARBLST_MULTI_MASTER [expr 0x1 <<  9 ]
set AT91C_TWI_SCLWS       [expr 0x1 << 10 ]
set AT91C_TWI_EOSACC      [expr 0x1 << 11 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
# -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- 
set AT91C_TWI_TXCOMP_SLAVE [expr 0x1 <<  0 ]
set AT91C_TWI_TXCOMP_MASTER [expr 0x1 <<  0 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_RXRDY       [expr 0x1 <<  1 ]
set AT91C_TWI_TXRDY_MASTER [expr 0x1 <<  2 ]
set AT91C_TWI_TXRDY_SLAVE [expr 0x1 <<  2 ]
set AT91C_TWI_SVREAD      [expr 0x1 <<  3 ]
set AT91C_TWI_SVACC       [expr 0x1 <<  4 ]
set AT91C_TWI_GACC        [expr 0x1 <<  5 ]
set AT91C_TWI_OVRE        [expr 0x1 <<  6 ]
set AT91C_TWI_NACK_SLAVE  [expr 0x1 <<  8 ]
set AT91C_TWI_NACK_MASTER [expr 0x1 <<  8 ]
set AT91C_TWI_ARBLST_MULTI_MASTER [expr 0x1 <<  9 ]
set AT91C_TWI_SCLWS       [expr 0x1 << 10 ]
set AT91C_TWI_EOSACC      [expr 0x1 << 11 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDRX       [expr 0x1 << 12 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_ENDTX       [expr 0x1 << 13 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_RXBUFF      [expr 0x1 << 14 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]
set AT91C_TWI_TXBUFE      [expr 0x1 << 15 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Usart
# *****************************************************************************
# -------- US_CR : (USART Offset: 0x0)  Control Register -------- 
set AT91C_US_RSTRX        [expr 0x1 <<  2 ]
set AT91C_US_RSTTX        [expr 0x1 <<  3 ]
set AT91C_US_RXEN         [expr 0x1 <<  4 ]
set AT91C_US_RXDIS        [expr 0x1 <<  5 ]
set AT91C_US_TXEN         [expr 0x1 <<  6 ]
set AT91C_US_TXDIS        [expr 0x1 <<  7 ]
set AT91C_US_RSTSTA       [expr 0x1 <<  8 ]
set AT91C_US_STTBRK       [expr 0x1 <<  9 ]
set AT91C_US_STPBRK       [expr 0x1 << 10 ]
set AT91C_US_STTTO        [expr 0x1 << 11 ]
set AT91C_US_SENDA        [expr 0x1 << 12 ]
set AT91C_US_RSTIT        [expr 0x1 << 13 ]
set AT91C_US_RSTNACK      [expr 0x1 << 14 ]
set AT91C_US_RETTO        [expr 0x1 << 15 ]
set AT91C_US_DTREN        [expr 0x1 << 16 ]
set AT91C_US_DTRDIS       [expr 0x1 << 17 ]
set AT91C_US_RTSEN        [expr 0x1 << 18 ]
set AT91C_US_RTSDIS       [expr 0x1 << 19 ]
# -------- US_MR : (USART Offset: 0x4)  Mode Register -------- 
set AT91C_US_USMODE       [expr 0xF <<  0 ]
set 	AT91C_US_USMODE_NORMAL               0x0
set 	AT91C_US_USMODE_RS485                0x1
set 	AT91C_US_USMODE_HWHSH                0x2
set 	AT91C_US_USMODE_MODEM                0x3
set 	AT91C_US_USMODE_ISO7816_0            0x4
set 	AT91C_US_USMODE_ISO7816_1            0x6
set 	AT91C_US_USMODE_IRDA                 0x8
set AT91C_US_CLKS         [expr 0x3 <<  4 ]
set 	AT91C_US_CLKS_CLOCK                [expr 0x0 <<  4 ]
set 	AT91C_US_CLKS_FDIV1                [expr 0x1 <<  4 ]
set 	AT91C_US_CLKS_SLOW                 [expr 0x2 <<  4 ]
set 	AT91C_US_CLKS_EXT                  [expr 0x3 <<  4 ]
set AT91C_US_CHRL         [expr 0x3 <<  6 ]
set 	AT91C_US_CHRL_5_BITS               [expr 0x0 <<  6 ]
set 	AT91C_US_CHRL_6_BITS               [expr 0x1 <<  6 ]
set 	AT91C_US_CHRL_7_BITS               [expr 0x2 <<  6 ]
set 	AT91C_US_CHRL_8_BITS               [expr 0x3 <<  6 ]
set AT91C_US_SYNC         [expr 0x1 <<  8 ]
set AT91C_US_PAR          [expr 0x7 <<  9 ]
set 	AT91C_US_PAR_EVEN                 [expr 0x0 <<  9 ]
set 	AT91C_US_PAR_ODD                  [expr 0x1 <<  9 ]
set 	AT91C_US_PAR_SPACE                [expr 0x2 <<  9 ]
set 	AT91C_US_PAR_MARK                 [expr 0x3 <<  9 ]
set 	AT91C_US_PAR_NONE                 [expr 0x4 <<  9 ]
set 	AT91C_US_PAR_MULTI_DROP           [expr 0x6 <<  9 ]
set AT91C_US_NBSTOP       [expr 0x3 << 12 ]
set 	AT91C_US_NBSTOP_1_BIT                [expr 0x0 << 12 ]
set 	AT91C_US_NBSTOP_15_BIT               [expr 0x1 << 12 ]
set 	AT91C_US_NBSTOP_2_BIT                [expr 0x2 << 12 ]
set AT91C_US_CHMODE       [expr 0x3 << 14 ]
set 	AT91C_US_CHMODE_NORMAL               [expr 0x0 << 14 ]
set 	AT91C_US_CHMODE_AUTO                 [expr 0x1 << 14 ]
set 	AT91C_US_CHMODE_LOCAL                [expr 0x2 << 14 ]
set 	AT91C_US_CHMODE_REMOTE               [expr 0x3 << 14 ]
set AT91C_US_MSBF         [expr 0x1 << 16 ]
set AT91C_US_MODE9        [expr 0x1 << 17 ]
set AT91C_US_CKLO         [expr 0x1 << 18 ]
set AT91C_US_OVER         [expr 0x1 << 19 ]
set AT91C_US_INACK        [expr 0x1 << 20 ]
set AT91C_US_DSNACK       [expr 0x1 << 21 ]
set AT91C_US_VAR_SYNC     [expr 0x1 << 22 ]
set AT91C_US_MAX_ITER     [expr 0x1 << 24 ]
set AT91C_US_FILTER       [expr 0x1 << 28 ]
set AT91C_US_MANMODE      [expr 0x1 << 29 ]
set AT91C_US_MODSYNC      [expr 0x1 << 30 ]
set AT91C_US_ONEBIT       [expr 0x1 << 31 ]
# -------- US_IER : (USART Offset: 0x8)  Interrupt Enable Register -------- 
set AT91C_US_RXRDY        [expr 0x1 <<  0 ]
set AT91C_US_TXRDY        [expr 0x1 <<  1 ]
set AT91C_US_RXBRK        [expr 0x1 <<  2 ]
set AT91C_US_ENDRX        [expr 0x1 <<  3 ]
set AT91C_US_ENDTX        [expr 0x1 <<  4 ]
set AT91C_US_OVRE         [expr 0x1 <<  5 ]
set AT91C_US_FRAME        [expr 0x1 <<  6 ]
set AT91C_US_PARE         [expr 0x1 <<  7 ]
set AT91C_US_TIMEOUT      [expr 0x1 <<  8 ]
set AT91C_US_TXEMPTY      [expr 0x1 <<  9 ]
set AT91C_US_ITERATION    [expr 0x1 << 10 ]
set AT91C_US_TXBUFE       [expr 0x1 << 11 ]
set AT91C_US_RXBUFF       [expr 0x1 << 12 ]
set AT91C_US_NACK         [expr 0x1 << 13 ]
set AT91C_US_RIIC         [expr 0x1 << 16 ]
set AT91C_US_DSRIC        [expr 0x1 << 17 ]
set AT91C_US_DCDIC        [expr 0x1 << 18 ]
set AT91C_US_CTSIC        [expr 0x1 << 19 ]
set AT91C_US_MANE         [expr 0x1 << 20 ]
# -------- US_IDR : (USART Offset: 0xc)  Interrupt Disable Register -------- 
set AT91C_US_RXRDY        [expr 0x1 <<  0 ]
set AT91C_US_TXRDY        [expr 0x1 <<  1 ]
set AT91C_US_RXBRK        [expr 0x1 <<  2 ]
set AT91C_US_ENDRX        [expr 0x1 <<  3 ]
set AT91C_US_ENDTX        [expr 0x1 <<  4 ]
set AT91C_US_OVRE         [expr 0x1 <<  5 ]
set AT91C_US_FRAME        [expr 0x1 <<  6 ]
set AT91C_US_PARE         [expr 0x1 <<  7 ]
set AT91C_US_TIMEOUT      [expr 0x1 <<  8 ]
set AT91C_US_TXEMPTY      [expr 0x1 <<  9 ]
set AT91C_US_ITERATION    [expr 0x1 << 10 ]
set AT91C_US_TXBUFE       [expr 0x1 << 11 ]
set AT91C_US_RXBUFF       [expr 0x1 << 12 ]
set AT91C_US_NACK         [expr 0x1 << 13 ]
set AT91C_US_RIIC         [expr 0x1 << 16 ]
set AT91C_US_DSRIC        [expr 0x1 << 17 ]
set AT91C_US_DCDIC        [expr 0x1 << 18 ]
set AT91C_US_CTSIC        [expr 0x1 << 19 ]
set AT91C_US_MANE         [expr 0x1 << 20 ]
# -------- US_IMR : (USART Offset: 0x10)  Interrupt Mask Register -------- 
set AT91C_US_RXRDY        [expr 0x1 <<  0 ]
set AT91C_US_TXRDY        [expr 0x1 <<  1 ]
set AT91C_US_RXBRK        [expr 0x1 <<  2 ]
set AT91C_US_ENDRX        [expr 0x1 <<  3 ]
set AT91C_US_ENDTX        [expr 0x1 <<  4 ]
set AT91C_US_OVRE         [expr 0x1 <<  5 ]
set AT91C_US_FRAME        [expr 0x1 <<  6 ]
set AT91C_US_PARE         [expr 0x1 <<  7 ]
set AT91C_US_TIMEOUT      [expr 0x1 <<  8 ]
set AT91C_US_TXEMPTY      [expr 0x1 <<  9 ]
set AT91C_US_ITERATION    [expr 0x1 << 10 ]
set AT91C_US_TXBUFE       [expr 0x1 << 11 ]
set AT91C_US_RXBUFF       [expr 0x1 << 12 ]
set AT91C_US_NACK         [expr 0x1 << 13 ]
set AT91C_US_RIIC         [expr 0x1 << 16 ]
set AT91C_US_DSRIC        [expr 0x1 << 17 ]
set AT91C_US_DCDIC        [expr 0x1 << 18 ]
set AT91C_US_CTSIC        [expr 0x1 << 19 ]
set AT91C_US_MANE         [expr 0x1 << 20 ]
# -------- US_CSR : (USART Offset: 0x14)  Channel Status Register -------- 
set AT91C_US_RXRDY        [expr 0x1 <<  0 ]
set AT91C_US_TXRDY        [expr 0x1 <<  1 ]
set AT91C_US_RXBRK        [expr 0x1 <<  2 ]
set AT91C_US_ENDRX        [expr 0x1 <<  3 ]
set AT91C_US_ENDTX        [expr 0x1 <<  4 ]
set AT91C_US_OVRE         [expr 0x1 <<  5 ]
set AT91C_US_FRAME        [expr 0x1 <<  6 ]
set AT91C_US_PARE         [expr 0x1 <<  7 ]
set AT91C_US_TIMEOUT      [expr 0x1 <<  8 ]
set AT91C_US_TXEMPTY      [expr 0x1 <<  9 ]
set AT91C_US_ITERATION    [expr 0x1 << 10 ]
set AT91C_US_TXBUFE       [expr 0x1 << 11 ]
set AT91C_US_RXBUFF       [expr 0x1 << 12 ]
set AT91C_US_NACK         [expr 0x1 << 13 ]
set AT91C_US_RIIC         [expr 0x1 << 16 ]
set AT91C_US_DSRIC        [expr 0x1 << 17 ]
set AT91C_US_DCDIC        [expr 0x1 << 18 ]
set AT91C_US_CTSIC        [expr 0x1 << 19 ]
set AT91C_US_RI           [expr 0x1 << 20 ]
set AT91C_US_DSR          [expr 0x1 << 21 ]
set AT91C_US_DCD          [expr 0x1 << 22 ]
set AT91C_US_CTS          [expr 0x1 << 23 ]
set AT91C_US_MANERR       [expr 0x1 << 24 ]
# -------- US_MAN : (USART Offset: 0x50) Manchester Encoder Decoder Register -------- 
set AT91C_US_TX_PL        [expr 0xF <<  0 ]
set AT91C_US_TX_PP        [expr 0x3 <<  8 ]
set 	AT91C_US_TX_PP_ALL_ONE              [expr 0x0 <<  8 ]
set 	AT91C_US_TX_PP_ALL_ZERO             [expr 0x1 <<  8 ]
set 	AT91C_US_TX_PP_ZERO_ONE             [expr 0x2 <<  8 ]
set 	AT91C_US_TX_PP_ONE_ZERO             [expr 0x3 <<  8 ]
set AT91C_US_TX_MPOL      [expr 0x1 << 12 ]
set AT91C_US_RX_PL        [expr 0xF << 16 ]
set AT91C_US_RX_PP        [expr 0x3 << 24 ]
set 	AT91C_US_RX_PP_ALL_ONE              [expr 0x0 << 24 ]
set 	AT91C_US_RX_PP_ALL_ZERO             [expr 0x1 << 24 ]
set 	AT91C_US_RX_PP_ZERO_ONE             [expr 0x2 << 24 ]
set 	AT91C_US_RX_PP_ONE_ZERO             [expr 0x3 << 24 ]
set AT91C_US_RX_MPOL      [expr 0x1 << 28 ]
set AT91C_US_DRIFT        [expr 0x1 << 30 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Synchronous Serial Controller Interface
# *****************************************************************************
# -------- SSC_CR : (SSC Offset: 0x0) SSC Control Register -------- 
set AT91C_SSC_RXEN        [expr 0x1 <<  0 ]
set AT91C_SSC_RXDIS       [expr 0x1 <<  1 ]
set AT91C_SSC_TXEN        [expr 0x1 <<  8 ]
set AT91C_SSC_TXDIS       [expr 0x1 <<  9 ]
set AT91C_SSC_SWRST       [expr 0x1 << 15 ]
# -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- 
set AT91C_SSC_CKS         [expr 0x3 <<  0 ]
set 	AT91C_SSC_CKS_DIV                  0x0
set 	AT91C_SSC_CKS_TK                   0x1
set 	AT91C_SSC_CKS_RK                   0x2
set AT91C_SSC_CKO         [expr 0x7 <<  2 ]
set 	AT91C_SSC_CKO_NONE                 [expr 0x0 <<  2 ]
set 	AT91C_SSC_CKO_CONTINOUS            [expr 0x1 <<  2 ]
set 	AT91C_SSC_CKO_DATA_TX              [expr 0x2 <<  2 ]
set AT91C_SSC_CKI         [expr 0x1 <<  5 ]
set AT91C_SSC_CKG         [expr 0x3 <<  6 ]
set 	AT91C_SSC_CKG_NONE                 [expr 0x0 <<  6 ]
set 	AT91C_SSC_CKG_LOW                  [expr 0x1 <<  6 ]
set 	AT91C_SSC_CKG_HIGH                 [expr 0x2 <<  6 ]
set AT91C_SSC_START       [expr 0xF <<  8 ]
set 	AT91C_SSC_START_CONTINOUS            [expr 0x0 <<  8 ]
set 	AT91C_SSC_START_TX                   [expr 0x1 <<  8 ]
set 	AT91C_SSC_START_LOW_RF               [expr 0x2 <<  8 ]
set 	AT91C_SSC_START_HIGH_RF              [expr 0x3 <<  8 ]
set 	AT91C_SSC_START_FALL_RF              [expr 0x4 <<  8 ]
set 	AT91C_SSC_START_RISE_RF              [expr 0x5 <<  8 ]
set 	AT91C_SSC_START_LEVEL_RF             [expr 0x6 <<  8 ]
set 	AT91C_SSC_START_EDGE_RF              [expr 0x7 <<  8 ]
set 	AT91C_SSC_START_0                    [expr 0x8 <<  8 ]
set AT91C_SSC_STOP        [expr 0x1 << 12 ]
set AT91C_SSC_STTDLY      [expr 0xFF << 16 ]
set AT91C_SSC_PERIOD      [expr 0xFF << 24 ]
# -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- 
set AT91C_SSC_DATLEN      [expr 0x1F <<  0 ]
set AT91C_SSC_LOOP        [expr 0x1 <<  5 ]
set AT91C_SSC_MSBF        [expr 0x1 <<  7 ]
set AT91C_SSC_DATNB       [expr 0xF <<  8 ]
set AT91C_SSC_FSLEN       [expr 0xF << 16 ]
set AT91C_SSC_FSOS        [expr 0x7 << 20 ]
set 	AT91C_SSC_FSOS_NONE                 [expr 0x0 << 20 ]
set 	AT91C_SSC_FSOS_NEGATIVE             [expr 0x1 << 20 ]
set 	AT91C_SSC_FSOS_POSITIVE             [expr 0x2 << 20 ]
set 	AT91C_SSC_FSOS_LOW                  [expr 0x3 << 20 ]
set 	AT91C_SSC_FSOS_HIGH                 [expr 0x4 << 20 ]
set 	AT91C_SSC_FSOS_TOGGLE               [expr 0x5 << 20 ]
set AT91C_SSC_FSEDGE      [expr 0x1 << 24 ]
# -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- 
set AT91C_SSC_CKS         [expr 0x3 <<  0 ]
set 	AT91C_SSC_CKS_DIV                  0x0
set 	AT91C_SSC_CKS_TK                   0x1
set 	AT91C_SSC_CKS_RK                   0x2
set AT91C_SSC_CKO         [expr 0x7 <<  2 ]
set 	AT91C_SSC_CKO_NONE                 [expr 0x0 <<  2 ]
set 	AT91C_SSC_CKO_CONTINOUS            [expr 0x1 <<  2 ]
set 	AT91C_SSC_CKO_DATA_TX              [expr 0x2 <<  2 ]
set AT91C_SSC_CKI         [expr 0x1 <<  5 ]
set AT91C_SSC_CKG         [expr 0x3 <<  6 ]
set 	AT91C_SSC_CKG_NONE                 [expr 0x0 <<  6 ]
set 	AT91C_SSC_CKG_LOW                  [expr 0x1 <<  6 ]
set 	AT91C_SSC_CKG_HIGH                 [expr 0x2 <<  6 ]
set AT91C_SSC_START       [expr 0xF <<  8 ]
set 	AT91C_SSC_START_CONTINOUS            [expr 0x0 <<  8 ]
set 	AT91C_SSC_START_TX                   [expr 0x1 <<  8 ]
set 	AT91C_SSC_START_LOW_RF               [expr 0x2 <<  8 ]
set 	AT91C_SSC_START_HIGH_RF              [expr 0x3 <<  8 ]
set 	AT91C_SSC_START_FALL_RF              [expr 0x4 <<  8 ]
set 	AT91C_SSC_START_RISE_RF              [expr 0x5 <<  8 ]
set 	AT91C_SSC_START_LEVEL_RF             [expr 0x6 <<  8 ]
set 	AT91C_SSC_START_EDGE_RF              [expr 0x7 <<  8 ]
set 	AT91C_SSC_START_0                    [expr 0x8 <<  8 ]
set AT91C_SSC_STTDLY      [expr 0xFF << 16 ]
set AT91C_SSC_PERIOD      [expr 0xFF << 24 ]
# -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- 
set AT91C_SSC_DATLEN      [expr 0x1F <<  0 ]
set AT91C_SSC_DATDEF      [expr 0x1 <<  5 ]
set AT91C_SSC_MSBF        [expr 0x1 <<  7 ]
set AT91C_SSC_DATNB       [expr 0xF <<  8 ]
set AT91C_SSC_FSLEN       [expr 0xF << 16 ]
set AT91C_SSC_FSOS        [expr 0x7 << 20 ]
set 	AT91C_SSC_FSOS_NONE                 [expr 0x0 << 20 ]
set 	AT91C_SSC_FSOS_NEGATIVE             [expr 0x1 << 20 ]
set 	AT91C_SSC_FSOS_POSITIVE             [expr 0x2 << 20 ]
set 	AT91C_SSC_FSOS_LOW                  [expr 0x3 << 20 ]
set 	AT91C_SSC_FSOS_HIGH                 [expr 0x4 << 20 ]
set 	AT91C_SSC_FSOS_TOGGLE               [expr 0x5 << 20 ]
set AT91C_SSC_FSDEN       [expr 0x1 << 23 ]
set AT91C_SSC_FSEDGE      [expr 0x1 << 24 ]
# -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- 
set AT91C_SSC_TXRDY       [expr 0x1 <<  0 ]
set AT91C_SSC_TXEMPTY     [expr 0x1 <<  1 ]
set AT91C_SSC_ENDTX       [expr 0x1 <<  2 ]
set AT91C_SSC_TXBUFE      [expr 0x1 <<  3 ]
set AT91C_SSC_RXRDY       [expr 0x1 <<  4 ]
set AT91C_SSC_OVRUN       [expr 0x1 <<  5 ]
set AT91C_SSC_ENDRX       [expr 0x1 <<  6 ]
set AT91C_SSC_RXBUFF      [expr 0x1 <<  7 ]
set AT91C_SSC_CP0         [expr 0x1 <<  8 ]
set AT91C_SSC_CP1         [expr 0x1 <<  9 ]
set AT91C_SSC_TXSYN       [expr 0x1 << 10 ]
set AT91C_SSC_RXSYN       [expr 0x1 << 11 ]
set AT91C_SSC_TXENA       [expr 0x1 << 16 ]
set AT91C_SSC_RXENA       [expr 0x1 << 17 ]
# -------- SSC_IER : (SSC Offset: 0x44) SSC Interrupt Enable Register -------- 
set AT91C_SSC_TXRDY       [expr 0x1 <<  0 ]
set AT91C_SSC_TXEMPTY     [expr 0x1 <<  1 ]
set AT91C_SSC_ENDTX       [expr 0x1 <<  2 ]
set AT91C_SSC_TXBUFE      [expr 0x1 <<  3 ]
set AT91C_SSC_RXRDY       [expr 0x1 <<  4 ]
set AT91C_SSC_OVRUN       [expr 0x1 <<  5 ]
set AT91C_SSC_ENDRX       [expr 0x1 <<  6 ]
set AT91C_SSC_RXBUFF      [expr 0x1 <<  7 ]
set AT91C_SSC_CP0         [expr 0x1 <<  8 ]
set AT91C_SSC_CP1         [expr 0x1 <<  9 ]
set AT91C_SSC_TXSYN       [expr 0x1 << 10 ]
set AT91C_SSC_RXSYN       [expr 0x1 << 11 ]
# -------- SSC_IDR : (SSC Offset: 0x48) SSC Interrupt Disable Register -------- 
set AT91C_SSC_TXRDY       [expr 0x1 <<  0 ]
set AT91C_SSC_TXEMPTY     [expr 0x1 <<  1 ]
set AT91C_SSC_ENDTX       [expr 0x1 <<  2 ]
set AT91C_SSC_TXBUFE      [expr 0x1 <<  3 ]
set AT91C_SSC_RXRDY       [expr 0x1 <<  4 ]
set AT91C_SSC_OVRUN       [expr 0x1 <<  5 ]
set AT91C_SSC_ENDRX       [expr 0x1 <<  6 ]
set AT91C_SSC_RXBUFF      [expr 0x1 <<  7 ]
set AT91C_SSC_CP0         [expr 0x1 <<  8 ]
set AT91C_SSC_CP1         [expr 0x1 <<  9 ]
set AT91C_SSC_TXSYN       [expr 0x1 << 10 ]
set AT91C_SSC_RXSYN       [expr 0x1 << 11 ]
# -------- SSC_IMR : (SSC Offset: 0x4c) SSC Interrupt Mask Register -------- 
set AT91C_SSC_TXRDY       [expr 0x1 <<  0 ]
set AT91C_SSC_TXEMPTY     [expr 0x1 <<  1 ]
set AT91C_SSC_ENDTX       [expr 0x1 <<  2 ]
set AT91C_SSC_TXBUFE      [expr 0x1 <<  3 ]
set AT91C_SSC_RXRDY       [expr 0x1 <<  4 ]
set AT91C_SSC_OVRUN       [expr 0x1 <<  5 ]
set AT91C_SSC_ENDRX       [expr 0x1 <<  6 ]
set AT91C_SSC_RXBUFF      [expr 0x1 <<  7 ]
set AT91C_SSC_CP0         [expr 0x1 <<  8 ]
set AT91C_SSC_CP1         [expr 0x1 <<  9 ]
set AT91C_SSC_TXSYN       [expr 0x1 << 10 ]
set AT91C_SSC_RXSYN       [expr 0x1 << 11 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR PWMC Channel Interface
# *****************************************************************************
# -------- PWMC_CMR : (PWMC_CH Offset: 0x0) PWMC Channel Mode Register -------- 
set AT91C_PWMC_CPRE       [expr 0xF <<  0 ]
set 	AT91C_PWMC_CPRE_MCK                  0x0
set 	AT91C_PWMC_CPRE_MCK_DIV_2            0x1
set 	AT91C_PWMC_CPRE_MCK_DIV_4            0x2
set 	AT91C_PWMC_CPRE_MCK_DIV_8            0x3
set 	AT91C_PWMC_CPRE_MCK_DIV_16           0x4
set 	AT91C_PWMC_CPRE_MCK_DIV_32           0x5
set 	AT91C_PWMC_CPRE_MCK_DIV_64           0x6
set 	AT91C_PWMC_CPRE_MCK_DIV_128          0x7
set 	AT91C_PWMC_CPRE_MCK_DIV_256          0x8
set 	AT91C_PWMC_CPRE_MCK_DIV_512          0x9
set 	AT91C_PWMC_CPRE_MCK_DIV_1024         0xA
set 	AT91C_PWMC_CPRE_MCKA                 0xB
set 	AT91C_PWMC_CPRE_MCKB                 0xC
set AT91C_PWMC_CALG       [expr 0x1 <<  8 ]
set AT91C_PWMC_CPOL       [expr 0x1 <<  9 ]
set AT91C_PWMC_CES        [expr 0x1 << 10 ]
set AT91C_PWMC_DTE        [expr 0x1 << 16 ]
set AT91C_PWMC_DTHI       [expr 0x1 << 17 ]
set AT91C_PWMC_DTLI       [expr 0x1 << 18 ]
# -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- 
set AT91C_PWMC_CDTY       [expr 0xFFFFFF <<  0 ]
# -------- PWMC_CDTYUPDR : (PWMC_CH Offset: 0x8) PWMC Channel Duty Cycle Update Register -------- 
set AT91C_PWMC_CDTYUPD    [expr 0xFFFFFF <<  0 ]
# -------- PWMC_CPRDR : (PWMC_CH Offset: 0xc) PWMC Channel Period Register -------- 
set AT91C_PWMC_CPRD       [expr 0xFFFFFF <<  0 ]
# -------- PWMC_CPRDUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Period Update Register -------- 
set AT91C_PWMC_CPRDUPD    [expr 0xFFFFFF <<  0 ]
# -------- PWMC_CCNTR : (PWMC_CH Offset: 0x14) PWMC Channel Counter Register -------- 
set AT91C_PWMC_CCNT       [expr 0xFFFFFF <<  0 ]
# -------- PWMC_DTR : (PWMC_CH Offset: 0x18) Channel Dead Time Value Register -------- 
set AT91C_PWMC_DTL        [expr 0xFFFF <<  0 ]
set AT91C_PWMC_DTH        [expr 0xFFFF << 16 ]
# -------- PWMC_DTUPDR : (PWMC_CH Offset: 0x1c) Channel Dead Time Value Register -------- 
set AT91C_PWMC_DTLUPD     [expr 0xFFFF <<  0 ]
set AT91C_PWMC_DTHUPD     [expr 0xFFFF << 16 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface
# *****************************************************************************
# -------- PWMC_MR : (PWMC Offset: 0x0) PWMC Mode Register -------- 
set AT91C_PWMC_DIVA       [expr 0xFF <<  0 ]
set AT91C_PWMC_PREA       [expr 0xF <<  8 ]
set 	AT91C_PWMC_PREA_MCK                  [expr 0x0 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_2            [expr 0x1 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_4            [expr 0x2 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_8            [expr 0x3 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_16           [expr 0x4 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_32           [expr 0x5 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_64           [expr 0x6 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_128          [expr 0x7 <<  8 ]
set 	AT91C_PWMC_PREA_MCK_DIV_256          [expr 0x8 <<  8 ]
set AT91C_PWMC_DIVB       [expr 0xFF << 16 ]
set AT91C_PWMC_PREB       [expr 0xF << 24 ]
set 	AT91C_PWMC_PREB_MCK                  [expr 0x0 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_2            [expr 0x1 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_4            [expr 0x2 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_8            [expr 0x3 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_16           [expr 0x4 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_32           [expr 0x5 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_64           [expr 0x6 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_128          [expr 0x7 << 24 ]
set 	AT91C_PWMC_PREB_MCK_DIV_256          [expr 0x8 << 24 ]
set AT91C_PWMC_CLKSEL     [expr 0x1 << 31 ]
# -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
set AT91C_PWMC_CHID8      [expr 0x1 <<  8 ]
set AT91C_PWMC_CHID9      [expr 0x1 <<  9 ]
set AT91C_PWMC_CHID10     [expr 0x1 << 10 ]
set AT91C_PWMC_CHID11     [expr 0x1 << 11 ]
set AT91C_PWMC_CHID12     [expr 0x1 << 12 ]
set AT91C_PWMC_CHID13     [expr 0x1 << 13 ]
set AT91C_PWMC_CHID14     [expr 0x1 << 14 ]
set AT91C_PWMC_CHID15     [expr 0x1 << 15 ]
# -------- PWMC_DIS : (PWMC Offset: 0x8) PWMC Disable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
set AT91C_PWMC_CHID8      [expr 0x1 <<  8 ]
set AT91C_PWMC_CHID9      [expr 0x1 <<  9 ]
set AT91C_PWMC_CHID10     [expr 0x1 << 10 ]
set AT91C_PWMC_CHID11     [expr 0x1 << 11 ]
set AT91C_PWMC_CHID12     [expr 0x1 << 12 ]
set AT91C_PWMC_CHID13     [expr 0x1 << 13 ]
set AT91C_PWMC_CHID14     [expr 0x1 << 14 ]
set AT91C_PWMC_CHID15     [expr 0x1 << 15 ]
# -------- PWMC_SR : (PWMC Offset: 0xc) PWMC Status Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
set AT91C_PWMC_CHID8      [expr 0x1 <<  8 ]
set AT91C_PWMC_CHID9      [expr 0x1 <<  9 ]
set AT91C_PWMC_CHID10     [expr 0x1 << 10 ]
set AT91C_PWMC_CHID11     [expr 0x1 << 11 ]
set AT91C_PWMC_CHID12     [expr 0x1 << 12 ]
set AT91C_PWMC_CHID13     [expr 0x1 << 13 ]
set AT91C_PWMC_CHID14     [expr 0x1 << 14 ]
set AT91C_PWMC_CHID15     [expr 0x1 << 15 ]
# -------- PWMC_IER1 : (PWMC Offset: 0x10) PWMC Interrupt Enable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
set AT91C_PWMC_CHID8      [expr 0x1 <<  8 ]
set AT91C_PWMC_CHID9      [expr 0x1 <<  9 ]
set AT91C_PWMC_CHID10     [expr 0x1 << 10 ]
set AT91C_PWMC_CHID11     [expr 0x1 << 11 ]
set AT91C_PWMC_CHID12     [expr 0x1 << 12 ]
set AT91C_PWMC_CHID13     [expr 0x1 << 13 ]
set AT91C_PWMC_CHID14     [expr 0x1 << 14 ]
set AT91C_PWMC_CHID15     [expr 0x1 << 15 ]
set AT91C_PWMC_FCHID0     [expr 0x1 << 16 ]
set AT91C_PWMC_FCHID1     [expr 0x1 << 17 ]
set AT91C_PWMC_FCHID2     [expr 0x1 << 18 ]
set AT91C_PWMC_FCHID3     [expr 0x1 << 19 ]
set AT91C_PWMC_FCHID4     [expr 0x1 << 20 ]
set AT91C_PWMC_FCHID5     [expr 0x1 << 21 ]
set AT91C_PWMC_FCHID6     [expr 0x1 << 22 ]
set AT91C_PWMC_FCHID7     [expr 0x1 << 23 ]
set AT91C_PWMC_FCHID8     [expr 0x1 << 24 ]
set AT91C_PWMC_FCHID9     [expr 0x1 << 25 ]
set AT91C_PWMC_FCHID10    [expr 0x1 << 26 ]
set AT91C_PWMC_FCHID11    [expr 0x1 << 27 ]
set AT91C_PWMC_FCHID12    [expr 0x1 << 28 ]
set AT91C_PWMC_FCHID13    [expr 0x1 << 29 ]
set AT91C_PWMC_FCHID14    [expr 0x1 << 30 ]
set AT91C_PWMC_FCHID15    [expr 0x1 << 31 ]
# -------- PWMC_IDR1 : (PWMC Offset: 0x14) PWMC Interrupt Disable Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
set AT91C_PWMC_CHID8      [expr 0x1 <<  8 ]
set AT91C_PWMC_CHID9      [expr 0x1 <<  9 ]
set AT91C_PWMC_CHID10     [expr 0x1 << 10 ]
set AT91C_PWMC_CHID11     [expr 0x1 << 11 ]
set AT91C_PWMC_CHID12     [expr 0x1 << 12 ]
set AT91C_PWMC_CHID13     [expr 0x1 << 13 ]
set AT91C_PWMC_CHID14     [expr 0x1 << 14 ]
set AT91C_PWMC_CHID15     [expr 0x1 << 15 ]
set AT91C_PWMC_FCHID0     [expr 0x1 << 16 ]
set AT91C_PWMC_FCHID1     [expr 0x1 << 17 ]
set AT91C_PWMC_FCHID2     [expr 0x1 << 18 ]
set AT91C_PWMC_FCHID3     [expr 0x1 << 19 ]
set AT91C_PWMC_FCHID4     [expr 0x1 << 20 ]
set AT91C_PWMC_FCHID5     [expr 0x1 << 21 ]
set AT91C_PWMC_FCHID6     [expr 0x1 << 22 ]
set AT91C_PWMC_FCHID7     [expr 0x1 << 23 ]
set AT91C_PWMC_FCHID8     [expr 0x1 << 24 ]
set AT91C_PWMC_FCHID9     [expr 0x1 << 25 ]
set AT91C_PWMC_FCHID10    [expr 0x1 << 26 ]
set AT91C_PWMC_FCHID11    [expr 0x1 << 27 ]
set AT91C_PWMC_FCHID12    [expr 0x1 << 28 ]
set AT91C_PWMC_FCHID13    [expr 0x1 << 29 ]
set AT91C_PWMC_FCHID14    [expr 0x1 << 30 ]
set AT91C_PWMC_FCHID15    [expr 0x1 << 31 ]
# -------- PWMC_IMR1 : (PWMC Offset: 0x18) PWMC Interrupt Mask Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
set AT91C_PWMC_CHID8      [expr 0x1 <<  8 ]
set AT91C_PWMC_CHID9      [expr 0x1 <<  9 ]
set AT91C_PWMC_CHID10     [expr 0x1 << 10 ]
set AT91C_PWMC_CHID11     [expr 0x1 << 11 ]
set AT91C_PWMC_CHID12     [expr 0x1 << 12 ]
set AT91C_PWMC_CHID13     [expr 0x1 << 13 ]
set AT91C_PWMC_CHID14     [expr 0x1 << 14 ]
set AT91C_PWMC_CHID15     [expr 0x1 << 15 ]
set AT91C_PWMC_FCHID0     [expr 0x1 << 16 ]
set AT91C_PWMC_FCHID1     [expr 0x1 << 17 ]
set AT91C_PWMC_FCHID2     [expr 0x1 << 18 ]
set AT91C_PWMC_FCHID3     [expr 0x1 << 19 ]
set AT91C_PWMC_FCHID4     [expr 0x1 << 20 ]
set AT91C_PWMC_FCHID5     [expr 0x1 << 21 ]
set AT91C_PWMC_FCHID6     [expr 0x1 << 22 ]
set AT91C_PWMC_FCHID7     [expr 0x1 << 23 ]
set AT91C_PWMC_FCHID8     [expr 0x1 << 24 ]
set AT91C_PWMC_FCHID9     [expr 0x1 << 25 ]
set AT91C_PWMC_FCHID10    [expr 0x1 << 26 ]
set AT91C_PWMC_FCHID11    [expr 0x1 << 27 ]
set AT91C_PWMC_FCHID12    [expr 0x1 << 28 ]
set AT91C_PWMC_FCHID13    [expr 0x1 << 29 ]
set AT91C_PWMC_FCHID14    [expr 0x1 << 30 ]
set AT91C_PWMC_FCHID15    [expr 0x1 << 31 ]
# -------- PWMC_ISR1 : (PWMC Offset: 0x1c) PWMC Interrupt Status Register -------- 
set AT91C_PWMC_CHID0      [expr 0x1 <<  0 ]
set AT91C_PWMC_CHID1      [expr 0x1 <<  1 ]
set AT91C_PWMC_CHID2      [expr 0x1 <<  2 ]
set AT91C_PWMC_CHID3      [expr 0x1 <<  3 ]
set AT91C_PWMC_CHID4      [expr 0x1 <<  4 ]
set AT91C_PWMC_CHID5      [expr 0x1 <<  5 ]
set AT91C_PWMC_CHID6      [expr 0x1 <<  6 ]
set AT91C_PWMC_CHID7      [expr 0x1 <<  7 ]
set AT91C_PWMC_CHID8      [expr 0x1 <<  8 ]
set AT91C_PWMC_CHID9      [expr 0x1 <<  9 ]
set AT91C_PWMC_CHID10     [expr 0x1 << 10 ]
set AT91C_PWMC_CHID11     [expr 0x1 << 11 ]
set AT91C_PWMC_CHID12     [expr 0x1 << 12 ]
set AT91C_PWMC_CHID13     [expr 0x1 << 13 ]
set AT91C_PWMC_CHID14     [expr 0x1 << 14 ]
set AT91C_PWMC_CHID15     [expr 0x1 << 15 ]
set AT91C_PWMC_FCHID0     [expr 0x1 << 16 ]
set AT91C_PWMC_FCHID1     [expr 0x1 << 17 ]
set AT91C_PWMC_FCHID2     [expr 0x1 << 18 ]
set AT91C_PWMC_FCHID3     [expr 0x1 << 19 ]
set AT91C_PWMC_FCHID4     [expr 0x1 << 20 ]
set AT91C_PWMC_FCHID5     [expr 0x1 << 21 ]
set AT91C_PWMC_FCHID6     [expr 0x1 << 22 ]
set AT91C_PWMC_FCHID7     [expr 0x1 << 23 ]
set AT91C_PWMC_FCHID8     [expr 0x1 << 24 ]
set AT91C_PWMC_FCHID9     [expr 0x1 << 25 ]
set AT91C_PWMC_FCHID10    [expr 0x1 << 26 ]
set AT91C_PWMC_FCHID11    [expr 0x1 << 27 ]
set AT91C_PWMC_FCHID12    [expr 0x1 << 28 ]
set AT91C_PWMC_FCHID13    [expr 0x1 << 29 ]
set AT91C_PWMC_FCHID14    [expr 0x1 << 30 ]
set AT91C_PWMC_FCHID15    [expr 0x1 << 31 ]
# -------- PWMC_SYNC : (PWMC Offset: 0x20) PWMC Synchronous Channels Register -------- 
set AT91C_PWMC_SYNC0      [expr 0x1 <<  0 ]
set AT91C_PWMC_SYNC1      [expr 0x1 <<  1 ]
set AT91C_PWMC_SYNC2      [expr 0x1 <<  2 ]
set AT91C_PWMC_SYNC3      [expr 0x1 <<  3 ]
set AT91C_PWMC_SYNC4      [expr 0x1 <<  4 ]
set AT91C_PWMC_SYNC5      [expr 0x1 <<  5 ]
set AT91C_PWMC_SYNC6      [expr 0x1 <<  6 ]
set AT91C_PWMC_SYNC7      [expr 0x1 <<  7 ]
set AT91C_PWMC_SYNC8      [expr 0x1 <<  8 ]
set AT91C_PWMC_SYNC9      [expr 0x1 <<  9 ]
set AT91C_PWMC_SYNC10     [expr 0x1 << 10 ]
set AT91C_PWMC_SYNC11     [expr 0x1 << 11 ]
set AT91C_PWMC_SYNC12     [expr 0x1 << 12 ]
set AT91C_PWMC_SYNC13     [expr 0x1 << 13 ]
set AT91C_PWMC_SYNC14     [expr 0x1 << 14 ]
set AT91C_PWMC_SYNC15     [expr 0x1 << 15 ]
set AT91C_PWMC_UPDM       [expr 0x3 << 16 ]
set 	AT91C_PWMC_UPDM_MODE0                [expr 0x0 << 16 ]
set 	AT91C_PWMC_UPDM_MODE1                [expr 0x1 << 16 ]
set 	AT91C_PWMC_UPDM_MODE2                [expr 0x2 << 16 ]
# -------- PWMC_UPCR : (PWMC Offset: 0x28) PWMC Update Control Register -------- 
set AT91C_PWMC_UPDULOCK   [expr 0x1 <<  0 ]
# -------- PWMC_SCUP : (PWMC Offset: 0x2c) PWM Update Period Register -------- 
set AT91C_PWMC_UPR        [expr 0xF <<  0 ]
set AT91C_PWMC_UPRCNT     [expr 0xF <<  4 ]
# -------- PWMC_SCUPUPD : (PWMC Offset: 0x30) PWM Update Period Update Register -------- 
set AT91C_PWMC_UPVUPDAL   [expr 0xF <<  0 ]
# -------- PWMC_IER2 : (PWMC Offset: 0x34) PWMC Interrupt Enable Register -------- 
set AT91C_PWMC_WRDY       [expr 0x1 <<  0 ]
set AT91C_PWMC_ENDTX      [expr 0x1 <<  1 ]
set AT91C_PWMC_TXBUFE     [expr 0x1 <<  2 ]
set AT91C_PWMC_UNRE       [expr 0x1 <<  3 ]
# -------- PWMC_IDR2 : (PWMC Offset: 0x38) PWMC Interrupt Disable Register -------- 
set AT91C_PWMC_WRDY       [expr 0x1 <<  0 ]
set AT91C_PWMC_ENDTX      [expr 0x1 <<  1 ]
set AT91C_PWMC_TXBUFE     [expr 0x1 <<  2 ]
set AT91C_PWMC_UNRE       [expr 0x1 <<  3 ]
# -------- PWMC_IMR2 : (PWMC Offset: 0x3c) PWMC Interrupt Mask Register -------- 
set AT91C_PWMC_WRDY       [expr 0x1 <<  0 ]
set AT91C_PWMC_ENDTX      [expr 0x1 <<  1 ]
set AT91C_PWMC_TXBUFE     [expr 0x1 <<  2 ]
set AT91C_PWMC_UNRE       [expr 0x1 <<  3 ]
# -------- PWMC_ISR2 : (PWMC Offset: 0x40) PWMC Interrupt Status Register -------- 
set AT91C_PWMC_WRDY       [expr 0x1 <<  0 ]
set AT91C_PWMC_ENDTX      [expr 0x1 <<  1 ]
set AT91C_PWMC_TXBUFE     [expr 0x1 <<  2 ]
set AT91C_PWMC_UNRE       [expr 0x1 <<  3 ]
set AT91C_PWMC_CMPM0      [expr 0x1 <<  8 ]
set AT91C_PWMC_CMPM1      [expr 0x1 <<  9 ]
set AT91C_PWMC_CMPM2      [expr 0x1 << 10 ]
set AT91C_PWMC_CMPM3      [expr 0x1 << 11 ]
set AT91C_PWMC_CMPM4      [expr 0x1 << 12 ]
set AT91C_PWMC_CMPM5      [expr 0x1 << 13 ]
set AT91C_PWMC_CMPM6      [expr 0x1 << 14 ]
set AT91C_PWMC_CMPM7      [expr 0x1 << 15 ]
set AT91C_PWMC_CMPU0      [expr 0x1 << 16 ]
set AT91C_PWMC_CMPU1      [expr 0x1 << 17 ]
set AT91C_PWMC_CMPU2      [expr 0x1 << 18 ]
set AT91C_PWMC_CMPU3      [expr 0x1 << 19 ]
set AT91C_PWMC_CMPU4      [expr 0x1 << 20 ]
set AT91C_PWMC_CMPU5      [expr 0x1 << 21 ]
set AT91C_PWMC_CMPU6      [expr 0x1 << 22 ]
set AT91C_PWMC_CMPU7      [expr 0x1 << 23 ]
# -------- PWMC_OOV : (PWMC Offset: 0x44) PWM Output Override Value Register -------- 
set AT91C_PWMC_OOVH0      [expr 0x1 <<  0 ]
set AT91C_PWMC_OOVH1      [expr 0x1 <<  1 ]
set AT91C_PWMC_OOVH2      [expr 0x1 <<  2 ]
set AT91C_PWMC_OOVH3      [expr 0x1 <<  3 ]
set AT91C_PWMC_OOVH4      [expr 0x1 <<  4 ]
set AT91C_PWMC_OOVH5      [expr 0x1 <<  5 ]
set AT91C_PWMC_OOVH6      [expr 0x1 <<  6 ]
set AT91C_PWMC_OOVH7      [expr 0x1 <<  7 ]
set AT91C_PWMC_OOVH8      [expr 0x1 <<  8 ]
set AT91C_PWMC_OOVH9      [expr 0x1 <<  9 ]
set AT91C_PWMC_OOVH10     [expr 0x1 << 10 ]
set AT91C_PWMC_OOVH11     [expr 0x1 << 11 ]
set AT91C_PWMC_OOVH12     [expr 0x1 << 12 ]
set AT91C_PWMC_OOVH13     [expr 0x1 << 13 ]
set AT91C_PWMC_OOVH14     [expr 0x1 << 14 ]
set AT91C_PWMC_OOVH15     [expr 0x1 << 15 ]
set AT91C_PWMC_OOVL0      [expr 0x1 << 16 ]
set AT91C_PWMC_OOVL1      [expr 0x1 << 17 ]
set AT91C_PWMC_OOVL2      [expr 0x1 << 18 ]
set AT91C_PWMC_OOVL3      [expr 0x1 << 19 ]
set AT91C_PWMC_OOVL4      [expr 0x1 << 20 ]
set AT91C_PWMC_OOVL5      [expr 0x1 << 21 ]
set AT91C_PWMC_OOVL6      [expr 0x1 << 22 ]
set AT91C_PWMC_OOVL7      [expr 0x1 << 23 ]
set AT91C_PWMC_OOVL8      [expr 0x1 << 24 ]
set AT91C_PWMC_OOVL9      [expr 0x1 << 25 ]
set AT91C_PWMC_OOVL10     [expr 0x1 << 26 ]
set AT91C_PWMC_OOVL11     [expr 0x1 << 27 ]
set AT91C_PWMC_OOVL12     [expr 0x1 << 28 ]
set AT91C_PWMC_OOVL13     [expr 0x1 << 29 ]
set AT91C_PWMC_OOVL14     [expr 0x1 << 30 ]
set AT91C_PWMC_OOVL15     [expr 0x1 << 31 ]
# -------- PWMC_OS : (PWMC Offset: 0x48) PWM Output Selection Register -------- 
set AT91C_PWMC_OSH0       [expr 0x1 <<  0 ]
set AT91C_PWMC_OSH1       [expr 0x1 <<  1 ]
set AT91C_PWMC_OSH2       [expr 0x1 <<  2 ]
set AT91C_PWMC_OSH3       [expr 0x1 <<  3 ]
set AT91C_PWMC_OSH4       [expr 0x1 <<  4 ]
set AT91C_PWMC_OSH5       [expr 0x1 <<  5 ]
set AT91C_PWMC_OSH6       [expr 0x1 <<  6 ]
set AT91C_PWMC_OSH7       [expr 0x1 <<  7 ]
set AT91C_PWMC_OSH8       [expr 0x1 <<  8 ]
set AT91C_PWMC_OSH9       [expr 0x1 <<  9 ]
set AT91C_PWMC_OSH10      [expr 0x1 << 10 ]
set AT91C_PWMC_OSH11      [expr 0x1 << 11 ]
set AT91C_PWMC_OSH12      [expr 0x1 << 12 ]
set AT91C_PWMC_OSH13      [expr 0x1 << 13 ]
set AT91C_PWMC_OSH14      [expr 0x1 << 14 ]
set AT91C_PWMC_OSH15      [expr 0x1 << 15 ]
set AT91C_PWMC_OSL0       [expr 0x1 << 16 ]
set AT91C_PWMC_OSL1       [expr 0x1 << 17 ]
set AT91C_PWMC_OSL2       [expr 0x1 << 18 ]
set AT91C_PWMC_OSL3       [expr 0x1 << 19 ]
set AT91C_PWMC_OSL4       [expr 0x1 << 20 ]
set AT91C_PWMC_OSL5       [expr 0x1 << 21 ]
set AT91C_PWMC_OSL6       [expr 0x1 << 22 ]
set AT91C_PWMC_OSL7       [expr 0x1 << 23 ]
set AT91C_PWMC_OSL8       [expr 0x1 << 24 ]
set AT91C_PWMC_OSL9       [expr 0x1 << 25 ]
set AT91C_PWMC_OSL10      [expr 0x1 << 26 ]
set AT91C_PWMC_OSL11      [expr 0x1 << 27 ]
set AT91C_PWMC_OSL12      [expr 0x1 << 28 ]
set AT91C_PWMC_OSL13      [expr 0x1 << 29 ]
set AT91C_PWMC_OSL14      [expr 0x1 << 30 ]
set AT91C_PWMC_OSL15      [expr 0x1 << 31 ]
# -------- PWMC_OSS : (PWMC Offset: 0x4c) PWM Output Selection Set Register -------- 
set AT91C_PWMC_OSSH0      [expr 0x1 <<  0 ]
set AT91C_PWMC_OSSH1      [expr 0x1 <<  1 ]
set AT91C_PWMC_OSSH2      [expr 0x1 <<  2 ]
set AT91C_PWMC_OSSH3      [expr 0x1 <<  3 ]
set AT91C_PWMC_OSSH4      [expr 0x1 <<  4 ]
set AT91C_PWMC_OSSH5      [expr 0x1 <<  5 ]
set AT91C_PWMC_OSSH6      [expr 0x1 <<  6 ]
set AT91C_PWMC_OSSH7      [expr 0x1 <<  7 ]
set AT91C_PWMC_OSSH8      [expr 0x1 <<  8 ]
set AT91C_PWMC_OSSH9      [expr 0x1 <<  9 ]
set AT91C_PWMC_OSSH10     [expr 0x1 << 10 ]
set AT91C_PWMC_OSSH11     [expr 0x1 << 11 ]
set AT91C_PWMC_OSSH12     [expr 0x1 << 12 ]
set AT91C_PWMC_OSSH13     [expr 0x1 << 13 ]
set AT91C_PWMC_OSSH14     [expr 0x1 << 14 ]
set AT91C_PWMC_OSSH15     [expr 0x1 << 15 ]
set AT91C_PWMC_OSSL0      [expr 0x1 << 16 ]
set AT91C_PWMC_OSSL1      [expr 0x1 << 17 ]
set AT91C_PWMC_OSSL2      [expr 0x1 << 18 ]
set AT91C_PWMC_OSSL3      [expr 0x1 << 19 ]
set AT91C_PWMC_OSSL4      [expr 0x1 << 20 ]
set AT91C_PWMC_OSSL5      [expr 0x1 << 21 ]
set AT91C_PWMC_OSSL6      [expr 0x1 << 22 ]
set AT91C_PWMC_OSSL7      [expr 0x1 << 23 ]
set AT91C_PWMC_OSSL8      [expr 0x1 << 24 ]
set AT91C_PWMC_OSSL9      [expr 0x1 << 25 ]
set AT91C_PWMC_OSSL10     [expr 0x1 << 26 ]
set AT91C_PWMC_OSSL11     [expr 0x1 << 27 ]
set AT91C_PWMC_OSSL12     [expr 0x1 << 28 ]
set AT91C_PWMC_OSSL13     [expr 0x1 << 29 ]
set AT91C_PWMC_OSSL14     [expr 0x1 << 30 ]
set AT91C_PWMC_OSSL15     [expr 0x1 << 31 ]
# -------- PWMC_OSC : (PWMC Offset: 0x50) PWM Output Selection Clear Register -------- 
set AT91C_PWMC_OSCH0      [expr 0x1 <<  0 ]
set AT91C_PWMC_OSCH1      [expr 0x1 <<  1 ]
set AT91C_PWMC_OSCH2      [expr 0x1 <<  2 ]
set AT91C_PWMC_OSCH3      [expr 0x1 <<  3 ]
set AT91C_PWMC_OSCH4      [expr 0x1 <<  4 ]
set AT91C_PWMC_OSCH5      [expr 0x1 <<  5 ]
set AT91C_PWMC_OSCH6      [expr 0x1 <<  6 ]
set AT91C_PWMC_OSCH7      [expr 0x1 <<  7 ]
set AT91C_PWMC_OSCH8      [expr 0x1 <<  8 ]
set AT91C_PWMC_OSCH9      [expr 0x1 <<  9 ]
set AT91C_PWMC_OSCH10     [expr 0x1 << 10 ]
set AT91C_PWMC_OSCH11     [expr 0x1 << 11 ]
set AT91C_PWMC_OSCH12     [expr 0x1 << 12 ]
set AT91C_PWMC_OSCH13     [expr 0x1 << 13 ]
set AT91C_PWMC_OSCH14     [expr 0x1 << 14 ]
set AT91C_PWMC_OSCH15     [expr 0x1 << 15 ]
set AT91C_PWMC_OSCL0      [expr 0x1 << 16 ]
set AT91C_PWMC_OSCL1      [expr 0x1 << 17 ]
set AT91C_PWMC_OSCL2      [expr 0x1 << 18 ]
set AT91C_PWMC_OSCL3      [expr 0x1 << 19 ]
set AT91C_PWMC_OSCL4      [expr 0x1 << 20 ]
set AT91C_PWMC_OSCL5      [expr 0x1 << 21 ]
set AT91C_PWMC_OSCL6      [expr 0x1 << 22 ]
set AT91C_PWMC_OSCL7      [expr 0x1 << 23 ]
set AT91C_PWMC_OSCL8      [expr 0x1 << 24 ]
set AT91C_PWMC_OSCL9      [expr 0x1 << 25 ]
set AT91C_PWMC_OSCL10     [expr 0x1 << 26 ]
set AT91C_PWMC_OSCL11     [expr 0x1 << 27 ]
set AT91C_PWMC_OSCL12     [expr 0x1 << 28 ]
set AT91C_PWMC_OSCL13     [expr 0x1 << 29 ]
set AT91C_PWMC_OSCL14     [expr 0x1 << 30 ]
set AT91C_PWMC_OSCL15     [expr 0x1 << 31 ]
# -------- PWMC_OSSUPD : (PWMC Offset: 0x54) Output Selection Set for PWMH / PWML output of the channel x -------- 
set AT91C_PWMC_OSSUPDH0   [expr 0x1 <<  0 ]
set AT91C_PWMC_OSSUPDH1   [expr 0x1 <<  1 ]
set AT91C_PWMC_OSSUPDH2   [expr 0x1 <<  2 ]
set AT91C_PWMC_OSSUPDH3   [expr 0x1 <<  3 ]
set AT91C_PWMC_OSSUPDH4   [expr 0x1 <<  4 ]
set AT91C_PWMC_OSSUPDH5   [expr 0x1 <<  5 ]
set AT91C_PWMC_OSSUPDH6   [expr 0x1 <<  6 ]
set AT91C_PWMC_OSSUPDH7   [expr 0x1 <<  7 ]
set AT91C_PWMC_OSSUPDH8   [expr 0x1 <<  8 ]
set AT91C_PWMC_OSSUPDH9   [expr 0x1 <<  9 ]
set AT91C_PWMC_OSSUPDH10  [expr 0x1 << 10 ]
set AT91C_PWMC_OSSUPDH11  [expr 0x1 << 11 ]
set AT91C_PWMC_OSSUPDH12  [expr 0x1 << 12 ]
set AT91C_PWMC_OSSUPDH13  [expr 0x1 << 13 ]
set AT91C_PWMC_OSSUPDH14  [expr 0x1 << 14 ]
set AT91C_PWMC_OSSUPDH15  [expr 0x1 << 15 ]
set AT91C_PWMC_OSSUPDL0   [expr 0x1 << 16 ]
set AT91C_PWMC_OSSUPDL1   [expr 0x1 << 17 ]
set AT91C_PWMC_OSSUPDL2   [expr 0x1 << 18 ]
set AT91C_PWMC_OSSUPDL3   [expr 0x1 << 19 ]
set AT91C_PWMC_OSSUPDL4   [expr 0x1 << 20 ]
set AT91C_PWMC_OSSUPDL5   [expr 0x1 << 21 ]
set AT91C_PWMC_OSSUPDL6   [expr 0x1 << 22 ]
set AT91C_PWMC_OSSUPDL7   [expr 0x1 << 23 ]
set AT91C_PWMC_OSSUPDL8   [expr 0x1 << 24 ]
set AT91C_PWMC_OSSUPDL9   [expr 0x1 << 25 ]
set AT91C_PWMC_OSSUPDL10  [expr 0x1 << 26 ]
set AT91C_PWMC_OSSUPDL11  [expr 0x1 << 27 ]
set AT91C_PWMC_OSSUPDL12  [expr 0x1 << 28 ]
set AT91C_PWMC_OSSUPDL13  [expr 0x1 << 29 ]
set AT91C_PWMC_OSSUPDL14  [expr 0x1 << 30 ]
set AT91C_PWMC_OSSUPDL15  [expr 0x1 << 31 ]
# -------- PWMC_OSCUPD : (PWMC Offset: 0x58) Output Selection Clear for PWMH / PWML output of the channel x -------- 
set AT91C_PWMC_OSCUPDH0   [expr 0x1 <<  0 ]
set AT91C_PWMC_OSCUPDH1   [expr 0x1 <<  1 ]
set AT91C_PWMC_OSCUPDH2   [expr 0x1 <<  2 ]
set AT91C_PWMC_OSCUPDH3   [expr 0x1 <<  3 ]
set AT91C_PWMC_OSCUPDH4   [expr 0x1 <<  4 ]
set AT91C_PWMC_OSCUPDH5   [expr 0x1 <<  5 ]
set AT91C_PWMC_OSCUPDH6   [expr 0x1 <<  6 ]
set AT91C_PWMC_OSCUPDH7   [expr 0x1 <<  7 ]
set AT91C_PWMC_OSCUPDH8   [expr 0x1 <<  8 ]
set AT91C_PWMC_OSCUPDH9   [expr 0x1 <<  9 ]
set AT91C_PWMC_OSCUPDH10  [expr 0x1 << 10 ]
set AT91C_PWMC_OSCUPDH11  [expr 0x1 << 11 ]
set AT91C_PWMC_OSCUPDH12  [expr 0x1 << 12 ]
set AT91C_PWMC_OSCUPDH13  [expr 0x1 << 13 ]
set AT91C_PWMC_OSCUPDH14  [expr 0x1 << 14 ]
set AT91C_PWMC_OSCUPDH15  [expr 0x1 << 15 ]
set AT91C_PWMC_OSCUPDL0   [expr 0x1 << 16 ]
set AT91C_PWMC_OSCUPDL1   [expr 0x1 << 17 ]
set AT91C_PWMC_OSCUPDL2   [expr 0x1 << 18 ]
set AT91C_PWMC_OSCUPDL3   [expr 0x1 << 19 ]
set AT91C_PWMC_OSCUPDL4   [expr 0x1 << 20 ]
set AT91C_PWMC_OSCUPDL5   [expr 0x1 << 21 ]
set AT91C_PWMC_OSCUPDL6   [expr 0x1 << 22 ]
set AT91C_PWMC_OSCUPDL7   [expr 0x1 << 23 ]
set AT91C_PWMC_OSCUPDL8   [expr 0x1 << 24 ]
set AT91C_PWMC_OSCUPDL9   [expr 0x1 << 25 ]
set AT91C_PWMC_OSCUPDL10  [expr 0x1 << 26 ]
set AT91C_PWMC_OSCUPDL11  [expr 0x1 << 27 ]
set AT91C_PWMC_OSCUPDL12  [expr 0x1 << 28 ]
set AT91C_PWMC_OSCUPDL13  [expr 0x1 << 29 ]
set AT91C_PWMC_OSCUPDL14  [expr 0x1 << 30 ]
set AT91C_PWMC_OSCUPDL15  [expr 0x1 << 31 ]
# -------- PWMC_FMR : (PWMC Offset: 0x5c) PWM Fault Mode Register -------- 
set AT91C_PWMC_FPOL0      [expr 0x1 <<  0 ]
set AT91C_PWMC_FPOL1      [expr 0x1 <<  1 ]
set AT91C_PWMC_FPOL2      [expr 0x1 <<  2 ]
set AT91C_PWMC_FPOL3      [expr 0x1 <<  3 ]
set AT91C_PWMC_FPOL4      [expr 0x1 <<  4 ]
set AT91C_PWMC_FPOL5      [expr 0x1 <<  5 ]
set AT91C_PWMC_FPOL6      [expr 0x1 <<  6 ]
set AT91C_PWMC_FPOL7      [expr 0x1 <<  7 ]
set AT91C_PWMC_FMOD0      [expr 0x1 <<  8 ]
set AT91C_PWMC_FMOD1      [expr 0x1 <<  9 ]
set AT91C_PWMC_FMOD2      [expr 0x1 << 10 ]
set AT91C_PWMC_FMOD3      [expr 0x1 << 11 ]
set AT91C_PWMC_FMOD4      [expr 0x1 << 12 ]
set AT91C_PWMC_FMOD5      [expr 0x1 << 13 ]
set AT91C_PWMC_FMOD6      [expr 0x1 << 14 ]
set AT91C_PWMC_FMOD7      [expr 0x1 << 15 ]
set AT91C_PWMC_FFIL00     [expr 0x1 << 16 ]
set AT91C_PWMC_FFIL01     [expr 0x1 << 17 ]
set AT91C_PWMC_FFIL02     [expr 0x1 << 18 ]
set AT91C_PWMC_FFIL03     [expr 0x1 << 19 ]
set AT91C_PWMC_FFIL04     [expr 0x1 << 20 ]
set AT91C_PWMC_FFIL05     [expr 0x1 << 21 ]
set AT91C_PWMC_FFIL06     [expr 0x1 << 22 ]
set AT91C_PWMC_FFIL07     [expr 0x1 << 23 ]
# -------- PWMC_FSR : (PWMC Offset: 0x60) Fault Input x Value -------- 
set AT91C_PWMC_FIV0       [expr 0x1 <<  0 ]
set AT91C_PWMC_FIV1       [expr 0x1 <<  1 ]
set AT91C_PWMC_FIV2       [expr 0x1 <<  2 ]
set AT91C_PWMC_FIV3       [expr 0x1 <<  3 ]
set AT91C_PWMC_FIV4       [expr 0x1 <<  4 ]
set AT91C_PWMC_FIV5       [expr 0x1 <<  5 ]
set AT91C_PWMC_FIV6       [expr 0x1 <<  6 ]
set AT91C_PWMC_FIV7       [expr 0x1 <<  7 ]
set AT91C_PWMC_FS0        [expr 0x1 <<  8 ]
set AT91C_PWMC_FS1        [expr 0x1 <<  9 ]
set AT91C_PWMC_FS2        [expr 0x1 << 10 ]
set AT91C_PWMC_FS3        [expr 0x1 << 11 ]
set AT91C_PWMC_FS4        [expr 0x1 << 12 ]
set AT91C_PWMC_FS5        [expr 0x1 << 13 ]
set AT91C_PWMC_FS6        [expr 0x1 << 14 ]
set AT91C_PWMC_FS7        [expr 0x1 << 15 ]
# -------- PWMC_FCR : (PWMC Offset: 0x64) Fault y Clear -------- 
set AT91C_PWMC_FCLR0      [expr 0x1 <<  0 ]
set AT91C_PWMC_FCLR1      [expr 0x1 <<  1 ]
set AT91C_PWMC_FCLR2      [expr 0x1 <<  2 ]
set AT91C_PWMC_FCLR3      [expr 0x1 <<  3 ]
set AT91C_PWMC_FCLR4      [expr 0x1 <<  4 ]
set AT91C_PWMC_FCLR5      [expr 0x1 <<  5 ]
set AT91C_PWMC_FCLR6      [expr 0x1 <<  6 ]
set AT91C_PWMC_FCLR7      [expr 0x1 <<  7 ]
# -------- PWMC_FPV : (PWMC Offset: 0x68) PWM Fault Protection Value -------- 
set AT91C_PWMC_FPVH0      [expr 0x1 <<  0 ]
set AT91C_PWMC_FPVH1      [expr 0x1 <<  1 ]
set AT91C_PWMC_FPVH2      [expr 0x1 <<  2 ]
set AT91C_PWMC_FPVH3      [expr 0x1 <<  3 ]
set AT91C_PWMC_FPVH4      [expr 0x1 <<  4 ]
set AT91C_PWMC_FPVH5      [expr 0x1 <<  5 ]
set AT91C_PWMC_FPVH6      [expr 0x1 <<  6 ]
set AT91C_PWMC_FPVH7      [expr 0x1 <<  7 ]
set AT91C_PWMC_FPVL0      [expr 0x1 << 16 ]
set AT91C_PWMC_FPVL1      [expr 0x1 << 17 ]
set AT91C_PWMC_FPVL2      [expr 0x1 << 18 ]
set AT91C_PWMC_FPVL3      [expr 0x1 << 19 ]
set AT91C_PWMC_FPVL4      [expr 0x1 << 20 ]
set AT91C_PWMC_FPVL5      [expr 0x1 << 21 ]
set AT91C_PWMC_FPVL6      [expr 0x1 << 22 ]
set AT91C_PWMC_FPVL7      [expr 0x1 << 23 ]
# -------- PWMC_FPER1 : (PWMC Offset: 0x6c) PWM Fault Protection Enable Register 1 -------- 
set AT91C_PWMC_FPE0       [expr 0xFF <<  0 ]
set AT91C_PWMC_FPE1       [expr 0xFF <<  8 ]
set AT91C_PWMC_FPE2       [expr 0xFF << 16 ]
set AT91C_PWMC_FPE3       [expr 0xFF << 24 ]
# -------- PWMC_FPER2 : (PWMC Offset: 0x70) PWM Fault Protection Enable Register 2 -------- 
set AT91C_PWMC_FPE4       [expr 0xFF <<  0 ]
set AT91C_PWMC_FPE5       [expr 0xFF <<  8 ]
set AT91C_PWMC_FPE6       [expr 0xFF << 16 ]
set AT91C_PWMC_FPE7       [expr 0xFF << 24 ]
# -------- PWMC_FPER3 : (PWMC Offset: 0x74) PWM Fault Protection Enable Register 3 -------- 
set AT91C_PWMC_FPE8       [expr 0xFF <<  0 ]
set AT91C_PWMC_FPE9       [expr 0xFF <<  8 ]
set AT91C_PWMC_FPE10      [expr 0xFF << 16 ]
set AT91C_PWMC_FPE11      [expr 0xFF << 24 ]
# -------- PWMC_FPER4 : (PWMC Offset: 0x78) PWM Fault Protection Enable Register 4 -------- 
set AT91C_PWMC_FPE12      [expr 0xFF <<  0 ]
set AT91C_PWMC_FPE13      [expr 0xFF <<  8 ]
set AT91C_PWMC_FPE14      [expr 0xFF << 16 ]
set AT91C_PWMC_FPE15      [expr 0xFF << 24 ]
# -------- PWMC_EL0MR : (PWMC Offset: 0x7c) PWM Event Line 0 Mode Register -------- 
set AT91C_PWMC_L0CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L0CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L0CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L0CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L0CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L0CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L0CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L0CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_EL1MR : (PWMC Offset: 0x80) PWM Event Line 1 Mode Register -------- 
set AT91C_PWMC_L1CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L1CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L1CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L1CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L1CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L1CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L1CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L1CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_EL2MR : (PWMC Offset: 0x84) PWM Event line 2 Mode Register -------- 
set AT91C_PWMC_L2CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L2CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L2CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L2CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L2CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L2CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L2CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L2CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_EL3MR : (PWMC Offset: 0x88) PWM Event line 3 Mode Register -------- 
set AT91C_PWMC_L3CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L3CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L3CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L3CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L3CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L3CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L3CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L3CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_EL4MR : (PWMC Offset: 0x8c) PWM Event line 4 Mode Register -------- 
set AT91C_PWMC_L4CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L4CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L4CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L4CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L4CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L4CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L4CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L4CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_EL5MR : (PWMC Offset: 0x90) PWM Event line 5 Mode Register -------- 
set AT91C_PWMC_L5CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L5CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L5CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L5CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L5CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L5CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L5CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L5CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_EL6MR : (PWMC Offset: 0x94) PWM Event line 6 Mode Register -------- 
set AT91C_PWMC_L6CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L6CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L6CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L6CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L6CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L6CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L6CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L6CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_EL7MR : (PWMC Offset: 0x98) PWM Event line 7 Mode Register -------- 
set AT91C_PWMC_L7CSEL0    [expr 0x1 <<  0 ]
set AT91C_PWMC_L7CSEL1    [expr 0x1 <<  1 ]
set AT91C_PWMC_L7CSEL2    [expr 0x1 <<  2 ]
set AT91C_PWMC_L7CSEL3    [expr 0x1 <<  3 ]
set AT91C_PWMC_L7CSEL4    [expr 0x1 <<  4 ]
set AT91C_PWMC_L7CSEL5    [expr 0x1 <<  5 ]
set AT91C_PWMC_L7CSEL6    [expr 0x1 <<  6 ]
set AT91C_PWMC_L7CSEL7    [expr 0x1 <<  7 ]
# -------- PWMC_WPCR : (PWMC Offset: 0xe4) PWM Write Protection Control Register -------- 
set AT91C_PWMC_WPCMD      [expr 0x3 <<  0 ]
set AT91C_PWMC_WPRG0      [expr 0x1 <<  2 ]
set AT91C_PWMC_WPRG1      [expr 0x1 <<  3 ]
set AT91C_PWMC_WPRG2      [expr 0x1 <<  4 ]
set AT91C_PWMC_WPRG3      [expr 0x1 <<  5 ]
set AT91C_PWMC_WPRG4      [expr 0x1 <<  6 ]
set AT91C_PWMC_WPRG5      [expr 0x1 <<  7 ]
set AT91C_PWMC_WPKEY      [expr 0xFFFFFF <<  8 ]
# -------- PWMC_WPVS : (PWMC Offset: 0xe8) Write Protection Status Register -------- 
set AT91C_PWMC_WPSWS0     [expr 0x1 <<  0 ]
set AT91C_PWMC_WPSWS1     [expr 0x1 <<  1 ]
set AT91C_PWMC_WPSWS2     [expr 0x1 <<  2 ]
set AT91C_PWMC_WPSWS3     [expr 0x1 <<  3 ]
set AT91C_PWMC_WPSWS4     [expr 0x1 <<  4 ]
set AT91C_PWMC_WPSWS5     [expr 0x1 <<  5 ]
set AT91C_PWMC_WPVS       [expr 0x1 <<  7 ]
set AT91C_PWMC_WPHWS0     [expr 0x1 <<  8 ]
set AT91C_PWMC_WPHWS1     [expr 0x1 <<  9 ]
set AT91C_PWMC_WPHWS2     [expr 0x1 << 10 ]
set AT91C_PWMC_WPHWS3     [expr 0x1 << 11 ]
set AT91C_PWMC_WPHWS4     [expr 0x1 << 12 ]
set AT91C_PWMC_WPHWS5     [expr 0x1 << 13 ]
set AT91C_PWMC_WPVSRC     [expr 0xFFFF << 16 ]
# -------- PWMC_CMP0V : (PWMC Offset: 0x130) PWM Comparison Value 0 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP0VUPD : (PWMC Offset: 0x134) PWM Comparison Value 0 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP0M : (PWMC Offset: 0x138) PWM Comparison 0 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP0MUPD : (PWMC Offset: 0x13c) PWM Comparison 0 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]
# -------- PWMC_CMP1V : (PWMC Offset: 0x140) PWM Comparison Value 1 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP1VUPD : (PWMC Offset: 0x144) PWM Comparison Value 1 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP1M : (PWMC Offset: 0x148) PWM Comparison 1 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP1MUPD : (PWMC Offset: 0x14c) PWM Comparison 1 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]
# -------- PWMC_CMP2V : (PWMC Offset: 0x150) PWM Comparison Value 2 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP2VUPD : (PWMC Offset: 0x154) PWM Comparison Value 2 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP2M : (PWMC Offset: 0x158) PWM Comparison 2 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP2MUPD : (PWMC Offset: 0x15c) PWM Comparison 2 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]
# -------- PWMC_CMP3V : (PWMC Offset: 0x160) PWM Comparison Value 3 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP3VUPD : (PWMC Offset: 0x164) PWM Comparison Value 3 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP3M : (PWMC Offset: 0x168) PWM Comparison 3 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP3MUPD : (PWMC Offset: 0x16c) PWM Comparison 3 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]
# -------- PWMC_CMP4V : (PWMC Offset: 0x170) PWM Comparison Value 4 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP4VUPD : (PWMC Offset: 0x174) PWM Comparison Value 4 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP4M : (PWMC Offset: 0x178) PWM Comparison 4 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP4MUPD : (PWMC Offset: 0x17c) PWM Comparison 4 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]
# -------- PWMC_CMP5V : (PWMC Offset: 0x180) PWM Comparison Value 5 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP5VUPD : (PWMC Offset: 0x184) PWM Comparison Value 5 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP5M : (PWMC Offset: 0x188) PWM Comparison 5 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP5MUPD : (PWMC Offset: 0x18c) PWM Comparison 5 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]
# -------- PWMC_CMP6V : (PWMC Offset: 0x190) PWM Comparison Value 6 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP6VUPD : (PWMC Offset: 0x194) PWM Comparison Value 6 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP6M : (PWMC Offset: 0x198) PWM Comparison 6 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP6MUPD : (PWMC Offset: 0x19c) PWM Comparison 6 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]
# -------- PWMC_CMP7V : (PWMC Offset: 0x1a0) PWM Comparison Value 7 Register -------- 
set AT91C_PWMC_CV         [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVM        [expr 0x1 << 24 ]
# -------- PWMC_CMP7VUPD : (PWMC Offset: 0x1a4) PWM Comparison Value 7 Update Register -------- 
set AT91C_PWMC_CVUPD      [expr 0xFFFFFF <<  0 ]
set AT91C_PWMC_CVMUPD     [expr 0x1 << 24 ]
# -------- PWMC_CMP7M : (PWMC Offset: 0x1a8) PWM Comparison 7 Mode Register -------- 
set AT91C_PWMC_CEN        [expr 0x1 <<  0 ]
set AT91C_PWMC_CTR        [expr 0xF <<  4 ]
set AT91C_PWMC_CPR        [expr 0xF <<  8 ]
set AT91C_PWMC_CPRCNT     [expr 0xF << 12 ]
set AT91C_PWMC_CUPR       [expr 0xF << 16 ]
set AT91C_PWMC_CUPRCNT    [expr 0xF << 20 ]
# -------- PWMC_CMP7MUPD : (PWMC Offset: 0x1ac) PWM Comparison 7 Mode Update Register -------- 
set AT91C_PWMC_CENUPD     [expr 0x1 <<  0 ]
set AT91C_PWMC_CTRUPD     [expr 0xF <<  4 ]
set AT91C_PWMC_CPRUPD     [expr 0xF <<  8 ]
set AT91C_PWMC_CUPRUPD    [expr 0xF << 16 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR Serial Parallel Interface
# *****************************************************************************
# -------- SPI_CR : (SPI Offset: 0x0) SPI Control Register -------- 
set AT91C_SPI_SPIEN       [expr 0x1 <<  0 ]
set AT91C_SPI_SPIDIS      [expr 0x1 <<  1 ]
set AT91C_SPI_SWRST       [expr 0x1 <<  7 ]
set AT91C_SPI_LASTXFER    [expr 0x1 << 24 ]
# -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- 
set AT91C_SPI_MSTR        [expr 0x1 <<  0 ]
set AT91C_SPI_PS          [expr 0x1 <<  1 ]
set 	AT91C_SPI_PS_FIXED                [expr 0x0 <<  1 ]
set 	AT91C_SPI_PS_VARIABLE             [expr 0x1 <<  1 ]
set AT91C_SPI_PCSDEC      [expr 0x1 <<  2 ]
set AT91C_SPI_FDIV        [expr 0x1 <<  3 ]
set AT91C_SPI_MODFDIS     [expr 0x1 <<  4 ]
set AT91C_SPI_LLB         [expr 0x1 <<  7 ]
set AT91C_SPI_PCS         [expr 0xF << 16 ]
set AT91C_SPI_DLYBCS      [expr 0xFF << 24 ]
# -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- 
set AT91C_SPI_RD          [expr 0xFFFF <<  0 ]
set AT91C_SPI_RPCS        [expr 0xF << 16 ]
# -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- 
set AT91C_SPI_TD          [expr 0xFFFF <<  0 ]
set AT91C_SPI_TPCS        [expr 0xF << 16 ]
set AT91C_SPI_LASTXFER    [expr 0x1 << 24 ]
# -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- 
set AT91C_SPI_RDRF        [expr 0x1 <<  0 ]
set AT91C_SPI_TDRE        [expr 0x1 <<  1 ]
set AT91C_SPI_MODF        [expr 0x1 <<  2 ]
set AT91C_SPI_OVRES       [expr 0x1 <<  3 ]
set AT91C_SPI_ENDRX       [expr 0x1 <<  4 ]
set AT91C_SPI_ENDTX       [expr 0x1 <<  5 ]
set AT91C_SPI_RXBUFF      [expr 0x1 <<  6 ]
set AT91C_SPI_TXBUFE      [expr 0x1 <<  7 ]
set AT91C_SPI_NSSR        [expr 0x1 <<  8 ]
set AT91C_SPI_TXEMPTY     [expr 0x1 <<  9 ]
set AT91C_SPI_SPIENS      [expr 0x1 << 16 ]
# -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- 
set AT91C_SPI_RDRF        [expr 0x1 <<  0 ]
set AT91C_SPI_TDRE        [expr 0x1 <<  1 ]
set AT91C_SPI_MODF        [expr 0x1 <<  2 ]
set AT91C_SPI_OVRES       [expr 0x1 <<  3 ]
set AT91C_SPI_ENDRX       [expr 0x1 <<  4 ]
set AT91C_SPI_ENDTX       [expr 0x1 <<  5 ]
set AT91C_SPI_RXBUFF      [expr 0x1 <<  6 ]
set AT91C_SPI_TXBUFE      [expr 0x1 <<  7 ]
set AT91C_SPI_NSSR        [expr 0x1 <<  8 ]
set AT91C_SPI_TXEMPTY     [expr 0x1 <<  9 ]
# -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- 
set AT91C_SPI_RDRF        [expr 0x1 <<  0 ]
set AT91C_SPI_TDRE        [expr 0x1 <<  1 ]
set AT91C_SPI_MODF        [expr 0x1 <<  2 ]
set AT91C_SPI_OVRES       [expr 0x1 <<  3 ]
set AT91C_SPI_ENDRX       [expr 0x1 <<  4 ]
set AT91C_SPI_ENDTX       [expr 0x1 <<  5 ]
set AT91C_SPI_RXBUFF      [expr 0x1 <<  6 ]
set AT91C_SPI_TXBUFE      [expr 0x1 <<  7 ]
set AT91C_SPI_NSSR        [expr 0x1 <<  8 ]
set AT91C_SPI_TXEMPTY     [expr 0x1 <<  9 ]
# -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- 
set AT91C_SPI_RDRF        [expr 0x1 <<  0 ]
set AT91C_SPI_TDRE        [expr 0x1 <<  1 ]
set AT91C_SPI_MODF        [expr 0x1 <<  2 ]
set AT91C_SPI_OVRES       [expr 0x1 <<  3 ]
set AT91C_SPI_ENDRX       [expr 0x1 <<  4 ]
set AT91C_SPI_ENDTX       [expr 0x1 <<  5 ]
set AT91C_SPI_RXBUFF      [expr 0x1 <<  6 ]
set AT91C_SPI_TXBUFE      [expr 0x1 <<  7 ]
set AT91C_SPI_NSSR        [expr 0x1 <<  8 ]
set AT91C_SPI_TXEMPTY     [expr 0x1 <<  9 ]
# -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- 
set AT91C_SPI_CPOL        [expr 0x1 <<  0 ]
set AT91C_SPI_NCPHA       [expr 0x1 <<  1 ]
set AT91C_SPI_CSNAAT      [expr 0x1 <<  2 ]
set AT91C_SPI_CSAAT       [expr 0x1 <<  3 ]
set AT91C_SPI_BITS        [expr 0xF <<  4 ]
set 	AT91C_SPI_BITS_8                    [expr 0x0 <<  4 ]
set 	AT91C_SPI_BITS_9                    [expr 0x1 <<  4 ]
set 	AT91C_SPI_BITS_10                   [expr 0x2 <<  4 ]
set 	AT91C_SPI_BITS_11                   [expr 0x3 <<  4 ]
set 	AT91C_SPI_BITS_12                   [expr 0x4 <<  4 ]
set 	AT91C_SPI_BITS_13                   [expr 0x5 <<  4 ]
set 	AT91C_SPI_BITS_14                   [expr 0x6 <<  4 ]
set 	AT91C_SPI_BITS_15                   [expr 0x7 <<  4 ]
set 	AT91C_SPI_BITS_16                   [expr 0x8 <<  4 ]
set AT91C_SPI_SCBR        [expr 0xFF <<  8 ]
set AT91C_SPI_DLYBS       [expr 0xFF << 16 ]
set AT91C_SPI_DLYBCT      [expr 0xFF << 24 ]

# *****************************************************************************
#              SOFTWARE API DEFINITION  FOR USB Device Interface
# *****************************************************************************
# -------- UDP_FRM_NUM : (UDP Offset: 0x0) USB Frame Number Register -------- 
set AT91C_UDP_FRM_NUM     [expr 0x7FF <<  0 ]
set AT91C_UDP_FRM_ERR     [expr 0x1 << 16 ]
set AT91C_UDP_FRM_OK      [expr 0x1 << 17 ]
# -------- UDP_GLB_STATE : (UDP Offset: 0x4) USB Global State Register -------- 
set AT91C_UDP_FADDEN      [expr 0x1 <<  0 ]
set AT91C_UDP_CONFG       [expr 0x1 <<  1 ]
set AT91C_UDP_ESR         [expr 0x1 <<  2 ]
set AT91C_UDP_RSMINPR     [expr 0x1 <<  3 ]
set AT91C_UDP_RMWUPE      [expr 0x1 <<  4 ]
# -------- UDP_FADDR : (UDP Offset: 0x8) USB Function Address Register -------- 
set AT91C_UDP_FADD        [expr 0xFF <<  0 ]
set AT91C_UDP_FEN         [expr 0x1 <<  8 ]
# -------- UDP_IER : (UDP Offset: 0x10) USB Interrupt Enable Register -------- 
set AT91C_UDP_EPINT0      [expr 0x1 <<  0 ]
set AT91C_UDP_EPINT1      [expr 0x1 <<  1 ]
set AT91C_UDP_EPINT2      [expr 0x1 <<  2 ]
set AT91C_UDP_EPINT3      [expr 0x1 <<  3 ]
set AT91C_UDP_EPINT4      [expr 0x1 <<  4 ]
set AT91C_UDP_EPINT5      [expr 0x1 <<  5 ]
set AT91C_UDP_EPINT6      [expr 0x1 <<  6 ]
set AT91C_UDP_EPINT7      [expr 0x1 <<  7 ]
set AT91C_UDP_RXSUSP      [expr 0x1 <<  8 ]
set AT91C_UDP_RXRSM       [expr 0x1 <<  9 ]
set AT91C_UDP_EXTRSM      [expr 0x1 << 10 ]
set AT91C_UDP_SOFINT      [expr 0x1 << 11 ]
set AT91C_UDP_WAKEUP      [expr 0x1 << 13 ]
# -------- UDP_IDR : (UDP Offset: 0x14) USB Interrupt Disable Register -------- 
set AT91C_UDP_EPINT0      [expr 0x1 <<  0 ]
set AT91C_UDP_EPINT1      [expr 0x1 <<  1 ]
set AT91C_UDP_EPINT2      [expr 0x1 <<  2 ]
set AT91C_UDP_EPINT3      [expr 0x1 <<  3 ]
set AT91C_UDP_EPINT4      [expr 0x1 <<  4 ]
set AT91C_UDP_EPINT5      [expr 0x1 <<  5 ]
set AT91C_UDP_EPINT6      [expr 0x1 <<  6 ]
set AT91C_UDP_EPINT7      [expr 0x1 <<  7 ]
set AT91C_UDP_RXSUSP      [expr 0x1 <<  8 ]
set AT91C_UDP_RXRSM       [expr 0x1 <<  9 ]
set AT91C_UDP_EXTRSM      [expr 0x1 << 10 ]
set AT91C_UDP_SOFINT      [expr 0x1 << 11 ]
set AT91C_UDP_WAKEUP      [expr 0x1 << 13 ]
# -------- UDP_IMR : (UDP Offset: 0x18) USB Interrupt Mask Register -------- 
set AT91C_UDP_EPINT0      [expr 0x1 <<  0 ]
set AT91C_UDP_EPINT1      [expr 0x1 <<  1 ]
set AT91C_UDP_EPINT2      [expr 0x1 <<  2 ]
set AT91C_UDP_EPINT3      [expr 0x1 <<  3 ]
set AT91C_UDP_EPINT4      [expr 0x1 <<  4 ]
set AT91C_UDP_EPINT5      [expr 0x1 <<  5 ]
set AT91C_UDP_EPINT6      [expr 0x1 <<  6 ]
set AT91C_UDP_EPINT7      [expr 0x1 <<  7 ]
set AT91C_UDP_RXSUSP      [expr 0x1 <<  8 ]
set AT91C_UDP_RXRSM       [expr 0x1 <<  9 ]
set AT91C_UDP_EXTRSM      [expr 0x1 << 10 ]
set AT91C_UDP_SOFINT      [expr 0x1 << 11 ]
set AT91C_UDP_WAKEUP      [expr 0x1 << 13 ]
# -------- UDP_ISR : (UDP Offset: 0x1c) USB Interrupt Status Register -------- 
set AT91C_UDP_EPINT0      [expr 0x1 <<  0 ]
set AT91C_UDP_EPINT1      [expr 0x1 <<  1 ]
set AT91C_UDP_EPINT2      [expr 0x1 <<  2 ]
set AT91C_UDP_EPINT3      [expr 0x1 <<  3 ]
set AT91C_UDP_EPINT4      [expr 0x1 <<  4 ]
set AT91C_UDP_EPINT5      [expr 0x1 <<  5 ]
set AT91C_UDP_EPINT6      [expr 0x1 <<  6 ]
set AT91C_UDP_EPINT7      [expr 0x1 <<  7 ]
set AT91C_UDP_RXSUSP      [expr 0x1 <<  8 ]
set AT91C_UDP_RXRSM       [expr 0x1 <<  9 ]
set AT91C_UDP_EXTRSM      [expr 0x1 << 10 ]
set AT91C_UDP_SOFINT      [expr 0x1 << 11 ]
set AT91C_UDP_ENDBUSRES   [expr 0x1 << 12 ]
set AT91C_UDP_WAKEUP      [expr 0x1 << 13 ]
# -------- UDP_ICR : (UDP Offset: 0x20) USB Interrupt Clear Register -------- 
set AT91C_UDP_EPINT0      [expr 0x1 <<  0 ]
set AT91C_UDP_EPINT1      [expr 0x1 <<  1 ]
set AT91C_UDP_EPINT2      [expr 0x1 <<  2 ]
set AT91C_UDP_EPINT3      [expr 0x1 <<  3 ]
set AT91C_UDP_EPINT4      [expr 0x1 <<  4 ]
set AT91C_UDP_EPINT5      [expr 0x1 <<  5 ]
set AT91C_UDP_EPINT6      [expr 0x1 <<  6 ]
set AT91C_UDP_EPINT7      [expr 0x1 <<  7 ]
set AT91C_UDP_RXSUSP      [expr 0x1 <<  8 ]
set AT91C_UDP_RXRSM       [expr 0x1 <<  9 ]
set AT91C_UDP_EXTRSM      [expr 0x1 << 10 ]
set AT91C_UDP_SOFINT      [expr 0x1 << 11 ]
set AT91C_UDP_WAKEUP      [expr 0x1 << 13 ]
# -------- UDP_RST_EP : (UDP Offset: 0x28) USB Reset Endpoint Register -------- 
set AT91C_UDP_EP0         [expr 0x1 <<  0 ]
set AT91C_UDP_EP1         [expr 0x1 <<  1 ]
set AT91C_UDP_EP2         [expr 0x1 <<  2 ]
set AT91C_UDP_EP3         [expr 0x1 <<  3 ]
set AT91C_UDP_EP4         [expr 0x1 <<  4 ]
set AT91C_UDP_EP5         [expr 0x1 <<  5 ]
set AT91C_UDP_EP6         [expr 0x1 <<  6 ]
set AT91C_UDP_EP7         [expr 0x1 <<  7 ]
# -------- UDP_CSR : (UDP Offset: 0x30) USB Endpoint Control and Status Register -------- 
set AT91C_UDP_TXCOMP      [expr 0x1 <<  0 ]
set AT91C_UDP_RX_DATA_BK0 [expr 0x1 <<  1 ]
set AT91C_UDP_RXSETUP     [expr 0x1 <<  2 ]
set AT91C_UDP_ISOERROR    [expr 0x1 <<  3 ]
set AT91C_UDP_STALLSENT   [expr 0x1 <<  3 ]
set AT91C_UDP_TXPKTRDY    [expr 0x1 <<  4 ]
set AT91C_UDP_FORCESTALL  [expr 0x1 <<  5 ]
set AT91C_UDP_RX_DATA_BK1 [expr 0x1 <<  6 ]
set AT91C_UDP_DIR         [expr 0x1 <<  7 ]
set AT91C_UDP_EPTYPE      [expr 0x7 <<  8 ]
set 	AT91C_UDP_EPTYPE_CTRL                 [expr 0x0 <<  8 ]
set 	AT91C_UDP_EPTYPE_ISO_OUT              [expr 0x1 <<  8 ]
set 	AT91C_UDP_EPTYPE_BULK_OUT             [expr 0x2 <<  8 ]
set 	AT91C_UDP_EPTYPE_INT_OUT              [expr 0x3 <<  8 ]
set 	AT91C_UDP_EPTYPE_ISO_IN               [expr 0x5 <<  8 ]
set 	AT91C_UDP_EPTYPE_BULK_IN              [expr 0x6 <<  8 ]
set 	AT91C_UDP_EPTYPE_INT_IN               [expr 0x7 <<  8 ]
set AT91C_UDP_DTGLE       [expr 0x1 << 11 ]
set AT91C_UDP_EPEDS       [expr 0x1 << 15 ]
set AT91C_UDP_RXBYTECNT   [expr 0x7FF << 16 ]
# -------- UDP_TXVC : (UDP Offset: 0x74) Transceiver Control Register -------- 
set AT91C_UDP_TXVDIS      [expr 0x1 <<  8 ]
set AT91C_UDP_PUON        [expr 0x1 <<  9 ]

# *****************************************************************************
#               REGISTER ADDRESS DEFINITION FOR AT91SAM3S4
# *****************************************************************************
# ========== Register definition for SYS peripheral ========== 
set AT91C_SYS_GPBR  0x400E1490
# ========== Register definition for SMC peripheral ========== 
set AT91C_SMC_DELAY2 0x400E00C4
set AT91C_SMC_CYCLE4 0x400E0048
set AT91C_SMC_CTRL5 0x400E005C
set AT91C_SMC_IPNAME2 0x400E00F4
set AT91C_SMC_DELAY5 0x400E00D0
set AT91C_SMC_DELAY4 0x400E00CC
set AT91C_SMC_CYCLE0 0x400E0008
set AT91C_SMC_PULSE1 0x400E0014
set AT91C_SMC_DELAY6 0x400E00D4
set AT91C_SMC_FEATURES 0x400E00F8
set AT91C_SMC_DELAY3 0x400E00C8
set AT91C_SMC_CTRL1 0x400E001C
set AT91C_SMC_PULSE7 0x400E0074
set AT91C_SMC_CTRL7 0x400E007C
set AT91C_SMC_VER   0x400E00FC
set AT91C_SMC_SETUP5 0x400E0050
set AT91C_SMC_CYCLE3 0x400E0038
set AT91C_SMC_SETUP3 0x400E0030
set AT91C_SMC_DELAY1 0x400E00C0
set AT91C_SMC_ADDRSIZE 0x400E00EC
set AT91C_SMC_PULSE3 0x400E0034
set AT91C_SMC_PULSE5 0x400E0054
set AT91C_SMC_PULSE4 0x400E0044
set AT91C_SMC_SETUP2 0x400E0020
set AT91C_SMC_DELAY8 0x400E00DC
set AT91C_SMC_CYCLE7 0x400E0078
set AT91C_SMC_CTRL0 0x400E000C
set AT91C_SMC_CYCLE2 0x400E0028
set AT91C_SMC_IPNAME1 0x400E00F0
set AT91C_SMC_SETUP1 0x400E0010
set AT91C_SMC_CTRL2 0x400E002C
set AT91C_SMC_CTRL4 0x400E004C
set AT91C_SMC_SETUP6 0x400E0060
set AT91C_SMC_CYCLE5 0x400E0058
set AT91C_SMC_CTRL6 0x400E006C
set AT91C_SMC_SETUP4 0x400E0040
set AT91C_SMC_PULSE2 0x400E0024
set AT91C_SMC_DELAY7 0x400E00D8
set AT91C_SMC_SETUP7 0x400E0070
set AT91C_SMC_CYCLE1 0x400E0018
set AT91C_SMC_CTRL3 0x400E003C
set AT91C_SMC_SETUP0 0x400E0000
set AT91C_SMC_PULSE0 0x400E0004
set AT91C_SMC_PULSE6 0x400E0064
set AT91C_SMC_CYCLE6 0x400E0068
# ========== Register definition for MATRIX peripheral ========== 
set AT91C_MATRIX_SFR2  0x400E0318
set AT91C_MATRIX_SFR3  0x400E031C
set AT91C_MATRIX_SCFG8 0x400E0260
set AT91C_MATRIX_MCFG2 0x400E0208
set AT91C_MATRIX_MCFG7 0x400E021C
set AT91C_MATRIX_SCFG3 0x400E024C
set AT91C_MATRIX_SCFG0 0x400E0240
set AT91C_MATRIX_SFR12 0x400E0340
set AT91C_MATRIX_SCFG1 0x400E0244
set AT91C_MATRIX_SFR8  0x400E0330
set AT91C_MATRIX_VER 0x400E03FC
set AT91C_MATRIX_SFR13 0x400E0344
set AT91C_MATRIX_SFR5  0x400E0324
set AT91C_MATRIX_MCFG0 0x400E0200
set AT91C_MATRIX_SCFG6 0x400E0258
set AT91C_MATRIX_SFR14 0x400E0348
set AT91C_MATRIX_SFR1  0x400E0314
set AT91C_MATRIX_SFR15 0x400E034C
set AT91C_MATRIX_SFR6  0x400E0328
set AT91C_MATRIX_SFR11 0x400E033C
set AT91C_MATRIX_IPNAME2 0x400E03F4
set AT91C_MATRIX_ADDRSIZE 0x400E03EC
set AT91C_MATRIX_MCFG5 0x400E0214
set AT91C_MATRIX_SFR9  0x400E0334
set AT91C_MATRIX_MCFG3 0x400E020C
set AT91C_MATRIX_SCFG4 0x400E0250
set AT91C_MATRIX_MCFG1 0x400E0204
set AT91C_MATRIX_SCFG7 0x400E025C
set AT91C_MATRIX_SFR10 0x400E0338
set AT91C_MATRIX_SCFG2 0x400E0248
set AT91C_MATRIX_SFR7  0x400E032C
set AT91C_MATRIX_IPNAME1 0x400E03F0
set AT91C_MATRIX_MCFG4 0x400E0210
set AT91C_MATRIX_SFR0  0x400E0310
set AT91C_MATRIX_FEATURES 0x400E03F8
set AT91C_MATRIX_SCFG5 0x400E0254
set AT91C_MATRIX_MCFG6 0x400E0218
set AT91C_MATRIX_SCFG9 0x400E0264
set AT91C_MATRIX_SFR4  0x400E0320
# ========== Register definition for CCFG peripheral ========== 
set AT91C_CCFG_FLASH0 0x400E0318
set AT91C_CCFG_RAM0 0x400E0310
set AT91C_CCFG_ROM  0x400E0314
set AT91C_CCFG_EBICSA 0x400E031C
set AT91C_CCFG_BRIDGE 0x400E0320
# ========== Register definition for NVIC peripheral ========== 
set AT91C_NVIC_MMAR 0xE000ED34
set AT91C_NVIC_STIR 0xE000EF00
set AT91C_NVIC_MMFR2 0xE000ED58
set AT91C_NVIC_CPUID 0xE000ED00
set AT91C_NVIC_DFSR 0xE000ED30
set AT91C_NVIC_HAND4PR 0xE000ED18
set AT91C_NVIC_HFSR 0xE000ED2C
set AT91C_NVIC_PID6 0xE000EFD8
set AT91C_NVIC_PFR0 0xE000ED40
set AT91C_NVIC_VTOFFR 0xE000ED08
set AT91C_NVIC_ISPR 0xE000E200
set AT91C_NVIC_PID0 0xE000EFE0
set AT91C_NVIC_PID7 0xE000EFDC
set AT91C_NVIC_STICKRVR 0xE000E014
set AT91C_NVIC_PID2 0xE000EFE8
set AT91C_NVIC_ISAR0 0xE000ED60
set AT91C_NVIC_SCR  0xE000ED10
set AT91C_NVIC_PID4 0xE000EFD0
set AT91C_NVIC_ISAR2 0xE000ED68
set AT91C_NVIC_ISER 0xE000E100
set AT91C_NVIC_IPR  0xE000E400
set AT91C_NVIC_AIRCR 0xE000ED0C
set AT91C_NVIC_CID2 0xE000EFF8
set AT91C_NVIC_ICPR 0xE000E280
set AT91C_NVIC_CID3 0xE000EFFC
set AT91C_NVIC_CFSR 0xE000ED28
set AT91C_NVIC_AFR0 0xE000ED4C
set AT91C_NVIC_ICSR 0xE000ED04
set AT91C_NVIC_CCR  0xE000ED14
set AT91C_NVIC_CID0 0xE000EFF0
set AT91C_NVIC_ISAR1 0xE000ED64
set AT91C_NVIC_STICKCVR 0xE000E018
set AT91C_NVIC_STICKCSR 0xE000E010
set AT91C_NVIC_CID1 0xE000EFF4
set AT91C_NVIC_DFR0 0xE000ED48
set AT91C_NVIC_MMFR3 0xE000ED5C
set AT91C_NVIC_MMFR0 0xE000ED50
set AT91C_NVIC_STICKCALVR 0xE000E01C
set AT91C_NVIC_PID1 0xE000EFE4
set AT91C_NVIC_HAND12PR 0xE000ED20
set AT91C_NVIC_MMFR1 0xE000ED54
set AT91C_NVIC_AFSR 0xE000ED3C
set AT91C_NVIC_HANDCSR 0xE000ED24
set AT91C_NVIC_ISAR4 0xE000ED70
set AT91C_NVIC_ABR  0xE000E300
set AT91C_NVIC_PFR1 0xE000ED44
set AT91C_NVIC_PID5 0xE000EFD4
set AT91C_NVIC_ICTR 0xE000E004
set AT91C_NVIC_ICER 0xE000E180
set AT91C_NVIC_PID3 0xE000EFEC
set AT91C_NVIC_ISAR3 0xE000ED6C
set AT91C_NVIC_HAND8PR 0xE000ED1C
set AT91C_NVIC_BFAR 0xE000ED38
# ========== Register definition for MPU peripheral ========== 
set AT91C_MPU_REG_BASE_ADDR3 0xE000EDB4
set AT91C_MPU_REG_NB 0xE000ED98
set AT91C_MPU_ATTR_SIZE1 0xE000EDA8
set AT91C_MPU_REG_BASE_ADDR1 0xE000EDA4
set AT91C_MPU_ATTR_SIZE3 0xE000EDB8
set AT91C_MPU_CTRL  0xE000ED94
set AT91C_MPU_ATTR_SIZE2 0xE000EDB0
set AT91C_MPU_REG_BASE_ADDR 0xE000ED9C
set AT91C_MPU_REG_BASE_ADDR2 0xE000EDAC
set AT91C_MPU_ATTR_SIZE 0xE000EDA0
set AT91C_MPU_TYPE  0xE000ED90
# ========== Register definition for CM3 peripheral ========== 
set AT91C_CM3_SHCSR 0xE000ED24
set AT91C_CM3_CCR   0xE000ED14
set AT91C_CM3_ICSR  0xE000ED04
set AT91C_CM3_CPUID 0xE000ED00
set AT91C_CM3_SCR   0xE000ED10
set AT91C_CM3_AIRCR 0xE000ED0C
set AT91C_CM3_SHPR  0xE000ED18
set AT91C_CM3_VTOR  0xE000ED08
# ========== Register definition for PDC_DBGU0 peripheral ========== 
set AT91C_DBGU0_TPR 0x400E0708
set AT91C_DBGU0_PTCR 0x400E0720
set AT91C_DBGU0_TNCR 0x400E071C
set AT91C_DBGU0_PTSR 0x400E0724
set AT91C_DBGU0_RNCR 0x400E0714
set AT91C_DBGU0_RPR 0x400E0700
set AT91C_DBGU0_TCR 0x400E070C
set AT91C_DBGU0_RNPR 0x400E0710
set AT91C_DBGU0_TNPR 0x400E0718
set AT91C_DBGU0_RCR 0x400E0704
# ========== Register definition for DBGU0 peripheral ========== 
set AT91C_DBGU0_CR  0x400E0600
set AT91C_DBGU0_IDR 0x400E060C
set AT91C_DBGU0_CIDR 0x400E0740
set AT91C_DBGU0_IPNAME2 0x400E06F4
set AT91C_DBGU0_FEATURES 0x400E06F8
set AT91C_DBGU0_FNTR 0x400E0648
set AT91C_DBGU0_RHR 0x400E0618
set AT91C_DBGU0_THR 0x400E061C
set AT91C_DBGU0_ADDRSIZE 0x400E06EC
set AT91C_DBGU0_MR  0x400E0604
set AT91C_DBGU0_IER 0x400E0608
set AT91C_DBGU0_BRGR 0x400E0620
set AT91C_DBGU0_CSR 0x400E0614
set AT91C_DBGU0_VER 0x400E06FC
set AT91C_DBGU0_IMR 0x400E0610
set AT91C_DBGU0_IPNAME1 0x400E06F0
set AT91C_DBGU0_EXID 0x400E0744
# ========== Register definition for PDC_DBGU1 peripheral ========== 
set AT91C_DBGU1_RNCR 0x400E0914
set AT91C_DBGU1_RPR 0x400E0900
set AT91C_DBGU1_TNCR 0x400E091C
set AT91C_DBGU1_TNPR 0x400E0918
set AT91C_DBGU1_PTSR 0x400E0924
set AT91C_DBGU1_PTCR 0x400E0920
set AT91C_DBGU1_RCR 0x400E0904
set AT91C_DBGU1_RNPR 0x400E0910
set AT91C_DBGU1_TPR 0x400E0908
set AT91C_DBGU1_TCR 0x400E090C
# ========== Register definition for DBGU1 peripheral ========== 
set AT91C_DBGU1_RHR 0x400E0818
set AT91C_DBGU1_IPNAME1 0x400E08F0
set AT91C_DBGU1_CIDR 0x400E0940
set AT91C_DBGU1_CR  0x400E0800
set AT91C_DBGU1_VER 0x400E08FC
set AT91C_DBGU1_IPNAME2 0x400E08F4
set AT91C_DBGU1_BRGR 0x400E0820
set AT91C_DBGU1_FNTR 0x400E0848
set AT91C_DBGU1_MR  0x400E0804
set AT91C_DBGU1_ADDRSIZE 0x400E08EC
set AT91C_DBGU1_CSR 0x400E0814
set AT91C_DBGU1_IMR 0x400E0810
set AT91C_DBGU1_EXID 0x400E0944
set AT91C_DBGU1_IDR 0x400E080C
set AT91C_DBGU1_FEATURES 0x400E08F8
set AT91C_DBGU1_IER 0x400E0808
set AT91C_DBGU1_THR 0x400E081C
# ========== Register definition for PIOA peripheral ========== 
set AT91C_PIOA_SENIDR 0x400E0F58
set AT91C_PIOA_OWSR 0x400E0EA8
set AT91C_PIOA_PSR  0x400E0E08
set AT91C_PIOA_MDER 0x400E0E50
set AT91C_PIOA_IPNAME1 0x400E0EF0
set AT91C_PIOA_FEATURES 0x400E0EF8
set AT91C_PIOA_SP2  0x400E0E74
set AT91C_PIOA_ODR  0x400E0E14
set AT91C_PIOA_IDR  0x400E0E44
set AT91C_PIOA_PDR  0x400E0E04
set AT91C_PIOA_PDSR 0x400E0E3C
set AT91C_PIOA_PPDER 0x400E0E94
set AT91C_PIOA_SENIER 0x400E0F54
set AT91C_PIOA_SLEW2 0x400E0F04
set AT91C_PIOA_SENMR 0x400E0F50
set AT91C_PIOA_PPUDR 0x400E0E60
set AT91C_PIOA_OWDR 0x400E0EA4
set AT91C_PIOA_ADDRSIZE 0x400E0EEC
set AT91C_PIOA_IFER 0x400E0E20
set AT91C_PIOA_PPDSR 0x400E0E98
set AT91C_PIOA_SP1  0x400E0E70
set AT91C_PIOA_SENIMR 0x400E0F5C
set AT91C_PIOA_SENDATA 0x400E0F64
set AT91C_PIOA_VER  0x400E0EFC
set AT91C_PIOA_PER  0x400E0E00
set AT91C_PIOA_IMR  0x400E0E48
set AT91C_PIOA_PPUSR 0x400E0E68
set AT91C_PIOA_ODSR 0x400E0E38
set AT91C_PIOA_SENISR 0x400E0F60
set AT91C_PIOA_IFDR 0x400E0E24
set AT91C_PIOA_SODR 0x400E0E30
set AT91C_PIOA_SLEW1 0x400E0F00
set AT91C_PIOA_IER  0x400E0E40
set AT91C_PIOA_MDSR 0x400E0E58
set AT91C_PIOA_ISR  0x400E0E4C
set AT91C_PIOA_IFSR 0x400E0E28
set AT91C_PIOA_PPDDR 0x400E0E90
set AT91C_PIOA_PPUER 0x400E0E64
set AT91C_PIOA_OWER 0x400E0EA0
set AT91C_PIOA_IPNAME2 0x400E0EF4
set AT91C_PIOA_MDDR 0x400E0E54
set AT91C_PIOA_CODR 0x400E0E34
set AT91C_PIOA_OER  0x400E0E10
set AT91C_PIOA_OSR  0x400E0E18
set AT91C_PIOA_ABSR 0x400E0E78
# ========== Register definition for PDC_PIOA peripheral ========== 
set AT91C_PIOA_RPR  0x400E0F68
set AT91C_PIOA_TPR  0x400E0F70
set AT91C_PIOA_RCR  0x400E0F6C
set AT91C_PIOA_PTSR 0x400E0F8C
set AT91C_PIOA_TCR  0x400E0F74
set AT91C_PIOA_PTCR 0x400E0F88
set AT91C_PIOA_RNPR 0x400E0F78
set AT91C_PIOA_TNCR 0x400E0F84
set AT91C_PIOA_RNCR 0x400E0F7C
set AT91C_PIOA_TNPR 0x400E0F80
# ========== Register definition for PIOB peripheral ========== 
set AT91C_PIOB_MDDR 0x400E1054
set AT91C_PIOB_ABSR 0x400E1078
set AT91C_PIOB_SP1  0x400E1070
set AT91C_PIOB_ODSR 0x400E1038
set AT91C_PIOB_SLEW1 0x400E1100
set AT91C_PIOB_SENISR 0x400E1160
set AT91C_PIOB_OSR  0x400E1018
set AT91C_PIOB_IFER 0x400E1020
set AT91C_PIOB_SENDATA 0x400E1164
set AT91C_PIOB_MDSR 0x400E1058
set AT91C_PIOB_IFDR 0x400E1024
set AT91C_PIOB_MDER 0x400E1050
set AT91C_PIOB_SENIDR 0x400E1158
set AT91C_PIOB_IER  0x400E1040
set AT91C_PIOB_OWDR 0x400E10A4
set AT91C_PIOB_IFSR 0x400E1028
set AT91C_PIOB_ISR  0x400E104C
set AT91C_PIOB_PPUDR 0x400E1060
set AT91C_PIOB_PDSR 0x400E103C
set AT91C_PIOB_IPNAME2 0x400E10F4
set AT91C_PIOB_PPUER 0x400E1064
set AT91C_PIOB_SLEW2 0x400E1104
set AT91C_PIOB_OER  0x400E1010
set AT91C_PIOB_CODR 0x400E1034
set AT91C_PIOB_PPDDR 0x400E1090
set AT91C_PIOB_OWER 0x400E10A0
set AT91C_PIOB_VER  0x400E10FC
set AT91C_PIOB_PPDER 0x400E1094
set AT91C_PIOB_IMR  0x400E1048
set AT91C_PIOB_PPUSR 0x400E1068
set AT91C_PIOB_IPNAME1 0x400E10F0
set AT91C_PIOB_ADDRSIZE 0x400E10EC
set AT91C_PIOB_SP2  0x400E1074
set AT91C_PIOB_IDR  0x400E1044
set AT91C_PIOB_SENMR 0x400E1150
set AT91C_PIOB_SODR 0x400E1030
set AT91C_PIOB_PPDSR 0x400E1098
set AT91C_PIOB_PSR  0x400E1008
set AT91C_PIOB_ODR  0x400E1014
set AT91C_PIOB_OWSR 0x400E10A8
set AT91C_PIOB_FEATURES 0x400E10F8
set AT91C_PIOB_PDR  0x400E1004
set AT91C_PIOB_SENIMR 0x400E115C
set AT91C_PIOB_SENIER 0x400E1154
set AT91C_PIOB_PER  0x400E1000
# ========== Register definition for PIOC peripheral ========== 
set AT91C_PIOC_VER  0x400E12FC
set AT91C_PIOC_IMR  0x400E1248
set AT91C_PIOC_PSR  0x400E1208
set AT91C_PIOC_PPDSR 0x400E1298
set AT91C_PIOC_OER  0x400E1210
set AT91C_PIOC_OSR  0x400E1218
set AT91C_PIOC_MDDR 0x400E1254
set AT91C_PIOC_PPUSR 0x400E1268
set AT91C_PIOC_ODSR 0x400E1238
set AT91C_PIOC_SLEW2 0x400E1304
set AT91C_PIOC_SENMR 0x400E1350
set AT91C_PIOC_IFER 0x400E1220
set AT91C_PIOC_PDR  0x400E1204
set AT91C_PIOC_MDER 0x400E1250
set AT91C_PIOC_SP2  0x400E1274
set AT91C_PIOC_IPNAME1 0x400E12F0
set AT91C_PIOC_IER  0x400E1240
set AT91C_PIOC_OWDR 0x400E12A4
set AT91C_PIOC_IDR  0x400E1244
set AT91C_PIOC_PDSR 0x400E123C
set AT91C_PIOC_SENIDR 0x400E1358
set AT91C_PIOC_SENISR 0x400E1360
set AT91C_PIOC_PER  0x400E1200
set AT91C_PIOC_SENDATA 0x400E1364
set AT91C_PIOC_IPNAME2 0x400E12F4
set AT91C_PIOC_PPDDR 0x400E1290
set AT91C_PIOC_ADDRSIZE 0x400E12EC
set AT91C_PIOC_IFDR 0x400E1224
set AT91C_PIOC_ODR  0x400E1214
set AT91C_PIOC_CODR 0x400E1234
set AT91C_PIOC_MDSR 0x400E1258
set AT91C_PIOC_FEATURES 0x400E12F8
set AT91C_PIOC_IFSR 0x400E1228
set AT91C_PIOC_PPUER 0x400E1264
set AT91C_PIOC_PPDER 0x400E1294
set AT91C_PIOC_OWSR 0x400E12A8
set AT91C_PIOC_ISR  0x400E124C
set AT91C_PIOC_OWER 0x400E12A0
set AT91C_PIOC_PPUDR 0x400E1260
set AT91C_PIOC_SENIMR 0x400E135C
set AT91C_PIOC_SLEW1 0x400E1300
set AT91C_PIOC_SENIER 0x400E1354
set AT91C_PIOC_SODR 0x400E1230
set AT91C_PIOC_SP1  0x400E1270
set AT91C_PIOC_ABSR 0x400E1278
# ========== Register definition for PMC peripheral ========== 
set AT91C_PMC_PLLAR 0x400E0428
set AT91C_PMC_UCKR  0x400E041C
set AT91C_PMC_FSMR  0x400E0470
set AT91C_PMC_MCKR  0x400E0430
set AT91C_PMC_SCER  0x400E0400
set AT91C_PMC_PCSR  0x400E0418
set AT91C_PMC_MCFR  0x400E0424
set AT91C_PMC_PCER1 0x400E0500
set AT91C_PMC_FOCR  0x400E0478
set AT91C_PMC_PCSR1 0x400E0508
set AT91C_PMC_FSPR  0x400E0474
set AT91C_PMC_SCSR  0x400E0408
set AT91C_PMC_IDR   0x400E0464
set AT91C_PMC_UDPR  0x400E0438
set AT91C_PMC_PCDR1 0x400E0504
set AT91C_PMC_VER   0x400E04FC
set AT91C_PMC_IMR   0x400E046C
set AT91C_PMC_IPNAME2 0x400E04F4
set AT91C_PMC_SCDR  0x400E0404
set AT91C_PMC_PCKR  0x400E0440
set AT91C_PMC_ADDRSIZE 0x400E04EC
set AT91C_PMC_PCDR  0x400E0414
set AT91C_PMC_MOR   0x400E0420
set AT91C_PMC_SR    0x400E0468
set AT91C_PMC_IER   0x400E0460
set AT91C_PMC_PLLBR 0x400E042C
set AT91C_PMC_IPNAME1 0x400E04F0
set AT91C_PMC_PCER  0x400E0410
set AT91C_PMC_FEATURES 0x400E04F8
set AT91C_PMC_PCR   0x400E050C
# ========== Register definition for CKGR peripheral ========== 
set AT91C_CKGR_PLLAR 0x400E0428
set AT91C_CKGR_UCKR 0x400E041C
set AT91C_CKGR_MOR  0x400E0420
set AT91C_CKGR_MCFR 0x400E0424
set AT91C_CKGR_PLLBR 0x400E042C
# ========== Register definition for RSTC peripheral ========== 
set AT91C_RSTC_RSR  0x400E1404
set AT91C_RSTC_RCR  0x400E1400
set AT91C_RSTC_RMR  0x400E1408
set AT91C_RSTC_VER  0x400E14FC
# ========== Register definition for SUPC peripheral ========== 
set AT91C_SUPC_FWUTR 0x400E1428
set AT91C_SUPC_SR   0x400E1424
set AT91C_SUPC_BOMR 0x400E1414
set AT91C_SUPC_WUMR 0x400E141C
set AT91C_SUPC_WUIR 0x400E1420
set AT91C_SUPC_CR   0x400E1410
set AT91C_SUPC_MR   0x400E1418
# ========== Register definition for RTTC peripheral ========== 
set AT91C_RTTC_RTSR 0x400E143C
set AT91C_RTTC_RTVR 0x400E1438
set AT91C_RTTC_RTMR 0x400E1430
set AT91C_RTTC_RTAR 0x400E1434
# ========== Register definition for WDTC peripheral ========== 
set AT91C_WDTC_WDCR 0x400E1450
set AT91C_WDTC_WDMR 0x400E1454
set AT91C_WDTC_WDSR 0x400E1458
# ========== Register definition for RTC peripheral ========== 
set AT91C_RTC_VER   0x400E148C
set AT91C_RTC_TIMR  0x400E1468
set AT91C_RTC_CALALR 0x400E1474
set AT91C_RTC_IER   0x400E1480
set AT91C_RTC_MR    0x400E1464
set AT91C_RTC_CALR  0x400E146C
set AT91C_RTC_TIMALR 0x400E1470
set AT91C_RTC_SCCR  0x400E147C
set AT91C_RTC_CR    0x400E1460
set AT91C_RTC_IDR   0x400E1484
set AT91C_RTC_IMR   0x400E1488
set AT91C_RTC_SR    0x400E1478
# ========== Register definition for ADC0 peripheral ========== 
set AT91C_ADC0_CDR2 0x40038058
set AT91C_ADC0_CGR  0x40038048
set AT91C_ADC0_CDR7 0x4003806C
set AT91C_ADC0_IDR  0x40038028
set AT91C_ADC0_CR   0x40038000
set AT91C_ADC0_FEATURES 0x400380F8
set AT91C_ADC0_CWR  0x40038040
set AT91C_ADC0_IPNAME1 0x400380F0
set AT91C_ADC0_CDR9 0x40038074
set AT91C_ADC0_CDR3 0x4003805C
set AT91C_ADC0_SR   0x40038030
set AT91C_ADC0_CHER 0x40038010
set AT91C_ADC0_CDR1 0x40038054
set AT91C_ADC0_CDR6 0x40038068
set AT91C_ADC0_MR   0x40038004
set AT91C_ADC0_CWSR 0x40038044
set AT91C_ADC0_VER  0x400380FC
set AT91C_ADC0_COR  0x4003804C
set AT91C_ADC0_CDR8 0x40038070
set AT91C_ADC0_IPNAME2 0x400380F4
set AT91C_ADC0_CDR0 0x40038050
set AT91C_ADC0_LCDR 0x40038020
set AT91C_ADC0_CDR12 0x40038080
set AT91C_ADC0_CHDR 0x40038014
set AT91C_ADC0_OVR  0x4003803C
set AT91C_ADC0_CDR15 0x4003808C
set AT91C_ADC0_CDR11 0x4003807C
set AT91C_ADC0_ADDRSIZE 0x400380EC
set AT91C_ADC0_CDR13 0x40038084
set AT91C_ADC0_ACR  0x40038094
set AT91C_ADC0_CDR5 0x40038064
set AT91C_ADC0_CDR14 0x40038088
set AT91C_ADC0_IMR  0x4003802C
set AT91C_ADC0_CHSR 0x40038018
set AT91C_ADC0_CDR10 0x40038078
set AT91C_ADC0_IER  0x40038024
set AT91C_ADC0_CDR4 0x40038060
# ========== Register definition for DAC0 peripheral ========== 
set AT91C_DAC0_FEATURES 0x4003C0F8
set AT91C_DAC0_ADDRSIZE 0x4003C0EC
set AT91C_DAC0_WPMR 0x4003C0E4
set AT91C_DAC0_CHDR 0x4003C014
set AT91C_DAC0_IPNAME1 0x4003C0F0
set AT91C_DAC0_IDR  0x4003C028
set AT91C_DAC0_CR   0x4003C000
set AT91C_DAC0_IPNAME2 0x4003C0F4
set AT91C_DAC0_IMR  0x4003C02C
set AT91C_DAC0_CHSR 0x4003C018
set AT91C_DAC0_ACR  0x4003C094
set AT91C_DAC0_WPSR 0x4003C0E8
set AT91C_DAC0_CHER 0x4003C010
set AT91C_DAC0_CDR  0x4003C020
set AT91C_DAC0_IER  0x4003C024
set AT91C_DAC0_ISR  0x4003C030
set AT91C_DAC0_VER  0x4003C0FC
set AT91C_DAC0_MR   0x4003C004
# ========== Register definition for ACC0 peripheral ========== 
set AT91C_ACC0_IPNAME1 0x400400F0
set AT91C_ACC0_MR   0x40040004
set AT91C_ACC0_FEATURES 0x400400F8
set AT91C_ACC0_IMR  0x4004002C
set AT91C_ACC0_ACR  0x40040094
set AT91C_ACC0_ADDRSIZE 0x400400EC
set AT91C_ACC0_IER  0x40040024
set AT91C_ACC0_ISR  0x40040030
set AT91C_ACC0_IDR  0x40040028
set AT91C_ACC0_MODE 0x400400E4
set AT91C_ACC0_VER  0x400400FC
set AT91C_ACC0_CR   0x40040000
set AT91C_ACC0_IPNAME2 0x400400F4
set AT91C_ACC0_STATUS 0x400400E8
# ========== Register definition for HCBDMA peripheral ========== 
set AT91C_HCBDMA_CBIMR 0x4004401C
set AT91C_HCBDMA_CBCRCCR 0x40044034
set AT91C_HCBDMA_CBSR 0x40044010
set AT91C_HCBDMA_CBCRCISR 0x4004404C
set AT91C_HCBDMA_CBCRCSR 0x4004403C
set AT91C_HCBDMA_CBIDR 0x40044018
set AT91C_HCBDMA_CBCRCIDR 0x40044044
set AT91C_HCBDMA_CBDLIER 0x40044024
set AT91C_HCBDMA_CBEN 0x40044008
set AT91C_HCBDMA_FEATURES 0x400440F8
set AT91C_HCBDMA_CBDSCR 0x40044000
set AT91C_HCBDMA_ADDRSIZE 0x400440EC
set AT91C_HCBDMA_CBDLISR 0x40044030
set AT91C_HCBDMA_CBDLIDR 0x40044028
set AT91C_HCBDMA_CBCRCIMR 0x40044048
set AT91C_HCBDMA_VER 0x400440FC
set AT91C_HCBDMA_CBCRCIER 0x40044040
set AT91C_HCBDMA_IPNAME2 0x400440F4
set AT91C_HCBDMA_CBIER 0x40044014
set AT91C_HCBDMA_CBISR 0x40044020
set AT91C_HCBDMA_IPNAME1 0x400440F0
set AT91C_HCBDMA_CBDIS 0x4004400C
set AT91C_HCBDMA_CBNXTEN 0x40044004
set AT91C_HCBDMA_CBDLIMR 0x4004402C
set AT91C_HCBDMA_CBCRCMR 0x40044038
# ========== Register definition for TC0 peripheral ========== 
set AT91C_TC0_SR    0x40010020
set AT91C_TC0_CCR   0x40010000
set AT91C_TC0_CMR   0x40010004
set AT91C_TC0_IER   0x40010024
set AT91C_TC0_CV    0x40010010
set AT91C_TC0_RB    0x40010018
set AT91C_TC0_IDR   0x40010028
set AT91C_TC0_RA    0x40010014
set AT91C_TC0_RC    0x4001001C
set AT91C_TC0_IMR   0x4001002C
# ========== Register definition for TC1 peripheral ========== 
set AT91C_TC1_SR    0x40010060
set AT91C_TC1_CV    0x40010050
set AT91C_TC1_RA    0x40010054
set AT91C_TC1_IER   0x40010064
set AT91C_TC1_RB    0x40010058
set AT91C_TC1_RC    0x4001005C
set AT91C_TC1_CCR   0x40010040
set AT91C_TC1_IMR   0x4001006C
set AT91C_TC1_IDR   0x40010068
set AT91C_TC1_CMR   0x40010044
# ========== Register definition for TC2 peripheral ========== 
set AT91C_TC2_SR    0x400100A0
set AT91C_TC2_IER   0x400100A4
set AT91C_TC2_CCR   0x40010080
set AT91C_TC2_IDR   0x400100A8
set AT91C_TC2_RA    0x40010094
set AT91C_TC2_RB    0x40010098
set AT91C_TC2_IMR   0x400100AC
set AT91C_TC2_CV    0x40010090
set AT91C_TC2_RC    0x4001009C
set AT91C_TC2_CMR   0x40010084
# ========== Register definition for TC3 peripheral ========== 
set AT91C_TC3_IDR   0x40014028
set AT91C_TC3_IER   0x40014024
set AT91C_TC3_SR    0x40014020
set AT91C_TC3_CV    0x40014010
set AT91C_TC3_CMR   0x40014004
set AT91C_TC3_RC    0x4001401C
set AT91C_TC3_RA    0x40014014
set AT91C_TC3_IMR   0x4001402C
set AT91C_TC3_RB    0x40014018
set AT91C_TC3_CCR   0x40014000
# ========== Register definition for TC4 peripheral ========== 
set AT91C_TC4_CV    0x40014050
set AT91C_TC4_CMR   0x40014044
set AT91C_TC4_RA    0x40014054
set AT91C_TC4_IMR   0x4001406C
set AT91C_TC4_RC    0x4001405C
set AT91C_TC4_SR    0x40014060
set AT91C_TC4_RB    0x40014058
set AT91C_TC4_IDR   0x40014068
set AT91C_TC4_IER   0x40014064
set AT91C_TC4_CCR   0x40014040
# ========== Register definition for TC5 peripheral ========== 
set AT91C_TC5_CV    0x40014090
set AT91C_TC5_IER   0x400140A4
set AT91C_TC5_CMR   0x40014084
set AT91C_TC5_IMR   0x400140AC
set AT91C_TC5_RA    0x40014094
set AT91C_TC5_RB    0x40014098
set AT91C_TC5_RC    0x4001409C
set AT91C_TC5_SR    0x400140A0
set AT91C_TC5_CCR   0x40014080
set AT91C_TC5_IDR   0x400140A8
# ========== Register definition for TCB0 peripheral ========== 
set AT91C_TCB0_BCR  0x400100C0
set AT91C_TCB0_VER  0x400100FC
set AT91C_TCB0_ADDRSIZE 0x400100EC
set AT91C_TCB0_FEATURES 0x400100F8
set AT91C_TCB0_IPNAME2 0x400100F4
set AT91C_TCB0_BMR  0x400100C4
set AT91C_TCB0_IPNAME1 0x400100F0
# ========== Register definition for TCB1 peripheral ========== 
set AT91C_TCB1_IPNAME1 0x40010130
set AT91C_TCB1_IPNAME2 0x40010134
set AT91C_TCB1_BCR  0x40010100
set AT91C_TCB1_VER  0x4001013C
set AT91C_TCB1_FEATURES 0x40010138
set AT91C_TCB1_ADDRSIZE 0x4001012C
set AT91C_TCB1_BMR  0x40010104
# ========== Register definition for TCB2 peripheral ========== 
set AT91C_TCB2_VER  0x4001017C
set AT91C_TCB2_ADDRSIZE 0x4001016C
set AT91C_TCB2_FEATURES 0x40010178
set AT91C_TCB2_BCR  0x40010140
set AT91C_TCB2_IPNAME2 0x40010174
set AT91C_TCB2_BMR  0x40010144
set AT91C_TCB2_IPNAME1 0x40010170
# ========== Register definition for TCB3 peripheral ========== 
set AT91C_TCB3_IPNAME2 0x400140F4
set AT91C_TCB3_BMR  0x400140C4
set AT91C_TCB3_IPNAME1 0x400140F0
set AT91C_TCB3_FEATURES 0x400140F8
set AT91C_TCB3_ADDRSIZE 0x400140EC
set AT91C_TCB3_VER  0x400140FC
set AT91C_TCB3_BCR  0x400140C0
# ========== Register definition for TCB4 peripheral ========== 
set AT91C_TCB4_BMR  0x40014104
set AT91C_TCB4_BCR  0x40014100
set AT91C_TCB4_IPNAME2 0x40014134
set AT91C_TCB4_FEATURES 0x40014138
set AT91C_TCB4_IPNAME1 0x40014130
set AT91C_TCB4_VER  0x4001413C
set AT91C_TCB4_ADDRSIZE 0x4001412C
# ========== Register definition for TCB5 peripheral ========== 
set AT91C_TCB5_VER  0x4001417C
set AT91C_TCB5_ADDRSIZE 0x4001416C
set AT91C_TCB5_BMR  0x40014144
set AT91C_TCB5_FEATURES 0x40014178
set AT91C_TCB5_IPNAME2 0x40014174
set AT91C_TCB5_IPNAME1 0x40014170
set AT91C_TCB5_BCR  0x40014140
# ========== Register definition for EFC0 peripheral ========== 
set AT91C_EFC0_FMR  0x400E0A00
set AT91C_EFC0_FVR  0x400E0A14
set AT91C_EFC0_FSR  0x400E0A08
set AT91C_EFC0_FCR  0x400E0A04
set AT91C_EFC0_FRR  0x400E0A0C
# ========== Register definition for MCI0 peripheral ========== 
set AT91C_MCI0_DMA  0x40000050
set AT91C_MCI0_SDCR 0x4000000C
set AT91C_MCI0_IPNAME1 0x400000F0
set AT91C_MCI0_CSTOR 0x4000001C
set AT91C_MCI0_RDR  0x40000030
set AT91C_MCI0_CMDR 0x40000014
set AT91C_MCI0_IDR  0x40000048
set AT91C_MCI0_ADDRSIZE 0x400000EC
set AT91C_MCI0_WPCR 0x400000E4
set AT91C_MCI0_RSPR 0x40000020
set AT91C_MCI0_IPNAME2 0x400000F4
set AT91C_MCI0_CR   0x40000000
set AT91C_MCI0_IMR  0x4000004C
set AT91C_MCI0_WPSR 0x400000E8
set AT91C_MCI0_DTOR 0x40000008
set AT91C_MCI0_MR   0x40000004
set AT91C_MCI0_SR   0x40000040
set AT91C_MCI0_IER  0x40000044
set AT91C_MCI0_VER  0x400000FC
set AT91C_MCI0_FEATURES 0x400000F8
set AT91C_MCI0_BLKR 0x40000018
set AT91C_MCI0_ARGR 0x40000010
set AT91C_MCI0_FIFO 0x40000200
set AT91C_MCI0_TDR  0x40000034
set AT91C_MCI0_CFG  0x40000054
# ========== Register definition for PDC_TWI0 peripheral ========== 
set AT91C_TWI0_PTSR 0x40018124
set AT91C_TWI0_TPR  0x40018108
set AT91C_TWI0_RPR  0x40018100
set AT91C_TWI0_TNPR 0x40018118
set AT91C_TWI0_PTCR 0x40018120
set AT91C_TWI0_RCR  0x40018104
set AT91C_TWI0_RNCR 0x40018114
set AT91C_TWI0_RNPR 0x40018110
set AT91C_TWI0_TNCR 0x4001811C
set AT91C_TWI0_TCR  0x4001810C
# ========== Register definition for PDC_TWI1 peripheral ========== 
set AT91C_TWI1_TPR  0x4001C108
set AT91C_TWI1_RNCR 0x4001C114
set AT91C_TWI1_TNCR 0x4001C11C
set AT91C_TWI1_TCR  0x4001C10C
set AT91C_TWI1_TNPR 0x4001C118
set AT91C_TWI1_PTCR 0x4001C120
set AT91C_TWI1_RNPR 0x4001C110
set AT91C_TWI1_PTSR 0x4001C124
set AT91C_TWI1_RPR  0x4001C100
set AT91C_TWI1_RCR  0x4001C104
# ========== Register definition for TWI0 peripheral ========== 
set AT91C_TWI0_IMR  0x4001802C
set AT91C_TWI0_IPNAME1 0x400180F0
set AT91C_TWI0_CR   0x40018000
set AT91C_TWI0_IPNAME2 0x400180F4
set AT91C_TWI0_CWGR 0x40018010
set AT91C_TWI0_SMR  0x40018008
set AT91C_TWI0_ADDRSIZE 0x400180EC
set AT91C_TWI0_SR   0x40018020
set AT91C_TWI0_IER  0x40018024
set AT91C_TWI0_VER  0x400180FC
set AT91C_TWI0_RHR  0x40018030
set AT91C_TWI0_IADR 0x4001800C
set AT91C_TWI0_IDR  0x40018028
set AT91C_TWI0_THR  0x40018034
set AT91C_TWI0_FEATURES 0x400180F8
set AT91C_TWI0_MMR  0x40018004
# ========== Register definition for TWI1 peripheral ========== 
set AT91C_TWI1_CR   0x4001C000
set AT91C_TWI1_VER  0x4001C0FC
set AT91C_TWI1_IMR  0x4001C02C
set AT91C_TWI1_IADR 0x4001C00C
set AT91C_TWI1_THR  0x4001C034
set AT91C_TWI1_IPNAME2 0x4001C0F4
set AT91C_TWI1_FEATURES 0x4001C0F8
set AT91C_TWI1_SMR  0x4001C008
set AT91C_TWI1_IDR  0x4001C028
set AT91C_TWI1_SR   0x4001C020
set AT91C_TWI1_IPNAME1 0x4001C0F0
set AT91C_TWI1_IER  0x4001C024
set AT91C_TWI1_ADDRSIZE 0x4001C0EC
set AT91C_TWI1_CWGR 0x4001C010
set AT91C_TWI1_MMR  0x4001C004
set AT91C_TWI1_RHR  0x4001C030
# ========== Register definition for PDC_US0 peripheral ========== 
set AT91C_US0_RNCR  0x40024114
set AT91C_US0_PTCR  0x40024120
set AT91C_US0_TCR   0x4002410C
set AT91C_US0_RPR   0x40024100
set AT91C_US0_RNPR  0x40024110
set AT91C_US0_TNCR  0x4002411C
set AT91C_US0_PTSR  0x40024124
set AT91C_US0_RCR   0x40024104
set AT91C_US0_TNPR  0x40024118
set AT91C_US0_TPR   0x40024108
# ========== Register definition for US0 peripheral ========== 
set AT91C_US0_MAN   0x40024050
set AT91C_US0_IER   0x40024008
set AT91C_US0_NER   0x40024044
set AT91C_US0_BRGR  0x40024020
set AT91C_US0_VER   0x400240FC
set AT91C_US0_IF    0x4002404C
set AT91C_US0_RHR   0x40024018
set AT91C_US0_CSR   0x40024014
set AT91C_US0_FEATURES 0x400240F8
set AT91C_US0_ADDRSIZE 0x400240EC
set AT91C_US0_IMR   0x40024010
set AT91C_US0_THR   0x4002401C
set AT91C_US0_FIDI  0x40024040
set AT91C_US0_MR    0x40024004
set AT91C_US0_RTOR  0x40024024
set AT91C_US0_IPNAME1 0x400240F0
set AT91C_US0_IDR   0x4002400C
set AT91C_US0_IPNAME2 0x400240F4
set AT91C_US0_CR    0x40024000
set AT91C_US0_TTGR  0x40024028
# ========== Register definition for PDC_US1 peripheral ========== 
set AT91C_US1_TNPR  0x40028118
set AT91C_US1_RPR   0x40028100
set AT91C_US1_TCR   0x4002810C
set AT91C_US1_RCR   0x40028104
set AT91C_US1_TPR   0x40028108
set AT91C_US1_RNPR  0x40028110
set AT91C_US1_TNCR  0x4002811C
set AT91C_US1_PTCR  0x40028120
set AT91C_US1_RNCR  0x40028114
set AT91C_US1_PTSR  0x40028124
# ========== Register definition for US1 peripheral ========== 
set AT91C_US1_ADDRSIZE 0x400280EC
set AT91C_US1_IDR   0x4002800C
set AT91C_US1_FEATURES 0x400280F8
set AT91C_US1_IPNAME2 0x400280F4
set AT91C_US1_MAN   0x40028050
set AT91C_US1_CR    0x40028000
set AT91C_US1_TTGR  0x40028028
set AT91C_US1_IF    0x4002804C
set AT91C_US1_FIDI  0x40028040
set AT91C_US1_THR   0x4002801C
set AT91C_US1_VER   0x400280FC
set AT91C_US1_MR    0x40028004
set AT91C_US1_CSR   0x40028014
set AT91C_US1_IER   0x40028008
set AT91C_US1_NER   0x40028044
set AT91C_US1_RHR   0x40028018
set AT91C_US1_IPNAME1 0x400280F0
set AT91C_US1_IMR   0x40028010
set AT91C_US1_BRGR  0x40028020
set AT91C_US1_RTOR  0x40028024
# ========== Register definition for PDC_SSC0 peripheral ========== 
set AT91C_SSC0_RNCR 0x40004114
set AT91C_SSC0_TPR  0x40004108
set AT91C_SSC0_TCR  0x4000410C
set AT91C_SSC0_PTCR 0x40004120
set AT91C_SSC0_TNPR 0x40004118
set AT91C_SSC0_RPR  0x40004100
set AT91C_SSC0_TNCR 0x4000411C
set AT91C_SSC0_RNPR 0x40004110
set AT91C_SSC0_RCR  0x40004104
set AT91C_SSC0_PTSR 0x40004124
# ========== Register definition for SSC0 peripheral ========== 
set AT91C_SSC0_FEATURES 0x400040F8
set AT91C_SSC0_ADDRSIZE 0x400040F0
set AT91C_SSC0_CR   0x40004000
set AT91C_SSC0_RHR  0x40004020
set AT91C_SSC0_VER  0x400040FC
set AT91C_SSC0_TSHR 0x40004034
set AT91C_SSC0_RFMR 0x40004014
set AT91C_SSC0_IDR  0x40004048
set AT91C_SSC0_TFMR 0x4000401C
set AT91C_SSC0_RSHR 0x40004030
set AT91C_SSC0_TCMR 0x40004018
set AT91C_SSC0_RCMR 0x40004010
set AT91C_SSC0_SR   0x40004040
set AT91C_SSC0_NAME 0x400040F4
set AT91C_SSC0_THR  0x40004024
set AT91C_SSC0_CMR  0x40004004
set AT91C_SSC0_IER  0x40004044
set AT91C_SSC0_IMR  0x4000404C
# ========== Register definition for PDC_PWMC peripheral ========== 
set AT91C_PWMC_TNCR 0x4002011C
set AT91C_PWMC_RCR  0x40020104
set AT91C_PWMC_TCR  0x4002010C
set AT91C_PWMC_RNCR 0x40020114
set AT91C_PWMC_PTSR 0x40020124
set AT91C_PWMC_RNPR 0x40020110
set AT91C_PWMC_TNPR 0x40020118
set AT91C_PWMC_PTCR 0x40020120
set AT91C_PWMC_RPR  0x40020100
set AT91C_PWMC_TPR  0x40020108
# ========== Register definition for PWMC_CH0 peripheral ========== 
set AT91C_PWMC_CH0_CMR 0x40020200
set AT91C_PWMC_CH0_DTUPDR 0x4002021C
set AT91C_PWMC_CH0_CPRDR 0x4002020C
set AT91C_PWMC_CH0_CPRDUPDR 0x40020210
set AT91C_PWMC_CH0_CDTYR 0x40020204
set AT91C_PWMC_CH0_DTR 0x40020218
set AT91C_PWMC_CH0_CDTYUPDR 0x40020208
set AT91C_PWMC_CH0_CCNTR 0x40020214
# ========== Register definition for PWMC_CH1 peripheral ========== 
set AT91C_PWMC_CH1_DTUPDR 0x4002023C
set AT91C_PWMC_CH1_DTR 0x40020238
set AT91C_PWMC_CH1_CDTYUPDR 0x40020228
set AT91C_PWMC_CH1_CDTYR 0x40020224
set AT91C_PWMC_CH1_CCNTR 0x40020234
set AT91C_PWMC_CH1_CPRDR 0x4002022C
set AT91C_PWMC_CH1_CMR 0x40020220
set AT91C_PWMC_CH1_CPRDUPDR 0x40020230
# ========== Register definition for PWMC_CH2 peripheral ========== 
set AT91C_PWMC_CH2_CPRDUPDR 0x40020250
set AT91C_PWMC_CH2_CDTYR 0x40020244
set AT91C_PWMC_CH2_CCNTR 0x40020254
set AT91C_PWMC_CH2_CMR 0x40020240
set AT91C_PWMC_CH2_CDTYUPDR 0x40020248
set AT91C_PWMC_CH2_DTUPDR 0x4002025C
set AT91C_PWMC_CH2_DTR 0x40020258
set AT91C_PWMC_CH2_CPRDR 0x4002024C
# ========== Register definition for PWMC_CH3 peripheral ========== 
set AT91C_PWMC_CH3_CPRDR 0x4002026C
set AT91C_PWMC_CH3_DTUPDR 0x4002027C
set AT91C_PWMC_CH3_DTR 0x40020278
set AT91C_PWMC_CH3_CDTYR 0x40020264
set AT91C_PWMC_CH3_CMR 0x40020260
set AT91C_PWMC_CH3_CCNTR 0x40020274
set AT91C_PWMC_CH3_CPRDUPDR 0x40020270
set AT91C_PWMC_CH3_CDTYUPDR 0x40020268
# ========== Register definition for PWMC peripheral ========== 
set AT91C_PWMC_CMP6M 0x40020198
set AT91C_PWMC_ADDRSIZE 0x400200EC
set AT91C_PWMC_CMP5V 0x40020180
set AT91C_PWMC_FMR  0x4002005C
set AT91C_PWMC_IER2 0x40020034
set AT91C_PWMC_EL5MR 0x40020090
set AT91C_PWMC_CMP0VUPD 0x40020134
set AT91C_PWMC_FPER1 0x4002006C
set AT91C_PWMC_SCUPUPD 0x40020030
set AT91C_PWMC_DIS  0x40020008
set AT91C_PWMC_CMP1M 0x40020148
set AT91C_PWMC_CMP2V 0x40020150
set AT91C_PWMC_WPCR 0x400200E4
set AT91C_PWMC_CMP5MUPD 0x4002018C
set AT91C_PWMC_FPV  0x40020068
set AT91C_PWMC_UPCR 0x40020028
set AT91C_PWMC_CMP4MUPD 0x4002017C
set AT91C_PWMC_EL6MR 0x40020094
set AT91C_PWMC_OS   0x40020048
set AT91C_PWMC_OSSUPD 0x40020054
set AT91C_PWMC_FSR  0x40020060
set AT91C_PWMC_CMP2M 0x40020158
set AT91C_PWMC_EL2MR 0x40020084
set AT91C_PWMC_FPER3 0x40020074
set AT91C_PWMC_CMP4M 0x40020178
set AT91C_PWMC_ISR2 0x40020040
set AT91C_PWMC_CMP6VUPD 0x40020194
set AT91C_PWMC_CMP5VUPD 0x40020184
set AT91C_PWMC_EL7MR 0x40020098
set AT91C_PWMC_OSC  0x40020050
set AT91C_PWMC_CMP3MUPD 0x4002016C
set AT91C_PWMC_CMP2MUPD 0x4002015C
set AT91C_PWMC_CMP0M 0x40020138
set AT91C_PWMC_EL1MR 0x40020080
set AT91C_PWMC_CMP0MUPD 0x4002013C
set AT91C_PWMC_WPSR 0x400200E8
set AT91C_PWMC_CMP1MUPD 0x4002014C
set AT91C_PWMC_IMR2 0x4002003C
set AT91C_PWMC_CMP3V 0x40020160
set AT91C_PWMC_CMP3VUPD 0x40020164
set AT91C_PWMC_CMP3M 0x40020168
set AT91C_PWMC_FPER4 0x40020078
set AT91C_PWMC_OSCUPD 0x40020058
set AT91C_PWMC_CMP0V 0x40020130
set AT91C_PWMC_OOV  0x40020044
set AT91C_PWMC_ENA  0x40020004
set AT91C_PWMC_CMP6MUPD 0x4002019C
set AT91C_PWMC_SYNC 0x40020020
set AT91C_PWMC_IPNAME1 0x400200F0
set AT91C_PWMC_IDR2 0x40020038
set AT91C_PWMC_SR   0x4002000C
set AT91C_PWMC_FPER2 0x40020070
set AT91C_PWMC_EL3MR 0x40020088
set AT91C_PWMC_IMR1 0x40020018
set AT91C_PWMC_EL0MR 0x4002007C
set AT91C_PWMC_STEP 0x400200B0
set AT91C_PWMC_FCR  0x40020064
set AT91C_PWMC_CMP7MUPD 0x400201AC
set AT91C_PWMC_ISR1 0x4002001C
set AT91C_PWMC_CMP4VUPD 0x40020174
set AT91C_PWMC_VER  0x400200FC
set AT91C_PWMC_CMP5M 0x40020188
set AT91C_PWMC_IER1 0x40020010
set AT91C_PWMC_MR   0x40020000
set AT91C_PWMC_OSS  0x4002004C
set AT91C_PWMC_CMP7V 0x400201A0
set AT91C_PWMC_FEATURES 0x400200F8
set AT91C_PWMC_CMP4V 0x40020170
set AT91C_PWMC_CMP7M 0x400201A8
set AT91C_PWMC_EL4MR 0x4002008C
set AT91C_PWMC_CMP2VUPD 0x40020154
set AT91C_PWMC_CMP6V 0x40020190
set AT91C_PWMC_CMP1V 0x40020140
set AT91C_PWMC_IDR1 0x40020014
set AT91C_PWMC_SCUP 0x4002002C
set AT91C_PWMC_CMP1VUPD 0x40020144
set AT91C_PWMC_CMP7VUPD 0x400201A4
set AT91C_PWMC_IPNAME2 0x400200F4
# ========== Register definition for SPI0 peripheral ========== 
set AT91C_SPI0_ADDRSIZE 0x400080EC
set AT91C_SPI0_RDR  0x40008008
set AT91C_SPI0_FEATURES 0x400080F8
set AT91C_SPI0_CR   0x40008000
set AT91C_SPI0_IPNAME1 0x400080F0
set AT91C_SPI0_VER  0x400080FC
set AT91C_SPI0_IDR  0x40008018
set AT91C_SPI0_TDR  0x4000800C
set AT91C_SPI0_MR   0x40008004
set AT91C_SPI0_IER  0x40008014
set AT91C_SPI0_IMR  0x4000801C
set AT91C_SPI0_IPNAME2 0x400080F4
set AT91C_SPI0_CSR  0x40008030
set AT91C_SPI0_SR   0x40008010
# ========== Register definition for UDP peripheral ========== 
set AT91C_UDP_RSTEP 0x40034028
set AT91C_UDP_CSR   0x40034030
set AT91C_UDP_IMR   0x40034018
set AT91C_UDP_FDR   0x40034050
set AT91C_UDP_ISR   0x4003401C
set AT91C_UDP_IPNAME2 0x400340F4
set AT91C_UDP_ICR   0x40034020
set AT91C_UDP_VER   0x400340FC
set AT91C_UDP_IER   0x40034010
set AT91C_UDP_FEATURES 0x400340F8
set AT91C_UDP_IPNAME1 0x400340F0
set AT91C_UDP_GLBSTATE 0x40034004
set AT91C_UDP_ADDRSIZE 0x400340EC
set AT91C_UDP_NUM   0x40034000
set AT91C_UDP_IDR   0x40034014
set AT91C_UDP_TXVC  0x40034074
set AT91C_UDP_FADDR 0x40034008

# *****************************************************************************
#               BASE ADDRESS DEFINITIONS FOR AT91SAM3S4
# *****************************************************************************
set AT91C_BASE_SYS       0x400E0000
set AT91C_BASE_SMC       0x400E0000
set AT91C_BASE_MATRIX    0x400E0200
set AT91C_BASE_CCFG      0x400E0310
set AT91C_BASE_NVIC      0xE000E000
set AT91C_BASE_MPU       0xE000ED90
set AT91C_BASE_CM3       0xE000ED00
set AT91C_BASE_PDC_DBGU0 0x400E0700
set AT91C_BASE_DBGU0     0x400E0600
set AT91C_BASE_PDC_DBGU1 0x400E0900
set AT91C_BASE_DBGU1     0x400E0800
set AT91C_BASE_PIOA      0x400E0E00
set AT91C_BASE_PDC_PIOA  0x400E0F68
set AT91C_BASE_PIOB      0x400E1000
set AT91C_BASE_PIOC      0x400E1200
set AT91C_BASE_PMC       0x400E0400
set AT91C_BASE_CKGR      0x400E041C
set AT91C_BASE_RSTC      0x400E1400
set AT91C_BASE_SUPC      0x400E1410
set AT91C_BASE_RTTC      0x400E1430
set AT91C_BASE_WDTC      0x400E1450
set AT91C_BASE_RTC       0x400E1460
set AT91C_BASE_ADC0      0x40038000
set AT91C_BASE_DAC0      0x4003C000
set AT91C_BASE_ACC0      0x40040000
set AT91C_BASE_HCBDMA    0x40044000
set AT91C_BASE_TC0       0x40010000
set AT91C_BASE_TC1       0x40010040
set AT91C_BASE_TC2       0x40010080
set AT91C_BASE_TC3       0x40014000
set AT91C_BASE_TC4       0x40014040
set AT91C_BASE_TC5       0x40014080
set AT91C_BASE_TCB0      0x40010000
set AT91C_BASE_TCB1      0x40010040
set AT91C_BASE_TCB2      0x40010080
set AT91C_BASE_TCB3      0x40014000
set AT91C_BASE_TCB4      0x40014040
set AT91C_BASE_TCB5      0x40014080
set AT91C_BASE_EFC0      0x400E0A00
set AT91C_BASE_MCI0      0x40000000
set AT91C_BASE_PDC_TWI0  0x40018100
set AT91C_BASE_PDC_TWI1  0x4001C100
set AT91C_BASE_TWI0      0x40018000
set AT91C_BASE_TWI1      0x4001C000
set AT91C_BASE_PDC_US0   0x40024100
set AT91C_BASE_US0       0x40024000
set AT91C_BASE_PDC_US1   0x40028100
set AT91C_BASE_US1       0x40028000
set AT91C_BASE_PDC_SSC0  0x40004100
set AT91C_BASE_SSC0      0x40004000
set AT91C_BASE_PDC_PWMC  0x40020100
set AT91C_BASE_PWMC_CH0  0x40020200
set AT91C_BASE_PWMC_CH1  0x40020220
set AT91C_BASE_PWMC_CH2  0x40020240
set AT91C_BASE_PWMC_CH3  0x40020260
set AT91C_BASE_PWMC      0x40020000
set AT91C_BASE_SPI0      0x40008000
set AT91C_BASE_UDP       0x40034000

# *****************************************************************************
#               PERIPHERAL ID DEFINITIONS FOR AT91SAM3S4
# *****************************************************************************
set AT91C_ID_SUPC    0
set AT91C_ID_RSTC    1
set AT91C_ID_RTC     2
set AT91C_ID_RTT     3
set AT91C_ID_WDG     4
set AT91C_ID_PMC     5
set AT91C_ID_EFC0    6
set AT91C_ID_DBGU0   8
set AT91C_ID_DBGU1   9
set AT91C_ID_HSMC3  10
set AT91C_ID_PIOA   11
set AT91C_ID_PIOB   12
set AT91C_ID_PIOC   13
set AT91C_ID_US0    14
set AT91C_ID_US1    15
set AT91C_ID_MCI0   18
set AT91C_ID_TWI0   19
set AT91C_ID_TWI1   20
set AT91C_ID_SPI0   21
set AT91C_ID_SSC0   22
set AT91C_ID_TC0    23
set AT91C_ID_TC1    24
set AT91C_ID_TC2    25
set AT91C_ID_TC3    26
set AT91C_ID_TC4    27
set AT91C_ID_TC5    28
set AT91C_ID_ADC0   29
set AT91C_ID_DAC0   30
set AT91C_ID_PWMC   31
set AT91C_ID_HCBDMA 32
set AT91C_ID_ACC0   33
set AT91C_ID_UDP    34

# *****************************************************************************
#               PIO DEFINITIONS FOR AT91SAM3S4
# *****************************************************************************
set AT91C_PIO_PA0        [expr 1 <<  0 ]
set AT91C_PA0_PWMH0    $AT91C_PIO_PA0
set AT91C_PA0_TIOA0    $AT91C_PIO_PA0
set AT91C_PA0_A17      $AT91C_PIO_PA0
set AT91C_PIO_PA1        [expr 1 <<  1 ]
set AT91C_PA1_PWMH1    $AT91C_PIO_PA1
set AT91C_PA1_TIOB0    $AT91C_PIO_PA1
set AT91C_PA1_A18      $AT91C_PIO_PA1
set AT91C_PIO_PA10       [expr 1 << 10 ]
set AT91C_PA10_UTXD0    $AT91C_PIO_PA10
set AT91C_PA10_SPI0_NPCS2 $AT91C_PIO_PA10
set AT91C_PIO_PA11       [expr 1 << 11 ]
set AT91C_PA11_SPI0_NPCS0 $AT91C_PIO_PA11
set AT91C_PA11_PWMH0    $AT91C_PIO_PA11
set AT91C_PIO_PA12       [expr 1 << 12 ]
set AT91C_PA12_SPI0_MISO $AT91C_PIO_PA12
set AT91C_PA12_PWMH1    $AT91C_PIO_PA12
set AT91C_PIO_PA13       [expr 1 << 13 ]
set AT91C_PA13_SPI0_MOSI $AT91C_PIO_PA13
set AT91C_PA13_PWMH2    $AT91C_PIO_PA13
set AT91C_PIO_PA14       [expr 1 << 14 ]
set AT91C_PA14_SPI0_SPCK $AT91C_PIO_PA14
set AT91C_PA14_PWMH3    $AT91C_PIO_PA14
set AT91C_PIO_PA15       [expr 1 << 15 ]
set AT91C_PA15_TF       $AT91C_PIO_PA15
set AT91C_PA15_TIOA1    $AT91C_PIO_PA15
set AT91C_PA15_PWML3    $AT91C_PIO_PA15
set AT91C_PIO_PA16       [expr 1 << 16 ]
set AT91C_PA16_TK       $AT91C_PIO_PA16
set AT91C_PA16_TIOB1    $AT91C_PIO_PA16
set AT91C_PA16_PWML2    $AT91C_PIO_PA16
set AT91C_PIO_PA17       [expr 1 << 17 ]
set AT91C_PA17_TD       $AT91C_PIO_PA17
set AT91C_PA17_PCK1     $AT91C_PIO_PA17
set AT91C_PA17_PWMH3    $AT91C_PIO_PA17
set AT91C_PIO_PA18       [expr 1 << 18 ]
set AT91C_PA18_RD       $AT91C_PIO_PA18
set AT91C_PA18_PCK2     $AT91C_PIO_PA18
set AT91C_PA18_A14      $AT91C_PIO_PA18
set AT91C_PIO_PA19       [expr 1 << 19 ]
set AT91C_PA19_RK       $AT91C_PIO_PA19
set AT91C_PA19_PWML0    $AT91C_PIO_PA19
set AT91C_PA19_A15      $AT91C_PIO_PA19
set AT91C_PIO_PA2        [expr 1 <<  2 ]
set AT91C_PA2_PWMH2    $AT91C_PIO_PA2
set AT91C_PA2_SCK0     $AT91C_PIO_PA2
set AT91C_PA2_DATRG    $AT91C_PIO_PA2
set AT91C_PIO_PA20       [expr 1 << 20 ]
set AT91C_PA20_RF       $AT91C_PIO_PA20
set AT91C_PA20_PWML1    $AT91C_PIO_PA20
set AT91C_PA20_A16      $AT91C_PIO_PA20
set AT91C_PIO_PA21       [expr 1 << 21 ]
set AT91C_PA21_RXD1     $AT91C_PIO_PA21
set AT91C_PA21_PCK1     $AT91C_PIO_PA21
set AT91C_PIO_PA22       [expr 1 << 22 ]
set AT91C_PA22_TXD1     $AT91C_PIO_PA22
set AT91C_PA22_SPI0_NPCS3 $AT91C_PIO_PA22
set AT91C_PA22_NCS2     $AT91C_PIO_PA22
set AT91C_PIO_PA23       [expr 1 << 23 ]
set AT91C_PA23_SCK1     $AT91C_PIO_PA23
set AT91C_PA23_PWMH0    $AT91C_PIO_PA23
set AT91C_PA23_A19      $AT91C_PIO_PA23
set AT91C_PIO_PA24       [expr 1 << 24 ]
set AT91C_PA24_RTS1     $AT91C_PIO_PA24
set AT91C_PA24_PWMH1    $AT91C_PIO_PA24
set AT91C_PA24_A20      $AT91C_PIO_PA24
set AT91C_PIO_PA25       [expr 1 << 25 ]
set AT91C_PA25_CTS1     $AT91C_PIO_PA25
set AT91C_PA25_PWMH2    $AT91C_PIO_PA25
set AT91C_PA25_A23      $AT91C_PIO_PA25
set AT91C_PIO_PA26       [expr 1 << 26 ]
set AT91C_PA26_DCD1     $AT91C_PIO_PA26
set AT91C_PA26_TIOA2    $AT91C_PIO_PA26
set AT91C_PA26_MCI0_DA2 $AT91C_PIO_PA26
set AT91C_PIO_PA27       [expr 1 << 27 ]
set AT91C_PA27_DTR1     $AT91C_PIO_PA27
set AT91C_PA27_TIOB2    $AT91C_PIO_PA27
set AT91C_PA27_MCI0_DA3 $AT91C_PIO_PA27
set AT91C_PIO_PA28       [expr 1 << 28 ]
set AT91C_PA28_DSR1     $AT91C_PIO_PA28
set AT91C_PA28_TCLK1    $AT91C_PIO_PA28
set AT91C_PA28_MCI0_CDA $AT91C_PIO_PA28
set AT91C_PIO_PA29       [expr 1 << 29 ]
set AT91C_PA29_RI1      $AT91C_PIO_PA29
set AT91C_PA29_TCLK2    $AT91C_PIO_PA29
set AT91C_PA29_MCI0_CK  $AT91C_PIO_PA29
set AT91C_PIO_PA3        [expr 1 <<  3 ]
set AT91C_PA3_TWD0     $AT91C_PIO_PA3
set AT91C_PA3_SPI0_NPCS3 $AT91C_PIO_PA3
set AT91C_PIO_PA30       [expr 1 << 30 ]
set AT91C_PA30_PWML2    $AT91C_PIO_PA30
set AT91C_PA30_SPI0_NPCS2 $AT91C_PIO_PA30
set AT91C_PA30_MCI0_DA0 $AT91C_PIO_PA30
set AT91C_PIO_PA31       [expr 1 << 31 ]
set AT91C_PA31_SPI0_NPCS1 $AT91C_PIO_PA31
set AT91C_PA31_PCK2     $AT91C_PIO_PA31
set AT91C_PA31_MCI0_DA1 $AT91C_PIO_PA31
set AT91C_PIO_PA4        [expr 1 <<  4 ]
set AT91C_PA4_TWCK0    $AT91C_PIO_PA4
set AT91C_PA4_TCLK0    $AT91C_PIO_PA4
set AT91C_PIO_PA5        [expr 1 <<  5 ]
set AT91C_PA5_RXD0     $AT91C_PIO_PA5
set AT91C_PA5_SPI0_NPCS3 $AT91C_PIO_PA5
set AT91C_PIO_PA6        [expr 1 <<  6 ]
set AT91C_PA6_TXD0     $AT91C_PIO_PA6
set AT91C_PA6_PCK0     $AT91C_PIO_PA6
set AT91C_PIO_PA7        [expr 1 <<  7 ]
set AT91C_PA7_RTS0     $AT91C_PIO_PA7
set AT91C_PA7_PWMH3    $AT91C_PIO_PA7
set AT91C_PIO_PA8        [expr 1 <<  8 ]
set AT91C_PA8_CTS0     $AT91C_PIO_PA8
set AT91C_PA8_ADTRG    $AT91C_PIO_PA8
set AT91C_PIO_PA9        [expr 1 <<  9 ]
set AT91C_PA9_URXD0    $AT91C_PIO_PA9
set AT91C_PA9_SPI0_NPCS1 $AT91C_PIO_PA9
set AT91C_PA9_PWMFI0   $AT91C_PIO_PA9
set AT91C_PIO_PB0        [expr 1 <<  0 ]
set AT91C_PB0_PWMH0    $AT91C_PIO_PB0
set AT91C_PIO_PB1        [expr 1 <<  1 ]
set AT91C_PB1_PWMH1    $AT91C_PIO_PB1
set AT91C_PIO_PB10       [expr 1 << 10 ]
set AT91C_PIO_PB11       [expr 1 << 11 ]
set AT91C_PIO_PB12       [expr 1 << 12 ]
set AT91C_PB12_PWML1    $AT91C_PIO_PB12
set AT91C_PIO_PB13       [expr 1 << 13 ]
set AT91C_PB13_PWML2    $AT91C_PIO_PB13
set AT91C_PB13_PCK0     $AT91C_PIO_PB13
set AT91C_PIO_PB14       [expr 1 << 14 ]
set AT91C_PB14_SPI0_NPCS1 $AT91C_PIO_PB14
set AT91C_PB14_PWMH3    $AT91C_PIO_PB14
set AT91C_PIO_PB2        [expr 1 <<  2 ]
set AT91C_PB2_URXD1    $AT91C_PIO_PB2
set AT91C_PB2_SPI0_NPCS2 $AT91C_PIO_PB2
set AT91C_PIO_PB3        [expr 1 <<  3 ]
set AT91C_PB3_UTXD1    $AT91C_PIO_PB3
set AT91C_PB3_PCK2     $AT91C_PIO_PB3
set AT91C_PIO_PB4        [expr 1 <<  4 ]
set AT91C_PB4_TWD1     $AT91C_PIO_PB4
set AT91C_PB4_PWMH2    $AT91C_PIO_PB4
set AT91C_PIO_PB5        [expr 1 <<  5 ]
set AT91C_PB5_TWCK1    $AT91C_PIO_PB5
set AT91C_PB5_PWML0    $AT91C_PIO_PB5
set AT91C_PIO_PB6        [expr 1 <<  6 ]
set AT91C_PIO_PB7        [expr 1 <<  7 ]
set AT91C_PIO_PB8        [expr 1 <<  8 ]
set AT91C_PIO_PB9        [expr 1 <<  9 ]
set AT91C_PIO_PC0        [expr 1 <<  0 ]
set AT91C_PC0_D0       $AT91C_PIO_PC0
set AT91C_PC0_PWML0    $AT91C_PIO_PC0
set AT91C_PIO_PC1        [expr 1 <<  1 ]
set AT91C_PC1_D1       $AT91C_PIO_PC1
set AT91C_PC1_PWML1    $AT91C_PIO_PC1
set AT91C_PIO_PC10       [expr 1 << 10 ]
set AT91C_PC10_NANDWE   $AT91C_PIO_PC10
set AT91C_PIO_PC11       [expr 1 << 11 ]
set AT91C_PC11_NRD      $AT91C_PIO_PC11
set AT91C_PIO_PC12       [expr 1 << 12 ]
set AT91C_PC12_NCS3     $AT91C_PIO_PC12
set AT91C_PIO_PC13       [expr 1 << 13 ]
set AT91C_PC13_NWAIT    $AT91C_PIO_PC13
set AT91C_PC13_PWML0    $AT91C_PIO_PC13
set AT91C_PIO_PC14       [expr 1 << 14 ]
set AT91C_PC14_NCS0     $AT91C_PIO_PC14
set AT91C_PIO_PC15       [expr 1 << 15 ]
set AT91C_PC15_NCS1     $AT91C_PIO_PC15
set AT91C_PC15_PWML1    $AT91C_PIO_PC15
set AT91C_PIO_PC16       [expr 1 << 16 ]
set AT91C_PC16_A21_NANDALE $AT91C_PIO_PC16
set AT91C_PIO_PC17       [expr 1 << 17 ]
set AT91C_PC17_A22_NANDCLE $AT91C_PIO_PC17
set AT91C_PIO_PC18       [expr 1 << 18 ]
set AT91C_PC18_A0_NBS0  $AT91C_PIO_PC18
set AT91C_PC18_PWMH0    $AT91C_PIO_PC18
set AT91C_PIO_PC19       [expr 1 << 19 ]
set AT91C_PC19_A1       $AT91C_PIO_PC19
set AT91C_PC19_PWMH1    $AT91C_PIO_PC19
set AT91C_PIO_PC2        [expr 1 <<  2 ]
set AT91C_PC2_D2       $AT91C_PIO_PC2
set AT91C_PC2_PWML2    $AT91C_PIO_PC2
set AT91C_PIO_PC20       [expr 1 << 20 ]
set AT91C_PC20_A2       $AT91C_PIO_PC20
set AT91C_PC20_PWMH2    $AT91C_PIO_PC20
set AT91C_PIO_PC21       [expr 1 << 21 ]
set AT91C_PC21_A3       $AT91C_PIO_PC21
set AT91C_PC21_PWMH3    $AT91C_PIO_PC21
set AT91C_PIO_PC22       [expr 1 << 22 ]
set AT91C_PC22_A4       $AT91C_PIO_PC22
set AT91C_PC22_PWML3    $AT91C_PIO_PC22
set AT91C_PIO_PC23       [expr 1 << 23 ]
set AT91C_PC23_A5       $AT91C_PIO_PC23
set AT91C_PC23_TIOA3    $AT91C_PIO_PC23
set AT91C_PIO_PC24       [expr 1 << 24 ]
set AT91C_PC24_A6       $AT91C_PIO_PC24
set AT91C_PC24_TIOB3    $AT91C_PIO_PC24
set AT91C_PIO_PC25       [expr 1 << 25 ]
set AT91C_PC25_A7       $AT91C_PIO_PC25
set AT91C_PC25_TCLK3    $AT91C_PIO_PC25
set AT91C_PIO_PC26       [expr 1 << 26 ]
set AT91C_PC26_A8       $AT91C_PIO_PC26
set AT91C_PC26_TIOA4    $AT91C_PIO_PC26
set AT91C_PIO_PC27       [expr 1 << 27 ]
set AT91C_PC27_A9       $AT91C_PIO_PC27
set AT91C_PC27_TIOB4    $AT91C_PIO_PC27
set AT91C_PIO_PC28       [expr 1 << 28 ]
set AT91C_PC28_A10      $AT91C_PIO_PC28
set AT91C_PC28_TCLK4    $AT91C_PIO_PC28
set AT91C_PIO_PC29       [expr 1 << 29 ]
set AT91C_PC29_A11      $AT91C_PIO_PC29
set AT91C_PC29_TIOA5    $AT91C_PIO_PC29
set AT91C_PIO_PC3        [expr 1 <<  3 ]
set AT91C_PC3_D3       $AT91C_PIO_PC3
set AT91C_PC3_PWML3    $AT91C_PIO_PC3
set AT91C_PIO_PC30       [expr 1 << 30 ]
set AT91C_PC30_A12      $AT91C_PIO_PC30
set AT91C_PC30_TIOB5    $AT91C_PIO_PC30
set AT91C_PIO_PC31       [expr 1 << 31 ]
set AT91C_PC31_A13      $AT91C_PIO_PC31
set AT91C_PC31_TCLK5    $AT91C_PIO_PC31
set AT91C_PIO_PC4        [expr 1 <<  4 ]
set AT91C_PC4_D4       $AT91C_PIO_PC4
set AT91C_PC4_SPI0_NPCS1 $AT91C_PIO_PC4
set AT91C_PIO_PC5        [expr 1 <<  5 ]
set AT91C_PC5_D5       $AT91C_PIO_PC5
set AT91C_PIO_PC6        [expr 1 <<  6 ]
set AT91C_PC6_D6       $AT91C_PIO_PC6
set AT91C_PIO_PC7        [expr 1 <<  7 ]
set AT91C_PC7_D7       $AT91C_PIO_PC7
set AT91C_PIO_PC8        [expr 1 <<  8 ]
set AT91C_PC8_NWR0_NWE $AT91C_PIO_PC8
set AT91C_PIO_PC9        [expr 1 <<  9 ]
set AT91C_PC9_NANDOE   $AT91C_PIO_PC9

# *****************************************************************************
#               MEMORY MAPPING DEFINITIONS FOR AT91SAM3S4
# *****************************************************************************
set AT91C_IRAM 	 0x20000000
set AT91C_IRAM_SIZE	 0x0000C000
set AT91C_IROM 	 0x00800000
set AT91C_IROM_SIZE	 0x00008000
set AT91C_EBI_CS0	 0x60000000
set AT91C_EBI_CS0_SIZE	 0x01000000
set AT91C_EBI_SM0	 0x60000000
set AT91C_EBI_SM0_SIZE	 0x01000000
set AT91C_EBI_CS1	 0x61000000
set AT91C_EBI_CS1_SIZE	 0x01000000
set AT91C_EBI_SM1	 0x61000000
set AT91C_EBI_SM1_SIZE	 0x01000000
set AT91C_EBI_CS2	 0x62000000
set AT91C_EBI_CS2_SIZE	 0x01000000
set AT91C_EBI_SM2	 0x62000000
set AT91C_EBI_SM2_SIZE	 0x01000000
set AT91C_EBI_CS3	 0x63000000
set AT91C_EBI_CS3_SIZE	 0x01000000
set AT91C_EBI_SM3	 0x63000000
set AT91C_EBI_SM3_SIZE	 0x01000000
set AT91C_EBI_CS4	 0x64000000
set AT91C_EBI_CS4_SIZE	 0x10000000
set AT91C_EBI_CF0	 0x64000000
set AT91C_EBI_CF0_SIZE	 0x10000000
set AT91C_EBI_CS5	 0x65000000
set AT91C_EBI_CS5_SIZE	 0x10000000
set AT91C_EBI_CF1	 0x65000000
set AT91C_EBI_CF1_SIZE	 0x10000000
set AT91C_EBI_SDRAM	 0x66000000
set AT91C_EBI_SDRAM_SIZE	 0x10000000
set AT91C_EBI_SDRAM_16BIT	 0x67000000
set AT91C_EBI_SDRAM_16BIT_SIZE	 0x02000000
set AT91C_EBI_SDRAM_32BIT	 0x68000000
set AT91C_EBI_SDRAM_32BIT_SIZE	 0x04000000


# *****************************************************************************
#               ATTRIBUTES DEFINITIONS FOR AT91SAM3S4
# *****************************************************************************
array set AT91SAM3S4_att {
	DBGU 	{ LP 	DBGU0_att 	DBGU1_att }
	MCI 	{ LP 	MCI0_att }
	PMC 	{ LP 	PMC_att }
	SMC 	{ LP 	SMC_att }
	RSTC 	{ LP 	RSTC_att }
	EFC 	{ LP 	EFC0_att }
	CCFG 	{ LP 	CCFG_att }
	SSC 	{ LP 	SSC0_att }
	WDTC 	{ LP 	WDTC_att }
	ACC 	{ LP 	ACC0_att }
	NVIC 	{ LP 	NVIC_att }
	SPI 	{ LP 	SPI0_att }
	USART 	{ LP 	US0_att 	US1_att }
	HCBDMA 	{ LP 	HCBDMA_att }
	TCB 	{ LP 	TCB0_att 	TCB1_att 	TCB2_att 	TCB3_att 	TCB4_att 	TCB5_att }
	CKGR 	{ LP 	CKGR_att }
	DAC 	{ LP 	DAC0_att }
	MPU 	{ LP 	MPU_att }
	CM3 	{ LP 	CM3_att }
	SUPC 	{ LP 	SUPC_att }
	TWI 	{ LP 	TWI0_att 	TWI1_att }
	PWMC_CH 	{ LP 	PWMC_CH0_att 	PWMC_CH1_att 	PWMC_CH2_att 	PWMC_CH3_att }
	HMATRIX2 	{ LP 	MATRIX_att }
	ADC 	{ LP 	ADC0_att }
	RTTC 	{ LP 	RTTC_att }
	UDP 	{ LP 	UDP_att }
	RTC 	{ LP 	RTC_att }
	TC 	{ LP 	TC0_att 	TC1_att 	TC2_att 	TC3_att 	TC4_att 	TC5_att }
	SYS 	{ LP 	SYS_att }
	PIO 	{ LP 	PIOA_att 	PIOB_att 	PIOC_att }
	PWMC 	{ LP 	PWMC_att }
	PDC 	{ LP 	PDC_DBGU0_att 	PDC_DBGU1_att 	PDC_PIOA_att 	PDC_TWI0_att 	PDC_TWI1_att 	PDC_US0_att 	PDC_US1_att 	PDC_SSC0_att 	PDC_PWMC_att }

}
# ========== Peripheral attributes for DBGU peripheral ========== 
array set DBGU0_att {
	CR 	{ R AT91C_DBGU0_CR 	WO }
	IDR 	{ R AT91C_DBGU0_IDR 	WO }
	CIDR 	{ R AT91C_DBGU0_CIDR 	RO }
	IPNAME2 	{ R AT91C_DBGU0_IPNAME2 	RW }
	FEATURES 	{ R AT91C_DBGU0_FEATURES 	RW }
	FNTR 	{ R AT91C_DBGU0_FNTR 	RW }
	RHR 	{ R AT91C_DBGU0_RHR 	RO }
	THR 	{ R AT91C_DBGU0_THR 	WO }
	ADDRSIZE 	{ R AT91C_DBGU0_ADDRSIZE 	RW }
	MR 	{ R AT91C_DBGU0_MR 	RW }
	IER 	{ R AT91C_DBGU0_IER 	WO }
	BRGR 	{ R AT91C_DBGU0_BRGR 	RW }
	CSR 	{ R AT91C_DBGU0_CSR 	RO }
	VER 	{ R AT91C_DBGU0_VER 	RW }
	IMR 	{ R AT91C_DBGU0_IMR 	RO }
	IPNAME1 	{ R AT91C_DBGU0_IPNAME1 	RW }
	EXID 	{ R AT91C_DBGU0_EXID 	RO }
	listeReg 	{ CR IDR CIDR IPNAME2 FEATURES FNTR RHR THR ADDRSIZE MR IER BRGR CSR VER IMR IPNAME1 EXID  }

}
array set DBGU1_att {
	RHR 	{ R AT91C_DBGU1_RHR 	RO }
	IPNAME1 	{ R AT91C_DBGU1_IPNAME1 	RW }
	CIDR 	{ R AT91C_DBGU1_CIDR 	RO }
	CR 	{ R AT91C_DBGU1_CR 	WO }
	VER 	{ R AT91C_DBGU1_VER 	RW }
	IPNAME2 	{ R AT91C_DBGU1_IPNAME2 	RW }
	BRGR 	{ R AT91C_DBGU1_BRGR 	RW }
	FNTR 	{ R AT91C_DBGU1_FNTR 	RW }
	MR 	{ R AT91C_DBGU1_MR 	RW }
	ADDRSIZE 	{ R AT91C_DBGU1_ADDRSIZE 	RW }
	CSR 	{ R AT91C_DBGU1_CSR 	RO }
	IMR 	{ R AT91C_DBGU1_IMR 	RO }
	EXID 	{ R AT91C_DBGU1_EXID 	RO }
	IDR 	{ R AT91C_DBGU1_IDR 	WO }
	FEATURES 	{ R AT91C_DBGU1_FEATURES 	RW }
	IER 	{ R AT91C_DBGU1_IER 	WO }
	THR 	{ R AT91C_DBGU1_THR 	WO }
	listeReg 	{ RHR IPNAME1 CIDR CR VER IPNAME2 BRGR FNTR MR ADDRSIZE CSR IMR EXID IDR FEATURES IER THR  }

}

# ========== Peripheral attributes for MCI peripheral ========== 
array set MCI0_att {
	DMA 	{ R AT91C_MCI0_DMA 	RW }
	SDCR 	{ R AT91C_MCI0_SDCR 	RW }
	IPNAME1 	{ R AT91C_MCI0_IPNAME1 	RW }
	CSTOR 	{ R AT91C_MCI0_CSTOR 	RW }
	RDR 	{ R AT91C_MCI0_RDR 	RO }
	CMDR 	{ R AT91C_MCI0_CMDR 	WO }
	IDR 	{ R AT91C_MCI0_IDR 	WO }
	ADDRSIZE 	{ R AT91C_MCI0_ADDRSIZE 	RW }
	WPCR 	{ R AT91C_MCI0_WPCR 	RW }
	RSPR 	{ R AT91C_MCI0_RSPR 	RO  4 }
	IPNAME2 	{ R AT91C_MCI0_IPNAME2 	RW }
	CR 	{ R AT91C_MCI0_CR 	WO }
	IMR 	{ R AT91C_MCI0_IMR 	RO }
	WPSR 	{ R AT91C_MCI0_WPSR 	R0 }
	DTOR 	{ R AT91C_MCI0_DTOR 	RW }
	MR 	{ R AT91C_MCI0_MR 	RW }
	SR 	{ R AT91C_MCI0_SR 	RO }
	IER 	{ R AT91C_MCI0_IER 	WO }
	VER 	{ R AT91C_MCI0_VER 	RW }
	FEATURES 	{ R AT91C_MCI0_FEATURES 	RW }
	BLKR 	{ R AT91C_MCI0_BLKR 	RW }
	ARGR 	{ R AT91C_MCI0_ARGR 	RW }
	FIFO 	{ R AT91C_MCI0_FIFO 	R0 }
	TDR 	{ R AT91C_MCI0_TDR 	RO }
	CFG 	{ R AT91C_MCI0_CFG 	RW }
	listeReg 	{ DMA SDCR IPNAME1 CSTOR RDR CMDR IDR ADDRSIZE WPCR RSPR IPNAME2 CR IMR WPSR DTOR MR SR IER VER FEATURES BLKR ARGR FIFO TDR CFG  }

}

# ========== Peripheral attributes for PMC peripheral ========== 
array set PMC_att {
	PLLAR 	{ R AT91C_PMC_PLLAR 	RW }
	UCKR 	{ R AT91C_PMC_UCKR 	RW }
	FSMR 	{ R AT91C_PMC_FSMR 	RW }
	MCKR 	{ R AT91C_PMC_MCKR 	RW }
	SCER 	{ R AT91C_PMC_SCER 	WO }
	PCSR 	{ R AT91C_PMC_PCSR 	RO }
	MCFR 	{ R AT91C_PMC_MCFR 	RO }
	PCER1 	{ R AT91C_PMC_PCER1 	WO }
	FOCR 	{ R AT91C_PMC_FOCR 	WO }
	PCSR1 	{ R AT91C_PMC_PCSR1 	RO }
	FSPR 	{ R AT91C_PMC_FSPR 	RW }
	SCSR 	{ R AT91C_PMC_SCSR 	RO }
	IDR 	{ R AT91C_PMC_IDR 	WO }
	UDPR 	{ R AT91C_PMC_UDPR 	RW }
	PCDR1 	{ R AT91C_PMC_PCDR1 	WO }
	VER 	{ R AT91C_PMC_VER 	RO }
	IMR 	{ R AT91C_PMC_IMR 	RO }
	IPNAME2 	{ R AT91C_PMC_IPNAME2 	RW }
	SCDR 	{ R AT91C_PMC_SCDR 	WO }
	PCKR 	{ R AT91C_PMC_PCKR 	RW  8 }
	ADDRSIZE 	{ R AT91C_PMC_ADDRSIZE 	RW }
	PCDR 	{ R AT91C_PMC_PCDR 	WO }
	MOR 	{ R AT91C_PMC_MOR 	RW }
	SR 	{ R AT91C_PMC_SR 	RO }
	IER 	{ R AT91C_PMC_IER 	WO }
	PLLBR 	{ R AT91C_PMC_PLLBR 	RW }
	IPNAME1 	{ R AT91C_PMC_IPNAME1 	RW }
	PCER 	{ R AT91C_PMC_PCER 	WO }
	FEATURES 	{ R AT91C_PMC_FEATURES 	RW }
	PCR 	{ R AT91C_PMC_PCR 	RW }
	listeReg 	{ PLLAR UCKR FSMR MCKR SCER PCSR MCFR PCER1 FOCR PCSR1 FSPR SCSR IDR UDPR PCDR1 VER IMR IPNAME2 SCDR PCKR ADDRSIZE PCDR MOR SR IER PLLBR IPNAME1 PCER FEATURES PCR  }

}

# ========== Peripheral attributes for SMC peripheral ========== 
array set SMC_att {
	DELAY2 	{ R AT91C_SMC_DELAY2 	WO }
	CYCLE4 	{ R AT91C_SMC_CYCLE4 	RW }
	CTRL5 	{ R AT91C_SMC_CTRL5 	RW }
	IPNAME2 	{ R AT91C_SMC_IPNAME2 	RW }
	DELAY5 	{ R AT91C_SMC_DELAY5 	WO }
	DELAY4 	{ R AT91C_SMC_DELAY4 	WO }
	CYCLE0 	{ R AT91C_SMC_CYCLE0 	RW }
	PULSE1 	{ R AT91C_SMC_PULSE1 	RW }
	DELAY6 	{ R AT91C_SMC_DELAY6 	WO }
	FEATURES 	{ R AT91C_SMC_FEATURES 	RW }
	DELAY3 	{ R AT91C_SMC_DELAY3 	WO }
	CTRL1 	{ R AT91C_SMC_CTRL1 	RW }
	PULSE7 	{ R AT91C_SMC_PULSE7 	RW }
	CTRL7 	{ R AT91C_SMC_CTRL7 	RW }
	VER 	{ R AT91C_SMC_VER 	RO }
	SETUP5 	{ R AT91C_SMC_SETUP5 	RW }
	CYCLE3 	{ R AT91C_SMC_CYCLE3 	RW }
	SETUP3 	{ R AT91C_SMC_SETUP3 	RW }
	DELAY1 	{ R AT91C_SMC_DELAY1 	WO }
	ADDRSIZE 	{ R AT91C_SMC_ADDRSIZE 	RW }
	PULSE3 	{ R AT91C_SMC_PULSE3 	RW }
	PULSE5 	{ R AT91C_SMC_PULSE5 	RW }
	PULSE4 	{ R AT91C_SMC_PULSE4 	RW }
	SETUP2 	{ R AT91C_SMC_SETUP2 	RW }
	DELAY8 	{ R AT91C_SMC_DELAY8 	WO }
	CYCLE7 	{ R AT91C_SMC_CYCLE7 	RW }
	CTRL0 	{ R AT91C_SMC_CTRL0 	RW }
	CYCLE2 	{ R AT91C_SMC_CYCLE2 	RW }
	IPNAME1 	{ R AT91C_SMC_IPNAME1 	RW }
	SETUP1 	{ R AT91C_SMC_SETUP1 	RW }
	CTRL2 	{ R AT91C_SMC_CTRL2 	RW }
	CTRL4 	{ R AT91C_SMC_CTRL4 	RW }
	SETUP6 	{ R AT91C_SMC_SETUP6 	RW }
	CYCLE5 	{ R AT91C_SMC_CYCLE5 	RW }
	CTRL6 	{ R AT91C_SMC_CTRL6 	RW }
	SETUP4 	{ R AT91C_SMC_SETUP4 	RW }
	PULSE2 	{ R AT91C_SMC_PULSE2 	RW }
	DELAY7 	{ R AT91C_SMC_DELAY7 	WO }
	SETUP7 	{ R AT91C_SMC_SETUP7 	RW }
	CYCLE1 	{ R AT91C_SMC_CYCLE1 	RW }
	CTRL3 	{ R AT91C_SMC_CTRL3 	RW }
	SETUP0 	{ R AT91C_SMC_SETUP0 	RW }
	PULSE0 	{ R AT91C_SMC_PULSE0 	RW }
	PULSE6 	{ R AT91C_SMC_PULSE6 	RW }
	CYCLE6 	{ R AT91C_SMC_CYCLE6 	RW }
	listeReg 	{ DELAY2 CYCLE4 CTRL5 IPNAME2 DELAY5 DELAY4 CYCLE0 PULSE1 DELAY6 FEATURES DELAY3 CTRL1 PULSE7 CTRL7 VER SETUP5 CYCLE3 SETUP3 DELAY1 ADDRSIZE PULSE3 PULSE5 PULSE4 SETUP2 DELAY8 CYCLE7 CTRL0 CYCLE2 IPNAME1 SETUP1 CTRL2 CTRL4 SETUP6 CYCLE5 CTRL6 SETUP4 PULSE2 DELAY7 SETUP7 CYCLE1 CTRL3 SETUP0 PULSE0 PULSE6 CYCLE6  }

}

# ========== Peripheral attributes for RSTC peripheral ========== 
array set RSTC_att {
	RSR 	{ R AT91C_RSTC_RSR 	RO }
	RCR 	{ R AT91C_RSTC_RCR 	WO }
	RMR 	{ R AT91C_RSTC_RMR 	RW }
	VER 	{ R AT91C_RSTC_VER 	RW }
	listeReg 	{ RSR RCR RMR VER  }

}

# ========== Peripheral attributes for EFC peripheral ========== 
array set EFC0_att {
	FMR 	{ R AT91C_EFC0_FMR 	RW }
	FVR 	{ R AT91C_EFC0_FVR 	RO }
	FSR 	{ R AT91C_EFC0_FSR 	RO }
	FCR 	{ R AT91C_EFC0_FCR 	WO }
	FRR 	{ R AT91C_EFC0_FRR 	RO }
	listeReg 	{ FMR FVR FSR FCR FRR  }

}

# ========== Peripheral attributes for CCFG peripheral ========== 
array set CCFG_att {
	FLASH0 	{ R AT91C_CCFG_FLASH0 	RW }
	RAM0 	{ R AT91C_CCFG_RAM0 	RW }
	ROM 	{ R AT91C_CCFG_ROM 	RW }
	EBICSA 	{ R AT91C_CCFG_EBICSA 	RW }
	BRIDGE 	{ R AT91C_CCFG_BRIDGE 	RW }
	listeReg 	{ FLASH0 RAM0 ROM EBICSA BRIDGE  }

}

# ========== Peripheral attributes for SSC peripheral ========== 
array set SSC0_att {
	FEATURES 	{ R AT91C_SSC0_FEATURES 	RW }
	ADDRSIZE 	{ R AT91C_SSC0_ADDRSIZE 	RW }
	CR 	{ R AT91C_SSC0_CR 	WO }
	RHR 	{ R AT91C_SSC0_RHR 	RO }
	VER 	{ R AT91C_SSC0_VER 	RO }
	TSHR 	{ R AT91C_SSC0_TSHR 	RW }
	RFMR 	{ R AT91C_SSC0_RFMR 	RW }
	IDR 	{ R AT91C_SSC0_IDR 	WO }
	TFMR 	{ R AT91C_SSC0_TFMR 	RW }
	RSHR 	{ R AT91C_SSC0_RSHR 	RO }
	TCMR 	{ R AT91C_SSC0_TCMR 	RW }
	RCMR 	{ R AT91C_SSC0_RCMR 	RW }
	SR 	{ R AT91C_SSC0_SR 	RO }
	NAME 	{ R AT91C_SSC0_NAME 	RW }
	THR 	{ R AT91C_SSC0_THR 	WO }
	CMR 	{ R AT91C_SSC0_CMR 	RW }
	IER 	{ R AT91C_SSC0_IER 	WO }
	IMR 	{ R AT91C_SSC0_IMR 	RO }
	listeReg 	{ FEATURES ADDRSIZE CR RHR VER TSHR RFMR IDR TFMR RSHR TCMR RCMR SR NAME THR CMR IER IMR  }

}

# ========== Peripheral attributes for WDTC peripheral ========== 
array set WDTC_att {
	WDCR 	{ R AT91C_WDTC_WDCR 	WO }
	WDMR 	{ R AT91C_WDTC_WDMR 	RW }
	WDSR 	{ R AT91C_WDTC_WDSR 	RO }
	listeReg 	{ WDCR WDMR WDSR  }

}

# ========== Peripheral attributes for ACC peripheral ========== 
array set ACC0_att {
	IPNAME1 	{ R AT91C_ACC0_IPNAME1 	RW }
	MR 	{ R AT91C_ACC0_MR 	RW }
	FEATURES 	{ R AT91C_ACC0_FEATURES 	RW }
	IMR 	{ R AT91C_ACC0_IMR 	RO }
	ACR 	{ R AT91C_ACC0_ACR 	RW }
	ADDRSIZE 	{ R AT91C_ACC0_ADDRSIZE 	RW }
	IER 	{ R AT91C_ACC0_IER 	WO }
	ISR 	{ R AT91C_ACC0_ISR 	RO }
	IDR 	{ R AT91C_ACC0_IDR 	WO }
	MODE 	{ R AT91C_ACC0_MODE 	RW }
	VER 	{ R AT91C_ACC0_VER 	RO }
	CR 	{ R AT91C_ACC0_CR 	WO }
	IPNAME2 	{ R AT91C_ACC0_IPNAME2 	RW }
	STATUS 	{ R AT91C_ACC0_STATUS 	RO }
	listeReg 	{ IPNAME1 MR FEATURES IMR ACR ADDRSIZE IER ISR IDR MODE VER CR IPNAME2 STATUS  }

}

# ========== Peripheral attributes for NVIC peripheral ========== 
array set NVIC_att {
	MMAR 	{ R AT91C_NVIC_MMAR 	RO }
	STIR 	{ R AT91C_NVIC_STIR 	RO }
	MMFR2 	{ R AT91C_NVIC_MMFR2 	RO }
	CPUID 	{ R AT91C_NVIC_CPUID 	RO }
	DFSR 	{ R AT91C_NVIC_DFSR 	RO }
	HAND4PR 	{ R AT91C_NVIC_HAND4PR 	RO }
	HFSR 	{ R AT91C_NVIC_HFSR 	RO }
	PID6 	{ R AT91C_NVIC_PID6 	RO }
	PFR0 	{ R AT91C_NVIC_PFR0 	RO }
	VTOFFR 	{ R AT91C_NVIC_VTOFFR 	RO }
	ISPR 	{ R AT91C_NVIC_ISPR 	RO  8 }
	PID0 	{ R AT91C_NVIC_PID0 	RO }
	PID7 	{ R AT91C_NVIC_PID7 	RO }
	STICKRVR 	{ R AT91C_NVIC_STICKRVR 	RW }
	PID2 	{ R AT91C_NVIC_PID2 	RO }
	ISAR0 	{ R AT91C_NVIC_ISAR0 	RO }
	SCR 	{ R AT91C_NVIC_SCR 	RO }
	PID4 	{ R AT91C_NVIC_PID4 	RO }
	ISAR2 	{ R AT91C_NVIC_ISAR2 	RO }
	ISER 	{ R AT91C_NVIC_ISER 	RW  8 }
	IPR 	{ R AT91C_NVIC_IPR 	RO 60 }
	AIRCR 	{ R AT91C_NVIC_AIRCR 	RO }
	CID2 	{ R AT91C_NVIC_CID2 	RO }
	ICPR 	{ R AT91C_NVIC_ICPR 	RO  8 }
	CID3 	{ R AT91C_NVIC_CID3 	RO }
	CFSR 	{ R AT91C_NVIC_CFSR 	RO }
	AFR0 	{ R AT91C_NVIC_AFR0 	RO }
	ICSR 	{ R AT91C_NVIC_ICSR 	RO }
	CCR 	{ R AT91C_NVIC_CCR 	RO }
	CID0 	{ R AT91C_NVIC_CID0 	RO }
	ISAR1 	{ R AT91C_NVIC_ISAR1 	RO }
	STICKCVR 	{ R AT91C_NVIC_STICKCVR 	RW }
	STICKCSR 	{ R AT91C_NVIC_STICKCSR 	RW }
	CID1 	{ R AT91C_NVIC_CID1 	RO }
	DFR0 	{ R AT91C_NVIC_DFR0 	RO }
	MMFR3 	{ R AT91C_NVIC_MMFR3 	RO }
	MMFR0 	{ R AT91C_NVIC_MMFR0 	RO }
	STICKCALVR 	{ R AT91C_NVIC_STICKCALVR 	RO }
	PID1 	{ R AT91C_NVIC_PID1 	RO }
	HAND12PR 	{ R AT91C_NVIC_HAND12PR 	RO }
	MMFR1 	{ R AT91C_NVIC_MMFR1 	RO }
	AFSR 	{ R AT91C_NVIC_AFSR 	RO }
	HANDCSR 	{ R AT91C_NVIC_HANDCSR 	RO }
	ISAR4 	{ R AT91C_NVIC_ISAR4 	RO }
	ABR 	{ R AT91C_NVIC_ABR 	RO  8 }
	PFR1 	{ R AT91C_NVIC_PFR1 	RO }
	PID5 	{ R AT91C_NVIC_PID5 	RO }
	ICTR 	{ R AT91C_NVIC_ICTR 	RO }
	ICER 	{ R AT91C_NVIC_ICER 	RW  8 }
	PID3 	{ R AT91C_NVIC_PID3 	RO }
	ISAR3 	{ R AT91C_NVIC_ISAR3 	RO }
	HAND8PR 	{ R AT91C_NVIC_HAND8PR 	RO }
	BFAR 	{ R AT91C_NVIC_BFAR 	RO }
	listeReg 	{ MMAR STIR MMFR2 CPUID DFSR HAND4PR HFSR PID6 PFR0 VTOFFR ISPR PID0 PID7 STICKRVR PID2 ISAR0 SCR PID4 ISAR2 ISER IPR AIRCR CID2 ICPR CID3 CFSR AFR0 ICSR CCR CID0 ISAR1 STICKCVR STICKCSR CID1 DFR0 MMFR3 MMFR0 STICKCALVR PID1 HAND12PR MMFR1 AFSR HANDCSR ISAR4 ABR PFR1 PID5 ICTR ICER PID3 ISAR3 HAND8PR BFAR  }

}

# ========== Peripheral attributes for SPI peripheral ========== 
array set SPI0_att {
	ADDRSIZE 	{ R AT91C_SPI0_ADDRSIZE 	RW }
	RDR 	{ R AT91C_SPI0_RDR 	RO }
	FEATURES 	{ R AT91C_SPI0_FEATURES 	RW }
	CR 	{ R AT91C_SPI0_CR 	RO }
	IPNAME1 	{ R AT91C_SPI0_IPNAME1 	RW }
	VER 	{ R AT91C_SPI0_VER 	RW }
	IDR 	{ R AT91C_SPI0_IDR 	WO }
	TDR 	{ R AT91C_SPI0_TDR 	WO }
	MR 	{ R AT91C_SPI0_MR 	RW }
	IER 	{ R AT91C_SPI0_IER 	WO }
	IMR 	{ R AT91C_SPI0_IMR 	RO }
	IPNAME2 	{ R AT91C_SPI0_IPNAME2 	RW }
	CSR 	{ R AT91C_SPI0_CSR 	RW  4 }
	SR 	{ R AT91C_SPI0_SR 	RO }
	listeReg 	{ ADDRSIZE RDR FEATURES CR IPNAME1 VER IDR TDR MR IER IMR IPNAME2 CSR SR  }

}

# ========== Peripheral attributes for USART peripheral ========== 
array set US0_att {
	MAN 	{ R AT91C_US0_MAN 	RW }
	IER 	{ R AT91C_US0_IER 	WO }
	NER 	{ R AT91C_US0_NER 	RO }
	BRGR 	{ R AT91C_US0_BRGR 	RW }
	VER 	{ R AT91C_US0_VER 	RW }
	IF 	{ R AT91C_US0_IF 	RW }
	RHR 	{ R AT91C_US0_RHR 	RO }
	CSR 	{ R AT91C_US0_CSR 	RO }
	FEATURES 	{ R AT91C_US0_FEATURES 	RW }
	ADDRSIZE 	{ R AT91C_US0_ADDRSIZE 	RW }
	IMR 	{ R AT91C_US0_IMR 	RO }
	THR 	{ R AT91C_US0_THR 	WO }
	FIDI 	{ R AT91C_US0_FIDI 	RW }
	MR 	{ R AT91C_US0_MR 	RW }
	RTOR 	{ R AT91C_US0_RTOR 	RW }
	IPNAME1 	{ R AT91C_US0_IPNAME1 	RW }
	IDR 	{ R AT91C_US0_IDR 	WO }
	IPNAME2 	{ R AT91C_US0_IPNAME2 	RW }
	CR 	{ R AT91C_US0_CR 	WO }
	TTGR 	{ R AT91C_US0_TTGR 	RW }
	listeReg 	{ MAN IER NER BRGR VER IF RHR CSR FEATURES ADDRSIZE IMR THR FIDI MR RTOR IPNAME1 IDR IPNAME2 CR TTGR  }

}
array set US1_att {
	ADDRSIZE 	{ R AT91C_US1_ADDRSIZE 	RW }
	IDR 	{ R AT91C_US1_IDR 	WO }
	FEATURES 	{ R AT91C_US1_FEATURES 	RW }
	IPNAME2 	{ R AT91C_US1_IPNAME2 	RW }
	MAN 	{ R AT91C_US1_MAN 	RW }
	CR 	{ R AT91C_US1_CR 	WO }
	TTGR 	{ R AT91C_US1_TTGR 	RW }
	IF 	{ R AT91C_US1_IF 	RW }
	FIDI 	{ R AT91C_US1_FIDI 	RW }
	THR 	{ R AT91C_US1_THR 	WO }
	VER 	{ R AT91C_US1_VER 	RW }
	MR 	{ R AT91C_US1_MR 	RW }
	CSR 	{ R AT91C_US1_CSR 	RO }
	IER 	{ R AT91C_US1_IER 	WO }
	NER 	{ R AT91C_US1_NER 	RO }
	RHR 	{ R AT91C_US1_RHR 	RO }
	IPNAME1 	{ R AT91C_US1_IPNAME1 	RW }
	IMR 	{ R AT91C_US1_IMR 	RO }
	BRGR 	{ R AT91C_US1_BRGR 	RW }
	RTOR 	{ R AT91C_US1_RTOR 	RW }
	listeReg 	{ ADDRSIZE IDR FEATURES IPNAME2 MAN CR TTGR IF FIDI THR VER MR CSR IER NER RHR IPNAME1 IMR BRGR RTOR  }

}

# ========== Peripheral attributes for HCBDMA peripheral ========== 
array set HCBDMA_att {
	CBIMR 	{ R AT91C_HCBDMA_CBIMR 	RO }
	CBCRCCR 	{ R AT91C_HCBDMA_CBCRCCR 	WO }
	CBSR 	{ R AT91C_HCBDMA_CBSR 	RO }
	CBCRCISR 	{ R AT91C_HCBDMA_CBCRCISR 	RO }
	CBCRCSR 	{ R AT91C_HCBDMA_CBCRCSR 	RO }
	CBIDR 	{ R AT91C_HCBDMA_CBIDR 	WO }
	CBCRCIDR 	{ R AT91C_HCBDMA_CBCRCIDR 	WO }
	CBDLIER 	{ R AT91C_HCBDMA_CBDLIER 	WO }
	CBEN 	{ R AT91C_HCBDMA_CBEN 	WO }
	FEATURES 	{ R AT91C_HCBDMA_FEATURES 	RW }
	CBDSCR 	{ R AT91C_HCBDMA_CBDSCR 	RW }
	ADDRSIZE 	{ R AT91C_HCBDMA_ADDRSIZE 	RW }
	CBDLISR 	{ R AT91C_HCBDMA_CBDLISR 	RO }
	CBDLIDR 	{ R AT91C_HCBDMA_CBDLIDR 	WO }
	CBCRCIMR 	{ R AT91C_HCBDMA_CBCRCIMR 	RO }
	VER 	{ R AT91C_HCBDMA_VER 	RO }
	CBCRCIER 	{ R AT91C_HCBDMA_CBCRCIER 	WO }
	IPNAME2 	{ R AT91C_HCBDMA_IPNAME2 	RW }
	CBIER 	{ R AT91C_HCBDMA_CBIER 	WO }
	CBISR 	{ R AT91C_HCBDMA_CBISR 	RO }
	IPNAME1 	{ R AT91C_HCBDMA_IPNAME1 	RW }
	CBDIS 	{ R AT91C_HCBDMA_CBDIS 	WO }
	CBNXTEN 	{ R AT91C_HCBDMA_CBNXTEN 	RW }
	CBDLIMR 	{ R AT91C_HCBDMA_CBDLIMR 	RO }
	CBCRCMR 	{ R AT91C_HCBDMA_CBCRCMR 	RW }
	listeReg 	{ CBIMR CBCRCCR CBSR CBCRCISR CBCRCSR CBIDR CBCRCIDR CBDLIER CBEN FEATURES CBDSCR ADDRSIZE CBDLISR CBDLIDR CBCRCIMR VER CBCRCIER IPNAME2 CBIER CBISR IPNAME1 CBDIS CBNXTEN CBDLIMR CBCRCMR  }

}

# ========== Peripheral attributes for TCB peripheral ========== 
array set TCB0_att {
	BCR 	{ R AT91C_TCB0_BCR 	WO }
	VER 	{ R AT91C_TCB0_VER 	RO }
	ADDRSIZE 	{ R AT91C_TCB0_ADDRSIZE 	RW }
	FEATURES 	{ R AT91C_TCB0_FEATURES 	RW }
	IPNAME2 	{ R AT91C_TCB0_IPNAME2 	RW }
	BMR 	{ R AT91C_TCB0_BMR 	RW }
	IPNAME1 	{ R AT91C_TCB0_IPNAME1 	RW }
	listeReg 	{ BCR VER ADDRSIZE FEATURES IPNAME2 BMR IPNAME1  }

}
array set TCB1_att {
	IPNAME1 	{ R AT91C_TCB1_IPNAME1 	RW }
	IPNAME2 	{ R AT91C_TCB1_IPNAME2 	RW }
	BCR 	{ R AT91C_TCB1_BCR 	WO }
	VER 	{ R AT91C_TCB1_VER 	RO }
	FEATURES 	{ R AT91C_TCB1_FEATURES 	RW }
	ADDRSIZE 	{ R AT91C_TCB1_ADDRSIZE 	RW }
	BMR 	{ R AT91C_TCB1_BMR 	RW }
	listeReg 	{ IPNAME1 IPNAME2 BCR VER FEATURES ADDRSIZE BMR  }

}
array set TCB2_att {
	VER 	{ R AT91C_TCB2_VER 	RO }
	ADDRSIZE 	{ R AT91C_TCB2_ADDRSIZE 	RW }
	FEATURES 	{ R AT91C_TCB2_FEATURES 	RW }
	BCR 	{ R AT91C_TCB2_BCR 	WO }
	IPNAME2 	{ R AT91C_TCB2_IPNAME2 	RW }
	BMR 	{ R AT91C_TCB2_BMR 	RW }
	IPNAME1 	{ R AT91C_TCB2_IPNAME1 	RW }
	listeReg 	{ VER ADDRSIZE FEATURES BCR IPNAME2 BMR IPNAME1  }

}
array set TCB3_att {
	IPNAME2 	{ R AT91C_TCB3_IPNAME2 	RW }
	BMR 	{ R AT91C_TCB3_BMR 	RW }
	IPNAME1 	{ R AT91C_TCB3_IPNAME1 	RW }
	FEATURES 	{ R AT91C_TCB3_FEATURES 	RW }
	ADDRSIZE 	{ R AT91C_TCB3_ADDRSIZE 	RW }
	VER 	{ R AT91C_TCB3_VER 	RO }
	BCR 	{ R AT91C_TCB3_BCR 	WO }
	listeReg 	{ IPNAME2 BMR IPNAME1 FEATURES ADDRSIZE VER BCR  }

}
array set TCB4_att {
	BMR 	{ R AT91C_TCB4_BMR 	RW }
	BCR 	{ R AT91C_TCB4_BCR 	WO }
	IPNAME2 	{ R AT91C_TCB4_IPNAME2 	RW }
	FEATURES 	{ R AT91C_TCB4_FEATURES 	RW }
	IPNAME1 	{ R AT91C_TCB4_IPNAME1 	RW }
	VER 	{ R AT91C_TCB4_VER 	RO }
	ADDRSIZE 	{ R AT91C_TCB4_ADDRSIZE 	RW }
	listeReg 	{ BMR BCR IPNAME2 FEATURES IPNAME1 VER ADDRSIZE  }

}
array set TCB5_att {
	VER 	{ R AT91C_TCB5_VER 	RO }
	ADDRSIZE 	{ R AT91C_TCB5_ADDRSIZE 	RW }
	BMR 	{ R AT91C_TCB5_BMR 	RW }
	FEATURES 	{ R AT91C_TCB5_FEATURES 	RW }
	IPNAME2 	{ R AT91C_TCB5_IPNAME2 	RW }
	IPNAME1 	{ R AT91C_TCB5_IPNAME1 	RW }
	BCR 	{ R AT91C_TCB5_BCR 	WO }
	listeReg 	{ VER ADDRSIZE BMR FEATURES IPNAME2 IPNAME1 BCR  }

}

# ========== Peripheral attributes for CKGR peripheral ========== 
array set CKGR_att {
	PLLAR 	{ R AT91C_CKGR_PLLAR 	RW }
	UCKR 	{ R AT91C_CKGR_UCKR 	RW }
	MOR 	{ R AT91C_CKGR_MOR 	RW }
	MCFR 	{ R AT91C_CKGR_MCFR 	RO }
	PLLBR 	{ R AT91C_CKGR_PLLBR 	RW }
	listeReg 	{ PLLAR UCKR MOR MCFR PLLBR  }

}

# ========== Peripheral attributes for DAC peripheral ========== 
array set DAC0_att {
	FEATURES 	{ R AT91C_DAC0_FEATURES 	RW }
	ADDRSIZE 	{ R AT91C_DAC0_ADDRSIZE 	RW }
	WPMR 	{ R AT91C_DAC0_WPMR 	RW }
	CHDR 	{ R AT91C_DAC0_CHDR 	WO }
	IPNAME1 	{ R AT91C_DAC0_IPNAME1 	RW }
	IDR 	{ R AT91C_DAC0_IDR 	WO }
	CR 	{ R AT91C_DAC0_CR 	WO }
	IPNAME2 	{ R AT91C_DAC0_IPNAME2 	RW }
	IMR 	{ R AT91C_DAC0_IMR 	RO }
	CHSR 	{ R AT91C_DAC0_CHSR 	RO }
	ACR 	{ R AT91C_DAC0_ACR 	RW }
	WPSR 	{ R AT91C_DAC0_WPSR 	R0 }
	CHER 	{ R AT91C_DAC0_CHER 	WO }
	CDR 	{ R AT91C_DAC0_CDR 	WO }
	IER 	{ R AT91C_DAC0_IER 	WO }
	ISR 	{ R AT91C_DAC0_ISR 	RO }
	VER 	{ R AT91C_DAC0_VER 	RO }
	MR 	{ R AT91C_DAC0_MR 	RW }
	listeReg 	{ FEATURES ADDRSIZE WPMR CHDR IPNAME1 IDR CR IPNAME2 IMR CHSR ACR WPSR CHER CDR IER ISR VER MR  }

}

# ========== Peripheral attributes for MPU peripheral ========== 
array set MPU_att {
	ADDR3 	{ R AT91C_MPU_REG_BASE_ADDR3 	RW }
	NB 	{ R AT91C_MPU_REG_NB 	RW }
	SIZE1 	{ R AT91C_MPU_ATTR_SIZE1 	RW }
	ADDR1 	{ R AT91C_MPU_REG_BASE_ADDR1 	RW }
	SIZE3 	{ R AT91C_MPU_ATTR_SIZE3 	RW }
	CTRL 	{ R AT91C_MPU_CTRL 	RW }
	SIZE2 	{ R AT91C_MPU_ATTR_SIZE2 	RW }
	ADDR 	{ R AT91C_MPU_REG_BASE_ADDR 	RW }
	ADDR2 	{ R AT91C_MPU_REG_BASE_ADDR2 	RW }
	SIZE 	{ R AT91C_MPU_ATTR_SIZE 	RW }
	TYPE 	{ R AT91C_MPU_TYPE 	RO }
	listeReg 	{ ADDR3 NB SIZE1 ADDR1 SIZE3 CTRL SIZE2 ADDR ADDR2 SIZE TYPE  }

}

# ========== Peripheral attributes for CM3 peripheral ========== 
array set CM3_att {
	SHCSR 	{ R AT91C_CM3_SHCSR 	RW }
	CCR 	{ R AT91C_CM3_CCR 	RW }
	ICSR 	{ R AT91C_CM3_ICSR 	RW }
	CPUID 	{ R AT91C_CM3_CPUID 	RO }
	SCR 	{ R AT91C_CM3_SCR 	RW }
	AIRCR 	{ R AT91C_CM3_AIRCR 	RW }
	SHPR 	{ R AT91C_CM3_SHPR 	RW  3 }
	VTOR 	{ R AT91C_CM3_VTOR 	RW }
	listeReg 	{ SHCSR CCR ICSR CPUID SCR AIRCR SHPR VTOR  }

}

# ========== Peripheral attributes for SUPC peripheral ========== 
array set SUPC_att {
	FWUTR 	{ R AT91C_SUPC_FWUTR 	RW }
	SR 	{ R AT91C_SUPC_SR 	RO }
	BOMR 	{ R AT91C_SUPC_BOMR 	RW }
	WUMR 	{ R AT91C_SUPC_WUMR 	RW }
	WUIR 	{ R AT91C_SUPC_WUIR 	RW }
	CR 	{ R AT91C_SUPC_CR 	WO }
	MR 	{ R AT91C_SUPC_MR 	RW }
	listeReg 	{ FWUTR SR BOMR WUMR WUIR CR MR  }

}

# ========== Peripheral attributes for TWI peripheral ========== 
array set TWI0_att {
	IMR 	{ R AT91C_TWI0_IMR 	RO }
	IPNAME1 	{ R AT91C_TWI0_IPNAME1 	RW }
	CR 	{ R AT91C_TWI0_CR 	WO }
	IPNAME2 	{ R AT91C_TWI0_IPNAME2 	RW }
	CWGR 	{ R AT91C_TWI0_CWGR 	RW }
	SMR 	{ R AT91C_TWI0_SMR 	RW }
	ADDRSIZE 	{ R AT91C_TWI0_ADDRSIZE 	RW }
	SR 	{ R AT91C_TWI0_SR 	RO }
	IER 	{ R AT91C_TWI0_IER 	WO }
	VER 	{ R AT91C_TWI0_VER 	WO }
	RHR 	{ R AT91C_TWI0_RHR 	RO }
	IADR 	{ R AT91C_TWI0_IADR 	RW }
	IDR 	{ R AT91C_TWI0_IDR 	WO }
	THR 	{ R AT91C_TWI0_THR 	WO }
	FEATURES 	{ R AT91C_TWI0_FEATURES 	RW }
	MMR 	{ R AT91C_TWI0_MMR 	RW }
	listeReg 	{ IMR IPNAME1 CR IPNAME2 CWGR SMR ADDRSIZE SR IER VER RHR IADR IDR THR FEATURES MMR  }

}
array set TWI1_att {
	CR 	{ R AT91C_TWI1_CR 	WO }
	VER 	{ R AT91C_TWI1_VER 	WO }
	IMR 	{ R AT91C_TWI1_IMR 	RO }
	IADR 	{ R AT91C_TWI1_IADR 	RW }
	THR 	{ R AT91C_TWI1_THR 	WO }
	IPNAME2 	{ R AT91C_TWI1_IPNAME2 	RW }
	FEATURES 	{ R AT91C_TWI1_FEATURES 	RW }
	SMR 	{ R AT91C_TWI1_SMR 	RW }
	IDR 	{ R AT91C_TWI1_IDR 	WO }
	SR 	{ R AT91C_TWI1_SR 	RO }
	IPNAME1 	{ R AT91C_TWI1_IPNAME1 	RW }
	IER 	{ R AT91C_TWI1_IER 	WO }
	ADDRSIZE 	{ R AT91C_TWI1_ADDRSIZE 	RW }
	CWGR 	{ R AT91C_TWI1_CWGR 	RW }
	MMR 	{ R AT91C_TWI1_MMR 	RW }
	RHR 	{ R AT91C_TWI1_RHR 	RO }
	listeReg 	{ CR VER IMR IADR THR IPNAME2 FEATURES SMR IDR SR IPNAME1 IER ADDRSIZE CWGR MMR RHR  }

}

# ========== Peripheral attributes for PWMC_CH peripheral ========== 
array set PWMC_CH0_att {
	CMR 	{ R AT91C_PWMC_CH0_CMR 	RW }
	DTUPDR 	{ R AT91C_PWMC_CH0_DTUPDR 	WO }
	CPRDR 	{ R AT91C_PWMC_CH0_CPRDR 	RW }
	CPRDUPDR 	{ R AT91C_PWMC_CH0_CPRDUPDR 	WO }
	CDTYR 	{ R AT91C_PWMC_CH0_CDTYR 	RW }
	DTR 	{ R AT91C_PWMC_CH0_DTR 	RW }
	CDTYUPDR 	{ R AT91C_PWMC_CH0_CDTYUPDR 	WO }
	CCNTR 	{ R AT91C_PWMC_CH0_CCNTR 	RO }
	listeReg 	{ CMR DTUPDR CPRDR CPRDUPDR CDTYR DTR CDTYUPDR CCNTR  }

}
array set PWMC_CH1_att {
	DTUPDR 	{ R AT91C_PWMC_CH1_DTUPDR 	WO }
	DTR 	{ R AT91C_PWMC_CH1_DTR 	RW }
	CDTYUPDR 	{ R AT91C_PWMC_CH1_CDTYUPDR 	WO }
	CDTYR 	{ R AT91C_PWMC_CH1_CDTYR 	RW }
	CCNTR 	{ R AT91C_PWMC_CH1_CCNTR 	RO }
	CPRDR 	{ R AT91C_PWMC_CH1_CPRDR 	RW }
	CMR 	{ R AT91C_PWMC_CH1_CMR 	RW }
	CPRDUPDR 	{ R AT91C_PWMC_CH1_CPRDUPDR 	WO }
	listeReg 	{ DTUPDR DTR CDTYUPDR CDTYR CCNTR CPRDR CMR CPRDUPDR  }

}
array set PWMC_CH2_att {
	CPRDUPDR 	{ R AT91C_PWMC_CH2_CPRDUPDR 	WO }
	CDTYR 	{ R AT91C_PWMC_CH2_CDTYR 	RW }
	CCNTR 	{ R AT91C_PWMC_CH2_CCNTR 	RO }
	CMR 	{ R AT91C_PWMC_CH2_CMR 	RW }
	CDTYUPDR 	{ R AT91C_PWMC_CH2_CDTYUPDR 	WO }
	DTUPDR 	{ R AT91C_PWMC_CH2_DTUPDR 	WO }
	DTR 	{ R AT91C_PWMC_CH2_DTR 	RW }
	CPRDR 	{ R AT91C_PWMC_CH2_CPRDR 	RW }
	listeReg 	{ CPRDUPDR CDTYR CCNTR CMR CDTYUPDR DTUPDR DTR CPRDR  }

}
array set PWMC_CH3_att {
	CPRDR 	{ R AT91C_PWMC_CH3_CPRDR 	RW }
	DTUPDR 	{ R AT91C_PWMC_CH3_DTUPDR 	WO }
	DTR 	{ R AT91C_PWMC_CH3_DTR 	RW }
	CDTYR 	{ R AT91C_PWMC_CH3_CDTYR 	RW }
	CMR 	{ R AT91C_PWMC_CH3_CMR 	RW }
	CCNTR 	{ R AT91C_PWMC_CH3_CCNTR 	RO }
	CPRDUPDR 	{ R AT91C_PWMC_CH3_CPRDUPDR 	WO }
	CDTYUPDR 	{ R AT91C_PWMC_CH3_CDTYUPDR 	WO }
	listeReg 	{ CPRDR DTUPDR DTR CDTYR CMR CCNTR CPRDUPDR CDTYUPDR  }

}

# ========== Peripheral attributes for HMATRIX2 peripheral ========== 
array set MATRIX_att {
	SFR2  	{ R AT91C_MATRIX_SFR2  	RW }
	SFR3  	{ R AT91C_MATRIX_SFR3  	RW }
	SCFG8 	{ R AT91C_MATRIX_SCFG8 	RW }
	MCFG2 	{ R AT91C_MATRIX_MCFG2 	RW }
	MCFG7 	{ R AT91C_MATRIX_MCFG7 	RW }
	SCFG3 	{ R AT91C_MATRIX_SCFG3 	RW }
	SCFG0 	{ R AT91C_MATRIX_SCFG0 	RW }
	SFR12 	{ R AT91C_MATRIX_SFR12 	RW }
	SCFG1 	{ R AT91C_MATRIX_SCFG1 	RW }
	SFR8  	{ R AT91C_MATRIX_SFR8  	RW }
	VER 	{ R AT91C_MATRIX_VER 	RW }
	SFR13 	{ R AT91C_MATRIX_SFR13 	RW }
	SFR5  	{ R AT91C_MATRIX_SFR5  	RW }
	MCFG0 	{ R AT91C_MATRIX_MCFG0 	RW }
	SCFG6 	{ R AT91C_MATRIX_SCFG6 	RW }
	SFR14 	{ R AT91C_MATRIX_SFR14 	RW }
	SFR1  	{ R AT91C_MATRIX_SFR1  	RW }
	SFR15 	{ R AT91C_MATRIX_SFR15 	RW }
	SFR6  	{ R AT91C_MATRIX_SFR6  	RW }
	SFR11 	{ R AT91C_MATRIX_SFR11 	RW }
	IPNAME2 	{ R AT91C_MATRIX_IPNAME2 	RW }
	ADDRSIZE 	{ R AT91C_MATRIX_ADDRSIZE 	RW }
	MCFG5 	{ R AT91C_MATRIX_MCFG5 	RW }
	SFR9  	{ R AT91C_MATRIX_SFR9  	RW }
	MCFG3 	{ R AT91C_MATRIX_MCFG3 	RW }
	SCFG4 	{ R AT91C_MATRIX_SCFG4 	RW }
	MCFG1 	{ R AT91C_MATRIX_MCFG1 	RW }
	SCFG7 	{ R AT91C_MATRIX_SCFG7 	RW }
	SFR10 	{ R AT91C_MATRIX_SFR10 	RW }
	SCFG2 	{ R AT91C_MATRIX_SCFG2 	RW }
	SFR7  	{ R AT91C_MATRIX_SFR7  	RW }
	IPNAME1 	{ R AT91C_MATRIX_IPNAME1 	RW }
	MCFG4 	{ R AT91C_MATRIX_MCFG4 	RW }
	SFR0  	{ R AT91C_MATRIX_SFR0  	RW }
	FEATURES 	{ R AT91C_MATRIX_FEATURES 	RW }
	SCFG5 	{ R AT91C_MATRIX_SCFG5 	RW }
	MCFG6 	{ R AT91C_MATRIX_MCFG6 	RW }
	SCFG9 	{ R AT91C_MATRIX_SCFG9 	RW }
	SFR4  	{ R AT91C_MATRIX_SFR4  	RW }
	listeReg 	{ SFR2  SFR3  SCFG8 MCFG2 MCFG7 SCFG3 SCFG0 SFR12 SCFG1 SFR8  VER SFR13 SFR5  MCFG0 SCFG6 SFR14 SFR1  SFR15 SFR6  SFR11 IPNAME2 ADDRSIZE MCFG5 SFR9  MCFG3 SCFG4 MCFG1 SCFG7 SFR10 SCFG2 SFR7  IPNAME1 MCFG4 SFR0  FEATURES SCFG5 MCFG6 SCFG9 SFR4   }

}

# ========== Peripheral attributes for ADC peripheral ========== 
array set ADC0_att {
	CDR2 	{ R AT91C_ADC0_CDR2 	RO }
	CGR 	{ R AT91C_ADC0_CGR 	RO }
	CDR7 	{ R AT91C_ADC0_CDR7 	RO }
	IDR 	{ R AT91C_ADC0_IDR 	WO }
	CR 	{ R AT91C_ADC0_CR 	WO }
	FEATURES 	{ R AT91C_ADC0_FEATURES 	RW }
	CWR 	{ R AT91C_ADC0_CWR 	RO }
	IPNAME1 	{ R AT91C_ADC0_IPNAME1 	RW }
	CDR9 	{ R AT91C_ADC0_CDR9 	RO }
	CDR3 	{ R AT91C_ADC0_CDR3 	RO }
	SR 	{ R AT91C_ADC0_SR 	RO }
	CHER 	{ R AT91C_ADC0_CHER 	WO }
	CDR1 	{ R AT91C_ADC0_CDR1 	RO }
	CDR6 	{ R AT91C_ADC0_CDR6 	RO }
	MR 	{ R AT91C_ADC0_MR 	RW }
	CWSR 	{ R AT91C_ADC0_CWSR 	RO }
	VER 	{ R AT91C_ADC0_VER 	RO }
	COR 	{ R AT91C_ADC0_COR 	RO }
	CDR8 	{ R AT91C_ADC0_CDR8 	RO }
	IPNAME2 	{ R AT91C_ADC0_IPNAME2 	RW }
	CDR0 	{ R AT91C_ADC0_CDR0 	RO }
	LCDR 	{ R AT91C_ADC0_LCDR 	RO }
	CDR12 	{ R AT91C_ADC0_CDR12 	RO }
	CHDR 	{ R AT91C_ADC0_CHDR 	WO }
	OVR 	{ R AT91C_ADC0_OVR 	RO }
	CDR15 	{ R AT91C_ADC0_CDR15 	RO }
	CDR11 	{ R AT91C_ADC0_CDR11 	RO }
	ADDRSIZE 	{ R AT91C_ADC0_ADDRSIZE 	RW }
	CDR13 	{ R AT91C_ADC0_CDR13 	RO }
	ACR 	{ R AT91C_ADC0_ACR 	RO }
	CDR5 	{ R AT91C_ADC0_CDR5 	RO }
	CDR14 	{ R AT91C_ADC0_CDR14 	RO }
	IMR 	{ R AT91C_ADC0_IMR 	RO }
	CHSR 	{ R AT91C_ADC0_CHSR 	RO }
	CDR10 	{ R AT91C_ADC0_CDR10 	RO }
	IER 	{ R AT91C_ADC0_IER 	WO }
	CDR4 	{ R AT91C_ADC0_CDR4 	RO }
	listeReg 	{ CDR2 CGR CDR7 IDR CR FEATURES CWR IPNAME1 CDR9 CDR3 SR CHER CDR1 CDR6 MR CWSR VER COR CDR8 IPNAME2 CDR0 LCDR CDR12 CHDR OVR CDR15 CDR11 ADDRSIZE CDR13 ACR CDR5 CDR14 IMR CHSR CDR10 IER CDR4  }

}

# ========== Peripheral attributes for RTTC peripheral ========== 
array set RTTC_att {
	RTSR 	{ R AT91C_RTTC_RTSR 	RO }
	RTVR 	{ R AT91C_RTTC_RTVR 	RO }
	RTMR 	{ R AT91C_RTTC_RTMR 	RW }
	RTAR 	{ R AT91C_RTTC_RTAR 	RW }
	listeReg 	{ RTSR RTVR RTMR RTAR  }

}

# ========== Peripheral attributes for UDP peripheral ========== 
array set UDP_att {
	RSTEP 	{ R AT91C_UDP_RSTEP 	RO }
	CSR 	{ R AT91C_UDP_CSR 	RW  8 }
	IMR 	{ R AT91C_UDP_IMR 	RO }
	FDR 	{ R AT91C_UDP_FDR 	RW  8 }
	ISR 	{ R AT91C_UDP_ISR 	RO }
	IPNAME2 	{ R AT91C_UDP_IPNAME2 	RW }
	ICR 	{ R AT91C_UDP_ICR 	RO }
	VER 	{ R AT91C_UDP_VER 	RO }
	IER 	{ R AT91C_UDP_IER 	WO }
	FEATURES 	{ R AT91C_UDP_FEATURES 	RW }
	IPNAME1 	{ R AT91C_UDP_IPNAME1 	RW }
	GLBSTATE 	{ R AT91C_UDP_GLBSTATE 	RW }
	ADDRSIZE 	{ R AT91C_UDP_ADDRSIZE 	RW }
	NUM 	{ R AT91C_UDP_NUM 	RO }
	IDR 	{ R AT91C_UDP_IDR 	WO }
	TXVC 	{ R AT91C_UDP_TXVC 	RW }
	FADDR 	{ R AT91C_UDP_FADDR 	RW }
	listeReg 	{ RSTEP CSR IMR FDR ISR IPNAME2 ICR VER IER FEATURES IPNAME1 GLBSTATE ADDRSIZE NUM IDR TXVC FADDR  }

}

# ========== Peripheral attributes for RTC peripheral ========== 
array set RTC_att {
	VER 	{ R AT91C_RTC_VER 	RO }
	TIMR 	{ R AT91C_RTC_TIMR 	RW }
	CALALR 	{ R AT91C_RTC_CALALR 	RW }
	IER 	{ R AT91C_RTC_IER 	WO }
	MR 	{ R AT91C_RTC_MR 	RW }
	CALR 	{ R AT91C_RTC_CALR 	RW }
	TIMALR 	{ R AT91C_RTC_TIMALR 	RW }
	SCCR 	{ R AT91C_RTC_SCCR 	WO }
	CR 	{ R AT91C_RTC_CR 	RW }
	IDR 	{ R AT91C_RTC_IDR 	WO }
	IMR 	{ R AT91C_RTC_IMR 	RO }
	SR 	{ R AT91C_RTC_SR 	RO }
	listeReg 	{ VER TIMR CALALR IER MR CALR TIMALR SCCR CR IDR IMR SR  }

}

# ========== Peripheral attributes for TC peripheral ========== 
array set TC0_att {
	SR 	{ R AT91C_TC0_SR 	RO }
	CCR 	{ R AT91C_TC0_CCR 	WO }
	CMR 	{ R AT91C_TC0_CMR 	RW }
	IER 	{ R AT91C_TC0_IER 	WO }
	CV 	{ R AT91C_TC0_CV 	RW }
	RB 	{ R AT91C_TC0_RB 	RW }
	IDR 	{ R AT91C_TC0_IDR 	WO }
	RA 	{ R AT91C_TC0_RA 	RW }
	RC 	{ R AT91C_TC0_RC 	RW }
	IMR 	{ R AT91C_TC0_IMR 	RO }
	listeReg 	{ SR CCR CMR IER CV RB IDR RA RC IMR  }

}
array set TC1_att {
	SR 	{ R AT91C_TC1_SR 	RO }
	CV 	{ R AT91C_TC1_CV 	RW }
	RA 	{ R AT91C_TC1_RA 	RW }
	IER 	{ R AT91C_TC1_IER 	WO }
	RB 	{ R AT91C_TC1_RB 	RW }
	RC 	{ R AT91C_TC1_RC 	RW }
	CCR 	{ R AT91C_TC1_CCR 	WO }
	IMR 	{ R AT91C_TC1_IMR 	RO }
	IDR 	{ R AT91C_TC1_IDR 	WO }
	CMR 	{ R AT91C_TC1_CMR 	RW }
	listeReg 	{ SR CV RA IER RB RC CCR IMR IDR CMR  }

}
array set TC2_att {
	SR 	{ R AT91C_TC2_SR 	RO }
	IER 	{ R AT91C_TC2_IER 	WO }
	CCR 	{ R AT91C_TC2_CCR 	WO }
	IDR 	{ R AT91C_TC2_IDR 	WO }
	RA 	{ R AT91C_TC2_RA 	RW }
	RB 	{ R AT91C_TC2_RB 	RW }
	IMR 	{ R AT91C_TC2_IMR 	RO }
	CV 	{ R AT91C_TC2_CV 	RW }
	RC 	{ R AT91C_TC2_RC 	RW }
	CMR 	{ R AT91C_TC2_CMR 	RW }
	listeReg 	{ SR IER CCR IDR RA RB IMR CV RC CMR  }

}
array set TC3_att {
	IDR 	{ R AT91C_TC3_IDR 	WO }
	IER 	{ R AT91C_TC3_IER 	WO }
	SR 	{ R AT91C_TC3_SR 	RO }
	CV 	{ R AT91C_TC3_CV 	RW }
	CMR 	{ R AT91C_TC3_CMR 	RW }
	RC 	{ R AT91C_TC3_RC 	RW }
	RA 	{ R AT91C_TC3_RA 	RW }
	IMR 	{ R AT91C_TC3_IMR 	RO }
	RB 	{ R AT91C_TC3_RB 	RW }
	CCR 	{ R AT91C_TC3_CCR 	WO }
	listeReg 	{ IDR IER SR CV CMR RC RA IMR RB CCR  }

}
array set TC4_att {
	CV 	{ R AT91C_TC4_CV 	RW }
	CMR 	{ R AT91C_TC4_CMR 	RW }
	RA 	{ R AT91C_TC4_RA 	RW }
	IMR 	{ R AT91C_TC4_IMR 	RO }
	RC 	{ R AT91C_TC4_RC 	RW }
	SR 	{ R AT91C_TC4_SR 	RO }
	RB 	{ R AT91C_TC4_RB 	RW }
	IDR 	{ R AT91C_TC4_IDR 	WO }
	IER 	{ R AT91C_TC4_IER 	WO }
	CCR 	{ R AT91C_TC4_CCR 	WO }
	listeReg 	{ CV CMR RA IMR RC SR RB IDR IER CCR  }

}
array set TC5_att {
	CV 	{ R AT91C_TC5_CV 	RW }
	IER 	{ R AT91C_TC5_IER 	WO }
	CMR 	{ R AT91C_TC5_CMR 	RW }
	IMR 	{ R AT91C_TC5_IMR 	RO }
	RA 	{ R AT91C_TC5_RA 	RW }
	RB 	{ R AT91C_TC5_RB 	RW }
	RC 	{ R AT91C_TC5_RC 	RW }
	SR 	{ R AT91C_TC5_SR 	RO }
	CCR 	{ R AT91C_TC5_CCR 	WO }
	IDR 	{ R AT91C_TC5_IDR 	WO }
	listeReg 	{ CV IER CMR IMR RA RB RC SR CCR IDR  }

}

# ========== Peripheral attributes for SYS peripheral ========== 
array set SYS_att {
	GPBR 	{ R AT91C_SYS_GPBR 	  8 }
	listeReg 	{ GPBR  }

}

# ========== Peripheral attributes for PIO peripheral ========== 
array set PIOA_att {
	SENIDR 	{ R AT91C_PIOA_SENIDR 	WO }
	OWSR 	{ R AT91C_PIOA_OWSR 	RO }
	PSR 	{ R AT91C_PIOA_PSR 	RO }
	MDER 	{ R AT91C_PIOA_MDER 	WO }
	IPNAME1 	{ R AT91C_PIOA_IPNAME1 	RW }
	FEATURES 	{ R AT91C_PIOA_FEATURES 	RW }
	SP2 	{ R AT91C_PIOA_SP2 	WO }
	ODR 	{ R AT91C_PIOA_ODR 	WO }
	IDR 	{ R AT91C_PIOA_IDR 	WO }
	PDR 	{ R AT91C_PIOA_PDR 	WO }
	PDSR 	{ R AT91C_PIOA_PDSR 	RO }
	PPDER 	{ R AT91C_PIOA_PPDER 	WO }
	SENIER 	{ R AT91C_PIOA_SENIER 	WO }
	SLEW2 	{ R AT91C_PIOA_SLEW2 	RW }
	SENMR 	{ R AT91C_PIOA_SENMR 	RW }
	PPUDR 	{ R AT91C_PIOA_PPUDR 	WO }
	OWDR 	{ R AT91C_PIOA_OWDR 	WO }
	ADDRSIZE 	{ R AT91C_PIOA_ADDRSIZE 	RW }
	IFER 	{ R AT91C_PIOA_IFER 	WO }
	PPDSR 	{ R AT91C_PIOA_PPDSR 	RO }
	SP1 	{ R AT91C_PIOA_SP1 	WO }
	SENIMR 	{ R AT91C_PIOA_SENIMR 	RO }
	SENDATA 	{ R AT91C_PIOA_SENDATA 	RO }
	VER 	{ R AT91C_PIOA_VER 	RW }
	PER 	{ R AT91C_PIOA_PER 	WO }
	IMR 	{ R AT91C_PIOA_IMR 	RO }
	PPUSR 	{ R AT91C_PIOA_PPUSR 	RO }
	ODSR 	{ R AT91C_PIOA_ODSR 	RO }
	SENISR 	{ R AT91C_PIOA_SENISR 	RO }
	IFDR 	{ R AT91C_PIOA_IFDR 	WO }
	SODR 	{ R AT91C_PIOA_SODR 	WO }
	SLEW1 	{ R AT91C_PIOA_SLEW1 	RW }
	IER 	{ R AT91C_PIOA_IER 	WO }
	MDSR 	{ R AT91C_PIOA_MDSR 	RO }
	ISR 	{ R AT91C_PIOA_ISR 	RO }
	IFSR 	{ R AT91C_PIOA_IFSR 	RO }
	PPDDR 	{ R AT91C_PIOA_PPDDR 	WO }
	PPUER 	{ R AT91C_PIOA_PPUER 	WO }
	OWER 	{ R AT91C_PIOA_OWER 	WO }
	IPNAME2 	{ R AT91C_PIOA_IPNAME2 	RW }
	MDDR 	{ R AT91C_PIOA_MDDR 	WO }
	CODR 	{ R AT91C_PIOA_CODR 	WO }
	OER 	{ R AT91C_PIOA_OER 	WO }
	OSR 	{ R AT91C_PIOA_OSR 	RO }
	ABSR 	{ R AT91C_PIOA_ABSR 	RO }
	listeReg 	{ SENIDR OWSR PSR MDER IPNAME1 FEATURES SP2 ODR IDR PDR PDSR PPDER SENIER SLEW2 SENMR PPUDR OWDR ADDRSIZE IFER PPDSR SP1 SENIMR SENDATA VER PER IMR PPUSR ODSR SENISR IFDR SODR SLEW1 IER MDSR ISR IFSR PPDDR PPUER OWER IPNAME2 MDDR CODR OER OSR ABSR  }

}
array set PIOB_att {
	MDDR 	{ R AT91C_PIOB_MDDR 	WO }
	ABSR 	{ R AT91C_PIOB_ABSR 	RO }
	SP1 	{ R AT91C_PIOB_SP1 	WO }
	ODSR 	{ R AT91C_PIOB_ODSR 	RO }
	SLEW1 	{ R AT91C_PIOB_SLEW1 	RW }
	SENISR 	{ R AT91C_PIOB_SENISR 	RO }
	OSR 	{ R AT91C_PIOB_OSR 	RO }
	IFER 	{ R AT91C_PIOB_IFER 	WO }
	SENDATA 	{ R AT91C_PIOB_SENDATA 	RO }
	MDSR 	{ R AT91C_PIOB_MDSR 	RO }
	IFDR 	{ R AT91C_PIOB_IFDR 	WO }
	MDER 	{ R AT91C_PIOB_MDER 	WO }
	SENIDR 	{ R AT91C_PIOB_SENIDR 	WO }
	IER 	{ R AT91C_PIOB_IER 	WO }
	OWDR 	{ R AT91C_PIOB_OWDR 	WO }
	IFSR 	{ R AT91C_PIOB_IFSR 	RO }
	ISR 	{ R AT91C_PIOB_ISR 	RO }
	PPUDR 	{ R AT91C_PIOB_PPUDR 	WO }
	PDSR 	{ R AT91C_PIOB_PDSR 	RO }
	IPNAME2 	{ R AT91C_PIOB_IPNAME2 	RW }
	PPUER 	{ R AT91C_PIOB_PPUER 	WO }
	SLEW2 	{ R AT91C_PIOB_SLEW2 	RW }
	OER 	{ R AT91C_PIOB_OER 	WO }
	CODR 	{ R AT91C_PIOB_CODR 	WO }
	PPDDR 	{ R AT91C_PIOB_PPDDR 	WO }
	OWER 	{ R AT91C_PIOB_OWER 	WO }
	VER 	{ R AT91C_PIOB_VER 	RW }
	PPDER 	{ R AT91C_PIOB_PPDER 	WO }
	IMR 	{ R AT91C_PIOB_IMR 	RO }
	PPUSR 	{ R AT91C_PIOB_PPUSR 	RO }
	IPNAME1 	{ R AT91C_PIOB_IPNAME1 	RW }
	ADDRSIZE 	{ R AT91C_PIOB_ADDRSIZE 	RW }
	SP2 	{ R AT91C_PIOB_SP2 	WO }
	IDR 	{ R AT91C_PIOB_IDR 	WO }
	SENMR 	{ R AT91C_PIOB_SENMR 	RW }
	SODR 	{ R AT91C_PIOB_SODR 	WO }
	PPDSR 	{ R AT91C_PIOB_PPDSR 	RO }
	PSR 	{ R AT91C_PIOB_PSR 	RO }
	ODR 	{ R AT91C_PIOB_ODR 	WO }
	OWSR 	{ R AT91C_PIOB_OWSR 	RO }
	FEATURES 	{ R AT91C_PIOB_FEATURES 	RW }
	PDR 	{ R AT91C_PIOB_PDR 	WO }
	SENIMR 	{ R AT91C_PIOB_SENIMR 	RO }
	SENIER 	{ R AT91C_PIOB_SENIER 	WO }
	PER 	{ R AT91C_PIOB_PER 	WO }
	listeReg 	{ MDDR ABSR SP1 ODSR SLEW1 SENISR OSR IFER SENDATA MDSR IFDR MDER SENIDR IER OWDR IFSR ISR PPUDR PDSR IPNAME2 PPUER SLEW2 OER CODR PPDDR OWER VER PPDER IMR PPUSR IPNAME1 ADDRSIZE SP2 IDR SENMR SODR PPDSR PSR ODR OWSR FEATURES PDR SENIMR SENIER PER  }

}
array set PIOC_att {
	VER 	{ R AT91C_PIOC_VER 	RW }
	IMR 	{ R AT91C_PIOC_IMR 	RO }
	PSR 	{ R AT91C_PIOC_PSR 	RO }
	PPDSR 	{ R AT91C_PIOC_PPDSR 	RO }
	OER 	{ R AT91C_PIOC_OER 	WO }
	OSR 	{ R AT91C_PIOC_OSR 	RO }
	MDDR 	{ R AT91C_PIOC_MDDR 	WO }
	PPUSR 	{ R AT91C_PIOC_PPUSR 	RO }
	ODSR 	{ R AT91C_PIOC_ODSR 	RO }
	SLEW2 	{ R AT91C_PIOC_SLEW2 	RW }
	SENMR 	{ R AT91C_PIOC_SENMR 	RW }
	IFER 	{ R AT91C_PIOC_IFER 	WO }
	PDR 	{ R AT91C_PIOC_PDR 	WO }
	MDER 	{ R AT91C_PIOC_MDER 	WO }
	SP2 	{ R AT91C_PIOC_SP2 	WO }
	IPNAME1 	{ R AT91C_PIOC_IPNAME1 	RW }
	IER 	{ R AT91C_PIOC_IER 	WO }
	OWDR 	{ R AT91C_PIOC_OWDR 	WO }
	IDR 	{ R AT91C_PIOC_IDR 	WO }
	PDSR 	{ R AT91C_PIOC_PDSR 	RO }
	SENIDR 	{ R AT91C_PIOC_SENIDR 	WO }
	SENISR 	{ R AT91C_PIOC_SENISR 	RO }
	PER 	{ R AT91C_PIOC_PER 	WO }
	SENDATA 	{ R AT91C_PIOC_SENDATA 	RO }
	IPNAME2 	{ R AT91C_PIOC_IPNAME2 	RW }
	PPDDR 	{ R AT91C_PIOC_PPDDR 	WO }
	ADDRSIZE 	{ R AT91C_PIOC_ADDRSIZE 	RW }
	IFDR 	{ R AT91C_PIOC_IFDR 	WO }
	ODR 	{ R AT91C_PIOC_ODR 	WO }
	CODR 	{ R AT91C_PIOC_CODR 	WO }
	MDSR 	{ R AT91C_PIOC_MDSR 	RO }
	FEATURES 	{ R AT91C_PIOC_FEATURES 	RW }
	IFSR 	{ R AT91C_PIOC_IFSR 	RO }
	PPUER 	{ R AT91C_PIOC_PPUER 	WO }
	PPDER 	{ R AT91C_PIOC_PPDER 	WO }
	OWSR 	{ R AT91C_PIOC_OWSR 	RO }
	ISR 	{ R AT91C_PIOC_ISR 	RO }
	OWER 	{ R AT91C_PIOC_OWER 	WO }
	PPUDR 	{ R AT91C_PIOC_PPUDR 	WO }
	SENIMR 	{ R AT91C_PIOC_SENIMR 	RO }
	SLEW1 	{ R AT91C_PIOC_SLEW1 	RW }
	SENIER 	{ R AT91C_PIOC_SENIER 	WO }
	SODR 	{ R AT91C_PIOC_SODR 	WO }
	SP1 	{ R AT91C_PIOC_SP1 	WO }
	ABSR 	{ R AT91C_PIOC_ABSR 	RO }
	listeReg 	{ VER IMR PSR PPDSR OER OSR MDDR PPUSR ODSR SLEW2 SENMR IFER PDR MDER SP2 IPNAME1 IER OWDR IDR PDSR SENIDR SENISR PER SENDATA IPNAME2 PPDDR ADDRSIZE IFDR ODR CODR MDSR FEATURES IFSR PPUER PPDER OWSR ISR OWER PPUDR SENIMR SLEW1 SENIER SODR SP1 ABSR  }

}

# ========== Peripheral attributes for PWMC peripheral ========== 
array set PWMC_att {
	CMP6M 	{ R AT91C_PWMC_CMP6M 	RW }
	ADDRSIZE 	{ R AT91C_PWMC_ADDRSIZE 	RW }
	CMP5V 	{ R AT91C_PWMC_CMP5V 	RW }
	FMR 	{ R AT91C_PWMC_FMR 	RW }
	IER2 	{ R AT91C_PWMC_IER2 	WO }
	EL5MR 	{ R AT91C_PWMC_EL5MR 	RW }
	CMP0VUPD 	{ R AT91C_PWMC_CMP0VUPD 	WO }
	FPER1 	{ R AT91C_PWMC_FPER1 	RW }
	SCUPUPD 	{ R AT91C_PWMC_SCUPUPD 	WO }
	DIS 	{ R AT91C_PWMC_DIS 	WO }
	CMP1M 	{ R AT91C_PWMC_CMP1M 	RW }
	CMP2V 	{ R AT91C_PWMC_CMP2V 	RW }
	WPCR 	{ R AT91C_PWMC_WPCR 	RW }
	CMP5MUPD 	{ R AT91C_PWMC_CMP5MUPD 	WO }
	FPV 	{ R AT91C_PWMC_FPV 	RW }
	UPCR 	{ R AT91C_PWMC_UPCR 	RW }
	CMP4MUPD 	{ R AT91C_PWMC_CMP4MUPD 	WO }
	EL6MR 	{ R AT91C_PWMC_EL6MR 	RW }
	OS 	{ R AT91C_PWMC_OS 	RW }
	OSSUPD 	{ R AT91C_PWMC_OSSUPD 	WO }
	FSR 	{ R AT91C_PWMC_FSR 	RO }
	CMP2M 	{ R AT91C_PWMC_CMP2M 	RW }
	EL2MR 	{ R AT91C_PWMC_EL2MR 	RW }
	FPER3 	{ R AT91C_PWMC_FPER3 	RW }
	CMP4M 	{ R AT91C_PWMC_CMP4M 	RW }
	ISR2 	{ R AT91C_PWMC_ISR2 	RO }
	CMP6VUPD 	{ R AT91C_PWMC_CMP6VUPD 	WO }
	CMP5VUPD 	{ R AT91C_PWMC_CMP5VUPD 	WO }
	EL7MR 	{ R AT91C_PWMC_EL7MR 	RW }
	OSC 	{ R AT91C_PWMC_OSC 	WO }
	CMP3MUPD 	{ R AT91C_PWMC_CMP3MUPD 	WO }
	CMP2MUPD 	{ R AT91C_PWMC_CMP2MUPD 	WO }
	CMP0M 	{ R AT91C_PWMC_CMP0M 	RW }
	EL1MR 	{ R AT91C_PWMC_EL1MR 	RW }
	CMP0MUPD 	{ R AT91C_PWMC_CMP0MUPD 	WO }
	WPSR 	{ R AT91C_PWMC_WPSR 	RO }
	CMP1MUPD 	{ R AT91C_PWMC_CMP1MUPD 	WO }
	IMR2 	{ R AT91C_PWMC_IMR2 	RO }
	CMP3V 	{ R AT91C_PWMC_CMP3V 	RW }
	CMP3VUPD 	{ R AT91C_PWMC_CMP3VUPD 	WO }
	CMP3M 	{ R AT91C_PWMC_CMP3M 	RW }
	FPER4 	{ R AT91C_PWMC_FPER4 	RW }
	OSCUPD 	{ R AT91C_PWMC_OSCUPD 	WO }
	CMP0V 	{ R AT91C_PWMC_CMP0V 	RW }
	OOV 	{ R AT91C_PWMC_OOV 	RW }
	ENA 	{ R AT91C_PWMC_ENA 	WO }
	CMP6MUPD 	{ R AT91C_PWMC_CMP6MUPD 	WO }
	SYNC 	{ R AT91C_PWMC_SYNC 	RW }
	IPNAME1 	{ R AT91C_PWMC_IPNAME1 	RW }
	IDR2 	{ R AT91C_PWMC_IDR2 	WO }
	SR 	{ R AT91C_PWMC_SR 	RO }
	FPER2 	{ R AT91C_PWMC_FPER2 	RW }
	EL3MR 	{ R AT91C_PWMC_EL3MR 	RW }
	IMR1 	{ R AT91C_PWMC_IMR1 	RO }
	EL0MR 	{ R AT91C_PWMC_EL0MR 	RW }
	STEP 	{ R AT91C_PWMC_STEP 	RW }
	FCR 	{ R AT91C_PWMC_FCR 	WO }
	CMP7MUPD 	{ R AT91C_PWMC_CMP7MUPD 	WO }
	ISR1 	{ R AT91C_PWMC_ISR1 	RO }
	CMP4VUPD 	{ R AT91C_PWMC_CMP4VUPD 	WO }
	VER 	{ R AT91C_PWMC_VER 	RO }
	CMP5M 	{ R AT91C_PWMC_CMP5M 	RW }
	IER1 	{ R AT91C_PWMC_IER1 	WO }
	MR 	{ R AT91C_PWMC_MR 	RW }
	OSS 	{ R AT91C_PWMC_OSS 	WO }
	CMP7V 	{ R AT91C_PWMC_CMP7V 	RW }
	FEATURES 	{ R AT91C_PWMC_FEATURES 	RW }
	CMP4V 	{ R AT91C_PWMC_CMP4V 	RW }
	CMP7M 	{ R AT91C_PWMC_CMP7M 	RW }
	EL4MR 	{ R AT91C_PWMC_EL4MR 	RW }
	CMP2VUPD 	{ R AT91C_PWMC_CMP2VUPD 	WO }
	CMP6V 	{ R AT91C_PWMC_CMP6V 	RW }
	CMP1V 	{ R AT91C_PWMC_CMP1V 	RW }
	IDR1 	{ R AT91C_PWMC_IDR1 	WO }
	SCUP 	{ R AT91C_PWMC_SCUP 	RW }
	CMP1VUPD 	{ R AT91C_PWMC_CMP1VUPD 	WO }
	CMP7VUPD 	{ R AT91C_PWMC_CMP7VUPD 	WO }
	IPNAME2 	{ R AT91C_PWMC_IPNAME2 	RW }
	listeReg 	{ CMP6M ADDRSIZE CMP5V FMR IER2 EL5MR CMP0VUPD FPER1 SCUPUPD DIS CMP1M CMP2V WPCR CMP5MUPD FPV UPCR CMP4MUPD EL6MR OS OSSUPD FSR CMP2M EL2MR FPER3 CMP4M ISR2 CMP6VUPD CMP5VUPD EL7MR OSC CMP3MUPD CMP2MUPD CMP0M EL1MR CMP0MUPD WPSR CMP1MUPD IMR2 CMP3V CMP3VUPD CMP3M FPER4 OSCUPD CMP0V OOV ENA CMP6MUPD SYNC IPNAME1 IDR2 SR FPER2 EL3MR IMR1 EL0MR STEP FCR CMP7MUPD ISR1 CMP4VUPD VER CMP5M IER1 MR OSS CMP7V FEATURES CMP4V CMP7M EL4MR CMP2VUPD CMP6V CMP1V IDR1 SCUP CMP1VUPD CMP7VUPD IPNAME2  }

}

# ========== Peripheral attributes for PDC peripheral ========== 
array set PDC_DBGU0_att {
	TPR 	{ R AT91C_DBGU0_TPR 	RW }
	PTCR 	{ R AT91C_DBGU0_PTCR 	WO }
	TNCR 	{ R AT91C_DBGU0_TNCR 	RW }
	PTSR 	{ R AT91C_DBGU0_PTSR 	RO }
	RNCR 	{ R AT91C_DBGU0_RNCR 	RW }
	RPR 	{ R AT91C_DBGU0_RPR 	RW }
	TCR 	{ R AT91C_DBGU0_TCR 	RW }
	RNPR 	{ R AT91C_DBGU0_RNPR 	RW }
	TNPR 	{ R AT91C_DBGU0_TNPR 	RW }
	RCR 	{ R AT91C_DBGU0_RCR 	RW }
	listeReg 	{ TPR PTCR TNCR PTSR RNCR RPR TCR RNPR TNPR RCR  }

}
array set PDC_DBGU1_att {
	RNCR 	{ R AT91C_DBGU1_RNCR 	RW }
	RPR 	{ R AT91C_DBGU1_RPR 	RW }
	TNCR 	{ R AT91C_DBGU1_TNCR 	RW }
	TNPR 	{ R AT91C_DBGU1_TNPR 	RW }
	PTSR 	{ R AT91C_DBGU1_PTSR 	RO }
	PTCR 	{ R AT91C_DBGU1_PTCR 	WO }
	RCR 	{ R AT91C_DBGU1_RCR 	RW }
	RNPR 	{ R AT91C_DBGU1_RNPR 	RW }
	TPR 	{ R AT91C_DBGU1_TPR 	RW }
	TCR 	{ R AT91C_DBGU1_TCR 	RW }
	listeReg 	{ RNCR RPR TNCR TNPR PTSR PTCR RCR RNPR TPR TCR  }

}
array set PDC_PIOA_att {
	RPR 	{ R AT91C_PIOA_RPR 	RW }
	TPR 	{ R AT91C_PIOA_TPR 	RW }
	RCR 	{ R AT91C_PIOA_RCR 	RW }
	PTSR 	{ R AT91C_PIOA_PTSR 	RO }
	TCR 	{ R AT91C_PIOA_TCR 	RW }
	PTCR 	{ R AT91C_PIOA_PTCR 	WO }
	RNPR 	{ R AT91C_PIOA_RNPR 	RW }
	TNCR 	{ R AT91C_PIOA_TNCR 	RW }
	RNCR 	{ R AT91C_PIOA_RNCR 	RW }
	TNPR 	{ R AT91C_PIOA_TNPR 	RW }
	listeReg 	{ RPR TPR RCR PTSR TCR PTCR RNPR TNCR RNCR TNPR  }

}
array set PDC_TWI0_att {
	PTSR 	{ R AT91C_TWI0_PTSR 	RO }
	TPR 	{ R AT91C_TWI0_TPR 	RW }
	RPR 	{ R AT91C_TWI0_RPR 	RW }
	TNPR 	{ R AT91C_TWI0_TNPR 	RW }
	PTCR 	{ R AT91C_TWI0_PTCR 	WO }
	RCR 	{ R AT91C_TWI0_RCR 	RW }
	RNCR 	{ R AT91C_TWI0_RNCR 	RW }
	RNPR 	{ R AT91C_TWI0_RNPR 	RW }
	TNCR 	{ R AT91C_TWI0_TNCR 	RW }
	TCR 	{ R AT91C_TWI0_TCR 	RW }
	listeReg 	{ PTSR TPR RPR TNPR PTCR RCR RNCR RNPR TNCR TCR  }

}
array set PDC_TWI1_att {
	TPR 	{ R AT91C_TWI1_TPR 	RW }
	RNCR 	{ R AT91C_TWI1_RNCR 	RW }
	TNCR 	{ R AT91C_TWI1_TNCR 	RW }
	TCR 	{ R AT91C_TWI1_TCR 	RW }
	TNPR 	{ R AT91C_TWI1_TNPR 	RW }
	PTCR 	{ R AT91C_TWI1_PTCR 	WO }
	RNPR 	{ R AT91C_TWI1_RNPR 	RW }
	PTSR 	{ R AT91C_TWI1_PTSR 	RO }
	RPR 	{ R AT91C_TWI1_RPR 	RW }
	RCR 	{ R AT91C_TWI1_RCR 	RW }
	listeReg 	{ TPR RNCR TNCR TCR TNPR PTCR RNPR PTSR RPR RCR  }

}
array set PDC_US0_att {
	RNCR 	{ R AT91C_US0_RNCR 	RW }
	PTCR 	{ R AT91C_US0_PTCR 	WO }
	TCR 	{ R AT91C_US0_TCR 	RW }
	RPR 	{ R AT91C_US0_RPR 	RW }
	RNPR 	{ R AT91C_US0_RNPR 	RW }
	TNCR 	{ R AT91C_US0_TNCR 	RW }
	PTSR 	{ R AT91C_US0_PTSR 	RO }
	RCR 	{ R AT91C_US0_RCR 	RW }
	TNPR 	{ R AT91C_US0_TNPR 	RW }
	TPR 	{ R AT91C_US0_TPR 	RW }
	listeReg 	{ RNCR PTCR TCR RPR RNPR TNCR PTSR RCR TNPR TPR  }

}
array set PDC_US1_att {
	TNPR 	{ R AT91C_US1_TNPR 	RW }
	RPR 	{ R AT91C_US1_RPR 	RW }
	TCR 	{ R AT91C_US1_TCR 	RW }
	RCR 	{ R AT91C_US1_RCR 	RW }
	TPR 	{ R AT91C_US1_TPR 	RW }
	RNPR 	{ R AT91C_US1_RNPR 	RW }
	TNCR 	{ R AT91C_US1_TNCR 	RW }
	PTCR 	{ R AT91C_US1_PTCR 	WO }
	RNCR 	{ R AT91C_US1_RNCR 	RW }
	PTSR 	{ R AT91C_US1_PTSR 	RO }
	listeReg 	{ TNPR RPR TCR RCR TPR RNPR TNCR PTCR RNCR PTSR  }

}
array set PDC_SSC0_att {
	RNCR 	{ R AT91C_SSC0_RNCR 	RW }
	TPR 	{ R AT91C_SSC0_TPR 	RW }
	TCR 	{ R AT91C_SSC0_TCR 	RW }
	PTCR 	{ R AT91C_SSC0_PTCR 	WO }
	TNPR 	{ R AT91C_SSC0_TNPR 	RW }
	RPR 	{ R AT91C_SSC0_RPR 	RW }
	TNCR 	{ R AT91C_SSC0_TNCR 	RW }
	RNPR 	{ R AT91C_SSC0_RNPR 	RW }
	RCR 	{ R AT91C_SSC0_RCR 	RW }
	PTSR 	{ R AT91C_SSC0_PTSR 	RO }
	listeReg 	{ RNCR TPR TCR PTCR TNPR RPR TNCR RNPR RCR PTSR  }

}
array set PDC_PWMC_att {
	TNCR 	{ R AT91C_PWMC_TNCR 	RW }
	RCR 	{ R AT91C_PWMC_RCR 	RW }
	TCR 	{ R AT91C_PWMC_TCR 	RW }
	RNCR 	{ R AT91C_PWMC_RNCR 	RW }
	PTSR 	{ R AT91C_PWMC_PTSR 	RO }
	RNPR 	{ R AT91C_PWMC_RNPR 	RW }
	TNPR 	{ R AT91C_PWMC_TNPR 	RW }
	PTCR 	{ R AT91C_PWMC_PTCR 	WO }
	RPR 	{ R AT91C_PWMC_RPR 	RW }
	TPR 	{ R AT91C_PWMC_TPR 	RW }
	listeReg 	{ TNCR RCR TCR RNCR PTSR RNPR TNPR PTCR RPR TPR  }

}

# ========== PIO information ========== 

array set def_PIOA_att {
 	PA0 	{  PWMH0   TIOA0   A17  }
 	PA1 	{  PWMH1   TIOB0   A18  }
 	PA10 	{  UTXD0   SPI0_NPCS2  }
 	PA11 	{  SPI0_NPCS0   PWMH0  }
 	PA12 	{  SPI0_MISO   PWMH1  }
 	PA13 	{  SPI0_MOSI   PWMH2  }
 	PA14 	{  SPI0_SPCK   PWMH3  }
 	PA15 	{  TF   TIOA1   PWML3  }
 	PA16 	{  TK   TIOB1   PWML2  }
 	PA17 	{  TD   PCK1   PWMH3  }
 	PA18 	{  RD   PCK2   A14  }
 	PA19 	{  RK   PWML0   A15  }
 	PA2 	{  PWMH2   SCK0   DATRG  }
 	PA20 	{  RF   PWML1   A16  }
 	PA21 	{  RXD1   PCK1  }
 	PA22 	{  TXD1   SPI0_NPCS3   NCS2  }
 	PA23 	{  SCK1   PWMH0   A19  }
 	PA24 	{  RTS1   PWMH1   A20  }
 	PA25 	{  CTS1   PWMH2   A23  }
 	PA26 	{  DCD1   TIOA2   MCI0_DA2  }
 	PA27 	{  DTR1   TIOB2   MCI0_DA3  }
 	PA28 	{  DSR1   TCLK1   MCI0_CDA  }
 	PA29 	{  RI1   TCLK2   MCI0_CK  }
 	PA3 	{  TWD0   SPI0_NPCS3  }
 	PA30 	{  PWML2   SPI0_NPCS2   MCI0_DA0  }
 	PA31 	{  SPI0_NPCS1   PCK2   MCI0_DA1  }
 	PA4 	{  TWCK0   TCLK0  }
 	PA5 	{  RXD0   SPI0_NPCS3  }
 	PA6 	{  TXD0   PCK0  }
 	PA7 	{  RTS0   PWMH3  }
 	PA8 	{  CTS0   ADTRG  }
 	PA9 	{  URXD0   SPI0_NPCS1   PWMFI0  }
 }

array set def_PIOB_att {
 	PB0 	{  PWMH0  }
 	PB1 	{  PWMH1  }
 	PB10 	{ }
 	PB11 	{ }
 	PB12 	{  PWML1  }
 	PB13 	{  PWML2   PCK0  }
 	PB14 	{  SPI0_NPCS1   PWMH3  }
 	PB2 	{  URXD1   SPI0_NPCS2  }
 	PB3 	{  UTXD1   PCK2  }
 	PB4 	{  TWD1   PWMH2  }
 	PB5 	{  TWCK1   PWML0  }
 	PB6 	{ }
 	PB7 	{ }
 	PB8 	{ }
 	PB9 	{ }
 }

array set def_PIOC_att {
 	PC0 	{  D0   PWML0  }
 	PC1 	{  D1   PWML1  }
 	PC10 	{  NANDWE  }
 	PC11 	{  NRD  }
 	PC12 	{  NCS3  }
 	PC13 	{  NWAIT   PWML0  }
 	PC14 	{  NCS0  }
 	PC15 	{  NCS1   PWML1  }
 	PC16 	{  A21_NANDALE  }
 	PC17 	{  A22_NANDCLE  }
 	PC18 	{  A0_NBS0   PWMH0  }
 	PC19 	{  A1   PWMH1  }
 	PC2 	{  D2   PWML2  }
 	PC20 	{  A2   PWMH2  }
 	PC21 	{  A3   PWMH3  }
 	PC22 	{  A4   PWML3  }
 	PC23 	{  A5   TIOA3  }
 	PC24 	{  A6   TIOB3  }
 	PC25 	{  A7   TCLK3  }
 	PC26 	{  A8   TIOA4  }
 	PC27 	{  A9   TIOB4  }
 	PC28 	{  A10   TCLK4  }
 	PC29 	{  A11   TIOA5  }
 	PC3 	{  D3   PWML3  }
 	PC30 	{  A12   TIOB5  }
 	PC31 	{  A13   TCLK5  }
 	PC4 	{  D4   SPI0_NPCS1  }
 	PC5 	{  D5  }
 	PC6 	{  D6  }
 	PC7 	{  D7  }
 	PC8 	{  NWR0_NWE  }
 	PC9 	{  NANDOE  }
 }

# *****************************************************************************
#               IP PIN DEFINITIONS FOR AT91SAM3S4
# *****************************************************************************

# table definition: portname direction is_a_pio is_open_drain

array set def_design_att {
  MCI0 {
    CK {mci0_ck output 1 0}
    CDA {mci0_cda output 1 0}
    DA0 {mci0_da0 inout 1 0}
    DA1 {mci0_da1 inout 1 0}
    DA2 {mci0_da2 inout 1 0}
    DA3 {mci0_da3 inout 1 0}
  }
  NAND0 {
    D0 {d0 inout 1 0}
    D1 {d1 inout 1 0}
    D2 {d2 inout 1 0}
    D3 {d3 inout 1 0}
    D4 {d4 inout 1 0}
    D5 {d5 inout 1 0}
    D6 {d6 inout 1 0}
    D7 {d7 inout 1 0}
    NANDCLE {a22_nandcle output 1 0}
    NANDALE {a21_nandale output 1 0}
    NANDWE {nandwe output 1 0}
    NANDOE {nandoe output 1 0}
    NCS0 {ncs0 output 1 0}
    NCS1 {ncs1 output 1 0}
    NCS2 {ncs2 output 1 0}
    NCS3 {ncs3 output 1 0}
  }
  SENS0 {
    SCK {pa[23] input 0 0}
    SD0 {pa[24] input 0 0}
    SD1 {pa[25] input 0 0}
    SD2 {pa[26] input 0 0}
    SD3 {pa[27] input 0 0}
    SD4 {pa[28] input 0 0}
    SD5 {pa[29] input 0 0}
    SD6 {pa[30] input 0 0}
    SD7 {pa[31] input 0 0}
    SEN0 {pa[15] input 0 0}
    SEN1 {pa[16] input 0 0}
  }
  SPI0 {
    NPCS0 {spi0_npcs0 inout 1 0}
    NPCS1 {spi0_npcs1 output 1 0}
    NPCS2 {spi0_npcs2 output 1 0}
    NPCS3 {spi0_npcs3 output 1 0}
    MOSI {spi0_mosi inout 1 0}
    MISO {spi0_miso inout 1 0}
    SPCK {spi0_spck inout 1 0}
  }
  SRAM0 {
    A0 {a0_nbs0 output 1 0}
    A1 {a1 output 1 0}
    A2 {a2 output 1 0}
    A3 {a3 output 1 0}
    A4 {a4 output 1 0}
    A5 {a5 output 1 0}
    A6 {a6 output 1 0}
    A7 {a7 output 1 0}
    A8 {a8 output 1 0}
    A9 {a9 output 1 0}
    A10 {a10 output 1 0}
    A11 {a11 output 1 0}
    A12 {a12 output 1 0}
    A13 {a13 output 1 0}
    A14 {a14 output 1 0}
    A15 {a15 output 1 0}
    A16 {a16 output 1 0}
    A17 {a17 output 1 0}
    A18 {a18 output 1 0}
    A19 {a19 output 1 0}
    A20 {a20 output 1 0}
    A21 {a21_nandale output 1 0}
    A22 {a22_nandcle output 1 0}
    A23 {a23 output 1 0}
    D0 {d0 inout 1 0}
    D1 {d1 inout 1 0}
    D2 {d2 inout 1 0}
    D3 {d3 inout 1 0}
    D4 {d4 inout 1 0}
    D5 {d5 inout 1 0}
    D6 {d6 inout 1 0}
    D7 {d7 inout 1 0}
    NRD {nrd output 1 0}
    NCS0 {ncs0 output 1 0}
    NCS1 {ncs1 output 1 0}
    NCS2 {ncs2 output 1 0}
    NCS3 {ncs3 output 1 0}
    NWR0 {nwr0_nwe output 1 0}
    NBS0 {a0_nbs0 output 1 0}
  }
  SSC0 {
    TK {tk inout 1 0}
    TD {td output 1 0}
    TF {tf inout 1 0}
    RK {rk inout 1 0}
    RD {rd input 1 0}
    RF {rf inout 1 0}
  }
}
