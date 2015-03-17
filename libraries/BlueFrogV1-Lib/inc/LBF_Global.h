/*******************************************************************************
 * LBF_Global.h
 * 
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


// =============================================================================
// This files contains all the includes that are typically required when
// writing a main() program for La BlueFrog
// =============================================================================

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_GLOBAL_H
#define __LBF_GLOBAL_H



// ---  to use ST's HAL and CMSIS Libraries   ----------
#include "stm32l1xx.h"



// ---  to run La BlueFrog's Board Initializations -----
#include "LBF_Board_Init.h"
#include "LBF_OLED_Init.h"



// ---  to use APIs to La BlueFrog Hardware   ----------
#include "LBF_lowlev_API.h"



// ---  to use MiddleWare APIs    ----------------------

// -- emWin Graphics Library
#include "LBF_emWin_Init.h"
#include "WM.h" // if using emWin Windows Manager
#include "GUI.h"  // if using emWin API

// -- FatFS File System
#include "ff_gen_drv.h"   // in turn, pulls ff.h and diskio.h
#include "DataFlash_diskio.h"
#include "LBF_FatFS_Init.h"


// -- USB Device Drivers
#include "LBF_LaunchUSB_MassStorage.h"




#endif  /*__LBF_GLOBAL_H*/

/***************************************************************END OF FILE****/
