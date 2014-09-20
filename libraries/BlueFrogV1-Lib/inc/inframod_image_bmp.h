/*******************************************************************************
 * inframod_image_bmp.h
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
#ifndef __INFRAMOD_IMAGE_BMP_H
#define __INFRAMOD_IMAGE_BMP_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"

#include "inframod_fat16.h"
#include "inframod_oled.h"

#if defined (DEBUG)
#include "inframod_uart.h"
#include "xprintf.h"
#endif

/* Structures ----------------------------------------------------------------*/

typedef struct
{
    char sign [2];              // BM
    uint32_t tailleFichier;     // taille totale de l'image
    uint32_t champ;             // reserved
    uint32_t offsetImg;         // debut des donnees
    uint32_t tailleHeader;      // 40
    uint32_t largeurImg;
    uint32_t hauteurImg;
    uint16_t nbPlan;
    uint16_t bitsParPixels;     // 8, 16, 24, 32
    uint32_t compress;          // 0
    uint32_t tailleImg;         // taille des donnees de l'image
    uint32_t resolHoriz;        // 0
    uint32_t resolVert;         // 0
    uint32_t nbCouleur;
    uint32_t nbCoulImp;         // nombre de couleurs importantes
} header_BMP ;

/* Exported functions ------------------------------------------------------- */

uint8_t BMP_LireImage (uint16_t addrCluster);
void BMP_AfficherLigne (uint8_t ligne, uint16_t *buffer16b, uint8_t largeurImg);


#endif  /*__INFRAMOD_IMAGE_BMP_H*/

/***************************************************************END OF FILE****/
