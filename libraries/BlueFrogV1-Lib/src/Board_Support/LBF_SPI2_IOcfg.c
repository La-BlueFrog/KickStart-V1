/*******************************************************************************
 * LBF_SPI2_IOcfg.c
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

#include "LBF_SPI2_IOcfg.h"


/*******************************************************************************
 * @brief  : IO COnfiguration for SPI #2
 * @param  : none.
 * @return : none.
 ******************************************************************************/

void LBF_SPI2_IOcfg(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

    /* Peripheral clock enable */
    __SPI2_CLK_ENABLE();
  
    /**SPI2 GPIO Configuration    
    PB13     ------> SPI2_SCK
    PB14     ------> SPI2_MISO
    PB15     ------> SPI2_MOSI 
    */
/*    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
*/

// COPY Previous with SPL :
//PB13=SCK
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//PB14=MIS0
    GPIO_InitStruct.Pin = GPIO_PIN_14;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//PB15=MOSI
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}





/***************************************************************END OF FILE****/
