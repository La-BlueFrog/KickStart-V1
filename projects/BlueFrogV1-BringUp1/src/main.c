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


boolean_t TestFlash (void);


    // Test reads and writes from/to Flash; set Green LED on if success
    if (TestFlash())
    {
           Green_Led_ON(); 
    }

    // Infinite Loop - Job done, blink Red LED
    while(1)
    {
          Red_Led_OFF();
          Delay_ms(700);
          Red_Led_ON();
          Delay_ms(300);        
    }
    
}


/*******************************************************************************
* Function Name  : TestFlash.

* Description    : Short test to write and read from data flash.
* Input          : None.
* Output         : None.
* Return         : TRUE if success, else FALSE.

*******************************************************************************/
boolean_t TestFlash(void) 
{
// Size of Flash= FLASH_NUMBER_OF_PAGES * FLASH_PAGE_SIZE

int rand();  //returns a value between 0 and RAND_MAX (defined by the compiler, often 32767)

uint8_t WriteDataBuff[4096]; 
uint8_t ReadDataBuff[4096];
uint8_t random[4096];
uint32_t i;
boolean_t Success;


/* First, Check Manufacturer ID of ADESTO Flash*/

  if ( (FLASH_ReadID()>>16 & 0xFF) == 0x1F )  //check manufacturer ID
  {
         Success=TRUE;
Green_Led_ON(); // DEBUG
  }
  else
  {
         Success=FALSE;
Red_Led_ON(); // DEBUG
  }

/* Now, Check Read/Write Functionality */

    // Generate random numbers and write into Flash 
    for (i=0; i< 4095; i++)
    {
         random[i] = (i+rand())%256;
         WriteDataBuff[i] = random[i];
    }
    FLASH_WriteBuffer(WriteDataBuff, 0x00, 4095);

   // Read back  
    FLASH_ReadBuffer(ReadDataBuff, 0x00, 4095);

    // Write complement 
    for (i=0; i<4095; i++)
    {
         WriteDataBuff[i] = ((uint8_t)~ReadDataBuff[i]);
    }
    FLASH_WriteBuffer(WriteDataBuff, 0x00, 4095);


    // Read and check if success (results consistent with full sequence)
    FLASH_ReadBuffer(ReadDataBuff, 0x00, 4095);
    for (i=0; i<4095; i++)
    {
         if (ReadDataBuff[i] != ((uint8_t)~random[i]) )
         {
             Success=FALSE;
         }
    } 

  
    // Also check unaligned start address (0x01 used here) and smaller than 1 page (222 bytes here)
    for (i=0; i< 222; i++)
    {
         WriteDataBuff[i] = random[i];
    }
    FLASH_WriteBuffer(WriteDataBuff, 0x01, 222);
    FLASH_ReadBuffer(ReadDataBuff, 0x01, 222);
    for (i=0; i<222; i++)
    {
         if (ReadDataBuff[i] != random[i] )
         {
             Success=FALSE;
         }
    } 


  return  Success ;
}


