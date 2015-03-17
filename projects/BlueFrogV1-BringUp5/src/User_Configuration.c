/*******************************************************************************
 * User_Configuration.c
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
 *************************************************************************/

#include "User_Configuration.h"

HeaderAssignment_t 	HEADER_POS1_ASSIGN, HEADER_POS2_ASSIGN ;
PinConditioning_t 	HEADER_POS1_GPIOTYPE, HEADER_POS2_GPIOTYPE ;


void User_Configuration(void)
{


/* ===================================================================== */
/* === Following parameters to be set-up by user ======================= */
/* ===  according to her/his requirements        ======================= */
/* ===================================================================== */

/* *****  Assignment of signals to external connector (header pins)   ****/
/* *****  (missing or invalid assignment leads to usage of default)   ****/


// -------  Position 1 -----------------:

        // Nature of STM32 signal provided on this header position
        // Valid options :  Uart1_Rx /  GPOut  /  GPIn (default)
HEADER_POS1_ASSIGN  	=  Uart1_Rx; 

        // Conditioning of signal selected above 
        // Valid options if Uart1_Rx 	:  NA  (parameter disregarded)
        // Valid options if GPOut 	:  OpenDrain / StdCmos (default)
        // Valid options if GPIn 	:  PUp / PDown/ NoPull (default)
HEADER_POS1_GPIOTYPE 	=  NA;


// -------  Position 2 -----------------:

        // Nature of STM32 signal provided on this header position
        // Valid options :  Uart1_Tx /  GPOut  /  GPIn (default)
HEADER_POS2_ASSIGN  	=  Uart1_Tx; 

        // Conditioning of signal selected above 
        // Valid options if Uart1_Tx 	:  NA  (parameter disregarded)
        // Valid options if GPOut 	:  OpenDrain / StdCmos (default)
        // Valid options if GPIn 	:  PUp / PDown/ NoPull (default)	
HEADER_POS2_GPIOTYPE 	=  NA;



}


/***************************************************************END OF FILE****/

