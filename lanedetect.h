#ifndef LANEDETECT_H
#define LANEDETECT_H

#include <opencv2/opencv.hpp>
#include <QObject>
#include <vector>

#include "config.h"
#include "types.h"

using namespace cv;
using namespace std;

class LaneDetect : public QObject
{
    Q_OBJECT
public:
    explicit LaneDetect(QObject *parent = 0);

private:
    void detectWayPoint(const Mat& image);
	Mat thresholdImage(const Mat& image);
    Mat findLane(const Mat& img);
    void slidingWindow(const Mat& image);

signals:
    void requestImage();
    void laneDetected(const WayPoint& wayPoints);

public slots:
    void subscriberImage(const Mat& image);
    void changeDir(int dir);
    void startLoop();
	
private:
    WayPoint wayPoints;
    int dir;
	
};

#endif // LANEDETECT_H
