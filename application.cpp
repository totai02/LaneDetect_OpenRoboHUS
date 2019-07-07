#include "application.h"

// Contructor cua application, bao gom cac lenh khoi tao va connect SIGNAL & SLOT
Application::Application(QObject *parent) : QObject(parent)
{
    startWindowThread();
    namedWindow( "Camera", CV_WINDOW_AUTOSIZE );
    createConnect();
}

// Ham destructor
// Khi chuong trinh ket thuc thi stop 2 thread Barcode & LandDetect
Application::~Application()
{
    // Huy cac Thread & cho den khi chung huy xong
    barcodeThread.quit();
    barcodeThread.wait();

    laneDetectThread.quit();
    laneDetectThread.wait();
}

// Khoi dong main thread: Lay anh tu thiet bi
void Application::start()
{
    while (waitKey(1) != 'q') {
        imagePublisher.captureImage();
    }
}

// SLOT nhan ket qua tu barcode detect
void Application::updateBarcode(const BarcodeVector& barcodeVector)
{
    barcodeResult = barcodeVector;
}

// SLOT nhan ket qua tu Lane Detect
void Application::updateWayPoint(const WayPoint &wayPoints)
{
    this->wayPoints = wayPoints;
}

void Application::showResult(const Mat &image)
{
    Mat img = image.clone();
    for (int i = 0; i < barcodeResult.size(); i++) {
        Point2f vertices[4];
        barcodeResult[i].bounding.points(vertices);
        for (int i = 0; i < 4; i++)
            line(img, vertices[i], vertices[(i+1)%4], Scalar(0,255,0), 2);
    }
    imshow("Camera", img);
}

// Function ket noi SIGNAL & SLOT
// Ket noi cac giao thuc nhan anh tu ImagePublisher
// Sau do tra lai ket qua
void Application::createConnect()
{
    // Thread Barcode Detect
    barcode.moveToThread(&barcodeThread);
    // Gui anh tu ImagePublisher sang BarcodeScanner.
    connect(&imagePublisher, SIGNAL(publishImageForBarcodeScanner(Mat)), &barcode, SLOT(subscriberImage(Mat)));
    // Yeu cau lay anh tu ImagePublisher.
    connect(&barcode, SIGNAL(requestImage()), &imagePublisher, SLOT(requestImageFromBarcodeScanner()));
    // Gui ket qua barcode da detect duoc.
    connect(&barcode, SIGNAL(barcodeDetected(BarcodeVector)), this, SLOT(updateBarcode(BarcodeVector)));
    // Khoi dong vong lap yeu cau anh tu ImagePublisher khi signal operate() duoc emit
    connect(this, SIGNAL(operate()), &barcode, SLOT(startLoop()));
    // Khoi dong thread
    barcodeThread.start();

    // Thread Lane Detect
    laneDetect.moveToThread(&laneDetectThread);
    connect(&imagePublisher, SIGNAL(publishImageForLaneDetect(Mat)), &laneDetect, SLOT(subscriberImage(Mat)));
    connect(&laneDetect, SIGNAL(requestImage()), &imagePublisher, SLOT(requestImageFromLaneDetect()));
    connect(&laneDetect, SIGNAL(laneDetected(WayPoint)), this, SLOT(updateWayPoint(WayPoint)));
    connect(this, SIGNAL(operate()), &laneDetect, SLOT(startLoop()));
    laneDetectThread.start();

    // Main thread connection
    connect(&imagePublisher, SIGNAL(showImage(Mat)), this, SLOT(showResult(Mat)));

    // Kich hoat cac thread
    emit operate();
}
