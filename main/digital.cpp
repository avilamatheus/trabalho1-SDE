#include "digital.h"
#include <stdio.h>

/**
 * Le um pino, dado o valor do mesmo.
 */
int Digital::digitalRead(gpio_num_t pin)
{
    return gpio_get_level(pin);
}

/**
 * Configura um pino, passando o pino e o modo de configuração.
 */
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

/**
 * Seta um valor em um pino, passando o pino e o valor.
 */
void Digital::digitalWrite(gpio_num_t pin, int value)
{
    gpio_set_level(pin, value);
}

Digital digital = Digital();
