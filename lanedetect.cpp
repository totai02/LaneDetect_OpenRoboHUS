#include "lanedetect.h"

LaneDetect::LaneDetect(QObject *parent) : QObject(parent)
{


}

void LaneDetect::detectWayPoint(const Mat &image)
{
    wayPoints.clear();
}

void LaneDetect::subscriberImage(const Mat &image)
{
    if (!image.empty()) {
        detectWayPoint(image);
        emit laneDetected(wayPoints);
        emit requestImage();
    } else {
        // Duy tri yeu cau lay anh
        emit requestImage();
    }
}

void LaneDetect::startLoop()
{
    emit requestImage();
}
