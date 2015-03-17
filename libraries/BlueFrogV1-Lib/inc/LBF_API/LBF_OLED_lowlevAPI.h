/*******************************************************************************
 * LFB_OLED_lowlevAPI.h
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
#ifndef __LFB_OLED_LOWLEVAPI_H
#define __LFB_OLED_LOWLEVAPI_H

#include <stdint.h>
// required as we declare a function as uint_8 below and
// want to keep this .h self-sufficient
#include "pin_aliases.h"
// same rationale as we use pin names


/* Exported macros --------------------------------------------------------*/

#define OLED_CS_LOW()           GPIO_LOW(OLED_CS_PORT, OLED_CS_PIN)
#define OLED_CS_HIGH()          GPIO_HIGH(OLED_CS_PORT, OLED_CS_PIN)
#define OLED_RS_LOW()           GPIO_LOW(OLED_RS_PORT, OLED_RS_PIN)
#define OLED_RS_HIGH()          GPIO_HIGH(OLED_RS_PORT, OLED_RS_PIN)
#define OLED_RESET_LOW()        GPIO_LOW(OLED_RESET_PORT, OLED_RESET_PIN)
#define OLED_RESET_HIGH()       GPIO_HIGH(OLED_RESET_PORT, OLED_RESET_PIN)

/* Exported constants  */

/* Colors for OLED in rgb565 format */
#define BLACK                   0x0000
#define WHITE                   0xFFFF
#define RED                     0xF800
#define GREEN                   0x07E0
#define BLUE                    0x001F
#define YELLOW                  0xFFE0
#define CYAN                    0x07FF
#define LIGHT_BLUE              0x1C9F
#define ORANGE                  0xFD20

/* Exported functions ------------------------------------------------------- */

// void OLED_Config (uint16_t *fconf);

/* Fonctions de Bas niveau */
uint8_t OLED_SPI_TransferByte (uint8_t octet);
void OLED_SendCmd (uint8_t Value);
void OLED_SendData (uint16_t Value);
void OLED_WriteReg (uint8_t RegName, uint8_t RegValue);
void OLED_DataStart (void);
void OLED_DataEnd (void);

/* Fonctions de Haut niveau */
void OLED_SetRegion(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void OLED_Fill(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color565);
void OLED_DisplayBuffer(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t *buffer);
void OLED_Clear (void);


#endif  /*__LFB_OLED_LOWLEVAPI_H*/

/***************************************************************END OF FILE****/
