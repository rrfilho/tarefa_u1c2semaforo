#include "exit_task.h"
#include <stdio.h>
#include "lab.h"
#include "osal.h"
#include "buttons.h"
#include "display.h"
#include "leds.h"

void exit_task() {
    char message[30];
    unsigned int count;
    while (true) {
        os_sleep_ms(100);
        if (!buttons_right_is_pressed()) continue;
        os_counting_semaphore_give();
        count = MAX_CAPACITY - os_counting_semaphore_value();
        leds_set_count(count);
        if (count == 0) sprintf(message, EMPTY_LAB);
        else sprintf(message, COUNT_LAB, count, MAX_CAPACITY);
        display_show_message(message);
    }
}