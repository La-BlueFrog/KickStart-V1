/*******************************************************************************
 * inframod_fat16.c
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
#include "inframod_fat16.h"


/* Privates prototypes -------------------------------------------------------*/
static uint16_t convert_asciitohex(uint8_t *data);

/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Lit le repertoire racine et liste toutes les images BMP en FAT16
 *           /!\ fonction recursive, pour trouver toutes les images /!\
 * @param  : nbImg: nombre d'image BMP presentes en memoire.
 *           listeBMP: liste des adresses (4 octets) des images.
 *           addrRacine: adresse de depart (repertoire racine)
 * @return : Rien.
 ******************************************************************************/
void FAT16_ListerImageBMP(uint16_t *nbImg, uint16_t *listeBMP, uint32_t addrRacine)
{
    uint8_t buffer[32];
    uint32_t addrSsRep, addrSuiv = addrRacine;
    
    do{
        // Si le repertoire est contenu dans la memoire, on lit par cluster
        if(addrRacine != FAT16_DEBUT_RACINE)
        {
            if(addrSuiv >= (addrRacine + FAT16_TAILLE_CLUSTER))
            {
                addrRacine = FAT16_ClusterSuivant(addrRacine);
                addrSuiv = addrRacine;
                if(addrRacine == 0) {break;}
            }
        }
        
        // Lecture ligne par ligne du repertoire racine
        FLASH_ReadBuffer(buffer, addrSuiv, 32);
        addrSuiv += 32;
        
        // Si le fichier est supprime
        if(buffer[0] == 0xE5) {continue;}
        
        // Sous-repertoire : recursivite
        if(buffer[11] == 0x10)
        {
            addrSsRep = ((buffer[27]<<8) | buffer[26]) * FAT16_TAILLE_CLUSTER + FAT16_DEBUT_CLUSTER;
            // Si le sous-rep boucle sur lui-meme (./../)
            if(addrSsRep == addrRacine) {continue;}
            if(addrSsRep == 0) {continue;}
            if(buffer[0]=='T' && buffer[1]=='R' && buffer[2]=='A' && buffer[3]=='S' && buffer[4]=='H') {continue;}
            
            FAT16_ListerImageBMP(nbImg, listeBMP, addrSsRep);
            continue;
        }
        
        // Format de l'image : BMP
        if(buffer[8] == 0x42 && buffer[9] == 0x4D && buffer[10] == 0x50)
        {
            // on limite la lecture a 200 images BMP.
            if (*nbImg > 200) {break;}
            listeBMP[*nbImg] = (buffer[27] << 8) | (buffer[26]);
            (*nbImg)++;
        }
    } while(buffer[0] != 0x00 && buffer[1] != 0x00);
}

/*******************************************************************************
 * @brief  : Recupere en memoire FLASH les variables du fichier config.txt
 * @param  : config: tableau contenant les variables.
 * @return : Rien.
 ******************************************************************************/
void FAT16_FichierConfig(uint16_t *config)
{
    uint8_t b[80], etat, var[4], i, j = 0;
    uint16_t offset, addrCluster = 0x0000;
    uint32_t listeCluster[5], addrSuiv = FAT16_DEBUT_RACINE;
    
    // Initialisations :
    for(i=0; i<80; i++) {b[i] = 0;}
    for(i=0; i<11; i++) {config[i] = 0xFFFF;}
    
    do{
        FLASH_ReadBuffer(b, addrSuiv, 32);
        addrSuiv += 32;
        
        // Fichier "config.txt"
        if(b[0]=='C' && b[1]=='O' && b[2]=='N' && b[3]=='F' && b[4]=='I' && b[5]=='G' && b[6]==' ' && b[7]==' ' && b[8]=='T' && b[9]=='X' && b[10]=='T')
        {
            addrCluster   = (b[27] << 8) | b[26];
            break;
        }
    }while(b[0] != 0x00 && b[1] != 0x00);
    
    // Lecture du fichier "config.txt"
    if(addrCluster != 0x0000)
    {
        offset = 0;
        FAT16_LocaliserCluster(listeCluster, addrCluster);
        
        do{
            FAT16_LireBuffer(b, offset, 0, 80, listeCluster);
            etat = 0;
            var[0]=0; var[1]=0; var[2]=0; var[3]=0;
            
            for(i=0; i<80; i++)
            {
                if(b[0] != 0x23 && b[i] != 0x0D)    // ignore les commentaires ('#')
                {
                    if(etat != 0 && b[i] != 0x20)   // ignore les espaces (' ')
                    {
                        var[etat-1] = b[i];
                        etat++;
                    }
                    if(b[i] == 0x3D)                // '='
                        etat = 1;
                }
                else if(b[i] == 0x0D && b[i+1] == 0x0A)     // '\n'
                    break;
            }
            offset += i+2;
            
            if(var[0] != 0)
            {
                config[j] = convert_asciitohex(var);
                j++;
            }
        
        }while(b[0] != 0x00 && b[1] != 0x00);
    }
}

/*******************************************************************************
 * @brief  : Reconstruit la file des clusters constituant le fichier.
 * @param  : listeCluster: liste les adresses (4 octets) des clusters.
 *           addrCluster: adresse du premier cluster.
 * @return : Rien.
 ******************************************************************************/
void FAT16_LocaliserCluster(uint32_t *listeCluster, uint16_t addrCluster)
{
    uint8_t buffer[2];
    uint16_t addrSuiv = addrCluster, i = 0;
    
#if defined (DEBUG)
    xprintf("\naddrCluster: 0x%02x", addrCluster);
#endif
    
    while(1)
    {
        listeCluster[i] = FAT16_DEBUT_CLUSTER + addrSuiv * FAT16_TAILLE_CLUSTER;
        FLASH_ReadBuffer(buffer, FAT16_DEBUT_ALLOC + addrSuiv * 2, 2);
        addrSuiv = (buffer[1] << 8) | buffer[0];
        
#if defined (DEBUG)
        xprintf(" > 0x%02x", addrSuiv);
#endif
        if (addrSuiv == 0xFFFF || addrSuiv == 0xFFF8) {break;}
        i++;
    }
}

/*******************************************************************************
 * @brief  : Retrouve le cluster suivant du fichier en cours de lecture.
 * @param  : addrCluster: adresse du cluster en cours.
 * @return : Le cluster suivant (4 octets).
 ******************************************************************************/
uint32_t FAT16_ClusterSuivant(uint32_t addrCluster)
{
    uint8_t buffer[2];
    uint16_t addrSuiv;
    uint32_t addrAlloc;
    
    // Cible l'adresse dans la table d'allocation
    addrAlloc = FAT16_DEBUT_ALLOC + ((addrCluster - FAT16_DEBUT_CLUSTER) >> 8);
    
    // Lit le cluster suivant dans la table
    FLASH_ReadBuffer(buffer, addrAlloc, 2);
    addrSuiv = (buffer[1] << 8) | buffer[0];
    
    if(addrSuiv == 0xFFFF || addrSuiv == 0xFFF8)
        return 0;
    else
        return (FAT16_DEBUT_CLUSTER + addrSuiv * FAT16_TAILLE_CLUSTER);
}

/*******************************************************************************
 * @brief  : Lit un buffer de taille et de numerotation donne en memoire.
 * @param  : buffer: le buffer a retourner.
 *           offset: decalage par rapport au header du fichier.
 *           numBuffer: numero du buffer a lire en memoire.
 *           tailleBuffer: taille du buffer, la taille ne varie pas sur la 
 *                         lecture complete du fichier.
 *           listeCluster: liste des adresses (4 octets) des clusters.
 * @return : Rien.
 ******************************************************************************/
void FAT16_LireBuffer(uint8_t *buffer, uint16_t offset, uint16_t numBuffer, uint16_t tailleBuffer, uint32_t *listeCluster)
{
    uint16_t numCluster, addrDebut, tailleData;
    
    numCluster = (offset + numBuffer*tailleBuffer) / FAT16_TAILLE_CLUSTER;
    addrDebut  = (offset + numBuffer*tailleBuffer) % FAT16_TAILLE_CLUSTER;
    tailleData = FAT16_TAILLE_CLUSTER - addrDebut;
    
    if(tailleData > tailleBuffer)
    {
        tailleData = tailleBuffer;
    }
    FLASH_ReadBuffer(buffer, listeCluster[numCluster]+addrDebut, tailleData);
    
    if(tailleData < tailleBuffer)
    {
        addrDebut = tailleData;
        numCluster++;
        tailleData = tailleBuffer - tailleData;
        FLASH_ReadBuffer(buffer+addrDebut, listeCluster[numCluster], tailleData);
    }
}

/* Privates functions --------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Convertie une donnee en ASCII correspondant a des chiffres 
 *           numeriques en valeur numerique.
 * @param  : data: buffer des donnees ASCII (0x30:0 ... 0x39:9) [0.1.2.3]
 * @return : La valeur data en valeur numerique.
 ******************************************************************************/
uint16_t convert_asciitohex(uint8_t *data)
{
    int8_t i, unit = 0;
    uint16_t temp = 0, result = 0;
    
    for(i=3; i>=0; i--)
    {
        if(data[i] != 0x00)
        {
            unit++;
            temp = data[i] - 0x30;
            
            if(unit == 2)
                temp *= 10;
            else if(unit == 3)
                temp *= 100;
            else if(unit == 4)
                temp *= 1000;
            
            result += temp;
        }
    }
    
    return result;
}

/***************************************************************END OF FILE****/
