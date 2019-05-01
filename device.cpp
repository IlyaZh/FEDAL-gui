#include "device.h"

const QSet<uint> Device::Commands = {0x0101, 0x0201, 0x0301, 0x0401, 0x0501, 0x0102, 0x0202, 0x0302, 0x0402, 0x0502, 0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0700, 0x0800};

Device::Device(int devId, QObject *parent) : QObject(parent),
    m_dataSource(nullptr),
    m_deviceForm(new DeviceForm(devId))
{
    this->devId = devId;
}

Device::~Device() {
    qDebug() << "dev delete";
}

void Device::setDataSource(AbstractData& dataSource) {
    if(m_dataSource != nullptr) disconnect(m_dataSource, nullptr, nullptr, nullptr);
    m_dataSource = &dataSource;
    connect(m_dataSource, SIGNAL(timeout()), this, SLOT(timeout()));
    connect(m_dataSource, SIGNAL(dataHasSent(uint, QVariant)), this, SLOT(dataHasSent()));
    connect(m_dataSource, SIGNAL(errorOccured()), this, SLOT(errorOccured()));
    connect(m_dataSource, SIGNAL(newDataIsReady()), this, SLOT(newDataIsReady()));
}

DeviceForm* Device::deviceForm() {

    return m_deviceForm;
}

void Device::setParameter(uint command, uint value) {
    m_dataSource->sentData(command, value);
}

// public slots
void Device::timeout() {}

void Device::errorOccured() {}

void Device::dataHasSent(uint command, QVariant value) {
    parameterValues[command] = value;
}

void Device::newDataIsReady() {}
