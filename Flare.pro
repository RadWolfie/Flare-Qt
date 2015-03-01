#-------------------------------------------------
#
# Project created by QtCreator 2014-08-10T18:37:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Flare
TEMPLATE = app

QMAKE_CC= gcc -std=c99

SOURCES += main.cpp\
        mainwindow.cpp \
    ZZTHaloGametype.c \
    crc32.c \
    aboutflaredialog.cpp

HEADERS  += mainwindow.h \
    ZZTHaloGametype.h \
    crc32.h \
    aboutflaredialog.h

FORMS    += mainwindow.ui \
    aboutflaredialog.ui
