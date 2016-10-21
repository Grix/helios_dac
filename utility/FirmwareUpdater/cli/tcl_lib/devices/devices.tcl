#  ----------------------------------------------------------------------------
#          SAM Software Package License
#  ----------------------------------------------------------------------------
#  Copyright (c) 2012, Atmel Corporation
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


# CIDR addresses
# 0x400E0740 for AT91SAM3U, SAM4S
# 0x400E0940 for SAM3X
# 0xFFFFEE40 for AT91SAM9263 and AT91CAP9
# 0xFFFFF240 for other devices
set cidr_addresses [list 0xfffff240 0xffffee40]
set sam3_cidr_addresses [list 0x400e0640 0x400e0740 0x400E0940]



# When reading the chip ID on the device, SAM-BA masks the 5 LS bits (device version)
# and then compares it with the following array. So the chip IDs written here must
# have the version field at 0.
array set devices {
    0x283A0760 at91sam3a2
    0x283B0960 at91sam3a4
    0x283E0A60 at91sam3a8
    0x284A0760 at91sam3x2
    0x285A0760 at91sam3x2
    0x286A0760 at91sam3x2
    0x284B0960 at91sam3x4
    0x285B0960 at91sam3x4
    0x286B0960 at91sam3x4
    0x284E0A60 at91sam3x8
    0x285E0A60 at91sam3x8
    0x286E0A60 at91sam3x8
    0x283A0730 at91sam3a2
    0x283B0930 at91sam3a4
    0x283E0A30 at91sam3a8
    0x284A0730 at91sam3x2
    0x285A0730 at91sam3x2
    0x286A0730 at91sam3x2
    0x284B0930 at91sam3x4
    0x285B0930 at91sam3x4
    0x286B0930 at91sam3x4
    0x284E0A30 at91sam3x8
    0x285E0A30 at91sam3x8
    0x286E0A30 at91sam3x8
    0x28890560 at91sam3s1
    0x28990560 at91sam3s1
    0x28a90560 at91sam3s1
    0x288a0760 at91sam3s2
    0x289a0760 at91sam3s2
    0x28aa0760 at91sam3s2
    0x29540960 at91sam3s4
    0x29440960 at91sam3s4
    0x29340960 at91sam3s4   
    0x28800960 at91sam3s4
    0x28900960 at91sam3s4
    0x28a00960 at91sam3s4
    0x28ab0a60 at91sam3s8
    0x289b0a60 at91sam3s8
    0x288b0a60 at91sam3s8
    0x28ac0c60 at91sam3s16
    0x289c0c60 at91sam3s16
    0x288c0c60 at91sam3s16
    0x29ab0a60 at91sam3sd8
    0x299b0a60 at91sam3sd8
    0x298b0a60 at91sam3sd8
    0x28090560 at91sam3u1
    0x28190560 at91sam3u1
    0x280a0760 at91sam3u2
    0x281a0760 at91sam3u2
    0x28000960 at91sam3u4
    0x28100960 at91sam3u4
    0x5a455040 at91sam3u4
    0x29540960 at91sam3n4
    0x29440960 at91sam3n4
    0x29340960 at91sam3n4
    0x29590760 at91sam3n2
    0x29490760 at91sam3n2
    0x29390760 at91sam3n2
    0x29580560 at91sam3n1
    0x29480560 at91sam3n1
    0x29380560 at91sam3n1
	0xa3cc0ce0 at91sam4e16
	0x288b09e0 at91sam4s4
    0x289b09e0 at91sam4s4
    0x28ab09e0 at91sam4s4
    0x288c0ae0 at91sam4s8
    0x289c0ae0 at91sam4s8
    0x28ac0ae0 at91sam4s8
    0x288c0ce0 at91sam4s16
    0x289c0ce0 at91sam4s16
    0x28ac0ce0 at91sam4s16
    0x29a70ee0 at91sam4sd32
    0x29970ee0 at91sam4sd32
    0x170a0940 at91sam7a3
    0x260a0940 at91sam7a3
    0x27330540 at91sam7l64
    0x27330740 at91sam7l128
    0x27280340 at91sam7s32,at91sam7se321
    0x27080340 at91sam7s32
    0x27090540 at91sam7s64
    0x270a0740 at91sam7s128
    0x270c0740 at91sam7s128
    0x270b0940 at91sam7s256
    0x270d0940 at91sam7s256
    0x270b0a40 at91sam7s512
    0x27280340 at91sam7se32
    0x272a0940 at91sam7se256
    0x272a0a40 at91sam7se512
    0x27050240 at91sam7s16,at91sam7s161
    0x275a0740 at91sam7x128
    0x275b0940 at91sam7x256
    0x275c0a40 at91sam7x512
    0x271a0740 at91sam7xc128
    0x271b0940 at91sam7xc256
    0x271c0a40 at91sam7xc512
    0x019803a0 at91sam9260
    0x019703a0 at91sam9261
    0x019607a0 at91sam9263
    0x819903a0 at91sam9g10
    0x019903a0 at91sam9g10
    0x019905a0 at91sam9g20
    0x819a05a0 at91sam9g15,at91sam9g25,at91sam9g35,at91sam9x25,at91sam9x35
    0x819b05a0 at91sam9g45,at91sam9m10
    0x819a07a0 at91sam9n12
    0x019b03a0 at91sam9rl64
    0x329993a0 at91sam9xe128
    0x329973a0 at91sam9xe128
    0x329a93a0 at91sam9xe256
    0x329a73a0 at91sam9xe512
    0x329a53a0 at91sam9xe512
    0x329aa3a0 at91sam9xe512
    0x329953a0 at91sam9xe512
    0x83770940 at91cap7
    0x039a03a0 at91cap9
}

array set EmbeddedProcessor {
    0x01 ARM946ES
    0x02 ARM7TDMI
    0x03 CM3
    0x04 ARM920T
    0x05 ARM926EJS
    0x06 CA5
    0x07 CM4
}

array set ArchitectureIdentifier {
    0x19 AT91SAM9xx
    0x29 AT91SAM9XExx
    0x34 AT91x34
    0x37 CAP7
    0x39 CAP9
    0x3b CAP11
	0x3c SAM4E
    0x40 AT91x40
    0x42 AT91x42
    0x55 AT91x55
    0x60 AT91SAM7Axx
    0x61 AT91SAM7AQxx
    0x63 AT91x63
    0x70 AT91SAM7Sxx
    0x71 AT91SAM7XCxx
    0x72 AT91SAM7SExx
    0x73 AT91SAM7Lxx
    0x75 AT91SAM7Xxx
    0x76 AT91SAM7SLxx
    0x80 ATSAM3UxC
    0x81 ATSAM3UxE
    0x83 ATSAM3AxC
    0x84 ATSAM3XxC
    0x85 ATSAM3XxE
    0x86 ATSAM3XxG
    0x88 ATSAM3SxA
    0x89 ATSAM3SxB
    0x8a ATSAM3SxC
    0x92 AT91x92
    0x93 ATSAM3NA
    0x94 ATSAM3NB
    0x95 ATSAM3NC
    0x98 ATSAM3SDxA
    0x99 ATSAM3SDxB
    0x9a ATSAM3SDxC
    0xa5 SAMA5
    0xf0 AT75Cxx
}
