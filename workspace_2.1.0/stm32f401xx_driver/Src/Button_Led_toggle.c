/*
 * Button_Led_toggle.c
 *
 *  Created on: 17-May-2026
 *      Author: nirmal.aryal
 */

#include <stdint.h>
#include "stm32f401xx.h"
#include "stm32f401xx_gpio_driver.h"

void delay ()
{
    for(int i=0 ; i< 200000; i++);
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
    HandleGPIOButton.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_INPUT;
    HandleGPIOButton.GPIO_PinConfig.GPIO_PinSpeed=GPIO_OP_SPEED_VERY_HIGH;
    HandleGPIOButton.GPIO_PinConfig.GPIO_PinPuPdControl=GPIO_NO_PU_PD;

    GPIO_PeriClockControl(GPIOA,ENABLE);
    GPIO_PeriClockControl(GPIOC,ENABLE);

    GPIO_Init(&HandleGPIOLED);
    GPIO_Init(&HandleGPIOButton);

    while(1)
    {
        if(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13)==0)//Button is pressed, active low because of Pull-up in NUCLEO F401RE
        {        
            delay();
            GPIO_ToggleOutputPin(GPIOA,GPIO_PIN_NO_5);
        }
    }

}
