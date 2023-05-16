#ifndef __DB__
#define __DB__

#include <inttypes.h>

typedef struct
{
    uint16_t used_record_number;
    uint16_t max_record_quantity;
} Header;

typedef struct
{
    char name[20];
    char phone[14];
    char address[30];
} Record;

class DB
{
public:
    void createHeader(Header *h);
    void updateHeader();
    void removeHeader();
    Header readHeader(bool printNum);
    void saveRecord(uint16_t record_number, Record *R);
    void listRecords();
    void searchName(char name[20]);
    Record searchPhone(char phone[14]);
    void removeRecord(char phone[14]);
};

extern DB db;

#endif
