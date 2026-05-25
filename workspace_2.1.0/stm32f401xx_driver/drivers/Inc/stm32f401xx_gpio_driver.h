/*
 * stm32f401xx_gpio_driver.h
 *
 *  Created on: 16-May-2026
 *      Author: nirmal.aryal
 */

#ifndef INC_STM32F401XX_GPIO_DRIVER_H_
#define INC_STM32F401XX_GPIO_DRIVER_H_

#include "stm32f401xx.h"

/*
* This is a configuration structure for GPIO Pin
i.e. Configurable members for a GPIO from Application layer
*/
typedef struct
{
    uint8_t GPIO_PinNumber; /* possible values from @GPIO_PIN_NO_XXX */
    uint8_t GPIO_PinMode; /* possible values from @GPIO_MODE_XXX */
    uint8_t GPIO_PinSpeed; /* possible values from @GPIO_SPEED_XXX */
    uint8_t GPIO_PinPuPdControl; /* possible values from @GPIO_PUPD_XXX */
    uint8_t GPIO_PinOPType; /* possible values from @GPIO_OP_TYPE_XXX */
    uint8_t GPIO_PinAltFunMode; /* possible values from @GPIO_ALT_FUN_XXX */
} GPIO_PinConfig_t;

/*
* Handle structure for a GPIO 
*/
typedef struct{
    GPIO_RegDef_t* pGPIOx; /* This will hold the Base Address of GPIO port to which the pin belongs */
    GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;

/**
 * @GPIO_PIN_NO_XXX
 * GPIO Pin no macro
 */
#define GPIO_PIN_NO_0       0
#define GPIO_PIN_NO_1       1
#define GPIO_PIN_NO_2       2
#define GPIO_PIN_NO_3       3
#define GPIO_PIN_NO_4       4
#define GPIO_PIN_NO_5       5
#define GPIO_PIN_NO_6       6
#define GPIO_PIN_NO_7       7
#define GPIO_PIN_NO_8       8
#define GPIO_PIN_NO_9       9
#define GPIO_PIN_NO_10      10
#define GPIO_PIN_NO_11      11
#define GPIO_PIN_NO_12      12
#define GPIO_PIN_NO_13      13
#define GPIO_PIN_NO_14      14
#define GPIO_PIN_NO_15      15

/**
* @GPIO_MODE_XXX
* GPIO Mode Macros
*/
#define GPIO_MODE_INPUT                  0
#define GPIO_MODE_OUTPUT                 1
#define GPIO_MODE_ALTRNATE_FUNCTION      2
#define GPIO_MODE_ANALOG                 3
#define GPIO_MODE_INTERRUPT_FALLING_EDGE     4 //Not in Manual, made custom 
#define GPIO_MODE_INTERRUPT_RISING_EDGE      5 //Not in Manual, made custom 
#define GPIO_MODE_INTERRUPT_RE_FE_TRIGGER    6 //Not in Manual, made custom  

/**
 * @GPIO_OP_TYPE_XXX
 * GPIO Pin Possible Output Type
 */

#define GPIO_OP_TYPE_PUSH_PULL           0
#define GPIO_OP_TYPE_OPEN_DRAIN          1

/**
 * @GPIO_SPEED_XXX
 * GPIO Output Speeds
 */

#define GPIO_OP_SPEED_LOW               0
#define GPIO_OP_SPEED_MEDIUM            1
#define GPIO_OP_SPEED_HIGH              2
#define GPIO_OP_SPEED_VERY_HIGH         3

/**
 * @GPIO_PUPD_XXX
 * GPIO Pull-up Pull-down configuration macro
 */

#define GPIO_NO_PU_PD         0
#define GPIO_PIN_PULL_UP      1
#define GPIO_PIN_PULL_DOWN    2    

/**
 * @brief GPIO Peripheral Clock Setup
 */

void GPIO_PeriClockControl(GPIO_RegDef_t* pGPIOx, uint8_t EnorDi);

/* 
* @brief GPIO Init and DeInit
*/

void GPIO_Init(GPIO_Handle_t* pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t* pGPIOx);

/*
* GPIO Read and Write
*/

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t* pGPIOx);
void GPIO_WritetoOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WritetoOutputPort(GPIO_RegDef_t* pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t* pGPIOx, uint8_t PinNumber);

/*
* IRQ Config and IRQ Handling
*/

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t IRQEnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);
#endif 
