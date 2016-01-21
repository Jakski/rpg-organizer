#-------------------------------------------------
#
# Project created by QtCreator 2016-01-17T18:28:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = rpg-organizer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    csv.cpp

HEADERS  += mainwindow.h \
    csv.h

FORMS    += mainwindow.ui
