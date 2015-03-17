/*******************************************************************************
 * LBF_Interrupts_Cfg.c
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

/* Init of hw required for various services e.g. TimerTick for delay function etc. */


#include "LBF_lowlev_API.h"

#include "LBF_Interrupts_Cfg.h"

/* Privates prototypes --------------------------------------------------*/
static void Assign_System_Interrupts(void);
static void Assign_OnChip_Interrupts();
static void Assign_OnBoard_Interrupts(void);
static void Assign_LBFext_Interrupts(void);
static void Configure_NVIC(void);

/* -----------------------------------------------------------------*/
void LBF_Interrupts_Cfg(void) 
{
        // start SYSCFG clock:
        //RCC_APB2PeriphClockCmd(RCC_APB2ENR_SYSCFGEN, ENABLE);

  	/*** IRQs from STM32 core  */		
	Assign_System_Interrupts();

	/*** IRQs  from STM32 on-chip peripherals */
	Assign_OnChip_Interrupts();

	/*** IRQs from other sources on LBF board (through STM32 GPIO) */
	Assign_OnBoard_Interrupts();

     	/*** IRQs from sources external to LBF board 
             (through LBF connector then STM32 GPIO)  */
	Assign_LBFext_Interrupts();

	Configure_NVIC();
}


/* === Local Functions :=============================================*/


void Assign_System_Interrupts(void) 
    {

    /**  SysTick Interrupt       ****************************************/
    
    //--> Set SysTick for Interrupts every 1ms    
    // See Services.c for principle of operation of Delay funtionality based on SysTick 

    //SysTick_Config( (SystemCoreClock/1000) ) ; ===> Now handled in HAL_Init() section of LBF_BoardInit()
    //CMSIS function that will generate a system tick every 1000*1us = 1ms

      /** Notes :  **/
      /* SystemCoreClock is a system variable defined in system_stm32l1xx.c
      It is passed as parameter to SysTick_Config so that the latter can generate
      a fixed 1us timebase of multiple thereof whatever the value of SystemCoreClk */
      /* The SysTick_Config() function is a CMSIS function which :
         - configures the SysTick Reload register with value passed as function parameter.
         - configures the SysTick IRQ priority to 0x0F: lowest urgency 
           (********CHANGE THAT???*********)
         - resets the SysTick Counter register.        
         - configures the SysTick Counter clock source to be Core Clock Source (HCLK).
         - enable the SysTick Interrupt.
         - starts the SysTick Counter.
      */
	/* ADDITIONAL NOTE about SysTick Interrupts :
	Delay generation is based on a variable (sysTickCounter) decremented in interrupt 
	service routine (ISR) of SysTick. This implies that if Delay_ms() is called from 
	a peripheral ISR process, then the SysTick interrupt must have higher priority 
	(numerically lower) than the peripheral interrupt, otherwise the caller ISR 
	process will be	blocked. 
	Use NVIC_SetPriority() function to change the SysTick interrupt priority.*/
	/* The following post may also be helpful when tinkering with SysTick priority 
	and pre-emption level :
	https://my.st.com/public/STe2ecommunities/mcu/Lists/cortex_mx_stm32/Flat.aspx?RootFolder=https://my.st.com/public/STe2ecommunities/mcu/Lists/	cortex_mx_stm32/STM32%20Interrupt%20priorities%20and%20preemption&FolderCTID=0x01200200770978C69A1141439FE559EB459D7580009C4E14902C3CDE46A77F0FFD06506F5B&currentviews=25
	*/
    }

/* -----------------------------------------------------------------*/

void Assign_OnChip_Interrupts(void) 
    {
    }

/* -----------------------------------------------------------------*/

void Assign_OnBoard_Interrupts(void) 
    {

GPIO_InitTypeDef GPIO_InitStruct;

     GPIO_InitStruct.Pull = GPIO_NOPULL;

     // Pin IRQB (IN) = PA6 - Falling Edge IT
     GPIO_InitStruct.Pin = GPIO_PIN_6;
     GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
     HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

     // Pin ONSTAT (IN) = PB0 -  RISING Edge IT
     GPIO_InitStruct.Pin = GPIO_PIN_0;
     GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
     HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);



    /**  Power ON/OFF Push-Button    
    
    EXTI_InitTypeDef EXTI_InitStruct;  
   
    // connect EXTI_Line0 to ONSTAT and enable it as rising edge IT
    SYSCFG_EXTILineConfig(PWR_ONSTAT_EXTI_PORT, PWR_ONSTAT_SOURCE);
    EXTI_InitStruct.EXTI_Line    = PWR_ONSTAT_EXTI_LINE ; 
                                   //defined in header file 
    EXTI_InitStruct.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct); 

   *******/

    }

/* -----------------------------------------------------------------*/


void Assign_LBFext_Interrupts(void) 
    {
    }

/* -----------------------------------------------------------------*/

void Configure_NVIC(void) 
    {

/* Now handled in HAL_Init() section of LBF_BoardInit()

       // Set SysTick Prority (lower numerical value = higher pre-emption level)
       NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);     
       //4 bits for preemp priority 0 bit for sub priority

       NVIC_SetPriority(SysTick_IRQn, __SysTick_IRQn_PRIO);  //defined in header file 
       // as is used in Delay function, level must be such that it pre-empts ISR that use Delay_ms()
*/


       /* Note - Following assumes NVIC Priority Grouping = 4, 
          i.e. Preemption priority on 4 bits, Sub-priority on 0 bits (i.e. not used) */


       /*** EXTI0_IRQn */
       // Triggered by GPIO-A/B/C/D pins [0] declared as Interrupt
       // In LBF v1.6: PB0 = ONSTAT
	HAL_NVIC_SetPriority(EXTI0_IRQn, __EXTI0_IRQn_PRIO , 0); 
                             // __EXTI0_IRQn_PRIO user-definable (.h)
        HAL_NVIC_EnableIRQ(EXTI0_IRQn);


        /*** EXTI15_10_IRQn */		
        // Triggered by GPIO-A/B/C/D pins [15] to [10] declared as Interrupt
        // In LBF v1.6: PA6 = IRQB
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, __EXTI15_10_IRQn_PRIO , 0); 
                             // __EXTI15_10_IRQn_PRIO user-definable (.h)
        // HAL_NVIC_EnableIRQ(EXTI0_IRQn);  !!!!!! NOT ENABLED for Now



        /*** EXTI9_5_IRQn */		

    }


/***************************************************************END OF FILE****/
