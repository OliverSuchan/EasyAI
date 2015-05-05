#-------------------------------------------------
#
# Project created by QtCreator 2015-05-05T18:06:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasyAI
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    ann/feedforwardnetwork.cpp \
    neuronwidget.cpp \
    inputneuron.cpp \
    outputneuron.cpp \
    connection.cpp

HEADERS  += mainwindow.hpp \
    ann/feedforwardnetwork.hpp \
    ann/matrix.hpp \
    neuronwidget.hpp \
    inputneuron.hpp \
    outputneuron.hpp \
    connection.hpp

FORMS    += mainwindow.ui

INCLUDEPATH += ann
