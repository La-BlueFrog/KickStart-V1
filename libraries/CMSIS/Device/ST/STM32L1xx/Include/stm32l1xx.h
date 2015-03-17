/**
  ******************************************************************************
  * @file    stm32l1xx.h
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    5-September-2014
  * @brief   CMSIS STM32L1xx Device Peripheral Access Layer Header File. 
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *            - Configuration section that allows to select:
  *              - The STM32L1xx device used in the target application
  *              - To use or not the peripheral’s drivers in application code(i.e. 
  *                code will be based on direct access to peripheral’s registers 
  *                rather than drivers API), this option is controlled by 
  *                "#define USE_HAL_DRIVER"
  *  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */


/* ========================================================================== */
/* --       Cut-down ST's version for La BlueFrog                     ------- */
/* --       considering the processor is fixed (STM32L151RC)          ------- */
/* --       and we do use HAL Library                                 ------- */
/* ========================================================================== */



/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup stm32l1xx
  * @{
  */
    
#ifndef __STM32L1XX_H
#define __STM32L1XX_H

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */
  
/** @addtogroup Library_configuration_section
  * @{
  */

/* Uncomment the line below according to the target STM32L device used in your 
   application 
  */

#if !defined (STM32L151xC) 
  #define STM32L151xC  
#endif

  
#if !defined  (USE_HAL_DRIVER)
  #define USE_HAL_DRIVER */
#endif 

/**
  * @brief CMSIS Device version number V2.0.0
  */
#define __STM32L1xx_CMSIS_DEVICE_VERSION_MAIN   (0x02) /*!< [31:24] main version */                                  
#define __STM32L1xx_CMSIS_DEVICE_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __STM32L1xx_CMSIS_DEVICE_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define __STM32L1xx_CMSIS_DEVICE_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32L1xx_CMSIS_DEVICE_VERSION        ((__CMSIS_DEVICE_VERSION_MAIN     << 24)\
                                      |(__CMSIS_DEVICE_HAL_VERSION_SUB1 << 16)\
                                      |(__CMSIS_DEVICE_HAL_VERSION_SUB2 << 8 )\
                                      |(__CMSIS_DEVICE_HAL_VERSION_RC))

/**
  * @}
  */

/** @addtogroup Device_Included
  * @{
  */

#if defined(STM32L151xC)
  #include "stm32l151xc.h"
#else
  #error "Please select first the target STM32L1xx device used in your application (in stm32l1xx.h file)"
#endif

/**
  * @}
  */

/** @addtogroup Exported_types
  * @{
  */  
typedef enum 

{
  RESET = 0, 
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum 
{
  DISABLE = 0, 
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum 
{
  ERROR = 0, 
  SUCCESS = !ERROR
} ErrorStatus;

/**
  * @}
  */


/** @addtogroup Exported_macros
  * @{
  */
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL))) 


/**
  * @}
  */

/***** REMOVED XC  (recursive call...)
#if defined (USE_HAL_DRIVER)
 #include "stm32l1xx_hal.h"
#endif 
***/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STM32L1xx_H */
/**
  * @}
  */

/**
  * @}
  */
  



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
