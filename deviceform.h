#ifndef DEVICEFORM_H
#define DEVICEFORM_H

#include <QWidget>
#include "led.h"

namespace Ui {
class DeviceForm;
}

class DeviceForm : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceForm(int deviceNumber, QWidget *parent = nullptr);
    ~DeviceForm();

private:
    Ui::DeviceForm *ui;
    Led* linkLed;
    Led* stateLed;
    int deviceNumber;
};

#endif // DEVICEFORM_H
