/*******************************************************************************
 * LBF_FLASH_Init.c
 * 
 * * Author: La BlueFrog, 2015
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
 *************************************************************************/

#include "LBF_lowlev_API.h"

#include "LBF_FLASH_Init.h"



/* Privates prototypes -------------------------------------------------------*/
 
static void FLASH_ConfigurePageSize (void);

/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Initialise the Adesto Data Flash.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_FLASH_Init(void)
{
    /* Configure ADESTO DataFlash in 512-byte per page mode */
    FLASH_ConfigurePageSize();
    
}




/*******************************************************************************

 * @brief  : Configure the page size of ADESTO DataFlash.
 * @param  : None.
 * @return : None.
 ******************************************************************************/
void FLASH_ConfigurePageSize(void)
{
 
    /* Select the FLASH: Chip Select low */
    FLASH_CS_LOW();

    /* Send Page Size Configuration Command for 512 bytes/page  */
    FLASH_SendByte(FLASH_CMD_PAGESIZE1);
    FLASH_SendByte(FLASH_CMD_PAGESIZE2);
    FLASH_SendByte(FLASH_CMD_PAGESIZE3);
    FLASH_SendByte(FLASH_CMD_PAGESIZE4);

    /* Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();
    
    /* Wait the end of Flash writing */
    FLASH_WaitForWriteEnd();
}


