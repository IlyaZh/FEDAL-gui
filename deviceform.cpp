#include "deviceform.h"
#include "ui_deviceform.h"

DeviceForm::DeviceForm(int deviceNumber, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceForm)
{
    ui->setupUi(this);

    this->deviceNumber = deviceNumber;

    QGridLayout* layout = new QGridLayout();
    QMultiMap<QString, QColor> linkStates;
    linkStates.insertMulti(QString::number(deviceNumber), QColor(10, 223, 42));
    linkStates.insertMulti(QString::number(deviceNumber), QColor(255, 255, 255));
    layout->addWidget(new Led(linkStates,this, "", true));
    ui->linkWidget;
    ui->stateWidget;
}

DeviceForm::~DeviceForm()
{
    delete ui;
}
