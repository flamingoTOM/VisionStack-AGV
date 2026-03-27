#include "GM65.h"
#include <SoftwareSerial.h>

GM65::GM65(int rxPin, int txPin) {
   _rxPin = rxPin;
   _txPin = txPin;
   _serial = new SoftwareSerial(rxPin, txPin);
   _serial->begin(9600);
 } 

void GM65::begin(long baudRate) {
    pinMode(_rxPin, INPUT);
    pinMode(_txPin, OUTPUT);
    _serial->begin(baudRate);
} 



int GM65:: readQRCode() {
      int qrcode = 0;
      _serial->println("AT+QRCODE");  // 发送读取二维码的命令
      delay(500);  // 等待模块响应
      unsigned long start_time = millis();                // 获取当前的系统时间
      delay(200);

      while (millis() - start_time < 2200)
      {
        if (_serial->available())
        {
          qrcode = _serial->read()-48 ;
          
          break;  // 返回读取到的二维码内容   
        }
        delay(20);
      }
      Serial.println(qrcode);
      return qrcode;
} 


