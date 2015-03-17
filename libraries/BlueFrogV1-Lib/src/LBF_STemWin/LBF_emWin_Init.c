/*******************************************************************************
 * LBF_LaunchUSB_MassStorage.c
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

#include "WM.h" //Windows Manager
#include "GUI.h"

#include "LBF_lowlev_API.h"

/* Private variables ---------------------------------------------------------*/



/* Functions -----------------------------------------------------------------*/


void LBF_emWin_Init(void) 
{

    // The CRC module (in RCC peripheral clock enable register) must be enabled 
    //  before using the STemWin library
    // So periph has been enabled in stm32l1xx_hal_conf.h)
    // Also need to enable the Peripheral clock  
    __CRC_CLK_ENABLE();

    // Activate the use of memory device feature 
    WM_SetCreateFlags(WM_CF_MEMDEV);


    // Init the STemWin GUI Library */
    GUI_Init();

}
 


/***************************************************************END OF FILE****/
