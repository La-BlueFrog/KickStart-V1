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
    Delay_ms(1000);
    LBF_LaunchUSB_MassStorage();
	// so that file created by this demo can be seen from PC
 
    /* ... the FAT File System (FatFS)                              */
    /*     (based on ChanN's FatFS included in STM32 Cube offering) */
    // LBF_FatFS_Init();

	// in this example, FatFS initialized from Application code 


    /* ... the STemWin Graphical Library                            */
    /*     (based on Segger's emWin included in STM32 Cube offering)*/
    // LBF_emWin_Init();


    Red_Led_OFF();



/* ===================================================== */
/* Application Code Below */
/* ===================================================== */


/* ==  User Declarations =============================== */

FIL MyFile;   /* File object for FatFS operations */

boolean_t Success = TRUE;
uint32_t i = 0;

uint32_t wbytes_count; /* File write counts */
uint8_t wtext[] = "Voici un petit texte passionnant, stocke en utilisant FatFS"; /* File write buffer */
uint32_t rbytes_count; /* File read counts */
uint8_t rtext[100]; /* File read buffer */


/* ==  Body     ======================================== */

Green_Led_ON();

    /* WRITE A TEXT FILE */
    Success &= LBF_FatFS_Init();
    if (Success)
    {
            if(f_open(&MyFile, "DUMMY.TXT", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
            {
                if(f_write(&MyFile, wtext, sizeof(wtext), (void *)&wbytes_count) == FR_OK);
                {
                    f_close(&MyFile);
                }
            }
    }     
    LBF_FatFS_DeInit();



    /* READ BACK FROM TEXT FILE */
    Success &= LBF_FatFS_Init();
    if (Success)
    {
            if(f_open(&MyFile, "DUMMY.TXT", FA_READ) == FR_OK)
            {
                if(f_read(&MyFile, rtext, sizeof(wtext), (void *)&rbytes_count) == FR_OK);
                {
                    f_close(&MyFile);
                }
            }
    }
    LBF_FatFS_DeInit();



    /* COMPARE BYTES RETRIEVED vs. WRITTEN */
    if (wbytes_count != rbytes_count)
    {
        Success = FALSE;
    }
    for (i=0; i<rbytes_count; i++)
    {
        if (wtext[i]!=rtext[i])
        {
            Success = FALSE;
        }
    }


    /* Blinking LED if success, else fixed LED */
    while(1)
    {
        if (Success==TRUE)
        {
            Red_Led_OFF();
        }
        Delay_ms(500);
        Red_Led_ON();
        Delay_ms(300);
     }     


}
 

/***  END OF FILE ************************************************************/
