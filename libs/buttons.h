#include <stdbool.h>
typedef void (*handler)();

void buttons_init();
bool buttons_left_is_pressed();
bool buttons_right_is_pressed();