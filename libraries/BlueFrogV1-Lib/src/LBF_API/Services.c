/*******************************************************************************
 * Services.c
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



/* Privates prototypes -------------------------------------------------------*/



/* Variables -------------------------------------------------------*/
static uint32_t volatile sysTickCounter;
   // Important to declare as volatile because is set in IRQ service routine and exploited outside it.
   // Without this keywork, risk of unexpected behavior with compiler optimizations turned on.
   // See e.g. this article for an explaination :
   // http://www.embedded.com/electronics-blogs/beginner-s-corner/4023801/Introduction-to-the-Volatile-Keyword


/* Functions -----------------------------------------------------------------*/


/********************************/
/* SERVICE: Delay               */
/* -----------------------------*/

/* Principle of operation :     */
/*  
    1. The SysTick_Config() function is a CMSIS function, implemented in Services_Init(),
       which :
       - configures the SysTick Reload register with value passed as function parameter.
       - configures the SysTick IRQ priority to the lowest value (0x0F).
       - resets the SysTick Counter register.
       - configures the SysTick Counter clock source to be Core Clock Source (HCLK).
       - enable the SysTick Interrupt.
       - starts the SysTick Counter.
    
    2. You may change the SysTick Clock source to be HCLK_Div8 by calling the
       SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8) just after the
       SysTick_Config() function call. The SysTick_CLKSourceConfig() is defined
       inside the misc.c file.

    3. You can change the SysTick IRQ priority by calling the
       NVIC_SetPriority(SysTick_IRQn,...) just after the SysTick_Config() function 
       call. The NVIC_SetPriority() is defined inside the core_cm3.h file.

    4. To adjust the SysTick time base, use the following formula:                          
         Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)   
       - Reload Value is the parameter to be passed for SysTick_Config() function
       - Reload Value should not exceed 0xFFFFFF
*/
/* ADDITIONAL NOTE about SysTick Interrupts :
Delay generation is based on a variable (sysTickCounter) decremented in interrupt service routine (ISR) of SysTick. This implies that if Delay_ms() is called from a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower) than the peripheral interrupt, otherwise the caller ISR process will be
blocked. Use NVIC_SetPriority() function to change the SysTick interrupt priority.*/
/* The following post may also be helpful when tinkering with SysTick priority and pre-emption level :
https://my.st.com/public/STe2ecommunities/mcu/Lists/cortex_mx_stm32/Flat.aspx?RootFolder=https://my.st.com/public/STe2ecommunities/mcu/Lists/cortex_mx_stm32/STM32%20Interrupt%20priorities%20and%20preemption&FolderCTID=0x01200200770978C69A1141439FE559EB459D7580009C4E14902C3CDE46A77F0FFD06506F5B&currentviews=25
*/

/****************
 * @brief  : idle loop for a delay expressed in ms.
 * @param  : nTime - required delay in ms.
 * @return : none.
 ****************/
void Delay_ms (uint32_t volatile nTime)
{
   sysTickCounter = nTime;
   while (sysTickCounter != 0) ;
	// This loop gets interrupted by SysTick IRQ which decrements sysTickCounter
        // So, exit after IRQ has fired nTime i.e. required delay has elapsed}
        // See declaration of sysTickCount above regarding use of "volatile" keyword
}


/*****************/
/* @brief  : SysTick IRQ Servicing   						     
 !!!! --> This function must be called in the SysTick_Handler (in stm32l1_it.c) <-- !!!!
 * @param  : xx.
 * @return : xx.
 ******************************************************************************/    
void sysTick_OccurenceCounter_Decrement(void) 
{
	if (sysTickCounter != 0x00) 
	{
		sysTickCounter--;
	}
}
 


/***************************************************************END OF FILE****/
