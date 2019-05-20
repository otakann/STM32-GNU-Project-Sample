#
#	Makefile of application api
#	libappapi.a
#

TOP_DIR				=	$(PWD)/
TOOLPATH_DIR		?= 	$(TOP_DIR)../../../../arm-none-eabi-toolchain/gcc-arm-none-eabi-5_4-2016q3/bin/
OUTPUT_DIR			?= 	$(TOP_DIR)../../output/
CMSIS_RTOS_DIR		=	$(TOP_DIR)../../cmsis/rtos/
CORE_RTOS_DIR		= 	$(TOP_DIR)../../package/freertos/
NT_SHELL_DIR		=	$(TOP_DIR)../../package/ntshell/
CLIB_DIR			=	$(TOP_DIR)../../package/clib/
VL53L0XDRIVER_DIR	=	$(TOP_DIR)../../package/vl53l0x_driver/

API_DIR				?=	$(TOP_DIR)
WRAP_DIR			=	$(TOP_DIR)../wrapper/
CMD_DIR				=	$(TOP_DIR)../cmd/
MSM_DIR				=	$(TOP_DIR)../msm/
PSM_DIR				=	$(TOP_DIR)../psm/
DATA_DIR			=	$(TOP_DIR)../data/

CROSS_COMPILE		?=	$(TOOLPATH_DIR)arm-none-eabi-
CC					=	$(CROSS_COMPILE)gcc
AR					=	$(CROSS_COMPILE)ar

FLOAT_TYPE			?=	-mfloat-abi=soft

VERSION				?=	RELEASE

GLOBAL_DEFINE		?=

GLOBAL_INCLUDES		?=	-I$(CORE_RTOS_DIR)inc \
						-I$(CMSIS_RTOS_DIR)inc \
						-I$(NT_SHELL_DIR)core \
						-I$(NT_SHELL_DIR)util \
						-I$(CLIB_DIR)inc \
						-I$(VL53L0XDRIVER_DIR)inc \
						-I$(WRAP_DIR)inc \
						-I$(CMD_DIR)interface \
						-I$(PSM_DIR)interface \
						-I$(DATA_DIR)inc \
						-I$(MSM_DIR)inc

INCLUDES			=	$(GLOBAL_INCLUDES)

OBJS				=	application_api.o

SOURCES				=	$(API_DIR)src/application_api.c

TARGET				=	libappapi.a

ifeq ($(VERSION), DEBUG)
DEBUG_CFLAGS		=	-g3 -O0
else
DEBUG_CFLAGS		=	-s -O2
endif

CFLAGS				=	-mcpu=cortex-m4 \
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

DFLAGS				=	$(GLOBAL_DEFINE)

#
# Compile Menu
#

.PHONY		: all clean install $(TARGET)

all			: $(TARGET)

$(TARGET)	: $(OBJS)
	$(AR) -crv $(TARGET) $(OBJS)

${OBJS} 	: ${SOURCES}
	$(CC) $(CFLAGS) $(DFLAGS) -c $(SOURCES)
    
clean		:
	rm -f *.o *.gcno *.gcda *.gcov *.Z* *~ $(TARGET)
	rm -rf $(OUTPUT_DIR)lib/

install		:
	if [ ! -d $(OUTPUT_DIR)lib/ ]; then mkdir -p $(OUTPUT_DIR)lib/; fi;
	cp -rfp $(TARGET) $(OUTPUT_DIR)lib/

