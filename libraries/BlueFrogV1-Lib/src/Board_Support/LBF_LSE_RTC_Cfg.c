/*******************************************************************************
 * LBF_LSE_RTC_Cfg.c
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


#include "LBF_LSE_RTC_Cfg.h"
#include "LBF_lowlev_API.h"

/* Privates prototypes -------------------------------------------------------*/


/* Functions -----------------------------------------------------------------*/


/*******************************************************************************/


void LBF_LSE_RTC_Cfg(void)
{
RCC_OscInitTypeDef RCC_OscInitStruct = {0};
RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  // Enable LSE Oscillator 
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON; 
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) //on en sort jamais si LSE choisi!!!
  { 
    // Error_Handler();
  }

  // RTC Clock Inits
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

}



/***************************************************************END OF FILE****/
