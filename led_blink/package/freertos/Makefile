#
#	Makefile of FreeRTOS kernel
#	libcorertos.a
#

TOP_DIR			=	$(PWD)/
TOOLPATH_DIR	?= 	$(TOP_DIR)../../../../arm-none-eabi-toolchain/gcc-arm-none-eabi-5_4-2016q3/bin/
OUTPUT_DIR		?= 	$(TOP_DIR)../../output/
CORE_RTOS_DIR	?= 	$(TOP_DIR)

CROSS_COMPILE	?=	$(TOOLPATH_DIR)arm-none-eabi-
CC				=	$(CROSS_COMPILE)gcc
AR				=	$(CROSS_COMPILE)ar

FLOAT_TYPE		?=	-mfloat-abi=softfp -mfpu=fpv4-sp-d16

VERSION			?=	RELEASE

INCLUDES		=	-I$(RTOS_DIR)inc

OBJS			=	croutine.o \
					event_groups.o \
					list.o \
					port.o \
					queue.o \
					stream_buffer.o \
					tasks.o \
					timers.o

SOURCES			=	$(RTOS_DIR)src/croutine.c \
					$(RTOS_DIR)src/event_groups.c \
					$(RTOS_DIR)src/list.c \
					$(RTOS_DIR)src/port.c \
					$(RTOS_DIR)src/queue.c \
					$(RTOS_DIR)src/stream_buffer.c \
					$(RTOS_DIR)src/tasks.c \
					$(RTOS_DIR)src/timers.c

TARGET			=	libcorertos.a

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

#
# Compile Menu
#

.PHONY		: all clean install $(TARGET)

all			: $(TARGET)

$(TARGET)	: $(OBJS)
	$(AR) -crv $(TARGET) $(OBJS)

${OBJS} 	: ${SOURCES}
	$(CC) $(CFLAGS) -c $(SOURCES)
    
clean		:
	rm -f *.o *.gcno *.gcda *.gcov *.Z* *~ $(TARGET)
	rm -rf $(OUTPUT_DIR)lib/

install		:
	if [ ! -d $(OUTPUT_DIR)lib/ ]; then mkdir -p $(OUTPUT_DIR)lib/; fi;
	cp -rfp $(TARGET) $(OUTPUT_DIR)lib/

