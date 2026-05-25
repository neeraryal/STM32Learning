/*
 * stm32f401xx_gpio_driver.c
 *
 *  Created on: 16-May-2026
 *      Author: nirmal.aryal
 */
#include <stdint.h>
#include "stm32f401xx_gpio_driver.h"
// #include "stm32f401xx.h"

/**
 * @brief  This function enables or disables the peripheral clock for the given GPIO port.
 * 
 * @param pGPIOx  Base address of the GPIO peripheral
 * @param EnorDi  Enable or Disable the clock (ENABLE/DISABLE)
 */
void GPIO_PeriClockControl(GPIO_RegDef_t* pGPIOx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }
        else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN();
        }
        else if(pGPIOx == GPIOH)
        {
            GPIOH_PCLK_EN();
        }
    }
    else
    {
        if(pGPIOx == GPIOA)
        {
            GPIOA_PCLK_DI();
        }
        else if(pGPIOx == GPIOB)
        {
            GPIOB_PCLK_DI();
        }
        else if(pGPIOx == GPIOC)
        {
            GPIOC_PCLK_DI();
        }
        else if(pGPIOx == GPIOD)
        {
            GPIOD_PCLK_DI();
        }
        else if(pGPIOx == GPIOE)
        {
            GPIOE_PCLK_DI();
        }
        else if(pGPIOx == GPIOH)
        {
            GPIOH_PCLK_DI();
        }
    }

}

/**
 * @brief  This function initializes the GPIO pin based on the configuration provided in the GPIO_Handle_t structure.
 * 
 * @param pGPIOHandle  Pointer to the GPIO handle structure containing the configuration for the GPIO pin
 */
void GPIO_Init(GPIO_Handle_t* pGPIOHandle)
{
    uint32_t temp=0;
    //1). Initialize the mode of the GPIO pin
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG) //Doing for non interrupt Modes
    {
        temp= pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //Clearing the 2 bits corresponding to the pin number
        pGPIOHandle->pGPIOx->MODER |= temp;
    }
    else 
    {
        //1. Interrupt mode
        if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_INTERRUPT_RISING_EDGE) //Rising edge trigger
        {
            //1. Configure the FTSR (Falling Trigger Selection Register)
            EXTI->FTSR |= 1<< (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            //Clear the corresponding RTSR Bit 
            EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_INTERRUPT_FALLING_EDGE) //Falling edge trigger
        {
            //2. Configure the RTSR (Rising Trigger Selection Register)
            EXTI->RTSR |= 1<< (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            //Clear the corresponding RTSR Bit 
            EXTI->FTSR &= ~(1<< pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_INTERRUPT_RE_FE_TRIGGER) //Rising-Falling edge trigger
        {
            EXTI->FTSR |= 1<< (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->RTSR|= 1<< (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }

        //2. Configure the GPIO port selection in SYSCFG_EXTICR()

        uint8_t syscfg_register_index =  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
        uint8_t syscfg_register_index_pos = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4 ) * 4;
        SYSCFG_PCLK_EN();
        SYSCFG->EXTICR[syscfg_register_index] &= ~(0xFF << syscfg_register_index_pos);
        SYSCFG->EXTICR[syscfg_register_index] |= GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx) << (syscfg_register_index_pos);

        //3. Enable the EXTI interrupt delivery using IMR (Interrupt Mask Register)
        EXTI->IMR|= 1<< (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }

    temp=0;
    //2). Configure the speed settings
    temp=pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //Clearing the 2 bits corresponding to the pin number
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;

    temp=0;
    //3). Configure the Pullup - Pulldown setting
    temp=pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //Clearing the 2 bits corresponding to the pin number
    pGPIOHandle->pGPIOx->PUPDR |= temp;

    temp=0;
    //4). Configure the Output type setting
    temp=pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //Clearing the bit corresponding to the pin number
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    temp=0;
    //5). Configure the Alternate functionality
    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ALTRNATE_FUNCTION)
    {
        uint8_t temp_pin = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
        uint8_t temp_AF_mode =pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8 ;
        temp=pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp_pin);
        pGPIOHandle->pGPIOx->AFR[temp_AF_mode] &= ~(0xF << (4*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //Clearing the 4 bits corresponding to the pin number
        pGPIOHandle->pGPIOx->AFR[temp_AF_mode] |= temp; 
    }   
}

/**
 * @brief  This function de-initializes the GPIO port, resetting all its registers to their default values.
 * 
 * @param pGPIOx  Base address of the GPIO peripheral to be de-initialized
 */
void GPIO_DeInit(GPIO_RegDef_t* pGPIOx)
{
    if(pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if(pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if(pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    else if(pGPIOx == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    else if(pGPIOx == GPIOE)
    {
        GPIOE_REG_RESET();
    }
    else if(pGPIOx == GPIOH)
    {
        GPIOH_REG_RESET();
    }
}

/**
 * @brief  This function reads the value from a specific GPIO input pin.
 * 
 * @param pGPIOx      Base address of the GPIO peripheral
 * @param PinNumber   The number of the GPIO pin to read (0-15)
 * @return uint8_t    The value read from the specified GPIO pin (0 or 1)
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber)
{
    uint8_t value;
    value = (uint8_t)(((pGPIOx->IDR)>>PinNumber)& (0x00000001));
    return value;
}
/**
 * @brief  This function reads the value from all the GPIO input pins of a specific GPIO port.
 * 
 * @param pGPIOx      Base address of the GPIO peripheral
 * @return uint16_t   The value read from all the GPIO pins of the specified GPIO port (16 bits, each bit represents a pin)
 */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t* pGPIOx)
{
    uint16_t value;
    value = (uint16_t)(pGPIOx->IDR);
    return value;
}
/**
 * @brief  This function writes a value to a specific GPIO output pin.
 * 
 * @param pGPIOx      Base address of the GPIO peripheral
 * @param PinNumber   The number of the GPIO pin to write to (0-15)
 * @param Value       The value to write to the specified GPIO pin (0 or 1)
 */
void GPIO_WritetoOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    if(Value == GPIO_PIN_SET)
        pGPIOx->ODR |= (Value << PinNumber);  //Write 1 to the Register bit
    else
        pGPIOx->ODR &= ~(Value << PinNumber); //Write 0 to the Register bit
} 

/*
 * @brief  This function writes a value to all the GPIO output pins of a specific GPIO port.
 * 
 * @param pGPIOx      Base address of the GPIO peripheral
 * @param Value       The value to write to all the GPIO pins of the specified GPIO port (16 bits, each bit represents a pin)
 */
void GPIO_WritetoOutputort(GPIO_RegDef_t* pGPIOx, uint16_t Value)
{
    pGPIOx->ODR = Value; 
}

/**
 * @brief  This function toggles the value of a specific GPIO output pin.
 * 
 * @param pGPIOx      Base address of the GPIO peripheral
 * @param PinNumber   The number of the GPIO pin to toggle (0-15)
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber)
{
    pGPIOx->ODR ^= (1<<PinNumber);
}

/**
 * @brief  This function configures the interrupt for a specific GPIO pin.
 * 
 * @param IRQNumber       The IRQ number corresponding to the GPIO pin
 * @param IRQEnorDi       Enable or Disable the interrupt (ENABLE/DISABLE)
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQEnorDi)
{
    if(IRQEnorDi == ENABLE)
    {
        if(IRQNumber <=31)
        {
            *NVIC_ISER0 = (1<<IRQNumber %32);
        }
        else if(IRQNumber <=63)
        {
            *NVIC_ISER1 = 1<<(IRQNumber %32);
        }
        else if(IRQNumber <=95)
        {
            *NVIC_ISER2 = 1<<(IRQNumber %32);
        }
    }
    else
    {
        if(IRQNumber <=31)
        {
            *NVIC_ICER0 = (1<<IRQNumber %32);
        }
        else if(IRQNumber <=63)
        {
            *NVIC_ICER0 = 1<<(IRQNumber %32);
        }
        else if(IRQNumber <=95)
        {
            *NVIC_ICER0 = 1<<(IRQNumber %32);
        }

    }

}

/**
 * @brief  This function configures the priority of a specific GPIO interrupt.
 * 
 * @param IRQNumber       The IRQ number corresponding to the GPIO pin
 * @param IRQPriority     The priority level to be assigned to the interrupt (0-15, where 0 is the highest priority)
 */
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
    uint8_t irq_prio_reg_x = IRQNumber / 4;
    uint8_t irq_prio_reg_x_offest = IRQNumber % 4 ;
    uint8_t shift_amount = (8 * irq_prio_reg_x_offest) + (8 - NO_PR_BITS_IMPLEMENTED); //NO_PR_BITS_IMPLEMENTED is defined in the CMSIS header file for the specific microcontroller, it indicates the number of bits implemented for interrupt priority in the NVIC. For STM32F401xx, it is 4.
    *(NVIC_PR_BASE_ADDR + (irq_prio_reg_x)) |= (IRQPriority << shift_amount);
}


/**
 * @brief  This function handles the interrupt for a specific GPIO pin.
 * 
 * @param PinNumber   The number of the GPIO pin for which the interrupt occurred (0-15)
 */
void GPIO_IRQHandling(uint8_t PinNumber)
{
    //1. Clear the EXTI PR (Pending Register) corresponding to the pin number
    if(EXTI->PR & (1<<PinNumber))
    {
        //Clear the pending bit by writing 1 to it
        EXTI->PR |= (1<<PinNumber);
    }
}

