/*******************************************************************************
 * LBF_PWR_lowlevAPI.h
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
#ifndef __LBF_PWR_LOWLEVAPI_H
#define __LBF_PWR_LOWLEVAPI_H

#include "custom_types.h"  //to use type boolean_t in below prototype and keep this header file self-sufficient
#include <stdint.h>        //same rationale, to use uint8_t below


//#include "pin_aliases.h"

/* Exported constants --------------------------------------------------------*/


/* Exported functions ------------------------------------------------------- */

void Turn_VDDH_On(void);
void Turn_VDDH_Off(void);
boolean_t Check_VDDH_On(void);

uint8_t I2C2_WriteSingleReg (uint8_t ChipID, uint8_t NomReg, uint8_t ValeurReg);
uint8_t I2C2_ReadSingleReg (uint8_t ChipID, uint8_t NomReg);


#endif  /*__LBF_PWR_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
