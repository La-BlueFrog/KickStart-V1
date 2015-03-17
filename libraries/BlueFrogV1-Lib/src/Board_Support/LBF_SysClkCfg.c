/*******************************************************************************
 * LBF_SysClkCfg
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


/* Init of hw required for various services e.g. TimerTick for delay function etc. */


#include "LBF_SysClkCfg.h"
#include "LBF_lowlev_API.h"

/* Privates prototypes -------------------------------------------------------*/


/* Functions -----------------------------------------------------------------*/


/*******************************************************************************/


void LBF_SysClkCfg(void)
{
// Derived from Cube MX Code Generator and EVAL152D USB MS example

  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

	
// Enable HSE Oscillator and Activate PLL with HSE as source 
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE; 
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  { 
    // Error_Handler();
  }

  // Set Voltage scale1 as MCU will run at 32MHz 
  __PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  // Poll VOSF bit of in PWR_CSR. Wait until it is reset to 0 
  // This indicates regulator has reached required voltage level
  while (__HAL_PWR_GET_FLAG(PWR_FLAG_VOS) != RESET) {};

  // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers
  //  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | 
                                 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    // Error_Handler();
  }

   __SYSCFG_CLK_ENABLE();
   // System Configuration Clock
   // The system configuration controller is mainly used to remap the memory accessible in the
   // code area, and manage the external interrupt line connection to the GPIOs.

}

/*
Clock Tree Configuration :
 A INDIQUER ICI  (Xtal fqxy, HSE slections etc)
*/


/***************************************************************END OF FILE****/
