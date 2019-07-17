#include <QApplication>
#include <QMetaType>

#include "types.h"
#include "application.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // define meta type
    qRegisterMetaType<Mat>("Mat");
    qRegisterMetaType<BarcodeVector>("BarcodeVector");
    qRegisterMetaType<WayPoint>("WayPoint");

    Application app;

    app.start();
	
    destroyAllWindows();

    return 0;
}
