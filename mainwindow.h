#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "globals.h"
#include <QDebug>

#include <QMainWindow>
#include <QQueue>
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
    ~MainWindow();

private slots:
    void on_toogleParametersButton_toggled(bool checked);

    void on_dial_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    int dialLastPosition;
    Led* waterLed;
    Led* blockLed;

};

#endif // MAINWINDOW_H
