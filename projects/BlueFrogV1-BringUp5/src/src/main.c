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

#include "stm32l1xx.h"
#include "LBF_Board_Init.h"
#include "LBF_lowlev_API.h"
#include "LBF_LaunchUSB_MassStorage.h"

/*******************************************************************************
* Function Name  : main.
* Description    : Main routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int main(void)
{


/* ===================================================== */
/* Board Initializations and Configurations except OLED  */
/* (clocks, I/Os, on-chip peripherals, on-board ICs)     */
/* ===================================================== */

    LBF_Board_Init();


/* ===================================================== */
/* Application Code Below */
/* ===================================================== */


/* ==  User Declarations =============================== */




/* ==  Body     ======================================== */


  LBF_LaunchUSB_MassStorage();
 

  Stm32_Led_ON();

  /* Run Application (Interrupt mode) */
  while (1)
  {
  }
    
}


/***  END OF FILE ************************************************************/
