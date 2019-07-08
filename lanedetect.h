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
    WayPoint wayPoints;
    void detectWayPoint(const Mat& image);
	Mat thresholdImage(const mat& image);
	void findLane(const Mat& imgHSV);

signals:
    void requestImage();
    void laneDetected(const WayPoint& wayPoints);

public slots:
    void subscriberImage(const Mat& image);
    void startLoop();
};

#endif // LANEDETECT_H
