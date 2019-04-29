#include "device.h"

Device::Device(QObject *parent) : QObject(parent)
{

}

Device::~Device() {

}

void Device::inParameter(quint16 command, quint16 value) {
    parameterValues[command] = QVariant(value);
}
