#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QPointer>
#include <QPoint>
#include <QSize>

class AppSettings : public QObject
{
    Q_OBJECT
public:
    explicit AppSettings(QString organization, QString application, QObject *parent = nullptr);
    void saveWindowSize(QSize);
    void saveWindowPos(QPoint);
    QSize getWindowSize();
    QPoint getWindowPos();
    void saveData(QString field, QVariant value, QString folder = "");
    QVariant getData(QString field, QString folder = "");
    ~AppSettings();

private:
    QSettings* settings;
};

#endif // APPSETTINGS_H
