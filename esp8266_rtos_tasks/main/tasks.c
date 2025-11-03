#include <stdio.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdint.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include <help_utils.h>
#include <esp_http_server.h>
#include <wifi_handle.h>
#include <ports_conf.h>
#include <http_handle.h>


const char *TAG = "tasks_app";



static TasksConfig_t TasksConfig[3] = {
    {.TaskName = "hello_task", .Period=1000/portTICK_PERIOD_MS},
    {.TaskName = "led_task", .Period = 1200/portTICK_PERIOD_MS},
    {.TaskName = "led_task2", .Period = 500/portTICK_PERIOD_MS},
};

static void writeHello(void *arg);
static void controlLed(void *arg);
static void task_led2(void *arg);


static void writeHello(void *arg)
{
    static uint32_t i = 0;
    while (1)
    {
        printf("Hello times %d\n", i++);
            fflush(stdout);
        vTaskDelay(TasksConfig[0].Period);
    }
}

static void controlLed(void *arg)
{
    static uint32_t ledState = 0;
    while (1)
    {
        gpio_set_level(GPIO_LED, ledState);

        if (GPIO_ON == ledState )
        {
            ledState = GPIO_OFF;
            
        }
        else
        {
            ledState = GPIO_ON;
        }
        printf("Led state %d\n", ledState);
        vTaskDelay(TasksConfig[1].Period);
    }

}


static void task_led2(void *arg)
{
    static uint32_t ledState = 0;
    while (1)
    {
        gpio_set_level(GPIO_LED2, ledState);

        if (GPIO_ON == ledState )
        {
            ledState = GPIO_OFF;
            
        }
        else
        {
            ledState = GPIO_ON;
        }
        printf("Led state %d\n", ledState);
        vTaskDelay(TasksConfig[2].Period);
    }
    


}


void app_main()
{
    BaseType_t taskCreate;

    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    app_wifi_start();


    wifi_ap_record_t ap_record;
    esp_wifi_sta_get_ap_info(&ap_record);
    printf("AP info ssid %s\n , channel %d \n",ap_record.ssid, ap_record.primary);
    show_mac(ap_record.bssid);


    gpio_set_direction(GPIO_LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_LED2, GPIO_MODE_OUTPUT);
    //start gpio task
    taskCreate = xTaskCreate(writeHello,TasksConfig[0].TaskName,1024u, NULL, 1, NULL);
    xTaskCreate(controlLed, TasksConfig[1].TaskName, 2048, NULL, 10, NULL);
    xTaskCreate(task_led2, TasksConfig[2].TaskName, 2048, NULL, 5, NULL);


    start_webserver();

    if (taskCreate != pdPASS)
    {
        printf("problem creating task %s\n", TasksConfig[0].TaskName);
    }

}