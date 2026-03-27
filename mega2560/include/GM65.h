#ifndef GM65_H
#define GM65_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class GM65 {
  public:
    GM65(int rxPin, int txPin);
    void begin(long baudRate);
    int readQRCode();
    void clearSerialBuffer();
    SoftwareSerial* _serial;

  private:
    int _rxPin;
    int _txPin;
};

#endif