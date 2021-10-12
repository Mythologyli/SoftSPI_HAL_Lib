/**
 * @file    softspi.c
 * @author  Myth
 * @version 0.1
 * @date    2021.10.12
 * @brief   STM32 SoftSPI Library
 */

#include "softspi.h"

SoftSPI_InitTypeDef config;

uint8_t GPIOx_Pin_Init(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode, uint32_t Pull);

HAL_StatusTypeDef SoftSPI_Init(SoftSPI_InitTypeDef *SoftSPI_Initure)
{
    config.SCLK_GPIO = SoftSPI_Initure->SCLK_GPIO;
    config.SCLK_Pin = SoftSPI_Initure->SCLK_Pin;

    if (!GPIOx_Pin_Init(config.SCLK_GPIO, config.SCLK_Pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL))
        return HAL_ERROR;

    config.MOSI_GPIO = SoftSPI_Initure->MOSI_GPIO;
    config.MOSI_Pin = SoftSPI_Initure->MOSI_Pin;

    if (!GPIOx_Pin_Init(config.MOSI_GPIO, config.MOSI_Pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL))
        return HAL_ERROR;

    config.MISO_GPIO = SoftSPI_Initure->MISO_GPIO;
    config.MISO_Pin = SoftSPI_Initure->MISO_Pin;

    if (!GPIOx_Pin_Init(config.MISO_GPIO, config.MISO_Pin, GPIO_MODE_INPUT, GPIO_PULLUP))
        return HAL_ERROR;

    config.SS_GPIO = SoftSPI_Initure->SS_GPIO;
    config.SS_Pin = SoftSPI_Initure->SS_Pin;

    if (!GPIOx_Pin_Init(config.SS_GPIO, config.SS_Pin, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL))
        return HAL_ERROR;

    config.Delay_Time = SoftSPI_Initure->Delay_Time;

    return HAL_OK;
}

uint8_t SoftSPI_WriteRead(uint8_t byte)
{
    uint8_t data = 0;
    uint8_t i;

    // Select Device
    HAL_GPIO_WritePin(config.SS_GPIO, config.SS_Pin, GPIO_PIN_RESET);

    for (i = 0; i < 8; i++)
    {
        HAL_GPIO_WritePin(config.SCLK_GPIO, config.SCLK_Pin, GPIO_PIN_RESET);
        SoftSPI_Delay_us(config.Delay_Time);

        if (byte & 0x80)
            HAL_GPIO_WritePin(config.MOSI_GPIO, config.MOSI_Pin, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(config.MOSI_GPIO, config.MOSI_Pin, GPIO_PIN_RESET);

        SoftSPI_Delay_us(config.Delay_Time);

        byte <<= 1;
        HAL_GPIO_WritePin(config.SCLK_GPIO, config.SCLK_Pin, GPIO_PIN_SET);
        SoftSPI_Delay_us(config.Delay_Time);

        data <<= 1;
        if (HAL_GPIO_ReadPin(config.MISO_GPIO, config.MISO_Pin) == GPIO_PIN_SET)
            data |= 0x01;

        SoftSPI_Delay_us(config.Delay_Time);
    }

    // Unselect Device
    HAL_GPIO_WritePin(config.SS_GPIO, config.SS_Pin, GPIO_PIN_SET);

    return data;
}

void SoftSPI_WriteReadBuff(uint8_t *pWrite, uint8_t *pRead, uint32_t len)
{
    uint8_t data;
    uint8_t byte;
    uint8_t i, j;

    // Select Device
    HAL_GPIO_WritePin(config.SS_GPIO, config.SS_Pin, GPIO_PIN_RESET);

    for (j = 0; j < len; j++)
    {
        data = 0;
        byte = pWrite[j];

        for (i = 0; i < 8; i++)
        {
            HAL_GPIO_WritePin(config.SCLK_GPIO, config.SCLK_Pin, GPIO_PIN_RESET);
            SoftSPI_Delay_us(config.Delay_Time);

            if (byte & 0x80)
                HAL_GPIO_WritePin(config.MOSI_GPIO, config.MOSI_Pin, GPIO_PIN_SET);
            else
                HAL_GPIO_WritePin(config.MOSI_GPIO, config.MOSI_Pin, GPIO_PIN_RESET);

            SoftSPI_Delay_us(config.Delay_Time);

            byte <<= 1;
            HAL_GPIO_WritePin(config.SCLK_GPIO, config.SCLK_Pin, GPIO_PIN_SET);
            SoftSPI_Delay_us(config.Delay_Time);

            data <<= 1;
            if (HAL_GPIO_ReadPin(config.MISO_GPIO, config.MISO_Pin) == GPIO_PIN_SET)
                data |= 0x01;

            SoftSPI_Delay_us(config.Delay_Time);
        }

        pRead[j] = data;
    }

    // Unselect Device
    HAL_GPIO_WritePin(config.SS_GPIO, config.SS_Pin, GPIO_PIN_SET);
}

uint8_t GPIOx_Pin_Init(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Mode, uint32_t Pull)
{
    switch ((uint32_t)(GPIOx))
    {
    case (uint32_t)GPIOA:
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_Initure.Pin = Pin;
        GPIO_Initure.Mode = Mode;
        GPIO_Initure.Pull = Pull;
        GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_Initure);
    }
    break;

    case (uint32_t)GPIOB:
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_GPIOB_CLK_ENABLE();

        GPIO_Initure.Pin = Pin;
        GPIO_Initure.Mode = Mode;
        GPIO_Initure.Pull = Pull;
        GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_Initure);
    }
    break;

    case (uint32_t)GPIOC:
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_GPIOC_CLK_ENABLE();

        GPIO_Initure.Pin = Pin;
        GPIO_Initure.Mode = Mode;
        GPIO_Initure.Pull = Pull;
        GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOC, &GPIO_Initure);
    }
    break;

    case (uint32_t)GPIOD:
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_GPIOD_CLK_ENABLE();

        GPIO_Initure.Pin = Pin;
        GPIO_Initure.Mode = Mode;
        GPIO_Initure.Pull = Pull;
        GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOD, &GPIO_Initure);
    }
    break;

    default:
        return 0;
    }

    return 1;
}
