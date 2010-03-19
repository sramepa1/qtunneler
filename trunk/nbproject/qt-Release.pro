TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = QTunneler
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
QT = core gui
SOURCES += Evaluator.cpp Border.cpp Tank.cpp BaseWall.cpp Sender.cpp Clicker.cpp Packet.cpp NetReceiver.cpp PacketQueue.cpp VectorObj.cpp Explosion.cpp Controller.cpp RoundObj.cpp GameWindow.cpp main.cpp Dispatcher.cpp Receiver.cpp Stone.cpp Model.cpp InitDialog.cpp QueueSender.cpp Matrix.cpp Projectile.cpp NetSender.cpp QueueReceiver.cpp Base.cpp
HEADERS += Model.h BaseWall.h QueueReceiver.h Base.h Controller.h Evaluator.h Projectile.h Receiver.h Matrix.h VectorObj.h Dispatcher.h Sender.h PacketQueue.h NetSender.h Tank.h Explosion.h InitDialog.h Border.h Clicker.h Stone.h QueueSender.h GameWindow.h NetReceiver.h Packet.h RoundObj.h
FORMS += InitDialog.ui GameWindow.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
