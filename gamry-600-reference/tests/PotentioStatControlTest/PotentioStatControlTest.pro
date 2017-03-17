QT += core
QT -= gui

CONFIG += c++11

TARGET = PotentioStatControlTest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    gamrypotentiostat.cpp

HEADERS += \
    gamrypotentiostat.hpp

DISTFILES += \
    temp
