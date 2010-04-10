/* 
 * File:   Validator.cpp
 * Author: pavel
 * 
 * Created on 30. březen 2010, 11:18
 */

#include "Initializer.h"
#include "QueueSender.h"
#include "QueueReceiver.h"
#include "NetReceiver.h"
#include "NetSender.h"

Initializer::Initializer() {
    evaluator = NULL;
}

void Initializer::initGUI() {

    comm = new Communicator(this);

    settingsModel = new SettingsModel(this);
    settingsDialog = new SettingsDialog(settingsModel);
    settingsController = new SettingsController(this,settingsModel,settingsDialog,comm);

    model = new Model(this);
    controller = new Controller(this,model);
    clicker = new Clicker(this);

    initDialog = new InitDialog();
    gameWindow = new GameWindow(model);

    initDialog->show();

    connect(initDialog,SIGNAL(switchToSettings()),settingsDialog,SLOT(showSettings()));
    connect(gameWindow,SIGNAL(switchToDialog()),initDialog,SLOT(showDialog()));

    connect(initDialog, SIGNAL(validateDialog(InitVector)), this, SLOT(validate(InitVector)));
    connect(this, SIGNAL(validated(QString)), initDialog, SLOT(validated(QString)));

    connect(controller,SIGNAL(initInProgress()),this,SLOT(displayInitInProgress()));


    // ---------------------------------------------------------------
    // TODO this is for testing only! startGame() will normally be invoked by controller receiving a start packet!

    connect(settingsDialog,SIGNAL(startGame()),this,SLOT(startGame()));

    // ---------------------------------------------------------------



    connect(settingsDialog,SIGNAL(disconnect()),settingsController,SLOT(closeConnection()));
    connect(settingsController,SIGNAL(disconnected()),initDialog,SLOT(showDialog()));
    connect(settingsController,SIGNAL(connectionEstablished()),this,SLOT(initCore()));
   
    connect(controller,SIGNAL(endGame(QString,bool)),this,SLOT(endGame(QString,bool)));
    connect(controller,SIGNAL(status(QString)),gameWindow,SLOT(setStatus(QString)));
    connect(controller,SIGNAL(redraw(quint32,quint32)),gameWindow,SLOT(redrawView(quint32,quint32)));

    connect(controller,SIGNAL(gameStarts()),this,SLOT(startGame()));
    connect(controller,SIGNAL(gameStarts()),clicker,SLOT(startClock()));
}


void Initializer::validate(InitVector vec) {
    bool ok = false;
    quint32 port = vec.port.toUInt(&ok,10);
    if(!ok || port > 65535 || port == 0) {
        emit validated(vec.port + " is not a valid port number");
    } else {
        emit validated(settingsController->initNetwork(vec.create,(quint16)port,vec.host));
    }
}

void Initializer::initCore() {

    controller->resetStateAndStop();

    if(settingsModel->isCreating()) {
        if(!evaluator) {
            evaluator = new Evaluator(this);
            connect(settingsDialog,SIGNAL(startGame()),evaluator,SLOT(generateWorldAndStartRound()));
        }else {
            evaluator->clearStateAndStop();
        }

        evaluator->addSender(new NetSender(evaluator,comm->socket));
        evaluator->addReceiver(new NetReceiver(evaluator,comm->socket));

        PacketQueue* q = new PacketQueue();
        evaluator->addSender(new QueueSender(evaluator,q));
        controller->setReceiver(new QueueReceiver(controller,q));

        q = new PacketQueue();
        clicker->resetSender(new QueueSender(clicker,q));
        evaluator->addReceiver(new QueueReceiver(evaluator,q));

        evaluator->start();
    }else {
        controller->setReceiver(new NetReceiver(controller,comm->socket));
        clicker->resetSender(new NetSender(clicker,comm->socket));
    }

    controller->start();   
}

void Initializer::displayInitInProgress() {
    settingsModel->setStatus(tr("Starting game..."));
    settingsModel->setReady(false);
    settingsDialog->reload();
}

void Initializer::startGame() {
    disconnect(comm->socket,SIGNAL(disconnected()),0,0);
    connect(comm->socket,SIGNAL(disconnected()),this,SLOT(handleDisconnectInGame()));

    settingsDialog->hide();
    gameWindow->show();
}

void Initializer::endGame(QString message, bool ok) {
    QMessageBox msgBox;
    msgBox.setText(ok ? tr("Finished") : tr("Error"));
    msgBox.setInformativeText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(ok ? QMessageBox::Information : QMessageBox::Critical);
    msgBox.exec();
    controller->quit();
    if(evaluator) evaluator->quit();
    gameWindow->hide();
    initDialog->show();
}

void Initializer::handleDisconnectInGame() {
    endGame(tr("Connection has been lost."),false);
}