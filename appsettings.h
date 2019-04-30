#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QPointer>

class AppSettings : public QObject
{
    Q_OBJECT
public:
    explicit AppSettings(QString organization, QString application, QObject *parent = nullptr);
    void saveWindowState(QByteArray);
    void saveWindowGeometry(QByteArray);
    QByteArray getWindowState();
    QByteArray getWindowGeometry();
    ~AppSettings();

signals:

public slots:

private:
    QPointer<QSettings> settings;
};

#endif // APPSETTINGS_H
