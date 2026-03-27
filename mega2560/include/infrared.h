#ifndef INFRARED_H
#define INFRARED_H

#include <IRremote.h>

#define IR_PIN 2 //红外接收器接在2号引脚
#define SENSOR_PIN A0  //红外避障传感器接在A0引脚

void infrared_avoidance();

#endif