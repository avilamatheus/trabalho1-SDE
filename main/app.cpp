#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "serial.h"
#include "memory.h"
#include <inttypes.h>
#include "db.h"
#include "db.cpp"

extern "C" void app_main();
Header header;
int v = 0;

/**
 * Opções do menu principal, retorna a opção escolhida pelo usuário
*/
char menu(void)
{
  char option;

  printf("********MENU********\n");
  printf("[1] - List all records\n");
  printf("[2] - Insert record\n");
  printf("[3] - Search record by name\n");
  printf("[4] - Search record by phone\n");
  printf("[5] - Delete record based on phone\n");
  printf("[6] - Shows the number of records currently stored\n");
  printf("[7] - Initialize the database (all stored information will be lost)\n");
  
  option = serial.readChar();
  return option;
}

/**
 * Função main do programa
*/
void app_main()
{
  // Inicializa a memória
  Memory i2c = Memory();
  i2c.init(0);

  // Inicia a comunicação serial
  serial.begin(9600);

  char name[20];
  char phone[14];

  while (1)
  {
    char option_input = menu();
    switch (option_input)
    {
    case '1':
      // lista todos os registros salvos na memória
      listRecords();
      printf("\n");
      break;
    case '2':
      Header position;
      Record new_record;

      printf("\n");
      position = readHeader(false);
      printf("Enter the name: ");

      serial.readString((uint8_t *)new_record.name, 20);

      printf("%s\n", new_record.name);

      printf("Enter the address: ");
      serial.readString((uint8_t *)new_record.address, 30);
      printf("%s\n", new_record.address);

      printf("Enter the phone: ");
      serial.readString((uint8_t *)new_record.phone, 14);

      printf("%s\n", new_record.phone);

      // salva o registro na memória
      saveRecord(position.used_record_number, &new_record);
      printf("\n");
      break;
    case '3':
      printf("\n");
      printf("Enter the name: ");
      serial.readString((uint8_t *)name, 20);
      printf("\n");

      // busca o registro pelo nome
      searchName(name);
      printf("\n");
      break;
    case '4':
      printf("\n");
      printf("Enter the phone: ");
      serial.readString((uint8_t *)phone, 14);
      printf("\n");

      // busca o registro pelo telefone
      searchPhone(phone);
      printf("\n");
      break;
    case '5':
      printf("\n");
      printf("Enter the phone: ");
      serial.readString((uint8_t *)phone, 14);

      // remove o registro pelo telefone
      removeRecord(phone);
      printf("\n");
      break;
    case '6':
      printf("\n");

      // mostra o número de registros salvos na memória
      readHeader(true);
      printf("\n");
      break;
    case '7':
      header.used_record_number = 0;
      header.max_record_quantity = 1023;

      createHeader(&header);
      break;
    }
  }
}
