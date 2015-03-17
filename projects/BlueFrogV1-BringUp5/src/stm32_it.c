/*******************************************************************************
 * stm32_it.c
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

#include "stm32_it.h"
#include "LBF_lowlev_API.h"


extern PCD_HandleTypeDef hpcd;



/******************************************************************************/
/*             Cortex-M Processor Exceptions Handlers                         */
/******************************************************************************/

/*******************************************************************************
* Function Name  : EXTI0_IRQHandler
* Description    : On/Off du systeme.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI0_IRQHandler(void)
{

  HAL_GPIO_EXTI_IRQHandler(PWR_ONSTAT_PIN);
  // Checks if PWR_ONSTAT_PIN is source of IT
  // if so: clears the IT and calls HAL_GPIO_EXTI_Callback (see below)

}



/*******************************************************************************
* Function Name  : EXTI15_10_IRQHandler
* Description    : IRQ du Power Management.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(PWR_IRQB_PIN);
  // Checks if IRQB is source of IT
  // if so: clears the IT and calls HAL_GPIO_EXTI_Callback (see below)

}

/*******************************************************************************
* Function Name  : EXTI10_IRQHandler
* Description    : IRQ du Power Management.

* Input          : None
* Output         : None

* Return         : None
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{
//    if(EXTI_GetITStatus(EXTI_Line10) != RESET)
    {
        
        //...
    }
}


/*******************************************************************************
* Function Name  : RTC_WKUP_IRQHandler
* Description    : Actualise l'heure toute les secondes.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_WKUP_IRQHandler(void)
{
    /*
    if (RTC_GetITStatus(RTC_IT_WUT) != RESET)
    {
        RTC_ClearITPendingBit(RTC_IT_WUT);
        EXTI_ClearITPendingBit(EXTI_Line20);
        
        ....;
    }
    */
}

/*******************************************************************************
* Function Name  : NMI_Handler
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMI_Handler(void)
{
}

/*******************************************************************************
* Function Name  : HardFault_Handler
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1);
}

/*******************************************************************************
* Function Name  : MemManage_Handler
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1);
}

/*******************************************************************************
* Function Name  : BusFault_Handler
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1);
}

/*******************************************************************************
* Function Name  : UsageFault_Handler
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1);
}

/*******************************************************************************
* Function Name  : SVC_Handler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVC_Handler(void)
{
}

/*******************************************************************************
* Function Name  : DebugMon_Handler
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMon_Handler(void)
{
}

/*******************************************************************************
* Function Name  : PendSV_Handler
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSV_Handler(void)
{
}

/*******************************************************************************
* Function Name  : SysTick_Handler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Handler(void)
{
  HAL_IncTick();
  sysTick_OccurenceCounter_Decrement();
}

/******************************************************************************/
/*                 STM32 Peripherals Interrupt Handlers                       */
/******************************************************************************/

/*******************************************************************************
* Function Name  : USB_HP_CAN1_TX_IRQHandler
* Description    : This function handles USB High Priority or CAN TX interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_HP_CAN1_TX_IRQHandler(void)
{

}

/*******************************************************************************
* Function Name  : USB_IRQHandler
* Description    : This function handles USB Low Priority interrupts
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_IRQHandler(void)
{
      HAL_PCD_IRQHandler(&hpcd);
}

/*******************************************************************************
* Function Name  : USB_FS_WKUP_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_FS_WKUP_IRQHandler(void)
{
//    EXTI_ClearITPendingBit(EXTI_Line18);
}


/**=========================================================================***/
/**==      Interrupt Service Routines CALLBACK FUNCTIONS                  ==***/
/**=========================================================================***/


/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

// Servicing Interrupt from PWR_ONSTAT (power off required)

  if (GPIO_Pin == PWR_ONSTAT_PIN)
  {

        Green_Led_ON();        

        // Power down OLED 
        // Recommended sequence - from DD-160128FC-1A datasheet:
	//	1. Send Display off command
	//	2. Power down VDDH
	//	3. Delay 100ms
	//	(When VDDH reach 0 and panel is completely discharged)
	//	4. Power down VDD & VDDIO 	
	if (Check_VDDH_On())
	// Do not send command if no OLED (else SPI hangs)
	{        // Display off
      		  OLED_WriteReg(0x06, 0x00);
	}
        //!! Need to make this more robust as one may have turned VDDH on
        //despite no OLED present

        Red_Led_ON();        

        // Power down OLED panel (VDDH 14V supply)
        Turn_VDDH_Off();
        Delay_ms(100);  
	    //Caution: TimerTick involved, its IRQ priority must be high (urgent) enough
	    // in Interrupt Configuration files
        
        // wait as long as /ONSTAT is high
        //while(GPIO_ReadInputDataBit(PWR_ONSTAT_GPIO_PORT, PWR_ONSTAT_PIN));
        while(HAL_GPIO_ReadPin(PWR_ONSTAT_GPIO_PORT, PWR_ONSTAT_PIN));

        // Power down VCC_NUM by un-acknowledging PowerAck pin of PMIC
        GPIO_LOW(PWR_POWERACK_GPIO_PORT, PWR_POWERACK_PIN);
  }


// Servicing Interrupt from IRQB 

  if (GPIO_Pin == PWR_IRQB_PIN)
  {
  }


}



/***************************************************************END OF FILE****/
