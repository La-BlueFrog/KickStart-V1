/*******************************************************************************
 * inframod_fat16.h
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
#ifndef __INFRAMOD_FAT16_H
#define __INFRAMOD_FAT16_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx.h"
#include "inframod_spi_flash.h"

#if defined (DEBUG)
#include "inframod_uart.h"
#include "xprintf.h"
#endif

/* Exported Constantes -------------------------------------------------------*/

#define FAT16_DEBUT_ALLOC       0x400       // debut de la table d'allocation
#define FAT16_TAILLE_ALLOC      0x0         // taille de la table

#define FAT16_DEBUT_RACINE      0x20000      // debut du repertoire racine
#define FAT16_TAILLE_RACINE     0x3C00      // taille du repertoire

#define FAT16_DEBUT_CLUSTER     0x23C00      // debut des "donnees memoire"
#define FAT16_TAILLE_CLUSTER    0x200       // taille d'un cluster (=512)
/*
typedef struct
{
    uint32_t FatStartSector;
    uint32_t FatSectors;
    uint32_t RootDirStartSector;
    uint32_t RootDirSectors;
    uint32_t DataStartSector;
    uint32_t DataSectors;
} FatFs;
*/
/* Exported functions ------------------------------------------------------- */

void FAT16_ListerImageBMP (uint16_t *nbImg, uint16_t *listeBMP, uint32_t addrRacine);
void FAT16_FichierConfig (uint16_t *config);

void FAT16_LocaliserCluster (uint32_t *listeCluster, uint16_t addrCluster);
uint32_t FAT16_ClusterSuivant (uint32_t addrCluster);
void FAT16_LireBuffer (uint8_t *buffer, uint16_t offset, uint16_t numBuffer, uint16_t tailleBuffer, uint32_t *listeCluster);

#endif  /*__INFRAMOD_FAT16_H*/
