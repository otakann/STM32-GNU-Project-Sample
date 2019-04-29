#
#	Makefile of STM32 with FreeRTOS platform Sample project
#	Led blink
#

CC						=	$(CROSS_COMPILE)gcc
AS						=	$(CROSS_COMPILE)gcc -x assembler-with-cpp
CP						=	$(CROSS_COMPILE)objcopy
AR						=	$(CROSS_COMPILE)ar
SIZE					=	$(CROSS_COMPILE)size

INCLUDES				=	-I$(LOW_LAYER_DIR) \
							-I$(CMSIS_DEV_DIR)inc \
							-I$(LLDRIVER_DIR)inc

AOBJS					=	startup_stm32l475xx.o

COBJS					=	system_stm32l4xx.o \
							stm32l4xx_it.o \
							main.o

OBJS					=	$(AOBJS) $(COBJS)

ASOURCES				=	$(LOW_LAYER_DIR)startup_stm32l475xx.s

CSOURCES				=	$(CMSIS_DIR)src/system_stm32l4xx.c \
							$(LOW_LAYER_DIR)stm32l4xx_it.c \
							$(LOW_LAYER_DIR)main.c

LIBS					=	$(OUTPUT_DIR)lib/*.a 

LIB_DIR					=	-L$(LOW_LAYER_DIR) \
							-L$(OUTPUT_DIR)lib 

TARGET_ELF				=	$(TARGET).elf
TARGET_HEX				=	$(TARGET).hex
TARGET_SIZ				=	$(TARGET).siz
TARGET_MAP				=	$(TARGET).map
TARGET_BIN				=	$(TARGET).bin

ifeq ($(VERSION), DEBUG)
DEBUG_CFLAGS			=	-g3 -O0 
else
DEBUG_CFLAGS			=	-s -O2 
endif

#
# Add application source here
#
INCLUDES				+=	-I$(APP_DIR)api/inc

CFLAGS					=	-mcpu=cortex-m4 \
							-mthumb \
							$(FLOAT_TYPE) \
							-fmessage-length=0 \
							-fsigned-char \
							-ffunction-sections \
							-fdata-sections \
							-ffreestanding \
							-fno-move-loop-invariants \
							-fno-strict-aliasing \
							-Werror \
							-Wall \
							-Wextra \
							-std=c99 \
							$(DEBUG_CFLAGS) $(INCLUDES)

DFLAGS					=	$(GLOBAL_DEFINE)

LDFLAGS					=	-mcpu=cortex-m4 \
							-mthumb \
							-T STM32L475VGTx_FLASH.ld \
							-Xlinker --gc-sections \
							-Xlinker "-(" \
							$(LIBS) \
							-Xlinker "-)" \
							$(LIB_DIR) \
							-Wl,-Map,$(TARGET_MAP) \
							--specs=nano.specs

#
# Compile Menu
#

.PHONY			: all clean install $(TARGET_ELF) $(TARGET_HEX) $(TARGET_BIN) $(TARGET_SIZ)

all				: $(TARGET_SIZ) $(TARGET_HEX) $(TARGET_BIN)
    
$(TARGET_HEX)	: $(TARGET_ELF)
	$(CP) -O ihex $(TARGET_ELF) $(TARGET_HEX)

$(TARGET_BIN)	: $(TARGET_ELF)
	$(CP) -O binary -S $(TARGET_ELF) $(TARGET_BIN)

$(TARGET_SIZ)	: $(TARGET_ELF)
	$(SIZE) --format=berkeley $(TARGET_ELF)

$(TARGET_ELF)	: $(OBJS)
	$(CC) -o $(TARGET_ELF) $(OBJS) $(LDFLAGS)

${AOBJS} 		: ${ASOURCES}
	$(AS) $(CFLAGS) $(DFLAGS) -c $(ASOURCES)

${COBJS} 		: ${CSOURCES}
	$(CC) $(CFLAGS) $(DFLAGS) -c $(CSOURCES)

install			:
	if [ ! -d $(OUTPUT_DIR) ]; then mkdir -p $(OUTPUT_DIR); fi;
	cp -rfp $(TARGET_HEX) $(OUTPUT_DIR)
	cp -rfp $(TARGET_BIN) $(OUTPUT_DIR)
	cp -rfp $(TARGET_MAP) $(OUTPUT_DIR)
    
clean			:
	rm -f *.o *.gcno *.gcda *.gcov *.Z* *~ $(TARGET_ELF) $(TARGET_HEX) $(TARGET_BIN) $(TARGET_MAP)
	rm -rf $(OUTPUT_DIR)$(TARGET_HEX)
	rm -rf $(OUTPUT_DIR)$(TARGET_BIN)
	rm -rf $(OUTPUT_DIR)$(TARGET_MAP)

