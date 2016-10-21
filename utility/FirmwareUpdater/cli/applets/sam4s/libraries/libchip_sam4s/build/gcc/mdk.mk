
# Compilation tools
AR = armar.exe
CC = armcc.exe
LD = armar.exe
SIZE = 
OBJCOPY = 

# Flags

CFLAGS += $(OPTIMIZATION) $(INCLUDES) -D$(CHIP_NAME) -DTRACE_LEVEL=$(TRACE_LEVEL)

ASFLAGS = $(OPTIMIZATION) $(INCLUDES) -D$(CHIP_NAME) -D__ASSEMBLY__

LDFLAGS = 
