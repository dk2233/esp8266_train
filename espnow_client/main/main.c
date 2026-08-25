
#include <stdio.h>
#include "esp_wifi_now.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "portmacro.h"
#include <esp_spi_flash.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include "esp_now.h"

const char * TAG = "MAIN APP";
#define ONBOARD_LED_GPIO   2  // GPIO2, czyli pin D4 na płytce
/*
gpio used by LED 2

in ESP8266 + NodeMCU it is blue led that exists on the board
*/
#define GPIO_LED  GPIO_NUM_2
/*
additional LED connected to D1 port
*/
#define GPIO_LED2  GPIO_NUM_5

#define GPIO_ON     (1u)

#define GPIO_OFF     (0u)
                              //
static void controlLed(void *arg)
{
    static uint32_t ledState = 0;

    while(1) {
        if (GPIO_ON == ledState )
        {
            ledState = GPIO_OFF;

        }
        else
        {
            ledState = GPIO_ON;
        }
        gpio_set_level(ONBOARD_LED_GPIO, ledState);
        ESP_LOGI(TAG, "Led state %d\n", ledState);
        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }

}

static void controlLed2(void *arg)
{
    static uint32_t ledState = 0;

    while(1) {
        if (GPIO_ON == ledState )
        {
            ledState = GPIO_OFF;

        }
        else
        {
            ledState = GPIO_ON;
        }
        gpio_set_level(GPIO_LED2, ledState);
        ESP_LOGI(TAG, "Led2 state %d\n", ledState);
        vTaskDelay(2500 / portTICK_PERIOD_MS);
    }
}

static void chip_info(void )
{
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP8266 chip with %d CPU cores, WiFi, ",
            chip_info.cores);

    printf("silicon revision %d, ", chip_info.revision);

    printf("if 0 - esp8266 %d\n",chip_info.model);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");


}

static void task_info(void *arg)
{
    while(1)
    {
        chip_info();
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}

void app_main()
{
    gpio_set_direction(ONBOARD_LED_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_LED2, GPIO_MODE_OUTPUT);
    /* Print 
     */
    BaseType_t xReturned = xTaskCreate(
                    controlLed,       /* Function that implements the task. */
                    "Task_Led",          /* Text name for the task. */
                    1024,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    tskIDLE_PRIORITY,/* Priority at which the task is created. */
                    NULL );      /* Used to pass out the created task's handle. */

    if( xReturned != pdPASS )
    {
        ESP_LOGE(TAG, "Error creating first task \n");

    }
     xReturned = xTaskCreate(
                    task_info,       /* Function that implements the task. */
                    "Task_Chip_Info",          /* Text name for the task. */
                    1024,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    tskIDLE_PRIORITY,/* Priority at which the task is created. */
                    NULL );      /* Used to pass out the created task's handle. */
    
     xReturned = xTaskCreate(
                    controlLed2,       /* Function that implements the task. */
                    "Task_Led",          /* Text name for the task. */
                    1024,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    tskIDLE_PRIORITY,/* Priority at which the task is created. */
                    NULL );      /* Used to pass out the created task's handle. */
     init_esp_now();
}
