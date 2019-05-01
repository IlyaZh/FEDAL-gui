#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "globals.h"
#include <QDebug>

#include <QMainWindow>
#include <QGridLayout>
#include <QQueue>
#include <QPointer>
#include <QSignalMapper>
#include <QUiLoader>
#include <QFile>
#include <QResizeEvent>
#include <QMoveEvent>
#include "deviceform.h"
#include "led.h"
#include "appsettings.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(AppSettings* = nullptr, QWidget *parent = nullptr);
    void addDeviceForm(DeviceForm* deviceForm);
    ~MainWindow() override;
    void resizeEvent(QResizeEvent *event) override;
    void moveEvent(QMoveEvent *event) override;

public slots:
    void showParameters(bool visible = true);
    void setDeviceOn(bool);

private slots:
    void on_dial_sliderMoved(int position);
    void parameterClicked(DeviceForm* device, QPushButton*);
    void on_onOffButton_clicked(bool checked);
    void on_extIntButton_clicked(bool checked);
    void on_startStopButton_clicked(bool checked);
    void waterClickedSlot();
    void blockClickedSlot();
    void on_frequencyButton_clicked();

private:
    Ui::MainWindow *ui;
    int dialLastPosition;
    QPointer<Led> waterLed;
    QPointer<Led> blockLed;
    QVector<DeviceForm*> deviceForms;
    QPushButton *clickedButton;
    QWidget* parametersFooter;
    QPointer<AppSettings> m_settings;

    QMap<QString, QColor> waterBlockStates;
    QMap<QString, QColor>::iterator waterItt, blockItt;


    void updateWindow();
    void initParameters();

};

#endif // MAINWINDOW_H
