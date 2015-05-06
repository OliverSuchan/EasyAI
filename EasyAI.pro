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
    connection.cpp \
    ann/dataio.cpp \
    createnetworkwindow.cpp \
    setvaluewindow.cpp \
    ineuralobject.cpp \
    trainingwindow.cpp \
    plotwidget.cpp \
    evaluationwindow.cpp

HEADERS  += mainwindow.hpp \
    ann/feedforwardnetwork.hpp \
    ann/matrix.hpp \
    neuronwidget.hpp \
    inputneuron.hpp \
    outputneuron.hpp \
    connection.hpp \
    ann/dataio.hpp \
    createnetworkwindow.hpp \
    setvaluewindow.hpp \
    ineuralobject.hpp \
    trainingwindow.hpp \
    plotwidget.hpp \
    evaluationwindow.hpp

FORMS    += mainwindow.ui \
    createnetworkwindow.ui \
    setvaluewindow.ui \
    trainingwindow.ui \
    plotwidget.ui \
    evaluationwindow.ui

INCLUDEPATH += ann
