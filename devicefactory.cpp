#include "devicefactory.h"

DeviceFactory::DeviceFactory(QObject *parent) : QObject(parent)
{

}

DeviceFactory::~DeviceFactory() {
    foreach(Device* device, devicesList) {
        delete device;
    }
    devicesList.clear();
}

Device* DeviceFactory::createDevice() {
    int number = devicesList.count() + 1;
    Device* newDevice = new Device(number);
    devicesList[number] = newDevice;
    return newDevice;
}

Device* DeviceFactory::getDevice(uint number) {
    return devicesList.value(number, nullptr);
}
