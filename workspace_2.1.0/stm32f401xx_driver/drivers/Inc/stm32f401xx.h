/*
 * stm32f401xx.h
 *
 *  Created on: 16-May-2026
 *      Author: nirmal.aryal
 */

#ifndef INC_STM32F401XX_H_
#define INC_STM32F401XX_H_

#include <stdint.h>

#define __vo volatile
/*
Base addresses of Memory
*/

/**************************************************** PROCESSOR SPECIFIC ADDRESS DEFINITION ****************************************************/

/**
 * AMM Coretx Mx Processor NVIC ISERx Register Address
 */

#define NVIC_ISER0       ((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1       ((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2       ((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3       ((__vo uint32_t*)0xE000E10C)

/**
 * AMM Coretx Mx Processor NVIC ICER  Register Address
 */

#define NVIC_ICER0       ((__vo uint32_t*)0XE000E180)
#define NVIC_ICER1       ((__vo uint32_t*)0XE000E184)
#define NVIC_ICER2       ((__vo uint32_t*)0XE000E188)
#define NVIC_ICER3       ((__vo uint32_t*)0XE000E18C)

/**
 * ARM Coretx Mx Processor Priority Register Address Calculation
 */
#define NVIC_PR_BASE_ADDR       ((__vo uint32_t*)0xE000E400)

#define NO_PR_BITS_IMPLEMENTED          4

#define FLASH_BASEADDR          0x08000000U
#define SRAM1_BASEADDR          0x20000000U
//#define SRAM2_BASEADDR        Do not have SRAM2 in NUCLEOF01RE
#define ROM_BASEADDR            0x1FFF0000U
#define SARM					SRAM1_BASEADDR


/*
Base address of APBx and AHBx Bus Interface
*/

#define PERIPH_BASE                 0x40000000U
#define APB1_PERIPH_BASEADDR        0x40000000U
#define APB2_PERIPH_BASEADDR        0x40010000U
#define AHB1_PERIPH_BASEADDR        0x40020000U
#define AHB2_PERIPH_BASEADDR        0x50000000U

/*
Base addresses of AHB1 Peripherals
*/

#define GPIOA_BASEADDR             (AHB1_PERIPH_BASEADDR + 0x0000U)
#define GPIOB_BASEADDR             (AHB1_PERIPH_BASEADDR + 0x0400U)
#define GPIOC_BASEADDR             (AHB1_PERIPH_BASEADDR + 0x0800U)
#define GPIOD_BASEADDR             (AHB1_PERIPH_BASEADDR + 0x0C00U)
#define GPIOE_BASEADDR             (AHB1_PERIPH_BASEADDR + 0x1000U)
#define GPIOH_BASEADDR             (AHB1_PERIPH_BASEADDR + 0x1C00U)
#define CRC_BASEADDR               (AHB1_PERIPH_BASEADDR + 0x3000U)
#define RCC_BASEADDR               (AHB1_PERIPH_BASEADDR + 0x3800U)
#define FLASH_INTERFACE_BASEADDR   (AHB1_PERIPH_BASEADDR + 0x3C00U)
#define DMA1_BASEADDR              (AHB1_PERIPH_BASEADDR + 0x6000U)
#define DMA2_BASEADDR              (AHB1_PERIPH_BASEADDR + 0x6400U)

/*
Base addresses of APB1 Peripherals
*/

#define TIM2_BASEADDR              (APB1_PERIPH_BASEADDR + 0x0000U)
#define TIM3_BASEADDR              (APB1_PERIPH_BASEADDR + 0x0400U)
#define TIM4_BASEADDR              (APB1_PERIPH_BASEADDR + 0x0800U)
#define TIM5_BASEaddr              (APB1_PERIPH_BASEADDR + 0x0C00U)

#define RTC_BASEADDR               (APB1_PERIPH_BASEADDR + 0x2800U)

#define I2C1_BASEADDR              (APB1_PERIPH_BASEADDR + 0x5400U)
#define I2C2_BASEADDR              (APB1_PERIPH_BASEADDR + 0x5800U)
#define I2C3_BASEADDR              (APB1_PERIPH_BASEADDR + 0x5C00U)

#define SPI2_BASEADDR              (APB1_PERIPH_BASEADDR + 0x3800U)
#define SPI3_BASEADDR              (APB1_PERIPH_BASEADDR + 0x3C00U)

#define USART2_BASEADDR            (APB1_PERIPH_BASEADDR + 0x4400U)

/*
Base addresses of APB2 Peripherals
*/  
#define EXTI_BASEADDR              (APB2_PERIPH_BASEADDR + 0x3C00U)
#define SYSCFG_BASEADDR            (APB2_PERIPH_BASEADDR + 0x3800U) 

#define SPI1_BASEADDR              (APB2_PERIPH_BASEADDR + 0x3000U)
#define SPI4_BASEADDR              (APB2_PERIPH_BASEADDR + 0x3400U)

#define USART1_BASEADDR            (APB2_PERIPH_BASEADDR + 0x1000U)
#define USART6_BASEADDR            (APB2_PERIPH_BASEADDR + 0x1400U)

#define ADC1_BASEADDR              (APB2_PERIPH_BASEADDR + 0x2000U)


/**************************************************** PERIPHERAL REGISTER DEFINITION STRUCTURE ****************************************************/
/*
* Note: Registers of a peripheral are specific to MCU
* e.g: Number of Registers of SPI peripheral of STM32F4x family of MCUs may be different(more or less, ompared to number of registers of SPI peripheral of STM32Lx or STM32F0x family of MCUs
* Please check your Device RM
*/

/*
* Peripheral register definition structure for GPIO
*/
typedef struct
{
    __vo uint32_t MODER;         /* GPIO port mode register                Address offset: 0x00      */
    __vo uint32_t OTYPER;        /* GPIO port output type register         Address offset: 0x04      */
    __vo uint32_t OSPEEDR;       /* GPIO port output speed register        Address offset: 0x08      */
    __vo uint32_t PUPDR;         /* GPIO port pull-up/pull-down register   Address offset: 0x0C      */
    __vo uint32_t IDR;           /* GPIO port input data register          Address offset: 0x10      */
    __vo uint32_t ODR;           /* GPIO port output data register         Address offset: 0x14      */
    __vo uint32_t BSRRL;         /* GPIO port bit set/reset low register   Address offset: 0x18      */
    __vo uint32_t LCKR;          /* GPIO port configuration lock register  Address offset: 0x1C      */
    __vo uint32_t AFR[2];        /* GPIO port input data register          Address offset: 0x20-24   */
} GPIO_RegDef_t;

/**
 * Peripheral register definition structure for SPI
*/

typedef struct{
    __vo uint32_t CR1;               /* SPI control register                 Address offset: 0x00       */
    __vo uint32_t CR2;               /* SPI control register                 Address offset: 0x04       */
    __vo uint32_t SR;                   /* SPI status register                  Address offset: 0x08      */       
    __vo uint32_t DR;                   /* SPI data register                    Address offset: 0x0C      */
    __vo uint32_t CRCPR;                /* SPI CRC polynomial register          Address offset: 0x10      */
    __vo uint32_t RXCRCR;               /* SPI RX CRC register                  Address offset: 0x04      */
    __vo uint32_t TXCRCR;               /* SPI TX CRC register                  Address offset: 0x18      */
    __vo uint32_t I2SCFGR;              /* SPI_I2S configuration register       Address offset: 0x1C      */
    __vo uint32_t I2SPR;                /* SPI_I2S prescaler register           Address offset: 0x20      */

}SPI_RegDef_t;

/*
* Peripheral register definition structure for RCC
*/
typedef struct
{
    __vo uint32_t CR;           /* RCC clock control register                                        Address offset: 0x00      */
    __vo uint32_t PLLCFGR;      /* RCC PLL configuration register                                    Address offset: 0x04      */
    __vo uint32_t CFGR;         /* GRCC clock configuration register                                 Address offset: 0x08      */
    __vo uint32_t CIR;          /* RCC clock interrupt register                                      Address offset: 0x0C      */
    __vo uint32_t AHB1RSTR;     /* RCC AHB1 peripheral reset register                                Address offset: 0x10      */
    __vo uint32_t AHB2RSTR;     /* RCC AHB2 peripheral reset register                                Address offset: 0x14      */
    uint32_t RESERVED0[2];      /* Reserved                                                          Address offset: 0x18-1C   */
    __vo uint32_t APB1RSTR;     /* RCC APB1 peripheral reset register                                Address offset: 0x20      */
    __vo uint32_t APB2RSTR;     /* RCC APB2 peripheral reset register                                Address offset: 0x24      */
    uint32_t RESERVED1[2];      /* Reserved                                                          Address offset: 0x28-2C   */
    __vo uint32_t AHB1ENR;      /* RCC AHB1 peripheral clock enable register                         Address offset: 0x30      */
    __vo uint32_t AHB2ENR;      /* RCC AHB2 peripheral clock enable register                         Address offset: 0x34      */
    uint32_t RESERVED3[2];      /* Reserved                                                          Address offset: 0x38-3C   */ 
    __vo uint32_t APB1ENR;      /* RCC APB1 peripheral clock enable register                         Address offset: 0x40      */
    __vo uint32_t APB2ENR;      /* RCC APB2 peripheral clock enable register                         Address offset: 0x44      */
    uint32_t RESERVED4[2];      /* Reserved                                                          Address offset: 0x48-4C   */
    __vo uint32_t AHB1LPENR;    /* RCC AHB1 peripheral clock enable in low power mode register       Address offset: 0x50      */
    __vo uint32_t AHB2LPENR;    /* RCC AHB2 peripheral clock enable in low power mode register       Address offset: 0x54      */
    uint32_t RESERVED5[2];      /* Reserved                                                          Address offset: 0x58-5C   */
    __vo uint32_t APB1LPENR;    /* RCC APB1 peripheral clock enable in low power mode register       Address offset: 0x60      */
    __vo uint32_t APB2LPENR;    /* RCC APB2 peripheral clock enabled in low power mode register      Address offset: 0x64      */
    uint32_t RESERVED6[2];      /* Reserved                                                          Address offset: 0x68-6C   */
    __vo uint32_t BDCR;         /* RCC Backup domain control register                                Address offset: 0x70      */
    __vo uint32_t CSR;          /* RCC clock control & status register                               Address offset: 0x74      */
    uint32_t RESERVED7[2];      /* Reserved                                                          Address offset: 0x78-7C   */
    __vo uint32_t SSCGR;        /* RCC spread spectrum clock generation register                     Address offset: 0x80      */
    __vo uint32_t PLLI2SCFGR;   /* RCC PLLI2S configuration register                                 Address offset: 0x84      */
    uint32_t RESERVED8;         /* Reserved                                                          Address offset: 0x88      */
    __vo uint32_t DCKCFGR;      /* RCC Dedicated Clocks Configuration Register                       Address offset: 0x8C      */
      
} RCC_RegDef_t;

/*
* Peripheral register definition structure for EXTI
*/

typedef struct 
{
uint32_t IMR;          /* EXTI Interrupt mask register                            Address offset: 0x00      */
uint32_t EMR;          /* EXTI Event mask register                                Address offset: 0x04      */
uint32_t RTSR;         /* EXTI Rising trigger selection register                  Address offset: 0x08      */
uint32_t FTSR;         /* EXTI Falling trigger selection register                 Address offset: 0x0C      */
uint32_t SWIER;        /* EXTI Software interrupt event register                  Address offset: 0x10      */
uint32_t PR;           /* EXTI Pending register                                   Address offset: 0x14      */
} EXTI_RegDef_t;

/**
 * Peripheral register definition structure for SYSCFG
 */

typedef struct 
{
    uint32_t MEMRMP;  /* SYSCFG memory remap register                              Address offset : 0x00          */
    uint32_t PMC;     /* SYSCFG peripheral mode configuration register             Address offset : 0x04          */
    uint32_t EXTICR[4]; /* SYSCFG external interrupt configuration register 1      Address offset : 0x08 - 0x14   */
    uint32_t RESERVED[2]; /*RESERVED                                               Address offset : 0x18 - 0x1C   */
    uint32_t CMPCR;   /* SYSCFG peripheral mode configuration register             Address offset : 0x20          */
}SYSCFG_RegDef_t;


/*
* Peripheral definitions (Peripheral base addresses typecasted to xxx_RegDef_t)
*/
#define GPIOA ((GPIO_RegDef_t *) GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t *) GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t *) GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t *) GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t *) GPIOE_BASEADDR)
#define GPIOH ((GPIO_RegDef_t *) GPIOH_BASEADDR)
// GPIO_RegDef_t *pGPIOA = GPIOA; /* This is how we can use this structure pointer. We can also directly use GPIOA->MODER to access the MODER register of GPIOA peripheral */

#define RCC ((RCC_RegDef_t *) RCC_BASEADDR)
#define EXTI ((EXTI_RegDef_t *) EXTI_BASEADDR)
#define SYSCFG ((SYSCFG_RegDef_t *) SYSCFG_BASEADDR)

#define SPI1 ((SPI_RegDef_t *) SPI1_BASEADDR)
#define SPI2 ((SPI_RegDef_t *) SPI2_BASEADDR)
#define SPI3 ((SPI_RegDef_t *) SPI3_BASEADDR)
#define SPI4 ((SPI_RegDef_t *) SPI4_BASEADDR)


/* 
* Clock Enable Macro for GPIOx Peripheral
*/

#define GPIOA_PCLK_EN() (RCC->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN() (RCC->AHB1ENR |= (1<<4))
#define GPIOH_PCLK_EN() (RCC->AHB1ENR |= (1<<7))


/* 
* Clock Enable Macro for I2Cx Peripheral
*/

#define I2C1_PCLK_EN() (RCC->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN() (RCC->APB1ENR |= (1<<22))
#define I2C3_PCLK_EN() (RCC->APB1ENR |= (1<<23))

/* 
* Clock Enable Macro for SPIx Peripheral
*/

#define SPI1_PCLK_EN() (RCC->APB2ENR |= (1<<12)) 
#define SPI2_PCLK_EN() (RCC->APB1ENR |= (1<<14)) 
#define SPI3_PCLK_EN() (RCC->APB1ENR |= (1<<15)) 
#define SPI4_PCLK_EN() (RCC->APB2ENR |= (1<<13)) 

/* 
* Clock Enable Macro for UASRT Peripheral
*/

#define USART1_PCLK_EN() (RCC->APB2ENR |= (1<<4)) 
#define USART2_PCLK_EN() (RCC->APB1ENR |= (1<<17)) 
#define USART6_PCLK_EN() (RCC->APB2ENR |= (1<<5)) 

/* 
* Clock Enable Macro for SYSCFG Peripheral
*/

#define SYSCFG_PCLK_EN() (RCC->APB2ENR |= (1<<14)) 


/* 
* Clock Disable Macro for GPIOx Peripheral
*/

#define GPIOA_PCLK_DI() (RCC->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI() (RCC->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI() (RCC->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI() (RCC->AHB1ENR &= ~(1<<4))
#define GPIOH_PCLK_DI() (RCC->AHB1ENR &= ~(1<<7))

/* 
* Clock Disable Macro for I2Cx Peripheral
*/

#define I2C1_PCLK_DI() (RCC->APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI() (RCC->APB1ENR &= ~(1<<22))
#define I2C3_PCLK_DI() (RCC->APB1ENR &= ~(1<<23))

/* 
* Clock Disable Macro for SPIx Peripheral
*/

#define SPI1_PCLK_DI() (RCC->APB2ENR &= ~(1<<12)) 
#define SPI2_PCLK_DI() (RCC->APB1ENR &= ~(1<<14)) 
#define SPI3_PCLK_DI() (RCC->APB1ENR &= ~(1<<15)) 
#define SPI4_PCLK_DI() (RCC->APB2ENR &= ~(1<<13)) 

/* 
* Clock Disable Macro for UASRT Peripheral
*/

#define USART1_PCLK_DI() (RCC->APB2ENR &= ~(1<<4)) 
#define USART2_PCLK_DI() (RCC->APB1ENR &= ~(1<<17)) 
#define USART6_PCLK_DI() (RCC->APB2ENR &= ~(1<<5)) 

/* 
* Clock Disable Macro for SYSCFG Peripheral
*/

#define SYSCFG_PCLK_EDI() (RCC->APB2ENR &= ~(1<<14)) 


/*
* Macro to reset GPIOx peripheral  
*/
#define GPIOA_REG_RESET()    do{ (RCC->AHB1RSTR |= (1<<0)); (RCC->AHB1RSTR &= ~(1<<0)); } while(0)
#define GPIOB_REG_RESET()    do{ (RCC->AHB1RSTR |= (1<<1)); (RCC->AHB1RSTR &= ~(1<<1)); } while(0)
#define GPIOC_REG_RESET()    do{ (RCC->AHB1RSTR |= (1<<2)); (RCC->AHB1RSTR &= ~(1<<2)); } while(0)
#define GPIOD_REG_RESET()    do{ (RCC->AHB1RSTR |= (1<<3)); (RCC->AHB1RSTR &= ~(1<<3)); } while(0)
#define GPIOE_REG_RESET()    do{ (RCC->AHB1RSTR |= (1<<4)); (RCC->AHB1RSTR &= ~(1<<4)); } while(0)
#define GPIOH_REG_RESET()    do{ (RCC->AHB1RSTR |= (1<<7)); (RCC->AHB1RSTR &= ~(1<<7)); } while(0)

/*
* MACRO to get 
*/

#define GPIO_BASEADDR_TO_CODE(x)  ((x == GPIOA) ? 0 : \
                                  (x == GPIOB) ? 1 : \
                                  (x == GPIOC) ? 2 : \
                                  (x == GPIOD) ? 3 : \
                                  (x == GPIOE) ? 4 : \
                                  (x == GPIOH) ? 7 : 0) 

/**
 * IRQ Macros for EXTI Lines 
 */

#define IRQ_NO_EXTI0          6
#define IRQ_NO_EXTI1          7
#define IRQ_NO_EXTI2          8
#define IRQ_NO_EXTI3          9
#define IRQ_NO_EXTI4          10
#define IRQ_NO_EXTI9_5        23
#define IRQ_NO_EXTI15_10      40
#define IRQ_NO_EXTI16         1
#define IRQ_NO_EXTI17         41
#define IRQ_NO_EXTI18         42 
#define IRQ_NO_EXTI21         2 
#define IRQ_NO_EXTI22         3



/*
* Some Generic Macros
*/

#define ENABLE                  1
#define DISABLE                 0
#define SET                     ENABLE
#define RESET                   DISABLE
#define GPIO_PIN_SET            SET
#define GPIO_PIN_RESET          RESET

#endif /* INC_STM32F401XX_H_ */