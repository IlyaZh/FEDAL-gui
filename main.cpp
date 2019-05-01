#include "globals.h"
#include "mainwindow.h"
#include <QApplication>
#include "deviceform.h"
#include "appsettings.h"
#include "device.h"

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QApplication::setAttribute(Qt::AA_Use96Dpi);
    QApplication a(argc, argv);

    AppSettings settings(ORG_NAME, APP_NAME);

    MainWindow w(&settings);
    w.show();

    QList<Device*> devices;

    for(int i = 0 ; i < MAX_DEVICES; ++i) {
        Device* device = new Device(i+1);
        devices.append(device);
        w.addDeviceForm(device->deviceForm());
    }
    w.showParameters(true);

    return a.exec();
}
