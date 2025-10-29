#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdint.h>
#include <driver/gpio.h>
#include <esp_wifi.h>

#define GPIO_LED  GPIO_NUM_2
#define GPIO_LED2  GPIO_NUM_5
#define GPIO_ON     (1u)
#define GPIO_OFF     (0u)


typedef struct 
{
    char * TaskName;
    uint32_t Period;
} TasksConfig_t;


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
    // wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    // ESP_ERROR_CHECK(esp_wifi_init(&cfg));


    gpio_set_direction(GPIO_LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(GPIO_LED2, GPIO_MODE_OUTPUT);
    //start gpio task
    taskCreate = xTaskCreate(writeHello,TasksConfig[0].TaskName,1024u, NULL, 1, NULL);
    xTaskCreate(controlLed, TasksConfig[1].TaskName, 2048, NULL, 10, NULL);
    xTaskCreate(task_led2, TasksConfig[2].TaskName, 2048, NULL, 5, NULL);


    if (taskCreate != pdPASS)
    {
        printf("problem creating task %s\n", TasksConfig[0].TaskName);
    }

}