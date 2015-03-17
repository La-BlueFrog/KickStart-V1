/*******************************************************************************
 * LBF_OLED_Init.c
 * 
 * Copyright 2014 Roman GAUCHI <roman.gauchi@gmail.com>
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

#include "LBF_OLED_Init.h"


/*******************************************************************************
 * @brief  : Configure the OLED.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void LBF_OLED_Init(uint16_t *fconf)
{
    /* 
     * note : Procedure de configuration selon
     * la datasheet du densitron DD-160128FC-1A
     */
    
    OLED_RESET_LOW();
    Delay_ms(10);
    OLED_RESET_HIGH();
    Delay_ms(10);
    
    // display off, analog reset
    OLED_WriteReg(0x04, 0x01);
    Delay_ms(10);
    // Power save mode : normal
    OLED_WriteReg(0x04, 0x00);
    Delay_ms(10);
    
    // Display off
    OLED_WriteReg(0x06, 0x00);
    
    // Export1 internal clock and OSC operates with external resistor
    OLED_WriteReg(0x02, 0x01);

    // Iref controlled by external resistor
    OLED_WriteReg(0x80, 0x00);
    
    if(fconf[0] == 0xFFFF)
    {
        // VALEURS PAR DEFAUTS ************************************************
        
        // Clock div ratio 1: freq setting 90Hz
        OLED_WriteReg(0x03, 0x30);
        
        // Driving current R G B - default R = 82uA / G = 56uA / B = 58uA
        OLED_WriteReg(0x10, 0x52);     // 0x52
        OLED_WriteReg(0x11, 0x38);     // 0x38
        OLED_WriteReg(0x12, 0x3A);     // 0x3A
        
        // Precharge time R G B
        OLED_WriteReg(0x08, 0x01);     // 0x04 / 0x01
        OLED_WriteReg(0x09, 0x01);     // 0x05 / 0x01
        OLED_WriteReg(0x0A, 0x01);     // 0x05 / 0x01
        
        // Precharge current R G B
        OLED_WriteReg(0x0B, 0x0A);     // 0x9D / 0x0A
        OLED_WriteReg(0x0C, 0x0A);     // 0x8C / 0x0A
        OLED_WriteReg(0x0D, 0x0A);     // 0x57 / 0x0A
    }
    else
    {
        uint8_t freq;
        freq = (uint8_t)(fconf[1]/5) - 15;
        
        // Frame Frequency
//        OLED_WriteReg(0x03, (freq << 8));
        OLED_WriteReg(0x03, (freq << 4));
        
        // Driving current R G B
        OLED_WriteReg(0x10, (uint8_t)fconf[2]);
        OLED_WriteReg(0x11, (uint8_t)fconf[3]);
        OLED_WriteReg(0x12, (uint8_t)fconf[4]);
        
        // Precharge time R G B
        OLED_WriteReg(0x08, (uint8_t)fconf[5]);
        OLED_WriteReg(0x09, (uint8_t)fconf[6]);
        OLED_WriteReg(0x0A, (uint8_t)fconf[7]);
        
        // Precharge current R G B
        OLED_WriteReg(0x0B, (uint8_t)fconf[8]);
        OLED_WriteReg(0x0C, (uint8_t)fconf[9]);
        OLED_WriteReg(0x0D, (uint8_t)fconf[10]);
    }
    



//    * Display mode set :
//     *  - RGB
//     *  - Column = 0->159
//     *  - Column data display = Normal display
//     *
    OLED_WriteReg(0x13, 0x00);
    
    // External interface mode=MPU
    OLED_WriteReg(0x14, 0x31);     // 0x01 ?
    
//   * Memory write mode :
//     *  - 8 bits dual transfer
//     *  - 65K support
//     *  - Horizontal address counter is increased
//     *  - Vertical address counter is increased
//     *  - The data is continuously written horizontally
//     *
    OLED_WriteReg(0x16, 0x66);
    
    // Duty = 128
    OLED_WriteReg(0x28, 0x7F);
    
    // Display start on line 0
    OLED_WriteReg(0x29, 0x00);
    
    //DDRAM read address start point 0x2E~0x2F
    OLED_WriteReg(0x2E, 0x00);     // X
    OLED_WriteReg(0x2F, 0x00);     // Y
    
    // Display screen saver size 0x33~0x36
    OLED_WriteReg(0x33, 0x00);     // Screen saver columns start
    OLED_WriteReg(0x34, 0x9F);     // Screen saver columns end
    OLED_WriteReg(0x35, 0x00);     // Screen saver row start
    OLED_WriteReg(0x36, 0x7F);     // Screen saver row end
    
    // CLEAR SCREEN !!
    OLED_Clear();
    
    Turn_VDDH_On();
    Delay_ms(100);
    
    // Display ON
    OLED_WriteReg(0x06, 0x01);


}



/***************************************************************END OF FILE****/
