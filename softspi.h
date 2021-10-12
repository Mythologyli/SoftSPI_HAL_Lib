/**
 * @file    softspi.h
 * @author  Myth
 * @version 0.2
 * @date    2021.10.12
 * @brief   STM32 SoftSPI Library
 */

#ifndef __SOFTSPI_H
#define __SOFTSPI_H

#include "softspi_conf.h"

/**
  * @brief  SoftSPI Structure definition
  */
typedef struct
{
    GPIO_TypeDef *SCLK_GPIO;
    uint32_t SCLK_Pin;

    GPIO_TypeDef *MOSI_GPIO;
    uint32_t MOSI_Pin;

    GPIO_TypeDef *MISO_GPIO;
    uint32_t MISO_Pin;

    GPIO_TypeDef *SS_GPIO;
    uint32_t SS_Pin;

    uint32_t Delay_Time;
} SoftSPI_TypeDef;

HAL_StatusTypeDef SoftSPI_Init(SoftSPI_TypeDef *SoftSPIx);

uint8_t SoftSPI_WriteRead(SoftSPI_TypeDef *SoftSPIx, uint8_t byte);

void SoftSPI_WriteReadBuff(SoftSPI_TypeDef *SoftSPIx, uint8_t *pWrite, uint8_t *pRead, uint32_t len);

#endif
