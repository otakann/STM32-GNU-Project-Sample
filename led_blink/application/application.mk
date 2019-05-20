#
#	Makefile of embedded develop application
#	Application
#

export WRAP_DIR			=	$(APP_DIR)wrapper/
export MSM_DIR			=	$(APP_DIR)msm/
export API_DIR			=	$(APP_DIR)api/
export GLOBAL_INCLUDES	=	-I$(CORE_RTOS_DIR)inc \
							-I$(CMSIS_RTOS_DIR)inc \
							-I$(CMSIS_DEV_DIR)inc \
							-I$(LLDRIVER_DIR)inc \
							-I$(WRAP_DIR)inc \
							-I$(MSM_DIR)inc \

.PHONY				: application cleanapplication api cleanapi wrap cleanwrap msm cleanmsm

api					:
	make -C $(API_DIR) && make -C $(API_DIR) install

cleanapi			:
	make -C $(API_DIR) clean

wrap				:
	make -C $(WRAP_DIR) && make -C $(WRAP_DIR) install

cleanwrap			:
	make -C $(WRAP_DIR) clean

msm					:
	make -C $(MSM_DIR) all && make -C $(MSM_DIR) install

cleanmsm			:
	make -C $(MSM_DIR) clean

application			: api wrap msm
    
cleanapplication	: cleanapi cleanwrap cleanmsm

