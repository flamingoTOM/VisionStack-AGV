#include "OLED.h"

OLED::OLED(int sda, int scl) {
  display = new Adafruit_SSD1306(128, 64, &Wire, sda, scl);
}

void OLED::begin() {
  display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
//开像素点发光
display->setTextColor(WHITE);
    //清屏
    display->clearDisplay();
    //设置字体大小
    display->setTextSize(2);
}

void OLED::clearDisplay() {
   display->clearDisplay();
}

/* void OLED::displayText(float text, int x, int y) {
  display->setCursor(x, y);
  display->println(text);
  display->display();
}  */

void OLED::displayText(const char* text, int x, int y) {
  display->setCursor(x, y); // 设置光标位置
  display->println(text);    // 打印文本
  display->display();        // 刷新显示
} 

//4行16列 
                    //   |  |  |09|12
                    // 01|34|67|10|13
                 //0// 00 00 00 00 00
                 //1// 00 00 00 00 00
 void OLED::all_zero()
{
  displayText("00", 0, 0); 
  displayText("00", 26, 0); 
  displayText("00", 52, 0);
  displayText("00", 78, 0);
  displayText("00", 104, 0); 
  displayText("00", 0, 20); 
  displayText("00", 26, 20); 
  displayText("00", 52, 20);
  displayText("00", 78, 20);
  displayText("00", 104, 20); 

} 


