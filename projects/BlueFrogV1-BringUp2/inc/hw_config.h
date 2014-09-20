/*******************************************************************************
 * hw_config.h
 * 
 * Copyright 2014 Roman GAUCHI <roman.gauchi@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 ******************************************************************************/



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"
#include "stm32l1xx_conf.h"

/* Librairies InfraModule_Lib_v0.1 */
#include "inframod_board.h"
#include "inframod_pwr.h"
#include "inframod_image_bmp.h"
#include "inframod_fat16.h"
#include "inframod_horloge.h"
#include "inframod_delay.h"

#if defined (DEBUG)
 #include "inframod_uart.h"
 #include "xprintf.h"
#endif

/* Librairies STM32_USB-FS-Device_Driver */
#include "mass_mal.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "usb_lib.h"

#include "stm32_it.h"

/* Exported constants --------------------------------------------------------*/

/* Unique Devices IDs register set */
#define ID1                     0x1FF80050
#define ID2                     0x1FF80054
#define ID3                     0x1FF80064

#define NOIR                    0x0000
#define BLANC                   0xFFFF
#define ROUGE                   0xF800
#define VERT                    0x07E0
#define BLEU                    0x001F
#define JAUNE                   0xFFE0
#define CYAN                    0x07FF
#define BLEU_CLAIR              0x1C9F
#define ORANGE                  0xFD20

/* Exported functions ------------------------------------------------------- */
void Set_System(void);
void Set_USBClock(void);

void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);

void Led_Config(void);
void Slide_Config(void);

void Led_Rouge_ON(void);
void Led_Rouge_OFF(void);
void Led_Verte_ON(void);
void Led_Verte_OFF(void);
void Led_RW_ON(void);
void Led_RW_OFF(void);
void USB_Configured_LED(void);
void USB_NotConfigured_LED(void);

void USB_Cable_Config (FunctionalState NewState);
void Get_SerialNum(void);

void MAL_Config(void);

#endif  /*__HW_CONFIG_H*/

/***************************************************************END OF FILE****/
