#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString windowTitle = QString("%1 (v.%2.%3.%4)").arg(SOFTWARE_TITLE).arg(MAJOR_VERSION).arg(MINOR_VERSION).arg(PATCH_VERSION);
    setWindowTitle(windowTitle);
}

MainWindow::~MainWindow()
{
    delete ui;
}
