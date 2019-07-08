#include "lanedetect.h"

LaneDetect::LaneDetect(QObject *parent) : QObject(parent)
{

}

Mat LaneDetect::thresholdImage(const mat& image) 
{
	Mat imgThresholded;
	inRange(imgHSV, Scalar(Config::LOW_H, Config::LOW_S, Config::LOW_V), Scalar(Config::HIGH_H, Config::HIGH_S, Config::HIGH_V), imgThresholded);
}

void LaneDetect::findLane(const Mat& imgHSV)
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
