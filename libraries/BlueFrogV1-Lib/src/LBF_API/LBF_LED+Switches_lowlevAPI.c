/*******************************************************************************
 * LBF_LED+Switches_lowlevAPI.c
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
 ******************************************************************************/


#include "LBF_lowlev_API.h"



/*******************************************************************************
* Function Name  : Red_Led_ON
* Description    : Switched Red LED On.
* Return         : None.
*******************************************************************************/
void Red_Led_ON(void)
{
    GPIO_HIGH(LED_RED_PORT, LED_RED_PIN);
}

/*******************************************************************************
* Function Name  : Red_Led_OFF
* Description    : Switched Red LED Off.
* Return         : None.
*******************************************************************************/
void Red_Led_OFF(void)
{
    GPIO_LOW(LED_RED_PORT, LED_RED_PIN);
}

/*******************************************************************************
* Function Name  : Red_Led_TOGGLE
* Description    : Toggles Red LED.
* Return         : None.
*******************************************************************************/
void Red_Led_TOGGLE(void)
{
    GPIO_TOGGLE(LED_RED_PORT, LED_RED_PIN);
}

/*******************************************************************************
* Function Name  : Green_Led_ON
* Description    : Switched Green LED On.
* Return         : None.
*******************************************************************************/
void Green_Led_ON(void)
{
    GPIO_HIGH(LED_GREEN_PORT, LED_GREEN_PIN);
}

/*******************************************************************************
* Function Name  : Green_Led_OFF
* Description    : Switched Green LED Off.
* Return         : None.
*******************************************************************************/
void Green_Led_OFF(void)
{
    GPIO_LOW(LED_GREEN_PORT, LED_GREEN_PIN);
}

/*******************************************************************************
* Function Name  : Green_Led_TOGGLE
* Description    : Toggles Green LED.
* Return         : None.
*******************************************************************************/
void Green_Led_TOGGLE(void)
{
    GPIO_TOGGLE(LED_GREEN_PORT, LED_GREEN_PIN);
}

/*******************************************************************************
* Function Name  : Get_Slider_Select1
* Description    : Determines if slider is in position #1.
* Return         : True/False
*******************************************************************************/
boolean_t Get_Slider_Select1(void)
{
//  return( (!GPIO_ReadInputDataBit(SLIDE_1_GPIO_PORT, SLIDE_1_PIN)==1)? TRUE:FALSE );
  return( (!HAL_GPIO_ReadPin(SLIDE_1_GPIO_PORT, SLIDE_1_PIN)==GPIO_PIN_SET)? TRUE:FALSE );
}

/*******************************************************************************
* Function Name  : Get_Slider_Select2
* Description    : Determines if slider is in position #2.
* Return         : True/False
*******************************************************************************/
boolean_t Get_Slider_Select2(void)
{
  return( (!HAL_GPIO_ReadPin(SLIDE_2_GPIO_PORT, SLIDE_2_PIN)==GPIO_PIN_SET)? TRUE:FALSE );
}


/***************************************************************END OF FILE****/
