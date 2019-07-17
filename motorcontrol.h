#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <iostream>
#include <softPwm.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include "config.h"

class MotorControl
{
public:
    MotorControl();
    ~MotorControl();
    void init();
    void stop();
    bool moveForward(float error, float velocity);

private:
    float max = Config::VELOCITY;
    float min = -Config::VELOCITY;

    float integral = 0;
    float pre_error = 0;
    float pre_veloc_error = 0;

    int pidCalculate(float, float kP, float kI, float kD);
    void left_forward(int val);
    void right_forward(int val);
    void left_back(int val);
    void right_back(int val);
    int middle(int value, int min, int max);

};

#endif // MOTORCONTROL_H
