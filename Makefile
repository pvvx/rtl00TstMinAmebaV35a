all: ram_all

.PHONY: ram_all
ram_all: 
	@$(MAKE) -f sdkbuild.mk
	@$(MAKE) -f flasher.mk genbin23 
	
.PHONY: mp
mp: 
	@$(MAKE) -f sdkbuild.mk mp
	@$(MAKE) -f flasher.mk genbin23 

.PHONY: clean clean_all
clean:
	@$(MAKE) -f sdkbuild.mk clean
clean_all:
	@$(MAKE) -f sdkbuild.mk clean_all
	
.PHONY: flash debug ramdebug setup 
setup: toolchain
	@$(MAKE) -f sdkbuild.mk $(MAKECMDGOALS)

flashburn: 
	@$(MAKE) -f flasher.mk flashburn
	
debug: 
	@$(MAKE) -f application.mk debug	

ramdebug: 
	@$(MAKE) -f application.mk ramdebug	

reset: 
	@make -f flasher.mk reset 

test: 
	@make -f flasher.mk test 

readfullflash:
	@make -f flasher.mk readfullflash 
