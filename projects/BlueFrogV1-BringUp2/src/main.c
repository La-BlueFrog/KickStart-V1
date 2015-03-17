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

uint16_t fconfig[11];  // configuration file to control some OLED parameters

uint32_t rand();  //returns a value between 0 and RAND_MAX (defined by the compiler, often 32767)
uint16_t color_table[8] = {BLACK, YELLOW, RED, WHITE, GREEN, BLUE, ORANGE, CYAN} ;
uint32_t start_color_index;
uint8_t Xstart, Ystart;
uint16_t random565;

/* ==  Body              =============================== */


    /*---- Initialize and Enable OLED:    -------------------*/
    fconfig[0]=0xFFFF;     
        //so OLED_Config() will use default init value
    LBF_OLED_Init(fconfig);  
        //sets up OLED register and powers on OLED VDDH(13V) 


    /*-------------------------------------------------------*/
    OLED_Fill(0, 0, 160, 128, BLUE);  

    Red_Led_ON();   //just to provide an intermediate status

 
    while(1)
    {
          if ( Get_Slider_Select1() )
          { 
	  Delay_ms(10);
          Xstart = rand()%160;
          random565 = ( ((rand()%32)<<11) + ((rand()%64)<<5) + ((rand()%32)) );
          OLED_Fill(Xstart, 0, rand()%5, 128, random565);

	  Delay_ms(10);
          Ystart = rand()%128;
          random565 = ( ((rand()%32)<<11) + ((rand()%64)<<5) + ((rand()%32)) );
          OLED_Fill(0, Ystart, 160, rand()%5, random565);
          }

          if ( Get_Slider_Select2() )
          {  
             // Fill the 160x128 screens with 8 colors organized as 2 rows of 4 blocks
             // Arguments: Xstart, Ystart, Width, Height, Color in RGB565 format 
	  start_color_index = rand();
          OLED_Fill(0, 0, 40, 64, color_table[(start_color_index+0)%8]);  
          OLED_Fill(40, 0,40, 64, rand()%65536 );
          OLED_Fill(80, 0, 40, 64, color_table[(start_color_index+2)%8]);
          OLED_Fill(120, 0, 40, 64, rand()%65536 );
          OLED_Fill(0, 64, 40, 64, color_table[(start_color_index+4)%8]);
          OLED_Fill(40, 64, 40, 64, rand()%65536 );
          OLED_Fill(80, 64, 40, 64, color_table[(start_color_index+6)%8]);
          OLED_Fill(120, 64, 40, 64, rand()%65536 );
          }


     }
 
    return 0;
}
	

/***************************************************************END OF FILE****/
