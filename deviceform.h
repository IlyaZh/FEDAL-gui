#ifndef DEVICEFORM_H
#define DEVICEFORM_H

#include "abstractdeviceform.h"
#include <QPushButton>
#include <QMultiMap>
#include "led.h"

namespace Ui {
class DeviceForm;
}

class DeviceForm : public AbstractDeviceForm
{
    Q_OBJECT

public:
    explicit DeviceForm(int deviceNumber, QWidget *parent = nullptr);
    ~DeviceForm() override;
    void setFrequency(double) override;
    void setCurrent(double) override;
    void setDuration(int) override;
    void setVoltage(double) override;
    void setDelay(int) override;

public slots:
    void setLink(bool) override;
    void setState(QPair<QString, QColor>);
    void inactivateFields(QPushButton *button = nullptr);
    void incDecDelta(int delta);

signals:
    void linkClicked();
    void stateClicked();
    void parameterClicked(DeviceForm* device, QPushButton*);

private slots:
    void on_frequencyButton_clicked(bool checked);
    void on_currentButton_clicked(bool checked);
    void on_durationButton_clicked(bool checked);
    void on_voltageButton_clicked(bool checked);
    void on_delayButton_clicked(bool checked);
    void linkClickedSlot();
    void stateClickedSlot();

private:
    Ui::DeviceForm *ui;
    Led* linkLed;
    Led* stateLed;
    QVector<QPushButton*> parameterButtons;

    void incDecButton(QPushButton* button, int delta);
    void incDecButton(QPushButton* button, double delta);
    QMultiMap<QString, QColor> linkStates;
    QMultiMap<QString, QColor> deviceStates;
    QMultiMap<QString, QColor>::iterator linkItt;
    QMultiMap<QString, QColor>::iterator deviceItt;
};

#endif // DEVICEFORM_H
