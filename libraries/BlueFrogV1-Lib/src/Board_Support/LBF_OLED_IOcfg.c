/*******************************************************************************
 * inframod_gpio_oled_config.c
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

#include "LBF_OLED_IOcfg.h"


/* Privates prototypes -------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Initialise et configure le peripherique I2C.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_OLED_IOcfg (void)
{

GPIO_InitTypeDef GPIO_InitStruct;
 
  // Std CMOS output, no pull resistor, m speed
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  // OLED CS = PA4,  Medium speed
 

  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  // OLED RS = PB9,  Medium speed

  GPIO_InitStruct.Pin = GPIO_PIN_11 | GPIO_PIN_13;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  //OLED PS = PC11,  OLED RESET = PC13, Low Speed



    /* 
     * Configuration de l'OLED :
     * RESET = 1    0:reset SEPS525
     * PS    = 0    0:bus serie 1:bus parallele
     * CS    = 1    0:SEPS525 accessible 1:SEPS525 verouille
     * RS    = 1    0:commande 1:parametre/data
     */
    OLED_RESET_LOW();
    
    GPIO_LOW(OLED_PS_PORT, OLED_PS_PIN);
    OLED_RS_HIGH();
    OLED_CS_HIGH();
    OLED_RESET_HIGH();
}


/***************************************************************END OF FILE****/
