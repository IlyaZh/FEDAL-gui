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
    static const QColor GREEN;
    static const QColor RED;
    static const QColor WHITE;
    static const QColor YELLOW;

    explicit Led(QString stateText, QColor color, QWidget *parent = nullptr, QString title = "", bool isClickable = false);
    ~Led() override;
    void setText(QString);
    void setColor(QColor);
    QString text();
    QColor color();
//    void setState(QString);
//    QPair<QString, QColor> state()

signals:
    void ledClicked();


private slots:
    void on_stateButton_clicked();

private:
    Ui::Led *ui;
//    QMultiMap<QString, QColor> m_states;
//    QMultiMap<QString, QColor>::Iterator currentState;
    bool isClickable;
    QString title;
    QColor m_color;

    void resizeEvent(QResizeEvent *event) override;
//    void event
//    void setState(QMultiMap<QString, QColor>::Iterator item);
};

#endif // LED_H
