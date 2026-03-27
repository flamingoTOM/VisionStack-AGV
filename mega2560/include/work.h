#ifndef WORK_H
#define WORK_H

#include "config.h"

extern int x_yaw;


/*--------------------------其他函数--------------------------------*/

void read_and_display(int x,int y);
void IC_read_adjust(int a ,int b);
void BIZHANG();

/*---------------------------视觉-----------------------------------*/

int jtpt_color();
int ypj_color();
void ltck_location();
void clearSerialBuffer();


/*---------------------------阶梯平台（前向）-------------------------------*/

void JTPY_A();
void STEP1_A();void STEP2_A();void Close_to_jtpy_A();void jtpy_catch_1_A();void jtpy_catch_2_A();void jtpy_catch_3_A();

void JTPY_B();
void STEP1_B();void STEP2_B();void Close_to_jtpy_B();void jtpy_catch_1_B();void jtpy_catch_2_B();void jtpy_catch_3_B();



/*--------------------------圆盘机（前向）--------------------------------*/
void YPJ_A();
void STEP3_A();void STEP4_A();void STEP5_A();void Close_to_ypj_A();

void YPJ_B();
void STEP3_B();void STEP4_B();void STEP5_B();void Close_to_ypj_B();

void Ultrasound_ms_1(int time_ms ,int far);
void Ultrasound_ms_2(int time_ms ,int far);
void YPJ_catch_ball();



/*---------------------------仓库（前向）-------------------------------*/
void LTCK_A();

void STEP6_A(); void Close_to_ck_A();void BIZHANG_A();void Dao_Duo_A();void put_in_ck_A();
void STEP7_A(); void Back_jtpt_A();  void BACK_HOME_A();

void LTCK_B();
void STEP6_B(); void Close_to_ck_B();void BIZHANG_B();void Dao_Duo_B();void put_in_ck_B();
void STEP7_B(); void Back_jtpt_B();  void BACK_HOME_B();


void find_ball(int ball_index);
void clearSerialBuffer_gm65();





#endif