#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QMap>
#include "deviceform.h"

class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QObject *parent = nullptr);
    ~Device();

signals:
    void outParameter(quint16 command, quint16 value);

public slots:
    void inParameter(quint16 command, quint16 value);

private:
    static const enum class COMMANDS {FREQUENCY = 0x0100, DURATION = 0x0200, CURRENT = 0x0300, VOLTAGE = 0x0400, DELAY = 0x0500} COMMANDS;
    static const enum class DIVIDERS {FREQUENCY = 10, DURATION = 1, CURRENT = 10, VOLTAGE = 10, DELAY = 1} DIVIDERS;
    QMap<quint16, QVariant> parameterValues;
};

#endif // DEVICE_H
