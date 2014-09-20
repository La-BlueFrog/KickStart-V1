/*******************************************************************************
 * inframod_image_bmp.c
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
#include "inframod_image_bmp.h"


/* Privates prototypes -------------------------------------------------------*/
static uint32_t little_endian_32b (uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);
static uint16_t little_endian_16b (uint8_t data1, uint8_t data2);
static uint16_t convert_16b (uint32_t data24b);

/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Lire une image BMP de taille 160x128 en memoire FLASH.
 * @param  : addrCluster: adresse du premier cluster de l'image (2 octets).
 * @return : '0' en cas de reussite.
 ******************************************************************************/
uint8_t BMP_LireImage(uint16_t addrCluster)
{
    uint8_t buffer[480], r, v, b;
    uint16_t ligneImg[160], i, j, tailleData, offsetHead;
    uint32_t addrImg, largeurImg, hauteurImg;
    uint32_t listeCluster[120];
    
    // Initialisation du buffer de ligne
    for(i=0; i<480; i++) {buffer[i] = 0x00;}
    
    addrImg = FAT16_DEBUT_CLUSTER + addrCluster * FAT16_TAILLE_CLUSTER;
    FLASH_ReadBuffer(buffer, addrImg, 30);
    
    // Test de l'image BMP
    if (buffer[0] != 0x42 && buffer[1] != 0x4D) {return 1;}
    
    offsetHead = little_endian_16b(buffer[10], buffer[11]);
    tailleData = little_endian_16b(buffer[28], buffer[29]);
    largeurImg = little_endian_32b(buffer[18], buffer[19], buffer[20], buffer[21]);
    hauteurImg = little_endian_32b(buffer[22], buffer[23], buffer[24], buffer[25]);
    
    // Securite des taille de donnees
    if (largeurImg > (uint32_t)(160)) {return 2;}
    if (hauteurImg > (uint32_t)(128)) {return 2;}
    
    // Recherche des donnees en memoire :
    FAT16_LocaliserCluster(listeCluster, addrCluster);
    
#if defined (DEBUG)
    xprintf("\nIMG: larg(%d), haut(%d)", largeurImg, hauteurImg);
#endif
    
    // Lecture et affichage de l'image ligne par ligne :
    for(i=0; i<hauteurImg; i++)
    {
        if (tailleData == 8)
        {
            FAT16_LireBuffer(buffer, offsetHead, i, largeurImg, listeCluster);
            for(j=0; j<largeurImg; j++)
            {
                ligneImg[j] = convert_16b((buffer[j]<<16) | (buffer[j]<<8) | (buffer[j]));
            }
        }
        else if (tailleData == 16)
        {
            FAT16_LireBuffer(buffer, offsetHead, i, largeurImg*2, listeCluster);
            for(j=0; j<largeurImg; j++)
            {
                ligneImg[j] = (uint16_t)((buffer[(j*2)+1] << 8) | buffer[(j*2)]);
            }
        }
        else if (tailleData == 24)
        {
            FAT16_LireBuffer(buffer, offsetHead, i, largeurImg*3, listeCluster);
            for(j=0; j<largeurImg; j++)
            {
                b = buffer[(j*3)] >> 3;
                v = buffer[(j*3)+1] >> 2;
                r = buffer[(j*3)+2] >> 3;
                ligneImg[j] = (uint16_t)((r << 11) | (v << 5) | b);
            }
        }
        OLED_AfficherBuffer(0, (uint8_t)(hauteurImg-1-i), (uint8_t)largeurImg, 1, ligneImg);
    }
    
    return 0;
}

/*******************************************************************************
 * @brief  : Rotationner une donnee de 32 bits en little endian.
 * @param  : Donnee en little endian.
 * @return : Donnee permutee sur 4 octets.
 ******************************************************************************/
uint32_t little_endian_32b (uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
    return (uint32_t)(data1 | (data2 << 8) | (data3 << 16) | (data4 << 24));
}

/*******************************************************************************
 * @brief  : Rotationner une donnee de 16 bits en little endian.
 * @param  : Donnee en little endian.
 * @return : Donnee permutee sur 2 octets.
 ******************************************************************************/
uint16_t little_endian_16b (uint8_t data1, uint8_t data2)
{
    return (uint16_t)(data1 | (data2 << 8));
}

/*******************************************************************************
 * @brief  : Convertir une donnee de 24bits en 16bits (ex: couleur).
 * @param  : Donnee sur 24 bits.
 * @return : Donnee convertie en 16bits.
 ******************************************************************************/
uint16_t convert_16b (uint32_t data24b)
{
    return ((data24b & 0xF80000) >> 8)|((data24b & 0xFC00) >> 5)|((data24b & 0xF8) >> 3);
}

/***************************************************************END OF FILE****/
