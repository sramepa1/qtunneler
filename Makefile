#############################################################################
# Makefile for building: dist/QTunneler
# Generated by qmake (2.01a) (Qt 4.5.2) on: �t 4 13 23:46:39 2010
# Project:  qtunneler.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile qtunneler.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -D_REENTRANT -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -g -D_REENTRANT -Wall -W $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtNetwork -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -Ibuild
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -L/usr/lib -lao -lQtGui -lQtNetwork -lQtCore -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = build/

####### Files

SOURCES       = Base.cpp \
		BaseWall.cpp \
		BitmapObj.cpp \
		Border.cpp \
		Clicker.cpp \
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
		NetReceiverThread.cpp \
		NetSender.cpp \
		OrientedRoundObj.cpp \
		PacketQueue.cpp \
		QueueReceiver.cpp \
		RoundObj.cpp \
		SettingsController.cpp \
		SettingsDialog.cpp \
		SettingsModel.cpp \
		Stone.cpp \
		Tank.cpp \
		View.cpp build/moc_Clicker.cpp \
		build/moc_Communicator.cpp \
		build/moc_Controller.cpp \
		build/moc_Evaluator.cpp \
		build/moc_GameWindow.cpp \
		build/moc_InitDialog.cpp \
		build/moc_Initializer.cpp \
		build/moc_Model.cpp \
		build/moc_NetReceiver.cpp \
		build/moc_NetReceiverThread.cpp \
		build/moc_NetSender.cpp \
		build/moc_PacketQueue.cpp \
		build/moc_QueueReceiver.cpp \
		build/moc_QueueSender.cpp \
		build/moc_Receiver.cpp \
		build/moc_Sender.cpp \
		build/moc_SettingsController.cpp \
		build/moc_SettingsDialog.cpp \
		build/moc_SettingsModel.cpp \
		build/moc_View.cpp \
		build/qrc_tile.cpp \
		build/qrc_tanks.cpp
OBJECTS       = build/Base.o \
		build/BaseWall.o \
		build/BitmapObj.o \
		build/Border.o \
		build/Clicker.o \
		build/Controller.o \
		build/Evaluator.o \
		build/Explosion.o \
		build/GameWindow.o \
		build/InitDialog.o \
		build/Initializer.o \
		build/main.o \
		build/Matrix.o \
		build/Model.o \
		build/NetReceiver.o \
		build/NetReceiverThread.o \
		build/NetSender.o \
		build/OrientedRoundObj.o \
		build/PacketQueue.o \
		build/QueueReceiver.o \
		build/RoundObj.o \
		build/SettingsController.o \
		build/SettingsDialog.o \
		build/SettingsModel.o \
		build/Stone.o \
		build/Tank.o \
		build/View.o \
		build/moc_Clicker.o \
		build/moc_Communicator.o \
		build/moc_Controller.o \
		build/moc_Evaluator.o \
		build/moc_GameWindow.o \
		build/moc_InitDialog.o \
		build/moc_Initializer.o \
		build/moc_Model.o \
		build/moc_NetReceiver.o \
		build/moc_NetReceiverThread.o \
		build/moc_NetSender.o \
		build/moc_PacketQueue.o \
		build/moc_QueueReceiver.o \
		build/moc_QueueSender.o \
		build/moc_Receiver.o \
		build/moc_Sender.o \
		build/moc_SettingsController.o \
		build/moc_SettingsDialog.o \
		build/moc_SettingsModel.o \
		build/moc_View.o \
		build/qrc_tile.o \
		build/qrc_tanks.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		qtunneler.pro
QMAKE_TARGET  = QTunneler
DESTDIR       = dist/
TARGET        = dist/QTunneler

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	@$(CHK_DIR_EXISTS) dist/ || $(MKDIR) dist/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: qtunneler.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtNetwork.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -unix -o Makefile qtunneler.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtNetwork.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile qtunneler.pro

dist: 
	@$(CHK_DIR_EXISTS) build/QTunneler1.0.0 || $(MKDIR) build/QTunneler1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) build/QTunneler1.0.0/ && $(COPY_FILE) --parents Base.h BaseWall.h BitmapObj.h Border.h Clicker.h Communicator.h Controller.h DefaultValues.h Evaluator.h Explosion.h GameWindow.h InitDialog.h Initializer.h InitVector.h Matrix.h Model.h NetReceiver.h NetReceiverThread.h NetSender.h OrientedRoundObj.h Packet.h PacketQueue.h Projectile.h QueueReceiver.h QueueSender.h Receiver.h RoundObj.h Sender.h SettingsController.h SettingsDialog.h SettingsModel.h Stone.h Tank.h View.h build/QTunneler1.0.0/ && $(COPY_FILE) --parents tile.qrc tanks.qrc build/QTunneler1.0.0/ && $(COPY_FILE) --parents Base.cpp BaseWall.cpp BitmapObj.cpp Border.cpp Clicker.cpp Controller.cpp Evaluator.cpp Explosion.cpp GameWindow.cpp InitDialog.cpp Initializer.cpp main.cpp Matrix.cpp Model.cpp NetReceiver.cpp NetReceiverThread.cpp NetSender.cpp OrientedRoundObj.cpp PacketQueue.cpp QueueReceiver.cpp RoundObj.cpp SettingsController.cpp SettingsDialog.cpp SettingsModel.cpp Stone.cpp Tank.cpp View.cpp build/QTunneler1.0.0/ && (cd `dirname build/QTunneler1.0.0` && $(TAR) QTunneler1.0.0.tar QTunneler1.0.0 && $(COMPRESS) QTunneler1.0.0.tar) && $(MOVE) `dirname build/QTunneler1.0.0`/QTunneler1.0.0.tar.gz . && $(DEL_FILE) -r build/QTunneler1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: build/moc_Clicker.cpp build/moc_Communicator.cpp build/moc_Controller.cpp build/moc_Evaluator.cpp build/moc_GameWindow.cpp build/moc_InitDialog.cpp build/moc_Initializer.cpp build/moc_Model.cpp build/moc_NetReceiver.cpp build/moc_NetReceiverThread.cpp build/moc_NetSender.cpp build/moc_PacketQueue.cpp build/moc_QueueReceiver.cpp build/moc_QueueSender.cpp build/moc_Receiver.cpp build/moc_Sender.cpp build/moc_SettingsController.cpp build/moc_SettingsDialog.cpp build/moc_SettingsModel.cpp build/moc_View.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) build/moc_Clicker.cpp build/moc_Communicator.cpp build/moc_Controller.cpp build/moc_Evaluator.cpp build/moc_GameWindow.cpp build/moc_InitDialog.cpp build/moc_Initializer.cpp build/moc_Model.cpp build/moc_NetReceiver.cpp build/moc_NetReceiverThread.cpp build/moc_NetSender.cpp build/moc_PacketQueue.cpp build/moc_QueueReceiver.cpp build/moc_QueueSender.cpp build/moc_Receiver.cpp build/moc_Sender.cpp build/moc_SettingsController.cpp build/moc_SettingsDialog.cpp build/moc_SettingsModel.cpp build/moc_View.cpp
build/moc_Clicker.cpp: Sender.h \
		Packet.h \
		DefaultValues.h \
		Model.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		Clicker.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) Clicker.h -o build/moc_Clicker.cpp

build/moc_Communicator.cpp: Communicator.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) Communicator.h -o build/moc_Communicator.cpp

build/moc_Controller.cpp: DefaultValues.h \
		Receiver.h \
		Packet.h \
		Model.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		Controller.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) Controller.h -o build/moc_Controller.cpp

build/moc_Evaluator.cpp: PacketQueue.h \
		Packet.h \
		Receiver.h \
		Sender.h \
		Model.h \
		DefaultValues.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		Evaluator.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) Evaluator.h -o build/moc_Evaluator.cpp

build/moc_GameWindow.cpp: View.h \
		Model.h \
		DefaultValues.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		Clicker.h \
		Sender.h \
		Packet.h \
		GameWindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) GameWindow.h -o build/moc_GameWindow.cpp

build/moc_InitDialog.cpp: GameWindow.h \
		View.h \
		Model.h \
		DefaultValues.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		Clicker.h \
		Sender.h \
		Packet.h \
		InitVector.h \
		InitDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) InitDialog.h -o build/moc_InitDialog.cpp

build/moc_Initializer.cpp: GameWindow.h \
		View.h \
		Model.h \
		DefaultValues.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		Clicker.h \
		Sender.h \
		Packet.h \
		InitDialog.h \
		InitVector.h \
		SettingsModel.h \
		SettingsController.h \
		SettingsDialog.h \
		Communicator.h \
		Controller.h \
		Receiver.h \
		Evaluator.h \
		PacketQueue.h \
		Initializer.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) Initializer.h -o build/moc_Initializer.cpp

build/moc_Model.cpp: DefaultValues.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		Model.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) Model.h -o build/moc_Model.cpp

build/moc_NetReceiver.cpp: Receiver.h \
		Packet.h \
		QueueReceiver.h \
		PacketQueue.h \
		NetReceiverThread.h \
		DefaultValues.h \
		NetReceiver.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) NetReceiver.h -o build/moc_NetReceiver.cpp

build/moc_NetReceiverThread.cpp: DefaultValues.h \
		PacketQueue.h \
		Packet.h \
		NetReceiverThread.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) NetReceiverThread.h -o build/moc_NetReceiverThread.cpp

build/moc_NetSender.cpp: DefaultValues.h \
		Sender.h \
		Packet.h \
		NetSender.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) NetSender.h -o build/moc_NetSender.cpp

build/moc_PacketQueue.cpp: Packet.h \
		PacketQueue.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) PacketQueue.h -o build/moc_PacketQueue.cpp

build/moc_QueueReceiver.cpp: Receiver.h \
		Packet.h \
		PacketQueue.h \
		QueueReceiver.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) QueueReceiver.h -o build/moc_QueueReceiver.cpp

build/moc_QueueSender.cpp: Sender.h \
		Packet.h \
		PacketQueue.h \
		QueueSender.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) QueueSender.h -o build/moc_QueueSender.cpp

build/moc_Receiver.cpp: Packet.h \
		Receiver.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) Receiver.h -o build/moc_Receiver.cpp

build/moc_Sender.cpp: Packet.h \
		Sender.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) Sender.h -o build/moc_Sender.cpp

build/moc_SettingsController.cpp: SettingsDialog.h \
		SettingsModel.h \
		Communicator.h \
		SettingsController.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) SettingsController.h -o build/moc_SettingsController.cpp

build/moc_SettingsDialog.cpp: SettingsModel.h \
		SettingsDialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) SettingsDialog.h -o build/moc_SettingsDialog.cpp

build/moc_SettingsModel.cpp: SettingsModel.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) SettingsModel.h -o build/moc_SettingsModel.cpp

build/moc_View.cpp: Model.h \
		DefaultValues.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		Clicker.h \
		Sender.h \
		Packet.h \
		View.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) View.h -o build/moc_View.cpp

compiler_rcc_make_all: build/qrc_tile.cpp build/qrc_tanks.cpp
compiler_rcc_clean:
	-$(DEL_FILE) build/qrc_tile.cpp build/qrc_tanks.cpp
build/qrc_tile.cpp: tile.qrc \
		tile.png
	/usr/bin/rcc -name tile tile.qrc -o build/qrc_tile.cpp

build/qrc_tanks.cpp: tanks.qrc \
		tanks/red-SW.png \
		tanks/green-SE.png \
		tanks/green-SW.png \
		tanks/blue-E.png \
		tanks/green-NW.png \
		tanks/red-NE.png \
		tanks/blue-SW.png \
		tanks/blue-SE.png \
		tanks/blue-NW.png \
		tanks/red-E.png \
		tanks/green-E.png \
		tanks/red-N.png \
		tanks/green-S.png \
		tanks/green-W.png \
		tanks/blue-S.png \
		tanks/green-NE.png \
		tanks/blue-W.png \
		tanks/red-NW.png \
		tanks/red-SE.png \
		tanks/blue-NE.png \
		tanks/red-W.png \
		tanks/red-S.png \
		tanks/green-N.png \
		tanks/blue-N.png
	/usr/bin/rcc -name tanks tanks.qrc -o build/qrc_tanks.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

build/Base.o: Base.cpp Base.h \
		DefaultValues.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Base.o Base.cpp

build/BaseWall.o: BaseWall.cpp BaseWall.h \
		BitmapObj.h \
		DefaultValues.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/BaseWall.o BaseWall.cpp

build/BitmapObj.o: BitmapObj.cpp BitmapObj.h \
		DefaultValues.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/BitmapObj.o BitmapObj.cpp

build/Border.o: Border.cpp Border.h \
		DefaultValues.h \
		RoundObj.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Border.o Border.cpp

build/Clicker.o: Clicker.cpp Clicker.h \
		Sender.h \
		Packet.h \
		DefaultValues.h \
		Model.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Clicker.o Clicker.cpp

build/Controller.o: Controller.cpp Controller.h \
		DefaultValues.h \
		Receiver.h \
		Packet.h \
		Model.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		BaseWall.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Controller.o Controller.cpp

build/Evaluator.o: Evaluator.cpp Evaluator.h \
		PacketQueue.h \
		Packet.h \
		Receiver.h \
		Sender.h \
		Model.h \
		DefaultValues.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		BaseWall.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Evaluator.o Evaluator.cpp

build/Explosion.o: Explosion.cpp Explosion.h \
		RoundObj.h \
		DefaultValues.h \
		BitmapObj.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Explosion.o Explosion.cpp

build/GameWindow.o: GameWindow.cpp GameWindow.h \
		View.h \
		Model.h \
		DefaultValues.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		Clicker.h \
		Sender.h \
		Packet.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/GameWindow.o GameWindow.cpp

build/InitDialog.o: InitDialog.cpp InitDialog.h \
		GameWindow.h \
		View.h \
		Model.h \
		DefaultValues.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		Clicker.h \
		Sender.h \
		Packet.h \
		InitVector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/InitDialog.o InitDialog.cpp

build/Initializer.o: Initializer.cpp Initializer.h \
		GameWindow.h \
		View.h \
		Model.h \
		DefaultValues.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		Clicker.h \
		Sender.h \
		Packet.h \
		InitDialog.h \
		InitVector.h \
		SettingsModel.h \
		SettingsController.h \
		SettingsDialog.h \
		Communicator.h \
		Controller.h \
		Receiver.h \
		Evaluator.h \
		PacketQueue.h \
		QueueSender.h \
		QueueReceiver.h \
		NetReceiver.h \
		NetReceiverThread.h \
		NetSender.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Initializer.o Initializer.cpp

build/main.o: main.cpp Initializer.h \
		GameWindow.h \
		View.h \
		Model.h \
		DefaultValues.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		Clicker.h \
		Sender.h \
		Packet.h \
		InitDialog.h \
		InitVector.h \
		SettingsModel.h \
		SettingsController.h \
		SettingsDialog.h \
		Communicator.h \
		Controller.h \
		Receiver.h \
		Evaluator.h \
		PacketQueue.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/main.o main.cpp

build/Matrix.o: Matrix.cpp Matrix.h \
		DefaultValues.h \
		BitmapObj.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Matrix.o Matrix.cpp

build/Model.o: Model.cpp Model.h \
		DefaultValues.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		BaseWall.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Model.o Model.cpp

build/NetReceiver.o: NetReceiver.cpp NetReceiver.h \
		Receiver.h \
		Packet.h \
		QueueReceiver.h \
		PacketQueue.h \
		NetReceiverThread.h \
		DefaultValues.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/NetReceiver.o NetReceiver.cpp

build/NetReceiverThread.o: NetReceiverThread.cpp NetReceiverThread.h \
		DefaultValues.h \
		PacketQueue.h \
		Packet.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/NetReceiverThread.o NetReceiverThread.cpp

build/NetSender.o: NetSender.cpp NetSender.h \
		DefaultValues.h \
		Sender.h \
		Packet.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/NetSender.o NetSender.cpp

build/OrientedRoundObj.o: OrientedRoundObj.cpp OrientedRoundObj.h \
		RoundObj.h \
		DefaultValues.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/OrientedRoundObj.o OrientedRoundObj.cpp

build/PacketQueue.o: PacketQueue.cpp PacketQueue.h \
		Packet.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/PacketQueue.o PacketQueue.cpp

build/QueueReceiver.o: QueueReceiver.cpp QueueReceiver.h \
		Receiver.h \
		Packet.h \
		PacketQueue.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/QueueReceiver.o QueueReceiver.cpp

build/RoundObj.o: RoundObj.cpp RoundObj.h \
		DefaultValues.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/RoundObj.o RoundObj.cpp

build/SettingsController.o: SettingsController.cpp SettingsController.h \
		SettingsDialog.h \
		SettingsModel.h \
		Communicator.h \
		DefaultValues.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/SettingsController.o SettingsController.cpp

build/SettingsDialog.o: SettingsDialog.cpp SettingsDialog.h \
		SettingsModel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/SettingsDialog.o SettingsDialog.cpp

build/SettingsModel.o: SettingsModel.cpp SettingsModel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/SettingsModel.o SettingsModel.cpp

build/Stone.o: Stone.cpp Stone.h \
		BitmapObj.h \
		DefaultValues.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Stone.o Stone.cpp

build/Tank.o: Tank.cpp Tank.h \
		DefaultValues.h \
		OrientedRoundObj.h \
		RoundObj.h \
		Projectile.h \
		BitmapObj.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Tank.o Tank.cpp

build/View.o: View.cpp View.h \
		Model.h \
		DefaultValues.h \
		Base.h \
		Border.h \
		RoundObj.h \
		Matrix.h \
		BitmapObj.h \
		Explosion.h \
		Tank.h \
		OrientedRoundObj.h \
		Projectile.h \
		Stone.h \
		Clicker.h \
		Sender.h \
		Packet.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/View.o View.cpp

build/moc_Clicker.o: build/moc_Clicker.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_Clicker.o build/moc_Clicker.cpp

build/moc_Communicator.o: build/moc_Communicator.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_Communicator.o build/moc_Communicator.cpp

build/moc_Controller.o: build/moc_Controller.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_Controller.o build/moc_Controller.cpp

build/moc_Evaluator.o: build/moc_Evaluator.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_Evaluator.o build/moc_Evaluator.cpp

build/moc_GameWindow.o: build/moc_GameWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_GameWindow.o build/moc_GameWindow.cpp

build/moc_InitDialog.o: build/moc_InitDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_InitDialog.o build/moc_InitDialog.cpp

build/moc_Initializer.o: build/moc_Initializer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_Initializer.o build/moc_Initializer.cpp

build/moc_Model.o: build/moc_Model.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_Model.o build/moc_Model.cpp

build/moc_NetReceiver.o: build/moc_NetReceiver.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_NetReceiver.o build/moc_NetReceiver.cpp

build/moc_NetReceiverThread.o: build/moc_NetReceiverThread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_NetReceiverThread.o build/moc_NetReceiverThread.cpp

build/moc_NetSender.o: build/moc_NetSender.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_NetSender.o build/moc_NetSender.cpp

build/moc_PacketQueue.o: build/moc_PacketQueue.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_PacketQueue.o build/moc_PacketQueue.cpp

build/moc_QueueReceiver.o: build/moc_QueueReceiver.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_QueueReceiver.o build/moc_QueueReceiver.cpp

build/moc_QueueSender.o: build/moc_QueueSender.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_QueueSender.o build/moc_QueueSender.cpp

build/moc_Receiver.o: build/moc_Receiver.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_Receiver.o build/moc_Receiver.cpp

build/moc_Sender.o: build/moc_Sender.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_Sender.o build/moc_Sender.cpp

build/moc_SettingsController.o: build/moc_SettingsController.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_SettingsController.o build/moc_SettingsController.cpp

build/moc_SettingsDialog.o: build/moc_SettingsDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_SettingsDialog.o build/moc_SettingsDialog.cpp

build/moc_SettingsModel.o: build/moc_SettingsModel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_SettingsModel.o build/moc_SettingsModel.cpp

build/moc_View.o: build/moc_View.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/moc_View.o build/moc_View.cpp

build/qrc_tile.o: build/qrc_tile.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/qrc_tile.o build/qrc_tile.cpp

build/qrc_tanks.o: build/qrc_tanks.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/qrc_tanks.o build/qrc_tanks.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

