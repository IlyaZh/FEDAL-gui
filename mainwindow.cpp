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

    QGridLayout* hbLayout = new QGridLayout(ui->waterWidget);
    hbLayout->addWidget(waterLed, 0, 0);
//    hbLayout->addItem(new QSpacerItem(20,20), 0, 1, 0, 0);
    ui->waterWidget->setLayout(hbLayout);

    hbLayout = new QGridLayout(ui->blockWidget);
//    hbLayout->addItem(new QSpacerItem(20,20), 0, 0, 0, 0);
    hbLayout->addWidget(blockLed, 0, 1);
    ui->blockWidget->setLayout(hbLayout);

    deviceForms.clear();

    connect(ui->toogleParametersButton, SIGNAL(clicked(bool)), this, SLOT(showParameters(bool)));

    connect(waterLed, SIGNAL(ledClicked()), this, SLOT(waterClickedSlot()));
    connect(blockLed, SIGNAL(ledClicked()), this, SLOT(blockClickedSlot()));
    waterBlockStates["OK"] = Led::GREEN;
    waterBlockStates["ERR"] = Led::RED;
    waterItt = waterBlockStates.begin();
    blockItt = waterBlockStates.begin();

    // font fix
    QFont font;
    foreach(QPushButton* button, this->findChildren<QPushButton*>()) {
        font = button->font();
        font.setPixelSize(18);
        button->setFont(font);
    }

    font = ui->unitLabel->font();
    font.setPixelSize(96);
    ui->unitLabel->setFont(font);

    font = ui->frequencyButton->font();
    font.setPixelSize(170);
    ui->frequencyButton->setFont(font);
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
        ui->toogleParametersButton->setText("Скрыть параметры");
        if(ui->parameterWidget->layout() == nullptr) {
            initParameters();
        }
    } else {
        ui->toogleParametersButton->setText("Показать параметры");
    }

    foreach(DeviceForm* device, deviceForms) {
        device->setVisible(visible);
    }
    parametersFooter->setVisible(visible);

    updateWindow();
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
        if (fieldName == "durationButton" || fieldName == "delayButton") {
                    int value = clickedButton->text().toInt(&isOk);
                    if(!isOk) {
                       value = 0;
                    }
                    value += delta;
                    if(value < 0) value = 0;
                    clickedButton->setText(QString::number(value));
        } else {
            double value = clickedButton->text().toDouble(&isOk);
            if(!isOk) {
               value = 0;
            }
            value += static_cast<double>(delta)/10;
            if(value < 0) value = 0;
            clickedButton->setText(QString::number(value, 'f', 1));
        }

    }
}

void MainWindow::parameterClicked(DeviceForm* device, QPushButton* button) {
    dialLastPosition = ui->dial->value();
    ui->dial->setEnabled(button->isChecked());

    if(button->isChecked()) {
        clickedButton = button;
        if(device != nullptr) {
            ui->frequencyButton->setChecked(false);
        }
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

// private

void MainWindow::updateWindow() {
    ui->parameterWidget->adjustSize();
    ui->centralWidget->adjustSize();
    this->adjustSize();
}

void MainWindow::initParameters() {
    QGridLayout* parametersLayout = new QGridLayout(ui->parameterWidget);
    int row = 0;
    foreach(DeviceForm* device, deviceForms) {
        parametersLayout->addWidget(device, row++, 0);
        device->setParent(ui->parameterWidget);
        connect(device, SIGNAL(parameterClicked(DeviceForm*, QPushButton*)), this, SLOT(parameterClicked(DeviceForm*, QPushButton*)));
//                QSize size = ui->parameterWidget->size();
//                ui->parameterWidget->resize(size.width(), size.height()+device->size().height());
    }

    // load footer
    QUiLoader loader;
    QFile file(":/forms/deviceform.ui");
    file.open(QFile::ReadOnly);
    parametersFooter = loader.load(&file, this);
    file.close();

    QList<QString> labels = {"Частота, Гц", "Ток, А", "Длит"
                             "., мкс", "Напряж., В","Задержка, мкс"};
    int i = 0;
    QFont font;
    foreach(auto* button, parametersFooter->findChildren<QPushButton*>()) {
        button->setStyleSheet("");
        button->setCheckable(false);
        font = button->font();
        font.setPixelSize(19);
        button->setFont(font);
        button->setText(labels[i++]);
    }
    QWidget* linkWidget = parametersFooter->findChild<QWidget*>("linkWidget");
    QWidget* stateWidget = parametersFooter->findChild<QWidget*>("stateWidget");

    QGridLayout *glayout = new QGridLayout(linkWidget);
    QLabel* label = new QLabel("Связь", linkWidget);
    label->setFont(font);
    glayout->addWidget(label);
    linkWidget->setLayout(glayout);
    linkWidget->setMinimumWidth(80);

    glayout = new QGridLayout(stateWidget);
    label = new QLabel("Сеть", stateWidget);
    label->setFont(font);
    label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    label->setAlignment(Qt::AlignHCenter);
    glayout->addWidget(label);
    stateWidget->setLayout(glayout);
    stateWidget->setMinimumWidth(80);

    parametersLayout->addWidget(parametersFooter, row++, 0);

    // end of loading footer

    ui->parameterWidget->setLayout(parametersLayout);
}

void MainWindow::on_frequencyButton_clicked()
{
    parameterClicked(nullptr, ui->frequencyButton);
}
