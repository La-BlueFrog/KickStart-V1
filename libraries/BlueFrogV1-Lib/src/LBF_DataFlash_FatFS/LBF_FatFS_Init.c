/*******************************************************************************
 * LBF_FatFS_Init.c
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


#include "LBF_lowlev_API.h"
#include "ff_gen_drv.h"   // in turn, pulls ff.h and diskio.h
#include "DataFlash_diskio.h"

// Please refer to ChaN's FatFS documentation available on the web


FATFS DataFlash_DISK_FatFs; /* File system object for User logical drive */
char DataFlash_DISK_Path[4]; /* User logical drive path */


/* =================================================================== */

boolean_t LBF_FatFS_Init (void)
{

boolean_t Success = TRUE;

    Success &= (FATFS_LinkDriver(&DataFlash_DISK_Driver, DataFlash_DISK_Path) == 0);
    if (Success)
    {
       Success &= (f_mount(&DataFlash_DISK_FatFs, (TCHAR const*)DataFlash_DISK_Path, 0) == FR_OK);
    }

    return Success;

}

/* =================================================================== */

void LBF_FatFS_DeInit (void)
{
    FATFS_UnLinkDriver(DataFlash_DISK_Path);
}

/********    END OF FILE  *****************************************************************/

