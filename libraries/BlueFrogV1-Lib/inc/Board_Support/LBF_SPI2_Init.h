/*******************************************************************************
 * LBF_SPI2_Init.h
 * 
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


/* 
 *        +-----------------------------------------------------------+
 *        |                     Pin assignment                        |
 *        +-----------------------------+---------------+-------------+
 *        |  STM32 SPI Pins             |     FLASH     |    Pin      |
 *        +-----------------------------+---------------+-------------+
 *        | FLASH_CS_PIN                | ChipSelect(/S)|    1        |
 *        | FLASH_SPI_MISO_PIN / MISO   | DataOut(DQ1)  |    2        |
 *        |                             | Write(/W)     |    3        |
 *        |                             | GND           |    4 (0 V)  |
 *        | FLASH_SPI_MOSI_PIN / MOSI   | DataIn(DQ0)   |    5        |
 *        | FLASH_SPI_SCK_PIN / SCK     | Clock(C)      |    6        |
 *        |                             | /HOLD         |    7        |
 *        |                             | VCC           |    8 (3.3 V)|
 *        +-----------------------------+---------------+-------------+
 * 
 ******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_SPI2_INIT_H
#define __LBF_SPI2_INIT_H



/* ----- Exported function prototypes ----------*/

void LBF_SPI2_Init(void);




#endif  /*__LBF_SPI2_INIT_H */ 

/***************************************************************END OF FILE****/
