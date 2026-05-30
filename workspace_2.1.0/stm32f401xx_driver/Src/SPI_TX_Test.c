/*
 * SPI_TX_Test.c
 *
 *  Created on: 28-May-2026
 *      Author: nirmal.aryal
 */

#include "stm32f401xx.h"
#include "stm32f401xx_spi_driver.h"
#include "stm32f401xx_gpio_driver.h"
#include <string.h>

//PB15 -----> SPI2 MOSI 
//PB14 -----> SPI2 MISO 
//PB13 -----> SPI2 SCLK
//PB12 -----> SPI2 NSS 

void delay()
{
  for(int i =0 ; i<500000; i++){}
}

void SPI_GPIOInit(void)
{
    GPIO_Handle_t Handle_SPI_GPIO;

    Handle_SPI_GPIO.pGPIOx=GPIOB;

    Handle_SPI_GPIO.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_ALTRNATE_FUNCTION;
    Handle_SPI_GPIO.GPIO_PinConfig.GPIO_PinAltFunMode=5;
    Handle_SPI_GPIO.GPIO_PinConfig.GPIO_PinSpeed=GPIO_OP_SPEED_VERY_HIGH;
    Handle_SPI_GPIO.GPIO_PinConfig.GPIO_PinOPType=GPIO_OP_TYPE_PUSH_PULL;
    Handle_SPI_GPIO.GPIO_PinConfig.GPIO_PinPuPdControl=GPIO_NO_PU_PD;

    GPIO_PeriClockControl(GPIOB,ENABLE);
    //MOSI
    Handle_SPI_GPIO.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_15;
    GPIO_Init(&Handle_SPI_GPIO);
    
    //MISO
    Handle_SPI_GPIO.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_14;
    GPIO_Init(&Handle_SPI_GPIO);
    
    //SCLK  
    Handle_SPI_GPIO.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_13;
    GPIO_Init(&Handle_SPI_GPIO);
    
    //NSS  
    Handle_SPI_GPIO.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_12;
    GPIO_Init(&Handle_SPI_GPIO);
    return;
}

void SPI_ButtonInit(void)
{
    GPIO_Handle_t HandleGPIOButton;
    HandleGPIOButton.pGPIOx=GPIOC;
    HandleGPIOButton.GPIO_PinConfig.GPIO_PinNumber=GPIO_PIN_NO_13;
    HandleGPIOButton.GPIO_PinConfig.GPIO_PinMode=GPIO_MODE_INPUT;
    HandleGPIOButton.GPIO_PinConfig.GPIO_PinSpeed=GPIO_OP_SPEED_VERY_HIGH;
    HandleGPIOButton.GPIO_PinConfig.GPIO_PinPuPdControl=GPIO_NO_PU_PD;
    GPIO_PeriClockControl(GPIOC,ENABLE);
    GPIO_Init(&HandleGPIOButton);
}

int main(void)
{
  SPI_GPIOInit();
  SPI_ButtonInit();
  SPI_Handle_t SPIHandle;

  SPIHandle.pSPIx=SPI2;
  SPIHandle.SPIConfig.SPI_DeviceMode=SPI_DEVICE_MODE_MASTER;
  SPIHandle.SPIConfig.SPI_DFF=SPI_DFF_8_BIT_FORMAT;
  SPIHandle.SPIConfig.SPI_BusConfig=SPI_BUS_CONFIG_FD;
  SPIHandle.SPIConfig.SPI_SCLKSpeed=SPI_SCLK_SPEED_DIV32;

  SPIHandle.SPIConfig.SPI_SSM=SPI_SSM_DI; //Hardware slave management enabled for NSS pin

  SPI_Init(&SPIHandle);
  SPI_SSOEConfig(SPI2,ENABLE); //SSOE=1: NSS output enabled (driven low when SPE=1)
  char buffer[]="Hello World";

  while(1)
  {
      // Wait for button press (PC13 goes LOW on Nucleo)
      while(GPIO_ReadFromInputPin(GPIOC,GPIO_PIN_NO_13));
      delay(); // Debounce
      SPI_PeripheralControl(SPI2,ENABLE);
      SPI_SendData(SPI2,(uint8_t*)buffer,strlen(buffer));
      while (SPI_GetSRFlagStatus(SPI2,SPI_BSY_FLAG_MASK));
      SPI_PeripheralControl(SPI2,DISABLE);
  }
}


/*
ESP 32 SPI Slave Code (for reference, not part of STM32 codebase):
*/

/*
 * ESP32 SPI Slave - Receives data from STM32F401RE SPI2 Master
 * 
 * Wiring (both boards are 3.3V - direct connection):
 * 
 *   STM32F401 (Master)     ESP32 (Slave)
 *   ------------------     -------------
 *   PB15 (MOSI)       -->  GPIO13
 *   PB14 (MISO)       <--  GPIO12
 *   PB13 (SCLK)       -->  GPIO14
 *   PB12 (NSS)        -->  GPIO15
 *   GND               ---  GND
 */

/*

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_slave.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define TAG "SPI_SLAVE"

#define GPIO_MOSI   13
#define GPIO_MISO   12
#define GPIO_SCLK   14
#define GPIO_CS     15

#define BUF_SIZE    64

uint8_t rxBuffer[BUF_SIZE];
uint8_t txBuffer[BUF_SIZE];

void app_main(void)
{
    spi_bus_config_t buscfg = {
        .mosi_io_num = GPIO_MOSI,
        .miso_io_num = GPIO_MISO,
        .sclk_io_num = GPIO_SCLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = BUF_SIZE,
    };

    spi_slave_interface_config_t slvcfg = {
        .mode = 0,
        .spics_io_num = GPIO_CS,
        .queue_size = 6,
        .flags = 0,
    };

    gpio_set_pull_mode(GPIO_MOSI, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(GPIO_SCLK, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(GPIO_CS, GPIO_PULLUP_ONLY);

    esp_err_t ret = spi_slave_initialize(SPI2_HOST, &buscfg, &slvcfg, SPI_DMA_DISABLED);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "SPI slave init failed: %s", esp_err_to_name(ret));
        return;
    }

    ESP_LOGI(TAG, "========================================");
    ESP_LOGI(TAG, "ESP32 SPI Slave Ready!");
    ESP_LOGI(TAG, "Waiting for data from STM32...");
    ESP_LOGI(TAG, "========================================");

    while (1) {
        memset(rxBuffer, 0, BUF_SIZE);

        spi_slave_transaction_t t = {
            .length = BUF_SIZE * 8,
            .rx_buffer = rxBuffer,
            .tx_buffer = txBuffer,
        };

        ret = spi_slave_transmit(SPI2_HOST, &t, portMAX_DELAY);

        if (ret == ESP_OK && t.trans_len > 0) {
            int byteCount = (t.trans_len + 7) / 8;
            ESP_LOGI(TAG, "Received %d bits (%d bytes)", (int)t.trans_len, byteCount);
            ESP_LOGI(TAG, "Data: %s", (char*)rxBuffer);

            printf("Hex: ");
            for (int i = 0; i < byteCount; i++) {
                printf("0x%02X ", rxBuffer[i]);
            }
            printf("\n\n");
        }
    }
}

*/