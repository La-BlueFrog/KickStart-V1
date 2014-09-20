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
    
    // Initialisation des leds et du slide
    Led_Config();
    Slide_Config();
    Led_Rouge_ON();
    
    // Initialisation de la memoire FLASH
    FLASH_Init();
    
    // Fichier de Configuration (heure, frequence, driving current, ...)
    FAT16_FichierConfig(fconfig);
    
#if defined (DEBUG)
    UART_Init();
    xdev_out(UART_EnvoyerData);
    xdev_in(UART_RecevoirData);
    xputs("\nInfraModule UART debugeur:\n\n");
#endif
    
    // Initialisation de l'OLED
    OLED_Init();
    OLED_Config(fconfig);
    
    // Recuperation des images en FLASH.
    FAT16_ListerImageBMP(&nbImg, listeImg, FAT16_DEBUT_RACINE);
    
#if defined (DEBUG)
    uint8_t i;
    for(i=0; i<nbImg; i++)
        xprintf("IMAGE: 0x%02x\n", listeImg[i]);
#endif

    if(nbImg == 0)
        OLED_Fill(0, 0, 160, 128, VERT);
    else
        BMP_LireImage(listeImg[0]);
    
    // Initialisation de l'horloge RTC
    HORLOGE_Init();
    HORLOGE_Config(fconfig[0]);
    
    // Initialisation de l'USB
    Set_USBClock();
    USB_Interrupts_Config();
    USB_Init();
    
    Led_Rouge_OFF();
    
    // Boucle Infinie, Fonctionnement par interruption
    while(1)
    {
        if (!GPIO_ReadInputDataBit(SLIDE_1_GPIO_PORT, SLIDE_1_PIN))
        {
            Led_Verte_ON();
            numImg++;
            if (numImg >= nbImg)
                numImg = 0;
            if(BMP_LireImage(listeImg[numImg]) != 0)
            {
                if(numImg%2)
                    OLED_Fill(0, 0, 160, 128, ROUGE);
                else
                    OLED_Fill(0, 0, 160, 128, BLEU);
            }
            
            Led_Verte_OFF();
            // Tant que le slide et a l'etat haut
            while(!GPIO_ReadInputDataBit(SLIDE_1_GPIO_PORT, SLIDE_1_PIN));
            delay_ms(10);
        }
        
        if (!GPIO_ReadInputDataBit(SLIDE_2_GPIO_PORT, SLIDE_2_PIN))
        {
            OLED_afficherHeure();
            
            // Clignotement et actualisation de l'heure
            RTC_TimeTypeDef RTC_TimeStruct;
            uint8_t second = RTC_TimeStruct.RTC_Seconds;
            uint8_t minute = RTC_TimeStruct.RTC_Minutes;
            while(GPIO_ReadInputDataBit(SLIDE_1_GPIO_PORT, SLIDE_1_PIN))
            {
                RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
                delay_ms(10);
                
                // Actualisation des minutes
                if(RTC_TimeStruct.RTC_Minutes != minute)
                {
                    OLED_afficherHeure();
                    minute = RTC_TimeStruct.RTC_Minutes;
                }
                
                // Actualisation des secondes
                if(RTC_TimeStruct.RTC_Seconds != second)
                {
                    if(second%2)
                        FONT_afficherSegment(64, 39, 10);
                    else
                        OLED_Fill(70, 44, 20, 40, NOIR);
                    second = RTC_TimeStruct.RTC_Seconds;
                }
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
