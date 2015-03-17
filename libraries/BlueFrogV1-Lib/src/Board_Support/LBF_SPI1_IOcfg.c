/*******************************************************************************
 * LBF_SPI1_IOcfg.c
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

#include "LBF_SPI1_IOcfg.h"



/*******************************************************************************
 * @brief  : Configuration of GPIOs used by SPI #1
 * @param  : none.
 * @return : none.
 ******************************************************************************/

void LBF_SPI1_IOcfg(void)
{
// Copied from HAL MX Generator (HAL_SPI_MspInit)

GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    __SPI1_CLK_ENABLE();
  
    /**SPI1 GPIO Configuration    
    PB3     ------> SPI1_SCK
    PB4     ------> SPI1_MISO
    PB5     ------> SPI1_MOSI 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}





/***************************************************************END OF FILE****/
