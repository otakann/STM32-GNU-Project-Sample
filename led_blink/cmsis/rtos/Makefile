#
#	Makefile of CMSIS-RTOS2 kernel
#	libcmsisrtos.a
#

TOP_DIR			=	$(PWD)/
TOOLPATH_DIR	?= 	$(TOP_DIR)../../../../arm-none-eabi-toolchain/gcc-arm-none-eabi-5_4-2016q3/bin/
OUTPUT_DIR		?= 	$(TOP_DIR)../../output/
CORE_RTOS_DIR	?= 	$(TOP_DIR)../../package/freertos/
CMSIS_RTOS_DIR	?=	$(TOP_DIR)../rtos/
WRAP_RTOS_DIR	?=	$(TOP_DIR)src/wrapper_FreeRTOS/
CMSIS_DEV_DIR	?=	$(TOP_DIR)../device/

CROSS_COMPILE	?=	$(TOOLPATH_DIR)arm-none-eabi-
CC				=	$(CROSS_COMPILE)gcc
AR				=	$(CROSS_COMPILE)ar

FLOAT_TYPE		?=	-mfloat-abi=softfp -mfpu=fpv4-sp-d16

VERSION			?=	RELEASE

INCLUDES		=	-I$(CORE_RTOS_DIR)inc \
					-I$(CMSIS_RTOS_DIR)inc \
					-I$(CMSIS_DEV_DIR)inc

OBJS			=	cmsis_os2_kernel.o \
					cmsis_os2_thread.o \
					cmsis_os2_threadflag.o \
					cmsis_os2_wait.o \
					cmsis_os2_timer.o \
					cmsis_os2_eventflag.o \
					cmsis_os2_mutex.o \
					cmsis_os2_semaphore.o \
					cmsis_os2_memorypool.o \
					cmsis_os2_messagequeue.o

SOURCES			=	$(WRAP_RTOS_DIR)cmsis_os2_kernel.c \
					$(WRAP_RTOS_DIR)cmsis_os2_thread.c \
					$(WRAP_RTOS_DIR)cmsis_os2_threadflag.c \
					$(WRAP_RTOS_DIR)cmsis_os2_wait.c \
					$(WRAP_RTOS_DIR)cmsis_os2_timer.c \
					$(WRAP_RTOS_DIR)cmsis_os2_eventflag.c \
					$(WRAP_RTOS_DIR)cmsis_os2_mutex.c \
					$(WRAP_RTOS_DIR)cmsis_os2_semaphore.c \
					$(WRAP_RTOS_DIR)cmsis_os2_memorypool.c \
					$(WRAP_RTOS_DIR)cmsis_os2_messagequeue.c

TARGET			=	libcmsisrtos.a

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

