#include <stdio.h>
#include <stdint.h>


typedef struct data_t
{
  uint8_t stat;
  uint8_t cmd;
  uint8_t type;
  uint16_t v1;
  float v2;
};

typedef union packet_t {
 struct data_t data;
 uint8_t packet[sizeof(struct data_t)];
};


#define PACKET_SIZE sizeof(struct data_t)

union packet_t sendMsg;
union packet_t receiveMsg;

void readByteArray();
void writeByteArray();
void printByteArray();

uint8_t byteArray[PACKET_SIZE];


int main()
{

  sendMsg.data.stat = 1;
  sendMsg.data.cmd = 44;
  sendMsg.data.type = 255;
  sendMsg.data.v1 = 3131;
  sendMsg.data.v2 = 1234.567;

  printByteArray(sendMsg);

  writeByteArray();

  readByteArray();

  printByteArray(receiveMsg);

}

void printByteArray(union packet_t msg)
{
  printf("%d",sendMsg.data.stat);
  printf("\t");
  printf("%d",sendMsg.data.cmd);
  printf("\t");
  printf("%d",sendMsg.data.type);
  printf("\t");
  printf("%d",sendMsg.data.v1);
  printf("\t");
  printf("%f",sendMsg.data.v2);
  printf("\n");
}

void readByteArray()
{
  for (int i=0; i < PACKET_SIZE; i++)
   {
     receiveMsg.packet[i] = byteArray[i];
   }

}

void writeByteArray()
{
  for(int i=0; i<PACKET_SIZE; i++)
  {
    printf("%X",sendMsg.packet[i]);
    printf("\t");
    byteArray[i] = sendMsg.packet[i]; // msg into byte array
  }
  printf("\n");
}
