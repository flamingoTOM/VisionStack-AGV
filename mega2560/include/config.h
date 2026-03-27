#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <JY901.h>
#include <work.h>
#include <motor.h>
#include <white_detect.h>
#include <HC_SR04.h>
#include <Servo.h>
#include <StepperMotor.h>
#include <MsTimer2.h>
#include <math.h>
#include <oled.h>
#include <GM65.h>
#include <ICCard.h>
#include <feedback.h>
#include <arm.h>
#include <TimerOne.h>
#include <LOBOTSERVOCONTROLLER.h>
#include <TJC.h>
#include <ObstacleAvoidance.h>







extern motor mt;
extern motor mt2;
extern robotarm Arm;
extern OLED oled;
extern StepperMotor Stepper3;
extern StepperMotor Stepper4;
extern HC_SR04 sensor;
extern HC_SR04 sensor2;
// extern Servo  myservo;
// extern Servo  myservo1;
// extern SoftwareSerial MV;
extern GM65 gm65;
extern SoftwareSerial TJC;
extern ICCard icCard;
extern ObstacleAvoidance oa;




void Task1();
void Task2();
void get_yaw(double *ex_yaw);
void HWT101();
void SendEnd();
void TJC_Show(int x,int y);


#endif