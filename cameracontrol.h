#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pigpio.h>
#include <iostream>
#include <cmath>

#include "config.h"

class CameraControl
{
public:
    CameraControl();

    void originState();

    void release();

    void turnLeft();

    void turnRight();

};

#endif // CAMERACONTROL_H
