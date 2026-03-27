// white_detect.h
#ifndef WHITE_DETECT_H
#define WHITE_DETECT_H

#include "config.h"

#define GRAY_1 40
#define GRAY_2 41
#define GRAY_3 42
#define GRAY_4 43
#define GRAY_5 30
#define GRAY_6 31
#define GRAY_7 32
#define GRAY_8 33

class white_detect
{
private:
    int count;
    bool detected;

public:
    int gray1_name[8] = {GRAY_1, GRAY_2, GRAY_3, GRAY_4, GRAY_5, GRAY_6, GRAY_7, GRAY_8};
    int a[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    white_detect();
    ~white_detect();
    
    void digital_read(int *a);
    int getcount();
    int getcount1();
    int getline();
    void adjust_line_pid();

private:
    int sum(int *a, int l);
    int calculate_line_error(int *sensor_values);
};

#endif
