#ifndef ABSTRACTDATA_H
#define ABSTRACTDATA_H

#include <QObject>
#include <QVariant>

class AbstractData : public QObject
{
    Q_OBJECT
public:
    explicit AbstractData(QObject *parent = nullptr);
    virtual QPair<uint, QVariant> getData() = 0;
    virtual QString errorString() = 0;

signals:
    void timeOut();
    void errorOccured();
    void dataHasSent(uint, QVariant);
    void newDataIsReady();


public slots:
    virtual void sentData(uint, uint) = 0;
};

#endif // ABSTRACTDATA_H
