/*******************************************************************************
 * LBF_PWR_IOcfg.h
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
#ifndef __LBF_PWR_IOCFG_H
#define __LBF_PWR_IOCFG_H




/* Exported Macros --------------------------------------------------------*/
#define OLED_VDDH_ON()          GPIO_HIGH(OLED_VDDH_PORT, OLED_VDDH_PIN)
#define OLED_VDDH_OFF()         GPIO_LOW(OLED_VDDH_PORT, OLED_VDDH_PIN)

/* Exported functions ------------------------------------------------------- */

void LBF_PWR_IOcfg(void);

// uint8_t PWR_EcrireReg (uint8_t NomReg, uint8_t ValeurReg);
// uint8_t PWR_LireReg (uint8_t NomReg, uint8_t *ValeurReg);

#endif  /*__LBF_PWR_IOCFG_H*/

/***************************************************************END OF FILE****/
