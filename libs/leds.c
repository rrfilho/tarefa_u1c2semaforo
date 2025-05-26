#include "leds.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define GREEN_PWM_LED 11
#define BLUE_PWM_LED 12
#define RED_PWM_LED 13
#define CLOCK_DIVIDER 2.0
#define WRAP 4096
#define ON 400
#define OFF 0

static int _max_count;

static void init_pin(unsigned int pin) {
    gpio_set_function(pin, GPIO_FUNC_PWM);
    unsigned int slice = pwm_gpio_to_slice_num(pin);
    pwm_set_clkdiv(slice, CLOCK_DIVIDER);
    pwm_set_wrap(slice, WRAP);
    pwm_set_gpio_level(pin, OFF);
    pwm_set_enabled(slice, true);
}

void leds_init(int max_count) {
    _max_count = max_count;
    init_pin(GREEN_PWM_LED);
    init_pin(BLUE_PWM_LED);
    init_pin(RED_PWM_LED);
}

static void set_level(unsigned int led_pin, unsigned int brightness) {
    pwm_set_gpio_level(led_pin, brightness);
}

static void _clear() {
    set_level(GREEN_PWM_LED, OFF);
    set_level(BLUE_PWM_LED, OFF);
    set_level(RED_PWM_LED, OFF);
}

void leds_set_count(int count) {
    _clear();
    if (count == 0) {
        set_level(BLUE_PWM_LED, ON);
        return;
    }
    if (count == _max_count) {
        set_level(RED_PWM_LED, ON);
        return;
    }
    if (count == _max_count - 1) {
        set_level(RED_PWM_LED, ON);
        set_level(GREEN_PWM_LED, ON);
        return;
    }
    set_level(GREEN_PWM_LED, ON);
}