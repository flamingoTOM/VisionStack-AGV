#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "math.h"
#include "feedback.h"

extern double current_error_yaw;
extern double global_yaw;

//42闭环步进电机引脚定义
#define   Emm42_1_En_Pin     22   // the number of the Emm42_En_pin
#define   Emm42_1_Pul_Pin    4    // the number of the Emm42_1_Pul_Pin
#define   Emm42_1_Dir_Pin    26   // the number of the Emm42_Dir_pin

#define   Emm42_2_En_Pin     23   // the number of the Emm42_En_pin
#define   Emm42_2_Pul_Pin    5    // the number of the Emm42_2_Pul_Pin
#define   Emm42_2_Dir_Pin    27   // the number of the Emm42_Dir_pin

#define   Emm42_3_En_Pin     24   // the number of the Emm42_En_pin
#define   Emm42_3_Pul_Pin    6    // the number of the Emm42_3_Pul_Pin
#define   Emm42_3_Dir_Pin    28   // the number of the Emm42_Dir_pin

#define   Emm42_4_En_Pin     25   // the number of the Emm42_En_pin
#define   Emm42_4_Pul_Pin    7    // the number of the Emm42_4_Pul_Pin
#define   Emm42_4_Dir_Pin    29   // the number of the Emm42_Dir_pin

#define   Emm42_5_En_Pin     34   // the number of the Emm42_En_pin
#define   Emm42_5_Pul_Pin    35   // the number of the Emm42_4_Pul_Pin
#define   Emm42_5_Dir_Pin    44   // the number of the Emm42_Dir_pin

#define servoPin  46
#define servoPin1 47

// #define   Emm42_6_En_Pin     36   // the number of the Emm42_En_pin
// #define   Emm42_6_Pul_Pin    37   // the number of the Emm42_4_Pul_Pin
// #define   Emm42_6_Dir_Pin    45   // the number of the Emm42_Dir_pin

#define   DIR                16   //步进电机细分
#define   Angle_18           1    //步进电机1.8步距角
#define   Angle_09           0    //步进电机0.9步距角

//电机调试定义
#define   STOP              'S'//停止
#define   FORWARD           'F'//前进
#define   BACKWARD          'B'//后退
#define   MOVE_LEFT         'L'//左移
#define   MOVE_RIGHT        'R'//右移
#define   TURN_LEFT         'Q'//左转
#define   TURN_RIGHT        'P'//右转
#define   LEFT_FORWARD      'J'//左前
#define   RIGHT_FORWARD     'K'//右前
#define   LEFT_BACKWARD     'M'//左后
#define   RIGHT_BACKWARD    'N'//右后
#define   STG_a           'x'//5步
#define   STG_b           'y'//10步
// #define   STP_a        'z'//6步
// #define   STP_b            'a'//12步


//定义函数
#define range(x, a, b)		(min(max(x, a), b))
//交换a,b
#define exchange(a, b, tmp) (tmp=a, a=b, b=tmp)
//取绝对值
#define myabs(x)			((x<0)? -x:x)

typedef struct
{
    int dir_A;
    int dir_B;
    int dir_C;
    int dir_D;
}DIR_X;// 规定PID极性

typedef struct
{
	int limit;		    //输出限幅
	float target;		//目标输出量
	float feedback;		//实际输出量	
	int Kp;	
	int Ki;	
	int Kd;	
	int e_0;			//当前误差
	int e_1;			//上一次误差
	int e_2;			//上上次误差
}PID;


typedef struct
{
    float SetYaw;     // 设定值
    float ActualYaw;  // 实际值
    float err;        // 当前误差
    float err_next;   // 上一次误差
    float err_last;   // 上上一次误差
    float kp, ki, kd;
    float integral;
}PIDD;

class motor
{
private:
    unsigned long motor_previousMillis1; // m1
    unsigned long motor_period1;
    unsigned long motor_previousMillis2; // m2
    unsigned long motor_period2;
    unsigned long motor_previousMillis3; // m3
    unsigned long motor_period3;
    unsigned long motor_previousMillis4; // m4
    unsigned long motor_period4;
    unsigned long motor_previousMillis5; // m4
    unsigned long motor_period5;
    unsigned long motor_previousMillis6; // m4
    unsigned long motor_period6;

    unsigned int TargetStepTime = 3;   // 最大速度，每步所需的毫秒数

    unsigned int SpeedDownStep = 100;  // 减速步数
    unsigned int SpeedUpStep = 100;    // 加速步数

    int delta_speed = 1;   
    int adjust_Step_time = 20000;  // 调整pid速度
    int adjust_speed = 1;

    unsigned int StepTime = 200;        // 非pid前进速度
    unsigned int acc = 15000;           // 加速度，步方/秒
    float step_angle = 1.8;             // 步距，每一步角度
    int dir = 16;                        // 细分

    char move_cmd = STOP; // 目标方向
    int theta = 0;        // 车轮旋转目标角度

    int pidStepTime = 800;              // pid前进速度
    int pid_current_Step = 0;                // pid前进距离

    int motor_step1_pid = 0;
    int motor_step2_pid = 0;
    int motor_step3_pid = 0;
    int motor_step4_pid = 0;

    unsigned int time;

    int pid2_Interrupt_flag=0;

    int info1;
    int info2;
    int info3;

    PIDD adjust_yaw = {0, 0, 0, 0, 0, 2000, 10,50};   // 角度调整pid
    //直行PID
    PID straight_pid = 
    {
        limit : 2000,
        target : 0,
        feedback : 0, 
        Kp : 500,
        Ki : 10,
        Kd : 50,
        e_0 : 0,
        e_1 : 0,
        e_2 : 0,
    };
    PID cross_pid = //
    {
        limit : 400,
        target : 0,
        feedback : 0, 
        Kp : 100,
        Ki : 40,
        Kd : 5,
        e_0 : 0,
        e_1 : 0,
        e_2 : 0,
    };
    PID adjust_pid = 
    {
        limit : 2000,
        target : 0,
        feedback : 0, 
        Kp : 20000,
        Ki : 100,
        Kd : 500,
        e_0 : 0,
        e_1 : 0,
        e_2 : 0,
    };
    void Stepmotor_dirction(); // 方向使能
    int pid_Caclulate(PID* pid);//pid运算
    int pid_Feedback(float expected_angle,float current_angle,PID* pid);//pid反馈

public:
    motor(unsigned int TargetStepTime, unsigned int acc, int dir, float step_angle);//设定最大速度:每步所需的毫秒数、加速度:步方/秒、细分、步距
    int pid1_Interrupt_flag = 0;
    int pid_Calculate(PID *pid);

    void reset_motor_parameters();
    // 可控接口

    void Stepmotor_Run_Control(char command); // 恒定速度运动，控制运动方向
    
    void Stepmotor_para_set(unsigned int TargetStepTime, unsigned int acc, int dir, float step_angle); // 设定最大速度、加速度、细分、步距

    void Stepmotor_Run(char command , unsigned int stepTime); // 恒定速度运动，控制运动方向、速度

    void Stepmotor_Same_Control(char command, int theta, int speed); // 恒定速度运动，控制运动方向、旋转角度、速度

    void Stepmotor_Closed_Control(char command, int theta); // 梯形变速运动，控制运动方向、旋转角度
    
    void Stepmotor_Closed1_Control(char command, int theta);

    void Stepmotor_Closed_Control21(char command, int theta);//右前

    void Stepmotor_Closed_Control12(char command, int theta);//左前

    void Stepmotor_pid_getpara1(char command, int pidStep, int TotalStep);// pid中断读取

    void Stepmotor_pid_calculate1(); // pid控制参数设置

    void Stepmotor_pidRun1(); // pid控制运动循环

    void Stepmotor_pid1_moveto(char command, int total_move_step, int pidStep); //pid 集成函数

    void Stepmotor_pid_getpara2(char command, int pidStep);// pid中断读取

    void Stepmotor_pid_calculate2(); // pid控制参数设置

    void Stepmotor_pidRun2(); // pid控制运动循环

    void Stepmotor_rangeRun(char command, int average_speed, float delta1, float delta2, float delta3);

    void adjust_yaw_pid(float target_yaw);

    int pid_calculate(float target_yaw, PIDD *pid);

    void print_para();

    void Stepmotor_pid2_moveto(char command, int total_move_step, int pidStep); //pid 集成函数

    void Stepmotor_Trapezoid_Control5(char command, int theta); // 梯形变速运动，控制运动方向、旋转角度
    
    void Stepmotor_Closed_Control42(char command, int theta);

    void StepMotor_General_Control(char command, uint16_t steptime);

    void servopulse(int angle);//定义一个脉冲函数

    void Stepmotor_Closed_Control50(char command, int theta);

    void Stepmotor_Running_low_speed_Control(char command);

    void  Stepmotor_Closed_Control_42(char command, int theta);
};

unsigned int myrange(unsigned int amt, unsigned int low, unsigned int high);
int cut(int x);
#endif