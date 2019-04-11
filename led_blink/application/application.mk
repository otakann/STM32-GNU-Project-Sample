#
#	Makefile of embedded develop application
#	Application
#

export WRAP_DIR		=	$(APP_DIR)wrapper/
export MSM_DIR		=	$(APP_DIR)msm/
export API_DIR		=	$(APP_DIR)api/

.PHONY				: application cleanapplication api cleanapi msm cleanmsm

api					:
	make -C $(API_DIR) && make -C $(API_DIR) install

cleanapi			:
	make -C $(API_DIR) clean

msm					:
	make -C $(MSM_DIR) all && make -C $(MSM_DIR) install

cleanmsm			:
	make -C $(MSM_DIR) clean

application			: api msm
    
cleanapplication	: cleanapi cleanmsm 

