#include "imagepublisher.h"

ImagePublisher::ImagePublisher(QObject *parent) : QObject(parent),
    capture(VideoCapture(0)), frameSize(Size(Config::WIDTH, Config::HEIGHT))
{
}

void ImagePublisher::captureImage()
{
    capture >> image;
    resize(image, image, frameSize);
    emit showImage(image);
}

void ImagePublisher::requestImageFromBarcodeScanner()
{
    emit publishImageForBarcodeScanner(image);
}

void ImagePublisher::requestImageFromLaneDetect()
{
    emit publishImageForLaneDetect(image);
}
