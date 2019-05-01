#include "led.h"
#include "ui_led.h"

const QColor Led::GREEN = QColor(10, 223, 42);
const QColor Led::RED = QColor(255, 60, 26);
const QColor Led::WHITE = QColor(255,255,255);
const QColor Led::YELLOW = Qt::yellow;

Led::Led(QString stateText, QColor color,  QWidget *parent, QString title, bool isClickable) :
    QWidget(parent),
    ui(new Ui::Led)
{
    ui->setupUi(this);

    this->isClickable = isClickable;

//    m_states = states;
//    currentState = m_states.begin();

    setColor(color);
    setText(stateText);

    this->title = title;
    if(this->title.isEmpty()) {
        ui->titleLabel->setVisible(false);
    } else {
        ui->titleLabel->setText(title);
    }

    QFont font = ui->titleLabel->font();
    font.setPixelSize(20);
    ui->titleLabel->setFont(font);

    font = ui->stateButton->font();
    font.setPixelSize(20);
    ui->stateButton->setFont(font);

    if(isClickable) ui->circleWidget->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

    this->setMinimumSize(this->sizeHint());
}

Led::~Led()
{
    delete ui;
}

/*void Led::setState(QString str) {
    if(m_states.contains(str)){
        ui->stateLabel->setText(str);
        ui->circleWidget->setStyleSheet("QWidget { \
                                    background: " + m_states.value(str).name() + "; \
                                    border: 2px solid black; \
                                    border-radius: 24px; \
                                }");
    }
}*/

//void Led::setState(QMultiMap<QString, QColor>::Iterator item) {
//    setState(item.key());
//}

//QPair<QString, QColor> Led::state() {
//    return QPair<QString, QColor>(currentState.key(), currentState.value());
//}

void Led::resizeEvent(QResizeEvent *event) {
//    setState(currentState);
}

void Led::setText(QString str) {
    ui->stateButton->setText(str);
}

void Led::setColor(QColor color) {
    m_color = color;
    ui->circleWidget->setStyleSheet("QWidget { \
                                    background: " + m_color.name() + "; \
                                    border: 2px solid black; \
                                    border-radius: 24px; \
                                }");
}

QString Led::text() {
    return ui->stateButton->text();
}

QColor Led::color() {
    return m_color;
}

void Led::on_stateButton_clicked()
{
    if(!isClickable) return;
    emit ledClicked();
}
