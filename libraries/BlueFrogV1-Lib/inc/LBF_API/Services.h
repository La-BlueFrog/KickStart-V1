/*******************************************************************************
 * Services.h
 * 
 * Author: La BlueFrog, 2015
 *
 * This program is free software; you can redistribute it and/or modify
 * t under the terms of the GNU General Public License as published by
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
#ifndef __SERVICES_H
#define __SERVICES_H

#include <stdint.h>  //to use uint32_t type below


/* ----- Exported Function Prototypes */

void Delay_ms (volatile uint32_t nTime);
void sysTick_OccurenceCounter_Decrement(void) ;


#endif  /*__SERVICES_H*/

/***************************************************************END OF FILE****/
