#-------------------------------------------------
#
# Project created by QtCreator 2018-05-07T04:09:48
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DataStructures_Project
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
    updatewidget.cpp \
    deletewidget.cpp \
    searchwidget.cpp \
    printwidget.cpp \
    hashtable.cpp \
    linkedlist.cpp \
    node.cpp \
    filehandling.cpp \
    treenode.cpp \
    tree.cpp \
    addmoredata.cpp

HEADERS += \
        mainwindow.h \
    updatewidget.h \
    deletewidget.h \
    searchwidget.h \
    printwidget.h \
    addmoredata.h

FORMS += \
        mainwindow.ui \
    updatewidget.ui \
    deletewidget.ui \
    searchwidget.ui \
    printwidget.ui \
    addmoredata.ui

RESOURCES +=
