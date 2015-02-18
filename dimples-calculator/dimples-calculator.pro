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
                /usr/local/include/node\

SOURCES += main.cpp \
    Generator.cpp \
    MathNode.cpp \
    NodeBuilder.cpp \
    Operations.cpp \
    init.cc \
    Wrapper.cc

LIBS += -stdlib=libc++

LIBS += -L/usr/local/lib \
        -lboost_regex

HEADERS += \
    MathNode.h \
    Generator.h \
    NodeBuilder.h \
    Operations.h \
    Wrapper.h

DISTFILES += \
    binding.gyp \
    dimples-calculator.js \
    binding.gyp \
    test.js
