#-------------------------------------------------
#
# Project created by QtCreator 2019-04-25T21:19:56
#
#-------------------------------------------------

QT       += core gui uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fedal-gui
TEMPLATE = app

#Application version
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_PATCH = 0

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
       "VERSION_MINOR=$$VERSION_MINOR"\
       "VERSION_PATCH=$$VERSION_PATCH"

VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}
VERSION_PE_HEADER = VERSION;

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    deviceform.cpp \
    led.cpp \
    device.cpp \
    abstractdeviceform.cpp \
    appsettings.cpp \
    devicefactory.cpp

HEADERS += \
        mainwindow.h \
    globals.h \
    deviceform.h \
    led.h \
    device.h \
    abstractdeviceform.h \
    abstractdata.h \
    appsettings.h \
    devicefactory.h

FORMS += \
        mainwindow.ui \
    deviceform.ui \
    led.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    uml-model.qmodel

RC_ICONS = FEDAL.ico
