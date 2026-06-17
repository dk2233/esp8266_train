#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdint.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include <help_utils.h>
#include <esp_http_server.h>
#include <string_view>
#include <wifi_handle.h>
#include <ports_conf.h>
#include <http_handle.h>
#include <task.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include "tasks.h"
#include "portmacro.h"



static const char *TAG = "tasks_app";

static void writeHello(void *arg);
static void controlLed(void *arg);
static void task_led2(void *arg);

static Task_Class task_obj1 = Task_Class(writeHello, "hello task", 1000/portTICK_PERIOD_MS, 2048, 10);
static Task_Class task_obj2 = Task_Class(controlLed, "led_task", 1200/portTICK_PERIOD_MS, 1024, 5);
static Task_Class task_obj3 = Task_Class(task_led2, "led_task2", 600/portTICK_PERIOD_MS, 1024, 2);

static void writeHello(void *arg)
{
    static uint32_t i = 0;
        ESP_LOGI(TAG, "Hello times %d\n", i++);
            //fflush(stdout);
}

static void controlLed(void *arg)
{
    static uint32_t ledState = 0;
        gpio_set_level(GPIO_LED, ledState);

        if (GPIO_ON == ledState )
        {
            ledState = GPIO_OFF;
            
        }
        else
        {
            ledState = GPIO_ON;
        }
        ESP_LOGI(TAG, "Led state %d\n", ledState);

}

/*
 *
 * to change Led state 
 *  http://espkoko/info?Led=1 - to change LedStateFromHttp
 * 
 *
 */
static void task_led2(void *arg)
{
    static uint32_t ledState = GPIO_OFF;
        if ((GPIO_ON == LedStateFromHttp) &&(GPIO_OFF == ledState))
        {
            ledState = GPIO_ON;
        }
        else
        {
            ledState = GPIO_OFF;
        }

            gpio_set_level(GPIO_LED2, ledState);

        ESP_LOGI(TAG,"Led state %d\n", LedStateFromHttp);
    


}


void Task_Class::task_function_method() 
{
    ESP_LOGI(TAG, " started task method in class with name %s \n", name.data());
    while(1) 
    {
        task_function(task_function_parameters);
        vTaskDelay(period);

    }


}

Task_Class::Task_Class(TaskFunction_t task_func, std::string_view  n, uint32_t perio, uint16_t stack_s ,  UBaseType_t prio, void *const function_parameters):
    task_function{task_func},
            name(n), 
            period{perio}, 
            stack_size{stack_s},
            priority{prio}, 
            task_function_parameters{function_parameters} {

            };


void Task_Class::start()
{
ESP_LOGI(TAG, "This -> %p\n %.*s\n", this, (int)this->name.size(), this->name.data());

            BaseType_t taskCreate  {xTaskCreate( 
                    Task_Class::freertos_task, 
                    name.data(), 
                    stack_size, 
                    this, 
                    priority, 
                    &handle_task)};

            if (taskCreate != pdPASS)
            {
                ESP_LOGI(TAG, "Problem creating task %s\n", name.data());
                        //.data());
            }
};

void Task_Class::freertos_task(void *pvParameters)
{
    Task_Class * this_task_class = static_cast<Task_Class*>(pvParameters);

    this_task_class->task_function_method();

}

void tasks_start()
{
    printf("[MEM] How many heap %d bytes\n", (int)esp_get_free_heap_size());

        
    task_obj1.start();
    task_obj2.start();
    task_obj3.start();
    printf("[MEM] How many heap %d bytes\n", (int)esp_get_free_heap_size());
}
