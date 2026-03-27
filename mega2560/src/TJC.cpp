#include "config.h"
#include "TJC.h"

void SendEnd(){
    TJC.write(0xff);
    TJC.write(0xff);
    TJC.write(0xff);
}

//TJC串口屏显示与arduino通信
void TJC_Show(int x,int y){

 char str[100];

     //用sprintf来格式化字符串，给n0的val属性赋值y
     sprintf(str, "n0.val=%d\xff\xff\xff", x);
     //把字符串发送出去
     TJC.print(str);
     SendEnd();

     //用sprintf来格式化字符串，给t0的txt属性赋值n
     sprintf(str, "n1.val=%d\xff\xff\xff", y);
     //把字符串发送出去
     TJC.print(str);
 SendEnd();
     delay(5);  //延时50ms,才能看清楚点击效果

   }

