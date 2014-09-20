/*******************************************************************************
 * stm32_it.c
 * 
 * Copyright 2014 Roman GAUCHI <roman.gauchi@gmail.com>
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



/* Includes ------------------------------------------------------------------*/
#include "stm32_it.h"


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
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        // Reset de l'interruption
        EXTI_ClearITPendingBit(EXTI_Line0);
        
        GPIO_HIGH(LED_VERTE_PORT, LED_VERTE_PIN);
        GPIO_HIGH(LED_ROUGE_PORT, LED_ROUGE_PIN);
        
#if defined (DEBUG)
        xprintf("\n[*] Au revoir ;-(\n");
#else
        // Display off
        OLED_EcrireReg(0x06, 0x00);
        
        // Power down VCC_OLED
        OLED_VDDH_OFF();
#endif
        delay_ms(100);
        
        // Tant que ONSTAT est a l'etat haut
        while(GPIO_ReadInputDataBit(PWR_ONSTAT_GPIO_PORT, PWR_ONSTAT_PIN));
        
        // Power down VCC_NUM
        GPIO_LOW(PWR_POWERACK_GPIO_PORT, PWR_POWERACK_PIN);
    }
}

/*******************************************************************************
* Function Name  : EXTI10_IRQHandler
* Description    : IRQ du Power Management.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line10) != RESET)
    {
        // Reset de l'interruption
        EXTI_ClearITPendingBit(EXTI_Line10);
        
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
        
        GPIO_TOGGLE(LED_VERTE_PORT, LED_VERTE_PIN);
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
    CTR_HP();
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
    USB_Istr();
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
    EXTI_ClearITPendingBit(EXTI_Line18);
}

/***************************************************************END OF FILE****/
