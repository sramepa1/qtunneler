TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = qtunneler
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
QT = core gui
SOURCES += SettingsController.cpp Evaluator.cpp Border.cpp Tank.cpp BaseWall.cpp Clicker.cpp SettingsModel.cpp NetReceiver.cpp PacketQueue.cpp Explosion.cpp Controller.cpp RoundObj.cpp GameWindow.cpp View.cpp main.cpp Stone.cpp Model.cpp InitDialog.cpp OrientedRoundObj.cpp Matrix.cpp NetSender.cpp Initializer.cpp BitmapObj.cpp QueueReceiver.cpp SettingsDialog.cpp Base.cpp
HEADERS += Model.h BaseWall.h QueueReceiver.h View.h Base.h Controller.h Evaluator.h Initializer.h SettingsDialog.h Receiver.h Projectile.h Matrix.h InitVector.h Sender.h PacketQueue.h NetSender.h BitmapObj.h SettingsController.h Tank.h Explosion.h InitDialog.h Border.h SettingsModel.h Clicker.h Communicator.h Stone.h QueueSender.h OrientedRoundObj.h GameWindow.h NetReceiver.h DefaultValues.h Packet.h RoundObj.h
FORMS +=
RESOURCES += tile.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = build/
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
