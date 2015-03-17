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
    LBF_emWin_Init();


    Red_Led_OFF();



/* ================================================================ */
/*   Application Code Below                                         */
/* ================================================================ */

/* ==  User Declarations ========================================== */

uint16_t fconfig[11];  // configuration file to control some OLED parameters
GUI_MEMDEV_Handle hMemDevice;  //handle to a memory device


/* ==  Body              ========================================== */

   fconfig[0]=0xFFFF;  // to use default settings
   LBF_OLED_Init(fconfig);  
        //sets up OLED register and powers on OLED VDDH(13V) 


   OLED_Fill(0, 0, 160, 128, CYAN);

   Red_Led_ON();


  /*** Start Demo *******************************************************/

  /* Different options posible */ 
  /* Use Display Cache or Use Memory Device or use Banded Memory Device */
  /* With 32K SRAM only the latter allows to cover full screen */


  // =============================================================
  // == Using the dislay cache  ==================================

  // Usage of display cache can be enabled through parameters of function 
  // GUIDRV_FlexColor_SetFunc() called in LCDConf_FlexColor_LBF.c
  // found in library LBF_STemWin

  // !!! ISSUE !!!
  // XSIZE_PHYS x YSIZE_PHYS (defined in above files) need to be set to 160x128 
  // to hold full display. However at 16bpp that represents about 40BK
  // but available SRAM is only 32KB...
  // Work-Around: define a smaller display cache (XSIZE_PHYS, YSIZE_PHYS)
  // -- but will not allow to address full screen

  // Not much interest vs use of "Memory Device", below, anyway
/*
  GUI_SetFont(&GUI_Font20_1);
  GUI_SetTextMode(GUI_TM_TRANS);  // write with transparent background
  GUI_DispStringAt("Hello from La BlueFrog !", LCD_GetXSize()/8, LCD_GetYSize()/2);  
  Green_Led_ON();
*/


  // =============================================================
  // == Using a "Memory Device"  (refer to emWin documentation) 

  // Work with a centered 128x64 window    
  // (cannot cover full screen for same memory limitation as above)
  #define X_FULL_SCREEN  160
  #define Y_FULL_SCREEN  128
  #define MD_X_LEFT  (X_FULL_SCREEN -128)/2
  #define MD_X_RIGHT  160-MD_X_LEFT
  #define MD_Y_TOP   (Y_FULL_SCREEN -64)/2
  #define MD_Y_BOT    128-MD_Y_TOP


  // Create Memory Device (top left & bottom right coordinates) on Layer 0:
  GUI_SelectLayer(0);
  hMemDevice = GUI_MEMDEV_Create(MD_X_LEFT, MD_Y_TOP,  (MD_X_RIGHT-MD_X_LEFT+1), (MD_Y_BOT-MD_Y_TOP+1) );
      // Caution: 
      // Memory allocated by GUI_X_Config in GUIConf_LBF.c must be sufficient to fit MemDevice buffer
      // plus other needs of emWin
      // Else GUI_MEMDEV_Create will fail (returns 0) and operations will be done directly to screen

  // Activate it: 
  GUI_MEMDEV_Select(hMemDevice);

  // Draw Stuff   (refer to emWin documentation)
  GUI_DrawGradientRoundedH( MD_X_LEFT, MD_Y_TOP,  MD_X_RIGHT, MD_Y_BOT, 
                            10, // rounded corner radius
                            0xFF0000, 0xFFFF00); // red to yellow
  GUI_SetPenSize(6);
  GUI_DrawLine(MD_X_LEFT, MD_Y_TOP, MD_X_RIGHT, MD_Y_BOT);
  GUI_DrawLine(MD_X_LEFT, MD_Y_BOT, MD_X_RIGHT, MD_Y_TOP);

  GUI_SetFont(&GUI_Font13_1);
  GUI_SetColor(GUI_BLACK);
  GUI_SetTextMode(GUI_TM_TRANS);  // write with transparent background
  GUI_DispStringAt("Hello !\n", MD_X_LEFT+10, MD_Y_TOP+10 );  

  // Copy to display
  GUI_MEMDEV_CopyToLCD(hMemDevice);

  // Free memory
  GUI_MEMDEV_Delete(hMemDevice);


  // =============================================================
  // == Using a "Banded Memory Device"  (refer to emWin documentation) 
  // == (Banding, aka tiling, allows to cover full screen by processing
  // ==  a number of bands successively)

  //TODO
  // use function: GUI_MEMDEV_Draw (GUI_RECT * pRect, GUI_CALLBACK_VOID_P * pfDraw, 
  //                 void* pData, int NumLines, int Flags);



while(1);

 
}



/***************************************************************END OF FILE****/
