#include "appsettings.h"

AppSettings::AppSettings(QString organization, QString application, QObject *parent) : QObject(parent)
{
    settings = new QSettings(organization, application, this);
}

AppSettings::~AppSettings() {
    if(settings) settings->deleteLater();
}
