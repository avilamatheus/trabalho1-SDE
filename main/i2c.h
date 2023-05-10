#ifndef __I2C_SOFTWARE_
#define __I2C_SOFTWARE_

#include <inttypes.h>
#include "driver/gpio.h"

class I2C
{
public:
    // Configures the software I2C interface with the specified data and clock pins.
    void configure(gpio_num_t data_pin, gpio_num_t clk_pin);

    // Generates an I2C start condition.
    void start(void);

    // Generates an I2C stop condition.
    void stop(void);

    // Writes a byte of data to the I2C bus and returns the ACK bit.
    uint8_t write(uint8_t byte);

    // Reads a byte of data from the I2C bus and returns the ACK bit.
    uint8_t read(void);

private:
    // Sets the data pin to a low state.
    void data_low(void);

    // Sets the data pin to a high state.
    void data_high(void);

    // Sets the clock pin to a high state.
    void clock_high(void);

    // Sets the clock pin to a low state.
    void clock_low(void);

    // Writes a bit of data to the I2C bus.
    void write_bit(uint8_t bit);

    // Reads a bit of data from the I2C bus.
    uint8_t read_bit(void);

    // Reads the ACK bit from the I2C bus after a write or read operation.
    uint8_t read_ack(uint8_t ack);
};

#endif
