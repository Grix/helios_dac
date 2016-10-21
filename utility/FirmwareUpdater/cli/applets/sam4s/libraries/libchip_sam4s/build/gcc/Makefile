# ----------------------------------------------------------------------------
#         SAM Software Package License
# ----------------------------------------------------------------------------
# Copyright (c) 2011, Atmel Corporation
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# - Redistributions of source code must retain the above copyright notice,
# this list of conditions and the disclaimer below.
#
# Atmel's name may not be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
# OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ----------------------------------------------------------------------------

SERIE = sam4s

# Makefile for compiling libchip

SUBMAKE_FILES=debug.mk gcc.mk iar.mk mdk.mk release.mk win.mk linux.mk sam4s.mk
#SUBMAKE_OPTIONS=--no-builtin-rules --no-builtin-variables -d -p
SUBMAKE_OPTIONS=--no-builtin-rules --no-builtin-variables
SUBMAKE_VARS=

#-------------------------------------------------------------------------------
# Rules
#-------------------------------------------------------------------------------

all: $(SERIE)4 $(SERIE)8 $(SERIE)16

$(SERIE)4: libchip_$(SERIE)4_gcc_dbg.a libchip_$(SERIE)4_gcc_rel.a

libchip_$(SERIE)4_gcc_dbg.a:
	@echo --- Making $@
	@$(MAKE) CHIP=$(SERIE)4 DEBUG=1 $(SUBMAKE_OPTIONS) -f $(SERIE).mk

libchip_$(SERIE)4_gcc_rel.a:
	@echo --- Making $@
	@$(MAKE) CHIP=$(SERIE)4 $(SUBMAKE_OPTIONS) -f $(SERIE).mk

$(SERIE)8: libchip_$(SERIE)8_gcc_dbg.a libchip_$(SERIE)8_gcc_rel.a

libchip_$(SERIE)8_gcc_dbg.a:
	@echo --- Making $@
	@$(MAKE) CHIP=$(SERIE)8 DEBUG=1 $(SUBMAKE_OPTIONS) -f $(SERIE).mk

libchip_$(SERIE)8_gcc_rel.a:
	@echo --- Making $@
	@$(MAKE) CHIP=$(SERIE)8 $(SUBMAKE_OPTIONS) -f $(SERIE).mk

$(SERIE)16: libchip_$(SERIE)16_gcc_dbg.a libchip_$(SERIE)16_gcc_rel.a

libchip_$(SERIE)16_gcc_dbg.a:
	@echo --- Making $@
	@$(MAKE) CHIP=$(SERIE)16 DEBUG=1 $(SUBMAKE_OPTIONS) -f $(SERIE).mk

libchip_$(SERIE)16_gcc_rel.a:
	@echo --- Making $@
	@$(MAKE) CHIP=$(SERIE)16 $(SUBMAKE_OPTIONS) -f $(SERIE).mk

.PHONY: clean
clean:
	@echo --- Cleaning $(SERIE)4
	@$(MAKE) CHIP=$(SERIE)4 $(SUBMAKE_OPTIONS) -f $(SERIE).mk $@
	@$(MAKE) CHIP=$(SERIE)4 DEBUG=1 $(SUBMAKE_OPTIONS) -f $(SERIE).mk $@

	@echo --- Cleaning $(SERIE)8
	@$(MAKE) CHIP=$(SERIE)8 $(SUBMAKE_OPTIONS) -f $(SERIE).mk $@
	@$(MAKE) CHIP=$(SERIE)8 DEBUG=1 $(SUBMAKE_OPTIONS) -f $(SERIE).mk $@

	@echo --- Cleaning $(SERIE)16
	@$(MAKE) CHIP=$(SERIE)16 $(SUBMAKE_OPTIONS) -f $(SERIE).mk $@
	@$(MAKE) CHIP=$(SERIE)16 DEBUG=1 $(SUBMAKE_OPTIONS) -f $(SERIE).mk $@

