#ifndef BARCODESCANNER_H
#define BARCODESCANNER_H

#include <opencv2/opencv.hpp>
#include <QObject>
#include <zbar.h>
#include <vector>

#include "types.h"

using namespace zbar;

class BarcodeScanner : public QObject
{
    Q_OBJECT
public:
    explicit BarcodeScanner(QObject *parent = 0);

private:
    void decode(const Mat &im);
    BarcodeVector decodedObjects;

signals:
    void requestImage();
    void barcodeDetected(const BarcodeVector& barcodeVector);

public slots:
    void subscriberImage(const Mat& image);
    void startLoop();

};

#endif // BARCODESCANNER_H
