#ifndef __MEMORY__
#define __MEMORY__

#include <cstdint>
#include "i2c.h"
#include "db.h"

class Memory
{
public:
	Memory();
	void init(uint8_t device);									   // Initializes the EEPROM device with the given device number
	void write(uint16_t address, uint8_t data[], uint16_t length); // Writes an array of bytes to the specified memory address of the EEPROM
	void read(uint16_t address, uint8_t data[], uint16_t length);  // Reads an array of bytes from the specified memory address of the EEPROM

private:
	uint8_t targetDevice;			// The target EEPROM device number
	void checkEepromAvailability(); // Tests if the EEPROM is available for communication
	I2C myI2c;						// Object of the I2C communication library
};

extern Memory MEMORY;

#endif
