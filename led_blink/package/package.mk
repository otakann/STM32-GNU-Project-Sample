#
#	Makefile of embedded develop package
#	Package
#

.PHONY			: package cleanpackage corertos cleancorertos lldriver cleanlldriver

lldriver		:
	make -C $(LLDRIVER_DIR) all && make -C $(LLDRIVER_DIR) install

cleanlldriver	:
	make -C $(LLDRIVER_DIR) clean

corertos		:
	make -C $(CORE_RTOS_DIR) all && make -C $(CORE_RTOS_DIR) install

cleancorertos	:
	make -C $(CORE_RTOS_DIR) clean

package			: lldriver corertos
    
cleanpackage	: cleanlldriver cleancorertos 

