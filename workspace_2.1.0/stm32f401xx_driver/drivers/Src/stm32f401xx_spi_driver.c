/*
 * stm32f401xx_spi_driver.c
 *
 *  Created on: 24-May-2026
 *      Author: nirmal.aryal
 */

#include "stm32f401xx.h"
#include "stm32f401xx_spi_driver.h"

/**
 * @brief SPI Peripheral Clock Setup
 * 
 * @param pSPIx Pointer to SPI peripheral (SPI1, SPI2, SPI3, SPI4)
 * @param EnorDi Enable or Disable the clock (ENABLE/DISABLE)
 */
void SPI_PeriClockControl(SPI_RegDef_t* pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pSPIx == SPI1)
        {
            SPI1_PCLK_EN();
        }
        else if(pSPIx == SPI2)
        {
            SPI2_PCLK_EN();
        }
        else if(pSPIx == SPI3)
        {
            SPI3_PCLK_EN();
        }      
        else if(pSPIx == SPI4)
        {
            SPI4_PCLK_EN();
        }
    }
    else
    {
        if(pSPIx == SPI1)
        {
            SPI1_PCLK_DI();
        }
        else if(pSPIx == SPI2)
        {
            SPI2_PCLK_DI();
        }
        else if(pSPIx == SPI3)
        {
            SPI3_PCLK_DI();
        }
        else if(pSPIx == SPI4)
        {
            SPI4_PCLK_DI();
        }
    }
}


/**
 * @brief SPI Init and DeInit
 * 
 * @param pSPIHandle Pointer to SPI handle structure
 */
void SPI_Init(SPI_Handle_t* pSPIHandle)
{
    uint32_t temp_reg = 0;

    //1. Inilialize the SPI MODE
    temp_reg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;

    //2. Initialize BUS Config
    if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
    {
        //Disable Bidiretctional Mode
        temp_reg  &= ~(1<<SPI_CR1_BIDIMODE);
    }
    if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
    {
        //Enable Bidiretctional Mode 
        temp_reg  |= (1<<SPI_CR1_BIDIMODE);
    }
    if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RX_ONLY)
    {
        //Disable Bidiretctional Mode  && Enable RX Only Mode
        temp_reg  &= ~(1<<SPI_CR1_BIDIMODE);
        temp_reg  |= (1<<SPI_CR1_RXONLY);
    }

    //3. Initialize Clock Speed
    temp_reg |= (pSPIHandle->SPIConfig.SPI_SCLKSpeed << SPI_CR1_BR);

    //4. Initialize DFF Value 
    temp_reg |= (pSPIHandle->SPIConfig.SPI_DFF<<SPI_CR1_DFF);

    //5. Initialize CPOL 
    temp_reg |= (pSPIHandle->SPIConfig.SPI_CPOL<<SPI_CR1_CPOL);

    //6. Initilaize CPHA 
    temp_reg |= (pSPIHandle->SPIConfig.SPI_CPHA<<SPI_CR1_CPHA);

    //7. Initilaize SSM
    temp_reg |= (pSPIHandle->SPIConfig.SPI_SSM<<SPI_CR1_SSM);
    if(pSPIHandle->SPIConfig.SPI_SSM == 1)
    {
        temp_reg |= 1<<SPI_CR1_RXONLY;
    }
    pSPIHandle->pSPIx->CR1 = temp_reg;
}

/**
 * @brief SPI DeInit
 * 
 * @param pSPIx Pointer to SPI peripheral (SPI1, SPI2, SPI3, SPI4)
 */
void SPI_DeInit(SPI_RegDef_t* pSPIx)
{

}

/**
 * @brief SPI Data send and Receive API
 * 
 * @param pSPIx Pointer to SPI peripheral (SPI1, SPI2, SPI3, SPI4)
 * @param pTXBuffer Pointer to transmit buffer
 * @param Len Length of data to be transmitted
 */
void SPI_SendData (SPI_RegDef_t* pSPIx, uint8_t * pTXBuffer , uint32_t Len)
{

}

/**
 * @brief SPI Data send and Receive API
 * 
 * @param pSPIx Pointer to SPI peripheral (SPI1, SPI2, SPI3, SPI4)
 * @param pRXBuffer Pointer to receive buffer
 * @param Len Length of data to be received
 */
void SPI_ReceiveData(SPI_RegDef_t* pSPIx, uint8_t * pRXBuffer , uint32_t Len)
{

}

/**
 * @brief SPI IRQ Priority Config
 * 
 * @param IRQNumber IRQ number
 * @param IRQPriority IRQ priority
 */
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{

}

/**
 * @brief SPI IRQ Interrupt Config
 * 
 * @param IRQNumber IRQ number
 * @param IRQEnorDi IRQ enable or disable
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQEnorDi)
{

}

/**
 * @brief SPI IRQ Handling
 * 
 * @param pHandle Pointer to SPI handle structure
 */
void SPI_IRQHandling(SPI_Handle_t * pHandle)
{

}