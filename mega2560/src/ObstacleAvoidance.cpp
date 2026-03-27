#include <config.h>
#include "ObstacleAvoidance.h"

ObstacleAvoidance::ObstacleAvoidance(int sensorPin) 
    : sensorPin(sensorPin) {}

void ObstacleAvoidance::begin() {
    pinMode(sensorPin, INPUT);  // 设置传感器引脚为输入
    Serial.begin(9600);          // 初始化串口通信
}

bool ObstacleAvoidance::isObjectDetected() {
    int sensorValue = digitalRead(sensorPin); // 读取传感器值
    return (sensorValue ==LOW); // 如果检测到物体，返回 true
}
