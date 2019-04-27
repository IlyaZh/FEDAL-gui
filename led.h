#ifndef LED_H
#define LED_H

#include <QWidget>
#include <QMap>
#include <QDebug>
#include <iterator>

namespace Ui {
class Led;
}

class Led : public QWidget
{
    Q_OBJECT

public:
    explicit Led(QMap<QString, QColor> &m_states, QWidget *parent = nullptr, QString title = "", bool isClickable = false);
    ~Led() override;
    void setState(QString);
    QPair<QString, QColor> state();

private:
    Ui::Led *ui;
    QMap<QString, QColor> m_states;
    QMap<QString, QColor>::Iterator currentState;
    bool isClickable;
    QString title;

    void resizeEvent(QResizeEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void setState(QMap<QString, QColor>::Iterator item);
};

#endif // LED_H
