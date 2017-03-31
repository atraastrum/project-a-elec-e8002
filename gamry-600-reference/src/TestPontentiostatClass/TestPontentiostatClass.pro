CONFIG += c++11

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    ../GamryChronoAmperometrySimpleUI/potentiostat.cpp

HEADERS += \
    ../GamryChronoAmperometrySimpleUI/potentiostat.hpp
