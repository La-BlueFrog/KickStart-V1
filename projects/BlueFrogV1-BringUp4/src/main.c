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


/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{
    uint16_t fconfig[11];
    uint16_t numImg = 0, nbImg = 0, listeImg[200];
    
    Set_System();
    
    // Initialisation du Power Management
    PWR_Init();
    
    // Initialisation de l'horloge RTC
    HORLOGE_Init();
    HORLOGE_Config(fconfig[0]);
    
    // Initialisation des leds et du slide
    Led_Config();
    Slide_Config();
    
    // Initialisation de la memoire FLASH
    FLASH_Init();
    
    // Fichier de Configuration (heure, frequence, driving current, ...)
    FAT16_FichierConfig(fconfig);
    
    
    // Initialisation de l'OLED
    //OLED_Init();
    //OLED_Config(fconfig);

    // Initialisation de l'USB
    Set_USBClock();
    USB_Interrupts_Config();
    USB_Init();
    
    Led_Rouge_ON();
    
    // Boucle Infinie, Fonctionnement par interruption
    // When slider is actioned, check number of pictures in USB folder
    while(1)
    {
        if ( (!GPIO_ReadInputDataBit(SLIDE_1_GPIO_PORT, SLIDE_1_PIN)) 
           ||(!GPIO_ReadInputDataBit(SLIDE_2_GPIO_PORT, SLIDE_2_PIN)) )
        {
            // Recuperation des images en FLASH.
            nbImg = 0;   
            FAT16_ListerImageBMP(&nbImg, listeImg, FAT16_DEBUT_RACINE);
           
            //  flash green light as many times as the number of pictures found in USB folder
            for (numImg=0; numImg<nbImg; numImg++)
            {
                 Led_Verte_ON();
                 delay_ms(300);
                 Led_Verte_OFF();
                  delay_ms(600);
            }
        }
    }
    
    return 0;
}

#ifdef USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line 
     * number, ex: printf("Wrong parameters value: file %s on line %d\r\n", 
     * file, line) */
    
    /* Infinite loop */
    while (1);
}
#endif

/***************************************************************END OF FILE****/
