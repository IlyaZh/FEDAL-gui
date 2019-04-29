#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    clickedButton(nullptr)
{
    ui->setupUi(this);

    QString windowTitle = QString("%1 (v.%2.%3.%4)").arg(SOFTWARE_TITLE).arg(MAJOR_VERSION).arg(MINOR_VERSION).arg(PATCH_VERSION);
    setWindowTitle(windowTitle);

    dialLastPosition = 0;

    // Init water annd cool indicators
    waterLed = new Led("OK", QColor(10, 223, 42), this, "Вода", true);
    blockLed = new Led("OK", QColor(10, 223, 42), this, "Блокировка", true);
    ui->waterWidget->layout()->addWidget(waterLed);
    ui->blockWidget->layout()->addWidget(blockLed);

    deviceForms.clear();

    connect(ui->toogleParametersButton, SIGNAL(clicked(bool)), this, SLOT(showParameters(bool)));

    connect(waterLed, SIGNAL(ledClicked()), this, SLOT(waterClickedSlot()));
    connect(blockLed, SIGNAL(ledClicked()), this, SLOT(blockClickedSlot()));
    waterBlockStates["OK"] = Led::GREEN;
    waterBlockStates["ERR"] = Led::RED;
    waterItt = waterBlockStates.begin();
    blockItt = waterBlockStates.begin();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addDeviceForm(DeviceForm* deviceForm) {
    deviceForms.push_back(deviceForm);
}

// public slots
void MainWindow::showParameters(bool visible) {
    if(visible) {
        if(ui->parameterWidget->layout() == nullptr) {
            QGridLayout* parametersLayout = new QGridLayout(ui->parameterWidget);
            int row = 0;
            foreach(DeviceForm* device, deviceForms) {
                parametersLayout->addWidget(device, row++, 0);
                device->setParent(ui->parameterWidget);
                connect(device, SIGNAL(parameterClicked(DeviceForm*, QPushButton*)), this, SLOT(parameterClicked(DeviceForm*, QPushButton*)));
            }
        } else {
            foreach(DeviceForm* device, deviceForms) {
                device->setVisible(true);
            }
        }
    } else {
        QLayout* parametersLayout = ui->parameterWidget->layout();
        if(parametersLayout) {
            foreach(DeviceForm* device, deviceForms) {
                device->setVisible(false);
            }
        }
    };
    ui->parameterWidget->adjustSize();
    ui->centralWidget->adjustSize();
    this->adjustSize();
}

void MainWindow::setDeviceOn(bool isDeviceOn) {
    ui->onOffButton->setChecked(isDeviceOn);
    if(isDeviceOn) {
        ui->onOffButton->setText("Включен");
    } else {
        ui->onOffButton->setText("Выключен");
    }
}

// private slots
void MainWindow::on_dial_sliderMoved(int position)
{
    int delta = position-dialLastPosition;
    if(abs(delta) > ui->dial->maximum()*0.9) {
        delta /= -abs(delta);
    }
    dialLastPosition = position;

    if(clickedButton != nullptr) {
        bool isOk = false;

        QString fieldName = clickedButton->objectName();
        if(fieldName == "frequencyButton" || fieldName == "currentButton" || fieldName == "voltageButton") {
            double value = clickedButton->text().toDouble(&isOk);
            if(!isOk) {
               value = 0;
            }
            value += static_cast<double>(delta)/10;
            if(value < 0) value = 0;
            clickedButton->setText(QString::number(value, 'f', 1));
        } else if (fieldName == "durationButton" || fieldName == "delayButton") {
            int value = clickedButton->text().toInt(&isOk);
            if(!isOk) {
               value = 0;
            }
            value += delta;
            if(value < 0) value = 0;
            clickedButton->setText(QString::number(value));
        }

    }
}

void MainWindow::parameterClicked(DeviceForm* device, QPushButton* button) {
    ui->dial->setValue(0);
    dialLastPosition = ui->dial->value();
    ui->dial->setEnabled(button->isChecked());

    if(button->isChecked()) {
        clickedButton = button;
        foreach(DeviceForm* devPtr, deviceForms) {
            if(devPtr != device) devPtr->inactivateFields();
        }
    } else {
        clickedButton = nullptr;
    }
}

void MainWindow::on_onOffButton_clicked(bool checked)
{
    setDeviceOn(checked);
}

void MainWindow::on_extIntButton_clicked(bool checked)
{
    if(checked) {
        ui->extIntButton->setText("Внешняя");
    } else {
        ui->extIntButton->setText("Внутреняя");
    }
}

void MainWindow::on_startStopButton_clicked(bool checked)
{
    if(checked) {
        ui->startStopButton->setText("Запущен");
    } else {
        ui->startStopButton->setText("Остановлен");
    }
}

void MainWindow::waterClickedSlot() {
    waterItt++;
    if(waterItt == waterBlockStates.end()) {
        waterItt = waterBlockStates.begin();
    }
    waterLed->setText(waterItt.key());
    waterLed->setColor(waterItt.value());
}

void MainWindow::blockClickedSlot() {
    blockItt++;
    if(blockItt == waterBlockStates.end()) {
        blockItt = waterBlockStates.begin();
    }
    blockLed->setText(blockItt.key());
    blockLed->setColor(blockItt.value());
}
