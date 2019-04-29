#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "globals.h"
#include <QDebug>

#include <QMainWindow>
#include <QGridLayout>
#include <QQueue>
#include <QPointer>
#include <QSignalMapper>
#include "deviceform.h"
#include "led.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void addDeviceForm(DeviceForm* deviceForm);
    ~MainWindow();

public slots:
    void showParameters(bool visible = true);
    void setDeviceOn(bool);

private slots:
    void on_toogleParametersButton_toggled(bool checked);
    void on_dial_sliderMoved(int position);
    void parameterClicked(DeviceForm* device, QPushButton*);
    void on_onOffButton_clicked(bool checked);

    void on_extIntButton_clicked(bool checked);

    void on_startStopButton_clicked(bool checked);
    void waterClickedSlot();
    void blockClickedSlot();

private:
    Ui::MainWindow *ui;
    int dialLastPosition;
    QPointer<Led> waterLed;
    QPointer<Led> blockLed;
    QVector<DeviceForm*> deviceForms;
    QPushButton *clickedButton;

    QMap<QString, QColor> waterBlockStates;
    QMap<QString, QColor>::iterator waterItt, blockItt;

};

#endif // MAINWINDOW_H
