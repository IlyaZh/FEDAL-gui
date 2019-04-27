#include "led.h"
#include "ui_led.h"

Led::Led(QMap<QString, QColor> &states, QWidget *parent, QString title, bool isClickable) :
    QWidget(parent),
    ui(new Ui::Led)
{
    ui->setupUi(this);

    this->isClickable = isClickable;

    m_states = states;
    currentState = m_states.begin();

    this->title = title;
    if(this->title.isEmpty()) {
        ui->titleLabel->setVisible(false);
    } else {
        ui->titleLabel->setText(title);
    }

    if(isClickable) ui->circleWidget->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

    this->setMinimumSize(this->sizeHint());
}

Led::~Led()
{
    delete ui;
}

void Led::setState(QString str) {
    if(m_states.contains(str)){
        ui->stateLabel->setText(str);
        ui->circleWidget->setStyleSheet("QWidget { \
                                    background: " + m_states.value(str).name() + "; \
                                    border: 2px solid black; \
                                    border-radius: 24px; \
                                }");
    }
}

void Led::setState(QMap<QString, QColor>::Iterator item) {
    setState(item.key());
}

QPair<QString, QColor> Led::state() {
    return QPair<QString, QColor>(currentState.key(), currentState.value());
}

void Led::resizeEvent(QResizeEvent *event) {
//    setState(currentState);
}

void Led::mouseDoubleClickEvent(QMouseEvent *event) {
    if(!isClickable) return;
    currentState++;
    if(currentState == m_states.end()) {
        currentState = m_states.begin();
    }
    setState(currentState);
}
