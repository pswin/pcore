QT += core
QT -= gui

CONFIG += c++11

TARGET = test_profiler
CONFIG += console
CONFIG -= app_bundle

include(../common.pri)

TEMPLATE = app

SOURCES += main.cpp
