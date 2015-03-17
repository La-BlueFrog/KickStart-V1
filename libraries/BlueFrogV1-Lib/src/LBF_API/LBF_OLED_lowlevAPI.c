/*******************************************************************************
 * LFB_OLED_lowlevAPI.c
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




/* Private Functions -----------------------------------------------------------------*/


/*******************************************************************************
 * @brief  : Send a byte on SPI1 output, simultaneously receive a byte on SPI input.
 * @param  : octet: byte to send.
 * @return : valoe of byte received.
 ******************************************************************************/
uint8_t OLED_SPI_TransferByte (uint8_t TxByte)
{

uint8_t RxByte = 0;

    HAL_SPI_TransmitReceive(&hspi1, &TxByte, &RxByte, 0x1, 1000);
    // SPI1, full duplex, blocking Tx/Rx of 1 byte with 1s timeout
    // (hspi1 is global)
    
    return RxByte;

}


/* WAS :
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    
    SPI_I2S_SendData(SPI1, octet);
    
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    
    return SPI_I2S_ReceiveData(SPI1);
*/



/*******************************************************************************
 * @brief  : Send 8bit command to SEPS525 (driver chip on OLED FPC).
 * @param  : Value of the command.
 * @return : None.
 ******************************************************************************/
void OLED_SendCmd(uint8_t Value)
{
    OLED_RS_LOW();
    OLED_CS_LOW();
    OLED_SPI_TransferByte(Value);
    OLED_CS_HIGH();
    OLED_RS_HIGH();
}

/*******************************************************************************
 * @brief  : Send 16bit data or parameter to SEPS525 (driver chip on OLED FPC).
 * @param  : Value of the data.
 * @return : Rien.
 ******************************************************************************/
void OLED_SendData(uint16_t Value)
{
    OLED_SPI_TransferByte((Value>>8) & 0xFF);
    OLED_SPI_TransferByte(Value & 0xFF);
}

/*******************************************************************************
 * @brief  : Write value in SEPS525 register
 * @param  : NomReg: nom du registre.
 *           ValeurReg: Valeur du registre.
 * @return : None.
 ******************************************************************************/
void OLED_WriteReg(uint8_t RegName, uint8_t RegValue)
{
    OLED_CS_LOW();
    OLED_RS_LOW();
    OLED_SPI_TransferByte(RegName);
    OLED_RS_HIGH();
    OLED_CS_HIGH();
    
    OLED_CS_LOW();
    OLED_SPI_TransferByte(RegValue);
    OLED_CS_HIGH();
}

/*******************************************************************************
 * @brief  : Start data transfer to SEPS525 memory.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void OLED_DataStart(void)
{
    OLED_CS_LOW();
    OLED_RS_LOW();
    OLED_SPI_TransferByte(0x22);
    OLED_RS_HIGH();
}

/*******************************************************************************
 * @brief  : Stop data transfer to SEPS525.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void OLED_DataEnd(void)
{
    OLED_CS_HIGH();
}

/*******************************************************************************
 * @brief  : Define a region where to write data in SEPS525 memory
 * @param  : x: position on x-axis of top-left corner of rectangle to draw.
 *           y: position on y-axis of top-left corner of rectangle to draw.
 *           width: width of the rectangle in pixels.
 *           height: height of the rectangle in pixels.
 * @return : none.
 ******************************************************************************/
void OLED_SetRegion(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
    uint8_t x1, x2, y1, y2;
    
    x1 = x;
    y1 = y;
    x2 = x + width - 1;
    y2 = y + height - 1;
    
    // Valeurs limites
    if (x1 < 0) x1=0;
    if (x1 >= 160) x1=159;
    if (x2 < 0) x2=0;
    if (x2 >= 160) x2=159;
    if (y1 < 0) y1=0;
    if (y1 >= 128) y1=127;
    if (y2 < 0) y2=0;
    if (y2 >= 128) y2=127;
    
    OLED_WriteReg(0x17, x1);   // X start
    OLED_WriteReg(0x18, x2);   // X end
    OLED_WriteReg(0x19, y1);   // Y start
    OLED_WriteReg(0x1A, y2);   // Y end
    
    OLED_WriteReg(0x20, x1);   // memory accesspointer x
    OLED_WriteReg(0x21, y1);   // memory accesspointer y
}

/*******************************************************************************
 * @brief  : Draw a uniformly colored rectangle on OLED screen.
 * @param  : x: position on x-axis of top-left corner.
 *           y: position on y-axis of top-left corner.
 *           width: width of the rectangle in pixels.
 *           height: height of the rectangle in pixels.
 *           color565: color of the rectangle in RGB565 format.
 * @return : none.
 ******************************************************************************/
void OLED_Fill(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color565)
{
    OLED_SetRegion(x, y, width, height);
    
    OLED_DataStart();
    uint16_t i;
    for (i=0; i<width*height; i++)
    {
        OLED_SendData(color565);
    }
    OLED_DataEnd();
}

/*******************************************************************************
 * @brief  : Display a rectangle with user-defined content.
 * @param  : x: position on x-axis of top-left corner.
 *           y: position on y-axis of top-left corner.
 *           width: width of the rectangle in pixels.
 *           height: height of the rectangle in pixels.
 *           *buffer: pointer to pre-filled buffer.
 * @return : Rien.
 ******************************************************************************/
void OLED_DisplayBuffer(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t *buffer)
{
    OLED_SetRegion(x, y, width, height);
    
    OLED_DataStart();
    uint16_t i;
    for (i=0; i<width*height; i++)
    {
        OLED_SendData(buffer[i]);
    }
    OLED_DataEnd();
}

/*******************************************************************************
 * @brief  : Clear OLED screen (display black).
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void OLED_Clear(void)
{
    OLED_Fill(0, 0, 160, 128, 0x0000);
}

/***************************************************************END OF FILE****/
