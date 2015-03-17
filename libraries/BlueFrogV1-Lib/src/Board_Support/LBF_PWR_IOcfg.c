/*******************************************************************************
 * LBF_PWR_IOcfg.c
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
 *************************************************************************/

#include "LBF_lowlev_API.h"

#include "LBF_PWR_IOcfg.h"

/*******************************************************************************
 * @brief  : Configure GPIOs dedicated to PMICs incl. LP3913 
 * @param  : none.
 * @return : none.
 ******************************************************************************/
void LBF_PWR_IOcfg(void)
{

GPIO_InitTypeDef GPIO_InitStruct;

// Inputs

    // Pin NRST (IN) = PA7  -  Input, no pull-up/-down
    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


// Outputs

    // Pin  POWERACK = PA1, OLED_VDDH/BOOSTCONV_EN = PA5
    // Std CMOS output, no pull_up/-down res., low speed
    GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;  //GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct) ;



// IRQs  - Moved to LBF_Interrupts_Cfg.c
/*
     GPIO_InitStruct.Pull = GPIO_NOPULL;

     // Pin IRQB (IN) = PA6 - Falling Edge
     GPIO_InitStruct.Pin = GPIO_PIN_6;
     GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
     HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

     // Pin ONSTAT (IN) = PB0 -  RISING Edge
     GPIO_InitStruct.Pin = GPIO_PIN_0;
     GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
     HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
*/


/* ---------------------------------------------- */
/* Make sure OLED VDDH is off at start-up         */

    OLED_VDDH_OFF();

}



/***************************************************************END OF FILE****/
