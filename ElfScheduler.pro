#-------------------------------------------------
#
# Project created by QtCreator 2017-07-25T02:04:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ElfScheduler
TEMPLATE = app


SOURCES += main.cpp\
		mainwindow.cpp \
    taskpane.cpp \
    taskviewerpane.cpp \
    taskeditorpane.cpp \
    datamodel.cpp

HEADERS  += mainwindow.h \
    taskpane.h \
    taskviewerpane.h \
    taskeditorpane.h \
    datamodel.h

FORMS    +=

CONFIG += c++11

QMAKE_CXXFLAGS += -O2
