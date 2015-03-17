/*******************************************************************************
 * main.c
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

#include "LBF_Global.h"


/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{


/* ================================================================ */
/* Board Initializations and Configurations except OLED             */
/* (clocks, I/Os, on-chip peripherals, on-board ICs)                */
/* ================================================================ */

    LBF_Board_Init();

    Red_Led_ON();

/* ================================================================ */
/* Optional initialization of Middleware libraries :                */
/* USBD drivers, FatFS File System, STemWin GUI                     */
/* ================================================================ */

    // UNCOMMENT IF YOU WELL BE USING ...:
  
    /* ... La BlueFrog as USB Mass Storage (Full Speed)             */
    /*     (based on ST-provided stack part of STM32 Cube offering  */
    // Delay_ms(1000);
    // LBF_LaunchUSB_MassStorage();
 
    /* ... the FAT File System (FatFS)                              */
    /*     (based on ChanN's FatFS included in STM32 Cube offering) */
    // LBF_FatFS_Init();

    /* ... the STemWin Graphical Library                            */
    /*     (based on Segger's emWin included in STM32 Cube offering)*/
    // LBF_emWin_Init();


    Red_Led_OFF();




/* ===================================================== */
/* Application Code Below */
/* ===================================================== */

/* ==  User Declarations =============================== */

uint8_t i = 0;


/* ==  Body              =============================== */

    Red_Led_ON();
    Green_Led_OFF();

    while(1) 
    {         
        UART_SendData(i);
        if (UART_ReceiveData() == i )
	{
          Red_Led_OFF();
          Green_Led_ON();
        }
        Delay_ms(500);
        Red_Led_ON();
        Delay_ms(500);
        i++; //wrap around at 255
    }
    // Run this test with external short between the 2 user configurable
    // connector pins -- which bear UART Tx and RX in this test.
    // --> Green_LED will remain on as soon as ONE UART transfer occurs correctly
    // Red_LED will blink is successive UART transfers are correct but will stay 
    // ON if transfers are not correct
    
}



/***************************************************************END OF FILE****/
