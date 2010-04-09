QT += network

CONFIG += qt debug

TEMPLATE = app
MOC_DIR = build
OBJECTS_DIR = build
DESTDIR = dist
TARGET = QTunneler
RCC_DIR = build
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += Base.h \
           BaseWall.h \
           BitmapObj.h \
           Border.h \
           Clicker.h \
           Communicator.h \
           Controller.h \
           DefaultValues.h \
           Evaluator.h \
           Explosion.h \
           GameWindow.h \
           InitDialog.h \
           Initializer.h \
           InitVector.h \
           Matrix.h \
           Model.h \
           NetReceiver.h \
           NetSender.h \
           OrientedRoundObj.h \
           Packet.h \
           PacketQueue.h \
           Projectile.h \
           QueueReceiver.h \
           QueueSender.h \
           Receiver.h \
           RoundObj.h \
           Sender.h \
           SettingsController.h \
           SettingsDialog.h \
           SettingsModel.h \
           Stone.h \
           Tank.h \
           View.h
SOURCES += Base.cpp \
           BaseWall.cpp \
           BitmapObj.cpp \
           Border.cpp \
           Clicker.cpp \
           Communicator.cpp \
           Controller.cpp \
           Evaluator.cpp \
           Explosion.cpp \
           GameWindow.cpp \
           InitDialog.cpp \
           Initializer.cpp \
           main.cpp \
           Matrix.cpp \
           Model.cpp \
           NetReceiver.cpp \
           NetSender.cpp \
           OrientedRoundObj.cpp \
           Packet.cpp \
           PacketQueue.cpp \
           Projectile.cpp \
           QueueReceiver.cpp \
           QueueSender.cpp \
           RoundObj.cpp \
           SettingsController.cpp \
           SettingsDialog.cpp \
           SettingsModel.cpp \
           Stone.cpp \
           Tank.cpp \
           View.cpp
RESOURCES += tile.qrc
