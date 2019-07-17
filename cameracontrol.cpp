#include "cameracontrol.h"

float inRange(float value, float min = 0, float max = 180);

float inRange(float value, float min, float max)
{
    if (value > max) value = max;
    else if (value < min) value = min;
    return value;
}

int angle2Pulse(float angle) { // deg
    return round(-10 * angle + 2400);
}

float pulse2Angle(int pulse) {
    return -0.1 * pulse + 240;
}

void stop(int signum)
{
    gpioServo(Config::SERVO, 0);
    gpioTerminate();
}

CameraControl::CameraControl()
{
    if (gpioInitialise() < 0) return;
    gpioSetSignalFunc(SIGINT, stop);
}

void CameraControl::originState()
{
    gpioServo(Config::SERVO, Config::SERVO_ORIG);
    time_sleep(0.5);
    gpioServo(Config::SERVO2, Config::SERVO2_ORIG);
}

void CameraControl::release()
{
    gpioServo(Config::SERVO, 0);
}

void CameraControl::turnLeft()
{
    gpioServo(Config::SERVO, 1600);
    time_sleep(0.25f);
}

void CameraControl::turnRight()
{
    gpioServo(Config::SERVO, 2400);
    time_sleep(0.25f);
}

