#-------------------------------------------------
#
# Project created by QtCreator 2017-09-20T11:50:55
#
#-------------------------------------------------

TEMPLATE = app
CONFIG += strict_c++
CONFIG += console c++11
QMAKE_CXXFLAGS = -std=c++11
CONFIG -= app_bundle
CONFIG += qt


SOURCES += main.cpp \
    marker.cpp \
    markerarray.cpp

HEADERS += \
    marker.h \
    markerarray.h
