#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T22:11:54
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Counter
TEMPLATE = app


SOURCES += main.cpp\
    game.cpp \
    game_inf.cpp

HEADERS  += \
    game.h \
    game_inf.h

FORMS    += \
    game.ui

RESOURCES += \
    Image.qrc

DISTFILES += \
    pynxl.rc

RC_FILE = \
    myRc.rc
