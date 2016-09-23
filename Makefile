all: ram_all

.PHONY: ram_all
ram_all: 
	@$(MAKE) -f sdkbuild.mk
	@$(MAKE) -f flasher.mk genbin23 
	
.PHONY: clean  clean_all
clean:
	@$(MAKE) -f sdkbuild.mk clean

clean_all:
	@$(MAKE) -f sdkbuild.mk clean_all
	
.PHONY:	debug ramdebug
debug: 
	@$(MAKE) -f application.mk debug	

ramdebug: 
	@$(MAKE) -f application.mk ramdebug	

.PHONY: flashburn runram reset test readfullflash
flashburn: 
	@$(MAKE) -f flasher.mk flashburn

runram: 
	@$(MAKE) --f flasher.mk runram

reset: 
	@make -f flasher.mk reset 

test: 
	@make -f flasher.mk test 

readfullflash:
	@make -f flasher.mk readfullflash 
