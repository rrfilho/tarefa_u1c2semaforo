#include "reset_task.h"
#include "osal.h"
#include "lab.h"
#include "display.h"
#include "leds.h"
#include "buzzer.h"

void reset_task() {
    while(true) {
        os_sleep_ms(100);
        if (!os_binary_semaphore_take()) continue;
        for(int i = 0; i < MAX_CAPACITY; i++) os_counting_semaphore_give();
        leds_set_count(0);
        display_show_message(EMPTY_LAB);
        buzzer_set(true);
        os_sleep_ms(100);
        buzzer_set(false);
        os_sleep_ms(100);
        buzzer_set(true);
        os_sleep_ms(100);
        buzzer_set(false);
    }
}