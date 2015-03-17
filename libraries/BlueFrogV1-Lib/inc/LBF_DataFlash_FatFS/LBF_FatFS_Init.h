/*******************************************************************************
 * LBF_FatFS_Init.h
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

// To prevent recursive inclusion
#ifndef __FATFS_INIT
#define __FATFS_INIT

boolean_t LBF_FatFS_Init (void);

void LBF_FatFS_DeInit (void);



#endif // __FATFS_INIT


/********    END OF FILE  *****************************************************************/

