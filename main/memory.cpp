#include "memory.h"
#include "i2c.h"
#include "digital.h"
#include "db.h"
#include <stdio.h>

/**
 * Instancia a classe I2C.
 */
Memory::Memory(void)
{
	myI2c = I2C();
}

/**
 * Verifica se o dispositivo esta disponivel.
 */
void Memory::checkEepromAvailability(void)
{
	uint8_t device = 0x50 | targetDevice;

	for (;;)
	{
		myI2c.start();
		int ack = myI2c.write((device << 1));
		if (ack == 0)
			return;
	}
}

/**
 * Inicia a memoria.
 */
void Memory::init(uint8_t device)
{
	targetDevice = device;
	myI2c.configure(PIN16, PIN5);
}

/**
 * Escreve dados na memoria.
 */
void Memory::write(uint16_t address, uint8_t data[], uint16_t length)
{
	uint8_t device = 0x50 | targetDevice;
	uint16_t actualAddress = address;
	for (int a = 0; a < length; a++)
	{
		checkEepromAvailability();
		myI2c.start();
		myI2c.write((device << 1) | 0);
		myI2c.write(actualAddress >> 8);
		myI2c.write(actualAddress);
		myI2c.write(data[a]);
		myI2c.stop();
		actualAddress++;
	}
}

/**
 * Le dados da memoria.
*/
void Memory::read(uint16_t address, uint8_t data[], uint16_t length)
{
	uint8_t device = 0x50 | targetDevice;
	uint16_t actualAddress = address;
	checkEepromAvailability();

	for (int a = 0; a < length; a++)
	{

		myI2c.start();
		myI2c.write((device << 1) | 0);
		myI2c.write(actualAddress >> 8);
		myI2c.write(actualAddress);
		myI2c.start();
		myI2c.write((device << 1) | 1);
		data[a] = myI2c.read();
		myI2c.stop();
		actualAddress++;
	}
}

Memory MEMORY;
