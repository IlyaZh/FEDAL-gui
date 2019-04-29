#ifndef ABSTRACTDEVICEFORM_H
#define ABSTRACTDEVICEFORM_H

#include <QWidget>

class AbstractDeviceForm : public QWidget
{
    Q_OBJECT
public:
    static const enum FIELDS {NONE, FREQUENCY, CURRENT, DURATION, VOLTAGE, DELAY} fields_t;

    explicit AbstractDeviceForm(int deviceNumber, QWidget *parent = nullptr);
    int getDeviceNumber();
    virtual void setFrequency(double) = 0;
    virtual void setCurrent(double) = 0;
    virtual void setDuration(int) = 0;
    virtual void setVoltage(double) = 0;
    virtual void setDelay(int) = 0;
    virtual void setLink(bool) = 0;

signals:

public slots:

protected:
    int m_deviceNumber;

private:

};

#endif // ABSTRACTDEVICEFORM_H
