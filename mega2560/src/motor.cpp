#include <motor.h>

motor::motor(unsigned int TargetStepTime, unsigned int acc, int dir, float step_angle)
{
    this->TargetStepTime = TargetStepTime; // 最大速度，每步所需的毫秒数
    this->acc = acc;                       // 加速度
    this->step_angle = step_angle;         // 步距
    this->dir = dir;                       // 细分

    pinMode(Emm42_1_En_Pin, OUTPUT);
    pinMode(Emm42_1_Pul_Pin, OUTPUT);
    pinMode(Emm42_1_Dir_Pin, OUTPUT);

    pinMode(Emm42_2_En_Pin, OUTPUT);
    pinMode(Emm42_2_Pul_Pin, OUTPUT);
    pinMode(Emm42_2_Dir_Pin, OUTPUT);

    pinMode(Emm42_3_En_Pin, OUTPUT);
    pinMode(Emm42_3_Pul_Pin, OUTPUT);
    pinMode(Emm42_3_Dir_Pin, OUTPUT);

    pinMode(Emm42_4_En_Pin, OUTPUT);
    pinMode(Emm42_4_Pul_Pin, OUTPUT);
    pinMode(Emm42_4_Dir_Pin, OUTPUT);

    pinMode(Emm42_5_En_Pin, OUTPUT);
    pinMode(Emm42_5_Pul_Pin, OUTPUT);
    pinMode(Emm42_5_Dir_Pin, OUTPUT);

    // pinMode(Emm42_6_En_Pin, OUTPUT);
    // pinMode(Emm42_6_Pul_Pin, OUTPUT);
    // pinMode(Emm42_6_Dir_Pin, OUTPUT);

    this->move_cmd = STOP;
    Stepmotor_dirction();
}

void motor::Stepmotor_dirction()
{
    /*
    //m1      m2\\



    \\m3      m4//
    */
    switch (this->move_cmd)
    {
    case STOP:
        digitalWrite(Emm42_1_En_Pin, LOW);
        digitalWrite(Emm42_2_En_Pin, LOW);
        digitalWrite(Emm42_3_En_Pin, LOW);
        digitalWrite(Emm42_4_En_Pin, LOW);

        break;
    case FORWARD:
        digitalWrite(Emm42_1_En_Pin, HIGH);
        digitalWrite(Emm42_2_En_Pin, HIGH);
        digitalWrite(Emm42_3_En_Pin, HIGH);
        digitalWrite(Emm42_4_En_Pin, HIGH);

        digitalWrite(Emm42_1_Dir_Pin, LOW);
        digitalWrite(Emm42_2_Dir_Pin, HIGH);
        digitalWrite(Emm42_3_Dir_Pin, LOW);
        digitalWrite(Emm42_4_Dir_Pin, HIGH);
        break;
    case BACKWARD:
        digitalWrite(Emm42_1_En_Pin, HIGH);
        digitalWrite(Emm42_2_En_Pin, HIGH);
        digitalWrite(Emm42_3_En_Pin, HIGH);
        digitalWrite(Emm42_4_En_Pin, HIGH);

        digitalWrite(Emm42_1_Dir_Pin, HIGH);
        digitalWrite(Emm42_2_Dir_Pin, LOW);
        digitalWrite(Emm42_3_Dir_Pin, HIGH);
        digitalWrite(Emm42_4_Dir_Pin, LOW);

        break;
    case MOVE_RIGHT:
        digitalWrite(Emm42_1_En_Pin, HIGH);
        digitalWrite(Emm42_2_En_Pin, HIGH);
        digitalWrite(Emm42_3_En_Pin, HIGH);
        digitalWrite(Emm42_4_En_Pin, HIGH);

        digitalWrite(Emm42_1_Dir_Pin, LOW);
        digitalWrite(Emm42_2_Dir_Pin, LOW);
        digitalWrite(Emm42_3_Dir_Pin, HIGH);
        digitalWrite(Emm42_4_Dir_Pin, HIGH);
        break;
    case MOVE_LEFT:
        digitalWrite(Emm42_1_En_Pin, HIGH);
        digitalWrite(Emm42_2_En_Pin, HIGH);
        digitalWrite(Emm42_3_En_Pin, HIGH);
        digitalWrite(Emm42_4_En_Pin, HIGH);

        digitalWrite(Emm42_1_Dir_Pin, HIGH);
        digitalWrite(Emm42_2_Dir_Pin, HIGH);
        digitalWrite(Emm42_3_Dir_Pin, LOW);
        digitalWrite(Emm42_4_Dir_Pin, LOW);

        break;
    case TURN_RIGHT:
        digitalWrite(Emm42_1_En_Pin, HIGH);
        digitalWrite(Emm42_2_En_Pin, HIGH);
        digitalWrite(Emm42_3_En_Pin, HIGH);
        digitalWrite(Emm42_4_En_Pin, HIGH);

        digitalWrite(Emm42_1_Dir_Pin, LOW);
        digitalWrite(Emm42_2_Dir_Pin, LOW);
        digitalWrite(Emm42_3_Dir_Pin, LOW);
        digitalWrite(Emm42_4_Dir_Pin, LOW);

        break;
    case TURN_LEFT:
        digitalWrite(Emm42_1_En_Pin, HIGH);
        digitalWrite(Emm42_2_En_Pin, HIGH);
        digitalWrite(Emm42_3_En_Pin, HIGH);
        digitalWrite(Emm42_4_En_Pin, HIGH);

        digitalWrite(Emm42_1_Dir_Pin, HIGH);
        digitalWrite(Emm42_2_Dir_Pin, HIGH);
        digitalWrite(Emm42_3_Dir_Pin, HIGH);
        digitalWrite(Emm42_4_Dir_Pin, HIGH);
        break;
    case RIGHT_FORWARD:
        digitalWrite(Emm42_1_En_Pin, HIGH);
        digitalWrite(Emm42_2_En_Pin, HIGH);
        digitalWrite(Emm42_3_En_Pin, HIGH);
        digitalWrite(Emm42_4_En_Pin, HIGH);

        digitalWrite(Emm42_1_Dir_Pin, LOW);
        digitalWrite(Emm42_4_Dir_Pin, HIGH);
        break;
    case LEFT_FORWARD:
        digitalWrite(Emm42_1_En_Pin, HIGH);
        digitalWrite(Emm42_2_En_Pin, HIGH);
        digitalWrite(Emm42_3_En_Pin, HIGH);
        digitalWrite(Emm42_4_En_Pin, HIGH);

        digitalWrite(Emm42_2_Dir_Pin, HIGH);
        digitalWrite(Emm42_3_Dir_Pin, LOW);
        break;
    case RIGHT_BACKWARD:
        digitalWrite(Emm42_1_En_Pin, HIGH);
        digitalWrite(Emm42_2_En_Pin, HIGH);
        digitalWrite(Emm42_3_En_Pin, HIGH);
        digitalWrite(Emm42_4_En_Pin, HIGH);

        digitalWrite(Emm42_2_Dir_Pin, LOW);
        digitalWrite(Emm42_3_Dir_Pin, LOW);
        break;
    case LEFT_BACKWARD:
        digitalWrite(Emm42_1_En_Pin, HIGH);
        digitalWrite(Emm42_2_En_Pin, HIGH);
        digitalWrite(Emm42_3_En_Pin, HIGH);
        digitalWrite(Emm42_4_En_Pin, HIGH);

        digitalWrite(Emm42_1_Dir_Pin, HIGH);
        digitalWrite(Emm42_4_Dir_Pin, LOW);
    case STG_a:
        digitalWrite(Emm42_5_En_Pin, HIGH);
        digitalWrite(Emm42_5_Dir_Pin, HIGH);
        break;
    case STG_b:
        digitalWrite(Emm42_5_En_Pin, HIGH);
        digitalWrite(Emm42_5_Dir_Pin, LOW);
        break;
    // case STP_a:
    //     digitalWrite(Emm42_6_En_Pin, LOW);
    //     digitalWrite(Emm42_6_Dir_Pin, HIGH);
    //     digitalWrite(Emm42_6_Pul_Pin, LOW);
    //     break;
    // case STP_b:
    //     digitalWrite(Emm42_6_En_Pin, LOW);
    //     digitalWrite(Emm42_6_Dir_Pin, LOW);
    //            digitalWrite(Emm42_6_Pul_Pin, LOW);
    //     break;
    default:
        break;
    }
}

void motor::Stepmotor_Run_Control(char command)
{
    this->move_cmd = command;
    Stepmotor_dirction();
    motor_period1 = motor_period2 = motor_period3 = motor_period4 = 300;
    unsigned long currentMillis = micros(); // store the current time
    if (currentMillis - this->motor_previousMillis1 >= this->motor_period1)
    {                                                // check if passed
        this->motor_previousMillis1 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_1_Pul_Pin, 1);
        delayMicroseconds(20);
        digitalWrite(Emm42_1_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis2 >= this->motor_period2)
    {                                                // check if passed
        this->motor_previousMillis2 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_2_Pul_Pin, 1);
        delayMicroseconds(20);
        digitalWrite(Emm42_2_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis3 >= this->motor_period3)
    {                                                // check if passed
        this->motor_previousMillis3 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_3_Pul_Pin, 1);
        delayMicroseconds(20);
        digitalWrite(Emm42_3_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis4 >= this->motor_period4)
    {                                                // check if passed
        this->motor_previousMillis4 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_4_Pul_Pin, 1);
        delayMicroseconds(20);
        digitalWrite(Emm42_4_Pul_Pin, 0);
    }
}


void motor::Stepmotor_Running_low_speed_Control(char command)
{
    this->move_cmd = command;
    Stepmotor_dirction();
    motor_period1 = motor_period2 = motor_period3 = motor_period4 = 300;
    unsigned long currentMillis = micros(); // store the current time
    if (currentMillis - this->motor_previousMillis1 >= this->motor_period1)
    {                                                // check if passed
        this->motor_previousMillis1 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_1_Pul_Pin, 1);
        delayMicroseconds(5);
        digitalWrite(Emm42_1_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis2 >= this->motor_period2)
    {                                                // check if passed
        this->motor_previousMillis2 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_2_Pul_Pin, 1);
        delayMicroseconds(5);
        digitalWrite(Emm42_2_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis3 >= this->motor_period3)
    {                                                // check if passed
        this->motor_previousMillis3 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_3_Pul_Pin, 1);
        delayMicroseconds(5);
        digitalWrite(Emm42_3_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis4 >= this->motor_period4)
    {                                                // check if passed
        this->motor_previousMillis4 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_4_Pul_Pin, 1);
        delayMicroseconds(5);
        digitalWrite(Emm42_4_Pul_Pin, 0);
    }
}

void motor::Stepmotor_Closed_Control42(char command, int theta)
{
    this->move_cmd = command;
    this->theta = theta;
    Stepmotor_dirction();
    unsigned int TotalStep;
    unsigned int SpeedUpStep;
    unsigned int SpeedDownStep;

    TotalStep = (this->theta / this->step_angle) * this->dir;

    double v0 = 1000000.0 / this->TargetStepTime; // 步/秒
    double Stepmin = (pow(v0, 2.0) / (2 * this->acc));

    if (TotalStep / 2 <= Stepmin)
    {
        SpeedUpStep = (unsigned int)(TotalStep / 2);
        SpeedDownStep = SpeedUpStep;
    }
    else
    {
        SpeedUpStep = (unsigned int)Stepmin;
        SpeedDownStep = TotalStep - (unsigned int)Stepmin;
    }

    for (unsigned int CurrentStep = 0; CurrentStep < TotalStep; CurrentStep++)
    {
        double v;
        if ((0 <= CurrentStep) && (CurrentStep < SpeedUpStep))
        {
            v = sqrt(double(acc * 2.0 * CurrentStep));
        }
        else if ((SpeedUpStep <= CurrentStep) && (CurrentStep <= SpeedDownStep))
        {
            v = v0;
        }
        else if ((SpeedDownStep < CurrentStep) && (CurrentStep <= TotalStep))
        {
            v = sqrt(double(acc * 2.0 * (TotalStep - CurrentStep))); // 步/秒
        }
        unsigned int CurrentStepTime = 1000000.0 / v;

        CurrentStepTime = ((CurrentStepTime <= this->TargetStepTime) ? this->TargetStepTime : CurrentStepTime); // 限幅
        motor_period5 = CurrentStepTime;
        unsigned long currentMillis = micros(); // store the current time
        if (currentMillis - this->motor_previousMillis1 >= this->motor_period1)
        {                                                // check if passed
            this->motor_previousMillis1 = currentMillis; // save the last time you toggle the level
            digitalWrite(Emm42_5_Pul_Pin, 1);
            delayMicroseconds(200);
            digitalWrite(Emm42_5_Pul_Pin, 0);
        }
    }
    digitalWrite(Emm42_5_En_Pin, HIGH);
}

// //57闭环步进电机控制平稳加速
void motor:: Stepmotor_Closed_Control_42(char command, int theta)
{
    this->move_cmd = command;
    this->theta = theta;
    Stepmotor_dirction();
    unsigned int TotalStep;
    unsigned int SpeedUpStep;
    unsigned int SpeedDownStep;

    TotalStep = (this->theta / this->step_angle) * this->dir;

    double v0 = 1000000.0 / this->TargetStepTime; // 步/秒
    double Stepmin = (pow(v0, 2.0) / (2 * this->acc));

    if (TotalStep / 2 <= Stepmin)
    {
        SpeedUpStep = (unsigned int)(TotalStep / 2);
        SpeedDownStep = SpeedUpStep;
    }
    else
    {
        SpeedUpStep = (unsigned int)Stepmin;
        SpeedDownStep = TotalStep - (unsigned int)Stepmin;
    }

    for (unsigned int CurrentStep = 0; CurrentStep < TotalStep; CurrentStep++)
    {
        double v;
        if ((0 <= CurrentStep) && (CurrentStep < SpeedUpStep))
        {
            v = sqrt(double(acc * 2.0 * CurrentStep));
        }
        else if ((SpeedUpStep <= CurrentStep) && (CurrentStep <= SpeedDownStep))
        {
            v = v0;
        }
        else if ((SpeedDownStep < CurrentStep) && (CurrentStep <= TotalStep))
        {
            v = sqrt(double(acc * 2.0 * (TotalStep - CurrentStep))); // 步/秒
        }
        unsigned int CurrentStepTime = 1000000.0 / v;

        CurrentStepTime = ((CurrentStepTime <= this->TargetStepTime) ? this->TargetStepTime : CurrentStepTime); // 限幅
        motor_period6 = CurrentStepTime;
        unsigned long currentMillis = micros(); // store the current time
        if (currentMillis - this->motor_previousMillis1 >= this->motor_period1)
        {                                                // check if passed
            this->motor_previousMillis1 = currentMillis; // save the last time you toggle the level
            digitalWrite(Emm42_5_Pul_Pin, 1);
            delayMicroseconds(50);
            digitalWrite(Emm42_5_Pul_Pin, 0);
        }

    }
    digitalWrite(Emm42_5_En_Pin, LOW);

}

// 42闭环步进电机控制平稳加速(50)
void motor::Stepmotor_Closed_Control50(char command, int theta)
{
    this->move_cmd = command;
    this->theta = theta;
    Stepmotor_dirction();
    unsigned int TotalStep;
    unsigned int SpeedUpStep;
    unsigned int SpeedDownStep;

    TotalStep = (this->theta / this->step_angle) * this->dir;

    double v0 = 1000000.0 / this->TargetStepTime; // 步/秒
    double Stepmin = (pow(v0, 2.0) / (2 * this->acc));

    if (TotalStep / 2 <= Stepmin)
    {
        SpeedUpStep = (unsigned int)(TotalStep / 2);
        SpeedDownStep = SpeedUpStep;
    }
    else
    {
        SpeedUpStep = (unsigned int)Stepmin;
        SpeedDownStep = TotalStep - (unsigned int)Stepmin;
    }
    for (unsigned int CurrentStep = 0; CurrentStep < TotalStep; CurrentStep++)
    {
        double v;
        if ((0 <= CurrentStep) && (CurrentStep < SpeedUpStep))
        {
            v = sqrt(double(acc * 2.0 * CurrentStep));
        }
        else if ((SpeedUpStep <= CurrentStep) && (CurrentStep <= SpeedDownStep))
        {
            v = v0;
        }
        else if ((SpeedDownStep < CurrentStep) && (CurrentStep <= TotalStep))
        {
            v = sqrt(double(acc * 2.0 * (TotalStep - CurrentStep))); // 步/秒
        }
        unsigned int CurrentStepTime = 1000000.0 / v;

        CurrentStepTime = ((CurrentStepTime <= this->TargetStepTime) ? this->TargetStepTime : CurrentStepTime); // 限幅
        motor_period1 = motor_period2 = motor_period3 = motor_period4 = CurrentStepTime;
        unsigned long currentMillis = micros(); // store the current time
        if (currentMillis - this->motor_previousMillis1 >= this->motor_period1)
        {                                                // check if passed
            this->motor_previousMillis1 = currentMillis; // save the last time you toggle the level
            digitalWrite(Emm42_1_Pul_Pin, 1);
            delayMicroseconds(100);
            digitalWrite(Emm42_1_Pul_Pin, 0);
        }
        if (currentMillis - this->motor_previousMillis2 >= this->motor_period2)
        {                                                // check if passed
            this->motor_previousMillis2 = currentMillis; // save the last time you toggle the level
            digitalWrite(Emm42_2_Pul_Pin, 1);
            delayMicroseconds(100);
            digitalWrite(Emm42_2_Pul_Pin, 0);
        }
        if (currentMillis - this->motor_previousMillis3 >= this->motor_period3)
        {                                                // check if passed
            this->motor_previousMillis3 = currentMillis; // save the last time you toggle the level
            digitalWrite(Emm42_3_Pul_Pin, 1);
            delayMicroseconds(100);
            digitalWrite(Emm42_3_Pul_Pin, 0);   
        }
        if (currentMillis - this->motor_previousMillis4 >= this->motor_period4)
        {                                                // check if passed
            this->motor_previousMillis4 = currentMillis; // save the last time you toggle the level
            digitalWrite(Emm42_4_Pul_Pin, 1);
            delayMicroseconds(100);
            digitalWrite(Emm42_4_Pul_Pin, 0);
        }
    }
    digitalWrite(Emm42_1_En_Pin, HIGH);
    digitalWrite(Emm42_2_En_Pin, HIGH);
    digitalWrite(Emm42_3_En_Pin, HIGH);
    digitalWrite(Emm42_4_En_Pin, HIGH);
}

// 42闭环步进电机控制平稳加速5
void motor::  Stepmotor_Closed_Control(char command, int theta)
{
    this->move_cmd = command;
    this->theta = theta;
    Stepmotor_dirction();
    unsigned int TotalStep;
    unsigned int SpeedUpStep;
    unsigned int SpeedDownStep;

    TotalStep = (this->theta / this->step_angle) * this->dir;

    double v0 = 1000000.0 / this->TargetStepTime; // 步/秒
    double Stepmin = (pow(v0, 2.0) / (2 * this->acc));

    if (TotalStep / 2 <= Stepmin)
    {
        SpeedUpStep = (unsigned int)(TotalStep / 2);
        SpeedDownStep = SpeedUpStep;
    }
    else
    {
        SpeedUpStep = (unsigned int)Stepmin;
        SpeedDownStep = TotalStep - (unsigned int)Stepmin;
    }
    for (unsigned int CurrentStep = 0; CurrentStep < TotalStep; CurrentStep++)
    {
        double v;
        if ((0 <= CurrentStep) && (CurrentStep < SpeedUpStep))
        {
            v = sqrt(double(acc * 2.0 * CurrentStep));
        }
        else if ((SpeedUpStep <= CurrentStep) && (CurrentStep <= SpeedDownStep))
        {
            v = v0;
        }
        else if ((SpeedDownStep < CurrentStep) && (CurrentStep <= TotalStep))
        {
            v = sqrt(double(acc * 2.0 * (TotalStep - CurrentStep))); // 步/秒
        }
        unsigned int CurrentStepTime = 1000000.0 / v;

        CurrentStepTime = ((CurrentStepTime <= this->TargetStepTime) ? this->TargetStepTime : CurrentStepTime); // 限幅
        motor_period1 = motor_period2 = motor_period3 = motor_period4 = CurrentStepTime;
        unsigned long currentMillis = micros(); // store the current time
        if (currentMillis - this->motor_previousMillis1 >= this->motor_period1)
        {                                                // check if passed
            this->motor_previousMillis1 = currentMillis; // save the last time you toggle the level
            digitalWrite(Emm42_1_Pul_Pin, 1);
            delayMicroseconds(3);
            digitalWrite(Emm42_1_Pul_Pin, 0);
        }
        if (currentMillis - this->motor_previousMillis2 >= this->motor_period2)
        {                                                // check if passed
            this->motor_previousMillis2 = currentMillis; // save the last time you toggle the level
            digitalWrite(Emm42_2_Pul_Pin, 1);
            delayMicroseconds(3);
            digitalWrite(Emm42_2_Pul_Pin, 0);
        }
        if (currentMillis - this->motor_previousMillis3 >= this->motor_period3)
        {                                                // check if passed
            this->motor_previousMillis3 = currentMillis; // save the last time you toggle the level
            digitalWrite(Emm42_3_Pul_Pin, 1);
            delayMicroseconds(3);
            digitalWrite(Emm42_3_Pul_Pin, 0);
        }
        if (currentMillis - this->motor_previousMillis4 >= this->motor_period4)
        {                                                // check if passed
            this->motor_previousMillis4 = currentMillis; // save the last time you toggle the level
            digitalWrite(Emm42_4_Pul_Pin, 1);
            delayMicroseconds(3);
            digitalWrite(Emm42_4_Pul_Pin, 0);
        }
    }
    digitalWrite(Emm42_1_En_Pin, HIGH);
    digitalWrite(Emm42_2_En_Pin, HIGH);
    digitalWrite(Emm42_3_En_Pin, HIGH);
    digitalWrite(Emm42_4_En_Pin, HIGH);
}

//控制42步进电机 斜向梯形稳定运动
void motor::Stepmotor_Closed_Control21(char command, int theta)
{
    this->move_cmd = command;
    this->theta = theta;
    Stepmotor_dirction();
    unsigned int TotalStep;
    unsigned int SpeedUpStep;
    unsigned int SpeedDownStep;

    TotalStep = (this->theta / this->step_angle) * this->dir;

    double v0 = 1000000.0 / this->TargetStepTime; // 步/秒
    double Stepmin = (pow(v0, 2.0) / (2 * this->acc));

    if (TotalStep / 2 <= Stepmin)
    {
        SpeedUpStep = (unsigned int)(TotalStep / 2);
        SpeedDownStep = SpeedUpStep;
    }
    else
    {
        SpeedUpStep = (unsigned int)Stepmin;
        SpeedDownStep = TotalStep - (unsigned int)Stepmin;
    }

    for (unsigned int CurrentStep = 0; CurrentStep < TotalStep; CurrentStep++)
    {
        double v;
        if ((0 <= CurrentStep) && (CurrentStep < SpeedUpStep))
        {
            v = sqrt(double(acc * 2.0 * CurrentStep));
        }
        else if ((SpeedUpStep <= CurrentStep) && (CurrentStep <= SpeedDownStep))
        {
            v = v0;
        }
        else if ((SpeedDownStep < CurrentStep) && (CurrentStep <= TotalStep))
        {
            v = sqrt(double(acc * 2.0 * (TotalStep - CurrentStep))); // 步/秒
        }
        unsigned int CurrentStepTime = 500000.0 / v;

        CurrentStepTime = ((CurrentStepTime <= this->TargetStepTime) ? this->TargetStepTime : CurrentStepTime); // 限幅
        motor_period1 = motor_period2 = motor_period3 = motor_period4 = CurrentStepTime;
        delayMicroseconds(CurrentStepTime);
        digitalWrite(Emm42_1_Pul_Pin, 1);
        digitalWrite(Emm42_2_Pul_Pin, 0);
        digitalWrite(Emm42_3_Pul_Pin, 0);
        digitalWrite(Emm42_4_Pul_Pin, 1);
        delayMicroseconds(CurrentStepTime);
        digitalWrite(Emm42_1_Pul_Pin, 0);
        digitalWrite(Emm42_2_Pul_Pin, 0);
        digitalWrite(Emm42_3_Pul_Pin, 0);
        digitalWrite(Emm42_4_Pul_Pin, 0);
    }
}

void motor::Stepmotor_Closed_Control12(char command, int theta)
{
    this->move_cmd = command;
    this->theta = theta;
    Stepmotor_dirction();
    unsigned int TotalStep;
    unsigned int SpeedUpStep;
    unsigned int SpeedDownStep;

    TotalStep = (this->theta / this->step_angle) * this->dir;

    double v0 = 1000000.0 / this->TargetStepTime; // 步/秒
    double Stepmin = (pow(v0, 2.0) / (2 * this->acc));

    if (TotalStep / 2 <= Stepmin)
    {
        SpeedUpStep = (unsigned int)(TotalStep / 2);
        SpeedDownStep = SpeedUpStep;
    }
    else
    {
        SpeedUpStep = (unsigned int)Stepmin;
        SpeedDownStep = TotalStep - (unsigned int)Stepmin;
    }

    for (unsigned int CurrentStep = 0; CurrentStep < TotalStep; CurrentStep++)
    {
        double v;
        if ((0 <= CurrentStep) && (CurrentStep < SpeedUpStep))
        {
            v = sqrt(double(acc * 2.0 * CurrentStep));
        }
        else if ((SpeedUpStep <= CurrentStep) && (CurrentStep <= SpeedDownStep))
        {
            v = v0;
        }
        else if ((SpeedDownStep < CurrentStep) && (CurrentStep <= TotalStep))
        {
            v = sqrt(double(acc * 2.0 * (TotalStep - CurrentStep))); // 步/秒
        }
        unsigned int CurrentStepTime = 1000000.0 / v;

        CurrentStepTime = ((CurrentStepTime <= this->TargetStepTime) ? this->TargetStepTime : CurrentStepTime); // 限幅
        motor_period1 = motor_period2 = motor_period3 = motor_period4 = CurrentStepTime;
        delayMicroseconds(CurrentStepTime);
        digitalWrite(Emm42_1_Pul_Pin, 0);
        digitalWrite(Emm42_2_Pul_Pin, 1);
        digitalWrite(Emm42_3_Pul_Pin, 1);
        digitalWrite(Emm42_4_Pul_Pin, 0);
        delayMicroseconds(CurrentStepTime);
        digitalWrite(Emm42_1_Pul_Pin, 0);
        digitalWrite(Emm42_2_Pul_Pin, 0);
        digitalWrite(Emm42_3_Pul_Pin, 0);
        digitalWrite(Emm42_4_Pul_Pin, 0);
    }
}

void motor::Stepmotor_Closed1_Control(char command, int theta)
{
    this->move_cmd = command;
    this->theta = theta;
    Stepmotor_dirction();
    unsigned int TotalStep;
    unsigned int SpeedUpStep;
    unsigned int SpeedDownStep;

    TotalStep = (this->theta / this->step_angle) * this->dir;

    double v0 = 1000000.0 / this->TargetStepTime; // 步/秒
    double Stepmin = (pow(v0, 2.0) / (2 * this->acc));

    if (TotalStep / 2 <= Stepmin)
    {
        SpeedUpStep = (unsigned int)(TotalStep / 2);
        SpeedDownStep = SpeedUpStep;
    }
    else
    {
        SpeedUpStep = (unsigned int)Stepmin;
        SpeedDownStep = TotalStep - (unsigned int)Stepmin;
    }

    for (unsigned int CurrentStep = 0; CurrentStep < TotalStep; CurrentStep++)
    {
        double v;
        if ((0 <= CurrentStep) && (CurrentStep < SpeedUpStep))
        {
            v = sqrt(double(acc * 2.0 * CurrentStep));
        }
        else if ((SpeedUpStep <= CurrentStep) && (CurrentStep <= SpeedDownStep))
        {
            v = v0;
        }
        else if ((SpeedDownStep < CurrentStep) && (CurrentStep <= TotalStep))
        {
            v = sqrt(double(acc * 2.0 * (TotalStep - CurrentStep))); // 步/秒
        }
        unsigned int CurrentStepTime = 1000000.0 / v;

        CurrentStepTime = ((CurrentStepTime <= this->TargetStepTime) ? this->TargetStepTime : CurrentStepTime); // 限幅
        motor_period1 = motor_period2 = motor_period3 = motor_period4 = CurrentStepTime;
        delayMicroseconds(CurrentStepTime);
        digitalWrite(Emm42_1_Pul_Pin, 1);
        digitalWrite(Emm42_2_Pul_Pin, 1);
        digitalWrite(Emm42_3_Pul_Pin, 1);
        digitalWrite(Emm42_4_Pul_Pin, 1);
        delayMicroseconds(CurrentStepTime);
        digitalWrite(Emm42_1_Pul_Pin, 0);
        digitalWrite(Emm42_2_Pul_Pin, 0);
        digitalWrite(Emm42_3_Pul_Pin, 0);
        digitalWrite(Emm42_4_Pul_Pin, 0);

        if (Serial.available() > 0)
        {
            Serial.println("motor stop!");
            Serial.println("STOP              'S'\nFORWARD           'F'\nBACKWARD          'B'\nMOVE_LEFT         'L'\nMOVE_RIGHT        'R'\nTURN_LEFT         'Q'\nTURN_RIGHT        'P'");
            Serial.println("press:cmd + circle + '#'");
            break;
        }
    }
}

// 42闭环步进电机控制斜向走

// 42闭环步进电机, 恒定速度运动，控制运动方向、速度

void motor::Stepmotor_Same_Control(char command, int theta, int speed)
{
    this->move_cmd = command;
    this->theta = theta;
    Stepmotor_dirction();
    unsigned int TotalStep;

    TotalStep = (this->theta / this->step_angle) * this->dir;

    double v0 = speed; // 步/秒
    double Stepmin = (pow(v0, 2.0) / (2 * this->acc));

    if (TotalStep / 2 <= Stepmin)
    {
        SpeedUpStep = (unsigned int)(TotalStep / 2);
        SpeedDownStep = SpeedUpStep;
    }
    else
    {
        SpeedUpStep = (unsigned int)Stepmin;
        SpeedDownStep = TotalStep - (unsigned int)Stepmin;
    }

    for (unsigned int CurrentStep = 0; CurrentStep < TotalStep; CurrentStep++)
    {
        double v;
        if ((0 <= CurrentStep) && (CurrentStep < SpeedUpStep))
        {
            v = sqrt(double(acc * 2.0 * CurrentStep));
        }
        else if ((SpeedUpStep <= CurrentStep) && (CurrentStep <= SpeedDownStep))
        {
            v = v0;
        }
        else if ((SpeedDownStep < CurrentStep) && (CurrentStep <= TotalStep))
        {
            v = sqrt(double(acc * 2.0 * (TotalStep - CurrentStep))); // 步/秒
        }
        unsigned int CurrentStepTime = 1000000.0 / v;

        CurrentStepTime = ((CurrentStepTime <= this->TargetStepTime) ? this->TargetStepTime : CurrentStepTime); // 限幅
        motor_period1 = motor_period2 = motor_period3 = motor_period4 = CurrentStepTime;
        unsigned long currentMillis = micros(); // store the current time
        if (currentMillis - this->motor_previousMillis1 >= this->motor_period1)
        {                                                // check if passed
            this->motor_previousMillis1 = currentMillis; // save the last time you toggle the level
            digitalWrite(Emm42_1_Pul_Pin, 1);
            delayMicroseconds(50);
            digitalWrite(Emm42_1_Pul_Pin, 0);
        }
        if (currentMillis - this->motor_previousMillis2 >= this->motor_period2)
        {                                                // check if passed
            this->motor_previousMillis2 = currentMillis; // save the last time you toggle the level
            digitalWrite(Emm42_2_Pul_Pin, 1);
            delayMicroseconds(50);
            digitalWrite(Emm42_2_Pul_Pin, 0);
        }
        if (currentMillis - this->motor_previousMillis3 >= this->motor_period3)
        {                                                // check if passed
            this->motor_previousMillis3 = currentMillis; // save the last time you toggle the level
            digitalWrite(Emm42_3_Pul_Pin, 1);
            delayMicroseconds(50);
            digitalWrite(Emm42_3_Pul_Pin, 0);
        }
        if (currentMillis - this->motor_previousMillis4 >= this->motor_period4)
        {                                                // check if passed
            this->motor_previousMillis4 = currentMillis; // save the last time you toggle the level
            digitalWrite(Emm42_4_Pul_Pin, 1);
            delayMicroseconds(50);
            digitalWrite(Emm42_4_Pul_Pin, 0);
        }
    }
    digitalWrite(Emm42_1_En_Pin, LOW);
    digitalWrite(Emm42_2_En_Pin, LOW);
    digitalWrite(Emm42_3_En_Pin, LOW);
    digitalWrite(Emm42_4_En_Pin, LOW);
}

void motor::Stepmotor_Run(char command, unsigned int stepTime)
{
    this->move_cmd = command;
    this->StepTime = stepTime;
    Stepmotor_dirction();
    motor_period1 = motor_period2 = motor_period3 = motor_period4 = StepTime;
    unsigned long currentMillis = micros(); // store the current time
    if (currentMillis - this->motor_previousMillis1 >= this->motor_period1)
    {                                                // check if passed
        this->motor_previousMillis1 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_1_Pul_Pin, 1);
        delayMicroseconds(10);
        digitalWrite(Emm42_1_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis2 >= this->motor_period2)
    {                                                // check if passed
        this->motor_previousMillis2 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_2_Pul_Pin, 1);
        delayMicroseconds(10);
        digitalWrite(Emm42_2_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis3 >= this->motor_period3)
    {                                                // check if passed
        this->motor_previousMillis3 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_3_Pul_Pin, 1);
        delayMicroseconds(10);
        digitalWrite(Emm42_3_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis4 >= this->motor_period4)
    {                                                // check if passed
        this->motor_previousMillis4 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_4_Pul_Pin, 1);
        delayMicroseconds(10);
        digitalWrite(Emm42_4_Pul_Pin, 0);
    }
}

void motor::Stepmotor_pid_calculate1()
{
    int delta;
    switch (this->move_cmd)
    {
    case FORWARD:
        delta = pid_Feedback(0, current_error_yaw, &straight_pid);
        this->motor_period1 = range(cut(pidStepTime + delta), 4, 20000);
        this->motor_period2 = range(cut(pidStepTime - delta), 4, 20000);
        this->motor_period3 = range(cut(pidStepTime + delta), 4, 20000);
        this->motor_period4 = range(cut(pidStepTime - delta), 4, 20000);
        break;
    case BACKWARD:
        delta = pid_Feedback(0, current_error_yaw, &straight_pid);
        this->motor_period1 = range(cut(pidStepTime - delta), 4, 20000);
        this->motor_period2 = range(cut(pidStepTime + delta), 4, 20000);
        this->motor_period3 = range(cut(pidStepTime - delta), 4, 20000);
        this->motor_period4 = range(cut(pidStepTime + delta), 4, 20000);
        break;
    case MOVE_LEFT:
        delta = pid_Feedback(0, current_error_yaw, &cross_pid);
        this->motor_period1 = range(cut(pidStepTime + delta), 4, 20000);
        this->motor_period2 = range(cut(pidStepTime + delta), 4, 20000);
        this->motor_period3 = range(cut(pidStepTime - delta), 4, 20000);
        this->motor_period4 = range(cut(pidStepTime - delta), 4, 20000);
        break;
    case MOVE_RIGHT:
        delta = pid_Feedback(0, current_error_yaw, &cross_pid);
        this->motor_period1 = range(cut(pidStepTime - delta), 4, 20000);
        this->motor_period2 = range(cut(pidStepTime - delta), 4, 20000);
        this->motor_period3 = range(cut(pidStepTime + delta), 4, 20000);
        this->motor_period4 = range(cut(pidStepTime + delta), 4, 20000);
        break;
    default:
        break;
    }
}

void motor::Stepmotor_pid_getpara1(char command, int pidStep, int TotalStep)
{
    this->move_cmd = command;
    this->pidStepTime = pidStep;
}

void motor::Stepmotor_pidRun1()
{
    Stepmotor_dirction();
    unsigned long currentMillis = micros(); // store the current time
    if (currentMillis - this->motor_previousMillis1 >= this->motor_period1)
    {                                                // check if passed
        this->motor_previousMillis1 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_1_Pul_Pin, !digitalRead(Emm42_1_Pul_Pin));
        this->motor_step1_pid++;
    }
    if (currentMillis - this->motor_previousMillis2 >= this->motor_period2)
    {                                                // check if passed
        this->motor_previousMillis2 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_2_Pul_Pin, !digitalRead(Emm42_2_Pul_Pin));
        this->motor_step2_pid++;
    }
    if (currentMillis - this->motor_previousMillis3 >= this->motor_period3)
    {                                                // check if passed
        this->motor_previousMillis3 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_3_Pul_Pin, !digitalRead(Emm42_3_Pul_Pin));
        this->motor_step3_pid++;
    }
    if (currentMillis - this->motor_previousMillis4 >= this->motor_period4)
    {                                                // check if passed
        this->motor_previousMillis4 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_4_Pul_Pin, !digitalRead(Emm42_4_Pul_Pin));
        this->motor_step4_pid++;
    }
    this->pid_current_Step = (int)((this->motor_step1_pid + this->motor_step2_pid + this->motor_step3_pid + this->motor_step4_pid) / 4);
}

void motor::Stepmotor_pid1_moveto(char command, int total_move_step, int pidStep)
{

    this->motor_step1_pid = this->motor_step2_pid = this->motor_step3_pid = this->motor_step4_pid = 0;
    this->motor_period1 = this->motor_period2 = this->motor_period3 = this->motor_period4 = 50000;
    this->Stepmotor_pid_getpara1(command, pidStep, total_move_step);
    this->pid1_Interrupt_flag = 1;
    do
    {
        this->Stepmotor_pidRun1();
    } while (!(this->pid_current_Step >= total_move_step));
    this->pid1_Interrupt_flag = 0;
    this->pid_current_Step = 0;
}
void motor::Stepmotor_pid_getpara2(char command, int pidStep)
{
    this->move_cmd = command;
    this->pidStepTime = pidStep;
}
void motor::Stepmotor_pid_calculate2()
{
    int average_speed = (int)(1000000 / this->pidStepTime);
    Stepmotor_dirction();
    switch (this->move_cmd)
    {
    case FORWARD:
        this->delta_speed = abs(pid_Feedback(0, current_error_yaw, &straight_pid));
        break;
    case BACKWARD:
        this->delta_speed = abs(pid_Feedback(0, current_error_yaw, &straight_pid));
        break;
    case MOVE_LEFT:
        this->delta_speed = abs(pid_Feedback(0, current_error_yaw, &cross_pid));
        break;
    case MOVE_RIGHT:
        this->delta_speed = abs(pid_Feedback(0, current_error_yaw, &cross_pid));
        break;
    default:
        break;
    }
    int add_speed;
    int subtract_speed;
    if (current_error_yaw > 0)
    {
        add_speed = average_speed + delta_speed;
        subtract_speed = average_speed - delta_speed;
        add_speed = range(add_speed, 30, 5000);           // average_speed + delta_speed
        subtract_speed = range(subtract_speed, 30, 5000); // average_speed - delta_speed
    }
    else
    {
        add_speed = average_speed - delta_speed;
        subtract_speed = average_speed + delta_speed;
        add_speed = range(add_speed, 30, 5000);           // average_speed - delta_speed
        subtract_speed = range(subtract_speed, 30, 5000); // average_speed + delta_speed
    }
    int add_Steptime = (int)(1000000 / add_speed);
    int subtract_Steptime = (int)(1000000 / subtract_speed);
    this->info1 = add_Steptime;
    this->info2 = add_speed;
    this->info3 = average_speed;
    switch (this->move_cmd)
    {
    case FORWARD:
        this->motor_period1 = add_Steptime;
        this->motor_period2 = subtract_Steptime;
        this->motor_period3 = add_Steptime;
        this->motor_period4 = subtract_Steptime;
        break;
    case BACKWARD:
        this->motor_period1 = subtract_Steptime;
        this->motor_period2 = add_Steptime;
        this->motor_period3 = subtract_Steptime;
        this->motor_period4 = add_Steptime;
        break;
    case MOVE_LEFT:
        this->motor_period1 = add_Steptime;
        this->motor_period2 = add_Steptime;
        this->motor_period3 = subtract_Steptime;
        this->motor_period4 = subtract_Steptime;
        break;
    case MOVE_RIGHT:
        this->motor_period1 = subtract_Steptime;
        this->motor_period2 = subtract_Steptime;
        this->motor_period3 = add_Steptime;
        this->motor_period4 = add_Steptime;
        break;
    default:
        break;
    }
}
void motor::Stepmotor_pidRun2()
{
    unsigned long currentMillis = micros(); // store the current time
    if (currentMillis - this->motor_previousMillis1 >= this->motor_period1)
    {                                                // check if passed
        this->motor_previousMillis1 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_1_Pul_Pin, 1);
        delayMicroseconds(10);
        digitalWrite(Emm42_1_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis2 >= this->motor_period2)
    {                                                // check if passed
        this->motor_previousMillis2 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_2_Pul_Pin, 1);
        delayMicroseconds(10);
        digitalWrite(Emm42_2_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis3 >= this->motor_period3)
    {                                                // check if passed
        this->motor_previousMillis3 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_3_Pul_Pin, 1);
        delayMicroseconds(10);
        digitalWrite(Emm42_3_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis4 >= this->motor_period4)
    {                                                // check if passed
        this->motor_previousMillis4 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_4_Pul_Pin, 1);
        delayMicroseconds(10);
        digitalWrite(Emm42_4_Pul_Pin, 0);
    }
}

void motor::StepMotor_General_Control(char command, uint16_t steptime)
{
    move_cmd = command;
    //StepTime = steptime;
    Stepmotor_dirction();
    uint32_t currentMillions = micros();
    if (currentMillions - motor_previousMillis1 >= steptime)
    {
        motor_previousMillis1 = currentMillions;
        digitalWrite(Emm42_1_Pul_Pin, 1);
        delayMicroseconds(10);
        digitalWrite(Emm42_1_Pul_Pin, 0);
    }
    if (currentMillions - motor_previousMillis2 >= steptime)
    {
        motor_previousMillis2 = currentMillions;
        digitalWrite(Emm42_2_Pul_Pin, 1);
        delayMicroseconds(10);
        digitalWrite(Emm42_2_Pul_Pin, 0);
    }
    if (currentMillions - motor_previousMillis3 >= steptime)
    {
        motor_previousMillis3 = currentMillions;
        digitalWrite(Emm42_3_Pul_Pin, 1);
        delayMicroseconds(10);
        digitalWrite(Emm42_3_Pul_Pin, 0);
    }
    if (currentMillions - motor_previousMillis4 >= steptime)
    {
        motor_previousMillis4 = currentMillions;
        digitalWrite(Emm42_4_Pul_Pin, 1);
        delayMicroseconds(10);
        digitalWrite(Emm42_4_Pul_Pin, 0);
    }
}
void motor::Stepmotor_rangeRun(char command, int average_speed, float delta1, float delta2, float delta3)
{
    this->move_cmd = command;
    Stepmotor_dirction();
    int Step_High;
    int Step_Low;
    if (abs(current_error_yaw) > 5)
    {
        Step_High = (int)average_speed * (1 - delta3);
        Step_Low = (int)average_speed * (1 + delta3);
    }
    else if (abs(current_error_yaw) <= 5 && abs(current_error_yaw) > 2)
    {
        Step_High = (int)average_speed * (1 - delta2);
        Step_Low = (int)average_speed * (1 + delta2);
    }
    else if (abs(current_error_yaw) <= 2 && abs(current_error_yaw) >= 1)
    {
        Step_High = (int)average_speed * (1 - delta1);
        Step_Low = (int)average_speed * (1 + delta1);
    }
    else
    {
        Step_High = Step_Low = (int)average_speed;
    }
    switch (command)
    {
    case FORWARD:
        if (current_error_yaw > 0)
        {
            this->motor_period1 = Step_High;
            this->motor_period2 = Step_Low;
            this->motor_period3 = Step_High;
            this->motor_period4 = Step_Low;
        }
        else
        {
            this->motor_period1 = Step_Low;
            this->motor_period2 = Step_High;
            this->motor_period3 = Step_Low;
            this->motor_period4 = Step_High;
        }
        break;
        break;
    case BACKWARD:
        if (current_error_yaw > 0)
        {
            this->motor_period1 = Step_Low;
            this->motor_period2 = Step_High;
            this->motor_period3 = Step_Low;
            this->motor_period4 = Step_High;
        }
        else
        {
            this->motor_period1 = Step_High;
            this->motor_period2 = Step_Low;
            this->motor_period3 = Step_High;
            this->motor_period4 = Step_Low;
        }
        break;
    case MOVE_LEFT:
        if (current_error_yaw > 0)
        {
            this->motor_period1 = Step_High;
            this->motor_period2 = Step_High;
            this->motor_period3 = Step_Low;
            this->motor_period4 = Step_Low;
        }
        else
        {
            this->motor_period1 = Step_Low;
            this->motor_period2 = Step_Low;
            this->motor_period3 = Step_High;
            this->motor_period4 = Step_High;
        }
        break;
    case MOVE_RIGHT:
        if (current_error_yaw > 0)
        {
            this->motor_period1 = Step_Low;
            this->motor_period2 = Step_Low;
            this->motor_period3 = Step_High;
            this->motor_period4 = Step_High;
        }
        else
        {
            this->motor_period1 = Step_High;
            this->motor_period2 = Step_High;
            this->motor_period3 = Step_Low;
            this->motor_period4 = Step_Low;
        }
        break;
    default:
        break;
    }
    unsigned long currentMillis = micros(); // store the current time
    if (currentMillis - this->motor_previousMillis1 >= this->motor_period1)
    {                                                // check if passed
        this->motor_previousMillis1 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_1_Pul_Pin, 1);
        delayMicroseconds(1);
        digitalWrite(Emm42_1_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis2 >= this->motor_period2)
    {                                                // check if passed
        this->motor_previousMillis2 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_2_Pul_Pin, 1);
        delayMicroseconds(1);
        digitalWrite(Emm42_2_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis3 >= this->motor_period3)
    {                                                // check if passed
        this->motor_previousMillis3 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_3_Pul_Pin, 1);
        delayMicroseconds(1);
        digitalWrite(Emm42_3_Pul_Pin, 0);
    }
    if (currentMillis - this->motor_previousMillis4 >= this->motor_period4)
    {                                                // check if passed
        this->motor_previousMillis4 = currentMillis; // save the last time you toggle the level
        digitalWrite(Emm42_4_Pul_Pin, 1);
        delayMicroseconds(1);
        digitalWrite(Emm42_4_Pul_Pin, 0);
    }
}

//原来的adjust
 /* void motor::adjust_yaw_pid(float target_yaw)
{
    int adjust_speed;
    int adjust_step_time;
    while (true)
    {
        adjust_speed = abs(pid_calculate(target_yaw, &adjust_yaw));
        adjust_speed = range(adjust_speed, 15, 50);
        adjust_step_time = (int)(100000 / adjust_speed);

        //Serial.print("Real Yaw: ");
        //Serial.println(real_yaw);

        //TJC_Show(int x,int y);

        if (real_yaw < target_yaw)
        {
            //Stepmotor_Closed_Control(TURN_LEFT,adjust_step_time);
            StepMotor_General_Control(TURN_LEFT, adjust_step_time);
        }
        else 
        {
            //Stepmotor_Closed_Control(TURN_RIGHT,adjust_step_time);
            StepMotor_General_Control(TURN_RIGHT, adjust_step_time);
        }


        if (abs(real_yaw - target_yaw) < 0.3)
        {
            delay(100);
            if (abs(real_yaw - target_yaw) < 0.3)
            {
                break;
            }
          
           
        }
    }
}  */

/*  void motor::adjust_yaw_pid(float target_yaw)
{

    unsigned long start_time = millis();                // 获取当前的系统时间
    delay(200);
  while (millis() - start_time < 3200)
  {
        float error = real_yaw - target_yaw ;
        float target_theta = error *2 ; 
        char direction_command = (error < 0) ? TURN_LEFT : TURN_RIGHT;
        Stepmotor_Closed_Control(direction_command, abs(target_theta));
        if (abs(error) < 0.2){break;}
        delay(4);
  }
} */

 void motor::adjust_yaw_pid(float target_yaw)
{
    const float Kp = 50; // 比例增益
    const float Ki = 0; // 积分增益
    const float Kd = 20; // 微分增益

    static float integral = 0; // 积分项
    static float last_error = 0; // 上一个误差
    unsigned long start_time = millis();
    
    while (millis() - start_time < 3200)
    {
        float error = real_yaw - target_yaw;
        
        // 计算 PID 输出
        integral += error;
        float derivative = error - last_error;
        float target_theta = Kp * error + Ki * integral + Kd * derivative;
        
        char direction_command = (error < 0) ? TURN_LEFT : TURN_RIGHT;
        Stepmotor_Closed_Control(direction_command, abs(target_theta));
        Serial.print("error = ");
        Serial.print(error);
        Serial.print("     real_raw = ");
        Serial.println(real_yaw);

        
        if (abs(error) < 0.08) {
            break; // 误差在允许范围内，停止调整
        }
        
        last_error = error; // 更新上一个误差
        //delay(2); // 可以考虑使用非阻塞的方法替代
    }
} 













/* int motor::pid_calculate(float target_yaw, PIDD *pid)
{
    int add_control;
    pid->SetYaw = target_yaw;
    pid->ActualYaw = real_yaw;
    pid->err = pid->SetYaw - pid->ActualYaw;
    add_control = pid->kp * (pid->err - pid->err_next) + (pid->ki) * (pid->err) + pid->kd * (pid->err - 2 * pid->err_next + pid->err_last);
    add_control = range(add_control, -2000, 2000);
    pid->err_last = pid->err_next;
    pid->err_next = pid->err;
    return (int)add_control;
} */

int motor::pid_calculate(float target_yaw, PIDD *pid)
{
    int add_control;

    // 设置目标角度
    pid->SetYaw = target_yaw;
    pid->ActualYaw = real_yaw;

    // 计算当前误差
    pid->err = pid->SetYaw - pid->ActualYaw;

    // 积分项累计误差（根据误差大小限制积分累计）
    if (abs(pid->err) > 1.0) {
        pid->integral += pid->err;  // 误差大于1时累积积分
    }
    pid->integral = constrain(pid->integral, -1500, 1500);  // 更严格的积分限制防止过饱和

    // 如果误差足够小（如<0.1），清零积分误差
    if (abs(pid->err) < 0.1) {
        pid->integral = 0;
    }

    // PID控制计算
    add_control = pid->kp * pid->err                             // 比例项
                + pid->ki * pid->integral                        // 积分项
                + pid->kd * (pid->err - 2 * pid->err_next + pid->err_last);  // 微分项

    // 限制控制输出范围，避免过调节
    add_control = constrain(add_control, -2000, 2000);

    // 更新误差历史
    pid->err_last = pid->err_next;
    pid->err_next = pid->err;

    return (int)add_control;
}






//解释这段代码  为什么要这样写
void motor::Stepmotor_pid2_moveto(char command, int total_move_step, int pidStep)
{
    this->motor_step1_pid = this->motor_step2_pid = this->motor_step3_pid = this->motor_step4_pid = 0;
    this->motor_period1 = this->motor_period2 = this->motor_period3 = this->motor_period4 = 50000;
    this->Stepmotor_pid_getpara2(command, pidStep);
    this->pid2_Interrupt_flag = 1;
    do
    {
        this->Stepmotor_pid_calculate2();
        this->Stepmotor_pidRun2();
    } while (!(this->pid_current_Step >= total_move_step));
    this->pid2_Interrupt_flag = 0;
    this->pid_current_Step = 0;
}

// int motor::pid_Caclulate(PID *pid)
// {
//     int out;
//     int ep, ei, ed;

//     pid->e_0 = pid->target - pid->feedback;
//     ep = pid->e_0 - pid->e_1;
//     ei = pid->e_0;
//     ed = pid->e_0 - 2 * pid->e_1 + pid->e_2;
//     out = pid->Kp * ep + pid->Ki * ei + pid->Kd * ed;
//     out = range(out, -pid->limit, pid->limit);
//     pid->e_2 = pid->e_1;
//     pid->e_1 = pid->e_0;
//     return out;
// }

int motor::pid_Feedback(float expected_angle, float current_angle, PID *pid)
{
    pid->target = expected_angle;
    pid->feedback = current_angle;
    int add_control = pid_Caclulate(pid);
    return (int)add_control;
}

int motor::pid_Calculate(PID *pid)
{
    pid->e_0 = pid->target - pid->feedback;
    int ep = pid->e_0 - pid->e_1;
    int ei = pid->e_0;
    int ed = pid->e_0 - 2 * pid->e_1 + pid->e_2;

    int out = pid->Kp * ep + pid->Ki * ei + pid->Kd * ed;
    out = range(out, -pid->limit, pid->limit);

    pid->e_2 = pid->e_1;
    pid->e_1 = pid->e_0;

    return out;
}


unsigned int myrange(unsigned int amt, unsigned int low, unsigned int high)
{
    if (amt < low)
    {
        amt = low;
    }
    else if (amt > high)
    {
        amt = high;
    }
    return amt;
}

int cut(int x)
{
    if (x <= 0)
    {
        return 0;
    }
    else
    {
        return x;
    }
}

void motor::print_para()
{
    Serial.print(motor_period1);
    Serial.print(",");
    Serial.print(motor_period2);
    Serial.print(",");
    Serial.print(motor_period3);
    Serial.print(",");
    Serial.print(motor_period4);
    Serial.print(",");
    Serial.print(current_error_yaw);
    Serial.print(",");
    Serial.println(this->pid_current_Step);
    // Serial.print(",");
    // Serial.print(this->info1);
    // Serial.print(",");
    // Serial.print(this->info2);
    // Serial.print(",");
    // Serial.println(this->info3);
}