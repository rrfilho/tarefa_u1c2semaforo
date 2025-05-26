#include "buttons.h"
#include "pico/stdlib.h"
#include "osal.h"

#define LEFT_BUTTON 5
#define RIGHT_BUTTON 6
#define JOYSTICK_BUTTON 22
#define DEBOUNCE_TIME_LIMIT_US 200000

static bool _is_left_button_pressed = false;
static bool _is_right_button_pressed = false;
static unsigned int _left_button_last_time_us = 0;
static unsigned int _right_button_last_time_us = 0;
static unsigned int _joystick_button_last_time_us = 0;

static unsigned int now_us() {
    return to_us_since_boot(get_absolute_time());
}

static bool has_wait_time_reached(unsigned int last_time) {
    return now_us() - last_time >= DEBOUNCE_TIME_LIMIT_US;
}

static void handler_with_debounce(unsigned int* time, bool* is_pressed) {
    if (!has_wait_time_reached(*time)) return;
    *is_pressed = true;
    *time = now_us();
}

static void joystick_handler_with_debounce() {
    if (!has_wait_time_reached(_joystick_button_last_time_us)) return;
    os_binary_semaphore_give();
    _joystick_button_last_time_us = now_us();
}

static void handler_adapter(uint gpio, uint32_t event_mask) {
    if (gpio == LEFT_BUTTON){
        handler_with_debounce(&_left_button_last_time_us, &_is_left_button_pressed);
        return;
    }
    if (gpio == RIGHT_BUTTON) {
        handler_with_debounce(&_right_button_last_time_us, &_is_right_button_pressed);
        return;
    }
    if (gpio == JOYSTICK_BUTTON) {
        joystick_handler_with_debounce();
        return;
    }
}

static void button_init(unsigned int button_pin) {
    gpio_init(button_pin);
    gpio_set_dir(button_pin, GPIO_IN);
    gpio_pull_up(button_pin);
    gpio_set_irq_enabled_with_callback(button_pin, GPIO_IRQ_EDGE_FALL, true, handler_adapter);
}

void buttons_init() {
    button_init(LEFT_BUTTON);
    button_init(RIGHT_BUTTON);
    button_init(JOYSTICK_BUTTON);
}

static bool is_button_pressed(bool* is_pressed) {
    bool temp = *is_pressed;
    *is_pressed = false;
    return temp;
}

bool buttons_left_is_pressed() {
    return is_button_pressed(&_is_left_button_pressed);
}

bool buttons_right_is_pressed() {
    return is_button_pressed(&_is_right_button_pressed);
}