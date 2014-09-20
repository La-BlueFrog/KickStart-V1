/**
  ******************************************************************************
  * @file    mass_mal.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Medium Access Layer interface
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"

#include "mass_mal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t Mass_Memory_Size[2];
uint32_t Mass_Block_Size[2];
uint32_t Mass_Block_Count[2];
__IO uint32_t Status = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : MAL_Init
* Description    : Initializes the Media on the STM32
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Init(uint8_t lun)
{
    FLASH_Init();
    return MAL_OK;
}
/*******************************************************************************
* Function Name  : MAL_Write
* Description    : Write sectors
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_Write(uint8_t lun, uint32_t Memory_Offset, uint32_t *Writebuff, uint16_t Transfer_Length)
{
#if defined (DEBUG)
    xprintf("[+] WriteBuffer: Adresse 0x%02x, NbOctets %d\n", Memory_Offset, Transfer_Length);
#endif
    FLASH_WriteBuffer((uint8_t*)Writebuff, Memory_Offset, (uint32_t)Transfer_Length);
    return MAL_OK;
}

/*******************************************************************************
* Function Name  : MAL_Read
* Description    : Read sectors
* Input          : None
* Output         : None
* Return         : Buffer pointer
*******************************************************************************/
uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint32_t *Readbuff, uint16_t Transfer_Length)
{
#if defined (DEBUG)
    xprintf("[-] ReadBuffer : Adresse 0x%02x, NbOctets %d\n", Memory_Offset, Transfer_Length);
#endif
    FLASH_ReadBuffer((uint8_t*)Readbuff, Memory_Offset, (uint32_t)Transfer_Length);
    return MAL_OK;
}

/*******************************************************************************
* Function Name  : MAL_GetStatus
* Description    : Get status
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
uint16_t MAL_GetStatus (uint8_t lun)
{
    
    Mass_Block_Count[0] = FLASH_BLOCK_SIZE * FLASH_ZONE_SIZE * FLASH_MAX_ZONE;
    Mass_Block_Size[0]  = FLASH_PAGE_SIZE;
    Mass_Memory_Size[0] = (Mass_Block_Count[0] * Mass_Block_Size[0]);
    
#if defined (DEBUG)
    xprintf("[+] GetStatus  : BlockCount=%d, BlockSize=%d\n", Mass_Block_Count[0], Mass_Block_Size[0]);
#endif
    
    return MAL_OK;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

