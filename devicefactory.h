#ifndef DEVICEFACTORY_H
#define DEVICEFACTORY_H

#include <QObject>
#include "device.h"
#include "deviceform.h"

class DeviceFactory : public QObject
{
    Q_OBJECT
public:
    explicit DeviceFactory(QObject *parent = nullptr);
    ~DeviceFactory();
    Device* createDevice();
    Device* getDevice(uint number);

signals:

public slots:

private:
    QMap<uint, Device*> devicesList;
};

#endif // DEVICEFACTORY_H
