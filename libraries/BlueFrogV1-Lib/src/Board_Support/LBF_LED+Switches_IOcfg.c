/*******************************************************************************
 * LBF_LED+Switches_IOcfg.c
 * 
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


#include "LBF_lowlev_API.h"

#include "LBF_LED+Switches_IOcfg.h"



/*******************************************************************************
* Function Name  : Led_Config
* Description    : configure the Read/Write LEDs.
* Input          : None.
* Return         : None.
*******************************************************************************/
void LBF_LED_IOcfg(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

  // Std CMOS output, no pull-up/-down resistor, low speed
  // Red LED = PA2
  // Green LED = PA3
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/*******************************************************************************
* Function Name  : Slide_Config
* Description    : Configure l'interrupteur Slide.
* Input          : None.
* Return         : None.
*******************************************************************************/
void LBF_SlideSwitch_IOcfg(void)
{
GPIO_InitTypeDef GPIO_InitStruct;

  // Input, pull-up resistor
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;

  //Slider Switch Position 1 = PC12    
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  //Slider Switch Position 2 = PA15    
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


}





/******************** BELOW: USB RELATED *************************************/

/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : Configures USB Clock input (48MHz)
* Input          : None.
* Return         : None.
*******************************************************************************/

/*******************************************************************************
* Function Name  : Enter_LowPowerMode
* Description    : Power-off system clocks and power while entering suspend mode
* Input          : None.

* Return         : None.
*******************************************************************************/


/*******************************************************************************
* Function Name  : Leave_LowPowerMode
* Description    : Restores system clocks and power while exiting suspend mode

* Input          : None.
* Return         : None.
*******************************************************************************/


/*******************************************************************************
* Function Name  : USB_Interrupts_Config

* Description    : Configures the USB interrupts
* Input          : None.
* Return         : None.
*******************************************************************************/

/*******************************************************************************
* Function Name  : USB_Configured_LED
* Description    : Turn ON the Read/Write LEDs.
* Input          : None.
* Return         : None.
*******************************************************************************/


/*******************************************************************************
* Function Name  : USB_NotConfigured_LED
* Description    : Turn off the Read/Write LEDs.
* Input          : None.
* Return         : None.
*******************************************************************************/


/*******************************************************************************
* Function Name  : USB_Cable_Config
* Description    : Software Connection/Disconnection of USB Cable.
* Input          : None.
* Return         : Status
*******************************************************************************/


/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

/*******************************************************************************
* Function Name  : HexToChar.
* Description    : Convert Hex 32Bits value into char.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

/*******************************************************************************
* Function Name  : MAL_Config
* Description    : MAL_layer configuration
* Input          : None.
* Return         : None.
*******************************************************************************/

/*******************************************************************************
* Function Name  : Set_EXTI
* Description    : Configure Interrupt Sources
* Input          : None.
* Return         : None.
*******************************************************************************/

/*
void Set_EXTI(void)
{
 
    EXTI_InitTypeDef EXTI_InitStructure;
    
    // Enable the SYSCFG module clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    
    // Configure the EXTI line 18 connected internally to the USB IP
    EXTI_ClearITPendingBit(EXTI_Line18);
    EXTI_InitStructure.EXTI_Line    = EXTI_Line18;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    // MAL configuration
    // MAL_Config(); 
}
*/


/***************************************************************END OF FILE****/
