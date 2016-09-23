#---------------------------
# User defined
#---------------------------
#SDK_PATH = sdk/# /c/Realtek/rtl8195a/v35a/sdk#not work, wait update 
#GCC_PATH = d:/MCU/GNU_Tools_ARM_Embedded/5.2_2015q4/bin/# + or set in PATH
#OPENOCD_PATH = d:/MCU/OpenOCD/bin/# + or set in PATH
TOOLS_PATH ?= component/soc/realtek/8195a/misc/iar_utility/common/tools/
FLASHER_PATH ?= flasher/
#---------------------------
# Default
#---------------------------
# Compilation tools
CROSS_COMPILE = $(GCC_PATH)arm-none-eabi-
AR = $(CROSS_COMPILE)ar
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
NM = $(CROSS_COMPILE)nm
LD = $(CROSS_COMPILE)gcc
GDB = $(CROSS_COMPILE)gdb
SIZE = $(CROSS_COMPILE)size
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

# TARGET dirs
TARGET ?= build
OBJ_DIR ?= build/obj
BIN_DIR ?= build/bin
ELFFILE ?= $(OBJ_DIR)/$(TARGET).axf

# Make bunary tools
ifneq ($(shell uname), Linux)
EXE = .exe
endif
PICK = $(TOOLS_PATH)pick$(EXE)
PADDING = $(TOOLS_PATH)padding$(EXE)
CHCKSUM = $(TOOLS_PATH)checksum$(EXE)

# openocd tools
OPENOCD = $(OPENOCD_PATH)openocd

