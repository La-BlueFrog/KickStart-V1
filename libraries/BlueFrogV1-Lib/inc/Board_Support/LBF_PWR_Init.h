/*******************************************************************************
 * LBF_PWR_Init.h
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
#ifndef __LBF_PWR_INIT_H
#define __LBF_PWR_INIT_H




/* Exported constants --------------------------------------------------------*/

// #define Tempo(x) timeout=0xFFFF; error++; while (x) { if (timeout-- == 0) return error;}

/* Power Management LP3913 */
//#define PWR_FLAG_TIMEOUT            ((uint32_t)0x1000)
//#define PWR_LONG_TIMEOUT            ((uint32_t)(10 * PWR_FLAG_TIMEOUT))

// #define PWR_I2C_SPEED               400000          // 400 kHz
// #define PWR_I2C_DR                  ((uint32_t)0x40005410)

#define PWR_I2C_CHIPID                 0x60
#define PWR_BUCK2_ADDR              0x06
/*****************************************
 * BUCK2 Output Voltage : 1.8V   => 0x41 *
 *                        2.8V   => 0x4B *
 *                        3.3V   => 0x50 *
 *                        RESET  => 0x5F *
 *****************************************/
#define PWR_BUCK2_VDD               0x4D            // 3.0V

/* Exported functions ------------------------------------------------------- */

void LBF_PWR_Init (void);



#endif  /*__LBF_PWR_INIT_H*/

/***************************************************************END OF FILE****/
