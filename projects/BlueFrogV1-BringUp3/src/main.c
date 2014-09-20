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
*
* When this program is running, module is seen as USB key (mass storage device)
* from PC. User can store and retrieve files.
* Upon first insertion (or if Flash gets erased), PC will propose formatting (and
* will normally use FAT16, based on storage capacity information it will obtain
* from the module).
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

    Led_Rouge_ON();  

    // Initialisation de l'horloge RTC
    // HORLOGE_Init();
    // HORLOGE_Config(fconfig[0]);


    // Basic Flash sanity check by reading manuf ID
    if ( (FLASH_ReadID()>>16 & 0xFF) == 0x1F )  
    {
       Led_Verte_ON();  
    }


    // A chance for user to first erase Flash memory by manoeuvring slider switch
    delay_ms(2000);  // some time for user to react
    if ( (!GPIO_ReadInputDataBit(SLIDE_1_GPIO_PORT, SLIDE_1_PIN)) 
              || (!GPIO_ReadInputDataBit(SLIDE_2_GPIO_PORT, SLIDE_2_PIN)) )
    {
       Led_Verte_OFF();
       FLASH_EraseBulk();  // takes a while - about 30+ seconds
    }

 
    // USB Initializations
    Set_USBClock();
    USB_Interrupts_Config();
    USB_Init();
    
    //OLED_Init();

    // Infinite Loop - USB handled by interrupts
   while(1)
    {    
            Led_Verte_ON();
            delay_ms(100);
            Led_Verte_OFF();
            delay_ms(500);        
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
