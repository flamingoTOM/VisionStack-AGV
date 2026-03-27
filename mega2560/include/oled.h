#ifndef OLED_H
#define OLED_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class OLED {
public:
  OLED(int sda, int scl);
  void begin();
  void clearDisplay();
  //void displayText(float text, int x, int y);
  void displayText(const char* text, int x, int y);
  void all_zero();
private:
  Adafruit_SSD1306* display;
};

#endif
