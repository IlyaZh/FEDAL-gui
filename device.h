#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QMap>
#include <QSharedPointer>
#include <QVariant>
#include "deviceform.h"
#include "abstractdata.h"

class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(int devId, QObject *parent = nullptr);
    ~Device();
    virtual void setDataSource(AbstractData&);
    virtual DeviceForm* deviceForm();
    void setParameter(uint command, uint value);

    static const enum class COMMANDS_NAME {FREQUENCY = 0x0100, DURATION = 0x0200, CURRENT = 0x0300, VOLTAGE = 0x0400, DELAY = 0x0500} COMMANDS_NAME;
    static const enum class COMMAND_DIVIDERS {FREQUENCY = 10, DURATION = 1, CURRENT = 10, VOLTAGE = 10, DELAY = 1} COMMAND_DIVIDERS;
    static const QSet<uint> Commands;

public slots:
    void timeout();
    void errorOccured();
    void dataHasSent(uint command, QVariant value);
    void newDataIsReady();

private:
    QMap<uint, QVariant> parameterValues;
    QMap<uint, QVariant>::Iterator currentCommand;
    AbstractData* m_dataSource;
    DeviceForm* m_deviceForm;
    int devId;
};

#endif // DEVICE_H
