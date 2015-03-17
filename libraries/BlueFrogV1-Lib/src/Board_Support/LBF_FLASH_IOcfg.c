/*******************************************************************************
 * LBF_FLASH_IOcfg.c
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
 *************************************************************************/

#include "LBF_lowlev_API.h"

#include "LBF_FLASH_IOcfg.h"


 /* 
 *        +--------------------------------------------------------------+
 *        |                     Pin assignment                           |
 *        +-----------------------------+------------------+-------------+
 *        |  STM32 SPI Pins             | Adesto FLASH     |    Pin      |
 *        +-----------------------------+------------------+-------------+
 *        | FLASH_CS_PIN                | ChipSelect(/CS)  |    4        |
 *        | FLASH_SPI_MISO_PIN / MISO   | SerialDataOut(SO)|    8        |
 *        | (GPIO)                      | WriteProtect(/WP)|    5        |
 *        |                             | GND              |    7 (0 V)  |
 *        | FLASH_SPI_MOSI_PIN / MOSI   | SerialDataIn(SI) |    1        |
 *        | FLASH_SPI_SCK_PIN / SCK     | SerialClock(SCK) |    2        |
 *        | (GPIO)                      | /RESET           |    3        |
 *        |                             | VCC              |    6 (3V)   |
 *        +-----------------------------+------------------+-------------+
 * 
 ******************************************************************************/



/* Privates prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Initialise the Adesto Data Flash.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_FLASH_IOcfg(void)
{

GPIO_InitTypeDef GPIO_InitStruct;

// Std CMOS output, no pull-up/-down resistor, medium speed
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP; // GPIO_NOPULL;// ie Copy previous with SPL
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;  //GPIO_SPEED_MEDIUM;

// PA8 = /HOLD
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

// PB12 = /CS
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

// PC9 = /WR
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

/* Initialise those pins in high (inactive) state */

FLASH_WR_HIGH();
FLASH_HOLD_HIGH();
FLASH_CS_HIGH();
}





/***************************************************************END OF FILE****/
