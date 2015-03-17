/*******************************************************************************
 * LBF_FLASH_lowlevAPI.c
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
#include "LBF_SPI2_Init.h"

 /* 
 *        +--------------------------------------------------------------+
 *        |                     Pin assignment                           |
 *        +-----------------------------+------------------+-------------+
 *        |  STM32 SPI Pins             | Adesto FLASH     |    Pin      |
 *        +-----------------------------+------------------+-------------+
 *        | FLASH_CS_PIN                | ChipSelect(/CS)  |    4        |
 *        | FLASH_SPI_MISO_PIN / MISO   | SerialDataOut(SO)|    8        |
 *        | (GPIO)                      | WriteProtect(/WP)|    5        |
 *        |                             | GND              |    7 (0 V)  |
 *        | FLASH_SPI_MOSI_PIN / MOSI   | SerialDataIn(SI) |    1        |
 *        | FLASH_SPI_SCK_PIN / SCK     | SerialClock(SCK) |    2        |
 *        | (GPIO)                      | /RESET           |    3        |
 *        |                             | VCC              |    6 (3V)   |
 *        +-----------------------------+------------------+-------------+
 * 
 ******************************************************************************/




/*******************************************************************************
 * @brief  : Ecrit une page en memoire (256 octets) en une seul fois.
 * @note   : le nombre d'octet ecrit ne peut pas depasser une page de FLASH.
 * @param  : pBuffer: pointeur sur le buffer contenant les donnees a ecrire en 
 *           memoire FLASH.
 * @param  : WriteAddr: addresse ou ecrire les donnees.
 * @param  : NumByteToWrite: nombre d'octet a ecrire en memoire FLASH, doit 
 *           etre egal ou inferieur a la taille d'une page de FLASH.
 * @return : Rien.
 ******************************************************************************/
void FLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t 	page_offset;
    uint16_t 	byte_offset;
    uint16_t 	i=0;
    uint8_t 	Buffer[FLASH_PAGE_LENGTH];
    uint16_t    NumByteToWrite_Copy;
    uint8_t*    pBuffer_Copy;
    uint32_t    AddrTargetPage;

    // Prepare for address in format expected by DataFlash :
    page_offset = WriteAddr / FLASH_PAGE_LENGTH;
    byte_offset = WriteAddr % FLASH_PAGE_LENGTH;

    /* Read full page and update relevant portions */
    NumByteToWrite_Copy = NumByteToWrite;
    pBuffer_Copy = pBuffer;
    AddrTargetPage = (WriteAddr/FLASH_PAGE_LENGTH) * FLASH_PAGE_LENGTH;
    FLASH_ReadBuffer(Buffer, AddrTargetPage, FLASH_PAGE_LENGTH);
    while (NumByteToWrite_Copy--)
    {
       Buffer[i+(WriteAddr-AddrTargetPage)] = *pBuffer_Copy;
       pBuffer_Copy++;
       i++;
    }

     /* Select the FLASH: Chip Select low */
    FLASH_CS_LOW();    

    /* Send "Write to Memory " instruction (through Buffer1 with built-in PAGE ERASE) */
    FLASH_SendByte(FLASH_CMD_WRITE1);


    /* Send WriteAddr high nibble address byte to write to */
    FLASH_SendByte(page_offset >> 7);
    /* Send WriteAddr medium nibble address byte to write to */
    FLASH_SendByte(((page_offset & 0x7F)<<1) + (byte_offset >> 8));
    /* Send WriteAddr low nibble address byte to write to */
    FLASH_SendByte(byte_offset & 0xFF);
    /* Note - Addressing scheme for DataFlash is a bit involed — refer to Adesto datasheet */
    
    /* while there is data to be written on the FLASH */
    while (NumByteToWrite--)
    {
        /* Send the current byte */
        FLASH_SendByte(*pBuffer);
        /* Point on the next byte to be written */
        pBuffer++;
    }
    
    /* Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();
    
    /* Wait the end of Flash writing */
    FLASH_WaitForWriteEnd();
}


/*******************************************************************************
 * @brief  : Ecrit un block de donnees en memoire. On décompose ce bloc en pages
 *           à écrire, éventuellement partiellement pour la 1ére et la dernière
 * @param  : pBuffer: pointeur sur le buffer contenant les donnees a ecrire en 
 *           memoire FLASH.
 * @param  : WriteAddr: addresse ou ecrire les donnees.
 * @param  : NumByteToWrite: nombre d'octet a ecrire en memoire FLASH.
 * @return : Rien.
 *******************************************************************************/
void FLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite)
{
    uint16_t NumOfPages = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    Addr = WriteAddr % FLASH_PAGE_LENGTH;
    count = FLASH_PAGE_LENGTH - Addr;
    NumOfPages =  NumByteToWrite / FLASH_PAGE_LENGTH;
    NumOfSingle = NumByteToWrite % FLASH_PAGE_LENGTH;
    
    if (Addr == 0) // WriteAddr is FLASH_PAGE_LENGTH aligned
    {
        if (NumOfPages == 0) // NumByteToWrite < FLASH_PAGE_LENGTH
        {
            FLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
        }
        else // NumByteToWrite > FLASH_PAGE_LENGTH
        {
            while (NumOfPages--)
            {
                FLASH_WritePage(pBuffer, WriteAddr, FLASH_PAGE_LENGTH);
                WriteAddr +=  FLASH_PAGE_LENGTH;
                pBuffer += FLASH_PAGE_LENGTH;
            }
            
            FLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else // WriteAddr is not FLASH_PAGE_LENGTH aligned
    {
        if (NumOfPages == 0) // NumByteToWrite < FLASH_PAGE_LENGTH
        {
            if (NumOfSingle > count) // (NumByteToWrite + WriteAddr) > FLASH_PAGE_LENGTH
            {
                temp = NumOfSingle - count;
                
                FLASH_WritePage(pBuffer, WriteAddr, count);
                WriteAddr += count;
                pBuffer += count;
                
                FLASH_WritePage(pBuffer, WriteAddr, temp);
            }
            else
            {
                FLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else // NumByteToWrite > FLASH_PAGE_LENGTH
        {
            NumByteToWrite -= count;
            NumOfPages =  NumByteToWrite / FLASH_PAGE_LENGTH;
            NumOfSingle = NumByteToWrite % FLASH_PAGE_LENGTH;
            
            FLASH_WritePage(pBuffer, WriteAddr, count);
            WriteAddr +=  count;
            pBuffer += count;
            
            while (NumOfPages--)
            {
                FLASH_WritePage(pBuffer, WriteAddr, FLASH_PAGE_LENGTH);
                WriteAddr +=  FLASH_PAGE_LENGTH;
                pBuffer += FLASH_PAGE_LENGTH;
            }
            
            if (NumOfSingle != 0)
            {
                FLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/*******************************************************************************
 * @brief  : Lit un block de donnees en memoire FLASH.
 * @param  : pBuffer: pointeur sur le buffer qui recoit les donnees a lire en 
 *           memoire FLASH.
 * @param  : ReadAddr: addresse ou les donnees sont lues.
 * @param  : NumByteToRead: nombre d'octet a lire de la memoire FLASH.
 * @return : Rien.
 ******************************************************************************/
void FLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead)
{

    uint16_t 	page_offset;
    uint16_t 	byte_offset;

    /* Compute address in format expected by ADESTO DataFlash */
    page_offset = ReadAddr / FLASH_PAGE_LENGTH;
    byte_offset = ReadAddr % FLASH_PAGE_LENGTH;

   /* Select the FLASH: Chip Select low */
    FLASH_CS_LOW();
    
    /* Send "Read from Memory " instruction (Continous array read, Low Frequency mode so no dummy byte after address) */
    FLASH_SendByte(FLASH_CMD_READ_LF);

    /* Send WriteAddr high nibble address byte to read from */
    FLASH_SendByte(page_offset >> 7);
    /* Send WriteAddr medium nibble address byte to read from */
    FLASH_SendByte(((page_offset & 0x7F)<<1) + (byte_offset >> 8));
    /* Send WriteAddr low nibble address byte to read from */
    FLASH_SendByte(byte_offset & 0xFF);
    /* Note - Addressing scheme for DataFlash is a bit involed — refer to Adesto datasheet */
  
    
    while (NumByteToRead--) /* while there is data to be read */
    {
        /* Read a byte from the FLASH */
        *pBuffer = FLASH_SendByte(FLASH_DUMMY_BYTE);
        /* Point to the next location where the byte read will be saved */
        pBuffer++;
    }
    
    /* Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();
}

/*******************************************************************************
 * @brief  : Lit l'identifiant de la memoire FLASH.
 * @param  : Aucun.
 * @return : Identification (ID) de la memoire FLASH.
 ******************************************************************************/
uint32_t FLASH_ReadID(void)
{
    uint8_t Temp0 = 0, Temp1 = 0, Temp2 = 0;
    uint32_t Temp = 0;
    
    /* Select the FLASH: Chip Select low */
    FLASH_CS_LOW();
    /* Send "RDID " instruction */
    FLASH_SendByte(FLASH_CMD_RDID);
    /* Read a byte from the FLASH */
    Temp0 = FLASH_SendByte(FLASH_DUMMY_BYTE);
    /* Read a byte from the FLASH */
    Temp1 = FLASH_SendByte(FLASH_DUMMY_BYTE);
    /* Read a byte from the FLASH */
    Temp2 = FLASH_SendByte(FLASH_DUMMY_BYTE);
    /* Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();
    
    Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;
    return Temp;
}


/*******************************************************************************
 * @brief  : Envoi un octet vers la Flash avec le SPI et retourne un octet lu.
 * @param  : byte: octet a envoyer.
 * @return : La valeur de l'octet recu.
 ******************************************************************************/

uint8_t FLASH_SendByte(uint8_t TxByte)
{

uint8_t RxByte = 0;

    HAL_SPI_TransmitReceive(&hspi2, &TxByte, &RxByte, 0x1, 1000);
    // SPI2, full duplex, blocking Tx/Rx of 1 byte with 1s timeout
    // (hspi2 is global)
    
    return RxByte;
}
 

/* WAS :
uint8_t FLASH_SendByte(uint8_t byte)
{
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
   
    SPI_I2S_SendData(SPI2, byte);

    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
    
    return SPI_I2S_ReceiveData(SPI2);
}
*/

/*******************************************************************************
 * @brief  : Efface completement la memoire FLASH.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void FLASH_EraseBulk(void)
{
 
    /* Bulk Erase */
    /* Select the FLASH: Chip Select low */
    FLASH_CS_LOW();

    /* Send Full Flash Erase instructions  */
    FLASH_SendByte(FLASH_CMD_BULKERASE1);
    FLASH_SendByte(FLASH_CMD_BULKERASE2);
    FLASH_SendByte(FLASH_CMD_BULKERASE3);
    FLASH_SendByte(FLASH_CMD_BULKERASE4);

    /* Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();
    
    /* Wait until Flash ready */
    FLASH_WaitForWriteEnd();
}

/*******************************************************************************
 * @brief  : Attend que le processus d'ecriture dans la Flash se termine.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void FLASH_WaitForWriteEnd(void)
{
    uint8_t flashstatus = 0;
    
    /* Select the FLASH: Chip Select low */
    FLASH_CS_LOW();
    
    /* Send "Read Status Register" instruction */
    FLASH_SendByte(FLASH_CMD_RDSR);
    
    /* Loop as long as the memory is busy  */
    do
    {
        /* Send a dummy byte to generate the clock needed by the FLASH
        and put the value of the status register in FLASH_Status variable */
        flashstatus = FLASH_SendByte(FLASH_DUMMY_BYTE);
    }
    while ((flashstatus & FLASH_READY_FLAG) != 0x80); /* Not ready, write still in progress */
    
    /* Deselect the FLASH: Chip Select high */
    FLASH_CS_HIGH();
}



/***************************************************************END OF FILE****/
