#include "appsettings.h"

AppSettings::AppSettings(QString organization, QString application, QObject *parent) : QObject(parent)
{
    settings = new QSettings(organization, application, this);
}

AppSettings::~AppSettings() {
    if(settings) settings->deleteLater();
}

void AppSettings::saveWindowSize(QSize size) {
    settings->setValue("window/size", size);
}

void AppSettings::saveWindowPos(QPoint pos) {
    settings->setValue("window/position", pos);
}

QSize AppSettings::getWindowSize() {
    return settings->value("window/size").toSize();
}

QPoint AppSettings::getWindowPos() {
    return settings->value("window/position", QPoint(0,0)).toPoint();
}

void AppSettings::saveData(QString field, QVariant value, QString folder) {
    if(!folder.isEmpty()) {
        folder += "/";
    }
    settings->setValue(folder + field, value);
}

QVariant AppSettings::getData(QString field, QString folder) {
    if(!folder.isEmpty()) {
        folder += "/";
    }
    return settings->value(folder + field);

}
