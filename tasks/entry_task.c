#include "entry_task.h"
#include <stdio.h>
#include "lab.h"
#include "osal.h"
#include "buttons.h"
#include "display.h"
#include "leds.h"
#include "buzzer.h"

static void beep() {
    buzzer_set(true);
    os_sleep_ms(300);
    buzzer_set(false);
}

void entry_task() {
    char message[30];
    unsigned int count;
    while (true) {
        os_sleep_ms(100);
        if (!buttons_left_is_pressed()) continue;
        if (os_counting_semaphore_value() == 0) beep();
        if (!os_counting_semaphore_take()) continue;
        count = MAX_CAPACITY - os_counting_semaphore_value();
        leds_set_count(count);
        if (count == MAX_CAPACITY) sprintf(message, FULL_LAB);
        else sprintf(message, COUNT_LAB, count, MAX_CAPACITY);
        display_show_message(message);
    }
}