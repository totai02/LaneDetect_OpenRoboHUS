#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QThread>

#include "timer.h"
#include "barcodescanner.h"
#include "lanedetect.h"
#include "imagepublisher.h"
#include "motorcontrol.h"
#include "cameracontrol.h"

using namespace cv;

class Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = 0);
    ~Application();
    void start();

signals:
    void operate();

public slots:
    void updateBarcode(const BarcodeVector& barcodeVector);
    void updateWayPoint(const WayPoint& wayPoints);
    void showResult(const Mat& image);

private:
    void createConnect();

	Timer timer;
    CameraControl cameraControl;
    MotorControl motorControl;
	
    WayPoint wayPoints;
    BarcodeVector barcodeResult;

    ImagePublisher imagePublisher;
    BarcodeScanner barcode;
    LaneDetect laneDetect;

    QThread barcodeThread;
    QThread laneDetectThread;
};

#endif // APPLICATION_H
