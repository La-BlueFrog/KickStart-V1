/*******************************************************************************
 * LBF_Board_Init.c
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


#include "LBF_Board_Init.h"

#include "LBF_lowlev_API.h"

#include "LBF_SysClkCfg.h"
#include "LBF_LSE_RTC_Cfg.h"
#include "LBF_I2C2_Init.h"
#include "LBF_SPI1_Init.h"
#include "LBF_SPI2_Init.h"
#include "LBF_UART1_Init.h"
#include "LBF_I2C2_IOcfg.h"
#include "LBF_SPI1_IOcfg.h"
#include "LBF_SPI2_IOcfg.h"
#include "LBF_UART1_IOcfg.h"
#include "LBF_FLASH_IOcfg.h"
#include "LBF_LED+Switches_IOcfg.h"
#include "LBF_PWR_IOcfg.h"
#include "LBF_OLED_IOcfg.h"
#include "LBF_PWR_IOcfg.h"
#include "LBF_Conn_IOcfg_UserDefd.h"  
#include "LBF_Interrupts_Cfg.h"
#include "LBF_PWR_Init.h"
#include "LBF_FLASH_Init.h"
#include "LBF_OLED_Init.h"

#include "User_Configuration.h"


/* Privates prototypes -------------------------------------------------------*/
static void HAL_Init_Private(void);


/* Functions -----------------------------------------------------------------*/


/*******************************************************************************/

/** Full Board Initializations and Configurations          **/
/** except OLED VDDH powering and init, handled separately **/
/** (as OLED may or may not be present)                    **/


void LBF_Board_Init(void) 
{

/* -------- Set Global Constants to select and condition signals*/
/* -------- made available on external connector (header pi     */
/* -------- These are defined by user in source file :          */
/* --------       User_Configuration.c                          */

     User_Configuration();


/* -------- Configure eFlash Prefetch,        ---------------- */
/*          Init and launch SysTick time base -----------------*/
/*          Set NVIC for pre-emption only (no sub-prio)    ----*/
    
     HAL_Init_Private();


/* -------- Deal with PMIC in priority :     ------------------*/
/*          Acknowledge power by setting PowerAck,         ----*/
/*          then do nothing as long as PMIC asserts its NRST --*/

    /* First, enable GPIO clocks */
     __GPIOA_CLK_ENABLE();
     __GPIOB_CLK_ENABLE();
     __GPIOC_CLK_ENABLE();
     __GPIOD_CLK_ENABLE();

     LBF_PWR_IOcfg();  	// PMIC IO interfacing (other than SCL/SDA pins)
     // i.e pins NRST (from PMIC), POWERACK 
     // Also disables DC-DC upconv for OLED

    /* Acknowledge power to PMIC via pin PowerAck */
    GPIO_HIGH(PWR_POWERACK_GPIO_PORT, PWR_POWERACK_PIN);

    /* Wait for PMIC to release its NRST output pin ==> fully stable power */
    while(HAL_GPIO_ReadPin(PWR_NRST_GPIO_PORT, PWR_NRST_PIN) == GPIO_PIN_RESET);



/* -------- Configure system clocks with default values  -------*/
/* --       User may override this in his own code if desired   */
/* -- NOTE: LSE not handled here (long start-up not compatible  */
/* --       with max latency to acknowledge PMIC after power-up)*/

     LBF_SysClkCfg();  


/* -------- Set board VDD level to 3V  -------------------------*/
/* ---      This requires I2C2 set-up to program PMIC       ----*/

     __I2C2_CLK_ENABLE();

     // configure SCL/SDA pins (PMIC I2C interface)
     LBF_I2C2_IOcfg();   

     // Initialize on-chip I2C peripheral IP
     LBF_I2C2_Init();    

     // Configuration PMIC for 3.0V VCC_NUM on board 
     //  (also for charge current limit to 100mA)
     LBF_PWR_Init();    

    

/* --------  STM32 IO Configuration  ------------------------  */

    /* First, enable GPIO clocks */
     __GPIOA_CLK_ENABLE();
     __GPIOB_CLK_ENABLE()  ;
     __GPIOC_CLK_ENABLE();
     __GPIOD_CLK_ENABLE();

    /* Fixed configuration IOs: */
     LBF_SPI1_IOcfg();		// interfacing with: OLED
     LBF_SPI2_IOcfg();   	// interfacing with: Data Flash
     LBF_LED_IOcfg();  		// LED IO interfacing
     LBF_SlideSwitch_IOcfg();  	// Slider IO switch interfacing
     LBF_FLASH_IOcfg();  	// Data Flash IO interfacing
     LBF_OLED_IOcfg();          // OLED IO interfacing

    /* User-definable IO configurations : */
     LBF_Conn_IOcfg_UserDefd();  


/* -------- On-Chip Peripheral Inits  -----------------------  */  
    
    /* Always-enabled peripherals : */

     LBF_SPI1_Init();  // used by OLED
     LBF_SPI2_Init();  // used by Data Flash


    /* User-enabled peripherals : */

    if ((HEADER_POS1_ASSIGN == Uart1_Rx) || (HEADER_POS2_ASSIGN == Uart1_Tx)) 
    {
     LBF_UART1_Init(); 
     // optionnally available on external connector (Tx and Rx only)
    }
    


/* --------  Interrupt Sources to STM32 + priorities  ----------  */

     LBF_Interrupts_Cfg();


/* --------  On-board hw initialization  ------------------------  */
    
     //Data Flash
     LBF_FLASH_Init();   


    // OLED not initialized here but under control of application
    // so thats screen is powered on only if OLED is present and needs to be on



/* --------  External 32KHz (Low-Speed External, LSE) init for RTC -*/
/* --------  (oscillator start-up takes some time)                --*/

    LBF_LSE_RTC_Cfg();


}


/*******************************************************************************/

/********************************************************************
 * HAL_Init_Private():    
 *     In-lining of HAL_Init() with custom SysTick priority, 
 *     defined by _SysTick_IRQn_PRIO                        
 ********************************************************************/
/* @brief This function configures the Flash prefetch, 
 *        Configures time base source and NVIC   
 * @note This function is called at the beginning of program after reset and before 
 *       the clock configuration
 * @note The time base configuration is based on MSI clock when exiting from Reset.
 *       Once done, time base tick start incrementing.  
 *        In the default implementation,Systick is used as source of time base.
 *        the tick variable is incremented each 1ms in its ISR.
 */
 
void HAL_Init_Private(void) 
{

#if (PREFETCH_ENABLE != 0)   
     __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
#endif

     HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
     	    // Leads to 4 bits to define preemption priority 
            // and 0 for sub-priority (i.e., not used)

     HAL_InitTick(__SysTick_IRQn_PRIO);   
    	    // Use SysTick as time base source and configure 1ms tick 
            // __SysTick_IRQn_PRIO is defined in UserConfiguration file

     // HAL_MspInit() not called as empty anyway - not used

}




/***************************************************************END OF FILE****/
