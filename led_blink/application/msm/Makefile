#
#	Makefile of machine status module
#	libappmsm.a
#

TOP_DIR			=	$(PWD)/
TOOLPATH_DIR	?= 	$(TOP_DIR)../../../../arm-none-eabi-toolchain/gcc-arm-none-eabi-5_4-2016q3/bin/
OUTPUT_DIR		?= 	$(TOP_DIR)../../output/
CORE_RTOS_DIR	?= 	$(TOP_DIR)../../package/freertos/
CMSIS_RTOS_DIR	?=	$(TOP_DIR)../../cmsis/rtos/
CMSIS_DEV_DIR	?=	$(TOP_DIR)../../cmsis/device/
LLDRIVER_DIR	?=	$(TOP_DIR)../../package/ll_driver/
APP_DIR			?=	$(TOP_DIR)../
MSM_DIR			?=	$(APP_DIR)msm/

CROSS_COMPILE	?=	$(TOOLPATH_DIR)arm-none-eabi-
CC				=	$(CROSS_COMPILE)gcc
AR				=	$(CROSS_COMPILE)ar

FLOAT_TYPE		?=	-mfloat-abi=soft

VERSION			?=	RELEASE

GLOBAL_DEFINE	?=	-DUSE_FULL_LL_DRIVER

INCLUDES		=	-I$(CMSIS_RTOS_DIR)inc \
					-I$(LLDRIVER_DIR)inc \
					-I$(CMSIS_DEV_DIR)inc

OBJS			=	msm_api.o

SOURCES			=	$(MSM)src/msm_api.c

TARGET			=	libappmsm.a

ifeq ($(VERSION), DEBUG)
DEBUG_CFLAGS	=	-g3 -O0
else
DEBUG_CFLAGS	=	-s -O2
endif

CFLAGS			=	-mcpu=cortex-m4 \
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

DFLAGS			=	$(GLOBAL_DEFINE)

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

