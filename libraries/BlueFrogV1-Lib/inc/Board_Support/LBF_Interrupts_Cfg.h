/*******************************************************************************
 * LBF_Interrupts_Cfg.h
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





/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_INTERRUPTS_CFG_H
#define __LBF_INTERRUPTS_CFG_H



/* ---------------- Exported Function Prototypes */

void LBF_Interrupts_Cfg(void) ;



/* ---------------  Interrupt Mapping  ---------------------- */

/**********  EXTI Interrupts : *************/

/*  IT Sources assigned to lines EXTI0 to EXTI15 (freely assignable on STM32) */
/*  (several IT sources may be assigned same line) (tbc)                      */

#define	PWR_ONSTAT_EXTI_LINE	EXTI_Line0
//#define	xxx	EXTI_Line1
//#define	xxx	EXTI_Line2
//#define	xxx	EXTI_Line3
//#define	xxx	EXTI_Line4
//#define	xxx	EXTI_Line5
//#define	xxx	EXTI_Line6
//#define	xxx	EXTI_Line7
//#define	xxx	EXTI_Line8
//#define	xxx	EXTI_Line9
//#define	xxx	EXTI_Line10
//#define	xxx	EXTI_Line11
//#define	xxx	EXTI_Line12
//#define	xxx	EXTI_Line13
//#define	xxx	EXTI_Line14
//#define	xxx	EXTI_Line15

/*  EXTI16 - assigned to PVD output on STM32 */
/*  EXTI17 - assigned to RTC alarm on STM32 */
/*  EXTI18 - assigned to USB device peripheral on STM32 */
/*  EXTI19 - assigned to RTC Tamper and TimeStamp on STM32 */
/*  EXTI20 - assigned to RT Wake-Up on STM32 */
/*  EXTI21 - assigned to Comparator1 Event on STM32 */
/*  EXTI22 - assigned to Comparator2 Event on STM32 */
/*  EXTI23 - assigned to Comparator Channel Acquisition on STM32 */


/* ---------------  Interrupt Priorities for NVIC  ---------------------- */

#define	__SysTick_IRQn_PRIO	0x4
// as is used in Delay function, level must be such that it pre-empts ISR that use Delay_ms()

#define __USB_LP_IRQn_PRIO	0x7
// was originally hard-coded to 0x7 by ST in reference usbd_conf.c


#define	__EXTI0_IRQn_PRIO	0xA	// ONSTAT pin from PMIC, triggers power-on/-off
#define	__EXTI15_10_IRQn_PRIO   0xF
//#define	EXTI9_5_IRQn_PRIO		xxx


//**********  A FAIRE :  faire apparaitre NVIC Setting explcite pour SysTick et reflechir à la bonne prio à donner



#endif  /*__LBF_INTERRUPTS_CFG_H */

/***************************************************************END OF FILE****/
