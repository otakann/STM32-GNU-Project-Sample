#
#	Makefile of embedded develop cmsis layer
#	CMSIS
#

.PHONY			: cmsisrtos cleancmsisrtos target cleantarget

cmsisrtos		:
	make -C $(CMSIS_RTOS_DIR) all && make -C $(CMSIS_RTOS_DIR) install

cleancmsisrtos	:
	make -C $(CMSIS_RTOS_DIR) clean

target			:
	make -C $(CMSIS_DEV_DIR) all && make -C $(CMSIS_DEV_DIR) install

cleantarget		:
	make -C $(CMSIS_DEV_DIR) clean

