#include "ICCard.h"

ICCard::ICCard(uint8_t ssPin, uint8_t rstPin) : mfrc522(ssPin, rstPin), zk(0) {}





 void ICCard::setup() {
  SPI.begin();
  mfrc522.PCD_Init();
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}


  
int ICCard::read_Card() {
    // 检查是否有卡片接近
    if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
        return -1; // 返回-1表示没有卡片
    }

    // 认证扇区0，块1
    byte sector = 0, block = 1;
    MFRC522::StatusCode status;
    MFRC522::MIFARE_Key key;
    memset(key.keyByte, 0xFF, sizeof(key.keyByte)); // 默认密钥

    byte blockAddr = sector * 4 + block;
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockAddr, &key, &(mfrc522.uid));

    // 读取数据块
    byte buffer[18];
    byte size = sizeof(buffer);
    status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);


    if (status == MFRC522::STATUS_OK) {
        //Serial.print("0x");
        //Serial.println(buffer[0]);
        int m= Ten_to_Sixteen(buffer[0]);
        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();
        Serial.println(m);
        
        return m;
    }

    // 结束与卡片的通信
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
   return -1;
} 














void ICCard::printBufferData(byte *buffer, byte bufferSize) {
    Serial.print("Received data: ");
    for (byte i = 0; i < bufferSize; i++) {
        if (buffer[i] < 0x10) {
            Serial.print("0");  // 补齐位数
        }
        Serial.print(buffer[i], HEX);  // 以十六进制格式打印数据
        Serial.print(" ");  // 每个字节后添加空格
    }
    Serial.println();  // 换行
}




char* ICCard::intToHex(int aa) {
  if (aa / 16 < 10)
    buffer[0] = aa / 16 + '0';
  else
    buffer[0] = aa / 16 - 10 + 'A';
  if (aa % 16 < 10)
    buffer[1] = aa % 16 + '0';
  else
    buffer[1] = aa % 16 - 10 + 'A';
  buffer[2] = '\0';
  return buffer;
}


int ICCard::turn(int a)
{
  
  enum status
  {
    line1_arrange3 = 1,
    line2_arrange3 = 2,
    line3_arrange3 = 3,
    line1_arrange2 = 4,
    line2_arrange2 = 5,
    line3_arrange2 = 6,
    line1_arrange1 = 7,
    line2_arrange1 = 8,
    line3_arrange1 = 9,
    Interference_ball = 10,
   
  };

  switch(a)
  {
    case 19:
    return line1_arrange3;
    case 35:
    return line2_arrange3;
    case 51:
    return line3_arrange3;
    case 18:
    return line1_arrange2;
    case 34:
    return line2_arrange2;
    case 50:
    return line3_arrange2;
    case 17:
    return line1_arrange1;
    case 33:
    return line2_arrange1;
    case 49:
    return line3_arrange1;
    break;
    case 20:
    return Interference_ball;
    break;
    case 53:  //test 
    return 123;
    break;
    default:
    return 0;
    break;
  }
  
}
int ICCard::true_turn(int turn, int position)
{
  

  int should_turn ;
  if(turn == 0)
  {
    return 0;
  }
  if (position == turn)
  {
    return 0;
  }
  if(position < turn)
  {
    should_turn = turn-position;
    return should_turn;
  }
  if(position > turn)
  {
  
    should_turn = position-turn;
    return should_turn;
  }
  else return 0;
  
}


int ICCard::Ten_to_Sixteen(int a)
{
    int b=a;
    int shi =b / 16;    //       50/16 =3
    int ge = b % 16;    //       50%16 =2
    int c =shi*10 +ge ;
    return c;
}