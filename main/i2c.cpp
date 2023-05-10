
#include "i2c.h"
#include "digital.h"
#include <stdio.h>
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "digital.h"

gpio_num_t DATA_PIN;
gpio_num_t CLK_PIN;

#define delay_us(A) ets_delay_us(2 * A)
#define delay_ms(A) vTaskDelay(500 / portTICK_PERIOD_MS)

void I2C::data_low(void)
{
    digital.pinMode(DATA_PIN, OUTPUT);
    digital.digitalWrite(DATA_PIN, LOW);
}

void I2C::data_high(void)
{
    digital.pinMode(DATA_PIN, INPUT);
}

void I2C::clock_high(void)
{
    digital.pinMode(CLK_PIN, INPUT);
}

void I2C::clock_low(void)
{
    digital.pinMode(CLK_PIN, OUTPUT);
    digital.digitalWrite(CLK_PIN, LOW);
}

void I2C::configure(gpio_num_t data_pin, gpio_num_t clk_pin)
{
    DATA_PIN = data_pin;
    CLK_PIN = clk_pin;

    // Configure I/O
    clock_high();
    data_high();
    delay_ms(1);
}
void I2C::start(void)
{
    clock_high();
    delay_us(10);
    data_high();
    delay_us(10);
    data_low();
    delay_us(10);
    clock_low();
    delay_us(10);
}

void I2C::write_bit(uint8_t bit)
{
    if (bit)
        data_high();
    else
        data_low();
    delay_us(10);
    clock_high();
    delay_us(10);
    clock_low();
    data_high();
}

uint8_t I2C::read_bit(void)
{
    uint8_t value;

    data_high();
    delay_us(10);
    clock_high();
    value = digital.digitalRead(DATA_PIN);
    delay_us(10);
    clock_low();
    return value;
}

uint8_t I2C::write(uint8_t byte)
{
    uint8_t a, x;
    for (x = 0; x < 8; x++)
        write_bit(1 & (byte >> (7 - x)));
    a = read_bit();

    delay_us(10);
    return a;
}

uint8_t I2C::read(void)
{
    uint8_t value = 0, x;

    for (x = 0; x < 8; x++)
        value = (value << 1) | read_bit();
    return value;
}

uint8_t I2C::read_ack(uint8_t ack)
{
    uint8_t value = 0, x;

    for (x = 0; x < 8; x++)
        value = (value << 1) | read_bit();
    write_bit(ack);
    return value;
}

void I2C::stop(void)
{
    data_low();
    delay_us(5);
    clock_low();
    delay_us(5);
    clock_high();
    delay_us(5);
    data_high();
    delay_us(5);
}
