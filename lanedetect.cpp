#include "lanedetect.h"

LaneDetect::LaneDetect(QObject *parent) : QObject(parent)
{

}

Mat LaneDetect::thresholdImage(const Mat& image) 
{
	Mat imgThresholded;
	cvtColor(image, imgThresholded, COLOR_BGR2HSV);
	inRange(imgHSV, Scalar(Config::LOW_H, Config::LOW_S, Config::LOW_V), Scalar(Config::HIGH_H, Config::HIGH_S, Config::HIGH_V), imgThresholded);
	return imgThresholded;
}

void LaneDetect::findLane(const Mat& img)
{
	Mat result;
	vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
	findContours( img, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	float maxArea = 0;
	for( int i = 0; i < contours.size(); i++ )
    {
		if (contourArea(Mat(contours[i])) > radius[i] * radius[i] * M_PI * 0.6)
		{
			
		}
    }
}

void transform(Point2f* src_vertices, Point2f* dst_vertices, Mat& src, Mat &dst){
    Mat M = getPerspectiveTransform(src_vertices, dst_vertices);
    warpPerspective(src, dst, M, dst.size(), INTER_LINEAR, BORDER_CONSTANT);
}

Mat DetectLane::birdViewTranform(const Mat& src)
{
    Point2f src_vertices[4];

    int width = src.size().width;
    int height = src.size().height;

    src_vertices[0] = Point(0, Config::SKY_LINE);
    src_vertices[1] = Point(width, Config::SKY_LINE);
    src_vertices[2] = Point(width, height);
    src_vertices[3] = Point(0, height);

    Point2f dst_vertices[4];
    dst_vertices[0] = Point(0, 0);
    dst_vertices[1] = Point(BIRDVIEW_WIDTH, 0);
    dst_vertices[2] = Point(BIRDVIEW_WIDTH - 105, BIRDVIEW_HEIGHT);
    dst_vertices[3] = Point(105, BIRDVIEW_HEIGHT);

    Mat M = getPerspectiveTransform(src_vertices, dst_vertices);

    Mat dst(BIRDVIEW_HEIGHT, BIRDVIEW_WIDTH, CV_8UC1);
    warpPerspective(src, dst, M, dst.size(), INTER_LINEAR, BORDER_CONSTANT);

    return dst;
}

void LaneDetect::detectWayPoint(const Mat& image)
{
    wayPoints.clear();
	Mat imgThresholded = thresholdImage(image);
}

void LaneDetect::subscriberImage(const Mat& image)
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
