#-------------------------------------------------
#
# Project created by A.D.K. 2019-07-05T22:49:30
#
#-------------------------------------------------

QT       += core gui sql

CONFIG += c++11


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI_TRM8TT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    eca-control-interface.cpp \
    ecasoundc_sa.c \
    thread1.cpp \
    kvu_numtostr.cpp \
    thread2.cpp

HEADERS  += mainwindow.h \
    eca-control-interface.h \
    ecasoundc.h \
    thread1.h \
    ecicpp_helpers.h \
    kvu_numtostr.h \
    thread2.h


FORMS    += mainwindow.ui

LIBS += -lasound

INCLUDEPATH += /usr/include/jack

LIBS += -L"/usr/include/jack" -ljack
