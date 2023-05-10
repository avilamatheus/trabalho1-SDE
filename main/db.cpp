#include "db.h"
#include <stdio.h>
#include <vector>
#include "memory.h"
#include <string.h>

void createHeader(Header *c)
{
    MEMORY.write(0, (uint8_t *)c, sizeof(Header));
}

Header readHeader(char command)
{
    Header actualHeader;
    MEMORY.read(0, (uint8_t *)&actualHeader, sizeof(Header));
    if (command == '6')
    {
        printf("Amount of used records: %d\n", actualHeader.used_record_number);
    }

    return actualHeader;
}

void updateHeader()
{
    Header actualHeader = readHeader('0');
    actualHeader.used_record_number = actualHeader.used_record_number + 1;
    MEMORY.write(0, (uint8_t *)&actualHeader, sizeof(Header));
};

void removeHeader()
{
    Header actualHeader = readHeader('0');
    actualHeader.used_record_number = actualHeader.used_record_number - 1;
    MEMORY.write(0, (uint8_t *)&actualHeader, sizeof(Header));
};

void saveRecord(uint16_t record_number, Record *R)
{
    uint16_t position;

    if (record_number == 1023)
    {
        printf("ERROR. MEMORY FULL!!!\n");
    }
    else
    {
        position = 4 + (record_number) * sizeof(Record);
        MEMORY.write(position, (uint8_t *)R, sizeof(Record));
        updateHeader();
    }
};

void listRecords()
{
    Header register_length = readHeader('1');
    Record register_queried;

    uint16_t position;
    for (int i = 0; i < register_length.used_record_number; i++)
    {
        position = 4 + (i) * sizeof(Record);
        MEMORY.read(position, (uint8_t *)&register_queried, sizeof(Record));
        printf("\n [REGISTER] %d :\n Name: %s\n Address: %s\n Phone: %s\n", i + 1, register_queried.name, register_queried.address, register_queried.phone);
    }
};

void searchName(char n[20])
{
    bool find = false;
    Header register_length = readHeader('3');
    Record register_queried;

    uint16_t position;
    for (int i = 0; i < register_length.used_record_number; i++)
    {
        position = 4 + (i) * sizeof(Record);
        MEMORY.read(position, (uint8_t *)&register_queried, sizeof(Record));

        if (strcmp(register_queried.name, n) == 0)
        {
            printf("[REGISTER] %d :\n Name: %s\n Address: %s\n Phone:%s\n", i + 1, register_queried.name, register_queried.address, register_queried.phone);
            find = true;
        }
    }

    if (!find)
    {
        printf("ERROR! Register not found.\n");
    }
}

Record searchPhone(char phone[14])
{
    bool find = false;
    Header register_length = readHeader('4');
    Record register_phone;
    Record register_queried;

    uint16_t position;
    for (int i = 0; i < register_length.used_record_number; i++)
    {
        position = 4 + (i) * sizeof(Record);
        MEMORY.read(position, (uint8_t *)&register_queried, sizeof(Record));

        if (strcmp(register_queried.phone, phone) == 0)
        {
            find = true;
            register_phone = register_queried;
            printf("[REGISTER] %d :\n Name: %s\n Address: %s\n Phone:%s\n", i + 1, register_queried.name, register_queried.address, register_queried.phone);
        }
    }

    if (!find)
    {
        printf("ERROR! Register not found.\n");
    }

    return register_phone;
}

void removeRecord(char phone[14])
{
    Record register_to_remove;
    printf("\n");
    register_to_remove = searchPhone(phone);

    Header register_length = readHeader('5');
    Record register_queried;

    uint16_t position;
    for (int i = 0; i < register_length.used_record_number; i++)
    {
        position = 4 + (i) * sizeof(Record);
        MEMORY.read(position, (uint8_t *)&register_queried, sizeof(Record));
        if (strcmp(register_queried.phone, register_to_remove.phone) == 0)
        {
            position = 4 + (register_length.used_record_number - 1) * sizeof(Record);
            MEMORY.read(position, (uint8_t *)&register_queried, sizeof(Record));
            saveRecord(i, &register_queried);
            removeHeader();
            removeHeader();
            break;
        }
    }
};
