#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h" 
#include "freertos/task.h"

#define GPIO_BASE_ADDR        0x60004000
#define GPIO_OUT_REG         (GPIO_BASE_ADDR+0x004)
#define GPIO_OUT_W1TS_REG    (GPIO_BASE_ADDR+0x0008)
#define GPIO_OUT_W1TC_REG    (GPIO_BASE_ADDR+0x000C)
#define GPIO_ENABLE_REG      (GPIO_BASE_ADDR+0x0020)

#define IO_MUX_GPIO_BASE      0x60009000
#define IO_MUX_GPIO5_REG     (IO_MUX_GPIO_BASE+0x18)

#define DELAY_MS 3000


void app_main(void)
{   
    volatile uint32_t* gpio_enable_reg = (volatile uint32_t*) GPIO_ENABLE_REG;
    volatile uint32_t* gpio_out_reg = (volatile uint32_t*) GPIO_OUT_REG;
    volatile uint32_t* gpio_out_w1ts_reg = (volatile uint32_t*) GPIO_OUT_W1TS_REG;
    volatile uint32_t* gpio_out_w1tc_reg = (volatile uint32_t*) GPIO_OUT_W1TC_REG;

    volatile uint32_t* io_mux_gpio5_reg = (volatile uint32_t*) IO_MUX_GPIO5_REG;

    // enable gpio
    *gpio_enable_reg = (1<<5);
    // ESP32 PIN CAN BE USED FOR DIFFERENT PURPOSES, SETUP PIN AS GPIO
    *io_mux_gpio5_reg |= 1<<12;

    while (1){
        // set up value to 1 on 5th gpio - power on
        *gpio_out_w1ts_reg = (1<<5); //1
        printf("1. %lu - gpio out reg value\n", *gpio_out_reg);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
        // set up value to 0 on 5th gpio - power off
        *gpio_out_w1tc_reg = (1<<5); //0
        printf("2. %lu - gpio out reg value\n", *gpio_out_reg);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));

    }
}
