/*******************************************************************************
 * pin_aliases.h
 * 
 * Author: La BlueFrog, 2015
 *
 * This program is free software; you can redistribute it and/or modify
 * t under the terms of the GNU General Public License as published by
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

#ifndef __PIN_ALIASES_H
#define __PIN_ALIASES_H

#include "stm32l1xx.h"  //to allow using Cortex-M register names while keeping this header self-sufficient

/******************************************************************************/
/*        DEFINITIONS DES CONSTANTES POUR LA VERSION INFRAMODULE V1.5         */
/******************************************************************************/

/* Entrees/Sorties */
#define SLIDE_1_PIN                     GPIO_PIN_12                 // PC12
#define SLIDE_1_GPIO_PORT               GPIOC
#define SLIDE_2_PIN                     GPIO_PIN_15                 // PA15
#define SLIDE_2_GPIO_PORT               GPIOA

#define LED_GREEN_PIN                   GPIO_PIN_2                  // PA2
#define LED_GREEN_PORT                  GPIOA
#define LED_RED_PIN                     GPIO_PIN_3                  // PA3
#define LED_RED_PORT                    GPIOA



/* I2C2 */
#define I2C2_SCL_PIN                 GPIO_PIN_10                 // PB10
#define I2C2_SCL_GPIO_PORT           GPIOB
#define I2C2_SDA_PIN                 GPIO_PIN_11                 // PB11
#define I2C2_SDA_GPIO_PORT           GPIOB


/* Power Management LP3913 (uses I2C2) */
#define PWR_ONSTAT_PIN                  GPIO_PIN_0                  // PB0
#define PWR_ONSTAT_GPIO_PORT            GPIOB
#define PWR_POWERACK_PIN                GPIO_PIN_1                  // PA1
#define PWR_POWERACK_GPIO_PORT          GPIOA
#define PWR_NRST_PIN                    GPIO_PIN_7                  // PA7
#define PWR_NRST_GPIO_PORT              GPIOA
#define PWR_IRQB_PIN                    GPIO_PIN_6                  // PA6
#define PWR_IRQB_GPIO_PORT              GPIOA


/* SPI2 */
#define SPI2_SCK_PIN               GPIO_PIN_13                 // PB13
#define SPI2_SCK_GPIO_PORT         GPIOB
#define SPI2_MISO_PIN              GPIO_PIN_14                 // PB14
#define SPI2_MISO_GPIO_PORT        GPIOB
#define SPI2_MOSI_PIN              GPIO_PIN_15                 // PB15
#define SPI2_MOSI_GPIO_PORT        GPIOB


/* Memoire FLASH M25PX16M (uses SPI2) */
#define FLASH_CS_PIN                    GPIO_PIN_12                 // PB12
#define FLASH_CS_GPIO_PORT              GPIOB
#define FLASH_HOLD_PIN                  GPIO_PIN_8                  // PA8
#define FLASH_HOLD_GPIO_PORT            GPIOA
#define FLASH_WR_PIN                    GPIO_PIN_9                  // PC9
#define FLASH_WR_GPIO_PORT              GPIOC


/* Ecran OLED DD-160128FC-1A */

// Broches de configuration
#define OLED_CPU_PIN                    GPIO_PIN_10                 // PC10
#define OLED_CPU_PORT                   GPIOC
#define OLED_PS_PIN                     GPIO_PIN_11                 // PC11
#define OLED_PS_PORT                    GPIOC

// Broches de controle
#define OLED_RS_PIN                     GPIO_PIN_9                  // PB9
#define OLED_RS_PORT                    GPIOB
#define OLED_CS_PIN                     GPIO_PIN_4                  // PA4
#define OLED_CS_PORT                    GPIOA
#define OLED_RD_PIN                     GPIO_PIN_2                  // PD2
#define OLED_RD_PORT                    GPIOD
#define OLED_WR_PIN                     GPIO_PIN_0                  // PA0
#define OLED_WR_PORT                    GPIOA
#define OLED_RESET_PIN                  GPIO_PIN_13                 // PC13
#define OLED_RESET_PORT                 GPIOC

// Broches de donnees - Bus parallele
#define OLED_D9_PIN                     GPIO_PIN_0                  // PC0
#define OLED_D9_PORT                    GPIOC
#define OLED_D10_PIN                    GPIO_PIN_1                  // PC1
#define OLED_D10_PORT                   GPIOC
#define OLED_D11_PIN                    GPIO_PIN_2                  // PC2
#define OLED_D11_PORT                   GPIOC
#define OLED_D12_PIN                    GPIO_PIN_3                  // PC3
#define OLED_D12_PORT                   GPIOC
#define OLED_D13_PIN                    GPIO_PIN_4                  // PC4
#define OLED_D13_PORT                   GPIOC
#define OLED_D14_PIN                    GPIO_PIN_5                  // PC5
#define OLED_D14_PORT                   GPIOC
#define OLED_D15_PIN                    GPIO_PIN_6                  // PC6
#define OLED_D15_PORT                   GPIOC
#define OLED_D16_PIN                    GPIO_PIN_7                  // PC7
#define OLED_D16_PORT                   GPIOC
#define OLED_D17_PIN                    GPIO_PIN_8                  // PC8
#define OLED_D17_PORT                   GPIOC
#define OLED_CS_PIN                     GPIO_PIN_4                  // PA4
#define OLED_CS_GPIO_PORT               GPIOA


// SPI1
#define SPI_1_SCK_PIN                GPIO_PIN_3                  // PB3 (D17)
#define SPI_1_SCK_GPIO_PORT          GPIOB
#define SPI_1_MISO_PIN               GPIO_PIN_4                  // PB4 (D15)
#define SPI_1_MISO_GPIO_PORT         GPIOB
#define SPI_1_MOSI_PIN               GPIO_PIN_5                  // PB5 (D16)
#define SPI_1_MOSI_GPIO_PORT         GPIOB


// Broches d'alimentation VCC_OLED
#define OLED_VDDH_PIN                   GPIO_PIN_5                  // PA5
#define OLED_VDDH_PORT                  GPIOA


/* Debug UART : TTL-232R-3V3 */
#define UART                            USART1
#define UART_TX_PIN                     GPIO_PIN_9                  // PA9 (TX)
#define UART_TX_PORT                    GPIOA
#define UART_RX_PIN                     GPIO_PIN_10                 // PA10 (RX)
#define UART_RX_PORT                    GPIOA


/* EXTERNAL CONNECTOR  */
#define HEADER_POS1_PIN                 GPIO_PIN_10                 // PA10
#define HEADER_POS1_PORT                GPIOA
#define HEADER_POS2_PIN                 GPIO_PIN_9                  // PA9 
#define HEADER_POS2_PORT                GPIOA



#endif /*__PIN_ALIASES_H*/

/***************************************************************END OF FILE****/
