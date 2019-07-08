#include "barcodescanner.h"
#include <QDebug>

BarcodeScanner::BarcodeScanner(QObject *parent) : QObject(parent)
{

}

void BarcodeScanner::subscriberImage(const Mat& image)
{
    if (!image.empty()) {
        decode(image);
        emit barcodeDetected(decodedObjects);
        emit requestImage();
    } else {
        emit requestImage();
    }
}

void BarcodeScanner::startLoop()
{
    emit requestImage();
}

void BarcodeScanner::decode(const Mat &im)
{
    // Create zbar scanner
    ImageScanner scanner;
    decodedObjects.clear();

    // Configure scanner
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
	
	// Convert to grayscale
	Mat img;
	cvtColor(im, img, cv::COLOR_BGR2GRAY);

    // Wrap image data in a zbar image
    Image image(im.cols, im.rows, "Y800", (uchar *)img.data, im.cols * im.rows);

    // Scan the image for barcodes and QRCodes
    int n = scanner.scan(image);

    for(Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
    {
        DecodedObject obj;

        obj.type = symbol->get_type_name();
        obj.data = symbol->get_data();

        std::vector<cv::Point> points;

        // Obtain location
        for(int i = 0; i< symbol->get_location_size(); i++)
        {
            points.push_back(cv::Point(symbol->get_location_x(i),symbol->get_location_y(i)));
        }

        obj.bounding = cv::minAreaRect(points);

        decodedObjects.push_back(obj);
    }
}

