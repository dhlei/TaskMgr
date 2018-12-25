#-------------------------------------------------
#
# Project created by QtCreator 2018-03-23T21:20:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = task_mgr
TEMPLATE = app

INCLUDEPATH = Painter\

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
        TaskMgr.cpp \
    Painter/MySector.cpp \
    DataHandle/memory_handler.c \
    DataHandle/disk_handler.cpp \
    Painter/MyLine.cpp \
    DataHandle/cpu_handler.cpp \
    Painter/MyColumn.cpp \
    DataHandle/process_handler.cpp

HEADERS += \
        TaskMgr.h \
    Painter/MySector.h \
    DataHandle/disk_handler.h \
    DataHandle/memory_handler.h \
    Painter/MyLine.h \
    DataHandle/cpu_handler.h \
    Painter/MyColumn.h \
    DataHandle/process_handler.h

FORMS += \
        TaskMgr.ui
