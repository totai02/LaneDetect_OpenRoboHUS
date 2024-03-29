#ifndef TYPES_H
#define TYPES_H
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#define LEFT 1
#define RIGHT 2

typedef struct
{
  std::string type;
  std::string data;
  cv::RotatedRect bounding;
} DecodedObject;

typedef std::vector<cv::Point> WayPoint;

typedef cv::Mat Mat;

typedef std::vector<DecodedObject> BarcodeVector;

#endif // TYPES_H
