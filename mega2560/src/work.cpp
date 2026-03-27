#include <work.h>

white_detect wt;

/*---------------------------------------------------全局变量-----------------------------------------------------*/

int x_yaw = 90;     //实际场地里，车在起点处车头的方向      
int jtpt_ball= 0;     //阶梯平台球计数
int ball_color = 2  ;   //红2 蓝3
int Matrix[2][5] = { {-1} }; // 创建一个 1x4 的数组并初始化为 0 //用来储存ic card数值
int m=0;    //目标行
int n=2;    //目标列
int last_n= 2 ;    //上一次目标行
int is_ball=0;         //0为无球   1为有球
int is_stop = 0 ;           //阶梯平台停止标志位，1停止
int QR_result[3] = { 0,0,0};          //二维码结果
int dao_duo[3][3] = { { -1 } };       //倒跺数组
int QR_chaosheng = 22 ;


/*---------------------------------------------------阶梯平台-----------------------------------------------------------------*/
void JTPY_A()
{
        STEP1_A();
        STEP2_A();
        Close_to_jtpy_A();
        jtpy_catch_1_A();
        jtpy_catch_2_A();
        jtpy_catch_3_A();
}

void JTPY_B()
{
        STEP1_B();
        STEP2_B();
        Close_to_jtpy_B();
        jtpy_catch_1_B();
        jtpy_catch_2_B();
        jtpy_catch_3_B();
}

/*---------------------------------------------------圆盘机----------------------------------------------------------------------*/
void YPJ_A()
{
    STEP3_A();
    STEP4_A();  
    STEP5_A();
    Close_to_ypj_A();
    YPJ_catch_ball(); 
}

void YPJ_B()
{
    STEP3_B();
    STEP4_B();  
    STEP5_B();
    Close_to_ypj_B();
    YPJ_catch_ball(); 
}
/*---------------------------------------------------立体仓库----------------------------------------------------------------------*/
void LTCK_A()
{
   // BIZHANG_A();
    STEP6_A();
    Close_to_ck_A();
    Dao_Duo_A();
    put_in_ck_A();
    STEP7_A();
    Back_jtpt_A();
    BACK_HOME_A();
}

void LTCK_B()
{
    //BIZHANG_B(); 
    STEP6_B();
    Close_to_ck_B();
    Dao_Duo_B();
    put_in_ck_B();
    STEP7_B();
    Back_jtpt_B();
    BACK_HOME_B(); 
}

/*---------------------------------------------------视觉----------------------------------------------------------------------*/

int jtpt_color()    //2红3蓝
{
    unsigned long start_time = millis();                // 获取当前的系统时间
    Serial2.print('4');                                 // 通过串口发送字符 '1'
    delay(200);
    while (millis() - start_time < 3200)
    { 
        if (Serial2.available())                   // 检查串口是否有可读取的数据
        {
            if (49 == Serial2.read()){clearSerialBuffer(); return 2;}
            if (50 == Serial2.read()){clearSerialBuffer(); return 3;}
        }
        delay(20);
    } 
    clearSerialBuffer();
    delay(20);
    return -1;             //没检测到
}


int ypj_color()   // 去检测什么颜色的球
{
   if(ball_color==2){ Serial2.print('2');  }
   if(ball_color==3){ Serial2.print('3');  }
   delay(200);

        if (Serial2.available())  // 检查是否有数据可读
         {
            if (Serial2.read() == 49) {clearSerialBuffer();  return 2;}
            if (Serial2.read() == 50) {clearSerialBuffer();  return 3;}
        }
        delay(20);  // 短暂延时，避免占用过多CPU资源
        clearSerialBuffer();
        return -1;
}

void ltck_location()
{
    clearSerialBuffer();
    int x[9]={-1};
     String str = ""; // Declare the variable 'str'
    unsigned long start_time = millis();                // 获取当前的系统时间
    if(ball_color==2){Serial2.print('5');  }
    if(ball_color==3){Serial2.print('6');  }
    delay(200);

    while (millis() - start_time < 3200)
    {
        if(Serial2.available())                   // 检查串口是否有可读取的数据
        {
            // Serial.println(Serial2.readStringUntil('\n'));
            str = Serial2.readStringUntil('\n');
            break;
        }
    }

    for (size_t i = 0; i < 9; i++) {
        if(i<3)       {dao_duo[0][i]   = str.charAt(i) - '0'; }
        if(i>2 && i<6){dao_duo[1][i-3] = str.charAt(i) - '0'; }
        if(i>5 && i<9){dao_duo[2][i-6] = str.charAt(i) - '0'; }
    }
        // 输出数组中的内容以验证
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++){            
                Serial.print(dao_duo[i][j]);
                Serial.print(" ");
            }
        } 
}

void clearSerialBuffer() {
    while (Serial2.read()>0) ;
}



/*--------------------------------------------其他封装---------------------------------------------*/

void read_and_display(int x,int y)
{
    icCard.setup();
    int a=x;
    int b=y;
    
    //读取
    unsigned long startTime = millis(); // 获取当前时间
    while (millis() - startTime < 2000)
    {
        Matrix[a][b]=icCard.read_Card();            //返回有效值 or -1
        Serial.println(Matrix[a][b]);
        if ( Matrix[a][b] >0 ){break;}        //检测到有效值跳出
        delay(20);
    }
    
    //显示
    char text[3]; // 需要足够的空间以存储数字和 '\0'
    snprintf(text, sizeof(text), "%d", Matrix[a][b]); // 将数字转换为字符串

    if(a==0 && b==0){oled.displayText(text, 0, 20);}
    if(a==0 && b==1){oled.displayText(text, 26, 20);}
    if(a==0 && b==2){oled.displayText(text, 52, 20);}
    if(a==0 && b==3){oled.displayText(text, 78, 20);}
    if(a==0 && b==4){oled.displayText(text, 104, 20);}

    if(a==1 && b==0){oled.displayText(text, 0, 0);}
    if(a==1 && b==1){oled.displayText(text, 26, 0);}
    if(a==1 && b==2){oled.displayText(text, 52, 0);}
    if(a==1 && b==3){oled.displayText(text, 78, 0);}
    if(a==1 && b==4){oled.displayText(text, 104, 0);}

}


void IC_read_adjust(int a ,int b)
{
    read_and_display(a,b);
    if (Matrix[a][b]==-1){Arm.cc(); delay(300); read_and_display(a,b);delay(400);}
    
}


void Ultrasound_ms_1(int time_ms, int target_distance) {
    int time = time_ms;
    unsigned long start_time = millis(); // 获取当前的系统时间

    // PID参数
    float Kp = 100;   // 比例系数
    float Ki = 0.1;    // 积分系数
    float Kd = 0;   // 微分系数

    float integral = 0; // 积分值
    float previous_error = 0; // 上一个误差

    while (millis() - start_time < time) {
        float distance = sensor.average_distance();
        float error = distance - target_distance;

        // 计算PID
        integral += error; // 积分
        float derivative = error - previous_error; // 微分

        // PID公式
        int target_theta = Kp * error + Ki * integral + Kd * derivative;
        char direction_command = (error < 0) ? MOVE_LEFT : MOVE_RIGHT;
        mt.Stepmotor_Closed_Control(direction_command, abs(target_theta));

        if (abs(error) < 0.1) {
            break; // 如果误差足够小，则退出循环
        }

        previous_error = error; // 更新上一个误差
    }
}



/* void Ultrasound_ms_1(int time_ms ,int far)         //超声测距蓝色
{
    int time = time_ms;
    int dist = far;
    unsigned long start_time = millis();                // 获取当前的系统时间
  while (millis() - start_time < time)
  {
        float distance = sensor.average_distance();
        float error = distance -dist ;

        int target_theta = error * 100; 
        char direction_command = (error < 0) ? MOVE_LEFT : MOVE_RIGHT;
        mt.Stepmotor_Closed_Control(direction_command, abs(target_theta));
        
        if (abs(error) < 0.1){break;}
        delay(4);
  }
} */

/* void Ultrasound_ms_2(int time_ms ,int far)         //超声测距黑色
{
    int time = time_ms;
    int dist = far;
    unsigned long start_time = millis();                // 获取当前的系统时间
  while (millis() - start_time < time)
  {
        float distance = sensor2.average_distance();
        float error = distance -dist ;

        int target_theta = error * 100; 
        char direction_command = (error < 0) ? MOVE_RIGHT : MOVE_LEFT;
        mt.Stepmotor_Closed_Control(direction_command, abs(target_theta));
        
        if (abs(error) < 0.1){break;}
        delay(4);
  } 
} */


void Ultrasound_ms_2(int time_ms, int target_distance) {
    int time = time_ms;
    unsigned long start_time = millis(); // 获取当前的系统时间

    // PID参数
    float Kp = 100; // 比例系数
    float Ki = 0.1; // 积分系数
    float Kd = 10; // 微分系数

    float integral = 0; // 积分值
    float previous_error = 0; // 上一个误差

    while (millis() - start_time < time) {
        float distance = sensor2.average_distance();
        float error = distance - target_distance;

        // 计算PID
        integral += error; // 积分
        float derivative = error - previous_error; // 微分

        // PID公式
        int target_theta = Kp * error + Ki * integral + Kd * derivative;
        char direction_command = (error < 0) ? MOVE_RIGHT : MOVE_LEFT;

        mt.Stepmotor_Closed_Control(direction_command, abs(target_theta));

        if (abs(error) < 0.1) {
            break; // 如果误差足够小，则退出循环
        }

        previous_error = error; // 更新上一个误差
    }
}


/*---------------------------------------------------任务----------------------------------------------------------------------*/


//方案一
//第一步：前往第一个十字架
void STEP1_A()
{
    mt.Stepmotor_Closed_Control(MOVE_RIGHT, 5100);
    mt.adjust_yaw_pid(x_yaw + 1);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(FORWARD, 9500);
}

//前往第二个十字架
void STEP2_A()
{
    while(wt.getline() == 0)  //到达十字架纵线
    {
        mt.Stepmotor_Run_Control(FORWARD);
    }
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);
    mt.Stepmotor_Closed_Control(FORWARD, 100);
    wt.adjust_line_pid();      //对准白线
    delay(20);

    while(true)                    //如果检测到十字架，停车
    {
        mt.Stepmotor_Closed_Control(FORWARD, 50);
        if(wt.getcount() == 1)
        {
            delay(20);
            if(wt.getcount() == 1)      
            {
                delay(20);
                break;
            }
        }
    }
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);
}

//直走右移，靠近阶梯平台
void Close_to_jtpy_A()
{
    mt.Stepmotor_Closed_Control(FORWARD, 4300);     //直走
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);
    mt.Stepmotor_Closed_Control(MOVE_RIGHT, 3100);  //右移
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);  
    Ultrasound_ms_1(3000 ,4);

}

void jtpy_catch_1_A()    // 抓取第一个目标颜色的球
{
    Serial2.print('4');     // 预先启动视觉
    delay(200);
    Arm.jtpy_hold_1();     //2.5  举起爪子
    delay(500);
    mt2.Stepmotor_Closed_Control42(STG_b,  4200);
    clearSerialBuffer();  // 清空串口缓冲区

 /*----------------------------------------第1个孔位------------------------------------*/
        if(jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_1();   //3s
            delay(3000);
            jtpt_ball ++ ;
            IC_read_adjust(1,4);
            Arm.jtpy_1_to_2();
            delay(1500); 
            mt.Stepmotor_Closed_Control50(FORWARD, 760);   //慢行
            Arm.jtpy_hold_1();
            delay(1000);
            mt2.Stepmotor_Closed_Control42(STG_a,  2100);
            delay(500);
        }
        else
        {
            mt.Stepmotor_Closed_Control50(FORWARD, 760);   //慢行
            delay(500);
        }

        clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据

 /*-------------------------------------------第2个孔位---------------------------------------*/
        if(jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_1();   //3.9s
            delay(3000);
            jtpt_ball ++ ;
            if(jtpt_ball==1){IC_read_adjust(1,4);}    
            if(jtpt_ball==2){IC_read_adjust(1,3);}   
            Arm.jtpy_1_to_2();
            delay(1500);
            if(jtpt_ball < 2)
            {
                mt.Stepmotor_Closed_Control50(FORWARD, 880);
                Arm.jtpy_hold_1();   //2500
                delay(2700);
                Arm.jtpy_hold_2_fast();       //0.4S
                mt2.Stepmotor_Closed_Control42(STG_a,  2100);
                delay(500);
            }    
        }
        else
        {
            Arm.jtpy_hold_2_fast();       //0.4S
            mt.Stepmotor_Closed_Control50(FORWARD, 800);
            delay(500);
        }

        if(jtpt_ball == 2)
        {
            is_stop =1;
            mt.Stepmotor_Closed_Control(MOVE_LEFT,3500);
        }
        else
        {
            clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据
            mt.adjust_yaw_pid(x_yaw);
            delay(200);
            Ultrasound_ms_1(1000 ,4);
        }
        
} 

 void jtpy_catch_2_A()    // 抓取第2个目标颜色的球
{
 /*-------------------------------------------第1个孔位---------------------------------------*/
        if(jtpt_ball < 2 && jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_2();   //3s
            delay(3000);
            jtpt_ball ++ ;
            if(jtpt_ball==1){IC_read_adjust(1,4);}    
            if(jtpt_ball==2){IC_read_adjust(1,3);}   
            Arm.jtpy_1_to_2();
            delay(1500);
            if(jtpt_ball < 2)
            {
                mt.Stepmotor_Closed_Control50(FORWARD, 720);
                Arm.jtpy_hold_2();
                delay(500);
                mt2.Stepmotor_Closed_Control42(STG_a,  2100);
                delay(1000);
            }
            
        }
        else if(jtpt_ball < 2)
        {
            mt.Stepmotor_Closed_Control50(FORWARD, 720);
            delay(2500);
        }
        else{delay(20);}
        clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据

        if(jtpt_ball == 2 && is_stop == 0)
        {
            is_stop =1;
            mt.Stepmotor_Closed_Control(MOVE_LEFT,3500);
        }



/*-------------------------------------------第2个孔位---------------------------------------*/
        if(jtpt_ball < 2 && jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_2();   //3s
            delay(3000);
            jtpt_ball ++ ;
            if(jtpt_ball==1){IC_read_adjust(1,4);}    
            if(jtpt_ball==2){IC_read_adjust(1,3);}   
            Arm.jtpy_1_to_2();
            delay(1500);
            if(jtpt_ball < 2)
            {
                mt.Stepmotor_Closed_Control50(FORWARD, 720);
                Arm.jtpy_hold_2();
                delay(500);
                mt2.Stepmotor_Closed_Control42(STG_a,  2100);
                delay(1000);
            }
        }
        else if(jtpt_ball < 2)
        {
            mt.Stepmotor_Closed_Control50(FORWARD, 720);
            delay(2500);
        }
        else{delay(20);}
        clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据

        if(jtpt_ball == 2 && is_stop == 0)
        {
            is_stop =1;
            mt.Stepmotor_Closed_Control(MOVE_LEFT,3500);
        }




        /*-------------------------------------------第3个孔位---------------------------------------*/
        mt.adjust_yaw_pid(x_yaw);
            delay(200);
            Ultrasound_ms_1(1000 ,3.8);
 
        if(jtpt_ball < 2 && jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_2();   //3s
            delay(3000);
            jtpt_ball ++ ;
            if(jtpt_ball==1){IC_read_adjust(1,4);}    
            if(jtpt_ball==2){IC_read_adjust(1,3);}   
            Arm.jtpy_1_to_2();
            delay(1500);
            if(jtpt_ball < 2)
            {
                mt.Stepmotor_Closed_Control50(FORWARD, 720);
                Arm.jtpy_hold_2();
                delay(500);
                mt2.Stepmotor_Closed_Control42(STG_a,  2100);
                delay(1000);
            }
            
        }
        else if(jtpt_ball < 2)
        {
            mt.Stepmotor_Closed_Control50(FORWARD, 720);
            delay(2500);
        }
        else{delay(20);}
        clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据

        if(jtpt_ball == 2 && is_stop == 0)
        {
            is_stop =1;
            mt.Stepmotor_Closed_Control(MOVE_LEFT,3500);
        }

        /*-------------------------------------------第4个孔位---------------------------------------*/
        if(jtpt_ball < 2 && jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_2();   //3s
            delay(3200);
            jtpt_ball ++ ;
            if(jtpt_ball==1){IC_read_adjust(1,4);}    
            if(jtpt_ball==2){IC_read_adjust(1,3);}   
            delay(200);
            Arm.jtpy_1_to_2();
            delay(1500);
            if(jtpt_ball < 2)
            {
                mt.Stepmotor_Closed_Control50(FORWARD, 820);
                Arm.jtpy_hold_3();
                delay(2500);
                Arm.jtpy_hold_3_fast();  //0.4s
                mt2.Stepmotor_Closed_Control42(STG_a,  2100);
                delay(500);
            } 
        }
        else if(jtpt_ball < 2)
        {
            mt.Stepmotor_Closed_Control50(FORWARD,820);
            delay(500);
            Arm.jtpy_hold_3_fast();  //0.4s
            delay(1000);
        }
        else{delay(20);}
        clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据

        if(jtpt_ball == 2 && is_stop == 0)
        {
            is_stop =1;
            mt.Stepmotor_Closed_Control(MOVE_LEFT,3500);
        }
        else if(jtpt_ball < 2 && is_stop == 0)
        {
            clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据
            mt.adjust_yaw_pid(x_yaw);
            delay(200);
            Ultrasound_ms_1(1500 ,5.5);
        }
    
} 

void jtpy_catch_3_A()  
{
    /*-------------------------------------第3-1个孔位---------------------------------- */
    if(jtpt_ball < 2 && jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_3();   //3s
            delay(3000);
            jtpt_ball ++ ;
            if(jtpt_ball==1){IC_read_adjust(1,4);}    
            if(jtpt_ball==2){IC_read_adjust(1,3);}   
            Arm.jtpy_1_to_2();
            delay(1500);
            if(jtpt_ball < 2)
            {
                mt.Stepmotor_Closed_Control50(FORWARD, 720);
                Arm.jtpy_hold_3();
                delay(2500);
                mt2.Stepmotor_Closed_Control42(STG_a,  2100);
                delay(1000);
            } 
        }
        else if(jtpt_ball < 2)
        {
            mt.Stepmotor_Closed_Control50(FORWARD, 720);
            delay(1000);
        }
        else{delay(20);}
        clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据

        if(jtpt_ball == 2 && is_stop == 0)
        {
            is_stop =1;
            mt.Stepmotor_Closed_Control(MOVE_LEFT,3500);
        }

        /*-------------------------------------第3-2个孔位---------------------------------- */
    if(jtpt_ball < 2 && jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_3();   //3s
            delay(3000);
            jtpt_ball ++ ;
            if(jtpt_ball==1){IC_read_adjust(1,4);}    
            if(jtpt_ball==2){IC_read_adjust(1,3);}   
            Arm.jtpy_1_to_2();
            delay(1500);
            clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据
        }
        
       if( is_stop == 0)
        {
            is_stop =1;
            mt.Stepmotor_Closed_Control(MOVE_LEFT,3500);
            //Arm.jtpy_catch_2();
            delay(500);
            if(jtpt_ball==0){mt2.Stepmotor_Closed_Control42(STG_a,  2100);}
        }
}
  
void STEP3_A()    //去第三个十字架
{
    mt.adjust_yaw_pid(x_yaw+1);    //陀螺仪校准
    while(wt.getline() == 0)  //到达十字架纵线
    {
        mt.Stepmotor_Run_Control(FORWARD);
    }
    mt.adjust_yaw_pid(x_yaw+1);    //陀螺仪校准
    delay(20);
    mt.Stepmotor_Closed_Control50(FORWARD, 80);
    wt.adjust_line_pid();      //对准白线
    delay(20);

    while(true)                    //如果检测到十字架，停车
    {
        mt.Stepmotor_Closed_Control(FORWARD, 50);
        if(wt.getcount() == 1)
        {
            delay(20);
            if(wt.getcount() == 1)      
            {
                delay(20);
                break;
            }
        }
    }
    mt.adjust_yaw_pid(x_yaw+1);    //陀螺仪校准
    delay(20);
    
}

void STEP4_A()    //去第四个十字架
{
    mt.Stepmotor_Closed_Control(FORWARD, 9000);
    STEP2_A();
}


void STEP5_A()       //去第5个十字架
{
    mt.Stepmotor_Closed_Control(FORWARD, 3000);
    mt.Stepmotor_Closed_Control(MOVE_LEFT, 8800); 

    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);

    while(wt.getline() == 0)  //到达十字架纵线
    {
        mt.Stepmotor_Run_Control(BACKWARD);
    }

    mt.Stepmotor_Closed_Control(BACKWARD, 100);
    wt.adjust_line_pid();      //对准白线

    while(true)                    //如果检测到十字架，停车
    {
        mt.Stepmotor_Closed_Control50(BACKWARD, 50);
        if(wt.getcount() == 1)
        {
            delay(20);
            if(wt.getcount() == 1)      
            {
                delay(20);
                break;
            }
        }
    }
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);
    mt.Stepmotor_Closed_Control(FORWARD, 2000);
    
}

void Close_to_ypj_A()
{
    mt.Stepmotor_Closed_Control(MOVE_LEFT, 2820);
    delay(200);
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准 
}

void YPJ_catch_ball()
{
    int k = 0;       //已经抓了几次
    
    Arm.ypj_hold(); //1.4s
    if(ball_color==2){Serial2.print('2');  }
    if(ball_color==3){Serial2.print('3');  }
    delay(3000);
    mt2.Stepmotor_Closed_Control42(STG_a,  2100);    //1.s

    unsigned long start_time = millis();                // 获取当前的系统时间
    while(k < 6 && millis() - start_time < 65000)     //做65s
    {
        clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据
        
        if(ypj_color() == ball_color)
        { 
            //delay(100);
            Arm.ypj_catch();
            delay(500);
            k++;
            Arm.ypj_put_1();
            delay(1800);
            if(k==1)
            {
                IC_read_adjust(1,2);
                delay(400);
                Arm.jtpy_1_to_2(); 
                delay(2100);
                Arm.ypj_hold();
                delay(500);
                mt2.Stepmotor_Closed_Control42(STG_a,  4050);
               // delay(1000);
            }
            if(k==2)
            {
                IC_read_adjust(0,0);
                delay(400);
                Arm.ypj_hold();
                delay(500);
                mt2.Stepmotor_Closed_Control42(STG_b,  2010);
                delay(500);
            }
            if(k==3)
            {
                IC_read_adjust(0,1);
                delay(400);
                Arm.ypj_hold();
                delay(500);
                mt2.Stepmotor_Closed_Control42(STG_b,  2100);
                delay(500);
            }
            if(k==4)
            {
                IC_read_adjust(0,2);
                delay(400);
                Arm.ypj_hold();
                delay(500);
                mt2.Stepmotor_Closed_Control42(STG_b,  2100); 
                delay(500);
            }
            if(k==5)
            {
                IC_read_adjust(0,3);
                delay(400);
                Arm.ypj_hold();
                delay(500);
                mt2.Stepmotor_Closed_Control42(STG_b,  2100); 
                delay(500);
            }
            if(k==6)
            {
                IC_read_adjust(0,4);
                delay(400);
                //mt2.Stepmotor_Closed_Control42(STG_a,  4200);
                //delay(500);
            }
        }
        delay(20);
        clearSerialBuffer();
    }

        Arm.to_zero();                                  //爪子举起来
        delay(200);
        mt.Stepmotor_Closed_Control(MOVE_RIGHT, 2600);  //车远离圆盘机

        /*------------------如果对面把我们的球抓走了---------------- */
        
        if(k==6){mt2.Stepmotor_Closed_Control42(STG_a,  4200);}
        if(k==5){mt2.Stepmotor_Closed_Control42(STG_a,  4200);} 
        if(k==4){mt2.Stepmotor_Closed_Control42(STG_a,  2100);}
        if(k==2){mt2.Stepmotor_Closed_Control42(STG_b,  2100);}
        if(k==1){mt2.Stepmotor_Closed_Control42(STG_b,  4200);} 
}

void BIZHANG_A()
{
    int is_jiancedao = 0;
    while(is_jiancedao == 0)
    {
        if(oa.isObjectDetected() == false)
        {
            mt.Stepmotor_Run_Control(BACKWARD);
        }
        else
        {
            is_jiancedao = 1;
            // Serial.println("有障碍物");
            mt.Stepmotor_Closed_Control(FORWARD,1000);
            mt.Stepmotor_Closed_Control(MOVE_RIGHT, 3500);
            mt.Stepmotor_Closed_Control(BACKWARD,6000);
            mt.Stepmotor_Closed_Control(MOVE_LEFT, 3500);
        }
    }
    mt.adjust_yaw_pid(x_yaw);
    while(wt.getline() == 0)  //到达十字架纵线
    {
        mt.Stepmotor_Run_Control(BACKWARD);
    }
}

void STEP6_A()   //去第6个十字架
{

    mt.adjust_yaw_pid(x_yaw-1);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(BACKWARD, 6000);

    while(wt.getline() == 0)  //到达十字架纵线
    {
        mt.Stepmotor_Run_Control(BACKWARD);
    }
    mt.Stepmotor_Closed_Control_42(BACKWARD, 100);
    mt.adjust_yaw_pid(x_yaw-1);    //陀螺仪校准

    wt.adjust_line_pid();
    delay(20);

    while(true)                    //如果检测到十字架，停车
    {
        mt.Stepmotor_Closed_Control50(BACKWARD, 50);
        if(wt.getcount() == 1)
        {
            delay(20);
            if(wt.getcount() == 1)      
            {
                delay(20);
                break;
            }
        }
    }
    mt.adjust_yaw_pid(x_yaw-1);    //陀螺仪校准
    delay(20);
}

void Close_to_ck_A()
{
    mt2.Stepmotor_Closed_Control42(STG_a,  2100);
    mt.Stepmotor_Closed_Control(BACKWARD, 5000);     //直走
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(MOVE_LEFT, 1000); 
    Ultrasound_ms_2(3000 ,14);
}

void Dao_Duo_A()
{
    Arm.look();    delay(1200);
    ltck_location();           //视觉2s
    delay(500);
    Arm.to_zero();
    delay(2200);
    int p=0;                   //已经抓了几个球
    int row[4]={-1};           //row[第几个球] = 在第几行

    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Ultrasound_ms_2(2000 ,13);

    /*---------------------------------第2列----------------------------------*/
    //100 
    //001 
    //010
    if(dao_duo[0][1]==1)
        {   Arm.dd_catch3(); p++;  delay(2400); row[p]=1;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a, 2100);}}
    if(dao_duo[1][1]==1)
        {   Arm.dd_catch2();  p++;  delay(2400); row[p]=2;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a, 2100);}}
    if(dao_duo[2][1]==1)
        {   Arm.dd_catch1(); p++;  delay(2400);  row[p]=3;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a, 2100);}}

    /*---------------------------------第1列----------------------------------*/
    mt.Stepmotor_Closed_Control50(BACKWARD,1340);    //1360
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Ultrasound_ms_2(2000 ,13);

    if(dao_duo[0][0]==1)
        {   Arm.dd_catch3(); p++;  delay(2400);   row[p]=1;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a,  2100);}}
    if(dao_duo[1][0]==1)
        {   Arm.dd_catch2(); p++;  delay(2400);  row[p]=2;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a,  2100);}}
    if(dao_duo[2][0]==1)
        {   Arm.dd_catch1(); p++;  delay(2400);  row[p]=3;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a,  2100);}}

    /*---------------------------------第3列----------------------------------*/
    mt.Stepmotor_Closed_Control50(FORWARD,2680);       //2720

    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Ultrasound_ms_2(2000 ,13);

    if(dao_duo[0][2]==1)
        {   Arm.dd_catch3(); p++;  delay(2400);   row[p]=1;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a,  2100);}}
    if(dao_duo[1][2]==1)
        {   Arm.dd_catch2(); p++;  delay(2400);   row[p]=2;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a,  2100);}}
    if(dao_duo[2][2]==1)
        {   Arm.dd_catch1(); p++;  delay(2800);  row[p]=3; }

    
     /*---------------------------------第4列----------------------------------*/
    mt.Stepmotor_Closed_Control50(FORWARD,1400);  //1300（预赛）
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Ultrasound_ms_2(2000 ,13);

    if(row[3]==1){delay(500); Arm.ck_1_put_3(); delay(2400);}
    if(row[3]==2){delay(500); Arm.ck_1_put_2(); delay(2400);}
    if(row[3]==3){delay(500); Arm.ck_1_put_1(); delay(2400);}

    if(row[2]==1){Arm.ck_1_catch_2(); delay(2300); Arm.ck_1_put_3(); delay(2400);}
    if(row[2]==2){Arm.ck_1_catch_2(); delay(2300); Arm.ck_1_put_2(); delay(2400);}
    if(row[2]==3){Arm.ck_1_catch_2(); delay(2300); Arm.ck_1_put_1(); delay(2400);}

    mt2.Stepmotor_Closed_Control42(STG_b,  2100);
    if(row[1]==1){Arm.ck_1_catch_2(); delay(2300); Arm.ck_1_put_3(); delay(2400);}
    if(row[1]==2){Arm.ck_1_catch_2(); delay(2300); Arm.ck_1_put_2(); delay(2400);}
    if(row[1]==3){Arm.ck_1_catch_2(); delay(2300); Arm.ck_1_put_1(); delay(2400);}

    mt2.Stepmotor_Closed_Control42(STG_b,  2100);
}

void  put_in_ck_A()
{
    mt.Stepmotor_Closed_Control50(BACKWARD,1360);    //1400
    clearSerialBuffer_gm65();

    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Ultrasound_ms_2(2000 , QR_chaosheng);

     QR_result[0]=gm65.readQRCode();
     if(QR_result[0]==0)
     {QR_result[0]=2;}

     Ultrasound_ms_2(2000 ,13);

/*-------------------------------------第3列----------------------------------------*/
    find_ball(33);
    if(m==0 && is_ball==1){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_3();     delay(2400);}
    if(m==1 && is_ball==1){is_ball=0; Arm.ck_1_catch_2 ();   delay(2400);   Arm.ck_1_put_3();     delay(2400);}

    find_ball(23);
    if(m==0 && is_ball==1){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_2();     delay(2400);}
    if(m==1 && is_ball==1){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_2();     delay(2400);}

    find_ball(10  +  QR_result[0]);
    if(m==0 && is_ball==1 && QR_result[0]!=0){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_1();     delay(2400);}
    if(m==1 && is_ball==1 && QR_result[0]!=0){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_1();     delay(2400);}
    
    clearSerialBuffer_gm65();
    mt.Stepmotor_Closed_Control50(BACKWARD,1340);     //1300
    delay(1000);
    

/*-------------------------------------第2列-----------------------------------------*/
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Ultrasound_ms_2(2000 , QR_chaosheng);
    
    
    QR_result[1]=gm65.readQRCode();
     if(QR_result[1]==0)
     {QR_result[1]=1;}

     Ultrasound_ms_2(2000 ,13);

    find_ball(32);
    if(m==0 && is_ball==1){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_3();     delay(2400);}
    if(m==1 && is_ball==1){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_3();     delay(2400);}

    find_ball(22);
    if(m==0 && is_ball==1){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_2();     delay(2400);}
    if(m==1 && is_ball==1){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_2();     delay(2400);}

    find_ball(10  +  QR_result[1]); 
    if(m==0 && is_ball==1 && QR_result[1]!=0){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_1();     delay(2400);}
    if(m==1 && is_ball==1 && QR_result[1]!=0){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_1();     delay(2400);}

     clearSerialBuffer_gm65();
    mt.Stepmotor_Closed_Control50(BACKWARD,1300);
    delay(1000);
   

/*-------------------------------------第1列-----------------------------------------*/
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Ultrasound_ms_2(2000 , QR_chaosheng);
    
     QR_result[2]=gm65.readQRCode();
     if(QR_result[2]==0)
     {QR_result[2]=3;}
    delay(200);

    Ultrasound_ms_2(2000 ,13);
    


    find_ball(31);
    if(m==0 && is_ball==1){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_3();     delay(2400);}
    if(m==1 && is_ball==1){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_3();     delay(2400);}

    find_ball(21);
    if(m==0 && is_ball==1){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_2();     delay(2400);}
    if(m==1 && is_ball==1){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_2();     delay(2400);}

    find_ball(10  +  QR_result[2]);
    if(m==0 && is_ball==1 && QR_result[2]!=0){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_1();     delay(2400);}
    if(m==1 && is_ball==1 && QR_result[2]!=0){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_1();     delay(2400);}
}

void find_ball(int ball_index)
{
    int index = ball_index;
    last_n = n;
    
    
    for(int i=0 ; i<2 ; i++)
    {
        for(int j=0 ; j<5 ;j++)
        {
            if(Matrix[i][j] == index)
            {
                m = i;
                n = j;
                is_ball = 1;        //有球标志位
            }
        }
    }

    //盘子移动到目标球的位置
    if(n > last_n){mt2.Stepmotor_Closed_Control42(STG_b,  2100*(n  -  last_n));}
    if(n < last_n){mt2.Stepmotor_Closed_Control42(STG_a,  2100*(last_n  -  n));}
    delay(200);
}

void clearSerialBuffer_gm65() {
    while (gm65._serial->read()>0) ;
}


void STEP7_A()   //去第7个十字架
{

    mt.Stepmotor_Closed_Control(MOVE_RIGHT,2100);
    delay(200);
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准

    /*----------------------step2----------------------*/

    while(wt.getline() == 0)  //到达十字架纵线
    {
        mt.Stepmotor_Run_Control(BACKWARD);
    }
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(BACKWARD,150);
    delay(20);
    wt.adjust_line_pid();
    delay(20);
    while(true)                    //如果检测到十字架，停车
    {
        mt.Stepmotor_Closed_Control(BACKWARD, 50);
        if(wt.getcount() == 1)
        {
            delay(20);
            if(wt.getcount() == 1)      
            {
                delay(20);
                break;
            }
        }
    }
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);
}


void Back_jtpt_A()
{
    mt.Stepmotor_Closed_Control(BACKWARD, 3000);
    mt.Stepmotor_Closed_Control(MOVE_RIGHT, 8700); 

    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);

    while(wt.getline() == 0)  //到达十字架纵线
    {
        mt.Stepmotor_Run_Control(FORWARD);
    }

    mt.Stepmotor_Closed_Control(FORWARD, 100);
    wt.adjust_line_pid();      //对准白线

    while(true)                    //如果检测到十字架，停车
    {
        mt.Stepmotor_Closed_Control50(FORWARD, 50);
        if(wt.getcount() == 1)
        {
            delay(20);
            if(wt.getcount() == 1)      
            {
                delay(20);
                break;
            }
        }
    }
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);
/*--------------close to 接替平台---------------------------------*/
    mt.Stepmotor_Closed_Control(FORWARD, 4400);     //直走4300
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);
    mt.Stepmotor_Closed_Control(MOVE_RIGHT, 2400);  //右移
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);  
    Ultrasound_ms_1(3000 ,15);
/*----------------------------------------------------------------*/

    find_ball(14);
    if(m==0 && is_ball==1){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.grq();     delay(5200);}
    if(m==1 && is_ball==1){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.grq();     delay(5200);}
}

void BACK_HOME_A()   //回家
{
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Arm.curl();
/*--------------------------------------盘子归中------------------------------*/
    int ball=Matrix[0][2];
    if(ball > 0) {find_ball(ball);}
    else         {ball=Matrix[1][2];}
    if(ball > 0) {find_ball(ball);}
/*----------------------------------------------------------------------------*/
    
    mt.Stepmotor_Closed_Control(MOVE_LEFT, 3000);
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(BACKWARD, 6900);
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(BACKWARD, 6900);
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(MOVE_LEFT, 5600);
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
}







/*---------------------------------对称方案----------------------------------------------------*/

//方案一
//第一步：前往第一个十字架
void STEP1_B()
{
    mt.Stepmotor_Closed_Control(MOVE_RIGHT, 5000);
    mt.adjust_yaw_pid(x_yaw-2);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(BACKWARD, 11000);
}

//前往第二个十字架
void STEP2_B()
{
    while(wt.getline() == 0)  //到达十字架纵线
    {
        mt.Stepmotor_Run_Control(BACKWARD);
    }
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);
    mt.Stepmotor_Closed_Control(BACKWARD, 100);
    wt.adjust_line_pid();      //对准白线
    delay(20);

    while(true)                    //如果检测到十字架，停车
    {
        mt.Stepmotor_Closed_Control(BACKWARD, 50);
        if(wt.getcount() == 1)
        {
            delay(20);
            if(wt.getcount() == 1)      
            {
                delay(20);
                break;
            }
        }
    }
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);
}

//直走右移，靠近阶梯平台
void Close_to_jtpy_B()
{
    mt.Stepmotor_Closed_Control(BACKWARD, 6400);     //直走
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);
    mt.Stepmotor_Closed_Control(MOVE_RIGHT, 2800);  //右移
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);  
    Ultrasound_ms_1(3000 ,4.2);

}

void jtpy_catch_1_B()    // 抓取第一个目标颜色的球
{
    Serial2.print('4');     // 预先启动视觉
    delay(200);
    Arm.jtpy_hold_1();     //2.5  举起爪子
    delay(500);
    mt2.Stepmotor_Closed_Control42(STG_b,  4200);
    clearSerialBuffer();  // 清空串口缓冲区

 /*----------------------------------------第1个孔位------------------------------------*/
        if(jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_1();   //3s
            delay(2500);
            jtpt_ball ++ ;
            IC_read_adjust(1,4);
            Arm.jtpy_1_to_2();
            delay(1500); 
            mt.Stepmotor_Closed_Control50(FORWARD, 760);   //慢行
            Arm.jtpy_hold_1();
            delay(1000);
            mt2.Stepmotor_Closed_Control42(STG_a,2100);
            delay(500);
        }
        else
        {
            mt.Stepmotor_Closed_Control50(FORWARD, 760);   //慢行
            delay(500);
        }

        clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据

 /*-------------------------------------------第2个孔位---------------------------------------*/
        if(jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_1();   //3.9s
            delay(2500);
            jtpt_ball ++ ;
            if(jtpt_ball==1){IC_read_adjust(1,4);}    
            if(jtpt_ball==2){IC_read_adjust(1,3);}   
            Arm.jtpy_1_to_2();
            delay(1500);
            if(jtpt_ball < 2)
            {
                mt.Stepmotor_Closed_Control50(FORWARD, 880);
                Arm.jtpy_hold_1();   //2500
                delay(2700);
                Arm.jtpy_hold_2_fast();       //0.4S
                mt2.Stepmotor_Closed_Control42(STG_a,  2100);
                delay(500);
            }    
        }
        else
        {
            Arm.jtpy_hold_2_fast();       //0.4S
            mt.Stepmotor_Closed_Control50(FORWARD, 800);
            delay(500);
        }

        if(jtpt_ball == 2)
        {
            is_stop =1;
            mt.Stepmotor_Closed_Control(MOVE_LEFT,3500);
        }
        else
        {
            clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据
            mt.adjust_yaw_pid(x_yaw);
            delay(200);
            Ultrasound_ms_1(1000 ,3.6);
        }
        
} 

 void jtpy_catch_2_B()    // 抓取第2个目标颜色的球
{
 /*-------------------------------------------第1个孔位---------------------------------------*/
        if(jtpt_ball < 2 && jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_2();   //3s
            delay(2500);
            jtpt_ball ++ ;
            if(jtpt_ball==1){IC_read_adjust(1,4);}    
            if(jtpt_ball==2){IC_read_adjust(1,3);}   
            Arm.jtpy_1_to_2();
            delay(1500);
            if(jtpt_ball < 2)
            {
                mt.Stepmotor_Closed_Control50(FORWARD, 720);
                Arm.jtpy_hold_2();
                delay(500);
                mt2.Stepmotor_Closed_Control42(STG_a,  2100);
                delay(1000);
            }
            
        }
        else if(jtpt_ball < 2)
        {
            mt.Stepmotor_Closed_Control50(FORWARD, 720);
            delay(2500);
        }
        else{delay(20);}
        clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据

        if(jtpt_ball == 2 && is_stop == 0)
        {
            is_stop =1;
            mt.Stepmotor_Closed_Control(MOVE_LEFT,3500);
        }



/*-------------------------------------------第2个孔位---------------------------------------*/
        if(jtpt_ball < 2 && jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_2();   //3s
            delay(2500);
            jtpt_ball ++ ;
            if(jtpt_ball==1){IC_read_adjust(1,4);}    
            if(jtpt_ball==2){IC_read_adjust(1,3);}   
            Arm.jtpy_1_to_2();
            delay(1500);
            if(jtpt_ball < 2)
            {
                mt.Stepmotor_Closed_Control50(FORWARD, 720);
                Arm.jtpy_hold_2();
                delay(500);
                mt2.Stepmotor_Closed_Control42(STG_a,  2100);
                delay(1000);
            }
        }
        else if(jtpt_ball < 2)
        {
            mt.Stepmotor_Closed_Control50(FORWARD, 720);
            delay(2500);
        }
        else{delay(20);}
        clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据

        if(jtpt_ball == 2 && is_stop == 0)
        {
            is_stop =1;
            mt.Stepmotor_Closed_Control(MOVE_LEFT,3500);
        }

        /*-------------------------------------------第3个孔位---------------------------------------*/
       mt.adjust_yaw_pid(x_yaw);
            delay(200);
            Ultrasound_ms_1(1000 ,3.6);
       
        if(jtpt_ball < 2 && jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_2();   //3s
            delay(2500);
            jtpt_ball ++ ;
            if(jtpt_ball==1){IC_read_adjust(1,4);}    
            if(jtpt_ball==2){IC_read_adjust(1,3);}   
            Arm.jtpy_1_to_2();
            delay(1500);
            if(jtpt_ball < 2)
            {
                mt.Stepmotor_Closed_Control50(FORWARD, 720);
                Arm.jtpy_hold_2();
                delay(500);
                mt2.Stepmotor_Closed_Control42(STG_a,  2100);
                delay(1000);
            }
            
        }
        else if(jtpt_ball < 2)
        {
            mt.Stepmotor_Closed_Control50(FORWARD, 720);
            delay(2500);
        }
        else{delay(20);}
        clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据

        if(jtpt_ball == 2 && is_stop == 0)
        {
            is_stop =1;
            mt.Stepmotor_Closed_Control(MOVE_LEFT,3500);
        }

        /*-------------------------------------------第4个孔位---------------------------------------*/
        if(jtpt_ball < 2 && jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_2();   //3s
            delay(2500);
            jtpt_ball ++ ;
            if(jtpt_ball==1){IC_read_adjust(1,4);}    
            if(jtpt_ball==2){IC_read_adjust(1,3);}   
            Arm.jtpy_1_to_2();
            delay(1500);
            if(jtpt_ball < 2)
            {
                mt.Stepmotor_Closed_Control50(FORWARD, 820);
                Arm.jtpy_hold_3();
                delay(2500);
                Arm.jtpy_hold_3_fast();  //0.4s
                mt2.Stepmotor_Closed_Control42(STG_a,  2100);
                delay(500);
            } 
        }
        else if(jtpt_ball < 2)
        {
            mt.Stepmotor_Closed_Control50(FORWARD,820);
            delay(500);
            Arm.jtpy_hold_3_fast();  //0.4s
            delay(1000);
        }
        else{delay(20);}
        clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据

        if(jtpt_ball == 2 && is_stop == 0)
        {
            is_stop =1;
            mt.Stepmotor_Closed_Control(MOVE_LEFT,3500);
        }
        else if(jtpt_ball < 2 && is_stop == 0)
        {
            clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据
            mt.adjust_yaw_pid(x_yaw);
            delay(200);
            Ultrasound_ms_1(1500 ,5.5);
        }
    
} 

void jtpy_catch_3_B()  
{
    /*-------------------------------------第3-1个孔位---------------------------------- */
    if(jtpt_ball < 2 && jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_3();   //3s
            delay(2500);
            jtpt_ball ++ ;
            if(jtpt_ball==1){IC_read_adjust(1,4);}    
            if(jtpt_ball==2){IC_read_adjust(1,3);}   
            Arm.jtpy_1_to_2();
            delay(1500);
            if(jtpt_ball < 2)
            {
                mt.Stepmotor_Closed_Control50(FORWARD, 720);
                Arm.jtpy_hold_3();
                delay(2500);
                mt2.Stepmotor_Closed_Control42(STG_a,  2100);
                delay(1000);
            } 
        }
        else if(jtpt_ball < 2)
        {
            mt.Stepmotor_Closed_Control50(FORWARD, 720);
            delay(1000);
        }
        else{delay(20);}
        clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据

        if(jtpt_ball == 2 && is_stop == 0)
        {
            is_stop =1;
            mt.Stepmotor_Closed_Control(MOVE_LEFT,3500);
        }

        /*-------------------------------------第3-2个孔位---------------------------------- */
    if(jtpt_ball < 2 && jtpt_color() == ball_color)
        {
            Arm.jtpy_catch_3();   //3s
            delay(2500);
            jtpt_ball ++ ;
            if(jtpt_ball==1){IC_read_adjust(1,4);}    
            if(jtpt_ball==2){IC_read_adjust(1,3);}   
            Arm.jtpy_1_to_2();
            delay(1500);
            clearSerialBuffer();  // 清空串口缓冲区，避免重复读取相同数据
        }
        
       if( is_stop == 0)
        {
            is_stop =1;
            mt.Stepmotor_Closed_Control(MOVE_LEFT,3500);
            //Arm.jtpy_catch_2();
            delay(500);
            if(jtpt_ball==0){mt2.Stepmotor_Closed_Control42(STG_a,  2100);}
        }
}


void STEP3_B()    //去第三个十字架
{
    mt.adjust_yaw_pid(x_yaw-1);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(BACKWARD,3000);


    while(wt.getline() == 0)  //到达十字架纵线
    {
        mt.Stepmotor_Run_Control(BACKWARD);
    }
    mt.adjust_yaw_pid(x_yaw-1);    //陀螺仪校准
    delay(20);
    mt.Stepmotor_Closed_Control50(BACKWARD, 80);
    wt.adjust_line_pid();      //对准白线
    delay(20);

    while(true)                    //如果检测到十字架，停车
    {
        mt.Stepmotor_Closed_Control(BACKWARD, 50);
        if(wt.getcount() == 1)
        {
            delay(20);
            if(wt.getcount() == 1)      
            {
                delay(20);
                break;
            }
        }
    }
    mt.adjust_yaw_pid(x_yaw-2);    //陀螺仪校准
    delay(20);
    
}

void STEP4_B()    //去第四个十字架
{
    mt.Stepmotor_Closed_Control(BACKWARD, 9000);
    STEP2_B();
}


void STEP5_B()       //去第5个十字架
{
    mt.Stepmotor_Closed_Control(FORWARD, 3000);
    mt.Stepmotor_Closed_Control(MOVE_LEFT, 8800); 

    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);

    while(wt.getline() == 0)  //到达十字架纵线
    {
        mt.Stepmotor_Run_Control(BACKWARD);
    }

    mt.Stepmotor_Closed_Control(BACKWARD, 100);
    wt.adjust_line_pid();      //对准白线

    while(true)                    //如果检测到十字架，停车
    {
        mt.Stepmotor_Closed_Control50(BACKWARD, 50);
        if(wt.getcount() == 1)
        {
            delay(20);
            if(wt.getcount() == 1)      
            {
                delay(20);
                break;
            }
        }
    }
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);
    mt.Stepmotor_Closed_Control(FORWARD, 1900);
    
}

void Close_to_ypj_B()
{
    mt.Stepmotor_Closed_Control(MOVE_LEFT, 2880);
    delay(200);
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准 
}




void BIZHANG_B()
{
    Arm.to_zero();
    mt.Stepmotor_Closed_Control(MOVE_RIGHT, 2600);
    delay(200);
    mt2.Stepmotor_Closed_Control42(STG_a,  4200);         

    int is_jiancedao = 0;
    while(is_jiancedao == 0)
    {
        if(oa.isObjectDetected() == false)
        {
            mt.Stepmotor_Run_Control(BACKWARD);
        }
        else
        {
            is_jiancedao = 1;
            // Serial.println("有障碍物");
            mt.Stepmotor_Closed_Control(BACKWARD,1000);
            mt.Stepmotor_Closed_Control(MOVE_RIGHT, 3500);
            mt.Stepmotor_Closed_Control(FORWARD,6000);
            mt.Stepmotor_Closed_Control(MOVE_LEFT, 3500);
        }
    }
    mt.adjust_yaw_pid(x_yaw);
    while(wt.getline() == 0)  //到达十字架纵线
    {
        mt.Stepmotor_Run_Control(BACKWARD);
    }
}

void STEP6_B()   //去第6个十字架
{
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(FORWARD, 6000);

    while(wt.getline() == 0)  //到达十字架纵线
    {
        mt.Stepmotor_Run_Control(FORWARD);
    }
    mt.Stepmotor_Closed_Control_42(FORWARD, 100);
    mt.adjust_yaw_pid(x_yaw-1);    //陀螺仪校准

    wt.adjust_line_pid();
    delay(20);
    while(true)                    //如果检测到十字架，停车
    {
        mt.Stepmotor_Closed_Control50(FORWARD, 50);
        if(wt.getcount() == 1)
        {
            delay(20);
            if(wt.getcount() == 1)      
            {
                delay(20);
                break;
            }
        }
    }
    mt.adjust_yaw_pid(x_yaw-1);    //陀螺仪校准
    delay(20);
}

void Close_to_ck_B()
{
    mt2.Stepmotor_Closed_Control42(STG_a,  2100);
    mt.Stepmotor_Closed_Control(FORWARD, 5900);     //直走   //5850(预赛)
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(MOVE_LEFT, 1500); 
    Ultrasound_ms_2(5000 ,14);
}

void Dao_Duo_B()
{
    Arm.look();    delay(2000);
    ltck_location();           //视觉2s
    delay(500);
    Arm.to_zero();
    delay(2200);
    Ultrasound_ms_2(2000 ,13.2);
    int p=0;                   //已经抓了几个球
    int row[4]={-1};           //row[第几个球] = 在第几行


    /*---------------------------------第2列----------------------------------*/
    //100 
    //001 
    //010
    if(dao_duo[0][1]==1)
        {   Arm.dd_catch3(); p++;  delay(2400); row[p]=1;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a, 2100);}}
    if(dao_duo[1][1]==1)
        {   Arm.dd_catch2();  p++;  delay(2400); row[p]=2;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a, 2100);}}
    if(dao_duo[2][1]==1)
        {   Arm.dd_catch1(); p++;  delay(2400);  row[p]=3;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a, 2100);}}

    /*---------------------------------第1列----------------------------------*/
    mt.Stepmotor_Closed_Control50(BACKWARD,1420);
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Ultrasound_ms_2(2000 ,13.4);

    if(dao_duo[0][0]==1)
        {   Arm.dd_catch3(); p++;  delay(2400);   row[p]=1;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a,  2100);}}
    if(dao_duo[1][0]==1)
        {   Arm.dd_catch2(); p++;  delay(2400);  row[p]=2;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a,  2100);}}
    if(dao_duo[2][0]==1)
        {   Arm.dd_catch1(); p++;  delay(2400);  row[p]=3;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a,  2100);}}

    /*---------------------------------第3列----------------------------------*/
    mt.Stepmotor_Closed_Control50(FORWARD,2640);
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Ultrasound_ms_2(2000 ,13.4);
    

    if(dao_duo[0][2]==1)
        {   Arm.dd_catch3(); p++;  delay(2400);   row[p]=1;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a,  2100);}}
    if(dao_duo[1][2]==1)
        {   Arm.dd_catch2(); p++;  delay(2400);   row[p]=2;
            if(p<3){ Arm.dd_put(); delay(2800); }
            if(p<2){mt2.Stepmotor_Closed_Control42(STG_a,  2100);}}
    if(dao_duo[2][2]==1)
        {   Arm.dd_catch1(); p++;  delay(2800);  row[p]=3; }

    
     /*---------------------------------第4列----------------------------------*/
    mt.Stepmotor_Closed_Control50(FORWARD,1300);
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Ultrasound_ms_2(2000 ,13);

    if(row[3]==1){delay(500); Arm.ck_1_put_3(); delay(2400);}
    if(row[3]==2){delay(500); Arm.ck_1_put_2(); delay(2400);}
    if(row[3]==3){delay(500); Arm.ck_1_put_1(); delay(2400);}

    if(row[2]==1){Arm.ck_1_catch_2(); delay(2300); Arm.ck_1_put_3(); delay(2400);}
    if(row[2]==2){Arm.ck_1_catch_2(); delay(2300); Arm.ck_1_put_2(); delay(2400);}
    if(row[2]==3){Arm.ck_1_catch_2(); delay(2300); Arm.ck_1_put_1(); delay(2400);}

    mt2.Stepmotor_Closed_Control42(STG_b,  2100);
    if(row[1]==1){Arm.ck_1_catch_2(); delay(2300); Arm.ck_1_put_3(); delay(2400);}
    if(row[1]==2){Arm.ck_1_catch_2(); delay(2300); Arm.ck_1_put_2(); delay(2400);}
    if(row[1]==3){Arm.ck_1_catch_2(); delay(2300); Arm.ck_1_put_1(); delay(2400);}

    mt2.Stepmotor_Closed_Control42(STG_b,  2100);
}

void  put_in_ck_B()
{
    clearSerialBuffer_gm65();
    mt.Stepmotor_Closed_Control50(BACKWARD,1460);
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Ultrasound_ms_2(2000 , QR_chaosheng);

    QR_result[0]=gm65.readQRCode();
     if(QR_result[0]==0)
     {QR_result[0]=2;}

     Ultrasound_ms_2(2000 ,13.4);

/*-------------------------------------第3列----------------------------------------*/
    find_ball(33);
    if(m==0 && is_ball==1){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_3();     delay(2400);}
    if(m==1 && is_ball==1){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_3();     delay(2400);}

    find_ball(23);
    if(m==0 && is_ball==1){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_2();     delay(2400);}
    if(m==1 && is_ball==1){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_2();     delay(2400);}

    find_ball(10 + QR_result[0]);
    if(m==0 && is_ball==1 && QR_result[0]!=0){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_1();     delay(2400);}
    if(m==1 && is_ball==1 && QR_result[0]!=0){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_1();     delay(2400);}

    clearSerialBuffer_gm65();
    mt.Stepmotor_Closed_Control50(BACKWARD,1360);
    delay(1000);
    

/*-------------------------------------第2列-----------------------------------------*/
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Ultrasound_ms_2(2000 , QR_chaosheng);

     QR_result[1]=gm65.readQRCode();
     if(QR_result[1]==0)
     {QR_result[1]=1;}

    delay(200);
    Ultrasound_ms_2(2000 ,13.4);

    find_ball(32);
    if(m==0 && is_ball==1){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_3();     delay(2400);}
    if(m==1 && is_ball==1){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_3();     delay(2400);}

    find_ball(22);
    if(m==0 && is_ball==1){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_2();     delay(2400);}
    if(m==1 && is_ball==1){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_2();     delay(2400);}

    find_ball(10 + QR_result[1]); 
    if(m==0 && is_ball==1 && QR_result[1]!=0){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_1();     delay(2400);}
    if(m==1 && is_ball==1 && QR_result[1]!=0){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_1();     delay(2400);}

    clearSerialBuffer_gm65();
    mt.Stepmotor_Closed_Control50(BACKWARD,1360);
    delay(1000);


/*-------------------------------------第1列-----------------------------------------*/
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Ultrasound_ms_2(2000 , QR_chaosheng);
    

    QR_result[2]=gm65.readQRCode();
     if(QR_result[2]==0)
     {QR_result[2]=3;}
    delay(200);

    Ultrasound_ms_2(2000 ,13.4);
    
    find_ball(31);
    if(m==0 && is_ball==1){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_3();     delay(2400);}
    if(m==1 && is_ball==1){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_3();     delay(2400);}

    find_ball(21);
    if(m==0 && is_ball==1){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_2();     delay(2400);}
    if(m==1 && is_ball==1){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_2();     delay(2400);}

    find_ball(10 + QR_result[2]);
    if(m==0 && is_ball==1 && QR_result[2]!=0){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.ck_1_put_1();     delay(2400);}
    if(m==1 && is_ball==1 && QR_result[2]!=0){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.ck_1_put_1();     delay(2400);}
}


void STEP7_B()   //去第7个十字架
{

    mt.Stepmotor_Closed_Control(MOVE_RIGHT , 2100);
    delay(200) ;
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准

   // mt.Stepmotor_Closed_Control(FORWARD, 4000);


    /*----------------------step2----------------------*/

    while(wt.getline() == 0)  //到达十字架纵线
    {
        mt.Stepmotor_Run_Control(FORWARD);
    }
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(FORWARD,150);
    delay(20);
    wt.adjust_line_pid();
    delay(20);
    while(true)                    //如果检测到十字架，停车
    {
        mt.Stepmotor_Closed_Control(FORWARD, 50);
        if(wt.getcount() == 1)
        {
            delay(20);
            if(wt.getcount() == 1)      
            {
                delay(20);
                break;
            } 
        }
    }
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);
}


void Back_jtpt_B()
{
    mt.Stepmotor_Closed_Control(FORWARD, 3000);
    mt.Stepmotor_Closed_Control(MOVE_RIGHT, 8800); 

    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);

    while(wt.getline() == 0)  //到达十字架纵线
    {
        mt.Stepmotor_Run_Control(BACKWARD);
    }

    mt.Stepmotor_Closed_Control(BACKWARD, 100);
    wt.adjust_line_pid();      //对准白线

    while(true)                    //如果检测到十字架，停车
    {
        mt.Stepmotor_Closed_Control50(BACKWARD, 50);
        if(wt.getcount() == 1)
        {
            delay(20);
            if(wt.getcount() == 1)      
            {
                delay(20);
                break;
            }
        }
    }
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);
/*--------------close to 接替平台---------------------------------*/
    mt.Stepmotor_Closed_Control(BACKWARD, 2100);     //直走2000
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);
    mt.Stepmotor_Closed_Control(MOVE_RIGHT, 2400);  //右移
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    delay(20);  
    Ultrasound_ms_1(3000 ,15);  
/*----------------------------------------------------------------*/

    find_ball(14);
    if(m==0 && is_ball==1){is_ball=0; Arm.ck_1_catch_1();   delay(2800);   Arm.grq();     delay(5200);}
    if(m==1 && is_ball==1){is_ball=0; Arm.ck_1_catch_2();   delay(2400);   Arm.grq();     delay(5200);}
}





void BACK_HOME_B()   //回家
{
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    Arm.curl();
/*--------------------------------------盘子归中------------------------------*/
    int ball=Matrix[0][2];
    if(ball > 0) {find_ball(ball);}
    else         {ball=Matrix[1][2];}
    if(ball > 0) {find_ball(ball);}
/*----------------------------------------------------------------------------*/
    
    mt.Stepmotor_Closed_Control(MOVE_LEFT, 4000);
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(FORWARD, 7100);
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(FORWARD, 7100);
    mt.adjust_yaw_pid(x_yaw);    //陀螺仪校准
    mt.Stepmotor_Closed_Control(MOVE_LEFT, 4000);
}

