#-------------------------------------------------
#
# Project created by QtCreator 2019-01-12T23:22:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Source
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    items/qgraphicsvertexitem.cpp \
    items/qgraphicsedgeitem.cpp \
    graph/graph.cpp \
    graph/edge.cpp \
    graph/vertex.cpp \
    items/qgraphicsalignedtextitem.cpp \
    widgets/qgraphview.cpp \
    statistics/edgestatistic.cpp \
    statistics/commonneighborhoodstatistic.cpp

HEADERS += \
        mainwindow.h \
    items/qgraphicsvertexitem.h \
    items/qgraphicsedgeitem.h \
    graph/graph.h \
    graph/edge.h \
    graph/vertex.h \
    items/qgraphicsalignedtextitem.h \
    widgets/qgraphview.h \
    statistics/edgestatistic.h \
    statistics/commonneighborhoodstatistic.h

FORMS += \
        mainwindow.ui
