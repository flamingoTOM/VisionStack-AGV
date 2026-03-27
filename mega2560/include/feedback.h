#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <Arduino.h>
#include <TimerOne.h>
#include <JY901.h>


extern double real_yaw;
extern double expect_yaw;
extern double current_error_yaw;

void HWT101();
void zl();            //置零函数

#endif 
