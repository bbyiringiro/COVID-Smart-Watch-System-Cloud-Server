#-------------------------------------------------
#
# Project created by Chi Wai Leo Kong, MEng Computing & Electronics, H00278458 cwk2@hw.ac.uk
# Digital Twin model for managing assets
# This is the core of the DT
#-------------------------------------------------

QT       += core
QT       += network
QT       += sql

QT       -= gui

TARGET = MultiServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    dataServerR.cpp \
    dataThreadR.cpp

HEADERS += \
    dataServerR.h \
    dataThreadR.h
