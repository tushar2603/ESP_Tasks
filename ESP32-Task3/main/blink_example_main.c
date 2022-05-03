
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "led_strip.h"
#include "sdkconfig.h"


TaskHandle_t Task1;
TaskHandle_t Task2;

gpio_num_t led1 = 2;
gpio_num_t led2 = 4;

void Task1code(void *p)
{
    gpio_reset_pin(led1);
    gpio_set_direction(led1, GPIO_MODE_OUTPUT);
    printf("Task 1 is running on core:\n");
    printf("%d\n", xPortGetCoreID());

    while(1)
    {
        
        gpio_set_level(led1, 0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        gpio_set_level(led1, 1);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void Task2code(void *p)
{
    printf("Hello world");
}

void app_main(void)
{
    xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);
    vTaskDelay(50/portTICK_PERIOD_MS);
    
    xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);
    vTaskDelay(50/portTICK_PERIOD_MS);
}

