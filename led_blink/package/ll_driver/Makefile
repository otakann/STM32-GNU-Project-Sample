#
#	Makefile of STM32 ll_driver
#	liblldriver.a
#

TOP_DIR			=	$(PWD)/
TOOLPATH_DIR	?=	$(TOP_DIR)../../../../arm-none-eabi-toolchain/gcc-arm-none-eabi-5_4-2016q3/bin/
OUTPUT_DIR		?=	$(TOP_DIR)../../output/
LLDRIVER_DIR	?=	$(TOP_DIR)
CMSIS_DEV_DIR	?=	$(TOP_DIR)../../cmsis/device/

CROSS_COMPILE	?=	$(TOOLPATH_DIR)arm-none-eabi-
CC				=	$(CROSS_COMPILE)gcc
AR				=	$(CROSS_COMPILE)ar

FLOAT_TYPE		?=	-mfloat-abi=soft

VERSION			?=	RELEASE

GLOBAL_DEFINE	?=	-DUSE_FULL_LL_DRIVER

INCLUDES		=	-I$(LLDRIVER_DIR)inc \
					-I$(CMSIS_DEV_DIR)inc

OBJS			=	stm32l4xx_ll_adc.o \
					stm32l4xx_ll_comp.o \
					stm32l4xx_ll_crc.o \
					stm32l4xx_ll_crs.o \
					stm32l4xx_ll_dac.o \
					stm32l4xx_ll_dma.o \
					stm32l4xx_ll_dma2d.o \
					stm32l4xx_ll_exti.o \
					stm32l4xx_ll_gpio.o \
					stm32l4xx_ll_i2c.o \
					stm32l4xx_ll_lptim.o \
					stm32l4xx_ll_lpuart.o \
					stm32l4xx_ll_opamp.o \
					stm32l4xx_ll_pwr.o \
					stm32l4xx_ll_rcc.o \
					stm32l4xx_ll_rng.o \
					stm32l4xx_ll_rtc.o \
					stm32l4xx_ll_spi.o \
					stm32l4xx_ll_swpmi.o \
					stm32l4xx_ll_tim.o \
					stm32l4xx_ll_usart.o \
					stm32l4xx_ll_utils.o

SOURCES			=	$(LLDRIVER_DIR)src/stm32l4xx_ll_adc.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_comp.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_crc.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_crs.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_dac.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_dma.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_dma2d.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_exti.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_gpio.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_i2c.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_lptim.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_lpuart.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_opamp.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_pwr.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_rcc.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_rng.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_rtc.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_spi.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_swpmi.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_tim.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_usart.c \
					$(LLDRIVER_DIR)src/stm32l4xx_ll_utils.c

TARGET			=	liblldriver.a

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
					-Wno-unused-parameter \
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

