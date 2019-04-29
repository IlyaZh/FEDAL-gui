#include "globals.h"
#include "mainwindow.h"
#include <QApplication>
#include "deviceform.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_Use96Dpi);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    for(int i = 0 ; i < MAX_DEVICES; ++i) {
        w.addDeviceForm(new DeviceForm(i+1, &w));
    }
    w.showParameters(true);

    return a.exec();
}
