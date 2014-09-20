/*******************************************************************************
 * main.c
 * 
 * Copyright 2014 Roman GAUCHI <roman.gauchi@gmail.com> & Xavier Cauchy
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


/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"

/* Privates prototypes -------------------------------------------------------*/



/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{

    // Board Initializations and Configurations
    Set_System();
    PWR_Init();
    Led_Config();
    Slide_Config();  
    FLASH_Init();
    OLED_Init();

    Led_Rouge_ON();  //just to provide a status


    // Infinite Loop -  Control LEDs from slider switch
    while(1)
    {
            if (!GPIO_ReadInputDataBit(SLIDE_1_GPIO_PORT, SLIDE_1_PIN))
            {
               Led_Verte_ON();
               Led_Rouge_OFF(); 
            }
            if (!GPIO_ReadInputDataBit(SLIDE_2_GPIO_PORT, SLIDE_2_PIN))
            {
               Led_Verte_OFF();
               Led_Rouge_ON();
            }   
    }
    
    return 0;
}



/***************************************************************END OF FILE****/
