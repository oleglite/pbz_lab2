#-------------------------------------------------
#
# Project created by QtCreator 2012-11-22T19:01:33
#
#-------------------------------------------------

QT       += core gui sql

TARGET = fishing
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    actionhandler.cpp

HEADERS  += mainwindow.h \
    database.h \
    actionhandler.h

FORMS    += mainwindow.ui \
    customRequestDialog.ui
