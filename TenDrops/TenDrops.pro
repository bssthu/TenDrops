#-------------------------------------------------
#
# Project created by QtCreator 2013-10-08T21:30:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TenDrops
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    grid.cpp \
    gameboard.cpp \
    mygraphicsview.cpp \
    drop.cpp \
    dropgraphics.cpp \
    gridgraphics.cpp \
    mapreader.cpp \
    state.cpp \
    AI/bfsthread.cpp \
    AI/mythread.cpp \
    AI/dfsthread.cpp

HEADERS  += mainwindow.h \
    grid.h \
    gameboard.h \
    Macro.h \
    mygraphicsview.h \
    drop.h \
    dropgraphics.h \
    gridgraphics.h \
    mapreader.h \
    state.h \
    AI/bfsthread.h \
    AI/mythread.h \
    AI/dfsthread.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc

CONFIG += \
    c++11

RC_FILE += \
    resource.rc

OTHER_FILES += \
    resource.rc
