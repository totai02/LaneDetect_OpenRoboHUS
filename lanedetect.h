#ifndef LANEDETECT_H
#define LANEDETECT_H

#include <opencv2/opencv.hpp>
#include <QObject>
#include <vector>

#include "config.h"
#include "types.h"

class LaneDetect : public QObject
{
    Q_OBJECT
public:
    explicit LaneDetect(QObject *parent = 0);

private:
    void detectWayPoint(const Mat& image);
	Mat thresholdImage(const Mat& image);
	void findLane(const Mat& img);
	Mat birdViewTranform(const Mat& src);

signals:
    void requestImage();
    void laneDetected(const WayPoint& wayPoints);

public slots:
    void subscriberImage(const Mat& image);
    void startLoop();
	
private:
    WayPoint wayPoints;
	
};

#endif // LANEDETECT_H
