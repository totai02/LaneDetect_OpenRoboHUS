#ifndef IMAGEPUBLISHER_H
#define IMAGEPUBLISHER_H

#include <QObject>
#include <opencv2/opencv.hpp>

#include "types.h"
#include "config.h"

using namespace cv;

class ImagePublisher : public QObject
{
    Q_OBJECT
public:
    explicit ImagePublisher(QObject *parent = 0);
    void captureImage();

signals:
    void showImage(const Mat& image);
    void publishImageForBarcodeScanner(const Mat& image);
    void publishImageForLaneDetect(const Mat& image);

public slots:
    void requestImageFromBarcodeScanner();
    void requestImageFromLaneDetect();

private:
    Mat image;
    VideoCapture capture;
    Size frameSize;
};

#endif // IMAGEPUBLISHER_H
