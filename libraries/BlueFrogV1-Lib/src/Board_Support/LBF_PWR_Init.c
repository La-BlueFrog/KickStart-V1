/*******************************************************************************
 * LBF_PWR_Init.c
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
 *************************************************************************/


#include "LBF_lowlev_API.h"
#include "LBF_I2C2_Init.h"
#include "LBF_PWR_Init.h"

/*******************************************************************************
 * @brief  : Initialise  LP3913 Power Management
 * @param  : none.
 * @return : none.
 ******************************************************************************/
void LBF_PWR_Init(void)
{

    // Set VCC_NUM to 3.0V
    I2C2_WriteSingleReg(PWR_I2C_CHIPID, PWR_BUCK2_ADDR, PWR_BUCK2_VDD);

    // Set charge current limit to 100mA
    I2C2_WriteSingleReg(PWR_I2C_CHIPID, 0x20, 0x01);     
    
}


/***************************************************************END OF FILE****/
