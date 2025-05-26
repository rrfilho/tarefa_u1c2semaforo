// Operational System Abstraction Layer
#include "osal.h"
#include <stdbool.h>
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"

static SemaphoreHandle_t _mutex;
static SemaphoreHandle_t _binary;
static SemaphoreHandle_t _counting;

void os_init(int counting_semaphore_max) {
    _mutex = xSemaphoreCreateMutex();
    _binary = xSemaphoreCreateBinary();
    _counting = xSemaphoreCreateCounting(counting_semaphore_max, counting_semaphore_max);
}

void os_sleep_ms(unsigned int duration) {
    vTaskDelay(pdMS_TO_TICKS(duration));
}

void os_create_task(task task, char* task_name) {
    xTaskCreate(task, task_name, configMINIMAL_STACK_SIZE + 128, NULL, tskIDLE_PRIORITY, NULL);
}

bool os_mutex_take() {
    return xSemaphoreTake(_mutex, portMAX_DELAY);
}

void os_mutex_give() {
    xSemaphoreGive(_mutex);
}

bool os_binary_semaphore_take() {
    return xSemaphoreTake(_binary, portMAX_DELAY);
}

void os_binary_semaphore_give() {
    xSemaphoreGiveFromISR(_binary, pdFALSE);
    portYIELD_FROM_ISR(pdFALSE); // change context
}

bool os_counting_semaphore_take() {
    return xSemaphoreTake(_counting, portMAX_DELAY);
}

void os_counting_semaphore_give() {
    xSemaphoreGive(_counting);
}

unsigned int os_counting_semaphore_value() {
    return uxSemaphoreGetCount(_counting);
}

void os_start() {
    vTaskStartScheduler();
    panic_unsupported();
}