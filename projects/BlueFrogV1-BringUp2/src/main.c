/*******************************************************************************
 * main.c
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
    uint16_t fconfig[11];  // configuration file to control some OLED parameters

     // Board Initializations and Configurations
    Set_System();
    PWR_Init();
    Led_Config();
    Slide_Config();  
    FLASH_Init();
    OLED_Init();  // OLED interface init- Power to OLED (VDDH=13V) is still disabled

    Led_Rouge_ON();  //just to provide an intermediate status


    // OLED configuration  
    fconfig[0]=0xFFFF;     //so OLED_Config() will use default init value
    OLED_Config(fconfig);  //sets up OLED register and powers on OLED VDDH(13V) 

    OLED_Fill(0, 0, 160, 128, BLEU);  
    Led_Verte_ON();  //just to provide an intermediate status

    while(1)
    {
          if ( (!GPIO_ReadInputDataBit(SLIDE_1_GPIO_PORT, SLIDE_1_PIN)) )
          {  
             OLED_Fill(0, 0, 40, 128, NOIR);  
             OLED_Fill(40, 0,40, 128, JAUNE);
             OLED_Fill(80, 0, 40, 128, VERT);
             OLED_Fill(120, 0, 40, 128, BLANC);
          }
          if ( (!GPIO_ReadInputDataBit(SLIDE_2_GPIO_PORT, SLIDE_2_PIN)) )
          {  
             // Fill the 160x128 screens with 8 colors organized as 2 rows of 4 blocks
             // Arguments: Xstart, Ystart, Width, Height, Color in RGB565 format (can use colors defined in hw_config.h)
             OLED_Fill(0, 0, 40, 64, NOIR);  
             OLED_Fill(40, 0,40, 64, JAUNE);
             OLED_Fill(80, 0, 40, 64, ROUGE);
             OLED_Fill(120, 0, 40, 64, BLANC);
             OLED_Fill(0, 64, 40, 64, VERT);
             OLED_Fill(40, 64, 40, 64, BLEU);
             OLED_Fill(80, 64, 40, 64, ORANGE);
             OLED_Fill(120, 64, 40, 64, CYAN);
          }
     }
 
    return 0;
}


/***************************************************************END OF FILE****/
