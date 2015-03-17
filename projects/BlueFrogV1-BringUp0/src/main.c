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

typedef enum {is_green, is_red} led_color_t;
led_color_t Active_LED = is_red;


/* ==  Body              =============================== */


   // Check I2C writes and reads from PMIC (ChipID=0x60) correctly
   // Set LED color to Green if correct, else Red
   // Reg.0x6 = Buck2 Control Register, contents 0x4D means Buck2 ON and VDD=3.0V
    ( I2C2_ReadSingleReg(0x60, 0x6) == 0x4D) 	?  (Active_LED = is_green) : (Active_LED = is_red);
    

    // Blink result LED - Allow user to change color from slider switch
    while(1) 
    {   
        (Active_LED == is_green) ?  Green_Led_ON() : Red_Led_ON();

	Delay_ms(500);

        Red_Led_OFF();
        Green_Led_OFF();
	Delay_ms(500);

        if ( Get_Slider_Select1() || Active_LED == is_green)
        {
            Active_LED = is_green;
        }
        if ( Get_Slider_Select2() || Active_LED == is_red)
        {
            Active_LED = is_red;
        }
    }
    
}



/***************************************************************END OF FILE****/
