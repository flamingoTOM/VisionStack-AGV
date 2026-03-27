#include "config.h"


motor mt (20, 6000, 4, 1.8);
motor mt2(20, 6000, 4, 1.8);
white_detect wat;
robotarm Arm(armmotor);         //机械臂
HC_SR04 sensor(8, 9);           //超声右
HC_SR04 sensor2(A13,A12);       //超声左
ICCard icCard(53,49);//ss rst   //IC卡读卡器
ObstacleAvoidance oa(47);       //丢石头激光传感避障
OLED oled(20, 21);              //OLED屏幕
GM65 gm65(A15,A14);             //GM65



void setup()
{
    Serial.begin(9600);
    armmotor.begin(9600);  //机械臂
    Serial2.begin(9600);  //树莓派
    Serial3.begin(9600);  //陀螺仪
    icCard.setup();
    sensor.begin();
    sensor2.begin();
    oa.begin();
    oled.begin();
    gm65.begin(9600);


    

    pinMode(40, INPUT);
    pinMode(41, INPUT);
    pinMode(42, INPUT);
    pinMode(43, INPUT);
    pinMode(30, INPUT);
    pinMode(31, INPUT);
    pinMode(32, INPUT);
    pinMode(33, INPUT);





    /*-------------- 开定时器2的中断 ----------------*/
    MsTimer2::set(20, HWT101); // 每200毫秒执行一次HWT101函数
    MsTimer2::start();          // 启动定时器

    zl();

}

void loop()
{
   
/*-----------------车头出发A-----------------*/

    
   JTPY_A();
   YPJ_A();
   LTCK_A();   
    

/*-----------------车尾出发B-----------------*/
 
     /* JTPY_B();
   YPJ_B(); 
   LTCK_B();    */ 
 


  while(1)
  {
    
  }










}
