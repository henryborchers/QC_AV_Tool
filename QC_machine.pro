#-------------------------------------------------
#
# Project created by QtCreator 2015-05-18T18:42:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QC_machine
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    treeitem.cpp \
    treemodel.cpp \
    filetreemodel.cpp \
    avmodel.cpp

HEADERS  += mainwindow.h \
    treeitem.h \
    treemodel.h \
    filetreemodel.h \
    avmodel.h \
    MediaInfoDLL.h

FORMS    += mainwindow.ui
CONFIG += c++11
DEFINES -= UNICODE
