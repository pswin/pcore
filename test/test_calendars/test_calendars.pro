QT += core
QT -= gui

CONFIG += c++11

TARGET = test_calendars
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

include(../common.pri)

