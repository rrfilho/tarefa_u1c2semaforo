#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "libs/osal.h"
#include "libs/display.h"
#include "libs/buttons.h"
#include "libs/leds.h"
#include "libs/buzzer.h"
#include "tasks/entry_task.h"
#include "tasks/exit_task.h"
#include "tasks/reset_task.h"
#include "tasks/lab.h"

void init() {
    stdio_init_all();
    os_init(MAX_CAPACITY);
    buttons_init();
    leds_init(MAX_CAPACITY);
    display_init();
    buzzer_init();
    leds_set_count(0);
    display_show_message(EMPTY_LAB);
}

int main() {
    init();
    os_create_task(entry_task, "Entrada");
    os_create_task(exit_task, "Saída");
    os_create_task(reset_task, "Reinício");
    os_start();
}