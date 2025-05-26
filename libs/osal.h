// Operational System Abstraction Layer
#include <stdbool.h>

typedef void (*task)();

void os_init(int max_count);
void os_sleep_ms(unsigned int duration);
void os_create_task(task task, char* task_name);
bool os_mutex_take();
void os_mutex_give();
bool os_binary_semaphore_take();
void os_binary_semaphore_give();
bool os_counting_semaphore_take();
void os_counting_semaphore_give();
unsigned int os_counting_semaphore_value();
void os_start();
