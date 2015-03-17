/*******************************************************************************
 * LBF_UART1_lowlevAPI.c
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

#include <stdint.h>



/*******************************************************************************
 * @brief  : Send 8-bit data through UART #1
 * @param  : none.
 * @retval : none.
 ******************************************************************************/
void UART_SendData (uint8_t data)
{
     HAL_UART_Transmit(&huart1, &data, 0x1, 1000);
    // UART1 blocking Tx of 1 byte with 1s timeout
    // (huart1 is global)
}

/*******************************************************************************
 * @brief  : Receive 8-bit data through UART #1
 * @param  : Aucun.
 * @retval : Rien.
 ******************************************************************************/
uint8_t UART_ReceiveData (void)
{
uint8_t RxByte = 0;
 
    HAL_UART_Receive(&huart1, &RxByte, 0x1, 1000);
    // UART1 blocking Rx of 1 byte with 1s timeout
    // (huart1 is global)
    
    return (RxByte);
    
}

/*******************************************************************************
 * @brief  : Send string of characters through UART #1
 * @param  : Aucun.
 * @retval : Rien.
 ******************************************************************************/
void UART_SendString(char* pString)
{
// Do it in a more clever way!... use HAL API to send in one shot...

    while((*pString)!='\0')
    {
        UART_SendData(*pString);
        pString++;
    }


}


/***************************************************************END OF FILE****/
