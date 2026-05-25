/*
 * BUTTON_LED_TOOGLE_VIA_INTERRUPT.c
 *
 *  Created on: 21-May-2026
 *      Author: nirmal.aryal
 */

#include <stdint.h>
#include "stm32f401xx.h"
#include "stm32f401xx_gpio_driver.h"

void delay ()
{
    for(int i=0 ; i< 10000; i++);
}

int main (void)
{
    GPIO_Handle_t HandleGPIOLED;
    HandleGPIOLED.pGPIOx=GPIOA;

    HandleGPIOLED.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_5;
    HandleGPIOLED.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_OUTPUT;
    HandleGPIOLED.GPIO_PinConfig.GPIO_PinSpeed=GPIO_OP_SPEED_VERY_HIGH;
    HandleGPIOLED.GPIO_PinConfig.GPIO_PinOPType=GPIO_OP_TYPE_PUSH_PULL;
    HandleGPIOLED.GPIO_PinConfig.GPIO_PinPuPdControl=GPIO_PIN_PULL_UP;

    GPIO_Handle_t HandleGPIOButton;
    HandleGPIOButton.pGPIOx=GPIOC;
    HandleGPIOButton.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_13;
    HandleGPIOButton.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_INTERRUPT_FALLING_EDGE;
    HandleGPIOButton.GPIO_PinConfig.GPIO_PinSpeed=GPIO_OP_SPEED_VERY_HIGH;
    HandleGPIOButton.GPIO_PinConfig.GPIO_PinPuPdControl=GPIO_PIN_PULL_UP;

    GPIO_PeriClockControl(GPIOA,ENABLE);
    GPIO_PeriClockControl(GPIOC,ENABLE);

    GPIO_Init(&HandleGPIOLED);
    GPIO_Init(&HandleGPIOButton);

    GPIO_IRQInterruptConfig(IRQ_NO_EXTI15_10, ENABLE);
    GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, 15);
    while(1);
}

volatile uint32_t debounce_tick = 0;
// ...existing code...

void EXTI15_10_IRQHandler(void)
{
    for(volatile int i = 0; i < 500000; i++); // debounce wait
    GPIO_IRQHandling(GPIO_PIN_NO_13);
    GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_5);
}
