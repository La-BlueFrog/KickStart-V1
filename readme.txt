
ReadMe file - V0.1 - 18-Sep-14
=================================

FILE STRUCTURE:

/STM32-Projects
	-- /libraries
		-- /BlueFrogV1-Lib
		   # Board init and controls  -  La BlueFrog specific
		-- /CMSIS
		   # ARM Cortex-M3 libs  -  supplied by ARM/ST
		-- /STM32L1xx_StdPeriph_Driver
		   # For configuration of STM32 on-chip peripherals  -  supplied by ST
		-- /STM32_USB-FS-Device_Driver
		   # USB2.0 (full speed) device driver  -  supplied by ST
	-- /projects
		-- /Project-A
			-- /inc
				xxx.h
			-- /src
				xxx.c
				/startup
					startup_stm32l1xx_md.s
					  # startup file called before main, 
					  # STM32L1-specific  -  supplied by ST
					stm32_flash.ld
					  # linker script for STM32L151RC
			-- Makefile
			   # Invoked by make statement to compile/link/load project,
			   # type make -help for usage options
			-- /obj 
			   # automagically created and filled in when building project with 'make'  
	-- /documentation
		-- /datasheets
		   # datasheets and user manuals of ICs used on La BlueFrog

=================================

To write an application, user essentially has to first call within main() a few functions already provided (in BlueFrogV1-Lib). This configures the STM32 clocks, IOs, etc. and defines a number of abstraction layers to use the IC on-board (for example, use the Data Flash with simple WriteBuffer/ReadBuffer type functions. After that he can write its application code, relying on functions/macros defined in BlueFrogV1-Lib or hw_config.c for easier (higher level) control of on-board chips.

See examples provided under /projects.
The example projects provided can be simply built by "make build" and programmed into the STM32 by "make run"

================================

Board Programming/Debug/IO Connector: 

                |
   UART_Rx  O   | ---------------------------------------------  e.g. to UART-USB cable connected to PC Virtual Com interface
   UART_Tx  O   | ---------------------------------------------    or for interfacing with external system (UART or GPIO)
                |
   GND      O   | --------------  STLink-V2 programmer
   SWLK     O   | --------------  STLink-V2 programmer
   Ext3V    O   | --------------  STLink-V2 programmer
   SWD      O   | --------------  STLink-V2 programmer
   RST      O   | ----  no connection needed
    ____________|


