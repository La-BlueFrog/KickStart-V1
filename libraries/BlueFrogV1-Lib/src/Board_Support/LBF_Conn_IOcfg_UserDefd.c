/*************************************************************************
 * LBF_Conn_IOcfg_UserDefd.c
 * Author: La BlueFrog, 2015
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
2
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

#include "LBF_lowlev_API.h"
#include "LBF_Conn_IOcfg_UserDefd.h"
#include "User_Configuration.h"


/*******************************************************************************
* Description  : Configures GPIO connected to header pins 
*                - either as std GPIO or as selected alternate function
* Input          : None.
* Return         : None.
*******************************************************************************/

// Type of interface provided on connector to be defined by user
// See  User_Configuration.h


// 2 user-definable pins on external connector for La BlueFrog V1
// PA10 = UART Rx or GPIO
// PA9 =  UART Tx or GPIO


void LBF_Conn_IOcfg_UserDefd(void)
{

GPIO_InitTypeDef GPIO_InitStruct;

   // ===== Header Pin #1 :  (i.e. PA10:  UART1_RX or user GPIO)  ===================

   if (HEADER_POS1_ASSIGN == Uart1_Rx)   // --- is UART ----------------------------
   {  

     /* Peripheral clock enable */
    __USART1_CLK_ENABLE();
  
    /**USART1 RX alternate function on PA10
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   }

   else   //---------------------------  PA10 is pure GPIO  ------------------------------
   {
       GPIO_InitStruct.Pin    = HEADER_POS1_PIN; 

       if (HEADER_POS1_ASSIGN == GPOut)   // is GPIO: OUT  (open-drain or std cmos)
       {  
          GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
          GPIO_InitStruct.Pull = GPIO_NOPULL;

          if (HEADER_POS1_GPIOTYPE == OpenDrain)   	
          {
              GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
          }
          else   // (std cmos / default)                
	  {
              GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  }
       }

       else                                // is GPIO: IN  (pull-up/-down or no-pull) - default               
       {
          GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
          if (HEADER_POS1_GPIOTYPE == PUp)
          {
              GPIO_InitStruct.Pull =  GPIO_PULLUP;
          }
          else if (HEADER_POS1_GPIOTYPE == PDown)
          {
              GPIO_InitStruct.Pull =  GPIO_PULLDOWN;
          }
          else  // (NoPull / Default)
	  {
              GPIO_InitStruct.Pull = GPIO_NOPULL;
	  }
       }
       HAL_GPIO_Init(HEADER_POS1_PORT, &GPIO_InitStruct);
   }


   // ===== Header Pin #2 :  (i.e. PA9:  UART1_TX or user GPIO)  ===================

   if (HEADER_POS2_ASSIGN == Uart1_Tx)   // --- is UART ----------------------------
   {  

     /* Peripheral clock enable */
    __USART1_CLK_ENABLE();
  
    /**USART1 TX alternate function on PA9
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   }

   else   //---------------------------  PA9 is pure GPIO  ------------------------------
   {
       GPIO_InitStruct.Pin    = HEADER_POS2_PIN; 

       if (HEADER_POS2_ASSIGN == GPOut)   // is GPIO: OUT  (open-drain or std cmos)
       {  
          GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
          GPIO_InitStruct.Pull = GPIO_NOPULL;

          if (HEADER_POS2_GPIOTYPE == OpenDrain)   	
          {
              GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
          }
          else   // (std cmos / default)                
	  {
              GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  }
       }

       else                                // is GPIO: IN  (pull-up/-down or no-pull) - default               
       {
          GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
          if (HEADER_POS2_GPIOTYPE == PUp)
          {
              GPIO_InitStruct.Pull =  GPIO_PULLUP;
          }
          else if (HEADER_POS2_GPIOTYPE == PDown)
          {
              GPIO_InitStruct.Pull =  GPIO_PULLDOWN;
          }
          else  // (NoPull / Default)
	  {
              GPIO_InitStruct.Pull = GPIO_NOPULL;
	  }
       }
       HAL_GPIO_Init(HEADER_POS2_PORT, &GPIO_InitStruct);
   }




}


/***************************************************************END OF FILE****/
