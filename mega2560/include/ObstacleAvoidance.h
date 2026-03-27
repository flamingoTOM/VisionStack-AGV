#ifndef OBSTACLEAVOIDANCE_H
#define OBSTACLEAVOIDANCE_H

class ObstacleAvoidance {
public:
    ObstacleAvoidance(int sensorPin);
    void begin();
    bool isObjectDetected(); // 返回布尔值，指示是否检测到物体
private:
    int sensorPin; // 光电传感器引脚
};

#endif // OBSTACLEAVOIDANCE_H
