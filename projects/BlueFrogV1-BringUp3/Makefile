################################################################################
#
# Makefile for La BlueFrog V1
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
HAL_DIR         = $(RACINE)/libraries/STM32L1xx_HAL_Driver
USB_DIR		= $(RACINE)/libraries/STM32_USB_Device_Library
FATFS_DIR	= $(RACINE)/libraries/FatFS_Lib
STEMWIN_DIR	= $(RACINE)/libraries/STemWin_Lib
INFRAMOD_DIR    = $(RACINE)/libraries/BlueFrogV1-Lib
  # "INFRA Module" is original code name of La BlueFrog
##MIDDLEWARE_DIR  = $(RACINE)/libraries/MIDDLEWARE-ToImprove


# Linker script
LINKER          = $(RACINE)/projects/STARTUP/STM32L151XC_FLASH.ld

# Source file paths : Startup
VPATH          := $(SRC_DIR):$(RACINE)/projects/STARTUP

# Source file paths : STM32L1xx_HAL_Driver
VPATH          := $(VPATH):$(HAL_DIR)/src
HAL_SRC   = $(notdir $(wildcard $(HAL_DIR)/src/*.c))

# Source file paths : STM32_USB_Device_Library /Class/MSC & /Core
VPATH          := $(VPATH):$(USB_DIR)/Class/MSC/Src
USB_CLASSMSC_SRC   = $(notdir $(wildcard $(USB_DIR)/Class/MSC/Src/*.c))
VPATH          := $(VPATH):$(USB_DIR)/Core/Src
USB_CORE_SRC   = $(notdir $(wildcard $(USB_DIR)/Core/Src/*.c))

# Source file paths : FatFS_Lib
VPATH          := $(VPATH):$(FATFS_DIR)/src
FATFS_SRC   = $(notdir $(wildcard $(FATFS_DIR)/src/*.c))

# Source file paths : BlueFrogV2-Lib
VPATH          := $(VPATH):$(INFRAMOD_DIR)/src/Debug_Utilities
DEBUG_SRC    = $(notdir $(wildcard $(INFRAMOD_DIR)/src/Debug_Utilities/*.c))
VPATH          := $(VPATH):$(INFRAMOD_DIR)/src/LBF_API
LBF_API_SRC    = $(notdir $(wildcard $(INFRAMOD_DIR)/src/LBF_API/*.c))
VPATH          := $(VPATH):$(INFRAMOD_DIR)/src/Board_Support
LBF_BSP_SRC    = $(notdir $(wildcard $(INFRAMOD_DIR)/src/Board_Support/*.c))
VPATH          := $(VPATH):$(INFRAMOD_DIR)/src/LBF_USB_MassStorage
LBF_USBMS_SRC    = $(notdir $(wildcard $(INFRAMOD_DIR)/src/LBF_USB_MassStorage/*.c))
VPATH          := $(VPATH):$(INFRAMOD_DIR)/src/LBF_STemWin
LBF_STEMWIN_SRC    = $(notdir $(wildcard $(INFRAMOD_DIR)/src/LBF_STemWin/*.c))
VPATH          := $(VPATH):$(INFRAMOD_DIR)/src/LBF_DataFlash_FatFS
LBF_FATFS_SRC   = $(notdir $(wildcard $(INFRAMOD_DIR)/src/LBF_DataFlash_FatFS/*.c))
# Didn't manage to use a wildcard for INFRAMOD_DIR/src/*/*.c   ...


# Source file paths : MIDDLEWARE
##VPATH          := $(VPATH):$(MIDDLEWARE_DIR)/src
##MIDDLEWARE_SRC  = $(notdir $(wildcard $(MIDDLEWARE_DIR)/src/*.c))


#----------------------------------------------------------------------------
# Creation of list of source files
SOURCES = \
	$(notdir $(wildcard $(RACINE)/projects/STARTUP/*.s)) \
	$(notdir $(wildcard $(SRC_DIR)/*.c)) \
	$(CMSIS_SRC) \
	$(HAL_SRC) \
	$(USB_CLASSMSC_SRC) \
	$(USB_CORE_SRC) \
	$(FATFS_SRC) \
	$(DEBUG_SRC) \
	$(LBF_API_SRC) \
	$(LBF_BSP_SRC) \
	$(LBF_USBMS_SRC) \
	$(LBF_STEMWIN_SRC) \
	$(LBF_FATFS_SRC) 
##	$(MIDDLEWARE_SRC)
# should define a single $(INFRAMOD_SRC) for all these paths

INCLUDES = \
	$(INC_DIR) \
	$(CMSIS_DIR)/Device/ST/STM32L1xx/Include \
	$(CMSIS_DIR)/Include \
	$(HAL_DIR)/inc \
	$(USB_DIR)/Class/MSC/Inc \
	$(USB_DIR)/Core/Inc \
	$(FATFS_DIR)/inc \
	$(STEMWIN_DIR)/inc \
	$(INFRAMOD_DIR)/inc \
	$(INFRAMOD_DIR)/inc/Debug_Utilities \
	$(INFRAMOD_DIR)/inc/LBF_API \
	$(INFRAMOD_DIR)/inc/Board_Support \
	$(INFRAMOD_DIR)/inc/LBF_USB_MassStorage \
	$(INFRAMOD_DIR)/inc/LBF_STemWin \
	$(INFRAMOD_DIR)/inc/LBF_DataFlash_FatFS
# Didn't manage to use a wildcard for INFRAMOD_DIR/inc/* ...

ARCH_FLAGS = -mthumb -mcpu=cortex-m3

CFLAGS = \
	$(ARCH_FLAGS) \
	$(addprefix -I,$(INCLUDES)) \
	-O$(OPT) \
	-Wall \
	-ffunction-sections \
	-fdata-sections \
	-DSTM32L151xC \
	-DUSE_HAL_DRIVER \
	-D$(DEBUGGER) \
	-fno-exceptions \
	-Wno-write-strings
#	-D$(VERSION) \

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

LIBS = -L$(STEMWIN_DIR)/Lib -lSTemWin524b_CM3_GCC

# Compilation Tools
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
#all: version build run size
all:  build run size

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
	@$(CC)  $(LDFLAGS) -o  $@  $^ $(LIBS)
#	@$(CC) $(LDFLAGS) -o $@ $^

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



help:
	@echo ""
	@echo "#==============================================================#"
	@echo "# Makefile for La BlueFrog V2                                  #"
	@echo "#                                                              #"
	@echo "# Usage: make [options]                                        #"
	@echo "#                                                              #"
	@echo "#  options:                                                    #"
	@echo "#   build     compile complete project (with *.o)              #"
	@echo "#   run       program STM32 on the board                       #"
	@echo "#   size      show size of binary                              #"
	@echo "#   clean     erase files *.bin *.hex *.lst *.elf *~           #"
	@echo "#   purge     erase directory:   obj/                          #"
	@echo "#   help      show this help                                   #"
	@echo "#==============================================================#"
	@echo ""

#----------------------------------------------------------------------------------
