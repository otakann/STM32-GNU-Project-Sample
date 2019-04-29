#
#	Makefile of Embedded system develop project
#	Led blink
#

export TARGET			=	led_blink

TOP_DIR					=	$(PWD)/
TOOLPATH_DIR			=	/usr/local/install/gcc-arm-none-eabi-8-2018-q4-major/bin/
PACKAGE_DIR				=	$(TOP_DIR)package/
CMSIS_DIR				=	$(TOP_DIR)cmsis/

export OUTPUT_DIR		=	$(TOP_DIR)output/
export LLDRIVER_DIR		=	$(PACKAGE_DIR)ll_driver/
export CORE_RTOS_DIR	= 	$(PACKAGE_DIR)freertos/
export CMSIS_RTOS_DIR	= 	$(CMSIS_DIR)rtos/
export CMSIS_DEV_DIR	=	$(CMSIS_DIR)device/
export LOW_LAYER_DIR	=	$(TOP_DIR)lowlayer/
export APP_DIR			=	$(TOP_DIR)application/
export WRAP_RTOS_DIR	?=	$(CMSIS_RTOS_DIR)src/wrapper_FreeRTOS/

export VERSION			?=	RELEASE
export GLOBAL_DEFINE	=	-DUSE_FULL_LL_DRIVER
export FLOAT_TYPE		?=	-mfloat-abi=softfp -mfpu=fpv4-sp-d16

export CROSS_COMPILE	=	$(TOOLPATH_DIR)arm-none-eabi-

.PHONY			: all clean

all				: package application cmsisrtos 
	make target

clean			: cleanpackage cleantarget cleanapplication cleancmsisrtos
	rm -rf $(OUTPUT_DIR)

include $(PACKAGE_DIR)package.mk
include $(CMSIS_DIR)cmsis.mk
include $(APP_DIR)application.mk

