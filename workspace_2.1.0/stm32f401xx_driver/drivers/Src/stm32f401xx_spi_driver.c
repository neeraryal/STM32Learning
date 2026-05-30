/*
 * stm32f401xx_spi_driver.c
 *
 *  Created on: 24-May-2026
 *      Author: nirmal.aryal
 */

#include "stm32f401xx.h"
#include "stm32f401xx_spi_driver.h"

/**
 * @brief Get the status of a  SPI  SR flag
 * 
 * @param pSPIx Pointer to the SPI peripheral
 * @param Flag The flag to check
 * @return uint8_t SET if the flag is set, RESET otherwise
 */
uint8_t SPI_GetSRFlagStatus(SPI_RegDef_t* pSPIx, uint8_t Flag)
{
    if(pSPIx->SR & Flag)
    {
        return SET;
    }
    return RESET;
}
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
    SPI_PeriClockControl(pSPIHandle->pSPIx,ENABLE);
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
 * @brief Enable or Disable the SPI Peripheral by setting or clearing the SPE bit in CR1 register
 * 
 * @param pSPIx Pointer to SPI peripheral (SPI1, SPI2, SPI3, SPI4) 
 * @param ENorDI Enable or Disable the SPI Peripheral (ENABLE/DISABLE)
 */
void SPI_PeripheralControl(SPI_RegDef_t* pSPIx,uint8_t ENorDI)
{
    if(ENorDI ==ENABLE)
    {
        pSPIx->CR1 |= (1<<SPI_CR1_SPE);
    }
    else{
        pSPIx->CR1 &= ~(1<<SPI_CR1_SPE);
    }
}
/**
 * @brief Enable or Disable the SPI Peripheral by setting or clearing the SPE bit in CR1 register
 * 
 * @param pSPIx Pointer to SPI peripheral (SPI1, SPI2, SPI3, SPI4) 
 * @param ENorDI Enable or Disable the SPI Peripheral (ENABLE/DISABLE)
 */
void SPI_SSIConfig(SPI_RegDef_t* pSPIx,uint8_t ENorDI)
{
    if(ENorDI ==ENABLE)
    {
        pSPIx->CR1 |= (1<<SPI_CR1_SSI);
    }
    else{
        pSPIx->CR1 &= ~(1<<SPI_CR1_SSI);
    }
}

void SPI_SSOEConfig(SPI_RegDef_t* pSPIx,uint8_t ENorDI)
{
    if(ENorDI == ENABLE)
    {
        pSPIx->CR2 |= (1<<SPI_CR2_SSOE);
    }
    else{
        pSPIx->CR2 &= ~(1<<SPI_CR2_SSOE);
    }
}
/**
 * @brief SPI Data send and Receive API
 * 
 * @param pSPIx Pointer to SPI peripheral (SPI1, SPI2, SPI3, SPI4)
 * @param pTXBuffer Pointer to transmit buffer
 * @param Len Length of data to be transmitted
 * 
 * @note Current Implementation is a blocking call
 */
void SPI_SendData (SPI_RegDef_t* pSPIx, uint8_t * pTXBuffer , uint32_t Len)
{
    //Implementing Blocking Call for SPI Write 
    //1. Check if len of data the we need to send is grater than 0
    while(Len >0)
    {
        //2. Check if Transmit Buffer is empty or not, as there can be data present , so we dont want to overwrite it.
        while(!SPI_GetSRFlagStatus(pSPIx,SPI_TXE_FLAG_MASK));

        //3. Chekc for the data size 8 or 16 bit 
        if(pSPIx->SR & 1<<11)
        {
            //16 Bit data fortmat
            pSPIx->DR = *((uint16_t*)pTXBuffer);
            Len-=2;
            pTXBuffer = (uint8_t*)((uint16_t*)pTXBuffer + 1);
        }
        else
        {
            //8 bit data format 
            pSPIx->DR = *pTXBuffer;
            Len-=1;
            pTXBuffer++;
        }
    }

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