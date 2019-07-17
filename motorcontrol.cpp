#include "motorcontrol.h"

MotorControl::MotorControl()
{
    setenv("WIRINGPI_GPIOMEM", "1", 1);
    wiringPiSetup();
}

MotorControl::~MotorControl()
{
    stop();
}

void MotorControl::init()
{
    softPwmCreate(Config::sPWM1_1, 0, 100);
    softPwmCreate(Config::sPWM1_2, 0, 100);
    softPwmCreate(Config::sPWM2_1, 0, 100);
    softPwmCreate(Config::sPWM2_2, 0, 100);
}

void MotorControl::stop()
{
    softPwmWrite(Config::sPWM1_1, 0);
    softPwmWrite(Config::sPWM1_2, 0);
    softPwmWrite(Config::sPWM2_1, 0);
    softPwmWrite(Config::sPWM2_2, 0);
}

bool MotorControl::moveForward(float error, float velocity)
{
    int change = pidCalculate(error, Config::KP, Config::KI, Config::KD);

    left_forward(velocity + change);
    right_forward(velocity - change);
}

int MotorControl::pidCalculate(float error, float kP, float kI, float kD)
{
    float Pout = kP * error;

    integral += error;

    if (integral > 1) integral = 1;
    else if (integral < -1) integral = -1;
    float Iout = kI * integral;

    float Dout = kD * (error - pre_error);

    int output = round(Pout + Iout + Dout);

    output = middle(output, min, max);

    pre_error = error;

    return output;
}

void MotorControl::left_forward(int val)
{
    softPwmWrite(Config::sPWM1_1, val);
    softPwmWrite(Config::sPWM1_2, 0);
}

void MotorControl::right_forward(int val)
{
    softPwmWrite(Config::sPWM2_1, val);
    softPwmWrite(Config::sPWM2_2, 0);
}

void MotorControl::left_back(int val)
{
    softPwmWrite(Config::sPWM1_1, 0);
    softPwmWrite(Config::sPWM1_2, val);
}

void MotorControl::right_back(int val)
{
    softPwmWrite(Config::sPWM2_1, 0);
    softPwmWrite(Config::sPWM2_2, val);
}

int MotorControl::middle(int value, int min, int max)
{
    if( value > max )
        value = max;
    else if( value < min )
        value = min;
    return value;
}


