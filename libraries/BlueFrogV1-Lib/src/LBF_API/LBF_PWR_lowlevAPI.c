/*******************************************************************************
 * LBF_PWR_lowlevAPI.c
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


#include "LBF_lowlev_API.h"


/* Static variables:  
   accessible only from this C file and retain their value 
   between different calls of the functions where they're used */
static boolean_t VDDH_On;




/* Functions -----------------------------------------------------------------*/

/*******************************************************************************
 * @brief  : Check whether VDDH to OLED has been enabled on the board
 * @param  : none.
 * @return : TRUE if VDDH is on, else FALSE
 ******************************************************************************/
boolean_t Check_VDDH_On (void)
{
    return VDDH_On;
}

/*******************************************************************************
 * @brief  : Enable generation of VDDH (14V) to OLED on the board 
 * @param  : none.
 * @return : none.
 ******************************************************************************/
void Turn_VDDH_On (void)
{
    GPIO_HIGH(OLED_VDDH_PORT, OLED_VDDH_PIN);
    VDDH_On = TRUE;
}

/*******************************************************************************
 * @brief  : Disable generation of VDDH to OLED on the board 
 * @param  : xx.
 * @return : xx.
 ******************************************************************************/
void Turn_VDDH_Off (void)
{
    GPIO_LOW(OLED_VDDH_PORT, OLED_VDDH_PIN);
    VDDH_On = FALSE;
}


/*******************************************************************************
 * @brief  : Ecrit une valeur dans un registre avec le protocole I2C.
 * @param  : NomReg: numero du registre.
 *           ValeurReg: valeur a donner.
 * @return : 0 en cas de reussite, different en cas d'echec.
 ******************************************************************************/
uint8_t I2C2_WriteSingleReg (uint8_t ChipID, uint8_t NomReg, uint8_t ValeurReg)
{


/*****   ATTENTION   ATTENTION    ATTENTION   ATTENTION   ATTENTION   ********/
/*****  The "7-bit device address that HAL expects is actually the    ********/
/*****  8-bit I2C write address (i.e. shift left by one bit, pad a 0) !!! ****/


    // I2C2, blocking write into 1 register with 1s timeout
    // (hi2c2 is global)
    HAL_I2C_Mem_Write( &hi2c2, (uint16_t) (ChipID<<1), (uint16_t) NomReg,  
                               I2C_MEMADD_SIZE_8BIT, &ValeurReg, 0x1, 1000) ;
  
    
    return 0;
}

/*******************************************************************************
 * @brief  : Lit une valeur dans un registre avec le protocole I2C.
 * @param  : NomReg: numero du registre.
 *           ValeurReg: valeur retournee.
 * @return : 0 en cas de reussite, different en cas d'echec.
 ******************************************************************************/
uint8_t I2C2_ReadSingleReg (uint8_t ChipID, uint8_t NomReg)
{
uint8_t ValeurReg = 0;

/*****   ATTENTION   ATTENTION    ATTENTION   ATTENTION   ATTENTION   ********/
/*****  The "7-bit device address that HAL expects is actually the    ********/
/*****  8-bit I2C write address (i.e. shift left by one bit, pad a 0) !!! ****/


    // I2C2, read 1 register in blocking mode with 1s timeout
    // (hi2c2 is global)
    HAL_I2C_Mem_Read( &hi2c2, (uint16_t)(ChipID<<1), (uint16_t) NomReg,
                               I2C_MEMADD_SIZE_8BIT, &ValeurReg, 0x1, 1000);

    return ValeurReg;
}





/***************************************************************END OF FILE****/
