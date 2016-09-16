#-------------------------------------------------
#
# Project created by QtCreator 2016-03-11T08:24:46
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QKomunikatorClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logowanie.cpp

HEADERS  += mainwindow.h \
    logowanie.h

FORMS    += mainwindow.ui \
    logowanie.ui

RESOURCES += \
    resource.qrc
