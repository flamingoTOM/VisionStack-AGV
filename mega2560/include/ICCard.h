#ifndef ICCARD_H
#define ICCARD_H

#include <MFRC522.h>

class ICCard {
public:
  ICCard(uint8_t ssPin, uint8_t rstPin);
  void setup();
  //void readCard();
  //void printCardData();
  int read_Card();
  void printBufferData(byte *buffer, byte bufferSize);
  int Ten_to_Sixteen(int a);
  int read_card_2();
  
//private:
  MFRC522 mfrc522;
  MFRC522::MIFARE_Key key;
  char buffer[3];
  int wuliao[10] = {0,0,0,0,0,0,0,0,0,0};
  int wuliao_p[2][10] = {1,2,3,4,5,6,7,8,9,10,10,10,10,10,10,10,10,10,10,10};
  int zk = 0;
  char* intToHex(int aa);
  int turn(int a);
  int mapping[10];
  int planB_yuanpan[10] = {10,10,10,10,10,10,10,10,10,10};
  int true_turn(int turn,int position);

};

#endif

