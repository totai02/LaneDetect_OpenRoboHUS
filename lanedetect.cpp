#include "lanedetect.h"
#include <QDebug>

LaneDetect::LaneDetect(QObject *parent) : QObject(parent)
{

}

Mat LaneDetect::thresholdImage(const Mat& image) 
{
    Mat imgThresholded;
    cvtColor(image, imgThresholded, COLOR_BGR2HSV);
    inRange(imgThresholded, Scalar(Config::LOW_H, Config::LOW_S, Config::LOW_V), Scalar(Config::HIGH_H, Config::HIGH_S, Config::HIGH_V), imgThresholded);
    return imgThresholded;
}

Mat LaneDetect::findLane(const Mat& img)
{
    Mat result = Mat::zeros(img.size(), CV_8UC1);
    std::vector<std::vector<Point> > contours;
    std::vector<Vec4i> hierarchy;
    findContours( img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    float maxArea = 0;
    int areaIdx = -1;

    for( int i = 0; i < contours.size(); i++ )
    {
        int top = img.size().height;
        int bottom = 0;
        for (int j = 0; j < contours[i].size(); j++)
        {
            if (contours[i][j].y < top)
            {
                top = contours[i][j].y;
            }
            if (contours[i][j].y > bottom)
            {
                bottom = contours[i][j].y;
            }
        }

        if (top < Config::SKY_LINE && bottom < Config::HEIGHT / 3 * 2) continue;

        float area = boundingRect(Mat(contours[i])).area();
        if (area > maxArea)
        {
            maxArea = area;
            areaIdx = i;
        }
    }
    if (areaIdx != -1) drawContours(result, contours, areaIdx, 255, CV_FILLED, 8, hierarchy);
    return result;
}

int* lookUpTable(const Mat& image, int bottom, int top)
{
    int *lut = new int[image.cols];

    for(int i = 0; i < image.cols;i++)
    {
        lut[i] = 0;
        for(int j = bottom;j < top;j++)
        {
            lut[i] += image.data[image.step * j + i ];
        }
    }
    return lut;
}

int max(int a, int b) {return a > b ? a: b;}
int min(int a, int b) {return a < b ? a: b;}

void LaneDetect::slidingWindow(const Mat &image)
{
    int *lut = lookUpTable(image, 0, image.rows);
    int cdf[image.cols];
    cdf[0] = lut[0];
    for (int i = 1; i < image.cols; i++)
    {
        cdf[i] = cdf[i - 1] + lut[i];
    }

    int idx = 0;
    int maxPixel = 0;
    for (int i = 0; i < image.cols - Config::WINDOW_WIDTH; i++)
    {
        if (cdf[i + Config::WINDOW_WIDTH] - cdf[i] > maxPixel)
        {
            maxPixel = cdf[i + Config::WINDOW_WIDTH] - cdf[i];
            idx = i;
        }
    }
    int level = image.rows - Config::WINDOW_HEIGHT;
    while (level > 0)
    {
        int *hCount = lookUpTable(image, level, level + Config::WINDOW_HEIGHT);
        maxPixel = 0;
        cdf[0] = hCount[0];
        for (int i = 1; i < image.cols; i++)
        {
            cdf[i] = cdf[i - 1] + hCount[i];
        }

        for (int i = max(0, idx - Config::WINDOW_WIDTH); i < min(image.cols - Config::WINDOW_WIDTH, idx + Config::WINDOW_WIDTH); i++)
        {
            if (cdf[i + Config::WINDOW_WIDTH] - cdf[i] > maxPixel)
            {
                maxPixel = cdf[i + Config::WINDOW_WIDTH] - cdf[i];
                idx = i;
            }
        }
        if (maxPixel > 3) wayPoints.push_back(Point(idx + Config::WINDOW_WIDTH / 2, level + Config::WINDOW_HEIGHT / 2));
        level -= Config::WINDOW_HEIGHT;
    }
}

void LaneDetect::detectWayPoint(const Mat& image)
{
    wayPoints.clear();
    Mat dst = thresholdImage(image);
    dst = findLane(dst);
    slidingWindow(dst);
}

void LaneDetect::subscriberImage(const Mat& image)
{
    if (!image.empty()) {
        detectWayPoint(image);
        emit laneDetected(wayPoints);
        emit requestImage();
    } else {
        emit requestImage();
    }
}

void LaneDetect::changeDir(int dir)
{
    this->dir = dir;
}

void LaneDetect::startLoop()
{
    emit requestImage();
}

