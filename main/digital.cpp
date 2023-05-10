#include "digital.h"
#include <stdio.h>

int Digital::digitalRead(gpio_num_t pin)
{
    return gpio_get_level(pin);
}

void Digital::pinMode(gpio_num_t pin, int config)
{
    unsigned char c = config & 1;
    if (c == INPUT)
        gpio_set_direction(pin, GPIO_MODE_INPUT);
    else
        gpio_set_direction(pin, GPIO_MODE_OUTPUT);

    if (config & 2)
    {
        gpio_set_pull_mode(pin, GPIO_PULLUP_ONLY);
    }
}
void Digital::digitalWrite(gpio_num_t pin, int value)
{
    gpio_set_level(pin, value);
}

Digital digital = Digital();
