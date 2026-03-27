#include "feedback.h"
#include "config.h"
// 陀螺仪角度数据
double real_yaw = 0;
double expect_yaw = 0;
double current_error_yaw = 0;
volatile int timerCounter = 0;

 void HWT101()
{
    while (Serial3.available()) 
    {
        JY901.CopeSerialData(Serial3.read()); 
    }

    // 储存数据
    real_yaw = (float)JY901.stcAngle.Angle[2]/32768*180;
    real_yaw = real_yaw + 90;

    //Serial.print("real_yaw:");Serial.println(real_yaw);
  
} 

void zl()
{
  Serial3.write(0xFF);
  Serial3.write(0xAA);
  Serial3.write(0x76);
  Serial3.write(0x00);
  Serial3.write(0x00);
  delay(2000);
}

/* void HWT101() 
{ 
    timerCounter++; // 每次中断计数器加1 // 每100次中断后才执行一次数据读取，相当于每20ms一次 
if (timerCounter >= 100) 
{ 
    timerCounter = 0; // 重置计数器 
    while (Serial3.available())
     { JY901.CopeSerialData(Serial3.read()); // 读取传感器数据
      double real_yaw1 = (float)JY901.stcAngle.Angle[2] / 32768 * 180; 
      real_yaw = real_yaw1 - 90;
       Serial.println(real_yaw); 
        } 
        } 
        } */