/*******************************************************************************
 * inframod_spi_flash.c
 * 
 * Copyright 2013 Roman GAUCHI <roman.gauchi@gmail.com> & Xavier Cauchy
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
 *******************************************************************************
 * 
 *        +-----------------------------------------------------------+
 *        |                     Pin assignment                        |
 *        +-----------------------------+---------------+-------------+
 *        |  STM32 SPI Pins             |     FLASH     |    Pin      |
 *        +-----------------------------+---------------+-------------+
 *        | FLASH_CS_PIN                | ChipSelect(/S)|    1        |
 *        | FLASH_SPI_MISO_PIN / MISO   | DataOut(DQ1)  |    2        |
 *        |                             | Write(/W)     |    3        |
 *        |                             | GND           |    4 (0 V)  |
 *        | FLASH_SPI_MOSI_PIN / MOSI   | DataIn(DQ0)   |    5        |
 *        | FLASH_SPI_SCK_PIN / SCK     | Clock(C)      |    6        |
 *        |                             | /HOLD         |    7        |
 *        |                             | VCC           |    8 (3.3 V)|
 *        +-----------------------------+---------------+-------------+
 * 
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "inframod_spi_flash.h"


/* Privates prototypes -------------------------------------------------------*/
void FLASH_LowLevel_Init (void);
void FLASH_HoldProtect_Init (void);
void FLASH_WriteProtect_Init (void);   
void FLASH_ConfigurePageSize (void);

/* Functions -----------------------------------------------------------------*/


/*******************************************************************************
 * @brief  : Initialise les peripheriques utilise par le SPI.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void FLASH_Init(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    
    FLASH_HoldProtect_Init();    /* GPIO pin HOLD from STM32 actually drives /RESET pin of Adesto Flash */
    FLASH_WriteProtect_Init();
    
    /* Initialisation des ports/pins */
    FLASH_LowLevel_Init();
    
    /* Dé-Selectionne la memoire FLASH */
    FLASH_CS_HIGH();
    
    /* Configuration du SPI */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(FLASH_SPI, &SPI_InitStructure);
    
    /* Active le FLASH_SPI */
    SPI_Cmd(FLASH_SPI, ENABLE);

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

/*******************************************************************************
 * @brief  : Initialise les pins utilisees par le SPI.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void FLASH_LowLevel_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* Active les horloges des pins du SPI */
    RCC_AHBPeriphClockCmd(  FLASH_SPI_SCK_GPIO_CLK |
                            FLASH_SPI_MISO_GPIO_CLK | 
                            FLASH_SPI_MOSI_GPIO_CLK | 
                            FLASH_CS_GPIO_CLK, 
                            ENABLE);
    
    /* Active l'horloge du peripherique SPI */
    RCC_APB1PeriphClockCmd(FLASH_SPI_CLK, ENABLE);
    
    /* Configure la pin SCK */
    GPIO_InitStructure.GPIO_Pin   = FLASH_SPI_SCK_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
    GPIO_Init(FLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);
    
    /* Configure la pin SPI_MISO */
    GPIO_InitStructure.GPIO_Pin   = FLASH_SPI_MISO_PIN;
    GPIO_Init(FLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);
    
    /* Configure la pin SPI_MOSI */
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI_PIN;
    GPIO_Init(FLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
    
    /* Connecte les pins SPI a leur fonctions alternatives */
    GPIO_PinAFConfig(FLASH_SPI_SCK_GPIO_PORT, FLASH_SPI_SCK_SOURCE, FLASH_SPI_SCK_AF);
    GPIO_PinAFConfig(FLASH_SPI_MISO_GPIO_PORT, FLASH_SPI_MISO_SOURCE, FLASH_SPI_MISO_AF);
    GPIO_PinAFConfig(FLASH_SPI_MOSI_GPIO_PORT, FLASH_SPI_MOSI_SOURCE, FLASH_SPI_MOSI_AF);
    
    /* Configure la pin CS */
    GPIO_InitStructure.GPIO_Pin   = FLASH_CS_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(FLASH_CS_GPIO_PORT, &GPIO_InitStructure);
}

/*******************************************************************************
 * @brief  : Initialise la pin HOLD.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void FLASH_HoldProtect_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* Active l'horloge de la pin HOLD */
    RCC_AHBPeriphClockCmd(FLASH_HOLD_GPIO_CLK, ENABLE);
    
    /* Configure la pin HOLD */
    GPIO_InitStructure.GPIO_Pin   = FLASH_HOLD_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
    GPIO_Init(FLASH_HOLD_GPIO_PORT, &GPIO_InitStructure);
    
    /* Initialise la pin a l'etat haut */
    FLASH_HOLD_HIGH();
}

/*******************************************************************************
 * @brief  : Initialise la pin WR/Vpp.
 * @param  : Aucun.
 * @return : Rien.
 ******************************************************************************/
void FLASH_WriteProtect_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* Active l'horloge de la pin WR */
    RCC_AHBPeriphClockCmd(FLASH_WR_GPIO_CLK, ENABLE);
    
    /* Configure la pin WR */
    GPIO_InitStructure.GPIO_Pin   = FLASH_WR_PIN;

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
    GPIO_Init(FLASH_HOLD_GPIO_PORT, &GPIO_InitStructure);
    
    /* Initialise la pin a l'etat haut */
    FLASH_WR_HIGH();
}

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
    uint8_t 	Buffer[FLASH_PAGE_SIZE];
    uint16_t    NumByteToWrite_Copy;
    uint8_t*    pBuffer_Copy;
    uint32_t    AddrTargetPage;

    // Prepare for address in format expected by DataFlash :
    page_offset = WriteAddr / FLASH_PAGE_SIZE;
    byte_offset = WriteAddr % FLASH_PAGE_SIZE;

    /* Read full page and update relevant portions */
    NumByteToWrite_Copy = NumByteToWrite;
    pBuffer_Copy = pBuffer;
    AddrTargetPage = (WriteAddr/FLASH_PAGE_SIZE) * FLASH_PAGE_SIZE;
    FLASH_ReadBuffer(Buffer, AddrTargetPage, FLASH_PAGE_SIZE);
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

    Addr = WriteAddr % FLASH_PAGE_SIZE;
    count = FLASH_PAGE_SIZE - Addr;
    NumOfPages =  NumByteToWrite / FLASH_PAGE_SIZE;
    NumOfSingle = NumByteToWrite % FLASH_PAGE_SIZE;
    
    if (Addr == 0) // WriteAddr is FLASH_PAGE_SIZE aligned
    {
        if (NumOfPages == 0) // NumByteToWrite < FLASH_PAGE_SIZE
        {
            FLASH_WritePage(pBuffer, WriteAddr, NumByteToWrite);
        }
        else // NumByteToWrite > FLASH_PAGE_SIZE
        {
            while (NumOfPages--)
            {
                FLASH_WritePage(pBuffer, WriteAddr, FLASH_PAGE_SIZE);
                WriteAddr +=  FLASH_PAGE_SIZE;
                pBuffer += FLASH_PAGE_SIZE;
            }
            
            FLASH_WritePage(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else // WriteAddr is not FLASH_PAGE_SIZE aligned
    {
        if (NumOfPages == 0) // NumByteToWrite < FLASH_PAGE_SIZE
        {
            if (NumOfSingle > count) // (NumByteToWrite + WriteAddr) > FLASH_PAGE_SIZE
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
        else // NumByteToWrite > FLASH_PAGE_SIZE
        {
            NumByteToWrite -= count;
            NumOfPages =  NumByteToWrite / FLASH_PAGE_SIZE;
            NumOfSingle = NumByteToWrite % FLASH_PAGE_SIZE;
            
            FLASH_WritePage(pBuffer, WriteAddr, count);
            WriteAddr +=  count;
            pBuffer += count;
            
            while (NumOfPages--)
            {
                FLASH_WritePage(pBuffer, WriteAddr, FLASH_PAGE_SIZE);
                WriteAddr +=  FLASH_PAGE_SIZE;
                pBuffer += FLASH_PAGE_SIZE;
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
    page_offset = ReadAddr / FLASH_PAGE_SIZE;
    byte_offset = ReadAddr % FLASH_PAGE_SIZE;

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
uint8_t FLASH_SendByte(uint8_t byte)
{
    /* Loop while DR register in not emplty */
    while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET);
    
    /* Send byte through the SPI1 peripheral */
    SPI_I2S_SendData(FLASH_SPI, byte);
    
    /* Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET);
    
    /* Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(FLASH_SPI);
}

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
