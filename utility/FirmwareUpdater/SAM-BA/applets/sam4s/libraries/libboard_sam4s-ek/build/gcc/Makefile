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

# Makefile for compiling libboard
SERIE = sam4s
BOARD = $(SERIE)_ek

SUBMAKE_FILES=debug.mk gcc.mk iar.mk mdk.mk release.mk win.mk linux.mk sam4s.mk
SUBMAKE_OPTIONS=--no-builtin-rules --no-builtin-variables
SUBMAKE_VARS=

#-------------------------------------------------------------------------------
# Rules
#-------------------------------------------------------------------------------

all: $(BOARD)

.PHONY: $(BOARD)
$(BOARD):
	@echo --- Making $(BOARD)
	@$(MAKE) DEBUG=1 $(SUBMAKE_OPTIONS) -f $(BOARD).mk
	@$(MAKE) $(SUBMAKE_OPTIONS) -f $(BOARD).mk

.PHONY: clean
clean:
	@echo --- Cleaning $(BOARD)
	@$(MAKE) $(SUBMAKE_OPTIONS) -f $(BOARD).mk $@
	@$(MAKE) DEBUG=1 $(SUBMAKE_OPTIONS) -f $(BOARD).mk $@


