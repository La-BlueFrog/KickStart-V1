/*******************************************************************************
 * inframod_horloge.c
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
#include "inframod_horloge.h"
#include "LBF_OLED_lowlevAPI.h"
//#include "stm32l1xx_conf.h"  //stm32 standard peripherals API


/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Inititalise le Real Time Clock.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void HORLOGE_Init (void)
{
    RTC_InitTypeDef  RTC_InitStruct;
    
    /* Enable the PWR clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    
    /* Allow access to RTC */
    PWR_RTCAccessCmd(ENABLE);
    
    /* Reset RTC Domain */
    RCC_RTCResetCmd(ENABLE);
    RCC_RTCResetCmd(DISABLE);
    
    /* Enable LSE oscillator (32.768 Hz) */
    RCC_LSEConfig(RCC_LSE_ON);
    
    /* Wait till LSE is ready */  
    while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
    
    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    
    /* Configure the RTC data register and RTC prescaler */
    RTC_InitStruct.RTC_AsynchPrediv = 0x7F;
    RTC_InitStruct.RTC_SynchPrediv  = 0xFF;
    RTC_InitStruct.RTC_HourFormat   = RTC_HourFormat_24;
    RTC_Init(&RTC_InitStruct);
    
    /* Enable the RTC Clock */
    RCC_RTCCLKCmd(ENABLE);
    
    /* Wait for RTC APB registers synchronisation */
    RTC_WaitForSynchro();
}

/*******************************************************************************
 * @brief  : Initialisation des interruptions externes du RTC.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void HORLOGE_EXTI_Init(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    
    EXTI_ClearITPendingBit(EXTI_Line20);
    EXTI_InitStructure.EXTI_Line    = EXTI_Line20;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // Enable the RTC Wakeup Interrupt
    NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // Configure the RTC WakeUp Clock source: CK_SPRE (1Hz)
    RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);
    RTC_SetWakeUpCounter(0x0);

    // Enable the RTC Wakeup Interrupt
    RTC_ITConfig(RTC_IT_WUT, ENABLE);

    // Enable Wakeup Counter
    RTC_WakeUpCmd(ENABLE);
}


/*******************************************************************************
 * @brief  : Configure l'heure affichee.
 * @param  : heure: heure de configuration.
 * @return : Rien.
 ******************************************************************************/
void HORLOGE_Config(uint16_t heure)
{
    RTC_TimeTypeDef  RTC_TimeStruct;
    
    if(heure == 2400) {heure = 0;}
    if(heure > 2359) {heure = 1200;}
    if(heure < 0) {heure = 1200;}
    
    // Heure => 12h 00mn 00s AM par defaut
    if(heure < 1200)
        RTC_TimeStruct.RTC_H12     = RTC_H12_AM;
    else
        RTC_TimeStruct.RTC_H12     = RTC_H12_PM;
    RTC_TimeStruct.RTC_Hours   = (uint8_t)(heure / 100);
    RTC_TimeStruct.RTC_Minutes = (uint8_t)(heure % 100);
    RTC_TimeStruct.RTC_Seconds = 0;
    RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);
}
 
/*******************************************************************************
 * @brief  : Afficher l'heure sur l'ecran OLED.
 * @param  : heure: heure a afficher.
 * @return : Rien.
 ******************************************************************************/
void OLED_afficherHeure (void)
{
    uint8_t heure;
    RTC_TimeTypeDef RTC_TimeStruct;
    
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);
    
    heure = (uint8_t)(RTC_TimeStruct.RTC_Hours / 10);
    FONT_afficherSegment(0, 39, heure);
    heure = (uint8_t)(RTC_TimeStruct.RTC_Hours % 10);
    FONT_afficherSegment(32, 39, heure);
    
    //FONT_afficherSegment(64, 39, 10);       // ':'
    OLED_Fill(64, 39, 32, 50, 0x0000);
    
    heure = (uint8_t)(RTC_TimeStruct.RTC_Minutes / 10);
    FONT_afficherSegment(96, 39, heure);
    heure = (uint8_t)(RTC_TimeStruct.RTC_Minutes % 10);
    FONT_afficherSegment(128, 39, heure);
}

/***************************************************************END OF FILE****/
