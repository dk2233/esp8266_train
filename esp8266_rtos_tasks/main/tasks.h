#ifndef TASKS_H
#define TASKS_H


#include <freertos/FreeRTOS.h>
#include <cstdint>
#include <string_view>
#include <tasks.h>
#include <task.h>
#include <esp_log.h>


constexpr uint16_t TASK_DEFAULT_SIZE {1024};

class Task_Class {
    private:
        TaskFunction_t task_function;
        std::string_view name;
        uint32_t period;
        uint16_t stack_size;
        UBaseType_t priority;
        void *const task_function_parameters;
        TaskHandle_t handle_task;
    public:
        Task_Class(TaskFunction_t task_func, 
                std::string_view n,
                uint32_t perio,
                uint16_t stack_s = TASK_DEFAULT_SIZE,
                UBaseType_t prio = tskIDLE_PRIORITY, 
                void *const function_parameters = NULL);
        //this pvParameters is only to be according to freertos prototype
        static void freertos_task(void *pvParameters);

        void task_function_method(); 


        void start();
};


void tasks_start();

#endif 
