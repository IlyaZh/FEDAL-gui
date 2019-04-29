#include "abstractdeviceform.h"

AbstractDeviceForm::AbstractDeviceForm(int deviceNumber, QWidget *parent) : QWidget(parent)
{
    m_deviceNumber = deviceNumber;
}

int AbstractDeviceForm::getDeviceNumber() {
    return m_deviceNumber;
}
