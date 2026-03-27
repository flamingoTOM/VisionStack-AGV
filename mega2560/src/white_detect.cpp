#include <white_detect.h>

// 默认构造函数
white_detect::white_detect() 
{
    count = 0;
    detected = false;
}

white_detect::~white_detect()
{
}

void white_detect::digital_read(int *a)     //将灰度传感器的值存在a1、a2、a3、a4、、、、a8中
{
    for (int i = 0; i < 8; i++)
    {
        a[i] = digitalRead(gray1_name[i]);
    }
}

int white_detect::getcount()
{//八个灰度传感器的值全为1时，count加1，表示检测到白线

    digital_read(a);
    if (sum(a, 8) == 8 || sum(a, 8) == 7 || sum(a, 8) == 6)
    {
        count=1;
    }
    return count;
}

int white_detect::getcount1()
{//八个灰度传感器的值全为1时，count加1，表示检测到白线

    digital_read(a);
    if (sum(a, 8) == 8)
    {
        count++;
    }
    return count;
}

int sum(int *a, int l)
{
    int sum = 0;
    for (int i = 0; i < l; i++)
    {
        sum += a[i];
    }
    return sum;
}

//检测到纵向白线
int white_detect::getline()  //1表示检测到纵向白线
{
    int x=0;
    digital_read(a);
    if (sum(a, 8) != 0){
        x=1;
    }
    return x;
}

void white_detect::adjust_line_pid()
{
    while (true)
    {
        // 获取传感器值
        int sensor_values[8];
        digital_read(sensor_values);

        // 计算误差
        int line_error = calculate_line_error(sensor_values);
        if (line_error == 999)        //如果没有检测到白线，就重新进入循环
        {
            delay(100);
            continue;
        }   
        Serial.print("line_error = ");
        Serial.println(line_error);

        // 判断是否已经足够接近目标
        if (abs(line_error) <= 0.1)
        {
            delay(100);
            if (abs(line_error) <= 0.1){break;}      
        }

        // 设定目标角度和旋转方向
        int target_theta = line_error * 100; 
        char direction_command = (line_error < 0) ? MOVE_LEFT : MOVE_RIGHT;

        // 调用闭环控制函数
        mt.Stepmotor_Closed_Control(direction_command, abs(target_theta));

        delay(100); 
    }
}

// 假设这个函数会根据传感器值计算白线的误差
int white_detect::calculate_line_error(int *sensor_values)
{
    int sum = 0;
    int weighted_sum = 0;

    for (int i = 0; i < 8; i++)
    {
        sum += sensor_values[i];
        weighted_sum += i * sensor_values[i];
    }

    if (sum == 0) // 如果没有检测到白线
    {
        return 999;
    }

    return (weighted_sum / sum) - 3.5; // 3.5 是中间传感器的索引
}



int white_detect::sum(int *a, int l)
{
    int sum = 0;
    for (int i = 0; i < l; i++)
    {
        sum += a[i];
    }
    return sum;
}