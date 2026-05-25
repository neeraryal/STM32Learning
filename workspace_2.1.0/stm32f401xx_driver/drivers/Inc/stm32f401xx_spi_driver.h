/*
 * stm32f401xx_spi_driver.h
 *
 *  Created on: 24-May-2026
 *      Author: nirmal.aryal
 */

#ifndef INC_STM32F401XX_SPI_DRIVER_H_
#define INC_STM32F401XX_SPI_DRIVER_H_

#include "stm32f401xx.h"

typedef struct{
    uint8_t SPI_DeviceMode;
    uint8_t SPI_BusConfig;
    uint8_t SPI_SCLKSpeed;
    uint8_t SPI_DFF;
    uint8_t SPI_CPOL;
    uint8_t SPI_CPHA;
    uint8_t SPI_SSM;

}SPI_Config_t;

typedef struct{
    SPI_RegDef_t  *pSPIx;;
    SPI_Config_t SPIConfig;
}SPI_Handle_t;


/**
 * @brief SPI Peripheral Clock Setup
 */

void SPI_PeriClockControl(SPI_RegDef_t* pSPIx, uint8_t EnorDi);

/**
* @brief SPI Init and DeInit
*/

void SPI_Init(SPI_Handle_t* pSPIHandle);
void SPI_DeInit(SPI_RegDef_t* pSPIx);

/**
* @brief SPI Data send and Receive API
*/

void SPI_SendData (SPI_RegDef_t* pSPIx, uint8_t * pTXBuffer , uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t* pSPIx, uint8_t * pRXBuffer , uint32_t Len);

/*
* IRQ Config and IRQ Handling
*/

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQEnorDi);
void SPI_IRQHandling(SPI_Handle_t * pHandle);

#endif /* INC_STM32F401XX_SPI_DRIVER_H_ */
