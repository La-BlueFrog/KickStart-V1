
ReadMe file - 



================================
FILE STRUCTURE:

/Rel2.4_KickStart-V1
	-- /libraries
		-- /BlueFrogV1-Lib
		   # Board init and controls  -  La BlueFrog specific
		   # Adaptation Layers for Middlewares (USBD, FatFS, emWin)
		-- /CMSIS
		   # ARM Cortex-M3 libs  -  supplied by ARM/ST
		-- /STM32L1xx_HAL_Driver
		   # Hardware Abstraction Layer for config of STM32 on-chip periphs 
		   # Supplied by ST as part of "STM32 C
		-- /STM32_USB-Device_Library
		   # USB2.0 (full speed) device driver -from ST
		-- /FatFS_Lib
		   # FAT File System  - from ST, derived from ChaN's open-source FatFS
		-- /STemWin_Lib
		   # Rich Graphics Library - from ST under licence from Segger (emWin)


	-- /projects
		-- /Project-A
			-- /inc
				xxx.h
			-- /src
				xxx.c
			-- Makefile
			   # Invoked by make statement to compile/link/load project,
			   # type make -help for usage options
			-- /obj 
			   # automagically created and filled in when building project with 'make'  
		-- /Project-B
			-- ..........
		-- /Project-A
			-- ..........
		-- /STARTUP
			-- startup_stm32l151xc.s
					  # startup file called before main, 
					  # STM32L1-specific  -  supplied by ST
			-- STM32151XC_FLASH.ld
					  # STM32L1-specific  -  supplied by ST
					stm32_flash.ld
					  # linker script for STM32L151RC
	-- /documentation
		-- /datasheets
		   # datasheets and user manuals of ICs used on La BlueFrog

=================================

To write an application, user essentially has to first call within main() a few board init and optional middleware initialization functions (see examples provided). This will configures the STM32 clocks, IOs, etc. and define a number of abstraction layers to use the IC on-board. User can then write its application code, relying on functions/macros defined in BlueFrogV1-Lib for easier (higher level) control of on-board chips, or in the Middleware provided.

See examples provided under /projects.
The example projects provided can be simply built by "make build" and programmed into the STM32 by "make run"

================================

Regarding development chains for the STM32, there are a number of options, with or without IDE. Please have a look at BlueFrog_Dev_Chain.pdf in directory /documentation.


================================

Board Programming/Debug/IO Connector: 

               |
   UART_Rx  O  | ----------------------------------------  e.g. to UART-USB cable connected to PC Virtual Com interface
   UART_Tx  O  | ----------------------------------------    or for interfacing with external system (UART or GPIO)
               |
   GND      O  | --------------  STLink-V2 programmer
   SWLK     O  | --------------  STLink-V2 programmer
   Ext3V    O  | --------------  STLink-V2 programmer
   SWD      O  | --------------  STLink-V2 programmer
   RST      O  | --- no connection needed
    ___________|

================================
