
# Compilation tools
AR = iarchive.exe
CC = iccarm.exe
LD = ilinkarm.exe
SIZE = 
OBJCOPY = 

# Flags

CFLAGS += $(OPTIMIZATION) $(INCLUDES) -D$(CHIP_NAME) -DTRACE_LEVEL=$(TRACE_LEVEL)

ASFLAGS = $(OPTIMIZATION) $(INCLUDES) -D$(CHIP_NAME) -D__ASSEMBLY__

LDFLAGS = 
