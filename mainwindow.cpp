#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString windowTitle = QString("%1 (v.%2.%3.%4)").arg(SOFTWARE_TITLE).arg(MAJOR_VERSION).arg(MINOR_VERSION).arg(PATCH_VERSION);
    setWindowTitle(windowTitle);

    dialLastPosition = 0;

    // Init water annd cool indicators
    QMap<QString, QColor> waterBlockStates;
    waterBlockStates.insert("OK", QColor(10, 223, 42));
    waterBlockStates.insert("ERR", QColor(255, 60, 26));
    waterLed = new Led(waterBlockStates, this, "Вода", true);
    blockLed = new Led(waterBlockStates, this, "Блокировка", true);
    waterLed->setState("OK");
    blockLed->setState("OK");
    ui->waterWidget->layout()->addWidget(waterLed);
    ui->blockWidget->layout()->addWidget(blockLed);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toogleParametersButton_toggled(bool checked)
{
    ui->parameterWidget->setVisible(checked);
    this->adjustSize();
}

void MainWindow::on_dial_sliderMoved(int position)
{
    int delta = position-dialLastPosition;
    if(abs(delta) > ui->dial->maximum()*0.9) {
        delta /= -abs(delta);
    }
    dialLastPosition = position;
}
