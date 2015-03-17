Implementation of USB Device fucntionalities in La BlueFrog relies on device drivers supplied by ST and found in .../libraries/STM32_USB_Device_Library.

The files found in the present directory are derived from examples provided by ST in the STM32L1 Cube Library -- specifically, in package STM32Cube_FW_L1_V1.0.0 :  STM32Cube_FW_L1_V1.0.0/Projects/STM32L152D_EVAL/Applications/USB_Device/MSC_Standalone. They were slightly adapted for La BLueFrog, including in the following aspects:
- priority of USB interrupt made user configurable
- 
