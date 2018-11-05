#-------------------------------------------------
#
# Project created by QtCreator 2018-10-07T20:06:53
#
#-------------------------------------------------

QT       += core gui

QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartTimer
TEMPLATE = app

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
    timerwidget.cpp \
    addtimerdialog.cpp \
    changetimerdialog.cpp \
    smarttimerlog.cpp \
    toggleswitch.cpp \
    alertwidget.cpp \
    addalarmdialog.cpp \
    changealarmdialog.cpp \
    globalsettingsdialog.cpp \
    rangewidget.cpp

HEADERS += \
        mainwindow.h \
    timerwidget.h \
    addtimerdialog.h \
    changetimerdialog.h \
    smarttimerlog.h \
    toggleswitch.h \
    alertwidget.h \
    addalarmdialog.h \
    changealarmdialog.h \
    widgetsettings.h \
    globalsettingsdialog.h \
    rangewidget.h

FORMS += \
        mainwindow.ui \
    timerwidget.ui \
    addtimerdialog.ui \
    changetimerdialog.ui \
    alertwidget.ui \
    addalarmdialog.ui \
    changealarmdialog.ui \
    globalsettingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    stylesheet.qss
