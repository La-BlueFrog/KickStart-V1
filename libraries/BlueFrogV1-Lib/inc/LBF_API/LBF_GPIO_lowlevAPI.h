/*******************************************************************************
 * LBF_GPIO_lowlevAPI.h
 * 
 * Author: La BlueFrog, 2015
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
#ifndef __LBF_GPIO_LOWLEVAPI_H
#define __LBF_GPIO_LOWLEVAPI_H

#include "stm32l1xx.h"  //to allow access to STM32 registers in macros below while keeping header self-sufficient

/* Exported Macros ------------------------------------------------------- */
//#define GPIO_HIGH(PORT,PIN)                  PORT->BSRRL = PIN
//#define GPIO_LOW(PORT,PIN)                   PORT->BSRRH = PIN
//#define GPIO_TOGGLE(PORT,PIN)                PORT->ODR ^= PIN
#define GPIO_HIGH(PORT,PIN)             HAL_GPIO_WritePin(PORT, PIN, GPIO_PIN_SET)
#define GPIO_LOW(PORT,PIN)              HAL_GPIO_WritePin(PORT, PIN, GPIO_PIN_RESET)
#define GPIO_TOGGLE(PORT,PIN)           HAL_GPIO_TogglePin(PORT, PIN)


/* Exported functions ------------------------------------------------------- */




#endif  /*__LBF_GPIO_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
