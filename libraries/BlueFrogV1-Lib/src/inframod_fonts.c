/*******************************************************************************
 * inframod_fonts.c
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
#include "inframod_fonts.h"


/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Afficher sur l'ecran oled un chiffre 7 segment.
 * @param  : x, y: positionnement du segment
 *           numSeg: numero du segment a afficher (':' => 10)
 * @return : Rien.
 ******************************************************************************/
void FONT_afficherSegment(uint8_t x, uint8_t y, uint8_t numSeg)
{
    int8_t i, j;
    
    OLED_SetRegion(x, y, 32, 50);
    
    OLED_DataStart();
    for(i=0; i<50; i++)
    {
        for(j=31; j>=0; j--)
        {
            if(((FontNumSeg[numSeg*50+i] >> j) & 1) == 1)
                OLED_EnvoyerData(0xFFFF);
            else
                OLED_EnvoyerData(0x0000);
        }
    }
    OLED_DataEnd();
}

/***************************************************************END OF FILE****/
