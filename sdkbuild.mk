
include sdkset.mk
include paths.mk

INCFLAGS = $(patsubst %,-I%,$(INCLUDES))

LIBFLAGS = $(addprefix -L,$(PATHLIBS)) $(addprefix -l,$(LIBS))

LFLAGS += -Wl,-Map=$(OBJ_DIR)/$(TARGET).map 

CFLAGS += $(INCFLAGS)

SRC_O = $(patsubst %.c,%.o,$(ADD_SRC_C)) $(patsubst %.c,%.o,$(SRC_C)) 
DRAM_O = $(patsubst %.c,%.o,$(DRAM_C))

SRC_C_LIST = $(ADD_SRC_C) $(SRC_C) $(DRAM_C) 
OBJ_LIST = $(addprefix $(OBJ_DIR)/,$(patsubst %.c,%.o,$(SRC_C_LIST))) 
DEPENDENCY_LIST = $(patsubst %.c,$(OBJ_DIR)/%.d,$(SRC_C_LIST))

TARGET?=build
OBJ_DIR?=build/obj
BIN_DIR?=build/bin

all: application

.PHONY: build_info
build_info:
	@echo \#define UTS_VERSION \"`date +%Y/%m/%d-%T`\" > .ver
	@echo \#define RTL8195AFW_COMPILE_TIME \"`date +%Y/%m/%d-%T`\" >> .ver
	@echo \#define RTL8195AFW_COMPILE_DATE \"`date +%Y%m%d`\" >> .ver
	@echo \#define RTL8195AFW_COMPILE_BY \"`id -u -n`\" >> .ver
	@echo \#define RTL8195AFW_COMPILE_HOST \"`$(HOSTNAME_APP)`\" >> .ver
	@if [ -x /bin/dnsdomainname ]; then \
		echo \#define RTL8195AFW_COMPILE_DOMAIN \"`dnsdomainname`\"; \
	elif [ -x /bin/domainname ]; then \
		echo \#define RTL8195AFW_COMPILE_DOMAIN \"`domainname`\"; \
	else \
		echo \#define RTL8195AFW_COMPILE_DOMAIN ; \
	fi >> .ver
	@echo \#define RTL195AFW_COMPILER \"gcc `$(CC) $(CFLAGS) -dumpversion | tr --delete '\r'`\" >> .ver
	@mv -f .ver project/realtek_ameba1_va0_example/inc/$@.h

.PHONY:	application 
application: prerequirement build_info $(SRC_O) $(DRAM_O) bootloader
	@echo "==========================================================="
	@echo "Link "$(TARGET)
#	@echo "==========================================================="
	@mkdir -p $(BIN_DIR)
	@$(LD) $(LFLAGS) -o $(OBJ_DIR)/$(TARGET).axf $(OBJ_LIST) $(OBJ_DIR)/ram_1.r.o $(LIBFLAGS) -T$(LDFILE)
	@$(OBJDUMP) -d $(OBJ_DIR)/$(TARGET).axf > $(OBJ_DIR)/$(TARGET).asm

.PHONY: bootloader	
bootloader:
	@echo "==========================================================="
	@echo "Make BootLoader (ram_1.p.bin, ram_1.r.bin)"
#	@echo "==========================================================="
	@mkdir -p $(BIN_DIR)
	@cp $(BOOTS)/ram_1.r.bin $(BIN_DIR)/ram_1.r.bin
	@cp $(BOOTS)/ram_1.p.bin $(BIN_DIR)/ram_1.p.bin
#	@chmod 777 $(OBJ_DIR)/ram_1.r.bin
	@$(OBJCOPY) --rename-section .data=.loader.data,contents,alloc,load,readonly,data -I binary -O elf32-littlearm -B arm $(BIN_DIR)/ram_1.r.bin $(OBJ_DIR)/ram_1.r.o

.PHONY:	prerequirement
prerequirement:
#	@$(file >DEPENDENCY_LIST.txt,$(DEPENDENCY_LIST))
	@echo "==========================================================="
	@echo "Compile "$(TARGET)
#	@echo "==========================================================="
	@mkdir -p $(OBJ_DIR)

$(SRC_O): %.o : %.c
	@echo $<
	@mkdir -p $(OBJ_DIR)/$(dir $@)
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $(OBJ_DIR)/$@
	@$(CC) -MM $(CFLAGS) $(INCFLAGS) $< -MT $@ -MF $(OBJ_DIR)/$(patsubst %.o,%.d,$@)

$(DRAM_O): %.o : %.c
	@echo $<
	@mkdir -p $(OBJ_DIR)/$(dir $@)
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $(OBJ_DIR)/$@
	@$(OBJCOPY) --prefix-alloc-sections .sdram $(OBJ_DIR)/$@
	@$(CC) -MM $(CFLAGS) $(INCFLAGS) $< -MT $@ -MF $(OBJ_DIR)/$(patsubst %.o,%.d,$@)
	
-include $(DEPENDENCY_LIST)

VPATH:=$(OBJ_DIR)

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@rm -f $(patsubst %.c,%.d,$(SRC_C_LIST))
	@rm -f $(patsubst %.c,%.o,$(SRC_C_LIST))
	
	