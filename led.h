#ifndef LED_H
#define LED_H

#include <QWidget>
#include <QMultiMap>
#include <QDebug>
#include <iterator>

namespace Ui {
class Led;
}

class Led : public QWidget
{
    Q_OBJECT

public:
    explicit Led(QMultiMap<QString, QColor> &m_states, QWidget *parent = nullptr, QString title = "", bool isClickable = false);
    ~Led() override;
    void setState(QString);
    QPair<QString, QColor> state();

private:
    Ui::Led *ui;
    QMultiMap<QString, QColor> m_states;
    QMultiMap<QString, QColor>::Iterator currentState;
    bool isClickable;
    QString title;

    void resizeEvent(QResizeEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void setState(QMultiMap<QString, QColor>::Iterator item);
};

#endif // LED_H
