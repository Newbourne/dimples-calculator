#-------------------------------------------------
#
# Project created by QtCreator 2015-01-30T16:18:17
#
#-------------------------------------------------

QT       += core declarative

QT       -= gui

CONFIG += c++11
QMAKE_CXXFLAGS += -stdlib=libc++
QMAKE_CXXFLAGS += -std=c++11

TARGET = dimples-calculator
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += /usr/local/include\

SOURCES += main.cpp

LIBS += -stdlib=libc++
LIBS += -L/usr/local/lib \
        -lboost_regex

HEADERS += \
    node.h \
    operations.h \
    nodebuilder.h \
    generator.h
