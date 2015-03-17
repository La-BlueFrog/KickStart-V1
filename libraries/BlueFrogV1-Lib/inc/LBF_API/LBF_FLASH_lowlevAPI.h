/*******************************************************************************
 * LBF_FLASH_lowlevAPI.h
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




/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LBF_FLASH_LOWLEVAPI_H
#define __LBF_FLASH_LOWLEVAPI_H

#include <stdint.h>  // to keep this header file self-sufficient as below function prototypes use uint32_t etc.
#include "pin_aliases.h" // to keep this header file self-sufficient as below macros use pin names
#include "stm32l1xx.h"   // to keep this header file self-sufficient as below macros use direct access to Cortex-M3 register names  (...change this !)


/* Exported constants --------------------------------------------------------*/

/* Commandes des registres de la Flash ADESTO AT45DB161E */
#define FLASH_CMD_WRITE1        0x82    /* Write to Page in Main Memory thru Buffer 1 with built-in page erase */
#define FLASH_CMD_WRITE2        0x85    /* Write to Page in Main Memory thru Buffer 2 with built-in page erase */
#define FLASH_CMD_READ_LF       0x03    /* Read from Memory instruction: Continuous Array, Low Frequency Mode */
#define FLASH_CMD_RDSR          0xD7       /* Read Status Register instruction  */
#define FLASH_CMD_RDID          0x9F       /* Read ID Register instruction  */
#define FLASH_CMD_PAGESIZE1     0x3D       /* Set Page Size instruction, Byte1  */
#define FLASH_CMD_PAGESIZE2     0x2A       /* ... Byte2  */
#define FLASH_CMD_PAGESIZE3     0x80       /* ... Byte3  */
#define FLASH_CMD_PAGESIZE4     0xA6       /* ... Byte4 - set for 512 byte size */
#define FLASH_CMD_BULKERASE1     0xC7       /* Chip Erase instruction, Byte1  */
#define FLASH_CMD_BULKERASE2     0x94       /* ... Byte2  */
#define FLASH_CMD_BULKERASE3     0x80       /* ... Byte3  */
#define FLASH_CMD_BULKERASE4     0x9A       /* ... Byte4  */

#define FLASH_DUMMY_BYTE        0xA5

#define FLASH_READY_FLAG        0x80    /* mask to extract Flash Ready/notBusy flag in status Register */

#define FLASH_PAGE_LENGTH           0x0200  // 512 bytes per page mode
#define FLASH_NUMBER_OF_PAGES	    4096    // 4096 pages in AT45DB161E
#define FLASH_CAPACITY	(FLASH_PAGE_LENGTH * FLASH_NUMBER_OF_PAGES)

#define FLASH_BLOCK_SIZE            0x0020  // 32x256 bytes pages per block
#define FLASH_ZONE_SIZE             0x0400  // 1024 Blocks per zone
#define FLASH_SPARE_AREA_SIZE       0x0010  // last 16 bytes as spare area
#define FLASH_MAX_ZONE              0x0001  // 1 zone of 64 blocks

/* Definitions des ports I/O */
#define FLASH_CS_LOW()          GPIO_LOW(FLASH_CS_GPIO_PORT, FLASH_CS_PIN)
#define FLASH_CS_HIGH()         GPIO_HIGH(FLASH_CS_GPIO_PORT, FLASH_CS_PIN)
#define FLASH_WR_LOW()          GPIO_LOW(FLASH_WR_GPIO_PORT, FLASH_WR_PIN)
#define FLASH_WR_HIGH()         GPIO_HIGH(FLASH_WR_GPIO_PORT, FLASH_WR_PIN)
#define FLASH_HOLD_LOW()        GPIO_LOW(FLASH_HOLD_GPIO_PORT, FLASH_HOLD_PIN)
#define FLASH_HOLD_HIGH()       GPIO_HIGH(FLASH_HOLD_GPIO_PORT, FLASH_HOLD_PIN)

/* Exported functions --------------------------------------------------------*/

/* Fonctions de couche haute */
void FLASH_EraseBulk(void);
void FLASH_WritePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void FLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint32_t NumByteToWrite);
void FLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint32_t NumByteToRead);
uint32_t FLASH_ReadID(void);

/* Fonctions de couche basse */
uint8_t FLASH_SendByte(uint8_t byte);
void FLASH_WaitForWriteEnd(void);



#endif  /*__LBF_FLASH_LOWLEVAPI_H */ 

/***************************************************************END OF FILE****/
