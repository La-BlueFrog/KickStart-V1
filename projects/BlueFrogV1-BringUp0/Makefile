################################################################################
#
# Makefile for La BlueFrog V1  (codename: Infra Module, v1.5 and v1.6)
# 
################################################################################

# Name of executable
TARGET          = inframod

# debugger
DEBUGGER        = DEBUG


# Optimization (0,1,2,s)
OPT             = s

# Directory paths
SRC_DIR         = ./src
INC_DIR         = ./inc
OBJ_DIR         = ./obj
BIN_DIR         = ./obj
RACINE          = ../..
CMSIS_DIR       = $(RACINE)/libraries/CMSIS
STDPERIPH_DIR   = $(RACINE)/libraries/STM32L1xx_StdPeriph_Driver
USBDEVICE_DIR   = $(RACINE)/libraries/STM32_USB-FS-Device_Driver
INFRAMOD_DIR    = $(RACINE)/libraries/BlueFrogV1-Lib
## "INFRA Module" is original code name of La BlueFrog

# Linker script
LINKER          = $(SRC_DIR)/startup/stm32_flash.ld

# Source file paths (user's)
VPATH          := $(SRC_DIR):$(SRC_DIR)/startup

# Source file paths : CMSIS
VPATH          := $(VPATH):$(CMSIS_DIR)/Device/ST/STM32L1xx/Source/Templates
CMSIS_SRC       = $(notdir $(wildcard $(CMSIS_DIR)/Device/ST/STM32L1xx/Source/Templates/*.c))

# Source file paths : STM32L1xx_StdPeriph_Driver
VPATH          := $(VPATH):$(STDPERIPH_DIR)/src
STDPERIPH_SRC   = $(notdir $(wildcard $(STDPERIPH_DIR)/src/*.c))

# Source file paths : STM32L1xx_USB-FS-Device_Driver
VPATH          := $(VPATH):$(USBDEVICE_DIR)/src
USBDEVICE_SRC   = $(notdir $(wildcard $(USBDEVICE_DIR)/src/*.c))

# Source file paths : BlueFrogV1-Lib
VPATH          := $(VPATH):$(INFRAMOD_DIR)/src
INFRAMOD_SRC    = $(notdir $(wildcard $(INFRAMOD_DIR)/src/*.c))

#-------------------------------------------------------------------------------
# Creation de la liste des fichiers sources
SOURCES = \
	$(notdir $(wildcard $(SRC_DIR)/startup/*.s)) \
	$(notdir $(wildcard $(SRC_DIR)/*.c)) \
	$(CMSIS_SRC) \
	$(STDPERIPH_SRC) \
	$(USBDEVICE_SRC) \
	$(INFRAMOD_SRC)

INCLUDES = \
	$(INC_DIR) \
	$(CMSIS_DIR)/Device/ST/STM32L1xx/Include \
	$(CMSIS_DIR)/Include \
	$(STDPERIPH_DIR)/inc \
	$(USBDEVICE_DIR)/inc \
	$(INFRAMOD_DIR)/inc

ARCH_FLAGS = -mthumb -mcpu=cortex-m3

CFLAGS = \
	$(ARCH_FLAGS) \
	$(addprefix -I,$(INCLUDES)) \
	-O$(OPT) \
	-Wall \
	-ffunction-sections \
	-fdata-sections \
	-DSTM32L1XX_MD \
	-DUSE_STDPERIPH_DRIVER \
	-D$(DEBUGGER) \
	-fno-exceptions \
	-Wno-write-strings

LDFLAGS = \
	$(ARCH_FLAGS) \
	-lm \
	-static \
	-Wl,-gc-sections \
	-T$(LINKER)

ASFLAGS = \
	$(ARCH_FLAGS) \
	-x assembler-with-cpp \
	$(addprefix -I,$(INCLUDES))

# Outils de compilation
CC      = arm-none-eabi-gcc
LD      = arm-none-eabi-ld
CP      = arm-none-eabi-objcopy
OD      = arm-none-eabi-objdump
SIZE    = arm-none-eabi-size


TARGET_BIN = $(BIN_DIR)/$(TARGET).bin
TARGET_HEX = $(OBJ_DIR)/$(TARGET).hex
TARGET_LST = $(OBJ_DIR)/$(TARGET).lst
TARGET_ELF = $(OBJ_DIR)/$(TARGET).elf
TARGET_OBJ = $(addsuffix .o,$(addprefix $(OBJ_DIR)/,$(basename $(SOURCES))))

#-------------------------------------------------------------------------------
all: version build run size

build: $(TARGET_BIN) $(TARGET_HEX) $(TARGET_LST)

$(TARGET_BIN): $(TARGET_ELF)
	@echo "-> "$(notdir $@)""
	@$(CP) -O binary $< $@

$(TARGET_HEX): $(TARGET_ELF)
	@echo "-> "$(notdir $@)""
	@$(CP) -O ihex $< $@

$(TARGET_LST): $(TARGET_ELF)
	@echo "-> "$(notdir $@)""
	@$(OD) -S $< > $@

$(TARGET_ELF): $(TARGET_OBJ)
	@echo -e "\033[01;33m==========  GENERATION  ====================================\033[m"
	@echo "-> "$(notdir $@)""
	@$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo -e "\033[01;42m-> COMPILE:\033[m "$(notdir $<)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo -e "\033[01;42m-> COMPILE:\033[m "$(notdir $<)
	@$(CC) $(CFLAGS) -c -o $@ $<  

$(OBJ_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	@echo -e "\033[01;42m-> COMPILE:\033[m "$(notdir $<)
	@$(CC) $(ASFLAGS) -c -o $@ $<

run: $(TARGET_BIN)
	@echo -e "\033[01;33m==========  PROGRAMMATION  =================================\033[m"
	@st-flash write $< 0x8000000

size: $(TARGET_ELF)
	@echo -e "\033[01;33m==========  TAILLE  ========================================\033[m"
	@$(SIZE) $<

clean:
	@echo -e "\033[01;41m-> SUPRESSION !\033[m"
	@rm -vf $(TARGET_BIN)
	@rm -vf $(TARGET_HEX)
	@rm -vf $(TARGET_LST)
	@rm -vf $(TARGET_ELF)
	@rm -vf $(SRC_DIR)/*~

purge:
	@echo -e "\033[01;41m-> SUPRESSION !!\033[m"
	@rm -vRf $(OBJ_DIR)

version:
	@echo -e "\033[01;41m /!\ ATTENTION : Compilation pour le module Infra version 1.5 ou v1.6 /!\ \033[0m"


help:
	@echo ""
	@echo "#==============================================================#"
	@echo "# Makefile for La BLueFrog-V1                                  #"
	@echo "#                                                              #"
	@echo "# Usage: make [options]                                        #"
	@echo "#                                                              #"
	@echo "#  options:                                                    #"
	@echo "#   build     compiler le projet complet (avec *.o)            #"
	@echo "#   run       programmer le microcontroleur sur kit            #"
	@echo "#   size      afficher la taille du binaire                    #"
	@echo "#   clean     effacer les fichiers *.bin *.hex *.lst *.elf *~  #"
	@echo "#   purge     effacer le dossier obj/                          #"
	@echo "#   help      afficher l'aide memoire                          #"
	@echo "#==============================================================#"
	@echo ""

#-------------------------------------------------------------------------------
