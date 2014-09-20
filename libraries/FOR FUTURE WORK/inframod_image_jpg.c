/*******************************************************************************
 * inframod_image_jpg.c
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
#include "inframod_tjpgdec.h"

/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : User defined call-back function to input JPEG data.
 * @param  : jd: Decoder object
 *           buff: Pointer to the read buffer (NULL:skip)
 *           nd: Number of bytes to read/skip from input stream
 * @return : .
 ******************************************************************************/
static UINT tjd_input (JDEC* jd, BYTE* buff, UINT nd)
{
    UINT rb;
    
    if (buff)
    {   /* Read nd bytes from the input stream */
        f_read(fil, buff, nd, &rb);
        return rb;  /* Returns number of bytes could be read */
    }
    else
    {   /* Skip nd bytes on the input stream */
        return (f_lseek(fil, f_tell(fil) + nd) == FR_OK) ? nd : 0;
    }
}

/*******************************************************************************
 * @brief  : User defined call-back function to output RGB bitmap.
 * @param  : jd: Decoder object
 *           bitmap: Bitmap data to be output
 *           rect: Rectangular region to output
 * @return : '1': Continue decompression, '0': Abort.
 ******************************************************************************/
static UINT tjd_output (JDEC* jd, void* bitmap, JRECT* rect)
{
    jd = jd;    /* Suppress warning (device identifier is not needed) */
    
    /* Check user interrupt at left end */
    //if (!rect->left) return 0;  /* Abort decompression */
    
    uint8_t largeur = 2*(rect->right - rect->left + 1);
    uint8_t hauteur = rect->bottom - rect->top + 1;
    
    /* Put the rectangular into the display */
    OLED_AfficherBuffer(rect->left, rect->top, largeur, hauteur, (uint16_t*)bitmap);
    
    return 1;
}



/*******************************************************************************
 * @brief  : Lire une image BMP en memoire et l'affichee.
 * @param  : fp: Pointer to the open file object to load
 *           work: Pointer to the working buffer (must be 4-byte aligned)
 *           sz_work: Size of the working buffer (must be power of 2)
 * @return : '1': Continue decompression, '0': Abort.
 ******************************************************************************/
//void JPG_LireImage (FIL *fp, void *work, UINT sz_work)
uint8_t JPG_LireImage(uint16_t addrCluster)
{
    void work[3100];
    
    JDEC jd;            /* Decoder object (124 bytes) */
    JRESULT rc;         /* Result code of TJpgDec API */
    
    /* Prepare to decompress the file */
    rc = jd_prepare(&jd, tjd_input, work, 3100, 0);
    if (rc == JDR_OK)
    {
        /* Start to decompress the JPEG file */
        rc = jd_decomp(&jd, tjd_output, 0);
    }
    else
    {
        /* Display error code */
        OLED_Fill(0,0,160,128,ROUGE);
    }
}
