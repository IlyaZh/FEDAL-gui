#include "deviceform.h"
#include "ui_deviceform.h"

DeviceForm::DeviceForm(int deviceNumber, QWidget *parent) :
    AbstractDeviceForm(deviceNumber, parent),
    ui(new Ui::DeviceForm)
{
    ui->setupUi(this);

    m_deviceNumber = deviceNumber;

    QGridLayout* layout = new QGridLayout(ui->linkWidget);
    linkLed = new Led(QString::number(m_deviceNumber), Led::WHITE, this, "", true);
    layout->addWidget(linkLed);
    ui->linkWidget->setLayout(layout);

    layout = new QGridLayout(ui->stateWidget);
    stateLed = new Led("OFF", Led::RED, this, "", true);
    layout->addWidget(stateLed);
    ui->stateWidget->setLayout(layout);

    setLink(false);
    setState(QPair<QString, QColor>("", Led::WHITE));

    parameterButtons.push_back(ui->frequencyButton);
    parameterButtons.push_back(ui->currentButton);
    parameterButtons.push_back(ui->durationButton);
    parameterButtons.push_back(ui->voltageButton);
    parameterButtons.push_back(ui->delayButton);

    foreach(QPushButton* button, parameterButtons) {
        QFont font = button->font();
        font.setPixelSize(48);
        button->setFont(font);
    }

    linkStates.insert(QString::number(m_deviceNumber), Led::WHITE);
    linkStates.insert(QString::number(m_deviceNumber), Led::GREEN);
    linkItt = linkStates.begin();
    deviceStates.insert("ON", Led::GREEN);
    deviceStates.insert("OFF", Led::YELLOW);
    deviceStates.insert("ERR", Led::RED);
    deviceStates.insert("", Led::WHITE);
    deviceItt = deviceStates.begin();
    connect(linkLed, SIGNAL(ledClicked()), this, SLOT(linkClickedSlot()));
    connect(stateLed, SIGNAL(ledClicked()), this, SLOT(stateClickedSlot()));
}

DeviceForm::~DeviceForm()
{
    delete ui;
}

// public slots
void DeviceForm::setLink(bool flag) {
    if(flag) {
        linkLed->setColor(Led::GREEN);
    } else {
        linkLed->setColor(Led::RED);
        ui->frequencyButton->setText("---.-");
        ui->durationButton->setText("----");
        ui->currentButton->setText("---.-");
        ui->voltageButton->setText("---.-");
        ui->delayButton->setText("----");
    }
}

void DeviceForm::setState(QPair<QString, QColor> state) {
    stateLed->setText(state.first);
    stateLed->setColor(state.second);
}

void DeviceForm::inactivateFields(QPushButton *button) {
    foreach(QPushButton *pBtn, parameterButtons) {
        if(pBtn != button) {
            pBtn->setChecked(false);
        }
    }
}

void DeviceForm::incDecDelta(int delta) {
//    switch(clickedParameter) {
//    FREQUENCY:
//        setFrequency()
//    CURRENT:
//    VOLTAGE:
//    DURATION:
//    DELAY:
//    }
}

// private slots

void DeviceForm::on_frequencyButton_clicked(bool checked)
{
    if(checked) {
        inactivateFields(ui->frequencyButton);
    }
    emit parameterClicked(this, ui->frequencyButton);
}

void DeviceForm::on_currentButton_clicked(bool checked)
{
    if(checked) {
        inactivateFields(ui->currentButton);
    }
   emit parameterClicked(this, ui->currentButton);
}

void DeviceForm::on_durationButton_clicked(bool checked)
{
    if(checked) {
        inactivateFields(ui->durationButton);
    }
    emit parameterClicked(this, ui->durationButton);
}

void DeviceForm::on_voltageButton_clicked(bool checked)
{
    if(checked) {
        inactivateFields(ui->voltageButton);
    }
    emit parameterClicked(this, ui->voltageButton);
}

void DeviceForm::on_delayButton_clicked(bool checked)
{
    if(checked) {
        inactivateFields(ui->delayButton);
    }
    emit parameterClicked(this, ui->delayButton);
}

// private
void DeviceForm::setFrequency(double value) {
    ui->frequencyButton->setText(QString::number(value, 'f', 1));
}

void DeviceForm::setCurrent(double value) {
    ui->currentButton->setText(QString::number(value, 'f', 1));
}

void DeviceForm::setDuration(int value) {
    ui->durationButton->setText(QString::number(value));
}

void DeviceForm::setVoltage(double value) {
    ui->voltageButton->setText(QString::number(value, 'f', 1));
}

void DeviceForm::setDelay(int value) {
    ui->delayButton->setText(QString::number(value));
}

void DeviceForm::incDecButton(QPushButton* button, int delta) {
    int newValue = button->text().toInt()+delta;
    if(newValue < 0) newValue = 0;
    button->setText(QString::number(newValue));
}

void DeviceForm::incDecButton(QPushButton* button, double delta) {
    double newValue = button->text().toDouble()+delta;
    if(newValue < 0) newValue = 0;
    button->setText(QString::number(newValue, 'f', 1));
}

void DeviceForm::linkClickedSlot() {
    linkItt++;
    if(linkItt == linkStates.end()) {
        linkItt = linkStates.begin();
    }

    linkLed->setText(linkItt.key());
    linkLed->setColor(linkItt.value());
}

void DeviceForm::stateClickedSlot() {
    deviceItt++;
    if(deviceItt == deviceStates.end()) {
        deviceItt = deviceStates.begin();
    }

    stateLed->setText(deviceItt.key());
    stateLed->setColor(deviceItt.value());

}
