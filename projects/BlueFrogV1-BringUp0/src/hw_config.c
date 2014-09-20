/*******************************************************************************
 * hw_config.c
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
#include "hw_config.h"

/* Private function prototypes -----------------------------------------------*/
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len);

/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Set_System
* Description    : Configures Main system clocks & power
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_System(void)
{
    /* At this stage the microcontroller clock setting is already configured,
     * this is done through SystemInit() function which is called from startup
     * file (startup_stm32xxx.s) before to branch to application main.
     * To reconfigure the default setting of SystemInit() function, refer to
     * system_stm32xxx.c file
     */
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
     MAL_Config(); 
}

/*******************************************************************************
* Function Name  : Set_USBClock
* Description    : Configures USB Clock input (48MHz)
* Input          : None.
* Return         : None.
*******************************************************************************/
void Set_USBClock(void)
{
    /* Enable USB clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/*******************************************************************************
* Function Name  : Enter_LowPowerMode
* Description    : Power-off system clocks and power while entering suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
    /* Set the device state to suspend */
    bDeviceState = SUSPENDED;
}

/*******************************************************************************
* Function Name  : Leave_LowPowerMode
* Description    : Restores system clocks and power while exiting suspend mode
* Input          : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
    DEVICE_INFO *pInfo = &Device_Info;

    /* Set the device state to the correct state */
    if (pInfo->Current_Configuration != 0)
    {
        /* Device configured */
        bDeviceState = CONFIGURED;
    }
    else
    {
        bDeviceState = ATTACHED;
    }
    /*Enable SystemCoreClock*/
    SystemInit(); 
}

/*******************************************************************************
* Function Name  : USB_Interrupts_Config
* Description    : Configures the USB interrupts
* Input          : None.
* Return         : None.
*******************************************************************************/
void USB_Interrupts_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    
    /* 2 bit for pre-emption priority, 2 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* Enable the USB Wake-up interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USB_FS_WKUP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : Led_Config
* Description    : configure the Read/Write LEDs.
* Input          : None.
* Return         : None.
*******************************************************************************/
void Led_Config(void)
{
    /* Configure the LEDs */
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_AHBPeriphClockCmd(LED_VERTE_CLK | LED_ROUGE_CLK, ENABLE);
    
    // Configure la led LD2 en sortie :
    GPIO_InitStructure.GPIO_Pin   = LED_VERTE_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(LED_ROUGE_PORT, &GPIO_InitStructure);
    
    // Configure la led LD3 en sortie :
    GPIO_InitStructure.GPIO_Pin   = LED_ROUGE_PIN;
    GPIO_Init(LED_ROUGE_PORT, &GPIO_InitStructure);
    
    GPIO_LOW(LED_VERTE_PORT, LED_VERTE_PIN);
    GPIO_LOW(LED_ROUGE_PORT, LED_ROUGE_PIN);
}

/*******************************************************************************
* Function Name  : Slide_Config
* Description    : Configure l'interrupteur Slide.
* Input          : None.
* Return         : None.
*******************************************************************************/
void Slide_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    // Demarrage des Horloges :
    RCC_AHBPeriphClockCmd(SLIDE_1_GPIO_CLK | SLIDE_2_GPIO_CLK, ENABLE);
    
    // Configure le Slide 1 en entree (pull-up) :
    GPIO_InitStruct.GPIO_Pin   = SLIDE_1_PIN;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(SLIDE_1_GPIO_PORT, &GPIO_InitStruct);
    
    // Configure le Slide 2 en entree :
    GPIO_InitStruct.GPIO_Pin   = SLIDE_2_PIN;
    GPIO_Init(SLIDE_2_GPIO_PORT, &GPIO_InitStruct);
}

/*******************************************************************************
* Function Name  : Led_Rouge_ON
* Description    : Allume la led rouge.
* Return         : None.
*******************************************************************************/
void Led_Rouge_ON(void)
{
    GPIO_HIGH(LED_ROUGE_PORT, LED_ROUGE_PIN);
}

/*******************************************************************************
* Function Name  : Led_Rouge_OFF
* Description    : Etteint la led rouge.
* Return         : None.
*******************************************************************************/
void Led_Rouge_OFF(void)
{
    GPIO_LOW(LED_ROUGE_PORT, LED_ROUGE_PIN);
}

/*******************************************************************************
* Function Name  : Led_Verte_ON
* Description    : Allume la led verte.
* Return         : None.
*******************************************************************************/
void Led_Verte_ON(void)
{
    GPIO_HIGH(LED_VERTE_PORT, LED_VERTE_PIN);
}

/*******************************************************************************
* Function Name  : Led_Verte_OFF
* Description    : Etteint la led verte.
* Return         : None.
*******************************************************************************/
void Led_Verte_OFF(void)
{
    GPIO_LOW(LED_VERTE_PORT, LED_VERTE_PIN);
}

/*******************************************************************************
* Function Name  : Led_RW_ON
* Description    : Allume la led de lecture/ecriture sur la FLASH.
* Input          : None.
* Return         : None.
*******************************************************************************/
void Led_RW_ON(void)
{
    GPIO_HIGH(LED_VERTE_PORT, LED_VERTE_PIN);
}

/*******************************************************************************
* Function Name  : Led_RW_OFF
* Description    : Etteint la led de lecture/ecriture sur la FLASH.
* Input          : None.
* Return         : None.
*******************************************************************************/
void Led_RW_OFF(void)
{
    GPIO_LOW(LED_VERTE_PORT, LED_VERTE_PIN);
}

/*******************************************************************************
* Function Name  : USB_Configured_LED
* Description    : Turn ON the Read/Write LEDs.
* Input          : None.
* Return         : None.
*******************************************************************************/
void USB_Configured_LED(void)
{
    ;//GPIO_HIGH(LED_ROUGE_PORT, LED_ROUGE_PIN);
}

/*******************************************************************************
* Function Name  : USB_NotConfigured_LED
* Description    : Turn off the Read/Write LEDs.
* Input          : None.
* Return         : None.
*******************************************************************************/
void USB_NotConfigured_LED(void)
{
    ;//GPIO_LOW(LED_ROUGE_PORT, LED_ROUGE_PIN);
}

/*******************************************************************************
* Function Name  : USB_Cable_Config
* Description    : Software Connection/Disconnection of USB Cable.
* Input          : None.
* Return         : Status
*******************************************************************************/
/*
 * For STM32L15xx devices it is possible to use the internal USB pullup
 * controlled by register SYSCFG_PMC (refer to RM0038 reference manual for
 * more details).
 * It is also possible to use external pullup (and disable the internal pullup)
 * by setting the define USB_USE_EXTERNAL_PULLUP in file platform_config.h
 * and configuring the right pin to be used for the external pull up configuration.
 * To have more details on how to use an external pull up, please refer to 
 * STM3210E-EVAL evaluation board manuals.
 */
void USB_Cable_Config (FunctionalState NewState)
{
    if (NewState != DISABLE)
    {
        SYSCFG_USBPuCmd(ENABLE);
    }
    else
    {
        SYSCFG_USBPuCmd(DISABLE);
    }
}

/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
    uint32_t Device_Serial0, Device_Serial1, Device_Serial2;
    
    Device_Serial0 = *(uint32_t*)ID1;
    Device_Serial1 = *(uint32_t*)ID2;
    Device_Serial2 = *(uint32_t*)ID3;
    
    Device_Serial0 += Device_Serial2;
    
    if (Device_Serial0 != 0)
    {
        IntToUnicode (Device_Serial0, &MASS_StringSerial[2] , 8);
        IntToUnicode (Device_Serial1, &MASS_StringSerial[18], 4);
    }
}

/*******************************************************************************
* Function Name  : HexToChar.
* Description    : Convert Hex 32Bits value into char.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void IntToUnicode (uint32_t value , uint8_t *pbuf , uint8_t len)
{
  uint8_t idx = 0;
  
  for( idx = 0 ; idx < len ; idx ++)
  {
    if( ((value >> 28)) < 0xA )
    {
      pbuf[ 2* idx] = (value >> 28) + '0';
    }
    else
    {
      pbuf[2* idx] = (value >> 28) + 'A' - 10; 
    }
    
    value = value << 4;
    
    pbuf[ 2* idx + 1] = 0;
  }
}

/*******************************************************************************
* Function Name  : MAL_Config
* Description    : MAL_layer configuration
* Input          : None.
* Return         : None.
*******************************************************************************/
void MAL_Config(void)
{
    MAL_Init(0);
}

/***************************************************************END OF FILE****/
