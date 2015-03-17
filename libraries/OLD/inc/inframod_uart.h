/*******************************************************************************
 * inframod_uart.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INFRAMOD_UART_H
#define __INFRAMOD_UART_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"


//#include "inframod_board.h"
#include "pin_aliases.h"


/* Exported functions ------------------------------------------------------- */
void UART_Init (void);

void UART_EnvoyerData (uint8_t data);
uint8_t UART_RecevoirData (void);
void UART_EnvoyerChaine(char *chaine);


#endif  /*__INFRAMOD_UART_H*/

/***************************************************************END OF FILE****/
