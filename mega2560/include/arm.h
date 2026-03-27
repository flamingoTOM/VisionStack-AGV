#ifndef ARM_H
#define ARM_H

#include <Arduino.h>
#include <LobotServoController.h>
#define armmotor Serial1

class robotarm
{
public:
    LobotServoController *ServoController_p;

    robotarm(HardwareSerial &A);
    ~robotarm();

/*---------------------------------------------仓库-----------------------------------------------*/

void jtpy_hold_1();
void jtpy_catch_1();
void jtpy_hold_2();
void jtpy_hold_2_fast();
void jtpy_catch_2();

void jtpy_hold_3();
void jtpy_hold_3_fast();
void jtpy_catch_3();

void jtpy_1_to_2();
void curl();

/*---------------------------------------------圆盘机-----------------------------------------------*/

void ypj_hold();
void ypj_catch();
void ypj_put_1();
void ypj_put_2();


/*---------------------------------------------立体仓库-----------------------------------------------*/
void to_zero();
void ck_1_catch_1();       
void ck_1_catch_2();       


void ck_1_put_1();
void ck_1_put_2();
void ck_1_put_3();

void cc() ;
void look();

void dd_catch1();
void dd_catch2();
void dd_catch3();
void dd_put(); 

void grq();
      
};

extern robotarm Arm;

#endif
